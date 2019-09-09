#include "gasket.h"

#include <QPainter>
#include <QPen>
#include <QWidget>
#include <cmath>
#include <QDebug>

Gasket::Gasket()
{

}


QRectF Gasket::boundingRect() const
{
    // outer most edges
    return QRectF(100, 100, k * 60, k * 60);
}

void Gasket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);

    QRectF rect = boundingRect();

    // draw rectangle
    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    painter->drawRect(rect);

    //############### creating detail lines #################

    QPointF stP = rect.topLeft();
    QPointF t; //tmp point

    QLineF l1(10*k, 0, 45*k, 0);
    QLineF l2(l1.p2(), QPointF(l1.p2().x(), l1.p2().y() + 15*k));

    t.rx() = l1.p2().x() - 14*k;
    t.ry() = l1.p2().y() + 10*k;
    QLineF l3(l2.p2(), t);
    QLineF l4(t, QPointF(t.x(), t.y() + 30*k));

    QLineF l5(l4.p2(), QPointF(l2.p2().x(), l2.p2().y() + 20*k));
    QLineF l6(l5.p2(), QPointF(l5.p2().x(), l5.p2().y() + 15*k));
    QLineF l7(l6.p2(), QPointF(l6.p2().x() - 35*k, l6.p2().y()));

    t.rx() = l7.p2().x() - 10*k;
    t.ry() = l7.p2().y() - 10*k;
    QVector<QPointF> l8 = drawArc(l7.p2(), t, 10*k, QPointF(t.x() + 10*k, t.y()));


    QVector<QLineF> lines({
                            l1, l2, l3, l4, l5, l6, l7
                         });
    //lines += l8;

    for(auto &line : lines){
        line.translate(stP);
        qDebug() <<line;
    }


    // painting
    pen.setColor(Qt::red);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawLines(lines);
    painter->drawLines(l8.data(), l8.size()/2);
}

QVector<QPointF> Gasket::drawArc(QPointF p1, QPointF p2, double r, QPointF center)
{
    QVector<QPointF> lines;

    auto circle = getPointForCircle(r, center);

    return circle;
}

QVector<QPointF> Gasket::getPointForCircle(double r, QPointF center)
{
    QVector<QPointF> lines;

    int n = 0;
    for (double phi = 0.; phi <= 2. * M_PI; phi += PHI_STEP, n++) {
        double x = cos (phi) * r + center.x();
        double y = sin (phi) * r + center.y();
        lines += QPointF(x, y);

        if(n % 2 == 0){ // for filling spaces between dashed lines
            lines += QPointF(x, y);
            x = cos (phi - PHI_STEP) * r + center.x();
            y = sin (phi - PHI_STEP) * r + center.y();
            lines += QPointF(x, y);
        }
    }

    return lines;
}
