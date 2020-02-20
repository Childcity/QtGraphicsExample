#ifndef EllipticHyperboloid_H
#define EllipticHyperboloid_H

#include "Basic/graphicsitembase.h"
#include "Basic/transformation2d.h"
#include "Basic/transformation3d.h"

#include <QChart>
#include <exception>

using std::vector;
using std::list;
using std::pair;
using namespace QtCharts;

class EllipticHyperboloid: public GraphicsItemBase {
private:
    vector<QVector3D> points_;

    Transformation3D *transformation3d_;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    EllipticHyperboloid(QChart *chart, Transformation2D *transformation2d, Transformation3D *transformation3d);

    QRectF boundingRect() const override;

    void redraw() override;

private:
    void transformateDatail() override;

    void genHyperboloid();

};

#endif // EllipticHyperboloid_H
