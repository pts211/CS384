#include "widget.h"
#include <QApplication>

#include "person.h"
#include <QtConcurrent>

void myRunFunction(QString name);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

//    MyThread thread1("A"), thread2("B"), thread3("C");
//    QFuture<void> t1 = QtConcurrent::run(myRunFunction, QString("A"));
//    QFuture<void> t2 = QtConcurrent::run(myRunFunction, QString("B"));
//    QFuture<void> t3 = QtConcurrent::run(myRunFunction, QString("C"));


//    t1.waitForFinished();
//    t2.waitForFinished();
//    t3.waitForFinished();

    return a.exec();
}



void myRunFunction(QString name)
{
    for(int i = 0; i <= 5; i++)
    {
        qDebug() << name << " " << i <<
                    "from" << QThread::currentThread();
    }
}
