// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#ifndef BUBBLEMANAGER_H
#define BUBBLEMANAGER_H

#include <vector>
#include <tuple>
#include <mutex>
#include <QPoint>
#include "bubble.h"
#include <QTimer>

/**
 * @brief The BubbleManager class manages all the bubbles in the screen of te prime numbers
 * game of the tutorial. It sets the boundaries and actions of the game, the semantics of the game,
 * as well as methods that control the spawn, speed and score value of the bubbles.
 */
class BubbleManager : public QObject
{
    Q_OBJECT

public:
    BubbleManager(int width, int height, int _timeBetweenFrames);
    ~BubbleManager();
     enum Mouse{left,right};
     void changeNumberOfBubblesOnScreen(int i);

private:
    int width;
    int height;
    int maxParticles = 0;
    int timeBetweenSpawn = 800;
    int timeBetweenFrames;
    int timePassedSinceLastSpawn;
    float particleVelocity = 100.0f;
    float initialParticleVelocity = particleVelocity;
    int score;
    std::vector<Bubble*> particleList;
    std::map<int, bool> nonPrimes;
    void removeBubbles(std::vector<int> toRemove);
    void createFactorBubbles(int, int, int, int);
    void speedIncrease();

signals:
    void drawParticles(std::vector<Bubble> list);
    void emitScore(int i);

public slots:
    void updatePositions();
    void removeBubbleWithMouse(const QPoint &point,Mouse mouse);
};

#endif // BUBBLEMANAGER_H
