QT += core gui widgets charts

TARGET = QtGraphicsExample
TEMPLATE = app

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
    Graphics/transformation.cpp \
    Graphics/bernoullilemniscate.cpp \
    Graphics/graphicsitembase.cpp

HEADERS += \
	MainWindow/mainwindow.h \
    Graphics/gasket.h \
	Graphics/figure.h \
	Graphics/circle.h \
    Graphics/arc.h \
	Graphics/movablepoint.h \
    Graphics/transformation.h \
    Graphics/bernoullilemniscate.h \
    Graphics/graphicsitembase.h

FORMS += \
    MainWindow/mainwindow.ui

RESOURCES += \
    res/images.qrc

