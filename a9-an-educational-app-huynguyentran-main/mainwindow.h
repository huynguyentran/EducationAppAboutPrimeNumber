// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sievewindow.h"
#include "gameui.h"
#include "primeinfo.h"
#include "othersievewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class contains the main menu of the tutorial, the four
 * buttons that show the rest of the tutorial, and a box2d animation.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sieveButton_clicked();
    void on_gameButton_clicked();
    void on_actionAbout_triggered();
    void on_pushButton_clicked();
    void on_sieveButton2_clicked();

private:
    Ui::MainWindow *ui;
    SieveWindow *firstAlgorithm;
    othersievewindow *secondAlgorithm;
    gameUI *game;
    PrimeInfo *info;
};

#endif // MAINWINDOW_H
