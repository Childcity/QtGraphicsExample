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

    genHyperboloid();
    refrashPictureData();
}

EllipticHyperboloid::EllipticHyperboloid(QChart *chart, Transformation2D *transformation2d, Transformation3D *transformation3d)
    : GraphicsItemBase (chart, transformation2d)
    , transformation3d_(transformation3d)
{
    Plane plane(chart, transformation2d);

    for (const auto &point : plane.getTriangles()) {
        texture_.emplace_back(point->pos() + QPointF(0, 39));
    }

    textureMaxX_ = std::max_element(texture_.cbegin(), texture_.cend(), maxComparator)->x();
    textureMaxY_ = std::max_element(texture_.cbegin(), texture_.cend(), maxComparator)->y();
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

    return QRectF(0 + xDelta
                  , 0 - 300 - yDelta
                  , 700
                  , 700);
}

float EllipticHyperboloid::getMeshStep() const
{
    return meshStep_;
}

void EllipticHyperboloid::setMeshStep(float meshStep)
{
    meshStep_ = meshStep;
}

QVector3D EllipticHyperboloid::getAbc() const
{
    return abc_;
}

void EllipticHyperboloid::setAbc(const QVector3D &abc)
{
    abc_ = abc;
}

void EllipticHyperboloid::setA(float a)
{
    abc_.setX(a);
}

void EllipticHyperboloid::setB(float b)
{
    abc_.setY(b);
}

void EllipticHyperboloid::setC(float c)
{
    abc_.setZ(c);
}

QPointF EllipticHyperboloid::getTextureTranslatePoint() const
{
    return textureTranslatePoint_;
}

void EllipticHyperboloid::setTextureTranslatePoint(const QPointF &textureTranslatePoint)
{
    textureTranslatePoint_ = textureTranslatePoint;
}

void EllipticHyperboloid::setTextureTranslatePointX(double x)
{
    textureTranslatePoint_.rx() = x;
}

void EllipticHyperboloid::setTextureTranslatePointY(double y)
{
    textureTranslatePoint_.ry() = y;
}

void EllipticHyperboloid::setTextureRotateAncle(double textureRotateAncle)
{
    textureRotateAncle_ = textureRotateAncle;
}

void EllipticHyperboloid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);

    painter->setPen(QPen(Qt::black, 0.3));
    painter->drawPath(meshPath_);

    painter->setPen(QPen(Qt::red, 2));
    painter->drawPath(texturePath_);

    transformateDatail();
}

void EllipticHyperboloid::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation2d_->getTransformation().first);
}

void EllipticHyperboloid::genHyperboloid()
{
    elipses_.clear();

    for (float V = -5.7f; V <= 5.7f; V+=meshStep_) {
        vector<QVector3D> elips;
        for (float U = 0.; U <= PI2; U+=meshStep_) {
            elips.emplace_back(QVector3D{
                                     abc_.x() * coshf(V) * cosf(U),
                                     abc_.y() * coshf(V) * sinf(U),
                                     abc_.z() * sinhf(V)
                                 });
            elips.emplace_back(elips.back());
        }
        elipses_.emplace_back(elips);
    }
}

void EllipticHyperboloid::refrashPictureData()
{
    meshPath_ = texturePath_ = QPainterPath();

    QPoint pinnedPoint = boundingRect().center().toPoint();
    vector<vector<QPointF>> elipses2d;


    // construct elipses
    for (const auto &elips : elipses_) {
        vector<QPointF> elips2d =
                transformation3d_
                ->setToIdentity()
                .translate(QVector3D(pinnedPoint.x(), pinnedPoint.y(), 0))
                .rotate()
                .mapTo2d(elips);
        elipses2d.emplace_back(std::move(elips2d));

        meshPath_.moveTo(elipses2d.back().front());
        for (const auto &p : elipses2d.back()) {
            meshPath_.lineTo(p);
        }
        meshPath_.closeSubpath();
    }

    const size_t pointsCount = elipses2d.front().size();
    const size_t elipsesCount = elipses2d.size();

    // construct parabolas
    for (size_t elipsPointId = 0; elipsPointId < pointsCount; ++elipsPointId) {
        meshPath_.moveTo(elipses2d[0][elipsPointId]);
        for (size_t elipsId = 0; elipsId < elipsesCount; ++elipsId) {
            meshPath_.lineTo(elipses2d[elipsId][elipsPointId]);
        }
    }


    // construct texture points on elliptic hyperboloid

    // textureMaxX_   = 100%
    // pX             = ((100% * pX) / textureMaxX_)
    //
    // * Find mapped_p on pointsCount *
    //
    // pointsCount  = 100%
    // mappedPX     = ((100% * pX) / textureMaxX_) * (pointsCount / 100%)
    //                 ||
    //                 \/
    //              xCoefficient = (elipsesCount-1) / textureMaxX_

    #define to_size(var) static_cast<size_t>((var)) /* cast to size_t */

    const double xCoefficient = (elipsesCount-1) / textureMaxX_ * 0.1;
    const double yCoefficient = (pointsCount-1) / textureMaxY_ * 0.1;


    QTransform textureTransformer;

    {
        Transformation2D transformer2d;
        transformer2d.setTranslationPoint(textureTranslatePoint_); // move texture by x and y
        transformer2d.setRotateAncle(textureRotateAncle_);                 // rotate texture
        transformer2d.setRotatePoint(textureTransformer.map(texture_[0])); // around its first point
        textureTransformer *= transformer2d.getTransformation().first;
    }

    size_t mpX_ctrlP, mpX1_endP;
    size_t mpY_ctrlP, mpY1_endP;

    for (size_t i = 0; i < texture_.size() - 1; i += 2) {
        //QVector2D &stP = texture_[i+0]; not used here...
        QPointF ctrlP = textureTransformer.map(texture_[i+1]);
        QPointF endP = textureTransformer.map(texture_[i+2]);

        mpX_ctrlP = to_size(ctrlP.x() * xCoefficient);
        mpY_ctrlP = to_size(ctrlP.y() * yCoefficient);

        mpX1_endP = to_size(endP.x() * xCoefficient);
        mpY1_endP = to_size(endP.y() * yCoefficient);

        if(mpX_ctrlP >= elipsesCount || mpY_ctrlP >= pointsCount || mpX1_endP >= elipsesCount || mpY1_endP >= pointsCount)
            continue;

        // add Bezie curve from currentPosition() to endP, that mapped to Elliptic Hyperboloid
        if (texturePath_.elementCount() == 0) {
            texturePath_.moveTo(elipses2d[mpX1_endP][mpY1_endP]);
        } else {
            texturePath_.quadTo(elipses2d[mpX_ctrlP][mpY_ctrlP],
                               elipses2d[mpX1_endP][mpY1_endP]);
            //texturePath_.addEllipse(elipses2d[mpX1_endP][mpY1_endP], 3, 3);
        }
    }
    texturePath_.closeSubpath();
}

double EllipticHyperboloid::maxComparator(const QPointF &l, const QPointF &r){
    return l.y() < r.y();
}

