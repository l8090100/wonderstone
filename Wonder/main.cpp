#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString::fromUtf8("fuck you"));
    w.resize(1280,720);
    w.show();
    return a.exec();
}
