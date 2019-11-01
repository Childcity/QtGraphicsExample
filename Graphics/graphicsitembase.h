#ifndef GRAPHICSITEMBASE_H
#define GRAPHICSITEMBASE_H

#include "transformation.h"

#include <QChart>
#include <QGraphicsItem>

using namespace QtCharts;

class GraphicsItemBase : public QGraphicsItem {
protected:
    constexpr static double k = 5.65;

    QChart *chart_;
    QPointF chartPos_;

    const Transformation *transformation_;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void transformateDatail();

    virtual void redraw();

public:
    GraphicsItemBase(QChart *chart, Transformation *transformation);

    QPointF getCoordXEnd();

    QPointF getCoordYEnd();

    ~GraphicsItemBase() override;
};

#endif // GRAPHICSITEMBASE_H
