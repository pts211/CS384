//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Algorithm Runner.h
//This class serves as a worker thread and manages execution of the algorithm.


#ifndef ALGORITHMRUNNER_H
#define ALGORITHMRUNNER_H

#include <QThread>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "person.h"

class AlgorithmRunner : public QThread
{
    Q_OBJECT
public:
    //PRE: there exists a circle List, as well as a ui object
    //POST: the process of the algorithm is completed. 
    explicit AlgorithmRunner(QVector<QGraphicsEllipseItem*> tCircleList, QObject *uiParent);
    

    //PRE: none
    //POST: Thread to manage running the algorithm.
    void run();

    //PRE: there exists a bool.
    //POST, Random process movement is enable dor disabled.
    void setRandom(bool isRandom) { this->mIsRandom = isRandom; }

private:
    bool mIsRandom;
    QVector<Person*> people; //pointer to the people vector. 

    //PRE: there exists a vector of numbers
    //POST the vector is randomized
    QVector<int> randomize(QVector<int> ind);

    //pre, there exists a variable max,
    //post: random number is generated between 0 and max.
    int rangedRand(unsigned int max) { return (qrand() % (max)); }

public slots:
    //The following two functions are slot functions, they are executed when a corresponding signal is received.

    //PRE: there exists an int, id.
    //POST: the person with supplied id enters the CS.
    void onEnterCS(int);

    //PRE: there exists two ints, and id and a request id.
    //POST: acknowledgement is sent to the person with reqId from id.
    void onSendAwk(int, int);

private slots:

    //NONE
};

#endif // ALGORITHMRUNNER_H
