//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Person.h
//This class represents a process, a process will want to get into the CS.

#ifndef PERSON_H
#define PERSON_H

#include <QThread>
#include <QVector>
#include <QPoint>

class Person : public QThread
{
    Q_OBJECT
public:
    static int PEOPLE_TOTAL;
    static int ALG_MODE;
    static int SPEED;
    int id;
    int speed;
    QPoint position;
    QPoint movement;
    bool inCS;
    bool isWaiting;
    bool stop;

    QVector<QPoint> points;

    //Vector for acknowledgements. This vector is populated when the person requests the CS.
    //As awks are received the vector items are removed. When it is empty all awks have been recieved.
    QVector<int> *awks;

    //Vector for requests. This vector acts as a stack for receieved requests while in the CS to
    //handled when the person leaves the CS.
    QVector<int> *requests;

    explicit Person(int id, QPoint pos, QObject *parent = 0);

    void run();

    //getters and setters 
    int getSpeed() const;
    void setSpeed(int value);

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

    QPoint getMovement();

    //POST: Sets the movement variable to state which direction (up, down, left, right) the
    //person needs to be moving to get to the next point of teh track.
    void setMovement();

    //PRE: The point of the track that the person is currently.
    //POST: If the point is the entry to the bridge (or exit) take special
    //actions, otherwise, set the movement direction and cross like normal.
    void evaluatePoint(QPoint c);


signals:

    //PRE: The person is in the CS and moving.
    //POST: The persons position is changed in the UI.
    void ChangePosition(int, QPoint);

    //PRE: The person wants to enter the CS.
    //post: Requests are sent to all other people. Requests contain the requestor's ID and desired direction.
    void SendRequest(int, QPoint);

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
    void ReceiveRequest(int, QPoint);
};

#endif // PERSON_H
