// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#include "gameui.h"
#include "ui_gameui.h"
#include <QMessageBox>

gameUI::gameUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameUI)
{
    ui->setupUi(this);
    ui->gameArea->setWidget(&game);
    connect(&game.bubbleManager,&BubbleManager::emitScore,this,&gameUI::updateScores);
    ui->timeLabel->setText("Time remaining: "+ QString::number(timerOfTheGame) + " seconds");
}

gameUI::~gameUI()
{
    delete ui;
}

/*
 *Updates the player score.
 */
void gameUI::updateScores(int i)
{
    currentScore = i;
    ui->scoreLabel->setText("Score: " + QString::number(currentScore));

}

/*
 * Display the time of the game and constantly update the time every second.
 */
void gameUI::timerStarted()
{
    timerOfTheGame--;
    ui->timeLabel->setText("Time remaining: "+ QString::number(timerOfTheGame) + " seconds");
    //If the timer is still larger than 0, keep updating it.
    if (timerOfTheGame > 0){
        QTimer::singleShot(1000,this,&gameUI::timerStarted);
    }
    //If the timer reach zero.
    else{
        //Ends the game.
        game.gameStartAndEnd(false);
        gameStarted=false;
        //Resets the time.
        timerOfTheGame =45;
        //Set the current score to be the highest score if it is higher than the highest score.
        if (currentScore>highestScore){
            highestScore = currentScore;
        }
        ui->highestScoreLabel->setText("Highest Score: " +  QString::number(highestScore));
        currentScore = 0;
    }


}

/*
 *Clicking the starting the game button.
 */
void gameUI::on_startButton_clicked()
{
    //If the game has not been started.
    if (gameStarted == false){
        //Starts the game and the timer.
        game.gameStartAndEnd(true);
        gameStarted=true;
        timerStarted();
    }
    //Else
    else if (gameStarted == true)
    {
        //Stops the game and the timer.
        game.gameStartAndEnd(false);
        gameStarted=false;
        timerOfTheGame=1;
    }
}

/*
 * Instructions about the game
 */
void gameUI::on_actionInstructions_triggered()
{
    //Sets a message box on top of the left side of the screen
    //about the instruction of the game.
    QMessageBox msgBox;
    msgBox.setText("Prime Numbers Game Instructions");
    msgBox.setInformativeText("This game is about testing your knowledge on the most basic prime numbers you should know.\n\n"
                              "The game consists of bubbles with numbers coming from the bottom to the top of the screen. "
                              "Each number is either a prime number or a non-prime number. For each of the following bubbles, "
                              "you should do the following:\n\n"
                              "\t- If the number is prime: LEFT CLICK (+1 points)\n"
                              "\t- If the number is factorizable(non-prime): RIGHT CLICK (+1 points)\n"
                              "\t  In addition: it will divide into two other bubbles that multiply to the factorizable \n"
                              "\t  number. You should then LEFT or RIGHT click the bubble depending on if they \n"
                              "\t  are prime or not. \n"
                              "\t- If you do a mistake, like RIGHT-clicking a prime number: (-1 points) \n"
                              "\t- If you let a bubble reach the top without clicking it correctly: (-1 points) \n"
                              "\t- If you touch a black bubble: (-3 points) \n\n"
                              "The goal of the game is that after a few attempts, you should have already memorized the most basic prime numbers. Good luck!");
    msgBox.setTextFormat(Qt::PlainText);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

