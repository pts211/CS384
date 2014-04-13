#include "person.h"
#include <QtCore>

int Person::PEOPLE_TOTAL(0);

extern QVector<int> tRequests;
extern QVector<int> tAwks;

Person::Person(int tId, QPoint pos, QObject *parent) :
    QThread(parent)
{
    this->mId = tId;
    this->mInCS = false;
    this->mIsWaiting = false;
    this->mPosition = pos;
    this->setDir();
    this->mStop = false;
    this->requests = new QVector<int>();
    this->awks = new QVector<int>();
}

void Person::run() {
    this->mStop = false;
    this->mInCS = true;

    this->setDir(); //Determine the direction of travel.

    //Using the direction run the correct for-loop to travel
    //the appropriate direction.
    for(int i=MIN_X; i<MAX_X; i++) {
        QMutex mutex;
        mutex.lock();
        if(this->mStop) break;
        mutex.unlock();

        this->mPosition += QPoint(this->mDirection, 0);
//        qDebug(qPrintable(QString::number(mPosition.x())));

        emit this->ChangePosition(this->mId, this->mDirection);
        this->msleep(5);
    }
    this->mInCS = false;

    //qDebug(this->mId + ": Leaving CS, sending AWKs.");
    this->respondToReq();
}

int Person::getDir() {
    QMutex m;
    m.lock();
    int tD = this->mDirection;
    m.unlock();

    return tD;
}

void Person::setDir() {
    if(this->mPosition.x() == MIN_X) {
        this->mDirection = 1;
    }else if(this->mPosition.x() == MAX_X) {
        this->mDirection = -1;
    }
}

void Person::setPos(int x, int y) {
    this->mPosition.setX(x);
    this->mPosition.setY(y);
}

bool Person::isInCS() {
    QMutex m;
    m.lock();
    bool tB = this->mInCS;
    m.unlock();

    return tB;

}
//Request the CS from all other people
void Person::requestCS() {
    //qDebug(this->mId + ": Sending requests to enter CS");
    this->mIsWaiting = true;

    for(int i = 0; i<PEOPLE_TOTAL; i++){
        this->awks->push_back(i);
    }
    emit this->SendRequest(this->mId);
}

//Accept awk from process
void Person::receiveAwk(int awkId) {
    tAwks.push_back(awkId);
    if(!this->awks->isEmpty()) {
        int temp = this->awks->indexOf(awkId);
        if(temp != -1){
            this->awks->remove(temp);
        }
    }
    if(this->awks->isEmpty()) {
        this->mIsWaiting = false;
      // qDebug(this->mId + ": Sending requests to enter CS");
        emit this->EnterCS(this->mId);
    }
}


void Person::ReceiveRequest(int reqId) {
    tRequests.push_back(reqId);
    //qDebug(this->mId + ": Request received from: " + id);
    if(!this->requests->contains(reqId)){
        this->requests->push_back(reqId);
    }

    if((!this->isInCS() && !this->mIsWaiting) || (this->mId == reqId && this->mIsWaiting)){
        //qDebug(this->mId + ": Wasn't in the CS, sending AWK to: " + id);
        this->respondToReq();
    }

}

void Person::respondToReq() {
    for(int reqId : *(this->requests)){
        emit this->SendAwk(mId, reqId);
    }
    this->requests->clear();
}
