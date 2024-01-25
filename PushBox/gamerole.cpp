#include "gamerole.h"

GameRole::GameRole(QWidget *parent)
    : QWidget{parent}
{
    init();
    currPos = QPoint(1, 1);
    currType = RoleType::right;
}

GameRole::~GameRole()
{
    if (imgUp != nullptr)
        delete imgUp;
    if (imgDown != nullptr)
        delete imgDown;
    if (imgLeft != nullptr)
        delete imgLeft;
    if (imgRight != nullptr)
        delete imgRight;

    qDebug() << "GameRole destory";
}

QPoint GameRole::eleBaseSize = QPoint(30, 30);

void GameRole::init()
{
    imgUp = new QImage(":/icon/img/up.png");
    imgDown = new QImage(":/icon/img/down.png");
    imgLeft = new QImage(":/icon/img/left.png");
    imgRight = new QImage(":/icon/img/right.png");
}

void GameRole::paint(QPainter *p)
{
    QPoint d = QPoint(currPos.y() * eleBaseSize.x(), currPos.x() * eleBaseSize.y());
    switch (currType) {
    case up:
        p->drawImage(d, *imgUp);
        break;
    case down:
        p->drawImage(d, *imgDown);
        break;
    case left:
        p->drawImage(d, *imgLeft);
        break;
    case right:
        p->drawImage(d, *imgRight);
        break;
    }
}

QPoint GameRole::getCurrPos()
{
    return currPos;
}

RoleType GameRole::getCurrType()
{
    return currType;
}

void GameRole::changePos(QPoint pos, RoleType type)
{
    currPos = pos;
    currType = type;
}
