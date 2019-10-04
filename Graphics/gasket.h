#ifndef GASKET_H
#define GASKET_H

#include <QChart>
#include <QGraphicsItem>

using namespace QtCharts;

class Gasket : public QGraphicsItem {
private:
    constexpr static double margin = 10;
    constexpr static double k = 5.65;
    constexpr static int fontSize = 12;
    constexpr static double textDistance = 2 * k;
    const QPointF affineXYDelta = {8, 48};

    QChart *chart_;

    bool isPointsNamesVisible_ = false;
    double height_ = 0;
    double width_ = 0;
    double AB_GH_ = 55;
    double CF_ = 20;
    double DE_ = 30;
    double PB_ = 14;
    double arc8R_ = 10;
    double arc13R_ = 10;
    double arc11R_ = 13;

    // Transformations
    double rotateAncle_ = 0;
    QPointF rotatePoint_;

    // Affine
    bool isAffineEnabled_ = false;
    QVector<QPair<float, QPointF>> affineSystemPoints_ = {
        QPair<float, QPointF>(10, {0, 0}),
        QPair<float, QPointF>(1000, {0, 0}),
        QPair<float, QPointF>(10, {0, 0})
    };

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    Gasket(QChart *chart);

    ~Gasket() override;

    QRectF boundingRect() const override;

    void setABGH(double value);

    void setHeight(double value);

    void setWidth(double width);

    void redraw();

    void setArc8R(double value);

    void setArc13R(double value);

    void setArc11R(double arc11R);

    void setPointsNamesVisible(bool isPointsNamesVisible);

    void setCF(double CF);

    void setDE(double DE);

    void setPB(double BP);

    void setRotateAncle(double rotateAncle);

    void setRotatePoint(const QPointF &rotatePoint);

    void setIsAffineEnabled(bool isAffineEnabled);

    void setAffineSystemPoints(const QPointF &affineSystemPoint, int i);

    void setAffineSystemWeights(float weight, int i);

    QPointF getCoordXEnd();

    QPointF getCoordYEnd();

private:
    void drawPointsNames(QPainter *painter, const QVector<QLineF> &lines);

    void drawSymetricLines(QPainter *painter, const QPointF &stP, const QVector<QPointF> &arc11);

    void transformateDatail();
};

#endif // GASKET_H
