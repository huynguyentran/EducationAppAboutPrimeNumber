// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "welcomeanimation.h"
#include <QMessageBox>
#include "QGridLayout"
#include "QTextBrowser"

/*
 * Construct the main window.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->show();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete firstAlgorithm;
}


/*
 * Opens the window for Sieves of Eratosthenes.
 */
void MainWindow::on_sieveButton_clicked()
{
    firstAlgorithm = new SieveWindow(this);
    firstAlgorithm->show();
}


/*
 * Opens the window for the Prime game.
 */
void MainWindow::on_gameButton_clicked()
{
    game = new gameUI(this);
    game->show();
}

/*
 * A drop bar to instroduce the group.
 */
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Educational App: Prime Numbers Tutorial");
    msgBox.setInformativeText("Group Name: Segmentation Fault\n"
                              "Class: CS 3505\n"
                              "Tools: C++, QT and Box2D\n"
                              "Team members: \n"
                              "\t-Steven Tasmin\n\t-Jose Matute Garcia\n\t-Huy Nguyen\n\t-Loc Vinh Phan\n\t-Anthony Dang\n\t-Benjamin Coverston");
    msgBox.setTextFormat(Qt::PlainText);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

/*
 *  Opens the window for starting information.
 */
void MainWindow::on_pushButton_clicked()
{
    info = new PrimeInfo();
    info->show();
}

/*
 *  Opens the window for Sieves of Sundaram.
 */
void MainWindow::on_sieveButton2_clicked()
{
    secondAlgorithm = new othersievewindow();
    secondAlgorithm->show();
}

