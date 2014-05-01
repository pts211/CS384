//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Widget.cpp
//This class manages the UI of the program.

#include "widget.h"
#include "ui_widget.h"

#include <QtCore>

QVector<int> tRequests;
QVector<int> tAwks;
QVector<QPoint> GLOBAL_POINTS;

//X and Y offset.
int O_X = 100;
int O_Y = 100;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lbl_speed_1->setText("Red Speed: " + QString("%1").arg(ui->slider_speed_1->value()));
    ui->lbl_speed_2->setText("Green Speed: " + QString("%1").arg(ui->slider_speed_2->value()));
    ui->lbl_speed_3->setText("Blue Speed: " + QString("%1").arg(ui->slider_speed_3->value()));
    ui->lbl_speed_4->setText("Yellow Speed: " + QString("%1").arg(ui->slider_speed_4->value()));

    //Create a new scene with the origin in the upper left corner.
    scene = new QGraphicsScene(0, 0, ui->graphicsView->width()-2, ui->graphicsView->height()-2);
    ui->graphicsView->setScene(scene);


    QBrush redBrush(Qt::red);
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QBrush yellowBrush(Qt::yellow);
    QPen blackpen(Qt::black);
    blackpen.setWidth((6));

    points.append(QPoint(0  , 0  ));
    points.append(QPoint(300, 0  ));
    points.append(QPoint(300, 100));
    points.append(QPoint(685, 100));
    points.append(QPoint(685, 0  ));
    points.append(QPoint(985, 0  ));
    points.append(QPoint(985, 300));
    points.append(QPoint(685, 300));
    points.append(QPoint(685, 200));
    points.append(QPoint(300, 200));
    points.append(QPoint(300, 300));
    points.append(QPoint(0  , 300));

    //Add desired offset.
    for(int i=0; i<points.size(); i++) {
        points[i].setX(points[i].x() + O_X);
        points[i].setY(points[i].y() + O_Y);
    }

    GLOBAL_POINTS = points;

    drawLines();


    circles.push_back(scene->addEllipse(0 +O_X  , 100 +O_Y, CSIZE, CSIZE, blackpen, redBrush));
    circles.push_back(scene->addEllipse(0 +O_X  , 200 +O_Y, CSIZE, CSIZE, blackpen, greenBrush));
    circles.push_back(scene->addEllipse(985 +O_X, 100 +O_Y, CSIZE, CSIZE, blackpen, blueBrush));
    circles.push_back(scene->addEllipse(985 +O_X, 200 +O_Y, CSIZE, CSIZE, blackpen, yellowBrush));

}

void Widget::drawLines() {

    QPen blackpen(Qt::black);
    blackpen.setWidth(2);

    foreach(QPoint p, points) {
        int nextIndex = 0;
        if( p != points.last() ) {
            nextIndex = points.indexOf(p) + 1;
        }
        QPoint n = points.at(nextIndex);
        scene->addLine(p.x(), p.y(), n.x(), n.y(), blackpen);
    }
}

//-------------------- SIGNALS Start --------------------
void Widget::onChangePosition(int id, QPoint change)
{
    circles[id]->moveBy(change.x(), change.y());
}
//-------------------- SIGNALS End --------------------




//-------------------- FUNCTIONS Start --------------------
QVector<QGraphicsEllipseItem*> Widget::getCircleList() {
    return this->circles;
}

void Widget::setRunner(AlgorithmRunner *tAR){
    this->mAR = tAR;
    this->mAR->setPoints(this->points);
    //connect(this, SIGNAL(ChangeSpeed(int,int)),this->mAR, SLOT(onChangeSpeed(int,int)));
    on_slider_speed_1_valueChanged(ui->slider_speed_1->value());
    on_slider_speed_2_valueChanged(ui->slider_speed_2->value());
    on_slider_speed_3_valueChanged(ui->slider_speed_3->value());
    on_slider_speed_4_valueChanged(ui->slider_speed_4->value());
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


void Widget::on_slider_speed_1_valueChanged(int speed)
{
    emit ChangeSpeed(0, speed);
    ui->lbl_speed_1->setText("Red Speed: " + QString("%1").arg(ui->slider_speed_1->value()));
}

void Widget::on_slider_speed_2_valueChanged(int speed)
{
    emit ChangeSpeed(1, speed);
    ui->lbl_speed_2->setText("Green Speed: " + QString("%1").arg(ui->slider_speed_2->value()));
}

void Widget::on_slider_speed_3_valueChanged(int speed)
{
    emit ChangeSpeed(2, speed);
    ui->lbl_speed_3->setText("Blue Speed: " + QString("%1").arg(ui->slider_speed_3->value()));
}

void Widget::on_slider_speed_4_valueChanged(int speed)
{
    emit ChangeSpeed(3, speed);
    ui->lbl_speed_4->setText("Yellow Speed: " + QString("%1").arg(ui->slider_speed_4->value()));
}
//-------------------- BUTTONS End --------------------


Widget::~Widget()
{
    delete ui;
}
