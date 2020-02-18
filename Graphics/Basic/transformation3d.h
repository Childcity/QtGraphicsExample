#ifndef TRANSFORMATION3D_H
#define TRANSFORMATION3D_H

#include <vector>
#include <QVector3D>

class Transformation3D {
private:
    std::vector<QVector3D> points_{};

public:
    explicit Transformation3D(std::vector<QVector3D> points)
        : points_(std::move(points))
    {}

    Transformation3D &rotate(double alph, double bett, double gamm)
    {

        return *this;
    }

};

#endif // TRANSFORMATION3D_H
