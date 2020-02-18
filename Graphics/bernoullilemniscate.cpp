#include "bernoullilemniscate.h"

#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

void BernoulliLemniscate::redraw()
{
    GraphicsItemBase::redraw();
    update();
}

QPointF BernoulliLemniscate::getTangentedPoint() const
{
    return tangentedPoint_ / k ;
}

void BernoulliLemniscate::setFocus(double focus)
{
    focus_ = focus;
    redraw();
    emit sigFocusChanged(focus);
}

double BernoulliLemniscate::getFocus() const
{
    return focus_;
}

double BernoulliLemniscate::getArea() const { return getFocusSQRT2MM() * getFocusSQRT2MM(); }

double BernoulliLemniscate::getLength() const { return getFocusSQRT2MM() * 5.244; }

BernoulliLemniscate::BernoulliLemniscate(QChart *chart, Transformation2D *transformation)
    : GraphicsItemBase (chart, transformation)
{}

BernoulliLemniscate::~BernoulliLemniscate(){}

QRectF BernoulliLemniscate::boundingRect() const
{
    double xDelta = transformation_->getDeltaWidth()*k
            + (transformation_->isProectiveEnabled() || transformation_->isAffineEnabled()
               ? affineXYDelta.x()*k
               : 0);

    double yDelta = transformation_->getDeltaHeight()*k
            - (transformation_->isProectiveEnabled() || transformation_->isAffineEnabled()
               ? affineXYDelta.y()*k
               : 0);

    double scaleDelta = pow(std::abs(focus_*k), 0.9999);

    return QRectF(150 - scaleDelta + xDelta,
                  0 - scaleDelta - yDelta,
                  400 + 2*scaleDelta,
                  200 + 2*scaleDelta);

}

void BernoulliLemniscate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);

    QPointF stP = boundingRect().center();
    const auto points = getPoints(focus_*k, stP);


    {
        painter->setPen(QPen(Qt::red, 3, Qt::PenStyle::SolidLine));
        painter->drawLines(points.second.constData(), points.second.length()/2);

        painter->setPen({Qt::black, 1});
        painter->setFont(QFont("", fontSize, 1));

        QPointF txtP;
        txtP.rx() = stP.x()+focus_*k;
        txtP.ry() = stP.y() - textDistance*2;
        painter->drawText(txtP, "F");

        txtP.rx() = stP.x()-focus_*k;
        txtP.ry() = stP.y() - textDistance*2;
        painter->drawText(txtP, "F");

        painter->setPen(QPen(Qt::black, 2, Qt::PenStyle::SolidLine));
        painter->drawEllipse(QRectF(stP.x()+focus_*k-5, stP.y()-5, 10, 10));
        painter->drawEllipse(QRectF(stP.x()+focus_*k-8, stP.y()-8, 16, 16));
        painter->drawEllipse(QRectF(stP.x()-focus_*k-5, stP.y()-5, 10, 10));
        painter->drawEllipse(QRectF(stP.x()-focus_*k-8, stP.y()-8, 16, 16));
    }


    double Mx = tangentedPoint_.x();
    double My = tangentedPoint_.y();

    const QPointF *realMxMy = findRealMxMy(points, Mx, My);

    if(realMxMy != points.second.end()){

        int posMxMy = points.second.indexOf(*realMxMy);
        double phi = points.first[posMxMy];

        emit sigCurvatureRadiusChanged(getFocusSQRT2MM() * getFocusSQRT2MM() / 3. * phi);

        // касательная
        // y = k * (x - x0) + y0

        double cSQRT_2 = getFocusSQRT2();
        double dx = ((cSQRT_2 * sin(phi)) * (sin(phi)*sin(phi) + 2.*cos(phi)*cos(phi) + 1.)) / pow(sin(phi)*sin(phi) + 1., 2);
        double dy = (cos(phi)*cos(phi) * (cSQRT_2 - cSQRT_2 * sin(phi)*sin(phi)) - cSQRT_2 * pow(sin(phi), 4) - cSQRT_2*sin(phi)*sin(phi)) / pow(sin(phi)*sin(phi) + 1., 2);

        double k = -dy/dx /** (phi>M_PI_4 ? -1 : 1)*/; //производная Лемнискаты Бернули

        double x1 = -1000., y1 = k * (x1 - Mx) + My;//k*x1 + (My - k*Mx);
        double x2 = 1000., y2 = k * (x2 - Mx) + My; //k*x2 + (My - k*Mx);
        painter->drawLine(QLineF(x1, y1, x2, y2));

        // нормаль
        // y = -1/k * (x - x0) + y0

        y1 = -1./k * (x1 - Mx) + My;
        y2 = -1./k * (x2 - Mx) + My;
        painter->drawLine(QLineF(x1, y1, x2, y2));


        // tangent point
        painter->drawEllipse(QRectF(Mx-5, My-5, 10, 10));
    }

    //painter->drawRect(boundingRect()); //draw rectangle
    transformateDatail();
}

void BernoulliLemniscate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        tangentedPoint_ = event->pos();
    }

    QGraphicsItem::mousePressEvent(event);
}

void BernoulliLemniscate::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation_->getTransformation().first);
}

QPair<QVector<double>, QVector<QPointF>> BernoulliLemniscate::getPoints(double c, QPointF delta)
{
    QPair<QVector<double>, QVector<QPointF>> points;
    double startAngle = 0;
    double endAngle = 2*M_PI;
    double phiStep = 0.01;

    for (double phi = startAngle; phi <= endAngle + phiStep; phi += phiStep) {
        //double p = sqrt(tan(M_PI_4) - phi);
        double x = c * M_SQRT2 * cos(phi) / (pow(sin(phi),2) + 1); //c * M_SQRT2 * (p + pow(p, 3)) / (1 + pow(p, 4));
        double y = c * M_SQRT2 * cos(phi) * sin(phi) / (pow(sin(phi),2) + 1);//c * M_SQRT2 * (p - pow(p, 3)) / (1 + pow(p, 4));

        if(std::isnan(x) || std::isnan(y))
            break;

        points.first <<phi;
        points.second << (QPointF(x, y) + delta);

        int pLen = points.second.length();
        if(pLen > 2 && pLen % 2 != 0){
            points.second << points.second.at(pLen-2) << points.second.at(pLen-1);
            points.first << points.first.at(pLen-2) << points.first.at(pLen-1);
        }
    }

    return points;
}

double BernoulliLemniscate::getFocusSQRT2() const { return focus_ * k * M_SQRT2; }

double BernoulliLemniscate::getFocusSQRT2MM() const { return focus_ * M_SQRT2; }

const QPointF *BernoulliLemniscate::findRealMxMy(const QPair<QVector<double>, QVector<QPointF> > &points, double Mx, double My){
    return std::find_if(points.second.constBegin(), points.second.constEnd(), [&](const QPointF &p){
        return fabs(p.x() - Mx) < 2 && fabs(p.y() - My) < 2; // choose accuracy of tangentedPoint_ has been chosen by user
    });
}
