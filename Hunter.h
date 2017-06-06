#ifndef Hunter_hpp
#define Hunter_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

class Hunter
{
public:
    Hunter();
    Hunter(int X, int Y);
    void move(string m);
    void setX(int mX);
    void setY(int mY);
    int getX();
    int getY();
    void setCHP(int curhp);
    int getCHP();
    void setPoint(int Point);
    int getPoint();
    int getMaxHP();
    char getN();
    void setN(char hn);
    void inputmove();
    int getPotion();
    void setPotion(int water);
    void inputpotion();
    void startinputpotion();
    bool getStop();
    void setStop(bool ss);
private:
    int x,y; // position of hunter
    int currentHP, maxHP; // hp of hunter
    char name;
    int point;
    int potion;
    bool stop;
};


#endif /* Hunter_hpp */

