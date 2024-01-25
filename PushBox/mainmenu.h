#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QString>
#include <QPixmap>
#include <QPalette>
#include <QDebug>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private:
    QPushButton *btnStartGame;
    QVBoxLayout *layout;

    void init();
    void iniSignalSlots();

// Widget处理
signals:
    void turnToLevelSelect();
};

#endif // MAINMENU_H
