#ifndef GASKET_H
#define GASKET_H

#include <QChart>
#include <QGraphicsItem>

using namespace QtCharts;

class Gasket : public QGraphicsItem {
private:
    constexpr static double k = 4.65;
    constexpr static int fontSize = 12;
    constexpr static double textDistance = 2 * k;

    QChart *chart_;

    bool isPointsNamesVisible_ = true;
    double height_ = 50;
    double AB_GH_ = 55;
    double CF_ = 20;
    double DE_ = 30;
    double PB_ = 14;
    double arc8R_ = 10;
    double arc13R_ = 10;
    double arc11R_ = 13;

public:
    Gasket(QChart *chart);

public:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setABGH(double value);

    void setHeight(double value);

    void redraw();

    void setArc8R(double value);

    void setArc13R(double value);

    void setArc11R(double arc11R);

    void setPointsNamesVisible(bool isPointsNamesVisible);

    void setCF(double CF);

    void setDE(double DE);

    void setPB(double BP);

private:
    void drawPointsNames(QPainter *painter, const QVector<QLineF> &lines);
};

#endif // GASKET_H
