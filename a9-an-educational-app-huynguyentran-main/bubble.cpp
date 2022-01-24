// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#include "bubble.h"
#include <iostream>

/*
 * Bubble constructor: construct a bubble object.
 */
Bubble::Bubble(int posX, int posY, int val)
{
    x = posX;
    y = posY;
    value = val;
}

/*
 * Deconstructor for the bubble object.
 */
Bubble::~Bubble()
{

}

/*
 * Copy constructor for bubble object.
 */
Bubble::Bubble(const Bubble& other)
{
    x = other.x;
    y = other.y;
    value = other.value;
}

/*
 * Assign bubble.
 */
Bubble& Bubble::operator=(Bubble other)
{
    std::swap(x, other.x);
    std::swap(y, other.y);
    std::swap(value, other.value);
    return *this;
}

/**
 * @brief Bubble::changePosition change the coordinates of the bubble to the new ones
 * in the parameters
 * @param newX
 * @param newY
 */
void Bubble::changePosition(int newX, int newY)
{
    x = newX;
    y = newY;
}

/*
 * Returns the x coordinate of the bubble.
 */
int Bubble::getPositionX()
{
    return x;
}

/*
 * Returns the y coordinate of the bubble.
 */
int Bubble::getPositionY()
{
    return y;
}

/*
 * Returns the value that the bubble represents.
 */
int Bubble::getValue()
{
    return value;
}
