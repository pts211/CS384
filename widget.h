#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *c1;
    QGraphicsEllipseItem *c2;
    QGraphicsEllipseItem *c3;
    QGraphicsEllipseItem *c4;
};

#endif // WIDGET_H
