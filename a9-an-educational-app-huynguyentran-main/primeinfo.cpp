// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#include "primeinfo.h"
#include "ui_primeinfo.h"

PrimeInfo::PrimeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrimeInfo)
{
    ui->setupUi(this);
}

// window destructor
PrimeInfo::~PrimeInfo()
{
    delete ui;
}
