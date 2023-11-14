#include "window2.h"
#include "ui_window2.h"
#include <QMediaPlayer>
#include<QAudioOutput>
#include "window3.h"
#include<QFileDialog>

Window2::Window2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window2)
{
    ui->setupUi(this);
    connect(ui->BackpushButton,&QPushButton::clicked,this,[=](){
        emit this->back();
    });
    this->page5 = new window3;
    connect(ui->StartFind,&QPushButton::clicked,this,[=](){
        this->hide();
        this->page5->show();
    });
    QAudioOutput *audioOutput = new QAudioOutput(this);
    QMediaPlayer *mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl::fromLocalFile("E:/QtCode/CampusNavigationMap/Voice.MP3"));
    connect(ui->VoicepushButton,&QPushButton::clicked,this,[=](){
        //QString filename = QFileDialog::getOpenFileName(this, "音频文件(*.MP3)");
        //mediaPlayer->setSource(QUrl::fromLocalFile(filename));
        mediaPlayer->play();
    });
    connect(ui->StopVoicepushButton,&QPushButton::clicked,this,[=](){
        mediaPlayer->stop();
    });
}

Window2::~Window2()
{
    delete ui;
}


