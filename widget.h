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

    //Retrieve a list of the circles that represent people.
    QVector<QGraphicsEllipseItem*> getCircleList();

    //Associate an instance of the Algorithm Runner object.
    void setRunner(AlgorithmRunner *tAR);

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QVector<QGraphicsEllipseItem*> circles;
    QVector<QPoint> points;

    AlgorithmRunner *mAR;

    //Create all of the lines in the scene. (Draws the track).
    void drawLines();

signals:

    //POST: The persons speed is changed.
    void ChangeSpeed(int, int);

    //POST:
    void Reset();

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
    void on_btn_reset_clicked();
};

#endif // WIDGET_H
