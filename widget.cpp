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


    for(QGraphicsEllipseItem *c : circles){
        QPoint pos = QPoint(c->rect().x(), c->rect().y());
        people.push_back(new Person(circles.indexOf(c), pos, this));
    }
    Person::PEOPLE_TOTAL = people.size();


    for(Person *p1 : people){
        //Configure each person's one-to-one signals and slots.
        connect(p1, SIGNAL(SendAwk(int,int)), this, SLOT(onSendAwk(int,int)));
        connect(p1, SIGNAL(EnterCS(int)), this, SLOT(onEnterCS(int)));
        connect(p1, SIGNAL(ChangePosition(int,int)), this, SLOT(onChangePosition(int,int)));
        for(Person *p2 : people){
            //Configure each person's one-to-many signals and slots.
            connect(p1, SIGNAL(SendRequest(int)), p2, SLOT(ReceiveRequest(int)));
//            if(!(people.indexOf(p1) == people.indexOf(p2))) {
//                connect(p1, SIGNAL(SendRequest(int)), p2, SLOT(ReceiveRequest(int)));
//            }
        }
    }




//    c1->setFlag(QGraphicsItem::ItemIsMovable);
}

void Widget::onChangePosition(int id, int change)
{
    circles[id]->moveBy(change, 0);
//    ui->lbl_id->setText(QString::number(id));
//    ui->lbl_delta->setText(QString::number(change));
}

void Widget::onRun(int id, int deltaX)
{
    ui->lbl_id->setText(QString::number(id));
    ui->lbl_delta->setText(QString::number(deltaX));
}

void Widget::onSendAwk(int id, int reqId) {
    people[reqId]->receiveAwk(id);
}

void Widget::onEnterCS(int id) {
    people[id]->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_start_clicked()
{
    int x = 1;
    people[0]->requestCS();
    for(int z=0; z<1000000; z++){
        x=x*x;
    }
    people[3]->requestCS();
    for(int z=0; z<1000000; z++){
        x=x*x;
    }
    people[2]->requestCS();
    for(int z=0; z<1000000; z++){
        x=x*x;
    }
    people[1]->requestCS();

//    for(Person *p : people){}
}

void Widget::on_btn_stop_clicked()
{
    QVector<int> *tempReqs = &tRequests;
    QVector<int> *tempAwks = &tAwks;
    qDebug("Hellow World");
    //for(Person *p : people){
//        p->mStop = true;
//    }
}
