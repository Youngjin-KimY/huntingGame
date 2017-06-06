#ifndef Grass_hpp
#define Grass_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;
class Grass
{
public:
    Grass();
    Grass(int X, int Y);
    Grass(char pit);
    char getG();
    void setG(char hole);
    void setX(int X);
    int getX();
    void setY(int Y);
    int getY();
private:
    int x,y; //this is postion
    char G;
};
#endif /* Grass_hpp */

