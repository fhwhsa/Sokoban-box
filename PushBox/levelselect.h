#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <QVector>
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <QGridLayout>

class LevelSelect : public QWidget
{
    Q_OBJECT
public:
    explicit LevelSelect(int passLevel, int levelCnt, QWidget *parent = nullptr);
    ~LevelSelect();

    void updatePassLevel(int l);

private:
    int levelCnt; // 总关卡数
    int passLevel; // 通关数
    QGridLayout *layout;
    QVector<QPushButton*> btnList; // 关卡选择按钮
    QVector<QString> path; // 按钮对应的关卡地图资源文件

    void init();
    void iniSignalSlots();

// Widget处理
signals:
    void startGame(QString mapPath, int cl);
};

#endif // LEVELSELECT_H
