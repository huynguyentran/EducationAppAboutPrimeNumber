// Students: Huy Nguyen, Steven Tasmin, Jose Matute, Loc Vinh Phan, Anthony Dang, Ben Coverston
// CS 3505
// Group: Segmentation Fault
// Assignment: A9-An-Educational-App
// Project: Prime Numbers Tutorial

#ifndef BUBBLE_H
#define BUBBLE_H

/**
 * @brief The Bubble class represents a bubble object in the prime numbers game
 * of the tutorial. It contains the x and y position, as well as its value(number)
 * and a method to change its current position.
 */
class Bubble
{
public:
    Bubble(int, int, int);
    ~Bubble();
    Bubble(const Bubble& other);
    Bubble &operator=(const Bubble other);

    void changePosition(int, int);
    int getPositionX();
    int getPositionY();
    int getValue();

private:
    int x, y;
    int value;
};

#endif // BUBBLE_H
