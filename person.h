//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Person.h
//This class represents a process, a process will want to get into the CS.

#ifndef PERSON_H
#define PERSON_H

//#include <QRunnable>
#include <QThread>
#include <QVector>
#include <QPoint>

//global variables.
//The minimum and maxium x coordinates for the person to be displayed in the UI.
const int MIN_X = 0;
const int MAX_X = 400;

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

    //Vector for acknowledgements. This vector is populated when the person requests the CS.
    //As awks are received the vector items are removed. When it is empty all awks have been recieved.
    QVector<int> *awks;

    //Vector for requests. This vector acts as a stack for receieved requests while in the CS to
    //handled when the person leaves the CS.
    QVector<int> *requests;

    explicit Person(int id, QPoint pos, QObject *parent = 0);

    void run();

    //getters and setters 
    int getDir();
    void setDir();

    //PRE: none
    //POST: tells if person is in the CS
    bool isInCS();

    //PRE: None
    //POST a person requests to go to the CS
    void requestCS();

    //PRE: there exists an id of a person.
    //POST: recieves an ACK from person with id.
    void receiveAwk(int id);

    //PRE:None
    //POST: Request the CS from all other people
    void respondToReq();
signals:

    //PRE: The person is in the CS and moving.
    //POST: The persons position is changed in the UI.
    void ChangePosition(int, int);

    //PRE: The person wants to enter the CS.
    //post: Requests are sent to all other people. Requests contain the requestor's ID and desired direction.
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
