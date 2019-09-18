#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"

#include <QChartView>
#include <qchart.h>

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
    connect(ui_->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value){ gasket_->setABGH(value); });
    connect(ui_->spinBox_2, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value){ gasket_->setHeight(value); });
    connect(ui_->spinBox_5, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value){ gasket_->setArc13R(value); });
    connect(ui_->spinBox_6, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value){ gasket_->setArc8R(value); });
    connect(ui_->spinBox_3, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value){ gasket_->setArc11R(value); });
    connect(ui_->spinBox_4, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value){ gasket_->setCF(value); });
    connect(ui_->spinBox_7, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value){ gasket_->setDE(value); });
    connect(ui_->spinBox_8, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value){ gasket_->setPB(value); });
    connect(ui_->spinBox_9, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value){ gasket_->setRotateAncle(value); });


    QGraphicsEllipseItem *rotatePoint = new QGraphicsEllipseItem(*new QRectF(pos().x()-5, pos().y()-5, 10, 10), gasket_);

    scene_->addItem(gasket_);
    scene_->addItem(rotatePoint);
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
