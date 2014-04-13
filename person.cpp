#include "person.h"
#include <QtCore>

int Person::PEOPLE_TOTAL(0);
int Person::ALG_MODE(1);
int Person::SPEED(5);
//ALG_MODE=1 : Ricart
//ALG_MODE=2 : Two-by-Two

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
    this->mSpeed = 5;   //TODO Default to slider position.
    this->mStop = false;
    this->requests = new QVector<int>();
    this->awks = new QVector<int>();
}
//-------------------- SLOTS Start --------------------
void Person::ReceiveRequest(int reqId, int reqDir) {

    if(ALG_MODE == 2 && reqId != this->mId){
        if(this->requests->isEmpty() && (this->getDir() == reqDir)) {
            emit this->SendAwk(this->mId, reqId);
            return;
        }
    }

    tRequests.push_back(reqId);
    if(!this->requests->contains(reqId)){
        this->requests->push_back(reqId);
    }

    if((!this->isInCS() && !this->mIsWaiting) || (this->mId == reqId && this->mIsWaiting)){
        this->respondToReq();
    }

}

//-------------------- SLOTS End --------------------



//-------------------- FUNCTIONS Start --------------------
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

        emit this->ChangePosition(this->mId, this->mDirection);
        mutex.lock();
        this->msleep(SPEED);
        mutex.unlock();
    }
    this->mInCS = false;
    this->setDir();
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

bool Person::isInCS() {
    QMutex m;
    m.lock();
    bool tB = this->mInCS;
    m.unlock();

    return tB;

}
//Request the CS from all other people
void Person::requestCS() {
    if(!this->isInCS() && !this->mIsWaiting){
        this->mIsWaiting = true;

        for(int i = 0; i<PEOPLE_TOTAL; i++){
            this->awks->push_back(i);
        }
        emit this->SendRequest(this->mId, this->getDir());
    }
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
        emit this->EnterCS(this->mId);
    }
}

void Person::respondToReq() {
    for(int reqId : *(this->requests)){
        emit this->SendAwk(this->mId, reqId);
    }
    this->requests->clear();
}
//-------------------- FUNCTIONS End --------------------
