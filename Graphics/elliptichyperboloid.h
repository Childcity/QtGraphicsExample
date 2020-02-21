#ifndef EllipticHyperboloid_H
#define EllipticHyperboloid_H

#include "Basic/graphicsitembase.h"
#include "Basic/transformation2d.h"
#include "Basic/transformation3d.h"

#include <QChart>
#include <vector>

using std::vector;
using namespace QtCharts;

class EllipticHyperboloid: public GraphicsItemBase {
private:
    constexpr static float PI2 = static_cast<float>(2.*M_PI);

    vector<vector<QVector3D>> elipses_;
    vector<QVector2D> texture_;

    Transformation3D *transformation3d_;
    float meshStep_ = 0.1f;

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
