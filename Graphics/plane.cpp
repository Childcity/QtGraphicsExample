#include "plane.h"
#include "arc.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

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


    return QRectF(150 + xDelta
                  , 0 - 100 - yDelta//50 - detail width
                  , 400 // if PB is longer then AB -> boundingRect should be extended till PB ends
                  , 400);
}

void Plane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);
    drawPlane(painter);
    transformateDatail();
}

void Plane::drawPlane(QPainter *painter)
{
    painter->drawRect(boundingRect()); //draw rectangle

    QPointF stP(20,250), t(stP);

    QPainterPath plaine(stP);

    stP.rx()+=5; stP.ry()-=50;
    t.rx() -= 4; t.ry() -= 20;
    plaine.quadTo(t, stP);

    qDebug() <<plaine.currentPosition() <<mauseP;

    painter->drawPath(plaine.translated(boundingRect().topLeft()));
}

void Plane::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation_->getTransformation().first);
}
