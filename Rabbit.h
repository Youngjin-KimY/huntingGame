#ifndef Rabbit_hpp
#define Rabbit_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

class Rabbit
{
public:
    Rabbit();
    void setX(int X);
    void setY(int Y);
    int getX();
    int getY();
    void setCurrHP(int mhp);
    int getCurrHP();
    void setShape(char nn);
    char getShape();
    void setBreed(int br);
    int getBreed();
    
private:
    int x, y;
    int currentHP, breed;
    char shape;
};


#endif /* Rabbit_hpp */

