#-------------------------------------------------
#
# Project created by QtCreator 2017-03-16T00:41:46
#
#-------------------------------------------------

QT += core gui
QT += sql
QT += widgets serialport
QT += network

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wonder
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    console.cpp \
    settingsdialog.cpp \
    systempage.cpp \
    settingtable.cpp \
    datapage.cpp \
    boardpage.cpp \
    showpage.cpp \
    database.cpp \
    motorblock.cpp \
    motorcue.cpp \
    cuedatamodel.cpp \
    customtablemodel.cpp \
    artnetdata.cpp \
    modesettingdata.cpp \
    cuedata.cpp \
    motorsettingdata.cpp \
    systemsettingdata.cpp \
    artnetmodel.cpp \
    systemsettingmodel.cpp \
    modesettingmodel.cpp \
    motorsettingmodel.cpp \
    motorcuemodel.cpp \
    threadfromqthread.cpp \
    runcuethread.cpp \
    robot.cpp \
    boardblock.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    console.h \
    settingsdialog.h \
    showpage.h \
    boardpage.h \
    datapage.h \
    systempage.h \
    database.h \
    artnetdata.h \
    motorblock.h \
    motorcue.h \
    cuedata.h \
    customtablemodel.h \
    modesettingdata.h \
    motorsettingdata.h \
    systemsettingdata.h \
    artnetmodel.h \
    systemsettingmodel.h \
    modesettingmodel.h \
    motorsettingmodel.h \
    motorcuemodel.h \
    threadfromqthread.h \
    runcuethread.h \
    robot.h \
    boardblock.h \
    mythread.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    systempage.ui \
    datapage.ui \
    showpage.ui \
    boardpage.ui

QMAKE_CXXFLAGS +=  -Wno-unused-parameter



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/osc-cpp-qt-master/osc-cpp-qt-master/bin/release/ -losc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/osc-cpp-qt-master/osc-cpp-qt-master/bin/debug/ -losc
else:unix: LIBS += -L$$PWD/osc-cpp-qt-master/osc-cpp-qt-master/bin/ -losc

INCLUDEPATH += $$PWD/osc-cpp-qt-master/osc-cpp-qt-master
DEPENDPATH += $$PWD/osc-cpp-qt-master/osc-cpp-qt-master
