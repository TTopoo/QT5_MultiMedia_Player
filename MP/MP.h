#pragma once
#include <QMainWindow>
#include "customslider.h"
#include "ui_MP.h"
#include <ui_MP.h>
class MP : public QMainWindow
{
    Q_OBJECT

public:
    MP(QWidget* parent = Q_NULLPTR);
    ~MP();
private:
    Ui::MP ui;
    CustomSlider* slider_Volume;

private slots:
    void on_pushButton_Volume_clicked();    //音量控制
    void on_pushButton_Open_clicked();      //打开文件
    void on_pushButton_Player_clicked();    //播放暂停
    void on_pushButton_Speed_clicked();     //倍速控制

    //自定义槽函数
    void horizontalSlider_clicked();
    void horizontalSlider_moved();
    void horizontalSlider_released();
    void slider_Volume_Changed();
    void onTimerOut();

};

