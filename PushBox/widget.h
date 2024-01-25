#ifndef WIDGET_H
#define WIDGET_H

#include "game.h"
#include "mainmenu.h"
#include "levelselect.h"

#include <QWidget>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QByteArray>
#include <QDataStream>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
//    virtual void keyPressEvent(QKeyEvent *event);

private:
    QStackedWidget* stackedWidget;
    QHBoxLayout *hLayout;
    QVBoxLayout *vlayout;
    MainMenu *mainMenu;
    LevelSelect *levelSelect;
    Game *game;
    QPushButton *btnMenu, *btnLevel;

    int levelCnt;
    int passLevel;
    QByteArray data;

    void init();
    void iniSignalSlots();
    void pushToStack(QWidget* w);
    void back();
    void turnToLevelSelectPage();
    void turnToGame(QString mapPath, int cl);
    void saveGameData();

private slots:
    void do_btnMenu();
    void do_btnLevel();
    void do_gamePassUpdate(int n);

};
#endif // WIDGET_H
