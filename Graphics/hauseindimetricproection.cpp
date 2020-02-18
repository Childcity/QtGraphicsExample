#include "hauseindimetricproection.h"

#include <QPainter>
#include <QPen>
#include <QDebug>
#include <qgraphicssceneevent.h>
#include <QGraphicsScene>
#include <QThread>

#include <Graphics/Basic/transformation3d.cpp>

void HauseInDimetricProection::redraw() {
    GraphicsItemBase::redraw();
    update();
}

HauseInDimetricProection::HauseInDimetricProection(QChart *chart, Transformation2D *transformation)
    : GraphicsItemBase (chart, transformation)
{

}

QRectF HauseInDimetricProection::boundingRect() const
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
                  , 0 - 150 - yDelta
                  , 430
                  , 430);
}

void HauseInDimetricProection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);
    //painter->setPen(QPen(p.second, 1));



    for (const auto &p : housePoints_) {
        painter->drawEllipse(p.toPointF(), 5, 5);
    }

    transformateDatail();
}

void HauseInDimetricProection::transformateDatail()
{
    Transformation3D transformer(housePoints_);
    transformer.rotate(1,1,1).rotate(2,1,3);

    GraphicsItemBase::transformateDatail();
    setTransform(transformation_->getTransformation().first);
}

void HauseInDimetricProection::genHouse()
{

}

