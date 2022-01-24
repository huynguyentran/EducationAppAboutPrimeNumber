// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#include "sievewindow.h"
#include "ui_sievewindow.h"

SieveWindow::SieveWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SieveWindow)
{
    ui->setupUi(this);
    // creates animation grid
    for(int i=0; i<10; ++i){
        for(int j=0; j<10; ++j){
            QLabel* num = new QLabel(this);
            num->setText(QString::number((i*10)+(j+1)));
            num->setStyleSheet("border: 2px solid black;");
            num->setAlignment(Qt::AlignCenter);
            labels.push_back(num);
            ui->gridLayout->addWidget(num, i+1, j+1);
        }
    }
}

// destructor
SieveWindow::~SieveWindow()
{
    delete ui;
}

// starts the animation in the grid
void SieveWindow::on_visualisedButton_clicked()
{
    ui->infoLabel->setAlignment(Qt::AlignHCenter);
    ui->visualisedButton->setDisabled(true);
    int n = 100;
    resetAnim(n);
    bool prime[n+1];
    memset(prime, true, sizeof(prime));
    int time = 2000;

    QTimer::singleShot(500, this, [=]{
        labels.at(0)->setStyleSheet(styleSheet().append(QString("background-color: green; border: 2px solid black;")));
        ui->infoLabel->setText("Enumerate the multiples of 1");
    });
    QTimer::singleShot(1000, this, [=]{
        labels.at(0)->setStyleSheet(styleSheet().append(QString("background-color: red; border: 2px solid black;")) );
    });

    for (int p = 2; p <= n; p++)
    {
        if (prime[p] == true)
        {
            if (p*p > n) {
                QTimer::singleShot(time, this, [=]{
                    labels.at(p-1)->setStyleSheet(styleSheet().append(QString("background-color: green; border: 2px solid black;")));
                    ui->infoLabel->setText("Enumerate the multiples of " + QString::number(p));
                });
                QTimer::singleShot(time+500, this, [=]{
                    labels.at(p-1)->setStyleSheet( styleSheet().append(QString("border: 2px solid black;")) );
                });
                time += 1000;
            }
            else
            {
                QTimer::singleShot(time, this, [=]{
                    labels.at(p-1)->setStyleSheet(styleSheet().append(QString("background-color: green; border: 2px solid black;")));
                    ui->infoLabel->setText("Enumerate the multiples of " + QString::number(p));
                });

                time += 500;
                for (int i = p + p; i <= n; i += p){
                    prime[i] = false;
                    QTimer::singleShot(time, this, [=]{ changeBg(i); });
                    time += 100;
                }

                QTimer::singleShot(time, this, [=]{
                    labels.at(p-1)->setStyleSheet( styleSheet().append(QString("border: 2px solid black;")) );
                });
                time += 1000;
            }
        }
    }

    time += 1000;

    for (int p = 2; p <= n; p++)
    {
        if (prime[p] == true)
        {
            QTimer::singleShot(time, this, [=]{
                labels.at(p-1)->setStyleSheet(styleSheet().append(QString("background-color: green; border: 2px solid black;")));
            });
        }
    }
    time += 1000;

    QTimer::singleShot(time, this, [=]{
        ui->visualisedButton->setDisabled(false);
        ui->infoLabel->setText("Click 'start' to replay animation");
    });
}

/**
 * @brief SieveWindow::changeBg changes the background color og a box in the grid for
 * the animation
 * @param num
 */
void SieveWindow::changeBg(int num){
    labels.at(num-1)->setStyleSheet(styleSheet().append(QString("background-color: red; border: 2px solid black;")));
}

/**
 * @brief SieveWindow::resetAnim resets the background color of all the boxes in the grid to
 * trasparent
 * @param size
 */
void SieveWindow::resetAnim(int size){
    for (int p = 1; p <= size; p++){
        labels.at(p-1)->setStyleSheet(styleSheet().append(QString("background-color: transparent; border: 2px solid black;")));
        ui->infoLabel->setText("Waiting");
    }
}

