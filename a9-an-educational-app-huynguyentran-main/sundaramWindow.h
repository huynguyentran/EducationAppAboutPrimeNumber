#ifndef SUNDARAMWINDOW_H
#define SUNDARAMWINDOW_H

#include <QMainWindow>
#include "QLabel"
#include <QTimer>

using std::vector;

namespace Ui {
class SundaramWindow;
}

class SundaramWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SundaramWindow(QWidget *parent = nullptr);
    ~SundaramWindow();

private slots:
    void on_startButton_clicked();

private:
    Ui::SundaramWindow *ui;
    vector<QLabel*> labels;
    bool checkPrime(int n);
};

#endif // SUNDARAMWINDOW_H
