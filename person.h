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
    //Algorithm Mode: 1 for Ricart and Agrawalas; 2 for "Two-by-Two"
    static int ALG_MODE;
    static int SPEED;

    int id;
    int speed;
    QPoint initialPosition;
    QPoint position;

    //A point with x,y each equal to +/- 1 or 0 to specify which
    //direction the person is moving.
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

    //The thread that is executed when the algorithm is running. Moves the person.
    void run();

    //Resets the person back to his original starting position and stops the thread.
    void reset();

    //getters and setters 
    int getSpeed() const { return this->speed; }
    void setSpeed(int value) { this->speed = value; }
    QPoint getMovement(){ return this->movement; }

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

    //POST: Sets the movement variable to state which direction (up, down, left, right) the
    //      person needs to be moving to get to the next point of the track.
    void setMovement();

    //PRE: The point of the track that the person is currently.
    //POST: If the point is the entry to the bridge (or exit) take special
    //      actions, otherwise, set the movement direction and cross like normal.
    void evaluatePoint(QPoint c);

signals:
    //The following are signal prototypes. Signals are emitted and received by
    //connected slots.

    //PRE: The person has moved update the UI.
    //POST: The persons position is changed in the UI.
    void ChangePosition(int, QPoint);

    //PRE: The person wants to enter the CS (cross the bridge).
    //post: Requests are sent to all other people. Requests contain the requestor's ID and desired movement.
    void SendRequest(int, QPoint);

    //PRE: Two integers exist that represent the function being awknowledged and the function
    //      who needs to receive the awk.
    //POST: acknowledgements are sent. 
    void SendAwk(int, int);

public slots:
    //PRE: there exists a requiredID and a required Direction
    //POST: pushes items on the stack that recive the request if something
    //is already in the CS 
    void ReceiveRequest(int, QPoint);

    //POST: The person is reset back to the initial position and the thread is stopped.
    //      The user can then start the simulation again.
    void onReset();
};

#endif // PERSON_H
