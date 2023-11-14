#ifndef WINDOW2_1_H
#define WINDOW2_1_H

#include <QMainWindow>
#include <cmath>
#include <QMainWindow>
#include <fstream>

namespace Ui {
class window2_1;
}

class window2_1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit window2_1(QWidget *parent = nullptr);
    int tp = 0;
    int num1 = 0, num2 = 0;
    double matrix[51][51] = {};
    bool reach[51] = {};
    void DFS(int P1, int P2);
    bool isin(QPoint x, QPoint y, int n = 10);
    double dist(QPoint a, QPoint b);
    void clr();
    ~window2_1();
private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_14_clicked();

private:
    Ui::window2_1 *ui;
};

#endif // WINDOW2_1_H
