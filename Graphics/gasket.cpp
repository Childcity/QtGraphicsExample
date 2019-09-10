#include "gasket.h"
#include "arc.h"

#include <QPainter>
#include <QPen>
#include <QWidget>
#include <QDebug>

void Gasket::setWidth(double value)
{
    width_ = value;
    redraw();
}

void Gasket::setHeight(double value)
{
    height_ = value;
    redraw();
}

void Gasket::redraw() {
    update();
    chart_->update();
}

void Gasket::setArc8R(double value)
{
    arc8R_ = value;
    redraw();
}

void Gasket::setArc13R(double value)
{
    arc13R_ = value;
    redraw();
}

void Gasket::setArc11R(double arc11R)
{
    arc11R_ = arc11R;
    redraw();
}

Gasket::Gasket(QChart *chart)
    : chart_(chart)
{}

QRectF Gasket::boundingRect() const
{
    // outer most edges
    QPointF bootomLeft = chart_->plotArea().bottomLeft();
    return QRectF(bootomLeft.x(), bootomLeft.y() - height_*k, width_*k, height_*k);
}

void Gasket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    using namespace Graphics;

    QRectF rect = boundingRect();

    // draw rectangle
    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    painter->drawRect(rect);

    //############### creating detail lines #################

    QPointF stP = rect.topLeft();
    QPointF t; //tmp point


    QLineF l1(10*k, 0, width_*k, 0);
    QLineF l2(l1.p2(), QPointF(l1.p2().x(), l1.p2().y() + 15*k));


    t.rx() = l1.p2().x() - 14*k;
    t.ry() = l1.p2().y() + 10.4*k;
    QLineF l3(l2.p2(), t);
    QLineF l4(t, QPointF(t.x(), t.y() + 30*k));


    QLineF l5(l4.p2(), QPointF(l2.p2().x(), l2.p2().y() + 20*k));
    QLineF l6(l5.p2(), QPointF(l5.p2().x(), l5.p2().y() + 15*k));
    QLineF l7(l6.p2(), QPointF(l6.p2().x() - (width_-10)*k, l6.p2().y()));


    t.rx() = l7.translated(stP).p2().x() - 10*k;
    t.ry() = l7.translated(stP).p2().y() - 10*k;
    Arc arc(M_PI/2., M_PI, arc8R_*k, QPointF(t.x() + 10*k, t.y()));
    QVector<QPointF> arc8 = arc.getPoints();


    t.rx() = l7.p2().x() - 10*k;
    t.ry() = l7.p2().y() - 10*k;
    QLineF l9(t, QPointF(t.x(), t.y() - 7.5*k));
    QLineF l10(l9.p2(), QPointF(l9.p2().x() + ((((6*k)))), l9.p2().y()));


    t.rx() = l9.translated(stP).p2().x() + 17*k;
    t.ry() = l9.translated(stP).p2().y() - 7.5*k;
    arc = Arc (-M_PI/1.26, M_PI/1.23, arc11R_*k, t);
    QVector<QPointF> arc11 = arc.getPoints();


    t.rx() = l9.p2().x();
    t.ry() = l9.p2().y() - 15*k;
    QLineF l12(t, QPointF(t.x(), t.y() - 7.5*k));
    QLineF l11(l12.p1(), QPointF(l12.p1().x() + ((((6*k)))), l12.p1().y()));


    t.rx() = l12.translated(stP).p2().x() + 10*k;
    t.ry() = l12.translated(stP).p2().y();
    arc = Arc (-M_PI, -M_PI/2., arc13R_*k, t);
    QVector<QPointF> arc13 = arc.getPoints();


    QVector<QLineF> lines({
                            l1, l2, l3, l4, l5, l6, l7, l9, l10, l11, l12
                         });

    for(auto &line : lines){
        line.translate(stP);
        //qDebug() <<line;
    }


    // painting
    pen.setColor(Qt::red);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawLines(lines);
    painter->drawLines(arc8.data(), arc8.size()/2);
    painter->drawLines(arc11.data(), arc11.size()/2);
    painter->drawLines(arc13.data(), arc13.size()/2);
}
