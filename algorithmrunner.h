//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Algorithm Runner.cpp
//The purpose of this program is to be the header for the Algorithms.


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
    //POST: runs the algorithm
    void run();

    //PRE: there exists a bool.
    //POST, the random numbers are set. 
    void setRandom(bool isRandom);

private:
    bool mIsRandom;
    QVector<Person*> people; //pointer to the people vector. 

    //PRE: there exists a vector of random numbers
    //POST the vector is randomized with the processes needed. 
    QVector<int> randomize(QVector<int> ind);

    //pre, there exists a variable max,
    //post: random spot in vector is returned. 
    int rangedRand(unsigned int max);

public slots:

    //The following two functions are signal functions: 

    //PRE: there exists an int as well as a signal.
    //POST: saends the signal to the gui. 
    void onEnterCS(int);

    //PRE: there exists two ints
    //POST: sends the signal to the gui. 
    void onSendAwk(int, int);

private slots:

    //NONE
};

#endif // ALGORITHMRUNNER_H
