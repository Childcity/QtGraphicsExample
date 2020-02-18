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
	Graphics/figure.cpp \
	Graphics/circle.cpp \
    Graphics/arc.cpp \
    Graphics/movablepoint.cpp \
    Graphics/bernoullilemniscate.cpp \
    Graphics/graphicsitembase.cpp \
    Graphics/plane.cpp \
    Graphics/dragonfractal.cpp \
    Graphics/hauseindimetricproection.cpp \
    Graphics/transformation2d.cpp

HEADERS += \
	MainWindow/mainwindow.h \
    Graphics/gasket.h \
	Graphics/figure.h \
	Graphics/circle.h \
    Graphics/arc.h \
	Graphics/movablepoint.h \
    Graphics/bernoullilemniscate.h \
    Graphics/graphicsitembase.h \
    Graphics/plane.h \
    Graphics/dragonfractal.h \
    Graphics/HauseInDimetricProection.h \
    Graphics/hauseindimetricproection.h \
    Graphics/transformation2d.h

FORMS += \
    MainWindow/mainwindow.ui

RESOURCES += \
    res/images.qrc

