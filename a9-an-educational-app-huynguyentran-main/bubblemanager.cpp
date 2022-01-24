// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#include "bubblemanager.h"
#include <random>
#include <algorithm>

/*
 * The constructor to create Bubble maanger. A class that manages all the the bubble
 * instances in the game.
 */
BubbleManager::BubbleManager(int screenW, int screenH, int _timeBetweenFrames)
{
    score= 0;
    width = screenW;
    height = screenH+50;
    //Initialize how much time have passed in a frame.
    timeBetweenFrames = _timeBetweenFrames;
    //Initialize how much time have passed since the bubble last spawn.
    timePassedSinceLastSpawn = timeBetweenSpawn;
    particleList.clear();
    //Initailize non prime numbers.
    nonPrimes[4]  = true;
    nonPrimes[6]  = true;
    nonPrimes[8]  = true;
    nonPrimes[9]  = true;
    nonPrimes[10] = true;
    speedIncrease();
}

/*
 * Increases the speed of the game as time goes on.
 */
void BubbleManager::speedIncrease(){
    particleVelocity+= 15;
    QTimer::singleShot(3000,this,&BubbleManager::speedIncrease);
}

/*
 * Destructor of the bubble manager.
 */
BubbleManager::~BubbleManager()
{
    for(Bubble* particle : particleList)
        delete particle;
    particleList.clear();
}

/*
 * Changes the number of bubbles on the screen at any given time.
 */
void BubbleManager::changeNumberOfBubblesOnScreen(int i){
    maxParticles = i;
    particleList.clear();
    particleVelocity = initialParticleVelocity;
    score=0;
}

/*
 * Creates new bubbles after factorizing a non-prime number.
 */
void BubbleManager::createFactorBubbles(int posX, int posY, int factor1, int factor2)
{
    //Not splitting at the top
    if ( posY > 0){
        Bubble* newParticle = new Bubble(posX -50, posY+30, factor1);
        Bubble* newParticle2 = new Bubble(posX +50, posY+30, factor2);
        //Inserts new bubbles to the list.
        particleList.insert(particleList.begin(),newParticle);
        particleList.insert(particleList.begin(),newParticle2);
    }
}

/*
 * Removes a instance bubble from the screen.
 */
void BubbleManager::removeBubbles(std::vector<int> toRemove)
{

    //Remove the particles that are at the top of the defined area.
    for (int i = toRemove.size()-1; i>=0;i--){
        //Bubble to be remove.
        Bubble* particle = particleList[toRemove[i]];
        //Get the positions of the bubble.
        int x= particle->getPositionX();
        int y= particle->getPositionY();
        int num = particle->getValue();
        //Removes the bubble from the list.
        particleList.erase(particleList.begin()+toRemove[i]);
        //If the bubble has not touched the top of the screen.
        if (y >5){
            //If the bubble is 4, creates 2,2.
            if (num == 4){
                createFactorBubbles(x, y, 2, 2);
            }
            //If the bubble is 6, creates 3,2.
            else if (num == 6){
                createFactorBubbles(x, y, 2, 3);
            }
            //If the bubble is 8, creates 4,2.
            else if (num == 8){
                createFactorBubbles(x, y, 2, 4);
            }
            //If the bubble is 9, creates 3,3.
            else if (num == 9){
                createFactorBubbles(x, y, 3, 3);
            }
            //If the bubble is 10, creates 5,2.
            else if (num == 10){
                createFactorBubbles(x, y, 2, 5);
            }
            else
            {
                continue;
            }
        }
        delete particle;
    }

    //duplicate all the positions to be sent to the view.
    std::vector<Bubble> unlinkedPositions;

    for(Bubble* particlePtr : particleList)
    {
        Bubble copy = *particlePtr;
        unlinkedPositions.push_back(copy);
    }

    //Sends the bubble coordinates to the view.
    emit drawParticles(unlinkedPositions);
}

/*
 *Updates the positions of the bubbles each frame.
 */
void BubbleManager::updatePositions()
{
    //A list of bubbles have reached the top of the screen.
    std::vector<int> toRemoveParticle;

    //If there's space on the screen, and there are some time passed, we add new bubble
    if(timePassedSinceLastSpawn >= timeBetweenSpawn && (int) particleList.size() < maxParticles)
    {
        int i = rand()%4;
        float horizontalMultiplier = 0.3 + ((float) rand()) / (RAND_MAX/(0.7-0.3)); //float from 0 to 1
        if (i > 0){
            Bubble* newParticle = new Bubble(width * horizontalMultiplier, height, rand() % 9+2);
            particleList.push_back(newParticle);
        }
        else
        {
            Bubble* newBomb = new Bubble(width * horizontalMultiplier, height, -1);
            particleList.push_back(newBomb);
        }

        timePassedSinceLastSpawn = 0;
    }
    else timePassedSinceLastSpawn += timeBetweenFrames;

    //This generator and normal distribution will define the horizontal of the bubbles.
    //movement of every particle.
    std::default_random_engine generator;
    //The constructor arguments for the normal distribution are the mean and standard deviation.
    std::normal_distribution<float> distribution(0.0f,1.5f);

    //Update the positions of all the bubbles.
    for (unsigned int i = 0; i < particleList.size();i++){
        Bubble &particle = *particleList[i];
        int x = particle.getPositionX();
        int y = particle.getPositionY();
        //Apply the movement of the bubble to go up.
        y -= (particleVelocity * (timeBetweenFrames / 1000.0f));
        //Check if bubble has reached the top of the screen.
        if (y <= 0)
        {
            toRemoveParticle.push_back(i);
            int bubbleValue = particle.getValue();
            if (bubbleValue != -1){
                score -=1;
            }
            continue;
        }
        x += std::clamp(distribution(generator),-3.0f,3.0f);
        particle.changePosition(x, y);
    }

    //Remove all the bubbles in the to be removed list.
    removeBubbles(toRemoveParticle);
    //Don't let the score be less than 0.
    if (score < 0){
        score =0;
    }
    emit emitScore(score);
}

/*
 * User's mouse input interaction with the bubbles.
 */
void BubbleManager::removeBubbleWithMouse(const QPoint &point, Mouse mouse)
{
    int x = point.x();
    int y = point.y();
    //A to be removed list of the bubbles.
    std::vector<int> toRemove;
    //Iterates through all the bubbles.
    for (unsigned int i = 0; i < particleList.size();i++){
        Bubble &particle = *particleList[i];
        int particleX = particle.getPositionX();
        int particleY = particle.getPositionY();
        int value = particle.getValue();
        //If the mouse is on top of the bubbles hit box.
        if (particleX <= x && x <= particleX + 60 && particleY <= y && y <= particleY + 60)
        {
            //Add that bubbble to the to be removed list.
            toRemove.push_back(i);
            if (mouse == left){
                //If you left click primes.
                if (nonPrimes[value])
                {
                    score -=2;

                }
                //If you left click bomb.
                else if (value == -1)
                {
                    score -=3;

                }
                //If you left click non-primes.
                else{
                    score += 1;
                }
            }
            else if ( mouse == right){
                //If you right click prime
                if (nonPrimes[value])
                {
                    score +=1;
                }
                //If you right click bomb.
                else if (value == -1)
                {
                    score -=3;

                }
                //If you right click non-primes.
                else{

                    score -= 1;
                }
            }
        }
    }

    //Remove bubbles in the to be removed list and update on the view.
    removeBubbles(toRemove);
    if (score < 0){
        score =0;

    }
    emit emitScore(score);


}
