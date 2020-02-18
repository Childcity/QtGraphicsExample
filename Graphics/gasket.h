#ifndef GASKET_H
#define GASKET_H

#include "Basic/graphicsitembase.h"
#include "Basic/transformation2d.h"

#include <QChart>
#include <QGraphicsItem>

using namespace QtCharts;

class Gasket : public GraphicsItemBase {
    constexpr static double margin = 10;

    bool isPointsNamesVisible_ = false;
    double AB_GH_ = 55;
    double CF_ = 20;
    double DE_ = 30;
    double PB_ = 14;
    double arc8R_ = 10;
    double arc13R_ = 10;
    double arc11R_ = 13;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    Gasket(QChart *chart, Transformation2D *transformation);

    ~Gasket() override;

    QRectF boundingRect() const override;

    void redraw() override;

    void setABGH(double value);

    void setArc8R(double value);

    void setArc13R(double value);

    void setArc11R(double arc11R);

    void setPointsNamesVisible(bool isPointsNamesVisible);

    void setCF(double CF);

    void setDE(double DE);

    void setPB(double BP);

private:
    void transformateDatail() override;

    void drawSymetricLines(QPainter *painter, const QPointF &stP, const QVector<QPointF> &arc11);

    void drawGasket(QPainter *painter);

    void drawPointsNames(QPainter *painter, const QVector<QLineF> &lines);
};

#endif // GASKET_H
