//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Algorithm Runner.cpp
//The purpose of this program is to be the runner for the Project.

#include "widget.h"
#include <QApplication>

#include "algorithmrunner.h"
#include "person.h"
#include <QtConcurrent>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    AlgorithmRunner *ar = new AlgorithmRunner(w.getCircleList(), &w);

    w.setRunner(ar);
    w.show();

    return a.exec();
}
