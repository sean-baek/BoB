#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <cstdlib>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pbCoffee->setEnabled(false);
    ui->pbTea->setEnabled(false);
    ui->pbMilk->setEnabled(false);
    // button click -> enabled!
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pb10_clicked()
{
    changeMoney(10);
    ui->lcdNumber->display(money);
}

void Widget::on_pb50_clicked()
{
    changeMoney(50);
    ui ->lcdNumber->display(money);
}

void Widget::on_pb100_clicked()
{
   changeMoney(100);
    ui ->lcdNumber->display(money);
}

void Widget::on_pb500_clicked()
{
    changeMoney(500);
    ui ->lcdNumber->display(money);
}

void Widget::on_pbCoffee_clicked()
{
    changeMoney(-100);;
    ui ->lcdNumber->display(money);
}

void Widget::on_pbTea_clicked()
{
    changeMoney(-150);
    ui ->lcdNumber->display(money);
}

void Widget::on_pbMilk_clicked()
{
    changeMoney(-200);
    ui ->lcdNumber->display(money);
}

void Widget::on_pbReset_clicked()
{
    char buf[100];

    int change500 = money / 500; money %= 500;
    int change100 = money / 100; money %= 100;
    int change50 = money / 50; money %= 50;
    int change10 = money / 10; money %= 10;

    sprintf(buf, "500 : %d\n100 :  %d\n50 : %d\n10 : %d\n", change500, change100, change50, change10);
    QMessageBox m;
    m.information(nullptr, "your change is", buf);
}

void Widget::changeMoney(int diff)
{
    money += diff;

    if (money >= 100) ui->pbCoffee->setEnabled(true);
    else ui->pbCoffee->setEnabled(false);

    if(money >= 150) ui->pbTea->setEnabled(true);
    else ui->pbTea->setEnabled(false);

    if(money >= 200) ui->pbMilk->setEnabled(true);
    else ui->pbMilk->setEnabled(false);
}
