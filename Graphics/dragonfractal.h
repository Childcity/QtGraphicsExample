#ifndef DragonFractal_H
#define DragonFractal_H

#include "graphicsitembase.h"
#include "transformation.h"

#include <QChart>
#include <QGraphicsItem>
#include <random>

using namespace QtCharts;

class DragonFractal: public GraphicsItemBase {
private:
    constexpr static int iterCount = 50000;

    std::array<QPointF, iterCount> points;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    DragonFractal(QChart *chart, Transformation *transformation);

    QRectF boundingRect() const override;

    void redraw() override;

private:
    void transformateDatail() override;

    void genDragon();

    double genRandom(double a, double b) const;

private:
    struct Randomizer {
    private:
        std::mt19937_64 rng_;
        std::uniform_real_distribution<double> *unif_;
    public:
        Randomizer(double a, double b)
        {
            // initialize the random number generator with time-dependent seed
            uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
            rng_.seed(ss);

            // initialize a uniform distribution between 0 and 1
            unif_ = new std::uniform_real_distribution<double>(a, b);
        }

        double getNext() { return (*unif_)(rng_); }

        ~Randomizer() { delete unif_; }
    };
};

#endif // DragonFractal_H
