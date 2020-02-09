#include "dragonfractal.h"

#include <QPainter>
#include <QPen>
#include <QDebug>
#include <qgraphicssceneevent.h>
#include <QGraphicsScene>

void DragonFractal::redraw() {
    GraphicsItemBase::redraw();
    update();
}

DragonFractal::DragonFractal(QChart *chart, Transformation *transformation)
    : GraphicsItemBase (chart, transformation)
{
}

QRectF DragonFractal::boundingRect() const
{
    // outer most edges
    double xDelta = transformation_->getDeltaWidth()*k
            + (transformation_->isProectiveEnabled() || transformation_->isAffineEnabled()
               ? affineXYDelta.x()*k
               : 0);

    double yDelta = transformation_->getDeltaHeight()*k
            - (transformation_->isProectiveEnabled() || transformation_->isAffineEnabled()
               ? affineXYDelta.y()*k
               : 0);


    return QRectF(160 + xDelta
                  , 0 - 150 - yDelta
                  , 430
                  , 430);
}

void DragonFractal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);

    painter->setPen(QPen(Qt::black, 1));

    genDragon();
    painter->drawPoints(points.begin(), points.size());

    transformateDatail();
}

void DragonFractal::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation_->getTransformation().first);
}

void DragonFractal::genDragon(){

    static std::vector<double> inSystem = {
        0.824074, 0.281482, -1.882290, -0.212346, 0.864198, -0.110607, 0.787473,
        0.088272, 0.520988, 0.785360, -0.463889, -0.377778, 8.095795, 0.212527
    };

    const auto getNextPoint = [&](size_t line, double x, double y){
        return QPointF {
            inSystem[0 + line*7] * x + inSystem[1 + line*7] * y + inSystem[2 + line*7]
                    , inSystem[3 + line*7] * x + inSystem[4 + line*7] * y + inSystem[5 + line*7]

        };
    };

    QPointF nextPoint;
    for (size_t i = 0; i < points.size(); ++i) {

        if(genRandom(0, 1) < inSystem[6]){
            nextPoint = getNextPoint(0, nextPoint.x(), nextPoint.y());
        } else {
            nextPoint = getNextPoint(1, nextPoint.x(), nextPoint.y());
        }

        nextPoint = {nextPoint.x()+60, nextPoint.y()+60};

        points[i] = {
            nextPoint.x() + boundingRect().bottomLeft().x(),
            nextPoint.y() + boundingRect().center().y()
        };
    }
}

double DragonFractal::genRandom(double a, double b) const
{
    static Randomizer rnd(a, b);
    return rnd.getNext();
}

