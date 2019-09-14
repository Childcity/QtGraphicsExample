#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"

#include <cmath>


namespace  Graphics {

const static double PHI_STEP = 0.05;

class Circle : public Figure {
protected:
    double r_;
    QPointF center_;
    double phiStep_ = PHI_STEP; //step for drawing
    double startAngle_ = 0.;
    double endAngle_ = 2. * M_PI;

public:
    Circle(double r, QPointF center, double phiStep = PHI_STEP);

    QVector<QPointF> getPoints() const override;

    virtual ~Circle() override;
};

}

#endif // CIRCLE_H
