#include "game.h"

Game::Game(QString path, int cl, QWidget *parent)
    : QWidget{parent}
{
    currLevel = cl;
    loadGame(path);
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

Game::~Game()
{
    if (timerForUpdate != nullptr)
        delete timerForUpdate;
    if (timerForTicking != nullptr)
        delete timerForTicking;
    if (gameRole != nullptr)
        delete gameRole;
    if (gameMap != nullptr)
        delete gameMap;
    if (painter != nullptr)
        delete painter;

    qDebug() << "Game destory";
}

void Game::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    painter->begin(this);

    gameMap->paintMap(painter);

    gameRole->paint(painter);

    painter->end();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    QPoint roleMovePos;
    RoleType type;

    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
        {
            roleMovePos = QPoint(-1, 0);
            type = RoleType::up;
            break;
        }

        case Qt::Key_S:
        case Qt::Key_Down:
        {
            roleMovePos = QPoint(1, 0);
            type = RoleType::down;
            break;
        }

        case Qt::Key_A:
        case Qt::Key_Left:
        {
            roleMovePos = QPoint(0, -1);
            type = RoleType::left;
            break;
        }

        case Qt::Key_D:
        case Qt::Key_Right:
        {
            roleMovePos = QPoint(0, 1);
            type = RoleType::right;
            break;
        }

        default:
        {
            roleMovePos = QPoint(0, 0);
            type = gameRole->getCurrType();
            break;
        }
    }


    QPoint roleNewPos = gameRole->getCurrPos() + roleMovePos;

    if (gameMap->isBlock(roleNewPos) || gameMap->isTarget(roleNewPos)) // 角色新位置是空地或者目标点
        gameRole->changePos(roleNewPos, type);
    else if (gameMap->isNormalBox(roleNewPos) || gameMap->isFinshBox(roleNewPos)) // 角色新位置是箱子（未到目标点/到目标点）
    {
        QPoint newBoxPos = roleNewPos; // 箱子新位置
        switch (type) {
        case RoleType::up :
            newBoxPos += QPoint(-1, 0);
            break;
        case RoleType::down :
            newBoxPos += QPoint(1, 0);
            break;
        case RoleType::left :
            newBoxPos += QPoint(0, -1);
            break;
        case RoleType::right :
            newBoxPos += QPoint(0, 1);
            break;
        }

        if (gameMap->isBlock(newBoxPos)) // 箱子新位置是空地
        {
            if (gameMap->isFinshBox(roleNewPos))
                finshCnt--;
            gameMap->modifyMap(newBoxPos, ElementType::normalBox);
            gameMap->modifyMap(roleNewPos, gameMap->isFinshBox(roleNewPos) ? ElementType::target : ElementType::block);
            gameRole->changePos(roleNewPos, type);
        }
        else if (gameMap->isTarget(newBoxPos)) // 箱子新位置是目标点
        {
            if (gameMap->isFinshBox(roleNewPos))
                finshCnt--;
            gameMap->modifyMap(newBoxPos, ElementType::finshBox);
            gameMap->modifyMap(roleNewPos, gameMap->isFinshBox(roleNewPos) ? ElementType::target : ElementType::block);
            gameRole->changePos(roleNewPos, type);
            finshCnt++;
        }

        if (finshCnt == gameMap->getBoxCnt()) // 判断是否所有箱子进点
        {
            timerForTicking->stop();
            timerForUpdate->stop();
            QMessageBox::information(this, tr(""), "You win!!\nIt takes " + QString::number(second) + " seconds");
            emit gamePass(currLevel);
        }

    }
}


void Game::loadGame(QString path)
{
    gameMap = new GameMap(this);
    gameRole = new GameRole(this);
    painter = new QPainter(this);

    gameMap->loadMap(path);
    gameRole->changePos(QPoint(1, 1)); // 人物位置

    finshCnt = gameMap->getOriFinshBoxCnt();

    timerForUpdate = new QTimer();
    timerForUpdate->callOnTimeout(this, QOverload<>::of(&Game::update));
    timerForUpdate->start(100);

    second = 0;
    timerForTicking = new QTimer();
    timerForTicking->setTimerType(Qt::PreciseTimer);
    timerForTicking->callOnTimeout(this, [this](){second++;});
    timerForTicking->start(1000);
}
