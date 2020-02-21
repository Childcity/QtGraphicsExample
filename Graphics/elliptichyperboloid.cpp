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
    vector<vector<QPointF>> elipses2d;
    QPainterPath mesh;


    // construct elipses
    for(const auto &elips : elipses_){
        vector<QPointF> elips2d =
                transformation3d_
                ->setToIdentity()
                .translate(QVector3D(pinnedPoint.x(), pinnedPoint.y(), 0))
                .rotate()
                .mapTo2d(elips);
        elipses2d.emplace_back(elips2d);

        mesh.moveTo(elips2d.front());
        for(const auto &p : elips2d){
            mesh.lineTo(p);
        }
        mesh.closeSubpath();
    }

    // construct parabolas
    for (size_t elipsPointId = 0; elipsPointId < elipses2d.front().size(); ++elipsPointId) {
        mesh.moveTo(elipses2d[0][elipsPointId]);
        for (size_t elipsId = 0; elipsId < elipses2d.size(); ++elipsId) {
            mesh.quadTo(elipses2d[elipsId][elipsPointId]+QPointF(2,2), elipses2d[elipsId][elipsPointId]);
        }
    }

    painter->setPen(QPen(Qt::black, 2));
    painter->drawPath(mesh);

//    for (const auto &p : points2d) {
//        painter->drawEllipse(p,5,5);
//    }

    //painter->drawLines(points2d.data(), points2d.size()/2);

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
    float a = 1, b = 1, c = 1;

    for (float V = -6.; V <= 6.f; V+=0.5) {
        vector<QVector3D> elips;
        for (float U = 0.; U <= PI2; U+=0.5) {
            elips.emplace_back(QVector3D{
                                     a * coshf(V) * cosf(U),
                                     b * coshf(V) * sinf(U),
                                     c * sinhf(V)
                                 });
            elips.emplace_back(elips.back());
        }
        elipses_.emplace_back(elips);
    }
}

