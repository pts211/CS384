#include "algorithmrunner.h"

AlgorithmRunner::AlgorithmRunner(QVector<QGraphicsEllipseItem*> tCircleList, QObject *uiParent) :
    QThread()
{

    for(QGraphicsEllipseItem *c : tCircleList){
        QPoint pos = QPoint(c->rect().x(), c->rect().y());
        people.push_back(new Person(tCircleList.indexOf(c), pos, this));
    }
    Person::PEOPLE_TOTAL = people.size();


    for(Person *p1 : people){
        //Configure each person's one-to-one signals and slots.
        connect(p1, SIGNAL(SendAwk(int,int)), this, SLOT(onSendAwk(int,int)));
        connect(p1, SIGNAL(EnterCS(int)), this, SLOT(onEnterCS(int)));
        connect(p1, SIGNAL(ChangePosition(int,int)), uiParent, SLOT(onChangePosition(int,int)));
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

//-------------------- SIGNALS Start --------------------
void AlgorithmRunner::onSendAwk(int id, int reqId) {
    people[reqId]->receiveAwk(id);
}

void AlgorithmRunner::onEnterCS(int id) {
    people[id]->start();
}
//-------------------- SIGNALS End --------------------

//-------------------- FUNCTIONS Start --------------------
void AlgorithmRunner::run() {
    QVector<int> indexes;
    for(int j=0; j<people.size(); j++){ indexes.push_back(j); }

    QVector<int> randomInd = this->randomize(indexes);

    for(int i=0; i<this->people.size(); i++){
        int temp = randomInd[i];
        this->people[temp]->requestCS();
        this->msleep(5);
    }
}

QVector<int> AlgorithmRunner::randomize(QVector<int> ind) {
    qsrand(QTime::currentTime().msec());
    QVector<int> tVec;

    int origSize = ind.size();
    for(int i=0; i<origSize; i++){
        int rindex = rangedRand(ind.size());
        tVec.push_back(ind[rindex]);
        ind.removeAt(rindex);
    }
    return tVec;
}

int AlgorithmRunner::rangedRand(unsigned int max){
    return (qrand() % (max));
}



