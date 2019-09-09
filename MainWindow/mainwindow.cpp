#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QChartView>
#include <qchart.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _chart = new QChart();
    _chart->setTitle("Simple areachart example");
    _chart->addSeries(new QLineSeries(new QLineSeries()));
    _chart->createDefaultAxes();
    _chart->axisX()->setRange(0, 100);
    _chart->axisY()->setRange(0, 100);


    _ui->chartView->setRenderHint(QPainter::Antialiasing);
    _ui->chartView->setChart(_chart);
    _scene = _ui->chartView->scene();

//    _scene = new QGraphicsScene(this);
//    _ui->graphicsView->setScene(_scene);

    // create our Gasket object and add it to the scene

    _gasket = new Gasket();
    _scene->addItem(_gasket);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   //QMainWindow::resizeEvent(event);

   resize(event->size().height() + 50, event->size().height());
}

MainWindow::~MainWindow()
{
    delete _gasket;
    delete _ui;
}
