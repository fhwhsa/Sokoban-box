#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    init();
    iniSignalSlots();
}

Widget::~Widget()
{
    qDebug() << "Widget destory";

    saveGameData();

    if (btnMenu != NULL)
        delete btnMenu;
    if (btnLevel != NULL)
        delete btnLevel;
    if (hLayout != NULL)
        delete hLayout;
    if (vlayout != NULL)
        delete vlayout;
    if (stackedWidget != nullptr)
        delete stackedWidget;
}

void Widget::init()
{
    this->setFixedSize(304, 304);
    this->setWindowTitle("推箱子");
    stackedWidget = new QStackedWidget(this);

    btnMenu = new QPushButton();
    btnMenu->setIcon(QIcon(":/icon/img/menu.png"));
    btnLevel = new QPushButton();
    btnLevel->setIcon(QIcon(":/icon/img/level.png"));

    hLayout = new QHBoxLayout();
    hLayout->addWidget(btnMenu);
    hLayout->addWidget(btnLevel);

    vlayout = new QVBoxLayout();
    vlayout->addLayout(hLayout);
    vlayout->addWidget(stackedWidget);
    vlayout->setContentsMargins(2, 2, 2, 2);

    this->setLayout(vlayout);

    mainMenu = new MainMenu;
    pushToStack(mainMenu);
    connect(mainMenu, &MainMenu::turnToLevelSelect, this, &Widget::turnToLevelSelectPage);


    QFile levelData("../PushBox/GameMap/data.txt");
    if (!levelData.open(QIODeviceBase::ReadOnly))
    {
        QMessageBox::critical(this, "错误", "文件打开失败：" + levelData.errorString());
        return;
    }

    levelCnt = 0;
    passLevel = 0;
    using namespace std;
    data = levelData.readAll();

    if (data.isNull())
    {
        QMessageBox::critical(this, "错误", "配置文件为空");
    }

    std::string str = data.toStdString();
    for (int i = str.find("LevelCnt={") + 10; str[i] != '}'; i++)
        levelCnt = levelCnt * 10 + str[i] - '0';
    for (int i = str.find("passLevel={") + 11; str[i] != '}'; i++)
        passLevel = passLevel * 10 + data[i] - '0';

    levelData.close();
}

void Widget::iniSignalSlots()
{
    connect(btnMenu, SIGNAL(clicked()), this, SLOT(do_btnMenu()));
    connect(btnLevel, SIGNAL(clicked()), this, SLOT(do_btnLevel()));
}

void Widget::pushToStack(QWidget *w)
{
    stackedWidget->addWidget(w);
    stackedWidget->setCurrentIndex(stackedWidget->count() - 1);
}

void Widget::back()
{
    int cnt = stackedWidget->count();
    QWidget *w = stackedWidget->currentWidget();
    stackedWidget->setCurrentIndex(cnt - 2);
    delete w;
}

void Widget::turnToLevelSelectPage()
{
    levelSelect = new LevelSelect(passLevel, levelCnt);
    pushToStack(levelSelect);
    connect(levelSelect, &LevelSelect::startGame, this, &Widget::turnToGame);
}

void Widget::turnToGame(QString mapPath, int cl)
{
    game = new Game(mapPath, cl);
    pushToStack(game);
    connect(game, &Game::gamePass, this, &Widget::do_gamePassUpdate);
}

void Widget::saveGameData()
{
    if (data.isNull())
        return;

    QFile file("../PushBox/GameMap/data.txt");
    if (!file.open(QIODeviceBase::WriteOnly | QIODeviceBase::Truncate | QIODeviceBase::Text))
    {
        QMessageBox::critical(this, "文件错误", file.errorString());
        return;
    }

    // 动态数字
    QString str = "LevelCnt={2}\npassLevel={" + QString::number(passLevel) + "}";
    file.write(str.toUtf8());

    file.close();
}

void Widget::do_btnMenu()
{
    while (stackedWidget->count() != 1)
        back();
}

void Widget::do_btnLevel()
{
    while (stackedWidget->count() != 2)
        back();
}

// 更新游戏状态
void Widget::do_gamePassUpdate(int n)
{
    if (n <= passLevel) {
        back();
        return;
    }

    passLevel = n;

    // 更新按钮使能状态
    if (n != levelCnt)
        levelSelect->updatePassLevel(n);
    back();
}


