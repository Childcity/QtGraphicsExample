#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"

#include <QChartView>
#include <qchart.h>

#include <Graphics/movablepoint.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    chart_ = new QChart();
    chart_->setParent(this);
    chart_->setTitle("Городецкий Николай - Вариант №3");
    chart_->legend()->setVisible(false);

    QValueAxis *axisX = new QValueAxis(chart_);
    axisX->setRange(0, 100);
    axisX->setTickCount(11);
    axisX->setMinorTickCount(1);
    axisX->setTitleText("X ----> mm");
    axisX->setLabelFormat("%.1f");

    QValueAxis *axisY = new QValueAxis(chart_);
    axisY->setRange(0, 100);
    axisY->setTickCount(11);
    axisY->setMinorTickCount(1);
    axisY->setTitleText("Y ----> mm");
    axisY->setLabelFormat("%.1f");

    chart_->setAxisX(axisX);
    chart_->setAxisY(axisY);


    ui_->chartView->setRenderHint(QPainter::Antialiasing);
    ui_->chartView->setChart(chart_);
    scene_ = ui_->chartView->scene();

    // create our Gasket object and add it to the scene
    gasket_ = new Gasket(chart_);

    connect(ui_->checkBox, &QCheckBox::clicked, [=](bool value){ gasket_->setPointsNamesVisible(value); });
    connect(ui_->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setABGH(value); });
    connect(ui_->spinBox_2, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setHeight(value); });
    connect(ui_->spinBox_10, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setWidth(value); });
    connect(ui_->spinBox_5, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setArc13R(value); });
    connect(ui_->spinBox_6, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setArc8R(value); });
    connect(ui_->spinBox_3, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setArc11R(value); });
    connect(ui_->spinBox_4, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setCF(value); });
    connect(ui_->spinBox_7, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setDE(value); });
    connect(ui_->spinBox_8, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setPB(value); });
    connect(ui_->spinBox_9, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setRotateAncle(value); });


    {
        // setting up rotatePoint
        MovablePoint *rotatePoint = new MovablePoint(10, Qt::blue, chart_);

        QPointF mappedPos = rotatePoint->mapFromItem(gasket_, gasket_->pos());
        QPointF delta = mappedPos - gasket_->pos();
        rotatePoint->setPos(mappedPos);
        connect(rotatePoint, &MovablePoint::positionChanged, this, [=](const QPointF &value){ gasket_->setRotatePoint(value - delta); });
    }



    {
        // setting up affinePoints
        QVector<MovablePoint::Ptr> affinePoints(3);
        QVector<QPointF> mappedPoss(3);
        QVector<QPointF> deltas(3);

        for (int i = 0; i < affinePoints.size(); ++i) {
            affinePoints[i] = new MovablePoint(6, Qt::green, chart_);

            auto newPlace = QPointF(gasket_->pos().x(), gasket_->pos().y() - 0);
            mappedPoss[i] = affinePoints[i]->mapFromItem(gasket_, newPlace);
            deltas[i] = mappedPoss[i] - gasket_->pos();
            affinePoints[i]->setPos(mappedPoss[i]);

            connect(affinePoints[i], &MovablePoint::positionChanged, this, [=](const QPointF &value){ gasket_->setAffineSystemPoints(value - deltas[i], i); });
        }
    }


    scene_->addItem(gasket_);

//     next doesn't need, because if we provide parent for MovablePoint object (chart_), it automaticaly adds to scene_
//     with chart_
//    scene_->addItem(rotatePoint);
//    scene_->addItem(affinePoints[0]);
//    scene_->addItem(affinePoints[1]);
//    scene_->addItem(affinePoints[2]);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui_;
    delete gasket_;
    chart_->deleteLater();
}
