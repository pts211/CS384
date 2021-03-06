//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Person.cpp
//This class represents a process, a process will want to get into the CS.

#include "person.h"
#include <QtCore>

int Person::PEOPLE_TOTAL(0);
int Person::SPEED(5);

//ALG_MODE=1 : Ricart
//ALG_MODE=2 : Two-by-Two
int Person::ALG_MODE(1);

//A global containing all of the points of the "track", formally
//declared in widget.cpp.
extern QVector<QPoint> GLOBAL_POINTS;

Person::Person(int tId, QPoint pos, QObject *parent) :
    QThread(parent)
{
    this->id = tId;
    this->inCS = false;
    this->isWaiting = false;
    this->initialPosition = pos;
    this->position = pos;
    this->points = GLOBAL_POINTS;
    this->speed = SPEED;
    this->stop = false;
    this->requests = new QVector<int>();
    this->awks = new QVector<int>();
}
//-------------------- SLOTS Start --------------------
void Person::ReceiveRequest(int reqId, QPoint reqMovement) {

    if(ALG_MODE == 2 && reqId != this->id){
        if(this->requests->isEmpty() && (this->getMovement() == reqMovement)) {
            emit this->SendAwk(this->id, reqId);
            return;
        }
    }

    if(!this->requests->contains(reqId)){
        this->requests->push_back(reqId);
    }

    //Respond to requests if not waiting or in CS. Additionally, if the request is from
    //this person instance and the person is waiting respond. (Respond when you ask yourself)
    if((!this->isInCS() && !this->isWaiting) || (this->id == reqId && this->isWaiting)){
        this->respondToReq();
    }
}

void Person::onReset() {
    QMutex mutex;
    mutex.lock();
    this->stop = true;
    mutex.unlock();

    this->inCS = false;
    this->isWaiting = false;
    this->requests = new QVector<int>();
    this->awks = new QVector<int>();

    QPoint moveBy;
    moveBy.setX(this->initialPosition.x() - this->position.x());
    moveBy.setY(this->initialPosition.y() - this->position.y());
    emit this->ChangePosition(this->id, moveBy);

    this->position += moveBy;
}

//-------------------- SLOTS End --------------------



//-------------------- FUNCTIONS Start --------------------
void Person::run() {
    this->stop = false;

    while(!this->stop)
    {
        if( (!this->isWaiting) || this->inCS ){
            setMovement();
            this->position += movement;
            emit this->ChangePosition(this->id, movement);

            QMutex mutex;
            mutex.lock();
            this->msleep(this->speed);
            mutex.unlock();
        }
    }
}

//This might not be needed at all. It is possible we could just use the evaluatePoint() method if we are smart about it.
//Oh well, better safe than sorrry!
void Person::setMovement() {
    foreach(QPoint a, points) {
        int nextIndex = 0;
        if( a != points.last() ) {
            nextIndex = points.indexOf(a) + 1;
        }
        QPoint b = points.at(nextIndex);

        if(a == position) {
            evaluatePoint(a);
        }
        else if(a.x() == b.x() && a.x() == position.x()) {
            if(position.y() > a.y() && position.y() < b.y()) {
                movement = QPoint(0, 1);
            }else if(position.y() < a.y() && position.y() > b.y()) {
                movement = QPoint(0, -1);
            }
        }else if(a.y() == b.y() && a.y() == position.y()) {
            if(position.x() > a.x() && position.x() < b.x()) {
                movement = QPoint(1, 0);
            }else if(position.x() < a.x() && position.x() > b.x()) {
                movement = QPoint(-1, 0);
            }
        }
    }
}

void Person::evaluatePoint(QPoint c) {
    int index = points.indexOf(c);

    switch(index) {
    //Moving Right
        case 2: //REQUEST CS
            movement = QPoint(1, 0);
            this->requestCS();
            break;
        case 0:
        case 4:
            movement = QPoint(1, 0);
            break;

    //Moving Left
        case 8: //REQUEST CS
            movement = QPoint(-1, 0);
            this->requestCS();
            break;
        case 6:
        case 10:
            movement = QPoint(-1, 0);
            break;

    // Moving Up
        case 3:  //LEAVE CS
            this->inCS = false;
            this->respondToReq();
            movement = QPoint(0, -1);
            break;
        case 7:
        case 11:
            movement = QPoint(0, -1);
            break;

    // Moving Down
        case 9: //LEAVE CS
            this->inCS = false;
            this->respondToReq();
            movement = QPoint(0, 1);
            break;
        case 1:
        case 5:
            movement = QPoint(0, 1);
            break;
    }
}

bool Person::isInCS() {
    QMutex m;
    m.lock();
    bool tB = this->inCS;
    m.unlock();

    return tB;
}

//Request the CS from all other people
void Person::requestCS() {
    if(!this->isInCS() && !this->isWaiting){
        this->isWaiting = true;

        //Populate awk vector with the id's of people present in the system.
        for(int i = 0; i<PEOPLE_TOTAL; i++){
            this->awks->push_back(i);
        }
        emit this->SendRequest(this->id, this->getMovement());
    }
}

//Accept awk from process
void Person::receiveAwk(int awkId) {
    //Remove the awk id from the awk vector if it is present.
    if(!this->awks->isEmpty()) {
        int temp = this->awks->indexOf(awkId);
        if(temp != -1){
            this->awks->remove(temp);
        }
    }
    if(this->awks->isEmpty()) {
        this->isWaiting = false;
        this->inCS = true;
    }
}

void Person::respondToReq() {
    for(int reqId : *(this->requests)){
        emit this->SendAwk(this->id, reqId);
    }
    this->requests->clear();
}
//-------------------- FUNCTIONS End --------------------
