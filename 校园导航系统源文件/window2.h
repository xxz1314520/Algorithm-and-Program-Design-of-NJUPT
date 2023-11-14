#ifndef WINDOW2_H
#define WINDOW2_H

#include <QMainWindow>
 #include <QMediaPlayer>
#include "window3.h"


namespace Ui {
class Window2;
}

class Window2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window2(QWidget *parent = nullptr);
    window3 *page5 =NULL;
    ~Window2();

signals:
    void back();

private:
    Ui::Window2 *ui;
};

#endif // WINDOW2_H
