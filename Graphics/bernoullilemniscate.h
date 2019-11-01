#ifndef BERNOULLILEMNISCATE_H
#define BERNOULLILEMNISCATE_H

#include "graphicsitembase.h"


class BernoulliLemniscate : public GraphicsItemBase {
    double focus_ = 120.;

public:
    BernoulliLemniscate(QChart *chart, Transformation *transformation);

    ~BernoulliLemniscate() override;

    QRectF boundingRect() const override;

    void redraw() override;

    void setFocus(double focus);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void transformateDatail() override;

    QPair<QVector<double>, QVector<QPointF>> getPoints(double c, QPointF delta)
    {
        QPair<QVector<double>, QVector<QPointF>> points;
        double startAngle = 0;
        double endAngle = 2*M_PI;
        double phiStep = 0.1;

        for (double phi = startAngle; phi <= endAngle + phiStep; phi += phiStep) {
            //double p = sqrt(tan(M_PI_4) - phi);
            double x = c * M_SQRT2 * cos(phi) / (pow(sin(phi),2) + 1); //c * M_SQRT2 * (p + pow(p, 3)) / (1 + pow(p, 4));
            double y = c * M_SQRT2 * cos(phi) * sin(phi) / (pow(sin(phi),2) + 1);//c * M_SQRT2 * (p - pow(p, 3)) / (1 + pow(p, 4));

            if(std::isnan(x) || std::isnan(y))
                break;

            points.first <<phi;
            points.second << (QPointF(x, y) + delta);

            int pLen = points.second.length();
            if(pLen > 2 && pLen % 2 != 0){
                points.second << points.second.at(pLen-2) << points.second.at(pLen-1);
                points.first << points.first.at(pLen-2) << points.first.at(pLen-1);
            }
        }

        return points;
    }
};

#endif // BERNOULLILEMNISCATE_H
