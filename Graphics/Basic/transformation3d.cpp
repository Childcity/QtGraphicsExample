#include "transformation3d.h"


Transformation3D::Transformation3D(QVector3D xyzRotationAngles)
    : xyzRotationAngles_(std::move(xyzRotationAngles))
{}



Transformation3D &Transformation3D::setRotationAngles(QVector3D rotationAngles)
{
    xyzRotationAngles_ = std::move(rotationAngles);
    return *this;
}

Transformation3D &Transformation3D::setXRotationAngles(float xRotationAngle)
{
    xyzRotationAngles_.setX(xRotationAngle);
    return *this;
}

Transformation3D &Transformation3D::setYRotationAngles(float yRotationAngle)
{
    xyzRotationAngles_.setY(yRotationAngle);
    return *this;
}

Transformation3D &Transformation3D::setZRotationAngles(float zRotationAngle)
{
    xyzRotationAngles_.setZ(zRotationAngle);
    return *this;
}

Transformation3D &Transformation3D::setToIdentity()
{
    proection_.setToIdentity();
    return *this;
}

Transformation3D &Transformation3D::rotate()
{
    proection_.rotate(xyzRotationAngles_.x(), {1, 0, 0});
    proection_.rotate(xyzRotationAngles_.y(), {0, 1, 0});
    proection_.rotate(xyzRotationAngles_.z(), {0, 0, 1});
    return *this;
}

Transformation3D &Transformation3D::translate(const QVector3D &delta)
{
    proection_.translate(delta);
    return *this;
}

Transformation3D &Transformation3D::scale(const QVector3D &scale)
{
    proection_.scale(scale);
    return *this;
}

std::vector<QPointF> Transformation3D::mapTo2d(const std::vector<QVector3D> &points3d) const
{
    std::vector<QPointF> mapped;

    for (const auto &p : points3d) {
        mapped.emplace_back(proection_.map(p).toPointF());
    }

    return mapped;
}
