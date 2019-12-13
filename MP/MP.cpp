#include "MP.h"
#include "ui_MP.h"
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTimer>

//播放视频的全局变量
QVBoxLayout* layout_video;//布局
QMediaPlayer* player;   //播放器
QVideoWidget* widget;   //视频播放控件
QTimer* timer;          //播放计时器
int maxValue = 1000;    //进度条最大值

//播放状态，true为播放，false为暂停
bool play_state;
//是否重新载入视频
bool if_reload = false;
//音量控制条是否出现
bool state_slider_volume = false;


MP::MP(QWidget* parent) :QMainWindow(parent)
{
    ui.setupUi(this);
    //音量调节：设置slider_volume,初始化、方向
    slider_Volume = new CustomSlider(this);
    slider_Volume->setOrientation(Qt::Vertical);

    //初始化不可用按钮
    ui.pushButton_Player->setEnabled(false);
    ui.pushButton_Volume->setEnabled(false);
    ui.pushButton_Speed->setEnabled(false);
    ui.horizontalSlider->setEnabled(false);
    slider_Volume->setEnabled(false);
    slider_Volume->hide();

    //连接信号与槽
    connect(ui.horizontalSlider, &CustomSlider::costomSliderClicked,
        this, &MP::horizontalSlider_clicked);
    connect(ui.horizontalSlider, &CustomSlider::sliderMoved,
        this, &MP::horizontalSlider_moved);
    connect(ui.horizontalSlider, &CustomSlider::sliderReleased,
        this, &MP::horizontalSlider_released);
    connect(slider_Volume, &CustomSlider::costomSliderClicked,
        this, &MP::slider_Volume_Changed);
    connect(slider_Volume, &CustomSlider::sliderMoved,
        this, &MP::slider_Volume_Changed);
}

MP::~MP()
{
}

void MP::on_pushButton_Volume_clicked()
{
    if (state_slider_volume) {
        slider_Volume->setEnabled(false);
        slider_Volume->hide();
    }
    else {
        slider_Volume->setEnabled(true);
        slider_Volume->setValue(player->volume());
        slider_Volume->setGeometry((QRect(ui.pushButton_Volume->pos().rx() +
            0.5 * ui.pushButton_Volume->width() - 15,
            ui.pushButton_Volume->y() - 100, 30, 102)));
        slider_Volume->show();
    }
    state_slider_volume = !state_slider_volume;
}

void MP::on_pushButton_Open_clicked()
{
    //选择视频文件
    QString filename = QFileDialog::getOpenFileName(this, tr("选择视频文件"), ".",
        tr("视频格式(*.avi *.mp4 *.flv *.mkv)"));
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(NULL, "Title", "Content", QMessageBox::Ok,
            QMessageBox::Ok);
        return;
    }
    if (if_reload)
    {//重新加载视频时，重置以下变量
        delete layout_video;
        delete player;
        delete widget;
        delete timer;
    }
    if_reload = true;

    //实例化三个全局变量
    layout_video = new QVBoxLayout;
    player = new QMediaPlayer;
    widget = new QVideoWidget;
    //设置视频播放区域与Label的边距
    layout_video->setMargin(1);
    //根据label_player尺寸设置播放区域
    widget->resize(ui.label->size());
    layout_video->addWidget(widget);
    ui.label->setLayout(layout_video);
    player->setVideoOutput(widget);

    //设置播放器
    player->setMedia(QUrl::fromLocalFile(filename));
    //play_state为true表示播放，false表示暂停
    play_state = true;
    ui.pushButton_Volume->setEnabled(true);
    ui.pushButton_Speed->setEnabled(true);
    ui.horizontalSlider->setEnabled(true);
    ui.horizontalSlider->setRange(0, maxValue);
    //启用播放/暂停按钮，并将其文本设置为“暂停”
    ui.pushButton_Player->setEnabled(true);
    ui.pushButton_Player->setText(trUtf8("暂停"));//这里显示会出现问题

    timer = new QTimer();
    timer->setInterval(1000);
    timer->start();

    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    //播放器开启
    player->play();
}

void MP::on_pushButton_Player_clicked()
{
    if (play_state) {
        player->pause();
        ui.pushButton_Player->setText(trUtf8("播放"));
    }
    else {
        player->play();
        ui.pushButton_Player->setText(trUtf8("暂停"));
    }
    play_state = !play_state;
}
void MP::on_pushButton_Speed_clicked()//倍速模式选择
{
    static int j = 1;
    switch (j)
    {
    case 1:
        player->setPlaybackRate(2);
        ui.pushButton_Speed->setText(trUtf8("X2"));
        j++;
        break;
    case 2:
        player->setPlaybackRate(0.5);
        ui.pushButton_Speed->setText(trUtf8("X0.5"));
        j++;
        break;
    case 3:
        player->setPlaybackRate(1);
        ui.pushButton_Speed->setText(trUtf8("X1"));
        j = 1;
        break;
    }
}

void MP::slider_Volume_Changed()
{
    player->setVolume(slider_Volume->value());
}

void MP::onTimerOut()
{
    ui.horizontalSlider->setValue(player->position() * maxValue / player->duration());
}

void MP::horizontalSlider_clicked()
{
    player->setPosition(ui.horizontalSlider->value() * player->duration() / maxValue);
}

void MP::horizontalSlider_moved()
{
    timer->stop();
    player->setPosition(ui.horizontalSlider->value() * player->duration() / maxValue);
}

void MP::horizontalSlider_released()
{
    timer->start();
}
