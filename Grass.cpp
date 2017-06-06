#include "Grass.h"

Grass::Grass()
{ }
Grass::Grass(int X, int Y)
{
    x=X;
    y=Y;
}
Grass::Grass(char pit)
{
    G=pit;
}
void Grass::setX(int X)
{
    x=X;
}
int Grass::getX()
{
    return x;
}
void Grass::setY(int Y)
{
    y=Y;
}
int Grass::getY()
{
    return y;
}
char Grass::getG()
{
    return G;
}
void Grass::setG(char hole)
{
    G = hole;
}
