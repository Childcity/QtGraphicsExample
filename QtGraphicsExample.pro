QT += core gui widgets charts

TARGET = QtGraphicsExample
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = build/
OBJECTS_DIR = obj/
MOC_DIR     = moc/
UI_DIR      = ui/

INCLUDEPATH += MainWindow

SOURCES += \
        main.cpp \
    MainWindow/mainwindow.cpp \
    MainWindow/gasket.cpp

HEADERS += \
    MainWindow/mainwindow.h \
    MainWindow/gasket.h

FORMS += \
    MainWindow/mainwindow.ui

