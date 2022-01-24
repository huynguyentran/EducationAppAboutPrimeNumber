// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#include "othersievewindow.h"
#include "ui_othersievewindow.h"

//implementing rule of three
//the constructor of othersievewindow
othersievewindow::othersievewindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::othersievewindow)
{
    ui->setupUi(this);

    //initialised grid of 10x10
    //to produce grid of 100 numbers
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

//implement the rule of three
//destructor of othersievewindow
othersievewindow::~othersievewindow()
{
    delete ui;
}

//a slot function when start button is clicked
//basically
void othersievewindow::on_startButton_clicked()
{
    //intialised variables
    int n = 100;
    resetAnim(n);
    int k = (n-1)/2;
    int time = 0;
    QMutex mutex;
    bool marked[n];
    vector<int> primeList;
    memset(marked, false, sizeof(marked));

    //disable button when playing
    ui->infoLabel->setAlignment(Qt::AlignHCenter);
    ui->startButton->setDisabled(true);

    //marked all the number from 1 to 100
    //that satisfy equations:
    //1 <= i <= j for all i,j part of 100
    //i + j + 2ij <= n
    for (int i=1; i<=k; i++){
        for (int j=i; (i + j + 2*i*j) <= n; j++){
            mutex.lock();
            //marked true if the number satisfy the conditions
            marked[i + j + 2*i*j] = true;
            QTimer::singleShot(time+300*(i + j + 2*i*j-1), this, [=]{
                labels.at(i + j + 2*i*j-1)->setStyleSheet(styleSheet().append(QString("background-color: red; border: 2px solid black;")));
                ui->infoLabel->setText("Remove " + QString::number(i + j + 2*i*j) + " as it satisfied the equation i + j + 2*i*j ");
            });
            mutex.unlock();
        }
    }

    // Remaining Numbers that did not satisfy those
    // equations, the number would be doubled and
    // increment by one (2*i +1)
    for (int i=1; i<=n; i++){
        mutex.lock();
        //number that did not satisfy previous condition
        //would be marked false
        if (marked[i] == false){
            QTimer::singleShot(33000+300*i, this, [=]{
                labels.at(i-1)->setStyleSheet(styleSheet().append(QString("background-color: purple; border: 2px solid black;")));
                ui->infoLabel->setText("Add " + QString::number(2*i + 1) + " to the list of prime numbers as index " + QString::number(i) + " was not marked previously");
            });
            //for visualisation purposes
            if ( 2*i + 1 <= 100){
                primeList.push_back(2*i + 1);
            }
        }
        mutex.unlock();
    }

    QTimer::singleShot(64600, this, [=]{
        labels.at(1)->setStyleSheet(styleSheet().append(QString("background-color: green; border: 2px solid black;")));
        ui->infoLabel->setText("Mark " + QString::number(2) + " as it is a prime number");
    });

    int timeTracker = 0;
    for (int num : primeList){
        timeTracker =64000+300*num;
        QTimer::singleShot(timeTracker, this, [=]{
            labels.at(num-1)->setStyleSheet(styleSheet().append(QString("background-color: green; border: 2px solid black;")));
            ui->infoLabel->setText("Mark " + QString::number(num) + " as it is a prime number");
        });
    }

    QTimer::singleShot(timeTracker+500, this, [=]{
        ui->startButton->setDisabled(false);
        ui->infoLabel->setText("Click 'start' to replay animation");
    });

}

//reset the animation after the animation is done
//set all grid back to original colours and indicate
//animation with 'waiting'
void othersievewindow::resetAnim(int size){
    for (int p = 1; p <= size; p++){
        labels.at(p-1)->setStyleSheet(styleSheet().append(QString("background-color: transparent; border: 2px solid black;")));
        ui->infoLabel->setText("Waiting");
    }
}

//A helper method to check whether or not a number is prime
//return true if the number is prime otherwise false
bool othersievewindow::checkPrime(int n){
        bool isPrime;
        // 0 and 1 are not prime numbers
        if (n == 0 || n == 1)
            isPrime = false;
        else {
            for (int i = 2; i <= n / 2; ++i)
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
        }
        if (isPrime) return true;
        else return false;
}
