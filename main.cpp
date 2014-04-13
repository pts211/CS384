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
