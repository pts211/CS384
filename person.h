//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Algorithm Runner.cpp
//The purpose of this program is to be the header  for the Algorithms.

#ifndef PERSON_H
#define PERSON_H

//#include <QRunnable>
#include <QThread>
#include <QVector>
#include <QPoint>

//global variables. 

const int MIN_X = 0;
const int MAX_X = 400;

//QVector<int> tRequests;
//QVector<int> tAwks;

class Person : public QThread
{
    Q_OBJECT
public:
    static int PEOPLE_TOTAL;
    static int ALG_MODE;
    static int SPEED;
    int mId;
    int mDirection;
    int mSpeed;
    QPoint mPosition;
    bool mInCS;
    bool mIsWaiting;
    bool mStop;

    QVector<int> *awks; //vector for the acknowledgements 
    QVector<int> *requests; //vector for the requests 

    explicit Person(int id, QPoint pos, QObject *parent = 0);
    void run();

    //getters and setters 
    int getDir();
    void setDir();

    //PRE: none
    //POST: tells if a person is in the Critical Section
    bool isInCS();

    //PRE: None
    //POST a person requests to go to the CS
    void requestCS();

    //PRE: there exists an id of a person
    //POST: recieves an ACK from all people
    void receiveAwk(int id);

    //PRE:None
    //POST: sends a request to every person. 
    void respondToReq();
signals:

    //PRE: there exists a person that is moving in the critical section
    //POST: the position of the persons are changed. 
    void ChangePosition(int, int);

    //PRE: there exists a process that is being requqested  
    //post: the requests is sent. 
    void SendRequest(int,int);

    //PRE: two integers exists
    //POST: acknowledgements are sent. 
    void SendAwk(int, int);


    //PRE: there exists the id of a person that wants to enter ths cs
    //POST: THe person enters the cs
    void EnterCS(int);

public slots:
    //PRE: there exists a requiredID and a required Direction
    //POST: pushes items on the stack that recive the request if something
    //is already in the CS 
    void ReceiveRequest(int,int);


};

#endif // PERSON_H
