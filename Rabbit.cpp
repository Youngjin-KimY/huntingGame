#include "Rabbit.h"

Rabbit::Rabbit()
{
    
}
void Rabbit::setX(int X)
{
    x = X;
}
void Rabbit::setY(int Y)
{
    y = Y;
}
int Rabbit::getX()
{
    return x;
}
int Rabbit::getY()
{
    return y;
}
void Rabbit::setCurrHP(int mhp)
{
    currentHP = mhp;
}
int Rabbit::getCurrHP()
{
    return currentHP;
}
void Rabbit::setShape(char nn)
{
    shape = nn;
}
char Rabbit::getShape()
{
    return shape;
}
void Rabbit::setBreed(int br)
{
    breed = br;
}
int Rabbit::getBreed()
{
    return breed;
}
