#include "circle.h"


Graphics::Circle::Circle(double r, QPointF center, double phiStep)
    : r_(r)
    , center_(center)
    , phiStep_(phiStep)
{}

QVector<QPointF> Graphics::Circle::getPoints() const {
    QVector<QPointF> points;

    int n = 0;
    for (double phi = startAngle_; phi <= endAngle_/* + (phiStep_ * 4)*/; phi += phiStep_, n++) {
        double x = cos (phi) * r_ + center_.x();
        double y = sin (phi) * r_ + center_.y();
        points += QPointF(x, y);

        if(n % 2 == 0){ // for filling spaces between dashed lines
            points += QPointF(x, y);
            x = cos (phi - phiStep_) * r_ + center_.x();
            y = sin (phi - phiStep_) * r_ + center_.y();
            points += QPointF(x, y);
        }
    }

    return points;
}

Graphics::Circle::~Circle() {}
