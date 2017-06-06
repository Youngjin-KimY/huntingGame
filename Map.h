#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <iostream>
#include "Hunter.h"
#include "Grass.h"
#include "Gpit.h"
#include "Tiger.h"
#include "Rabbit.h"

class Map
{
public:
    Map();
    void print();
    void worldmapchange();
    char worldmap[20][20];
    Hunter hunter;
    Grass grass[100];
    Gpit fpit[100];
    Tiger mtiger[100];
    Rabbit mrabbit[100];
    int timestep;
    void setNofG(int ng);
    int getNofG();
    void setNofP(int np);
    int getNofP();
    void setNofPotion(int npp);
    int getNofPotion();
    int getNofT();
    void setNofT(int mNofT);
    void setTfall(int tf);
    void setTstarve(int ts);
    void setTbreed(int tb);
    int getTfall();
    int getTstarve();
    int getTbreed();
    void setNofR(int nnr);
    int getNofR();
    int getTcap();
    void setTcap(int cap);
    void setRfall(int rf);
    void setRstarve(int rs);
    void setRbreed(int rb);
    void setRcaptured(int rc);
    int getRfall();
    int getRstarve();
    int getRbreed();
    int getRcaptured();
private:
    int NofG,NofP,NofT,NofR,Nofpotion;
    int Tfall, Tstarve, Tbreed, Tcaptured;
    int Rfall, Rstarve, Rbreed, Rcaptured;
};
#endif /* Map_hpp */

