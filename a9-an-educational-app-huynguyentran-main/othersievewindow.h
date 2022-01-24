// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#ifndef OTHERSIEVEWINDOW_H
#define OTHERSIEVEWINDOW_H

#include <QMainWindow>
#include "QLabel"
#include <QTimer>

using std::vector;

namespace Ui {
class othersievewindow;
}

/**
 * @brief The othersievewindow class represents the window in which the information of
 * the Sieve of Sundaram will be displayed on. It contains the main information, an
 * image of the pseudocode and an animation of the algorithm.
 *
 */
class othersievewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit othersievewindow(QWidget *parent = nullptr);
    ~othersievewindow();

private slots:
    void on_startButton_clicked();

private:
    Ui::othersievewindow *ui;
    vector<QLabel*> labels;
    bool checkPrime(int n);
    void resetAnim(int size);
};

#endif // OTHERSIEVEWINDOW_H
