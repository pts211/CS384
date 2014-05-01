//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Algorithm Runner.cpp
//This class serves as a worker thread and manages execution of the algorithm.
#include "algorithmrunner.h"


AlgorithmRunner::AlgorithmRunner(QVector<QGraphicsEllipseItem*> tCircleList, QObject *uiParent) :
    QThread()
{
    for(QGraphicsEllipseItem *c : tCircleList){
        QPoint pos = QPoint(c->rect().x(), c->rect().y());
        people.push_back(new Person(tCircleList.indexOf(c), pos, this));
    }
    Person::PEOPLE_TOTAL = people.size();

    connect(uiParent, SIGNAL(ChangeSpeed(int,int)), this, SLOT(onSpeedChange(int,int)));

    for(Person *p1 : people){
        //Configure each person's one-to-one signals and slots.
        connect(p1, SIGNAL(SendAwk(int,int)), this, SLOT(onSendAwk(int,int)));
        connect(p1, SIGNAL(EnterCS(int)), this, SLOT(onEnterCS(int)));
        connect(p1, SIGNAL(ChangePosition(int,QPoint)), uiParent, SLOT(onChangePosition(int,QPoint)));
        for(Person *p2 : people){
            //Configure each person's one-to-many signals and slots.
            connect(p1, SIGNAL(SendRequest(int,QPoint)), p2, SLOT(ReceiveRequest(int,QPoint)));
        }
    }
}

//-------------------- SLOTS Start --------------------
void AlgorithmRunner::onSendAwk(int id, int reqId) {
    people[reqId]->receiveAwk(id);
}

void AlgorithmRunner::onEnterCS(int id) {
    people[id]->start();
}

void AlgorithmRunner::onSpeedChange(int id, int speed) {
    people[id]->setSpeed(speed);
}

//-------------------- SLOTS End --------------------



//-------------------- FUNCTIONS Start --------------------
void AlgorithmRunner::run() {
    foreach(Person *p, people) {
        p->start();
    }
}

QVector<QPoint> AlgorithmRunner::getPoints()
{
    return points;
}

void AlgorithmRunner::setPoints(QVector<QPoint> value)
{
    points = value;
}



