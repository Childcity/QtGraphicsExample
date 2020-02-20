#include "dragonfractal.h"

#include <QPainter>
#include <QPen>
#include <QDebug>
#include <qgraphicssceneevent.h>
#include <QGraphicsScene>
#include <QThread>

void DragonFractal::redraw() {
    GraphicsItemBase::redraw();
    update();
}

DragonFractal::DragonFractal(QChart *chart, Transformation2D *transformation2d)
    : GraphicsItemBase (chart, transformation2d)
{
    genDragon();
}

QRectF DragonFractal::boundingRect() const
{
    // outer most edges
    double xDelta = transformation2d_->getDeltaWidth()*k
            + (transformation2d_->isProectiveEnabled() || transformation2d_->isAffineEnabled()
               ? affineXYDelta.x()*k
               : 0);

    double yDelta = transformation2d_->getDeltaHeight()*k
            - (transformation2d_->isProectiveEnabled() || transformation2d_->isAffineEnabled()
               ? affineXYDelta.y()*k
               : 0);


    return QRectF(160 + xDelta
                  , 0 - 150 + yDelta
                  , 400
                  , 400);
}

void DragonFractal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);

    //genDragon(); // uncomment, if you want to see generation in real time

    double yToMoveDragon = (boundingRect().center() - boundingRect().center() / 0.4).y();
    QPointF deltaToMoveDragon(boundingRect().center().x(), yToMoveDragon);

    for(const auto &p : points){
        painter->setPen(QPen(p.second, 1));
        painter->drawPoint((p.first * 30) + deltaToMoveDragon);
    }

    transformateDatail();
}

void DragonFractal::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation2d_->getTransformation().first);
}

void DragonFractal::genDragon(){

    // Init Dragon fractal coeficients
    static std::vector<double> inSystem = {
        0.824074, 0.281482, -1.882290, -0.212346, 0.864198, -0.110607, 0.787473,
        0.088272, 0.520988, 0.785360, -0.463889, -0.377778, 8.095795, 0.212527
    };

    // Lambda function, for getting Point by x, y and line in equation
    const auto getNextPoint = [&](size_t line, double x, double y){
        return QPointF {
            inSystem[0 + line*7] * x + inSystem[1 + line*7] * y + inSystem[2 + line*7],
            inSystem[3 + line*7] * x + inSystem[4 + line*7] * y + inSystem[5 + line*7]

        };
    };

    // Generate fractal by iteration method (points.size() iteretions)

    QPointF nextPoint;
    for (size_t i = 0; i < points.size(); ++i) {

        Qt::GlobalColor color;
        if(genRandom(0, 1) < inSystem[6]){
            color = Qt::black;
            nextPoint = getNextPoint(0, nextPoint.x(), nextPoint.y());
        } else {
            color = Qt::red;
            nextPoint = getNextPoint(1, nextPoint.x(), nextPoint.y());
        }

        points[i] = {nextPoint, color};
    }
}

double DragonFractal::genRandom(double a, double b) const
{
    static Randomizer rnd(a, b);
    return rnd.getNext();
}

