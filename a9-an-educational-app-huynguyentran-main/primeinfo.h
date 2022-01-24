// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#ifndef PRIMEINFO_H
#define PRIMEINFO_H

#include <QWidget>

namespace Ui {
class PrimeInfo;
}

/**
 * @brief The PrimeInfo class should be the first window the user comes across
 * in the tutorial. It contains basic introductory information about prime numbers for
 * the user to start learning about the topic.
 */
class PrimeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PrimeInfo(QWidget *parent = nullptr);
    ~PrimeInfo();

private:
    Ui::PrimeInfo *ui;
};

#endif // PRIMEINFO_H
