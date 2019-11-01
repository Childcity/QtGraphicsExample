#include "bernoullilemniscate.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

void BernoulliLemniscate::redraw()
{
    GraphicsItemBase::redraw();
    update();
}

void BernoulliLemniscate::setFocus(double focus)
{
    focus_ = focus;
}

BernoulliLemniscate::BernoulliLemniscate(QChart *chart, Transformation *transformation)
    : GraphicsItemBase (chart, transformation)
{}

BernoulliLemniscate::~BernoulliLemniscate(){}

QRectF BernoulliLemniscate::boundingRect() const
{
    return QRectF(0, 0, 200, 200);

}

void BernoulliLemniscate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);

    QPointF stP = boundingRect().center();
    const auto points = getPoints(120., stP);
    painter->drawLines(points.second.constData(), points.second.length()/2);
    qDebug() <<points.second <<endl<<endl;

    double Mx = 61.8656,
            My = 220.389;

    const auto realMxMy = std::find_if(points.second.constBegin(), points.second.constEnd(), [&](const QPointF &p){
        return fabs(p.x() - Mx) < 0.01 && fabs(p.y() - My) < 0.01;
    });

    if(realMxMy != points.second.end()){
        int posMxMy = points.second.indexOf(*realMxMy);
        double phi = points.first[posMxMy];

        // касательная
        // y = k * (x - x0) + y0

        double cSQRT_2 = 120. * M_SQRT2;
        double dx = ((cSQRT_2 * sin(phi)) * (sin(phi)*sin(phi) + 2.*cos(phi)*cos(phi) + 1.)) / pow(sin(phi)*sin(phi) + 1., 2);
        double dy = (cos(phi)*cos(phi) * (cSQRT_2 - cSQRT_2 * sin(phi)*sin(phi)) - cSQRT_2 * pow(sin(phi), 4) - cSQRT_2*sin(phi)*sin(phi)) / pow(sin(phi)*sin(phi) + 1., 2);

        double k = -dy/dx /** (phi>M_PI_4 ? -1 : 1)*/; //производная Лемнискаты Бернули

        double x1 = -1000., y1 = k * (x1 - Mx) + My;//k*x1 + (My - k*Mx);
        double x2 = 1000., y2 = k * (x2 - Mx) + My; //k*x2 + (My - k*Mx);

        painter->drawEllipse(QRectF(Mx-5, My-5, 10, 10));
        painter->drawLine(QLineF(x1, y1, x2, y2));
        //qDebug() <<QLineF(x1, y1, x2, y2);
    }

    transformateDatail();
}

void BernoulliLemniscate::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation_->getTransformation().first);
}
