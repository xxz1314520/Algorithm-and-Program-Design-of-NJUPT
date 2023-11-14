#include "window2_1.h"
#include "ui_window2_1.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFont>
#include <QFileDialog>
#include <QInputDialog>
QPoint P1, P2;                      //两个临时点，用于
QPoint P[51];                       //最大点数组，防止越界
QString Pl[51], pic;                //每个点的标签，pic为当前背景图片的存储路径，将点显示于背景之上
int ways;                           //右侧显示栏路径的数量
double dis, min;                    //dis是搜索路径时路径长度当前值，min是路径长度最小值
bool showlen = false;               //是否显示当前路径长度
bool showlen_1=false;               //是否显示当前路径
struct lines { int a, b; bool f = false; } temp1, line[101];//两点之间的连线，ab是两点p1，p2的下标，f是否是最短路径，如是则标红，否则保持蓝色。temp1是当前线，line数组存储所有线
class Stack     //用于dfs，遍历时，“错误”路径时倒退
{
private:
    int a[51] = {};//存储点的下标，最大为51个
    int num = 0;//初始化点的个数
public:
    void push(int n) { a[++num] = n; }    //将数据压入栈
    void pop() { a[num--] = 0; }          //数据出栈
    QString getstr()    //获取查询结果信息，在右侧显示栏中的标签显示路径结果
    {
        QString str = "";
        for (int i = 1; i < num; i++)
            str += Pl[a[i]] + "->";          //不同路径之间用"->"隔开
        str += Pl[a[num]];
        return str;
    }

    void showline()//将最短路径标红
    {
        for (int i = 1; i < num; i++)
        {
            for (int j = 1; line[j].a && j <= 100; j++)      //在line[j]存在并且line数量在100以内循环
                if ((line[j].a == a[i] && line[j].b == a[i + 1]) || (line[j].b == a[i] && line[j].a == a[i + 1]))//如果线当中点的下标与最短路径栈中存储的点下标相同
                {
                    line[j].f = true;            //将最短路径标红
                    break;
                }
        }
    }
}stack, temp2;            //temp2存储最短路径对应的栈
int count = 0;            //添加的点的默认下标
double window2_1::dist(QPoint a, QPoint b)    //计算两点间距离，将结果返回给dist
{
    return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}
bool window2_1::isin(QPoint x, QPoint y, int n)//判断鼠标光标是否点击成功（半径n的圆域范围内）
{
    if (dist(x, y) <= n) return true;
    else return false;
}

window2_1::window2_1(QWidget* parent) :   //构造函数
    QMainWindow(parent),
    ui(new Ui::window2_1)
{
    ui->setupUi(this);
    this->resize(1500,1000);     //约定窗口大小
    using namespace std;
    QString filename = "E:/QtCode/CampusNavigationMap/MapResource.map2";    //在界面打开时就加载地图
    if (filename != "")
    {
        ifstream in(filename.toStdString());
        if (in.is_open())          //如果打开则进行读取操作
        {
            string c;
            in >> c;
            ui->label_6->setText(QString::fromStdString(c));//转变为Qstring
            in >> num1 >> num2;
            for (int i = 1; i <= num2; i++)
            {
                int a, b;
                in >> a >> b;
                P[i].setX(a);
                P[i].setY(b);
                in >> c;
                Pl[i] = QString::fromStdString(c);
            }
            for (int i = 1; i <= num2; i++)
                for (int j = 1; j <= num2; j++)
                    in >> matrix[i][j];
            for (int i = 1; i <= num1; i++)
                in >> line[i].a >> line[i].b;
            in >> c;
            pic = QString::fromStdString(c);
            clr();
            in.close();//关闭文件
        }
        else QMessageBox::information(this, "提示", "读取失败");  //反之则报错
    }
}

window2_1::~window2_1()       //析构函数
{
    delete ui;
}


void window2_1::DFS(int i, int j)   //i为点的起点，j为点的终点
{
    reach[i] = true;   //起点到达
    stack.push(i);    //将起点压入栈内
    if (i == j)//判断已经到达终点
    {
        if (ways <= 200000) ui->listWidget->addItem(stack.getstr() + "，长度为：" + QString::number(dis)), ways++;
        if (min == 0 || dis < min)//将最短路径值赋给min以及temp2
        {
            min = dis;
            temp2 = stack;
        }
    }
    else//未到达终点，遍历所有可行途径
        for (int t = 1; t <= num2; t++)
            if (matrix[i][t] && !reach[t])//matrix[i][t]存在，即该路径存在，并且P[t]未达到
            {
                dis += matrix[i][t];//当前路径长度＋目前点到下一个点的距离
                DFS(t, j);//递归，t为新的起点
                dis -= matrix[i][t];//更换新路径，将此前路径长度减去
            }
    stack.pop();//将最新的点弹出
    reach[i] = false;//因为此点弹出，故未达到
}
void window2_1::clr()//清除右侧显示栏的显示信息
{
    ui->label_4->setText("");
    ui->label_5->setText("");
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    for (int i = 1; i <= num1; i++)
        if (line[i].f) line[i].f = false;  //红线变回蓝线
    update();//调用paintEvent函数
}
void window2_1::paintEvent(QPaintEvent*)  //绘图函数
{
    QPainter painter(this);//画笔，this为当前窗口
    painter.drawPixmap(450,50,380,536, QPixmap(pic));//载入背景图片并显示出来
    QFont font1("Microsoft YaHei", 9);//字体说明
    QFont font2("Microsoft YaHei", 12);
    painter.drawRect(450,50,380,536);//矩形大小，窗口大小
    painter.setFont(font1);
    painter.setRenderHint(QPainter::Antialiasing, true);//使接下来的绘图光滑

    if (showlen_1)//如果显示路径
        for (int i = 1; i < num2; i++)
            for (int j = i + 1; j <= num2; j++)
                if (matrix[i][j])//若路径存在
                {
                    for (int i = 1; i <= num1; i++)
                    {
                        if (!line[i].f) painter.setPen(Qt::blue);//设置画笔颜色为蓝色
                        else painter.setPen(Qt::red);
                        painter.drawLine(P[line[i].a], P[line[i].b]);//两点连线
                    }
                }

    painter.setPen(Qt::darkMagenta);
    if (showlen)//如果显示路径长
        for (int i = 1; i < num2; i++)
            for (int j = i + 1; j <= num2; j++)
                if (matrix[i][j])//若路径存在
                {
                    int x1, y1;
                    x1 = (P[i].x() + P[j].x()) / 2 - 10;//路径中央偏左
                    y1 = (P[i].y() + P[j].y()) / 2 + 4;//路径中央偏下
                    painter.drawText(QPoint(x1, y1), QString::number(matrix[i][j]));//路径长度显示在（x,y）位置处
                }
    painter.setPen(Qt::black);
    painter.setBrush(Qt::yellow);
    painter.setFont(font2);


    for (int i = 1; i <= num2; i++)
    {
        painter.drawEllipse(P[i], 4, 4);         //把点画出来
        painter.drawText(QPoint(P[i].x() + 5, P[i].y() + 6), Pl[i]);//画出点的标签，pl[i]为标签
    }
    ui->label_2->setText("点数：" + QString::number(num2));
    ui->label_3->setText("路径数：" + QString::number(num1));
}
void window2_1::mousePressEvent(QMouseEvent* event)//功能实现
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint temp = event->pos();//event->pos为当前点击位置
        switch (tp)
        {
        case 1://选择第一个点
            if (num1 == 100) QMessageBox::warning(this, "警告", "路径数已达上限");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, P[i]))//选中
                    {
                        P1 = P[i]; line[num1 + 1].a = i; tp = 2; ui->label->setText("请选择第二个点"); break;//将第一个点信息存入P1，line[num1+1]，并开始case2功能
                    }
            break;
        case 2://选择第二个点
            for (int i = 1; i <= num2; i++)
                if (P[i] != P1 && isin(temp, P[i]))//若选中了与第一个点不同的点
                {
                    int t = num1++;//线数量+1
                    P2 = P[i]; line[num1].b = i; tp = 1;//P2信息录入，完善line[num1]信息（num1已+1），tp回归1.
                    if (line[num1].a > line[num1].b)//保证线的第一个点下标比第二个小
                    {
                        int t1 = line[num1].a; line[num1].a = line[num1].b; line[num1].b = t1;
                    }
                    for (int j = 1; j < num1; j++)//判断是否路线已经存在
                    {
                        if (line[num1].a == line[j].a && line[num1].b == line[j].b)
                        {
                            line[num1--] = line[0];
                            QMessageBox::warning(this, "警告", "两条路径重合");
                            break;
                        }
                    }
                    if (t != num1)//将两点间的像素距离赋值给两点间的路径长度（默认）
                        matrix[line[num1].a][line[num1].b] = matrix[line[num1].b][line[num1].a] = dist(P[line[num1].a], P[line[num1].b]);
                    ui->label->setText("请选择第一个点");
                    break;
                }
            update();
            break;
        case 3://添加点
            if (num2 < 50 && temp.x() >= 450 && temp.x() <=830  && temp.y()>50 && temp.y() <= 586)//判断所加的点是否在窗口范围内
            {
                int t = num2++;
                for (int i = 1; i < num2; i++)
                    if (isin(temp, P[i], 20))//判断两点是否太近，选中条件为“半径10的圆邻域”，故两点距离需要大于20
                    {
                        num2--; QMessageBox::warning(this, "警告", "两个点靠太近");
                    }
                if (t == num2) break;
                P[num2] = event->pos();//当前位置赋给最新的P点
                Pl[num2] = QString::number(++count);//创建默认标签
                update();
            }
            else if (num2 == 50) QMessageBox::warning(this, "警告", "点数已达上限");
            else QMessageBox::warning(this, "警告", "点超出边界");
            break;
        case 4://删除点
            if (num2 == 0) QMessageBox::warning(this, "警告", "无任何点");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, P[i]))//选中想要删除的点
                    {
                        for (int j = i; j < num2; j++)
                        {
                            P[j] = P[j + 1];//将删除的点后的点前移
                            Pl[j] = Pl[j + 1];//点的标签同理
                            for (int k = 1; k <= num2; k++)//此一系列对matrix的操作使该点下标对应的行列删除
                                matrix[j][k] = matrix[j + 1][k];
                        }
                        for (int j = i; j < num2; j++)
                            for (int k = 1; k <= num2; k++)
                                matrix[k][j] = matrix[k][j + 1];
                        for (int j = 1; j <= num2; j++)
                            matrix[j][num2] = matrix[num2][j] = 0;
                        Pl[num2] = Pl[0];//最后一个点标签消失
                        P[num2--] = P[0];//最后一个点消失
                        for (int j = 1; j <= num1; j++)
                        {
                            if (i == line[j].a || i == line[j].b)//将line数组一并前移
                            {
                                for (int k = j; k < num1; k++)
                                    line[k] = line[k + 1];
                                line[num1--] = line[0];//将最后一条线消除，同时线数量减一
                                j--;
                            }
                            else//下标原在被选中的点之后的点所在线的下标前移
                            {
                                if (line[j].a > i) line[j].a--;
                                if (line[j].b > i) line[j].b--;
                            }
                        }
                        update();
                        break;
                    }
            break;
        case 5://选择第一个点删除路径
            if (num1 == 0) QMessageBox::warning(this, "警告", "无任何路径");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, P[i]))//判断选中
                    {
                        P1 = P[i]; temp1.a = i; tp = 6; ui->label->setText("请选择要删除路径的第二个点");
                    }
            break;
        case 6://选择第二个点删除路径
            for (int i = 1; i <= num2; i++)
            {
                if (P[i] != P1 && isin(temp, P[i]))//选中
                {
                    P2 = P[i]; temp1.b = i; tp = 5;//第二个点信息载入
                    if (temp1.a > temp1.b)//保证线的第二个点下标大于第一个
                    {
                        int t1 = temp1.a; temp1.a = temp1.b; temp1.b = t1;
                    }
                    int t3 = num1;
                    for (int j = 1; j <= num1; j++)
                    {
                        if (temp1.a == line[j].a && temp1.b == line[j].b)
                        {
                            matrix[line[j].a][line[j].b] = matrix[line[j].b][line[j].a] = 0;//点之间路径长度删除
                            {for (int k = j; k < num1; k++)
                                line[k] = line[k + 1];//路径（线）下标前移
                            line[num1--] = line[0];
                            break; }
                        }
                    }
                    ui->label->setText("请选择要删除路径的第一个点");
                    if (num1 == t3) QMessageBox::warning(this, "警告", "找不到这条路径");
                    else break;
                }
            }
            update(); break;
        case 7://编辑点的标签
            if (num2 == 0) QMessageBox::warning(this, "警告", "无任何点");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, P[i]))
                    {
                        QString s0 = QInputDialog::getText(this, "编辑标签", "输入文本(最多13个字)");
                        if (s0 != "") Pl[i] = s0.left(13);
                        break;
                    }
            break;
        case 8://选择起点
            for (int i = 1; i <= num2; i++)
                if (isin(temp, P[i]))
                {
                    P1 = P[i]; tp = 9; ui->label->setText("请选择终点");
                    temp1.a = i;//起点下标赋给temp1
                    ui->label_4->setText("起点：" + Pl[i]);
                    ui->label_5->setText("终点：");
                    break;
                }
            break;
        case 9://选择终点
            for (int i = 1; i <= num2; i++)
                if (P[i] != P1 && isin(temp, P[i]))//判断不与起点重合
                {
                    P2 = P[i];
                    temp1.b = i;//终点下标赋给temp1
                    ui->label_5->setText("终点：" + Pl[i]);
                    ui->listWidget->clear();
                    ways = 0;
                    min = 0;
                    DFS(temp1.a, temp1.b);
                    if (ways)//若有路
                    {
                        if (ways > 200000) ui->listWidget->addItem("路径数过多，超过200000条，无法完全显示！最短路径为：" + temp2.getstr() + "，长度为：\n\n" + QString::number(min));
                        else ui->listWidget_2->addItem("共" + QString::number(ways) + "条路径，其中最短路径为：" + temp2.getstr() + "，长度为：" + QString::number(min));
                        temp2.showline();                //最短路径展示
                        update();
                    }
                    else ui->listWidget->addItem("找不到路径");
                    tp = 0;
                    ui->label->setText(""); break;
                }
            break;
        case 10://编辑路径长度第一个点
            if (num1 == 0) QMessageBox::warning(this, "警告", "无任何路径");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, P[i]))//选中
                    {
                        P1 = P[i]; tp = 11; ui->label->setText("请选择要编辑路径长度的第二个点");//转入下一个case
                        temp1.a = i;
                        break;
                    }
            break;
        case 11://编辑路径长度第二个点
            for (int i = 1; i <= num2; i++)
                if (P[i] != P1 && isin(temp, P[i]))//不与第一个点重合
                {
                    P2 = P[i];
                    temp1.b = i;
                    tp = 10;
                    if (temp1.a > temp1.b)//保证线的第二个点下标大于第一个
                    {
                        int t1 = temp1.a; temp1.a = temp1.b; temp1.b = t1;
                    }
                    bool f0 = false;
                    for (int j = 1; j <= num1; j++)
                    {
                        if (temp1.a == line[j].a && temp1.b == line[j].b)
                        {
                            double number = QInputDialog::getDouble(this, "编辑长度", "输入浮点数(0.0001~999999)", matrix[temp1.a][temp1.b], 0.0001, 999999, 4);
                            if (number) matrix[temp1.a][temp1.b] = matrix[temp1.b][temp1.a] = number;//若输入了数，则点之间长度更改
                            f0 = true;
                            break;
                        }
                    }
                    ui->label->setText("请选择要编辑路径长度的第一个点");
                    if (!f0) QMessageBox::warning(this, "警告", "找不到这条路径");
                    update();
                    break;
                }
            break;
        }
    }
}

void window2_1::on_pushButton_clicked()
{
    clr();
    if (tp != 3) tp = 3, ui->label->setText("请选择一个位置添加点");//转到case 3
    else tp = 0, ui->label->setText("");//跳出
}

void window2_1::on_pushButton_2_clicked()
{
    clr();
    if (tp != 1) tp = 1, ui->label->setText("请选择第一个点");//转到case 1
    else tp = 0, ui->label->setText("");//跳出
}

void window2_1::on_pushButton_3_clicked()
{
    clr();
    if (tp != 4) tp = 4, ui->label->setText("请选择一个位置删除点");//转到case 4
    else tp = 0, ui->label->setText("");//跳出
}

void window2_1::on_pushButton_4_clicked()
{
    clr();
    if (tp != 5) tp = 5, ui->label->setText("请选择要删除路径的第一个点");//转到case 5
    else tp = 0, ui->label->setText("");//跳出
}

void window2_1::on_pushButton_5_clicked()
{
    clr();
    if (tp != 10) tp = 10, ui->label->setText("请选择要编辑路径长度的第一个点");//转到case 10
    else tp = 0, ui->label->setText("");//跳出
}

void window2_1::on_pushButton_6_clicked()
{
    clr();
    if (tp != 8) {
        if (num1 == 0) { QMessageBox::warning(this, "警告", "无任何路径"); return; }//判断整个地图是否存在路径
        tp = 8; ui->label->setText("请选择起点");//转到case 8
        ui->label_4->setText("起点："); ui->listWidget->clear();
            ui->label_5->setText("");
        ui->listWidget->addItem("搜索结果将会显示在这里");
    }
    else tp = 0, ui->label->setText("");//跳出
}

void window2_1::on_pushButton_7_clicked()
{
    clr();
    if (tp != 7) tp = 7, ui->label->setText("请选择要编辑标签的点");//转到case 7
    else tp = 0, ui->label->setText("");//跳出
}

void window2_1::on_pushButton_8_clicked()
{
    if (!showlen) showlen = true, ui->pushButton_8->setText("隐藏路径长");
    else showlen = false, ui->pushButton_8->setText("显示路径长");//每点一下切换状态
    update();
}



void window2_1::on_pushButton_9_clicked()
{
    QString s0 = QInputDialog::getText(this, "编辑标题", "输入文本(最多28个字)", QLineEdit::Normal, ui->label_6->text());
    if (s0 != "") ui->label_6->setText(s0.left(28));//跳出
}

void window2_1::on_pushButton_10_clicked()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "提示", "确认要清除地图吗？", QMessageBox::Yes | QMessageBox::No);
    if (btn == QMessageBox::Yes)//清除地图
    {
        pic = "";
        for (int i = 1; i <= num2; i++)
        {
            P[i] = P[0];
            Pl[i] = Pl[0];
            for (int j = 1; j <= num2; j++)
                matrix[i][j] = 0;
        }
        for (int i = 1; i <= num1; i++)
            line[i] = line[0];
        tp = num2 = num1 = count = 0;
        clr();
        ui->label->setText("");
    }
}

void window2_1::on_pushButton_11_clicked()//载入地图
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
                P[i].setX(a);
                P[i].setY(b);
                in >> c;
                Pl[i] = QString::fromStdString(c);
            }
            for (int i = 1; i <= num2; i++)
                for (int j = 1; j <= num2; j++)
                    in >> matrix[i][j];
            for (int i = 1; i <= num1; i++)
                in >> line[i].a >> line[i].b;
            in >> c;
            pic = QString::fromStdString(c);
            clr();
            QMessageBox::information(this, "提示", "读取成功");
            in.close();//关闭文件
        }
        else QMessageBox::information(this, "提示", "读取失败");
    }
}

void window2_1::on_pushButton_12_clicked()//保存地图
{
    using namespace std;
    QString filename = QFileDialog::getSaveFileName(this, "保存文件", "", "地图文件(*.map2)");    //文件扩展名为.map2
    if (filename != "")//判断地址是否输入成功
    {
        ofstream out(filename.toStdString());//转换为标准字符串进行保存
        if (out.is_open())
        {
            out << ui->label_6->text().toStdString() << endl;
            out << num1 << ' ' << num2 << endl;
            for (int i = 1; i <= num2; i++)
                out << P[i].x() << ' ' << P[i].y() << ' ' << Pl[i].toStdString() << endl;//空格隔开
            for (int i = 1; i <= num2; i++)
            {
                for (int j = 1; j <= num2; j++)
                    out << matrix[i][j] << ' ';
                out << endl;
            }
            for (int i = 1; i <= num1; i++)
                out << line[i].a << ' ' << line[i].b << endl;
            out << pic.toStdString() << endl;
            QMessageBox::information(this, "提示", "保存成功");
            out.close();//关闭文档
        }
        else QMessageBox::information(this, "提示", "保存失败");
    }
}

void window2_1::on_pushButton_13_clicked()//改背景
{
    QString temp = QFileDialog::getOpenFileName(this, "选择文件", "D:/", "图像文件(*.jpg *.jpeg *.bmg *.png *.gif)");
    if (temp != "") pic = temp;//传入图片存储路径
    update();
}

void window2_1::on_pushButton_14_clicked()
{
    if (!showlen_1) showlen_1 = true, ui->pushButton_14->setText("隐藏路径");
    else showlen_1 = false, ui->pushButton_14->setText("显示路径");//每点一下切换状态
    update();
}

