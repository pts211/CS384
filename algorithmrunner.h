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
    explicit AlgorithmRunner(QVector<QGraphicsEllipseItem*> tCircleList, QObject *uiParent);
    void run();

private:
    QVector<Person*> people;
    QVector<int> randomize(QVector<int> ind);
    int rangedRand(unsigned int max);

public slots:
    void onEnterCS(int);
    void onSendAwk(int, int);

private slots:

};

#endif // ALGORITHMRUNNER_H
