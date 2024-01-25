#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QIODeviceBase>
#include <QByteArray>
#include <QList>
#include <QMessageBox>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QImage>
#include <QDebug>

enum ElementType {
    block, // 0 空
    wall, // 1 墙
    normalBox, // 2 没进点的箱子
    finshBox, // 3 进点的箱子
    target // 4 目标点
};

class GameMap : public QWidget
{
    Q_OBJECT

public:
    explicit GameMap(QWidget *parent = nullptr);
    ~GameMap();

    static QPoint eleBaseSize; // 图片资源大小

    void paintMap(QPainter *p, QPoint start = QPoint(0, 0));
    bool isNormalBox(QPoint pos); // pos代表坐标，哪一行哪一列，下同
    bool isFinshBox(QPoint pos);
    bool isBlock(QPoint pos);
    bool isTarget(QPoint pos);
    void modifyMap(QPoint pos, ElementType val);
    void loadMap(QString path);
    int getBoxCnt(); // 箱子个数
    int getOriFinshBoxCnt(); // 地图初始时已经进点的箱子

private:
    int row, col, boxCnt, oriFinshBoxCnt;
    QVector<QVector<int>> gameMap;
    QImage *imgBlock, *imgWall, *imgNormalBox, *imgFinshBox, *imgTarget;

    void initImg();
};

#endif // GAMEMAP_H
