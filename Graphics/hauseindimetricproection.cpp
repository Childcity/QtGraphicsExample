#include "hauseindimetricproection.h"

#include <QPainter>
#include <QPen>
#include <QDebug>


void HauseInDimetricProection::redraw()
{
    GraphicsItemBase::redraw();
    update();
}

HauseInDimetricProection::HauseInDimetricProection(QChart *chart, Transformation2D *transformation2d, Transformation3D *transformation3d)
    : GraphicsItemBase (chart, transformation2d)
    , transformation3d_(transformation3d)
{}

QRectF HauseInDimetricProection::boundingRect() const
{
    // outer most edges
    double xDelta = transformation2d_->getDeltaWidth()*k
            + (transformation2d_->isProectiveEnabled() || transformation2d_->isAffineEnabled()
               ? affineXYDelta.x()*k
               : 0);

    double yDelta = transformation2d_->getDeltaHeight()*k
            - (transformation2d_->isProectiveEnabled() || transformation2d_->isAffineEnabled()
               ? affineXYDelta.y()*k
               : 0);

    return QRectF(160 + xDelta
                  , 0 - 150 - yDelta
                  , 500
                  , 500);
}

void HauseInDimetricProection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);

    QPoint pinnedPoint = boundingRect().topLeft().toPoint() - QPoint(100, 0);

    vector<QPointF> points2d =
            transformation3d_
            ->setToIdentity()
            .translate(QVector3D(pinnedPoint.x(), pinnedPoint.y(), 0))
            .rotate()
            .mapTo2d(points_);

    painter->setPen(QPen(Qt::red, 2));
    for (const auto &p : points2d) {
        painter->drawEllipse(p, 5, 5);
    }

    painter->setPen(QPen(Qt::black, 2));
    for (const auto &l : lines_) {
        painter->drawLine(points2d[l.first], points2d[l.second]);
    }

    //painter->drawRect(boundingRect());
    transformateDatail();
}

void HauseInDimetricProection::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation2d_->getTransformation().first);
}

void HauseInDimetricProection::genHouse()
{

}

