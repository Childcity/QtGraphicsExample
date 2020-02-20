#ifndef TRANSFORMATION3D_H
#define TRANSFORMATION3D_H

#include <vector>
#include <cmath>
#include <QVector3D>
#include <QMatrix4x4>

class Transformation3D {
private:
    QVector3D xyzRotationAngles_;
    QMatrix4x4 proection_;
    //std::vector<QVector3D> points3d_;

public:
    explicit Transformation3D(QVector3D xyzRotationAngles = QVector3D())
        : xyzRotationAngles_(std::move(xyzRotationAngles))
    {}

//    Transformation3D &rotate(double angle, const QVector3D &axis )
//    {
//        float x = axis.x();
//        float y = axis.y();
//        float z = axis.z();

//        float c = cos(angle);
//        float s = sin(angle);

//        QMatrix4x4 rotationMat = {
//           x*x*(1.0f-c)+c,   x*y*(1.0f-c)-z*s, x*z*(1.0f-c)+y*s, 0.0f,
//           y*x*(1.0f-c)+z*s, y*y*(1.0f-c)+c,   y*z*(1.0f-c)-x*s, 0.0f,
//           z*x*(1.0f-c)-y*s, z*y*(1.0f-c)+x*s, z*z*(1.0f-c)+c,   0.0f,
//           0.0f,             0.0f,             0.0f,             1.0f };

//        return *this;
//    }

    Transformation3D &setRotationAngles(QVector3D rotationAngles)
    {
        xyzRotationAngles_ = std::move(rotationAngles);
        return *this;
    }

    Transformation3D &setXRotationAngles(float xRotationAngle)
    {
        xyzRotationAngles_.setX(xRotationAngle);
        return *this;
    }

    Transformation3D &setYRotationAngles(float yRotationAngle)
    {
        xyzRotationAngles_.setY(yRotationAngle);
        return *this;
    }

    Transformation3D &setZRotationAngles(float zRotationAngle)
    {
        xyzRotationAngles_.setZ(zRotationAngle);
        return *this;
    }

//    Transformation3D *set3dPoints(std::vector<QVector3D> points3d)
//    {
//        points3d_ = std::move(points3d);
//        return this;
//    }


    Transformation3D &setToIdentity()
    {
        proection_.setToIdentity();
        return *this;
    }

    Transformation3D &rotate()
    {
        proection_.rotate(xyzRotationAngles_.x(), {1, 0, 0});
        proection_.rotate(xyzRotationAngles_.y(), {0, 1, 0});
        proection_.rotate(xyzRotationAngles_.z(), {0, 0, 1});
        return *this;
    }

    Transformation3D &translate(const QVector3D &delta)
    {
        proection_.translate(delta);
        return *this;
    }

    std::vector<QPointF> mapTo2d(const std::vector<QVector3D> &points3d) const
    {
        std::vector<QPointF> mapped;

        for (const auto &p : points3d) {
            mapped.emplace_back(proection_.map(p).toPointF());
        }

        return mapped;
    }
};

#endif // TRANSFORMATION3D_H
