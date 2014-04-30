//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Widget.cpp
//This class manages the UI of the program.

#include "widget.h"
#include "ui_widget.h"

#include <QtCore>

QVector<int> tRequests;
QVector<int> tAwks;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lbl_speed->setText("Update Speed: " + QString("%1").arg(ui->slider_speed->value()) + " ms");


    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth((6));

    circles.push_back(scene->addEllipse(MIN_X, 0, CSIZE, CSIZE, blackpen, redBrush));
    circles.push_back(scene->addEllipse(MIN_X, 50,CSIZE, CSIZE, blackpen, redBrush));
    circles.push_back(scene->addEllipse(MAX_X, 100, CSIZE, CSIZE, blackpen, blueBrush));
    circles.push_back(scene->addEllipse(MAX_X, 150, CSIZE, CSIZE, blackpen, blueBrush));
}

//-------------------- SIGNALS Start --------------------
void Widget::onChangePosition(int id, int change)
{
    circles[id]->moveBy(change, 0);
}

//-------------------- SIGNALS End --------------------




//-------------------- FUNCTIONS Start --------------------
QVector<QGraphicsEllipseItem*> Widget::getCircleList() {
    return this->circles;
}

//-------------------- FUNCTIONS End --------------------


//-------------------- BUTTONS Start --------------------
void Widget::on_btn_start_clicked()
{
    mAR->start();
}

void Widget::on_rd_Ricart_toggled(bool checked)
{
    if(checked){
        Person::ALG_MODE = 1;
    }
}

void Widget::on_rd_Two_toggled(bool checked)
{
    if(checked){
        Person::ALG_MODE = 2;
    }
}

void Widget::on_slider_speed_sliderMoved(int speed)
{
    //needs to get speed as well as the slider that is moved.
    Person::SPEED = speed;
    ui->lbl_speed->setText("Update Speed: " + QString("%1").arg(speed) + " ms");
}

void Widget::on_chk_random_toggled(bool checked)
{
    mAR->setRandom(checked);
}
//-------------------- BUTTONS End --------------------


Widget::~Widget()
{
    delete ui;
}
