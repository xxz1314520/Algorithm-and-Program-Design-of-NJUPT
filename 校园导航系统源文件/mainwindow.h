#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "window2.h"
#include "ui_mainwindow.h"
#include<QMenuBar>
#include "window2.h"
#include "adminwindow.h"
#include <QDebug>
#include<QMessageBox>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Window2 *page2=NULL;
    AdminWindow *page3= NULL;
    ~MainWindow();

private slots:
    void Slot_admin();
    void Slot_information1();
    void Slot_information2();
    void Slot_DevelopPersonnel();
    void Slot_AcknowledgementPersonnel();
    void Slot_ContactUs();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
