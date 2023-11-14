#ifndef WINDOW3_H
#define WINDOW3_H

#include <QMainWindow>
#include <cmath>
#include <QMainWindow>
#include <fstream>

namespace Ui {
class window3;
}

class window3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit window3(QWidget *parent = nullptr);
    int tp = 0;
    int num1 = 0, num2 = 0;
    double matrix_1[51][51] = {};
    bool reach_1[51] = {};
    void DFS_1(int P1_1, int P2_1);
    bool isin_1(QPoint x, QPoint y, int n = 10);
    double dist_1(QPoint a, QPoint b);
    void clr_1();
    ~window3();

private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::window3 *ui;
};

#endif // WINDOW3_H
