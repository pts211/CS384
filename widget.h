//Names: Paul Sites, Tim Kinely, Tiffani Dutton
//CS 384 Project
//Algorithm Runner.cpp
//The purpose of this program is to be the header for the widget.

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "person.h"
#include "algorithmrunner.h"

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

    void setRunner(AlgorithmRunner *tAR){ mAR = tAR; }

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QVector<QGraphicsEllipseItem*> circles;

    AlgorithmRunner *mAR;

public slots:
    void onChangePosition(int, int);

private slots:
    void on_btn_start_clicked();
    void on_rd_Ricart_toggled(bool checked);
    void on_rd_Two_toggled(bool checked);
    void on_slider_speed_sliderMoved(int position);
    void on_chk_random_toggled(bool checked);
};

#endif // WIDGET_H
