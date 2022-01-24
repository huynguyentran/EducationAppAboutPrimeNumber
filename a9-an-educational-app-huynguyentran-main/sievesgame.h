// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#ifndef SIEVESGAME_H
#define SIEVESGAME_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QMouseEvent>
#include "bubblemanager.h"
#include <QTimer>
#include "bubble.h"

/**
 * @brief The SievesGame class manages the prime numbers game that will be displayed
 * in the sievewindow class. It keeps track of mouse events for when the user clicks
 * bubbles and updates the screen with the new position of the bubbles.
 */
class SievesGame : public QWidget
{
        Q_OBJECT
public:
     explicit SievesGame(QWidget *parent = nullptr);
    ~SievesGame();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    BubbleManager bubbleManager;
    void gameStartAndEnd(bool gameState);

public slots:
    void updatePainter(std::vector<Bubble> list);
    void paintEvent(QPaintEvent *event) override;

private:
    bool usingMouse =true;
    bool movingMouseLeft = false;
    bool movingMouseRight = false;
    QImage image;
    QTimer bubbleUpdater;
    QPen bubblePen;
    QBrush bubbleBrush;
    QBrush smallerBubbleBrush;
    enum Mouse{left, right};
    std::vector<Bubble> particleToDraw;
    void mouseInGame(const QPoint &Point,Mouse mouse);

signals:
    void bubbleToRemove (const QPoint &Point, BubbleManager::Mouse mouse);
};

#endif // SIEVESGAME_H
