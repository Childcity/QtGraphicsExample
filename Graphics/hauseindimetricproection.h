#ifndef HauseInDimetricProection_H
#define HauseInDimetricProection_H

#include "Basic/graphicsitembase.h"
#include "Basic/transformation2d.h"

#include <QChart>

using namespace QtCharts;

class HauseInDimetricProection: public GraphicsItemBase {
private:
    std::vector<QVector3D> points_ {
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
    HauseInDimetricProection(QChart *chart, Transformation2D *transformation);

    QRectF boundingRect() const override;

    void redraw() override;

private:
    void transformateDatail() override;

    void genHouse();

};

#endif // HauseInDimetricProection_H
