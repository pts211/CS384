#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "person.h"

const int CSIZE = 40;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    Person *mPerson;

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QVector<QGraphicsEllipseItem*> circles;
    QVector<Person*> people;

public slots:
    void onChangePosition(int, int);
    void onRun(int, int);
    void onEnterCS(int);
    void onSendAwk(int, int);

private slots:
    void on_btn_start_clicked();
    void on_btn_stop_clicked();
};

#endif // WIDGET_H
