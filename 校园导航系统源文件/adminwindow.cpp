#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "window2_1.h"
#include <QMessageBox>

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    connect(ui->BackpushButton,&QPushButton::clicked,this,[=](){emit this->back();});
    this->page4 = new window2_1;
    connect(ui->LoginpushButton,&QPushButton::clicked,this,[=](){
            if(ui->lineEdit->text()=="admin"&&ui->lineEdit_2->text()=="xxz520")
            {
                this->page4->show();
            }
            else
            {
                QMessageBox::information(this, "提示", "用户名或密码输入错误！");
            }


});
}
AdminWindow::~AdminWindow()
{
    delete ui;
}
