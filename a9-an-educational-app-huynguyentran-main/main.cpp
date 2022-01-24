// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //adding comments to test the version control on QT
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
