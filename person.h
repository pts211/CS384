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

    QVector<int> *awks;
    QVector<int> *requests;

    explicit Person(int id, QPoint pos, QObject *parent = 0);
    void run();

    int getDir();
    void setDir();

    bool isInCS();
    void requestCS();
    void receiveAwk(int id);
    void respondToReq();
signals:
    void ChangePosition(int, int);
    void SendRequest(int,int);
    void SendAwk(int, int);
    void EnterCS(int);

public slots:
    void ReceiveRequest(int,int);


};

#endif // PERSON_H
