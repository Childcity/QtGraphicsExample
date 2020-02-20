#include "elliptichyperboloid.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

#include <cmath>

void EllipticHyperboloid::redraw()
{
    GraphicsItemBase::redraw();
    update();
}

EllipticHyperboloid::EllipticHyperboloid(QChart *chart, Transformation2D *transformation2d, Transformation3D *transformation3d)
    : GraphicsItemBase (chart, transformation2d)
    , transformation3d_(transformation3d)
{
    genHyperboloid();
}

QRectF EllipticHyperboloid::boundingRect() const
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

void EllipticHyperboloid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);

    QPoint pinnedPoint = boundingRect().center().toPoint();

    vector<QPointF> points2d =
            transformation3d_
            ->setToIdentity()
            .translate(QVector3D(pinnedPoint.x(), pinnedPoint.y(), 0))
            .rotate()
            .mapTo2d(points_);

    painter->setPen(QPen(Qt::red, 1));
    for (const auto &p : points2d) {
        painter->drawEllipse(p,5,5);
    }

    //painter->drawRect(boundingRect());
    transformateDatail();
}

void EllipticHyperboloid::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation2d_->getTransformation().first);
}

void EllipticHyperboloid::genHyperboloid()
{
    float a = 1, b = 2, c = 3;

    for (double V = -6.; V <= 6.; V+=0.5) {
        for (double U = 0.; U <= 2.*M_PI; U+=0.5) {
            points_.emplace_back(QVector3D{
                                     a * coshf(V) * cosf(U),
                                     b * coshf(V) * sinf(U),
                                     c * sinhf(V)
                                 });
        }
    }
}

