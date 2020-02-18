#include "transformation2d.h"

double Transformation2D::getDeltaWidth() const
{
    return deltaWidth_;
}

void Transformation2D::setDeltaWidth(double deltaWidth)
{
    deltaWidth_ = deltaWidth;
}

double Transformation2D::getRotateAncle() const
{
    return rotateAncle_;
}

void Transformation2D::setRotateAncle(double rotateAncle)
{
    rotateAncle_ = rotateAncle;
}

QPointF Transformation2D::getRotatePoint() const
{
    return rotatePoint_;
}

void Transformation2D::setRotatePoint(const QPointF &rotatePoint)
{
    rotatePoint_ = rotatePoint;
}

bool Transformation2D::isAffineEnabled() const
{
    return isAffineEnabled_;
}

void Transformation2D::setAffineEnabled(bool isAffineEnabled)
{
    isAffineEnabled_ = isAffineEnabled;
}

bool Transformation2D::isProectiveEnabled() const
{
    return isProectiveEnabled_;
}

void Transformation2D::setProectiveEnabled(bool isProectiveEnabled)
{
    isProectiveEnabled_ = isProectiveEnabled;
}

QVector<QPair<float, QPointF> > Transformation2D::getAffineSystemPoints() const
{
    return affineSystemPoints_;
}

void Transformation2D::setAffineSystemPoint(const QPointF &affineSystemPoint, int i)
{
    affineSystemPoints_[i].second = affineSystemPoint;
}

void Transformation2D::setAffineSystemWeight(float weight, int i)
{
    affineSystemPoints_[i].first = weight;
}

QPair<QTransform, QTransform> Transformation2D::getTransformation() const
{
    QTransform transformMatrix;

    {
        float a    = static_cast<float>(M_PI/180. * rotateAncle_);
        float sina = sinf(a);
        float cosa = cosf(a);
        float centerX = static_cast<float>(rotatePoint_.x());
        float centerY = static_cast<float>(rotatePoint_.y());

        // rotate about Z and translate
        QMatrix4x4 transformationMatrix = QMatrix4x4(cosa,   sina,   0,    centerX - cosa*centerX - sina*centerY,
                                                     -sina,   cosa,   0,   centerY - -sina*centerX - cosa*centerY,
                                                     0,       0,     1,   0,
                                                     0,       0,     0,   1);

        transformMatrix = transformationMatrix.toTransform();
    }

    if(isProectiveEnabled_){
        double Xy = affineSystemPoints_[0].second.x();
        double Yy = affineSystemPoints_[0].second.y();
        double Wy = static_cast<double>(affineSystemPoints_[0].first);

        double X0 = affineSystemPoints_[1].second.x();
        double Y0 = affineSystemPoints_[1].second.y();
        double W0 = static_cast<double>(affineSystemPoints_[1].first);

        double Xx = affineSystemPoints_[2].second.x();
        double Yx = affineSystemPoints_[2].second.y();
        double Wx = static_cast<double>(affineSystemPoints_[2].first);

        const auto proectiveT = QTransform(Xx*Wx,    Yx*Wx,          Wx,
                                           Xy*Wy,    Yy*Wy,          Wy,
                                           X0*W0,    Y0*W0,          W0);
        transformMatrix *= proectiveT;

        //            chart_->setPos(pos());
        //            chart_->setTransform(proectiveT);
        return {transformMatrix, proectiveT};
    }

    if(isAffineEnabled_){
        double Xy = affineSystemPoints_[0].second.x()/300;
        double Yy = affineSystemPoints_[0].second.y()/300;

        double X0 = affineSystemPoints_[1].second.x()/1000;
        double Y0 = affineSystemPoints_[1].second.y()/1000;


        double Xx = affineSystemPoints_[2].second.x()/300;
        double Yx = affineSystemPoints_[2].second.y()/300;

        const auto affineT = QTransform(Xx,    Yx,          0,
                                        Xy,    Yy,          0,
                                        X0,    Y0,          1);
        transformMatrix *= affineT;

        //            chart_->setPos(pos());
        //            chart_->setTransform(affineT);
        return {transformMatrix, affineT};
    }

    return {transformMatrix, QTransform()};
}

double Transformation2D::getDeltaHeight() const
{
    return deltaHeight_;
}

void Transformation2D::setDeltaHeight(double deltaHeight)
{
    deltaHeight_ = deltaHeight;
}
