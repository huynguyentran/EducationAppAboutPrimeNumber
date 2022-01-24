// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include "sievesgame.h"
#include "QTimer"

namespace Ui {
class gameUI;
}

/**
 * @brief The gameUI class represents the window in which the prime game tutorial will be
 * displayed on. It keeps track of the score and time left of the user.
 */
class gameUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameUI(QWidget *parent = nullptr);
    ~gameUI();
    void timerStarted();

public slots:
    void updateScores(int i);

private slots:
    void on_startButton_clicked();
    void on_actionInstructions_triggered();

private:
    Ui::gameUI *ui;
    SievesGame game;
    int timerOfTheGame = 45;
    bool gameStarted = false;
    int highestScore = 0;
    int currentScore = 0;
};

#endif // GAMEUI_H
