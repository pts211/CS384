#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth((6));

    int size_x = 40;
    int size_y = 40;

    c1 = scene->addEllipse(0,0,size_x,size_y,blackpen,redBrush);
    c2 = scene->addEllipse(0,50,size_x,size_y,blackpen,redBrush);
    c3 = scene->addEllipse(400,100,size_x,size_y,blackpen,blueBrush);
    c4 = scene->addEllipse(400,150,size_x,size_y,blackpen,blueBrush);

//    c1->setFlag(QGraphicsItem::ItemIsMovable);
}

Widget::~Widget()
{
    delete ui;
}
