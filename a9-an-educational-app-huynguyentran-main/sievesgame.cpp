// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#include "sievesgame.h"

SievesGame::SievesGame(QWidget *parent) : QWidget(parent),  
    bubbleManager(size().width(), size().height(), 1000/30),
    bubbleUpdater(this)
{
    //Bubble Particles Setup
    QColor outlineColor(41,231,231,255);
    bubblePen.setWidth(2);
    bubblePen.setColor(outlineColor);

    QColor mainFillColor(41,231,231,150);
    bubbleBrush.setColor(mainFillColor);
    bubbleBrush.setStyle(Qt::SolidPattern);

    QColor highlightFillColor(255,255,255,175);
    smallerBubbleBrush.setColor(highlightFillColor);
    smallerBubbleBrush.setStyle(Qt::SolidPattern);

    connect(&bubbleUpdater, &QTimer::timeout, &bubbleManager, &BubbleManager::updatePositions);
    //Get ready to take particles to draw from the bubbleManager.
    connect(&bubbleManager, &BubbleManager::drawParticles, this, &SievesGame::updatePainter);
    connect(this, &SievesGame::bubbleToRemove, &bubbleManager, &BubbleManager::removeBubbleWithMouse);
    bubbleUpdater.start(1000/30);

}

SievesGame::~SievesGame(){

}

/**
 * @brief SievesGame::gameStartAndEnd Chanhes the amounts of bubbles in the screen. It
 * is 0 if the game has not started and 4 otherwise.
 * @param gameState
 */
void SievesGame::gameStartAndEnd(bool gameState){
    if (gameState)
        bubbleManager.changeNumberOfBubblesOnScreen(4);
    else
        bubbleManager.changeNumberOfBubblesOnScreen(0);

}

/**
 * @brief SievesGame::mousePressEvent detects if when the user clicked
 * the screen, if it was a right click or a left click.
 * @param event
 */
void SievesGame::mousePressEvent(QMouseEvent *event)
{
    if (usingMouse){
        if (event->button() == Qt::LeftButton)
            movingMouseLeft= true;
        if (event -> button() == Qt::RightButton)
            movingMouseRight = true;
    }
}

/**
 * @brief SievesGame::mouseMoveEvent detects is when the user was moving the mouse,
 * if they pressed a left or right click beforehand
 * @param event
 */
void SievesGame::mouseMoveEvent(QMouseEvent *event)
{
    if (usingMouse){
        if (event->button() == Qt::LeftButton)
            movingMouseLeft= true;
        if (event -> button() == Qt::RightButton)
            movingMouseRight = true;
    }
}

/**
 * @brief SievesGame::mouseReleaseEvent detects the kind of movement the
 * user was doing after the mouse press got released
 * @param event
 */
void SievesGame::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if(movingMouseLeft){
            mouseInGame(event->pos(), left);
            movingMouseLeft = false;
        }
    }

    if (event->button() == Qt::RightButton) {
        if(movingMouseRight){
            mouseInGame(event->pos(), right);
            movingMouseRight = false;
        }
    }
}

/**
 * @brief SievesGame::paintEvent takes care of painting the bubbles to the screen
 * @param event
 */
void SievesGame::paintEvent(QPaintEvent *event)
{
    QPainter bubblePainter(this);
    bubblePainter.setPen(bubblePen);
    for (unsigned int i = 0; i < particleToDraw.size();i++){
        Bubble& coor = particleToDraw[i];
        int x = coor.getPositionX();
        int y = coor.getPositionY();
        int value = coor.getValue();
        QRect bubble(x, y, 60,60);
        QRect smallerBubble(x+13, y+13, 10,10);

        // black bubbles
        if (value == -1)
        {
            bubblePainter.setBrush(Qt::black);
            bubblePainter.drawEllipse(bubble);
            bubblePainter.setBrush(smallerBubbleBrush);
            bubblePainter.drawEllipse(smallerBubble);
        }
        // blue bubbles
        else
        {
            bubblePainter.setBrush(bubbleBrush);
            bubblePainter.drawEllipse(bubble);
            bubblePainter.setBrush(smallerBubbleBrush);
            QFont font = bubblePainter.font();
            font.setPixelSize(48);
            bubblePainter.setFont(font);
            if (value == 10) bubblePainter.drawText(x+4, y+45,QString::number(value));
            else bubblePainter.drawText(x+18, y+45,QString::number(value));
        }
    }
}

/**
 * @brief SievesGame::updatePainter updates the screen with the bubbles to draw
 * that are in the list that keeps track of the bubbles still on the screen
 * @param list
 */
void SievesGame::updatePainter(std::vector<Bubble> list){
    particleToDraw = list;
    update();
}

/**
 * @brief SievesGame::mouseInGame emits the bubble to remove signal
 * by sending the position in the screen and if the left or right
 * buttons were clicked
 * @param point
 * @param mouse
 */
void SievesGame::mouseInGame(const QPoint &point, Mouse mouse)
{
    if (mouse == left)
        emit bubbleToRemove(point, bubbleManager.left);
    else if (mouse == right)
        emit bubbleToRemove(point, bubbleManager.right);
}

