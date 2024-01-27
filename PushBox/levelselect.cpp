#include "levelselect.h"

LevelSelect::LevelSelect(int pl, int lc, QWidget *parent)
    : QWidget{parent},
    passLevel(pl),
    levelCnt(lc)
{
    init();
    iniSignalSlots();
}

LevelSelect::~LevelSelect()
{
    qDebug() << "LevelSelect destory";
    delete layout;
}

void LevelSelect::updatePassLevel(int l)
{
    if (l <= passLevel || l == levelCnt)
        return;

    passLevel = l;
    btnList[passLevel]->setEnabled(true);
}


void LevelSelect::init()
{
    // 设置背景图片
    setAutoFillBackground(true);    // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    //palette.setColor(QPalette::Window, Qt::red);  // 设置背景色
    //palette.setBrush(this->backgroundRole(), Qt::black);// 设置背景色
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":/icon/img/bg.jpg").scaled(    // 缩放背景图.
                         this->size(),
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation)));    // 使用平滑的缩放方式
    this->setPalette(palette);


    layout = new QGridLayout;
    for (int i = 0; i < levelCnt; i++)
    {
        QPushButton* tmp = new QPushButton(QString::number(i + 1), this);
        tmp->setFixedSize(QSize(50, 50));
        btnList.push_back(tmp);
        if (i > passLevel)
            tmp->setEnabled(false);
        path.push_back("./GameMap/" + QString::number(i + 1) + ".txt");
        layout->addWidget(tmp, i / 3, i % 3);
    }
    this->setLayout(layout);
}

void LevelSelect::iniSignalSlots()
{
    int i = 0;
    for (QPushButton* btn : btnList)
    {
        connect(btn, &QPushButton::clicked, [this, i](){
            emit startGame(path[i], i + 1);
        });
        i++;
    }
}


