#include "gamemap.h"

GameMap::GameMap(QWidget *parent)
    : QWidget{parent}
{
    initImg();
}

GameMap::~GameMap()
{
    if (imgBlock != nullptr)
        delete imgBlock;
    if (imgWall != nullptr)
        delete imgWall;
    if (imgNormalBox != nullptr)
        delete imgNormalBox;
    if (imgFinshBox != nullptr)
        delete imgFinshBox;
    if (imgTarget != nullptr)
        delete imgTarget;

    qDebug() << "GameMap destory";
}

QPoint GameMap::eleBaseSize = QPoint(30, 30);

void GameMap::initImg()
{
    imgBlock = new QImage(":/icon/img/block.png");
    imgWall = new QImage(":/icon/img/wall.png");
    imgNormalBox = new QImage(":/icon/img/normalBox.png");
    imgFinshBox = new QImage(":/icon/img/finshBox.png");
    imgTarget = new QImage(":/icon/img/target.png");
}

void GameMap::loadMap(QString path)
{
    QFile mapData(path);
    if (!mapData.open(QIODeviceBase::ReadOnly))
    {
        QMessageBox::critical(this, "错误", "文件打开失败：" + mapData.errorString());
        return;
    }

    QByteArray data = mapData.readAll();
    QList<QByteArray> dataList = data.split('\n');

    boxCnt = oriFinshBoxCnt = 0;
    // 最后一行为空，导入资源bug？
    for (int i = 0; i < dataList.size() - 1; i++) {
        QVector<int> t;
        for (const QByteArray& it : dataList[i].split(','))
        {
            int type = it.toInt();
            if (type == normalBox)
                boxCnt++;
            if (type == finshBox)
            {
                boxCnt++;
                oriFinshBoxCnt++;
            }
            t.push_back(type);
        }
        gameMap.push_back(t);
    }

    row = gameMap.size();
    col = gameMap[0].size();
}

int GameMap::getBoxCnt()
{
    return boxCnt;
}

int GameMap::getOriFinshBoxCnt()
{
    return oriFinshBoxCnt;
}

void GameMap::paintMap(QPainter *p, QPoint start)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            QPoint d = QPoint(j * eleBaseSize.x(), i * eleBaseSize.y());
            p->drawImage(start + d, *imgBlock);
            switch (gameMap[i][j]) {
                case wall:
                {
                    p->drawImage(start + d, *imgWall);
                    break;
                }
                case normalBox:
                {
                    p->drawImage(start + d, *imgNormalBox);
                    break;
                }
                case finshBox:
                {
                    p->drawImage(start + d, *imgFinshBox);
                    break;
                }
                case target:
                {
                    p->drawImage(start + d, *imgTarget);
                    break;
                }
            }
        }
    }

}

bool GameMap::isNormalBox(QPoint pos)
{
    if (gameMap[pos.x()][pos.y()] == ElementType::normalBox)
        return true;
    return false;
}

bool GameMap::isFinshBox(QPoint pos)
{
    if (gameMap[pos.x()][pos.y()] == ElementType::finshBox)
        return true;
    return false;
}

bool GameMap::isBlock(QPoint pos)
{
    if (gameMap[pos.x()][pos.y()] == ElementType::block)
        return true;
    return false;
}

bool GameMap::isTarget(QPoint pos)
{
    if (gameMap[pos.x()][pos.y()] == ElementType::target)
        return true;
    return false;
}

void GameMap::modifyMap(QPoint pos, ElementType val)
{
    gameMap[pos.x()][pos.y()] = val;
}
