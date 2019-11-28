#include "plane.h"
#include "arc.h"

#include <QPainter>
#include <QPen>
#include <QDebug>
#include <qgraphicssceneevent.h>

void Plane::redraw() {
    GraphicsItemBase::redraw();
    update();
}


Plane::Plane(QChart *chart, Transformation *transformation)
    : GraphicsItemBase (chart, transformation)
{}

Plane::~Plane(){}

QRectF Plane::boundingRect() const
{
    // outer most edges
    double xDelta = transformation_->getDeltaWidth()*k
            + (transformation_->isProectiveEnabled() || transformation_->isAffineEnabled()
               ? affineXYDelta.x()*k
               : 0);

    double yDelta = transformation_->getDeltaHeight()*k
            - (transformation_->isProectiveEnabled() || transformation_->isAffineEnabled()
               ? affineXYDelta.y()*k
               : 0);


    return QRectF(160 + xDelta
                  , 0 - 150 - yDelta//50 - detail width
                  , 430 // if PB is longer then AB -> boundingRect should be extended till PB ends
                  , 430);
}

void Plane::setTrianglesVisible(bool isTrianglesVisible)
{
    isTrianglesVisible_ = isTrianglesVisible;
    redraw();
}

void Plane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);
    drawPlane(painter);
    transformateDatail();
}

void Plane::mousePressEvent (QGraphicsSceneMouseEvent * event)
{
    mauseP = event->pos();

    return GraphicsItemBase::mousePressEvent(event);
}

void Plane::drawPlane(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 3, Qt::PenStyle::SolidLine));

    QList<QVector<QPointF>> triangles;
    QPointF stP(30,250), tmP(stP), delta(boundingRect().topLeft());
    QPainterPath plaine(stP);

    stP.rx() += 10;     stP.ry() -= 22;
    tmP.rx() -= 5;      tmP.ry() -= 6;
        triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() += 133;    stP.ry() -= 11;
    tmP.rx() += 101;    tmP.ry() -= 33;
        triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() += 33;     stP.ry() -= 0;
    tmP.rx() += 69;     tmP.ry() -= 23;
        triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() += 16;     stP.ry() -= 1;
    tmP.rx() += 18; tmP.ry() += 30;
        triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() += 83;     stP.ry() -=  85;
    tmP.rx() += 53;     tmP.ry() -= 63;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() += 47;     stP.ry() -= 11;
    tmP.rx() += 57;     tmP.ry() -= 44;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() += 34;     stP.ry() += 21;
    tmP.rx() += 67;     tmP.ry() += 20;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() -= 62;     stP.ry() += 95;
    tmP.rx() += 0;      tmP.ry() += 33;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() += 28;     stP.ry() += 18;
    tmP.rx() -= 52;      tmP.ry() += 84;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() += 28;     stP.ry() += 20;
    tmP.rx() += 50;      tmP.ry() -= 7;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() += 28;     stP.ry() += 26;
    tmP.rx() += 26;      tmP.ry() += 56;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() -= 18;     stP.ry() += 14;
    tmP.rx() -= 17;      tmP.ry() += 20;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() -= 104;     stP.ry() -= 27;
    tmP.rx() -= 65;      tmP.ry() -= 21;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() -= 47;     stP.ry() += 18;
    tmP.rx() -= 72;      tmP.ry() += 20;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() -= 82;     stP.ry() += 21;
    tmP.rx() -= 58;      tmP.ry() += 18;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() -= 62;     stP.ry() -= 26;
    tmP.rx() -= 62;      tmP.ry() -= 20;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() += 44;     stP.ry() -= 15;
    tmP.rx() -= 41;      tmP.ry() -= 30;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    stP.rx() -= 19;     stP.ry() -= 34;
    tmP.rx() += 40;      tmP.ry() -= 4;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<stP);
    plaine.quadTo(tmP, stP);

    tmP.rx() -= 68;      tmP.ry() -= 32;
    triangles << (QVector<QPointF>() <<plaine.currentPosition() << tmP <<plaine.elementAt(0));
    plaine.quadTo(tmP, plaine.elementAt(0));




//    qDebug() <<plaine.currentPosition() <<mauseP
//            <<"tmP-mP" <<tmP-mauseP
//           <<" pathPos-mP" <<stP -mauseP;

    painter->drawPath(plaine.translated(delta));

    //painter->drawRect(boundingRect()); //draw rectangle

    if(! isTrianglesVisible_)
        return;

    for (const auto &triangle : triangles) {
        painter->setPen(QPen(Qt::magenta, 1, Qt::PenStyle::SolidLine));
        painter->drawEllipse(triangle[1]+delta, 5, 5);

        painter->setPen(QPen(Qt::black, 1, Qt::PenStyle::DashLine));
        painter->drawLine({triangle[0]+delta, triangle[1]+delta});
        painter->drawLine({triangle[1]+delta, triangle[2]+delta});
        painter->drawEllipse(triangle[0]+delta, 2, 2);
        painter->drawEllipse(triangle[2]+delta, 2, 2);
    }
}

void Plane::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation_->getTransformation().first);
}