#ifndef Gpit_hpp
#define Gpit_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>

class Gpit
{
public:
    Gpit();
    void setX(int X);
    int getX();
    void setY(int Y);
    int getY();
    void setGreen(char g);
    char getGreen();
private:
    int x,y;// this is postion of grass
    char green;
};

#endif /* Gpit_hpp */

