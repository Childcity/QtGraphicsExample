#include "elliptichyperboloid.h"
#include "plane.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

#include <cmath>
#include <algorithm>

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

    Plane plane(chart, transformation2d);
    for (const auto &point : plane.getTriangles()) {
        texture_.emplace_back(point->pos());
    }
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
    QPainterPath meshPath;
    QPainterPath texturePath;


    // construct elipses
    for (const auto &elips : elipses_) {
        vector<QPointF> elips2d =
                transformation3d_
                ->setToIdentity()
                .translate(QVector3D(pinnedPoint.x(), pinnedPoint.y(), 0))
                .rotate()
                .mapTo2d(elips);
        elipses2d.emplace_back(elips2d);

        meshPath.moveTo(elips2d.front());
        for (const auto &p : elips2d) {
            meshPath.lineTo(p);
        }
        meshPath.closeSubpath();
    }

    const size_t pointsCount = elipses2d.front().size();
    const size_t elipsesCount = elipses2d.size();

    // construct parabolas
    for (size_t elipsPointId = 0; elipsPointId < pointsCount; ++elipsPointId) {
        meshPath.moveTo(elipses2d[0][elipsPointId]);
        for (size_t elipsId = 0; elipsId < elipsesCount; ++elipsId) {
            meshPath.lineTo(elipses2d[elipsId][elipsPointId]);
        }
    }


    // construct Plane points on elliptic hyperboloid

    const float textureBorderX = std::max_element(texture_.cbegin(), texture_.cend(), [&](const QVector2D l, const QVector2D r){
        return l.x() < r.x();
    })->x();
    const float textureBorderY = std::max_element(texture_.cbegin(), texture_.cend(), [&](const QVector2D l, const QVector2D r){
        return l.y() < r.y();
    })->y();

    const float xCoefficient = pointsCount / textureBorderX;
    const float yCoefficient = elipsesCount / textureBorderY;


    for (const auto &p : texture_) {
        auto pp = QPointF{p.x(), p.y()};
        for (size_t elipsPointId = 0; elipsPointId < pointsCount; ++elipsPointId) {
            for (size_t elipsId = 0; elipsId < elipsesCount; ++elipsId) {
                auto eh = elipses2d[elipsId][elipsPointId];
                if(std::abs((pp - eh).x()) < 1 && std::abs((pp - eh).y()) < 1)
                {
                    if(texturePath.elementCount()==0)
                        texturePath.moveTo(elipses2d[elipsId][elipsPointId]);
                    else
                        texturePath.lineTo(elipses2d[elipsId][elipsPointId]);
                }
            }
        }
    }

    texturePath.closeSubpath();

    painter->setPen(QPen(Qt::black, 2));
    painter->drawPath(meshPath);
    painter->setPen(QPen(Qt::red, 1));
    painter->drawPath(texturePath);

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

    for (float V = -6.; V <= 6.f; V+=meshStep_) {
        vector<QVector3D> elips;
        for (float U = 0.; U <= PI2; U+=meshStep_) {
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

