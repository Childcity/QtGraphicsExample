#ifndef ARC_H
#define ARC_H

#include "circle.h"

namespace Graphics {

class Arc : public Circle {

public:
    Arc(double startAngle, double endAngle, double r, QPointF center, double phiStep = PHI_STEP);

    QVector<QPointF> getPoints() const override;

    Arc &operator=(const Arc &other)
    {
        if (this != &other){
            r_ = other.r_;
            center_ = other.center_;
            phiStep_ = other.phiStep_;
            startAngle_ = other.startAngle_;
            endAngle_ = other.endAngle_;
        }

        return *this;
    }

    virtual ~Arc() override;
};

}

#endif // ARC_H
