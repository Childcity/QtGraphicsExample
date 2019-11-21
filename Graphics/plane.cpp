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


    return QRectF(x() + xDelta
                  , y() - 300 - yDelta//50 - detail width
                  , 300 // if PB is longer then AB -> boundingRect should be extended till PB ends
                  , 300);
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


}

void Plane::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation_->getTransformation().first);
}
