#include "arc.h"

#include <cmath>
#include <QDebug>

Graphics::Arc::Arc(double startAngle, double endAngle, double r, QPointF center, double phiStep)
    : Circle(r, center, phiStep)
{
    startAngle_ = startAngle;
    endAngle_ = endAngle;
}

QVector<QPointF> Graphics::Arc::getPoints() const
{
    return Circle::getPoints();
}

Graphics::Arc::~Arc() {}
