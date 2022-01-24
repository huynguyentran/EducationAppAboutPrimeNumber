// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#ifndef SIEVEWINDOW_H
#define SIEVEWINDOW_H

#include <QMainWindow>
#include "QLabel"
#include <QTimer>
using std::vector;

namespace Ui {
class SieveWindow;
}

/**
 * @brief The SieveWindow class represents the window in which the information of
 * the Sieve of Eratosthenes will be displayed on. It contains the main information, an
 * image of the pseudocode and an animation of the algorithm.
 *
 */
class SieveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SieveWindow(QWidget *parent = nullptr);
    ~SieveWindow();


private slots:
    void on_visualisedButton_clicked();
    void changeBg(int num);
    void resetAnim(int size);

private:
    Ui::SieveWindow *ui;
    vector<QLabel*> labels;
};

#endif // SIEVEWINDOW_H
