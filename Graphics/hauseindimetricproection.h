#ifndef HauseInDimetricProection_H
#define HauseInDimetricProection_H

#include "graphicsitembase.h"
#include "transformation.h"

#include <QChart>
#include <QGraphicsItem>
#include <random>

using namespace QtCharts;

class HauseInDimetricProection: public GraphicsItemBase {
private:
    QVector<QVector3D> housePoints_ {
        {
            {200, 350, 350}, {400, 350, 350}, {400, 200, 350},
            {300, 100, 350}, {200, 200, 350}, {200, 350, 50},
            {400, 350, 50}, {400, 200, 50}, {300, 100, 50},
            {200, 200, 50}
        }
    };

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    HauseInDimetricProection(QChart *chart, Transformation *transformation);

    QRectF boundingRect() const override;

    void redraw() override;

private:
    void transformateDatail() override;

    void genHouse();

};

#endif // HauseInDimetricProection_H
