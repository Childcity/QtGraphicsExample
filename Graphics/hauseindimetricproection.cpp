#include "hauseindimetricproection.h"

#include <QPainter>
#include <QPen>
#include <QDebug>


void HauseInDimetricProection::redraw() {
    GraphicsItemBase::redraw();
    update();
}

HauseInDimetricProection::HauseInDimetricProection(QChart *chart, Transformation2D *transformation2d)
    : GraphicsItemBase (chart, transformation2d)
{
    float alpha_ = 60;
    float alpha_sq = sinf(alpha_) * sinf(alpha_);
    float betta = sqrtf(alpha_sq / (1 - alpha_sq));
    transformation3d_.setRotationAngles({alpha_, betta, 0})->rotate();
}

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
                  , 430
                  , 430);
}

void HauseInDimetricProection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);

    vector<QPointF> mappedTo2dProection = transformation3d_.mapTo2d(points_);

    painter->setPen(QPen(Qt::red, 2));
    for (const auto &p : mappedTo2dProection) {
        painter->drawEllipse(p, 5, 5);
    }

    painter->setPen(QPen(Qt::black, 2));
    for (const auto &l : lines_) {
        painter->drawLine(mappedTo2dProection[l.first], mappedTo2dProection[l.second]);
    }

    painter->drawRect(boundingRect());
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

