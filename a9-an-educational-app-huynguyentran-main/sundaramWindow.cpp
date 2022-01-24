#include "sundaramWindow.h"
#include "ui_sundaramWindow.h"

SundaramWindow::SundaramWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::othersievewindow)
{
    ui->setupUi(this);

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

SundaramWindow::~SundaramWindow()
{
    delete ui;
}

void SundaramWindow::on_startButton_clicked()
{
    int n = 100;
    int nNew = (n-1)/2;
    int time = 2000;
    QMutex mutex;

    bool marked[n];
    bool markPrime[n];
    vector<int> primeList;
    memset(marked, false, sizeof(marked));

    for (int i=1; i<=nNew; i++){
        for (int j=i; (i + j + 2*i*j) <= n; j++){
            mutex.lock();
            marked[i + j + 2*i*j] = true;
            qInfo() << "i + j + 2*i*j = " << i + j + 2*i*j;
            QTimer::singleShot(time+300*(i + j + 2*i*j-1), this, [=]{
                labels.at(i + j + 2*i*j-1)->setStyleSheet(styleSheet().append(QString("background-color: red; border: 2px solid black;")));
                ui->infoLabel->setText("Removes number " + QString::number(i + j + 2*i*j) + " as it satisfied the equation i + j + 2*i*j ");
            });
            mutex.unlock();
        }
    }

//    // Since 2 is a prime number
//    if (n > 2){
//        mutex.lock();
//        qInfo() << 2;
//        qInfo() << "spacer";
//        QTimer::singleShot(2950, this, [=]{
//            labels.at(1)->setStyleSheet(styleSheet().append(QString("background-color: green; border: 2px solid black;")));
//        });
//        mutex.unlock();
//    }

    // Print other primes. Remaining primes are of the form
    // 2*i + 1 such that marked[i] is false.
    for (int i=1; i<=n; i++){
        mutex.lock();
        if (marked[i] == false){
            qInfo() << checkPrime(i);
            qInfo() << "indicate purple on:" << i;
            QTimer::singleShot(33000+300*i, this, [=]{
                labels.at(i-1)->setStyleSheet(styleSheet().append(QString("background-color: purple; border: 2px solid black;")));
                ui->infoLabel->setText("add number " + QString::number(2*i + 1) + " to the list of prime number as index " + QString::number(i) + " did not marked previously");
            });
            if ( 2*i + 1 <= 100){
                primeList.push_back(2*i + 1);
            }

        }
        mutex.unlock();
    }

    QTimer::singleShot(64600, this, [=]{
        labels.at(1)->setStyleSheet(styleSheet().append(QString("background-color: green; border: 2px solid black;")));
        ui->infoLabel->setText("marked " + QString::number(2) + " as the number is a prime number");
    });

    for (int num : primeList){
        qInfo() << num;
        QTimer::singleShot(64000+300*num, this, [=]{
            labels.at(num-1)->setStyleSheet(styleSheet().append(QString("background-color: green; border: 2px solid black;")));
            ui->infoLabel->setText("marked " + QString::number(num) + " as the number is a prime number");
        });
    }

}

bool SundaramWindow::checkPrime(int n){
        bool isPrime;
        // 0 and 1 are not prime numbers
        if (n == 0 || n == 1) {
            isPrime = false;
        }
        else {
            for (int i = 2; i <= n / 2; ++i) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }
        }
        if (isPrime) {
           return true;
        }
        else {
            return false;
        }
}



