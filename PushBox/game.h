#ifndef GAME_H
#define GAME_H

#include "gamemap.h"
#include "gamerole.h"

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QString>
#include <QDebug>

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QString path, int cl, QWidget *parent = nullptr);
    ~Game();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    QPainter *painter;
    GameMap *gameMap;
    GameRole *gameRole;
    QTimer *timerForUpdate, *timerForTicking;
    int finshCnt; // 到目标点的箱子
    int currLevel; // 当前关卡号
    int second; // 用于计时

    void loadGame(QString path); // 初始化

// 由Widget接收
signals:
    void gamePass(int n);
};

#endif // GAME_H
