//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Widget.h
//This class manages the UI of the program.

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "person.h"
#include "algorithmrunner.h"

//The size of the circles that represnt a person/process.
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

    QVector<QGraphicsEllipseItem*> getCircleList();

    void setRunner(AlgorithmRunner *tAR);

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QVector<QGraphicsEllipseItem*> circles;
    QVector<QPoint> points;

    AlgorithmRunner *mAR;

    void drawLines();

signals:

    //POST: The persons speed is changed.
    void ChangeSpeed(int, int);

    //PRE: The person wants to enter the CS.
    //post: Requests are sent to all other people. Requests contain the requestor's ID and desired direction.
    void SendRequest(int,int);

public slots:
    //PRE: A person id, the amount to shift the person.
    //POST: The circle is shifted.
    void onChangePosition(int, QPoint);

private slots:
    void on_btn_start_clicked();
    void on_rd_Ricart_toggled(bool checked);
    void on_rd_Two_toggled(bool checked);
    void on_slider_speed_1_valueChanged(int value);
    void on_slider_speed_2_valueChanged(int value);
    void on_slider_speed_3_valueChanged(int value);
    void on_slider_speed_4_valueChanged(int value);
};

#endif // WIDGET_H
