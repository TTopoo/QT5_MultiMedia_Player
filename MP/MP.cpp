#include "MP.h"
#include "ui_MP.h"
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTimer>

//������Ƶ��ȫ�ֱ���
QVBoxLayout* layout_video;//����
QMediaPlayer* player;   //������
QVideoWidget* widget;   //��Ƶ���ſؼ�
QTimer* timer;          //���ż�ʱ��
int maxValue = 1000;    //���������ֵ

//����״̬��trueΪ���ţ�falseΪ��ͣ
bool play_state;
//�Ƿ�����������Ƶ
bool if_reload = false;
//�����������Ƿ����
bool state_slider_volume = false;


MP::MP(QWidget* parent) :QMainWindow(parent)
{
    ui.setupUi(this);
    //�������ڣ�����slider_volume,��ʼ��������
    slider_Volume = new CustomSlider(this);
    slider_Volume->setOrientation(Qt::Vertical);

    //��ʼ�������ð�ť
    ui.pushButton_Player->setEnabled(false);
    ui.pushButton_Volume->setEnabled(false);
    ui.pushButton_Speed->setEnabled(false);
    ui.horizontalSlider->setEnabled(false);
    slider_Volume->setEnabled(false);
    slider_Volume->hide();

    //�����ź����
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
    //ѡ����Ƶ�ļ�
    QString filename = QFileDialog::getOpenFileName(this, tr("ѡ����Ƶ�ļ�"), ".",
        tr("��Ƶ��ʽ(*.avi *.mp4 *.flv *.mkv)"));
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(NULL, "Title", "Content", QMessageBox::Ok,
            QMessageBox::Ok);
        return;
    }
    if (if_reload)
    {//���¼�����Ƶʱ���������±���
        delete layout_video;
        delete player;
        delete widget;
        delete timer;
    }
    if_reload = true;

    //ʵ��������ȫ�ֱ���
    layout_video = new QVBoxLayout;
    player = new QMediaPlayer;
    widget = new QVideoWidget;
    //������Ƶ����������Label�ı߾�
    layout_video->setMargin(1);
    //����label_player�ߴ����ò�������
    widget->resize(ui.label->size());
    layout_video->addWidget(widget);
    ui.label->setLayout(layout_video);
    player->setVideoOutput(widget);

    //���ò�����
    player->setMedia(QUrl::fromLocalFile(filename));
    //play_stateΪtrue��ʾ���ţ�false��ʾ��ͣ
    play_state = true;
    ui.pushButton_Volume->setEnabled(true);
    ui.pushButton_Speed->setEnabled(true);
    ui.horizontalSlider->setEnabled(true);
    ui.horizontalSlider->setRange(0, maxValue);
    //���ò���/��ͣ��ť���������ı�����Ϊ����ͣ��
    ui.pushButton_Player->setEnabled(true);
    ui.pushButton_Player->setText(trUtf8("��ͣ"));//������ʾ���������

    timer = new QTimer();
    timer->setInterval(1000);
    timer->start();

    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    //����������
    player->play();
}

void MP::on_pushButton_Player_clicked()
{
    if (play_state) {
        player->pause();
        ui.pushButton_Player->setText(trUtf8("����"));
    }
    else {
        player->play();
        ui.pushButton_Player->setText(trUtf8("��ͣ"));
    }
    play_state = !play_state;
}
void MP::on_pushButton_Speed_clicked()//����ģʽѡ��
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
