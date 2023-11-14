#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMenuBar>
#include "window2.h"
#include "adminwindow.h"
#include <QDebug>
#include<QMessageBox>
#pragma warning(disable:4189)


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->page2 = new Window2;
    this->page3 = new AdminWindow;
    connect(ui->actionfr,SIGNAL(triggered()),this,SLOT(Slot_admin()));
    connect(ui->actionaada,SIGNAL(triggered()),this,SLOT(Slot_information1()));
    connect(ui->actionka,SIGNAL(triggered()),this,SLOT(Slot_DevelopPersonnel()));
    connect(ui->actionmi,SIGNAL(triggered()),this,SLOT(Slot_AcknowledgementPersonnel()));
    connect(ui->actionhj,SIGNAL(triggered()),this,SLOT(Slot_information2()));
    connect(ui->actionkj,SIGNAL(triggered()),this,SLOT(Slot_ContactUs()));
    connect(ui->BeginpushButton,&QPushButton::clicked,this,[=](){
        this->hide();
        this->page2->show();
    });
    connect(this->page2,&Window2::back,[=](){
        this->page2->hide();
        this->show();
    });
    connect(this->page3,&AdminWindow::back,[=](){
        this->page3->hide();
        this->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Slot_admin()
{
    this->hide();
    this->page3->show();

}
void MainWindow::Slot_information1()
{
    QMessageBox MBox;

    MBox.setWindowTitle("2023.10.30版本信息");
    MBox.setText("此程序开发历经两个版本。\n\n2023.10.30版本为最初版本。");
    MBox.setText("2023.11.10版本为最新版本。");
    MBox.setStyleSheet("QLabel{"
                       "min-width:400px;"
                       "min-height:240px;"
                       "font-size:18px;"
                       "}");
    MBox.exec();

}
void MainWindow::Slot_information2()
{
    QMessageBox MBox;
    MBox.setWindowTitle("使用须知");
    MBox.setText("  默认用户名为 'admin',密码为 'xxz520'。\n\n  提醒：由于QT打包发布的缺陷，您需要在MapSo\n\nurce.map2文件中，将底部的文件路径改为您的\n\n资源路径");
    MBox.setStyleSheet("QLabel{"
                       "min-width:400px;"
                       "min-height:240px;"
                       "font-size:18px;"
                       "}");
    MBox.exec();
}
void MainWindow::Slot_DevelopPersonnel()
{
    QMessageBox MBox;
    MBox.setWindowTitle("开发人员");
    MBox.setText("    此程序由南京邮电大学计算机学院、软件学院、\n\n网络空间安全学院B21031317徐相赵开发。");
    MBox.setStyleSheet("QLabel{"
                       "min-width:400px;"
                       "min-height:240px;"
                       "font-size:18px;"
                       "}");
    MBox.exec();
}
void MainWindow::Slot_AcknowledgementPersonnel()
{
    QMessageBox MBox;
    MBox.setWindowTitle("鸣谢人员");
    MBox.setText("    此程序特别鸣谢南京邮电大学教育与技术学院\n\nB21150305冯紫嵚同学，感谢她所制作提供的图\n\n片资源！");
    MBox.setStyleSheet("QLabel{"
                       "min-width:400px;"
                       "min-height:240px;"
                       "font-size:18px;"
                       "}");
    MBox.exec();
}
void MainWindow::Slot_ContactUs()
{
    QMessageBox MBox;
    MBox.setWindowTitle("帮助");
    MBox.setText("    如发现有任何问题，请联系19552690991进行\n\n维护。");
    MBox.setStyleSheet("QLabel{"
                       "min-width:400px;"
                       "min-height:240px;"
                       "font-size:18px;"
                       "}");
    MBox.exec();
}
