#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "window2_1.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
     window2_1 *page4 = NULL;
    ~AdminWindow();
signals:
    void back();
    void login();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
