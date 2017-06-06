#ifndef TIger_hpp
#define TIger_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

class Tiger
{
public:
    Tiger();
    void setX(int X);
    int getX();
    void setY(int Y);
    int getY();
    void setCurrentHP(int currenthp);
    int getCurrentHP();
    void setN(char nn);
    char getN();
    void setBreed(int bbreed);
    int getBreed();
private:
    int x,y; //positon
    int currentHP;
    int breed;
    char name;
};
#endif /* TIger_hpp */

