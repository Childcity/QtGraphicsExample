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
    ui_->tabWidget->setCurrentIndex(3);
    setStyleSheet("font: 10pt 'Ubuntu';font-style: normal;");

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

    transformation_ = new Transformation();

    // create our Gasket object and add it to the scene
    gasket_ = new Gasket(chart_, transformation_);
    bLemniscat_ = new BernoulliLemniscate(chart_, transformation_);
    plane_ = new Plane(chart_, transformation_);
    dragon_ = new DragonFractal(chart_, transformation_);

    connect(ui_->checkBox, &QCheckBox::clicked, [=](bool value){ gasket_->setPointsNamesVisible(value); });
    connect(ui_->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setABGH(value); });
    connect(ui_->spinBox_5, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setArc13R(value); });
    connect(ui_->spinBox_6, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setArc8R(value); });
    connect(ui_->spinBox_3, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setArc11R(value); });
    connect(ui_->spinBox_4, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setCF(value); });
    connect(ui_->spinBox_7, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setDE(value); });
    connect(ui_->spinBox_8, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ gasket_->setPB(value); });

    connect(ui_->spinBox_14, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ bLemniscat_->setFocus(value); });
    connect(ui_->checkBox_4, &QCheckBox::clicked, this, [=](bool value){ if(value) animationInterval_->start(); else animationInterval_->stop(); });
    connect(bLemniscat_, &BernoulliLemniscate::sigCurvatureRadiusChanged, this, [=](double curvRadius){ ui_->label_22->setText(QString("%1 (deg)").arg((curvRadius*180.)/M_PI)); });
    connect(bLemniscat_, &BernoulliLemniscate::sigFocusChanged, this, [=](double focus){
        ui_->spinBox_14->setValue(static_cast<int>(focus));
        ui_->label_29->setText(QString("%1 (mm)").arg(bLemniscat_->getArea()));
        ui_->label_30->setText(QString("%1 (mm)").arg(bLemniscat_->getArea()/2.));
        ui_->label_31->setText(QString("%1 (mm)").arg(bLemniscat_->getLength()));
    });

    connect(ui_->checkBox_5, &QCheckBox::clicked, this, [=](bool value){ plane_->setTrianglesVisible(value); });
    connect(ui_->checkBox_6, &QCheckBox::clicked, this, [=](bool value){ plane_->animateTo(ui_->lineEdit->text(), value); });

    // Transformation buttons
    connect(ui_->spinBox_2, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ transformation_->setDeltaHeight(value); redraw(); });
    connect(ui_->spinBox_10, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ transformation_->setDeltaWidth(value); redraw();  });
    connect(ui_->spinBox_9, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ transformation_->setRotateAncle(value); redraw();  });
    connect(ui_->checkBox_2, &QCheckBox::clicked, [=](bool value){ transformation_->setProectiveEnabled(value); redraw();  });
    connect(ui_->checkBox_3, &QCheckBox::clicked, [=](bool value){ transformation_->setAffineEnabled(value); redraw();  });
    connect(ui_->spinBox_11, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ transformation_->setAffineSystemWeight(value, 0); redraw(); });
    connect(ui_->spinBox_12, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ transformation_->setAffineSystemWeight(value, 1); redraw(); });
    connect(ui_->spinBox_13, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){ transformation_->setAffineSystemWeight(value, 2); redraw(); });
    connect(ui_->tabWidget, &QTabWidget::tabBarClicked, this, [=](int index){
        if (index == 0) {
            bLemniscat_->hide();
            plane_->hide();
            dragon_->hide();
            gasket_->show();
        } else if(index == 1){
            gasket_->hide();
            plane_->hide();
            dragon_->hide();
            bLemniscat_->show();
        } else if(index == 2){
            gasket_->hide();
            bLemniscat_->hide();
            dragon_->hide();
            plane_->show();
        } if(index == 3){
            gasket_->hide();
            bLemniscat_->hide();
            plane_->hide();
            dragon_->show();
        }
    });


    {
        // setting up rotatePoint
        MovablePoint *rotatePoint = new MovablePoint(10, Qt::blue, "", chart_);

        QPointF mappedPos = rotatePoint->mapFromItem(gasket_, gasket_->pos());
        QPointF delta = mappedPos - gasket_->pos();
        rotatePoint->setPos(mappedPos);

        transformation_->setRotatePoint(gasket_->pos());
        connect(rotatePoint, &MovablePoint::positionChanged, this, [=](const QPointF &value){
            ui_->checkBox_2->isChecked()||ui_->checkBox_3->isChecked()
                    ? transformation_->setRotatePoint(value)
                    : transformation_->setRotatePoint(value - delta);
            redraw();
        });
    }


    scene_ = ui_->chartView->scene();
    scene_->installEventFilter(this);
    scene_->setBackgroundBrush(QBrush(Qt::white, Qt::SolidPattern));
    scene_->addItem(gasket_);   gasket_->hide();
    scene_->addItem(bLemniscat_); bLemniscat_->hide();
    scene_->addItem(plane_); plane_->hide();
    scene_->addItem(dragon_);

    {
        // setting up affinePoints
        QVector<MovablePoint::Ptr> affinePoints(3);
        //QVector<MovablePoint::Ptr> realPoints(3);
        QVector<QPointF> deltas(3);

        for (int i = 0; i < affinePoints.size(); ++i) {
            /*
                realPoints[i] = new MovablePoint(15, Qt::yellow, {9+49}, chart_);
                realPoints[i]->setFlag(QGraphicsItem::ItemIsMovable, false);
                realPoints[i]->setAcceptedMouseButtons(Qt::MouseButton::NoButton);
            */

            affinePoints[i] = new MovablePoint(6, Qt::green, {i+49});
            auto newPlace = i==0 ? gasket_->boundingRect().bottomLeft()
                                 : i==1 ? chart_->boundingRect().topLeft()
                                        : gasket_->boundingRect().topRight();
            const QPointF mappedPoss = affinePoints[i]->mapFromItem(gasket_, newPlace);
            deltas[i] = mappedPoss - newPlace;

            connect(affinePoints[i], &MovablePoint::positionChanged, this, [=](const QPointF &value){
                transformation_->setAffineSystemPoint(value - deltas[i], i);
                redraw();

                /*
                  auto realPlace = i==0 ? chart_->boundingRect().bottomLeft()
                                      : i==1 ? chart_->boundingRect().topLeft()
                                             : chart_->boundingRect().topRight();
                  realPoints[i]->setPos(realPlace);

                  // show yello proection of green points
                  if(ui_->checkBox_2->isChecked()) realPoints[i]->show();
                  else realPoints[i]->hide();
                */
            });

            affinePoints[i]->setPos(mappedPoss);
            scene_->addItem(affinePoints[i]);
        }
    }

    setAnimation();
//     next doesn'tmP need, because if we provide parent for MovablePoint object (chart_), it automaticaly adds to scene_
//     with chart_
//    scene_->addItem(rotatePoint);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneMousePress
            || event->type() == QEvent::GraphicsSceneMouseDoubleClick) {
        ui_->label_18->setText("x: " + QString::number(bLemniscat_->getTangentedPoint().x()));
        ui_->label_19->setText("y: " + QString::number(bLemniscat_->getTangentedPoint().y()));
    }

    return QObject::eventFilter(obj, event);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
}

void MainWindow::redraw()
{
    gasket_->redraw();
    bLemniscat_->redraw();
    plane_->redraw();
}

void MainWindow::setAnimation()
{
    const int frameCount = 50;

    animationInterval_ = new QTimer(this);

    connect(animationInterval_, &QTimer::timeout, this, [&]{
        QTimeLine *timeLine = new QTimeLine(QRandomGenerator::global()->bounded(1000, 2500), this);
        timeLine->setFrameRange(0, frameCount);

        double randFocus = QRandomGenerator::global()->bounded(13, 80);
        double oldFocus = bLemniscat_->getFocus();
        double animationStep = (randFocus - oldFocus)/frameCount;

        connect(timeLine, &QTimeLine::frameChanged, this, [=]{
            double newFocus = bLemniscat_->getFocus() + animationStep;
            bLemniscat_->setFocus(newFocus);
        });

        timeLine->start();
    });

    animationInterval_->start(2000);
}

MainWindow::~MainWindow()
{
    delete ui_;
    delete gasket_;
    chart_->deleteLater();
    delete transformation_;
}
