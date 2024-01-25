#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent)
    : QWidget{parent}
{
    init();
    iniSignalSlots();
}

MainMenu::~MainMenu()
{
    if (btnStartGame != nullptr)
        delete btnStartGame;
    if (layout != nullptr)
        delete layout;

    qDebug() << "MainMenu destory";
}

void MainMenu::init()
{
    btnStartGame = new QPushButton;
    QPixmap img(":/icon/img/startBtn.png");
    btnStartGame->setIcon(QIcon(img));
    btnStartGame->setIconSize(img.size());
    btnStartGame->setFocusPolicy(Qt::NoFocus);
    btnStartGame->setStyleSheet("QPushButton{border:none;background:transparent;color:#ffffff;}"
                                "QPushButton:pressed{border-radius:21px;background-color: rgba(0, 0, 255, 0.1)}");


    layout = new QVBoxLayout;
    layout->addStretch(5);
    layout->addWidget(btnStartGame);
    layout->addStretch(5);

    this->setLayout(layout);

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
}

void MainMenu::iniSignalSlots()
{
    connect(btnStartGame, SIGNAL(clicked()), this, SIGNAL(turnToLevelSelect()));
}


