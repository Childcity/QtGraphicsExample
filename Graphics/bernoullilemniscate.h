#ifndef BERNOULLILEMNISCATE_H
#define BERNOULLILEMNISCATE_H

#include "Basic/graphicsitembase.h"


class BernoulliLemniscate : public QObject, public GraphicsItemBase {
    Q_OBJECT
private:
    double focus_ = 21.; //in mm

    QPointF tangentedPoint_;
    //очки перегиба

signals:
    void sigFocusChanged(double fucus);

    void sigCurvatureRadiusChanged(double curvatureRadius);

public:
    BernoulliLemniscate(QChart *chart, Transformation2D *transformation);

    ~BernoulliLemniscate() override;

    QRectF boundingRect() const override;

    void redraw() override;

    QPointF getTangentedPoint() const;

    void setFocus(double focus);

    double getFocus() const;

    double getArea() const;

    double getLength() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void transformateDatail() override;

    QPair<QVector<double>, QVector<QPointF>> getPoints(double c, QPointF delta);

    double getFocusSQRT2() const;

    double getFocusSQRT2MM() const;

    const QPointF *findRealMxMy(const QPair<QVector<double>, QVector<QPointF> > &points, double Mx, double My);
};

#endif // BERNOULLILEMNISCATE_H
