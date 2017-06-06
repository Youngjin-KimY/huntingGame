#include "Tiger.h"

Tiger::Tiger()
{ }

void Tiger::setX(int X)
{
    x = X;
}
int Tiger::getX()
{
    return x;
}
void Tiger::setY(int Y)
{
    y = Y;
}
int Tiger::getY()
{
    return y;
}
void Tiger::setCurrentHP(int currenthp)
{
    currentHP = currenthp;
}
int Tiger::getCurrentHP()
{
    return currentHP;
}
void Tiger::setN(char nn)
{
    name = nn;
}
char Tiger::getN()
{
    return name;
}
void Tiger::setBreed(int bbreed)
{
    breed = bbreed;
}
int Tiger::getBreed()
{
    return breed;
}

