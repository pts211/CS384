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
    int mId;
    QPoint mPosition;
    bool mInCS;
    bool mIsWaiting;
    int mDirection;
    bool mStop;

    QVector<int> *awks;
    QVector<int> *requests;

    explicit Person(int id, QPoint pos, QObject *parent = 0);
    void run();

    int getDir();
    void setDir();
    void setPos(int x, int y);

    bool isInCS();
    void requestCS();
    void receiveAwk(int id);
    void respondToReq();
signals:
    void ChangePosition(int, int);
    void SendRequest(int);
    void SendAwk(int, int);
    void EnterCS(int);

public slots:
    void ReceiveRequest(int);


};

#endif // PERSON_H
