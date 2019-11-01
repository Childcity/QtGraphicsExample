#include "graphicsitembase.h"

#include <QPainter>
#include <QValueAxis>
#include <QGraphicsScene>

GraphicsItemBase::GraphicsItemBase(QChart *chart, Transformation *transformation)
    : chart_(chart)
    , transformation_(transformation)
{
    // save default chart pos
    chartPos_ = chart_->pos();

    // move to Start of XY coordinate system
    setPos({chartPos_.x() + 48, chartPos_.y() + 170 + 142});
}

GraphicsItemBase::~GraphicsItemBase(){}

QPointF GraphicsItemBase::getCoordXEnd()
{
    auto xAxis = reinterpret_cast<QValueAxis *>(chart_->axisX());
    return {x() +  xAxis->max()*k, y()};
}

QPointF GraphicsItemBase::getCoordYEnd()
{
    auto yAxis = reinterpret_cast<QValueAxis *>(chart_->axisY());
    return {x(), y() - yAxis->max()*k};
}

void GraphicsItemBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // draw border around chart/points etc...
    painter->save();
    {
        painter->setPen(QPen(Qt::black, 1, Qt::PenStyle::SolidLine));
        //painter->drawRect(boundingRect()); //draw rectangle
        //painter->drawEllipse(QRectF(pos().x()-5, pos().y()-5, 10, 10));
        //painter->drawEllipse(QRectF(rotatePoint_.x()-5, rotatePoint_.y()-5, 10, 10));
        //painter->drawEllipse(QRectF(-5, -5, 10, 10));

        //auto chartRect = mapRectFromItem(chart_, chart_->scene()->sceneRect());
        //painter->drawEllipse(QRectF(chartRect.topRight().x()-10, chartRect.topRight().y(), 10, 10));
        //painter->drawEllipse(QRectF(chartRect.bottomLeft().x(), chartRect.bottomLeft().y()-10, 10, 10));
        painter->drawRect(mapRectFromItem(chart_, chart_->boundingRect()));
    }
    painter->restore();


    painter->setRenderHint(QPainter::Antialiasing);
}

void GraphicsItemBase::transformateDatail() {
    // set default chart pos
    chart_->setPos(chartPos_);

    if(transformation_->isAffineEnabled() || transformation_->isProectiveEnabled())
        chart_->setPos(pos());

    chart_->setTransform(transformation_->getTransformation().second);
}

void GraphicsItemBase::redraw(){
    chart_->update();
    scene()->invalidate();
}
