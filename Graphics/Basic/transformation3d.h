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
    explicit Transformation3D(QVector3D xyzRotationAngles = QVector3D());

//    Transformation3D &rotate(double angle, const QVector3D &axis )
//    {
//        float x = axis.x();
//        float y = axis.y();
//        float z = axis.z();

//        float c = cos(angle);
//        float s = sin(angle);

//        QMatrix4x4 rotationMat = {
//            x*x*(1.0f-c)+c,   x*y*(1.0f-c)-z*s, x*z*(1.0f-c)+y*s, 0.0f,
//            y*x*(1.0f-c)+z*s, y*y*(1.0f-c)+c,   y*z*(1.0f-c)-x*s, 0.0f,
//            z*x*(1.0f-c)-y*s, z*y*(1.0f-c)+x*s, z*z*(1.0f-c)+c,   0.0f,
//            0.0f,             0.0f,             0.0f,             1.0f };

//        return *this;
//    }

    Transformation3D &setRotationAngles(QVector3D rotationAngles);

    Transformation3D &setXRotationAngles(float xRotationAngle);

    Transformation3D &setYRotationAngles(float yRotationAngle);

    Transformation3D &setZRotationAngles(float zRotationAngle);

    Transformation3D &setToIdentity();

    Transformation3D &rotate();

    Transformation3D &translate(const QVector3D &delta);

    Transformation3D &scale(const QVector3D &scale);

    std::vector<QPointF> mapTo2d(const std::vector<QVector3D> &points3d) const;
};

#endif // TRANSFORMATION3D_H
