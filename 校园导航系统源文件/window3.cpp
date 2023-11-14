#include "window3.h"
#include "ui_window3.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFont>
#include <QFileDialog>
#include <QInputDialog>
QPoint P1_1, P2_1;          //两个临时点
QPoint P_1[51];             //点数组，防越界
QString Pl_1[51], pic_1;    //每个点的标签，pic_1为当前背景图片的存储路径
int ways_1;                 //右侧显示栏路径的数量
double dis_1, min_1;        //dis_1是搜索路径时路径长度当前值，min_1是路径长度最小值
bool showlen_2 = false;     //是否显示当前路径长度
bool showlen_1_2=false;     //是否显示当前路径
struct lines
{
    int a, b;
    bool f = false;
}temp1_1, line_1[101];      //直线，ab是两点p1_1，p2_1的下标，f是否是最短路径，如是则标红，否则保持蓝色。temp1_1是当前线，line_1数组存储所有线
class Stack_1//用于dfs_1，遍历时，“错误”路径时倒退
{
private:
    int a[51] = {};//存储点的下标
    int num = 0;//初始化点的个数
public:
    void push(int n) { a[++num] = n; }  //压入栈
    void pop() { a[num--] = 0; }//出栈
    QString getstr()    //右侧显示栏中点的标签展示，路径结果
    {
        QString str = "";
        for (int i = 1; i < num; i++)
            str += Pl_1[a[i]] + "->";
        str += Pl_1[a[num]];
        return str;
    }

    void showline()//将最短路径标红
    {
        for (int i = 1; i < num; i++)
        {
            for (int j = 1; line_1[j].a && j <= 100; j++)//在line_1[j]存在并且line_1数量在100以内循环
                if ((line_1[j].a == a[i] && line_1[j].b == a[i + 1]) || (line_1[j].b == a[i] && line_1[j].a == a[i + 1]))//如果线当中点的下标与最短路径栈中存储的点下标相同
                {
                    line_1[j].f = true;//标红

                    break;
                }
        }
    }
}stack, temp2_1;//temp2_1存储最短路径对应的栈
int count_1 = 0;//添加的点的默认下标
double window3::dist_1(QPoint a, QPoint b)//计算两点间距离的函数
{
    return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}

bool window3::isin_1(QPoint x, QPoint y, int n)//判断鼠标光标是否点击成功（半径n的圆域范围内）
{
    if (dist_1(x, y) <= n) return true;
    else return false;
}

window3::window3(QWidget* parent) ://构造函数
    QMainWindow(parent),
    ui(new Ui::window3)
{
    ui->setupUi(this);
    this->resize(1500,1000);
    using namespace std;
    QString filename = "E:/QtCode/CampusNavigationMap/MapResource.map2";
    if (filename != "")
    {
        ifstream in(filename.toStdString());
        if (in.is_open())
        {
            string c;
            in >> c;
            ui->label_6->setText(QString::fromStdString(c));//转变为Qstring
            in >> num1 >> num2;
            for (int i = 1; i <= num2; i++)
            {
                int a, b;
                in >> a >> b;
                P_1[i].setX(a);
                P_1[i].setY(b);
                in >> c;
                Pl_1[i] = QString::fromStdString(c);
            }
            for (int i = 1; i <= num2; i++)
                for (int j = 1; j <= num2; j++)
                    in >> matrix_1[i][j];
            for (int i = 1; i <= num1; i++)
                in >> line_1[i].a >> line_1[i].b;
            in >> c;
            pic_1 = QString::fromStdString(c);
            clr_1();
            in.close();//关闭文件
        }
        else QMessageBox::information(this, "提示", "读取失败");
    }
}

window3::~window3()//析构函数
{
    delete ui;
}


void window3::DFS_1(int i, int j)//i为起点，j为终点
{
    reach_1[i] = true;//起点到达
    stack.push(i);//将起点压入栈内
    if (i == j)//判断已经到达终点
    {
        if (ways_1 <= 200000) ui->listWidget->addItem(stack.getstr() + "，长度为：" + QString::number(dis_1)), ways_1++;
        if (min_1 == 0 || dis_1 < min_1)//将最短路径值赋给min_1以及temp2_1
        {
            min_1 = dis_1;
            temp2_1 = stack;
        }
    }
    else//未到达终点，遍历所有可行途径
        for (int t = 1; t <= num2; t++)
            if (matrix_1[i][t] && !reach_1[t])//martrix_1[i][t]存在，即该路径存在，并且P[t]_1未达到
            {
                dis_1 += matrix_1[i][t];//当前路径长度＋目前点到下一个点的距离
                DFS_1(t, j);//递归，t为新的起点
                dis_1 -= matrix_1[i][t];//更换新路径，将此前路径长度减去
            }
    stack.pop();//将最新的点弹出
    reach_1[i] = false;//因为此点弹出，故未达到
}
void window3::clr_1()//清除右侧显示栏的显示信息
{
    ui->label_4->setText("");
    ui->label_5->setText("");
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    for (int i = 1; i <= num1; i++)
        if (line_1[i].f) line_1[i].f = false;  //红线变回蓝线
    update();//调用paintEvent函数
}
void window3::paintEvent(QPaintEvent*)  //绘图函数
{
    QPainter painter(this);//画笔，this为当前窗口
    painter.drawPixmap(450,50,380,536, QPixmap(pic_1));//载入背景图片并显示出来
    QFont font1("Microsoft YaHei", 9);//字体说明
    QFont font2("Microsoft YaHei", 12);
    painter.drawRect(450,50,380,536);//矩形大小，窗口大小
    painter.setFont(font1);
    painter.setRenderHint(QPainter::Antialiasing, true);//使接下来的绘图光滑

    if (showlen_1_2)//如果显示路径
        for (int i = 1; i < num2; i++)
            for (int j = i + 1; j <= num2; j++)
                if (matrix_1[i][j])//若路径存在
                {
                    for (int i = 1; i <= num1; i++)
                    {
                        if (!line_1[i].f) painter.setPen(Qt::blue);//设置画笔颜色为蓝色
                        else painter.setPen(Qt::red);
                        painter.drawLine(P_1[line_1[i].a], P_1[line_1[i].b]);//两点连线
                    }
                }

    painter.setPen(Qt::darkMagenta);
    if (showlen_2)//如果显示路径长
        for (int i = 1; i < num2; i++)
            for (int j = i + 1; j <= num2; j++)
                if (matrix_1[i][j])//若路径存在
                {
                    int x1, y1;
                    x1 = (P_1[i].x() + P_1[j].x()) / 2 - 10;//路径中央偏左
                    y1 = (P_1[i].y() + P_1[j].y()) / 2 + 4;//路径中央偏下
                    painter.drawText(QPoint(x1, y1), QString::number(matrix_1[i][j]));//路径长度显示在（x,y）位置处
                }
    painter.setPen(Qt::black);
    painter.setBrush(Qt::yellow);
    painter.setFont(font2);


    for (int i = 1; i <= num2; i++)
    {
        painter.drawEllipse(P_1[i], 4, 4);         //把点画出来
        painter.drawText(QPoint(P_1[i].x() + 5, P_1[i].y() + 6), Pl_1[i]);//画出点的标签，Pl_1[i]为标签
    }
    ui->label_2->setText("点数：" + QString::number(num2));
    ui->label_3->setText("路径数：" + QString::number(num1));
}
void window3::mousePressEvent(QMouseEvent* event)//功能实现
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint temp_1 = event->pos();//event->pos为当前点击位置
        switch (tp)
        {
        case 8://选择起点
            for (int i = 1; i <= num2; i++)
                if (isin_1(temp_1, P_1[i]))
                {
                    P1_1 = P_1[i]; tp = 9; ui->label->setText("请选择终点");
                    temp1_1.a = i;//起点下标赋给temp1_1
                    ui->label_4->setText("起点：" + Pl_1[i]);
                    ui->label_5->setText("终点：");
                    break;
                }
            break;
        case 9://选择终点
            for (int i = 1; i <= num2; i++)
                if (P_1[i] != P1_1 && isin_1(temp_1, P_1[i]))//判断不与起点重合
                {
                    P2_1 = P_1[i];
                    temp1_1.b = i;//终点下标赋给temp1_1
                    ui->label_5->setText("终点：" + Pl_1[i]);
                    ui->listWidget->clear();
                    ways_1 = 0;
                    min_1 = 0;
                    DFS_1(temp1_1.a, temp1_1.b);
                    if (ways_1)//若有路
                    {
                        if (ways_1 > 200000) ui->listWidget->addItem("路径数过多，超过200000条，无法完全显示！最短路径为：" + temp2_1.getstr() + "，长度为：\n\n" + QString::number(min_1));
                        else ui->listWidget_2->addItem("共" + QString::number(ways_1) + "条路径，其中最短路径为：" + temp2_1.getstr() + "，长度为：" + QString::number(min_1));
                        temp2_1.showline();//最短路径展示
                        update();
                    }
                    else ui->listWidget->addItem("找不到路径");
                    tp = 0;
                    ui->label->setText(""); break;
                }
            break;

        }
    }
}

void window3::on_pushButton_1_clicked()
{
    if (!showlen_1_2) showlen_1_2 = true, ui->pushButton_1->setText("隐藏路径");
    else showlen_1_2 = false, ui->pushButton_1->setText("显示路径");//每点一下切换状态
    update();
}


void window3::on_pushButton_2_clicked()
{
    if (!showlen_2) showlen_2 = true, ui->pushButton_2->setText("隐藏路径长");
    else showlen_2 = false, ui->pushButton_2->setText("显示路径长");//每点一下切换状态
    update();
}


void window3::on_pushButton_3_clicked()
{
    clr_1();
    if (tp != 8) {
        if (num1 == 0) { QMessageBox::warning(this, "警告", "无任何路径"); return; }//判断整个地图是否存在路径
        tp = 8; ui->label->setText("请选择起点");//转到case 8
        ui->label_4->setText("起点："); ui->listWidget->clear();
            ui->label_5->setText("");
        ui->listWidget->addItem("搜索结果将会显示在这里");
    }
    else tp = 0, ui->label->setText("");//跳出
}


void window3::on_pushButton_4_clicked()
{
    this->close();
}


void window3::on_pushButton_5_clicked()
{
    using namespace std;
    QString filename = QFileDialog::getOpenFileName(this, "选择文件", "", "地图文件(*.map2)");
    if (filename != "")
    {
        ifstream in(filename.toStdString());
        if (in.is_open())
        {
            string c;
            in >> c;
            ui->label_6->setText(QString::fromStdString(c));//转变为Qstring
            in >> num1 >> num2;
            for (int i = 1; i <= num2; i++)
            {
                int a, b;
                in >> a >> b;
                P_1[i].setX(a);
                P_1[i].setY(b);
                in >> c;
                Pl_1[i] = QString::fromStdString(c);
            }
            for (int i = 1; i <= num2; i++)
                for (int j = 1; j <= num2; j++)
                    in >> matrix_1[i][j];
            for (int i = 1; i <= num1; i++)
                in >> line_1[i].a >> line_1[i].b;
            in >> c;
            pic_1 = QString::fromStdString(c);
            clr_1();
            QMessageBox::information(this, "提示", "读取成功");
            in.close();//关闭文件
        }
        else QMessageBox::information(this, "提示", "读取失败");
    }
}


void window3::on_pushButton_6_clicked()
{
    QString temp = QFileDialog::getOpenFileName(this, "选择文件", "D:/", "图像文件(*.jpg *.jpeg *.bmg *.png *.gif)");
    if (temp != "") pic_1 = temp;//传入图片存储路径
    update();
}

