QT += core gui widgets charts

TARGET = QtGraphicsExample
TEMPLATE = app

CONFIG += release

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = build/
OBJECTS_DIR = obj/
MOC_DIR     = moc/
UI_DIR      = ui/

SOURCES += \
        main.cpp \
	MainWindow/mainwindow.cpp \
    Graphics/gasket.cpp \
        Graphics/Basic/figure.cpp \
        Graphics/Basic/circle.cpp \
    Graphics/Basic/arc.cpp \
    Graphics/Basic/movablepoint.cpp \
    Graphics/bernoullilemniscate.cpp \
    Graphics/Basic/graphicsitembase.cpp \
    Graphics/plane.cpp \
    Graphics/dragonfractal.cpp \
    Graphics/hauseindimetricproection.cpp \
    Graphics/Basic/transformation2d.cpp \
    Graphics/Basic/transformation3d.cpp \
    Graphics/elliptichyperboloid.cpp

HEADERS += \
	MainWindow/mainwindow.h \
    Graphics/gasket.h \
        Graphics/Basic/figure.h \
        Graphics/Basic/circle.h \
    Graphics/Basic/arc.h \
        Graphics/Basic/movablepoint.h \
    Graphics/bernoullilemniscate.h \
    Graphics/Basic/graphicsitembase.h \
    Graphics/plane.h \
    Graphics/dragonfractal.h \
    Graphics/HauseInDimetricProection.h \
    Graphics/hauseindimetricproection.h \
    Graphics/Basic/transformation2d.h \
    Graphics/Basic/transformation3d.h \
    Graphics/elliptichyperboloid.h

FORMS += \
    MainWindow/mainwindow.ui

RESOURCES += \
    res/images.qrc

DISTFILES += \
    README.md

