#ifndef GRAPHICSITEMBASE_H
#define GRAPHICSITEMBASE_H

#include "transformation2d.h"

#include <QChart>
#include <QGraphicsItem>

using namespace QtCharts;

class GraphicsItemBase : public QGraphicsItem {
protected:
    constexpr static double k = 5.65;
    constexpr static int fontSize = 12;
    constexpr static double textDistance = 2 * k;
    const QPointF affineXYDelta = {8, 55};

    QChart *chart_;
    QPointF chartPos_;

    const Transformation2D *transformation_;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void transformateDatail();

    virtual void redraw();

public:
    GraphicsItemBase(QChart *chart, Transformation2D *transformation);

    QPointF getCoordXEnd();

    QPointF getCoordYEnd();

    ~GraphicsItemBase() override;
};

#endif // GRAPHICSITEMBASE_H
