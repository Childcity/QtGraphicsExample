#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <QMatrix4x4>
#include <QPair>
#include <QPointF>
#include <QTransform>
#include <QVector>

#include <algorithm>
#include <cmath>

class Transformation {
    double deltaHeight_ = 0;
    double deltaWidth_ = 0;

    double rotateAncle_ = 0;
    QPointF rotatePoint_;

    // Affine
    bool isAffineEnabled_ = false;
    bool isProectiveEnabled_ = false;
    QVector<QPair<float, QPointF>> affineSystemPoints_ = {
        {10, {0, 0}},
        {1000, {0, 0}},
        {10, {0, 0}}
    };

public:
    explicit Transformation(){}

    QPair<QTransform, QTransform> getTransformation() const;

    double getDeltaHeight() const;
    void setDeltaHeight(double deltaHeight);

    double getDeltaWidth() const;
    void setDeltaWidth(double deltaWidth);

    double getRotateAncle() const;
    void setRotateAncle(double rotateAncle);

    QPointF getRotatePoint() const;
    void setRotatePoint(const QPointF &rotatePoint);

    bool isAffineEnabled() const;
    void setAffineEnabled(bool isAffineEnabled);

    bool isProectiveEnabled() const;
    void setProectiveEnabled(bool isProectiveEnabled);

    QVector<QPair<float, QPointF> > getAffineSystemPoints() const;
    void setAffineSystemPoint(const QPointF &affineSystemPoint, int i);
    void setAffineSystemWeight(float weight, int i);
};

#endif // TRANSFORMATION_H
