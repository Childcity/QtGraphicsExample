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

    Transformation3D *transformation3d_;

    vector<vector<QVector3D>> elipses_;
    vector<QPointF> texture_;
    double textureMaxX_;
    double textureMaxY_;
    double textureRotateAncle_;

    // Picture pathes
    QPainterPath meshPath_;
    QPainterPath texturePath_;

    // EllipticHyperboloid parameters
    float meshStep_ = 0.05f;
    QVector3D abc_ = {2, 2, 2};
    QPointF textureTranslatePoint_ = {-100, 600};

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    EllipticHyperboloid(QChart *chart, Transformation2D *transformation2d, Transformation3D *transformation3d);

    QRectF boundingRect() const override;

    void redraw() override;

    float getMeshStep() const;
    void setMeshStep(float meshStep);

    QVector3D getAbc() const;
    void setAbc(const QVector3D &abc);
    void setA(float a);
    void setB(float b);
    void setC(float c);

    QPointF getTextureTranslatePoint() const;
    void setTextureTranslatePoint(const QPointF &textureTranslatePoint);
    void setTextureTranslatePointX(double x);
    void setTextureTranslatePointY(double y);

    void setTextureRotateAncle(double textureRotateAncle);

private:
    void transformateDatail() override;

    void genHyperboloid();

    void refrashPictureData();

    static double maxComparator(const QPointF &l, const QPointF &r);
};

#endif // EllipticHyperboloid_H
