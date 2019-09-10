#ifndef GASKET_H
#define GASKET_H

#include <QChart>
#include <QGraphicsItem>

using namespace QtCharts;

class Gasket : public QGraphicsItem {
private:
    const double k = 4.65;
    QChart *chart_;

    double width_ = 55;
    double height_ = 50;
    double arc8R_ = 10;
    double arc13R_ = 10;
    double arc11R_ = 13;

public:
    Gasket(QChart *chart);

public:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setWidth(double value);

    void setHeight(double value);

    void redraw();

    void setArc8R(double value);

    void setArc13R(double value);

    void setArc11R(double arc11R);
};

#endif // GASKET_H
