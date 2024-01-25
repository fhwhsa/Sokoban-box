#ifndef GAMEROLE_H
#define GAMEROLE_H

#include <QWidget>
#include <QImage>
#include <QString>
#include <QPainter>
#include <QPoint>
#include <QImage>
#include <QDebug>

enum RoleType {
    up, // 朝上
    down,
    left,
    right
};

// 改变角色位置时，需要先调用changPos函数改变位置，再调用paint函数
class GameRole : public QWidget
{
    Q_OBJECT
public:
    explicit GameRole(QWidget *parent = nullptr);
    ~GameRole();

    static QPoint eleBaseSize; // 图片资源大小
    void paint(QPainter *p);
    QPoint getCurrPos();
    RoleType getCurrType();
    void changePos(QPoint pos, RoleType type = RoleType::right);

private:
    RoleType currType;
    QPoint currPos; // 代表坐标，哪一行哪一列
    QImage *imgUp, *imgDown, *imgLeft, *imgRight;

    void init();

signals:

};

#endif // GAMEROLE_H
