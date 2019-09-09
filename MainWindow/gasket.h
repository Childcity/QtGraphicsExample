#ifndef GASKET_H
#define GASKET_H

#include <QGraphicsItem>


class Gasket : public QGraphicsItem {
private:
    const double PHI_STEP = 0.1;
    double k = 4.;

public:
    Gasket();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QVector<QPointF> drawArc(QPointF p1, QPointF p2, double r, QPointF center);
    QVector<QPointF> getPointForCircle(double r, QPointF center);
};

#endif // GASKET_H
