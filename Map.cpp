#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Map.h"

using namespace std;



Map::Map()
{
    //basicsetting
    srand((unsigned int)time(NULL));
    setTfall(0);
    setTstarve(0);
    setTbreed(0);
    setTcap(0);
    setRfall(0);
    setRbreed(0);
    setRstarve(0);
    setRcaptured(0);
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            worldmap[i][j] = '-';
        }
    }
    bool whole = true;
    while(whole)
    {
        int NofRabbit;
        cout << "Enter initial number of Rabbits : ";
        cin >> NofRabbit;
        int NofTiger;
        cout << "Enter initial number of tigers : ";
        cin >> NofTiger;
        int NofP;
        cout << "Enter initial number of pits : ";
        cin >> NofP;
        int NofG;
        cout << "Enter initial number of grasses: ";
        cin >> NofG;
        hunter.startinputpotion();
        if(NofP+NofG+1 <=200)
        {
            //hunter
            hunter.setN('H');
            hunter.setPoint(0);
            hunter.setCHP(3);
            hunter.setX(rand()%20);
            hunter.setY(rand()%20);
            worldmap[hunter.getY()][hunter.getX()] = hunter.getN();
            hunter.setPoint(hunter.getPoint());
            hunter.setStop(true);
    
            //pit
    
            bool pitB = true;
    
            setNofP(NofP);
            for(int i=0; i<NofP;i++)
            {
                while(pitB)
                {
                    grass[i].setG('O');
                    grass[i].setY(rand()%20);
                    grass[i].setX(rand()%20);
                    if(worldmap[grass[i].getY()][grass[i].getX()]=='-')
                    {
                        worldmap[grass[i].getY()][grass[i].getX()]=grass[i].getG();
                        break;
                    }
                }
            
            }
    
            // grass
    
            bool graB = true;
    
            setNofG(NofG);
            for(int i=0; i<NofG;i++)
            {
                while(graB)
                {
                    fpit[i].setGreen('*');
                    fpit[i].setY(rand()%20);
                    fpit[i].setX(rand()%20);
                    if(worldmap[fpit[i].getY()][fpit[i].getX()] == '-')
                    {
                        worldmap[fpit[i].getY()][fpit[i].getX()] =fpit[i].getGreen();
                        break;
                    }
            
                }
            }
            //Tiger
            bool TigerB=true;
            setNofT(NofTiger);
            for(int i=0; i<NofTiger; i++)
            {
                while(TigerB)
                {
                    mtiger[i].setBreed(0);
                    mtiger[i].setN('T');
                    mtiger[i].setCurrentHP(100); // need to change HP as 2 ----------------------------------
                    mtiger[i].setY(rand()%20);
                    mtiger[i].setX(rand()%20);
                    if(worldmap[mtiger[i].getY()][mtiger[i].getX()] == '-')
                    {
                        worldmap[mtiger[i].getY()][mtiger[i].getX()] =mtiger[i].getN();
                        break;
                    }
                }
            }
            
            //Rabbit
            bool RabbitB = true;
            setNofR(NofRabbit);
            for(int i=0; i<NofRabbit; i++)
            {
                while(RabbitB)
                {
                    mrabbit[i].setBreed(0);
                    mrabbit[i].setShape('R');
                    mrabbit[i].setCurrHP(2);
                    mrabbit[i].setY(rand()%20);
                    mrabbit[i].setX(rand()%20);
                    if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()] == '-')
                    {
                        worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
                        break;
                    }
                }
            }
            //potion
         break; // while//
        }
        
        
    }
    //timestep
    timestep = 0;
}

void Map::print()
{
	system("clear");
    cout << endl;
    cout << "Time step: " << timestep << endl; //  need to change;
    cout << "<" << "Score:"<<hunter.getPoint()<<", " <<"HP:"<<hunter.getCHP()<<", "<<"Potions:"<<hunter.getPotion()<<">"<< endl;
    cout << endl;
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            cout << worldmap[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
    cout << "number of rabbits :          "<< getNofR() << " <born:"<<getRbreed()<<", "<<"starve:"<<getRstarve()<<", "<<"captured:"<<getRcaptured()<<", "<<"fall:"<<getRfall()<<">"<<endl;
    cout << "number of tigers :           "<< getNofT() << " <born:"<<getTbreed()<<", "<<"starve:"<<getTstarve()<<", "<<"captured:"<<getTcap()<<", "<<"fall:"<<getTfall()<<">"<<endl;
    cout << "number of grasses :          "<< getNofG() << endl;
    cout << "number of pits :             "<< getNofP() << endl;
    cout << endl;
}
void Map::worldmapchange()
{
    //basix setting
    srand((unsigned int)time(NULL));
    
    //part of hunter
    worldmap[hunter.getY()][hunter.getX()] = '-';
    hunter.inputmove();
    
    //when Hunter find each chacter
    if(worldmap[hunter.getY()][hunter.getX()] == '-')
    {
        worldmap[hunter.getY()][hunter.getX()] = hunter.getN();
        hunter.setCHP(hunter.getCHP()-1);
        hunter.inputpotion();
        if(hunter.getCHP() == 0)
        {
            hunter.setStop(false);
        }
    }
    else if(worldmap[hunter.getY()][hunter.getX()] == 'O')
    {
        hunter.setStop(false);
    }
    else if(worldmap[hunter.getY()][hunter.getX()] == '*')
    {
        //need to regenerate grass
        for(int i=0;i<100; i++)
        {
            if(fpit[i].getY() == hunter.getY() && fpit[i].getX() == hunter.getX())
            {
                bool a = true;
                while(a)
                {
                    int newX = rand()%20, newY = rand()%20;
                    if(worldmap[newY][newX] == '-')
                    {
                        fpit[i].setY(newY);
                        fpit[i].setX(newX);
                        worldmap[newY][newX] = fpit[i].getGreen();
                        break;
                    }
                }
            }
        }
        worldmap[hunter.getY()][hunter.getX()] = hunter.getN();
    }
    else if(worldmap[hunter.getY()][hunter.getX()] == 'T')
    {
        worldmap[hunter.getY()][hunter.getX()] = hunter.getN();
        for(int i=0;i<getNofT();i++)
        {
            if(mtiger[i].getX() == hunter.getX() && mtiger[i].getY() == hunter.getY())
            {
                for(int j=i;j<100;j++)
                {
                    mtiger[j] = mtiger[j+1];
                }
                setNofT(getNofT()-1);
            }
        }
        setTcap(getTcap()+1);
        hunter.setCHP(hunter.getCHP()-1);
        hunter.inputpotion();
        hunter.setPoint(hunter.getPoint()+2);
    }
    else if(worldmap[hunter.getY()][hunter.getX()] == 'R')
    {
        worldmap[hunter.getY()][hunter.getX()] = hunter.getN();
        for(int i=0;i<getNofR();i++)
        {
            if(mrabbit[i].getX() == hunter.getX() && mrabbit[i].getY() == hunter.getY())
            {
                for(int j=i;j<100;j++)
                {
                    mrabbit[j] = mrabbit[j+1];
                }
                setNofR(getNofR()-1);
            }
        }
        setRcaptured(getRcaptured()+1);
        hunter.setCHP(hunter.getCHP()-1);
        hunter.inputpotion();
        hunter.setPoint(hunter.getPoint()+1);
    }
    
    
    //part of Tiger ----------------------------------------------------------
    for(int i=0;i<getNofT();i++)
    {
        
        if(mtiger[i].getY()==0&&mtiger[i].getX()!=0){ //1---------------------------------------------
            if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && fpit[i].getX() == mtiger[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && fpit[i].getX() == mtiger[i].getX()-1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()+1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else{
            }
        }
        else if(mtiger[i].getY()==0&&mtiger[i].getX()==0) //2 ---------------------------------------------
        {
            if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'R') // 토끼 먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-'; // 원래 자리에는 공백표시
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'R') // 토끼 먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'O') // pit에 빠질때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'O') // pit에 빠질때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '*') // 풀먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && fpit[i].getX() == mtiger[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()+1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else{
                
            }
        }
        else if(mtiger[i].getY()!=0&&mtiger[i].getX()==0) //3---------------------------------------------
        {
            if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()+1][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()-1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()+1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && fpit[i].getX() == mtiger[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else{
                
            }

        }
        else if(mtiger[i].getY()==19&&mtiger[i].getX()==19)//4---------------------------------------------
        {
            if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'R') // 토끼 먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-'; // 원래 자리에는 공백표시
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'R') // 토끼 먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'O') // pit빠질때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'O') //pit빠질때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '*') // 풀먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && fpit[i].getX() == mtiger[i].getX()-1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()-1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else{
                
            }

        }
        else if(mtiger[i].getY()==19&&mtiger[i].getX()==0)//5---------------------------------------------
        {
            if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'R') // 토끼 먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-'; // 원래 자리에는 공백표시
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'R') // 토끼 먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'O') // fall in the pits
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'O') // fall in the pits
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '*') // 풀먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()-1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && fpit[i].getX() == mtiger[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else{
                

            }
        }
        else if(mtiger[i].getY()==0&&mtiger[i].getX()==19) //6---------------------------------------------
        {
            if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'R') // 토끼 먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-'; // 원래 자리에는 공백표시
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'R') // 토끼 먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && fpit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'O') // fall in the pit
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'O') //fall in the pit
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '*') // 풀먹을때
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && fpit[i].getX() == mtiger[i].getX()-1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()+1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else{
                
            }

        }
        else if(mtiger[i].getY()!=19&&mtiger[i].getX()==19)//7---------------------------------------------
        {
            if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(3);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()-1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()-1][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()+1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && mtiger[i].getX() == mtiger[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else{
                
            }
        }
        else if(mtiger[i].getY()==19&&mtiger[i].getX()!=19)//8---------------------------------------------
        {
            if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(3);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()-1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && fpit[i].getX() == mtiger[i].getX()-1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && fpit[i].getX() == mtiger[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else{
                
            }
        }
        else// 네방향---------------------------------------------
        {
            if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'R')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                for(int k=0;k<getNofR();k++)
                {
                    if(mrabbit[k].getX() == mtiger[i].getX() && mrabbit[k].getY() == mtiger[i].getY())
                    {
                        for(int j=k;j<100;j++)
                        {
                            mrabbit[j] = mrabbit[j+1];
                        }
                        setNofR(getNofR()-1);
                    }
                }
                setRcaptured(getRcaptured()+1);
                mtiger[i].setCurrentHP(2);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == 'O')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mtiger[j]=mtiger[j+1];
                }
                setNofT(getNofT()-1);
                setTfall(getTfall()+1);
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()-1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY()+1 && fpit[i].getX() == mtiger[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && fpit[i].getX() == mtiger[i].getX()-1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
                
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '*')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mtiger[i].getY() && fpit[i].getX() == mtiger[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setY(mtiger[i].getY()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()-1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
            {
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
                mtiger[i].setX(mtiger[i].getX()+1);
                worldmap[mtiger[i].getY()][mtiger[i].getX()] = mtiger[i].getN();
            }
            else{
                
            }
        }//
        
        mtiger[i].setBreed(mtiger[i].getBreed()+1);
        mtiger[i].setCurrentHP(mtiger[i].getCurrentHP()-1);
        if(mtiger[i].getCurrentHP() == 0)//if HP of tiger is 0, tiger should be dead;
        {
            worldmap[mtiger[i].getY()][mtiger[i].getX()] = '-';
            for(int j=i; j<100;j++)
            {
                mtiger[j]=mtiger[j+1];
            }
            setNofT(getNofT()-1);
            setTstarve(getTstarve()+1);
        }
        else if(mtiger[i].getBreed() == 4 && mtiger[i].getN()=='T')//tiger breeding-------------------------
        {
            if(mtiger[i].getY()==0&&mtiger[i].getX()!=0){//1---------------------------------------------
                if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()+1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()-1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()+1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }
            else if(mtiger[i].getY()==0&&mtiger[i].getX()==0)//2-------------------------------------
            {
                if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()+1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()+1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//2
            else if(mtiger[i].getY()!=0&&mtiger[i].getX()==0)//3------------------------------------
            {
                if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()-1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()+1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()+1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//3
            else if(mtiger[i].getY()==19&&mtiger[i].getX()==19)//4-------------------------------------
            {
                if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()-1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()-1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//4
            else if(mtiger[i].getY()==19&&mtiger[i].getX()==0)//5----------------------------------------
            {
                if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()-1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()+1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                
            }//5
            else if(mtiger[i].getY()==0&&mtiger[i].getX()==19) //6---------------------------------------
            {
                if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()-1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()+1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                
            }//6
            
            else if(mtiger[i].getY()!=19&&mtiger[i].getX()==19)//7-----------------------------
            {
                if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()-1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()+1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()-1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//7
            else if(mtiger[i].getY()==19&&mtiger[i].getX()!=19)//8------------------------------------
            {
                if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()-1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()+1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()-1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//8
            else// 네방향---------------------------------------------
            {
                if(worldmap[mtiger[i].getY()-1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()-1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()][mtiger[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()+1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()][mtiger[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY());
                            mtiger[j].setX(mtiger[i].getX()-1);
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mtiger[i].getY()+1][mtiger[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mtiger[j].getN() == '\0')
                        {
                            mtiger[j].setN('T');
                            mtiger[j].setCurrentHP(2);
                            mtiger[j].setY(mtiger[i].getY()+1);
                            mtiger[j].setX(mtiger[i].getX());
                            mtiger[j].setBreed(0);
                            worldmap[mtiger[j].getY()][mtiger[j].getX()] = mtiger[j].getN();
                            setTbreed(getTbreed()+1);
                            setNofT(getNofT()+1);
                            if(mtiger[i].getBreed() == 4)
                                mtiger[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//9
            
        }//tiger breeding
        
        
    }
    
    //Part of Rabbit
    for(int i=0;i<getNofR();i++) //-------------------------------------------------------------------Rabbit
    {
        if(mrabbit[i].getY()==0&&mrabbit[i].getX()!=0)//1---------------------------------------------
        {
            if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()+1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()-1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()-1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()+1 && fpit[i].getX() == mrabbit[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()+1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()-1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setY(mrabbit[i].getY()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else{
            }
        }
        else if(mrabbit[i].getY()==0&& mrabbit[i].getX()==0) //2 ---------------------------------------
        {
            if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '*') // 풀먹을때
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()+1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()+1 && fpit[i].getX() == mrabbit[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()+1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == 'O') // pit에 빠질때
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == 'O') // pit에 빠질때
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setY(mrabbit[i].getY()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else{
                
            }
        }
        else if(mrabbit[i].getY()!=0&&mrabbit[i].getX()==0) //3---------------------------------------------
        {
            if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()-1 && fpit[i].getX() == mrabbit[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()-1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()+1 && fpit[i].getX() == mrabbit[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()+1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setY(mrabbit[i].getY()-1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setY(mrabbit[i].getY()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else{
                
            }
        }
        else if(mrabbit[i].getY()==19&&mrabbit[i].getX()==19)//4---------------------------------------------
        {
            if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '*') // 풀먹을때
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()-1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()-1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '*') // 풀먹을때
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()-1 && fpit[i].getX() == mrabbit[i].getX()-1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()-1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == 'O') // pit빠질때
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == 'O') //pit빠질때
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()-1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else{
                
            }
            
        }
        else if(mrabbit[i].getY()==19&&mrabbit[i].getX()==0)//5---------------------------------------------
        {
            if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '*') // 풀먹을때
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()-1 && fpit[i].getX() == mrabbit[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()-1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()+1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == 'O') // fall in the pits
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == 'O') // fall in the pits
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setY(mrabbit[i].getY()-1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else{
                
                
            }
        }
        else if(mrabbit[i].getY()==0&&mrabbit[i].getX()==19) //6---------------------------------------------
        {
            if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '*') // 풀먹을때
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()-1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()-1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()+1 && fpit[i].getX() == mrabbit[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()+1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == 'O') // fall in the pit
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == 'O') //fall in the pit
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()-1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setY(mrabbit[i].getY()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else{
                
            }
            
        }
        else if(mrabbit[i].getY()!=19&&mrabbit[i].getX()==19)//7---------------------------------------------
        {
            if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()-1 && fpit[i].getX() == mrabbit[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()-1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()+1 && mrabbit[i].getX() == mrabbit[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
                
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setY(mrabbit[i].getY()-1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setY(mrabbit[i].getY()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else{
                
            }
        }
        else if(mrabbit[i].getY()==19&&mrabbit[i].getX()!=19)//8---------------------------------------------
        {
            if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()-1 && mrabbit[i].getX() == mrabbit[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()-1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()-1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()-1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
                
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()+1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setY(mrabbit[i].getY()-1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()-1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else{
                
            }
        }
        else// 네방향---------------------------------------------
        {
            if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()-1 && fpit[i].getX() == mrabbit[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()-1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY()+1 && fpit[i].getX() == mrabbit[i].getX())
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setY(mrabbit[i].getY()+1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()-1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()-1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
                
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '*')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int i=0;i<100; i++)
                {
                    if(fpit[i].getY() == mrabbit[i].getY() && fpit[i].getX() == mrabbit[i].getX()+1)
                    {
                        bool a = true;
                        while(a)
                        {
                            int newX = rand()%20, newY = rand()%20;
                            if(worldmap[newY][newX] == '-')
                            {
                                fpit[i].setY(newY);
                                fpit[i].setX(newX);
                                worldmap[newY][newX] = fpit[i].getGreen();
                                break;
                            }
                        }
                    }
                }
                mrabbit[i].setX(mrabbit[i].getX()+1);
                mrabbit[i].setCurrHP(2);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == 'O')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                for(int j=i; j<100;j++)
                {
                    mrabbit[j]=mrabbit[j+1];
                }
                setNofR(getNofR()-1);
                setRfall(getRfall()+1);
            }
            else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setY(mrabbit[i].getY()-1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setY(mrabbit[i].getY()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()-1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
            {
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
                mrabbit[i].setX(mrabbit[i].getX()+1);
                worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = mrabbit[i].getShape();
            }
            else{
                
            }
        }//
        
        mrabbit[i].setBreed(mrabbit[i].getBreed()+1);
        mrabbit[i].setCurrHP(mrabbit[i].getCurrHP()-1); // need to check when Rabbit eats grass.
        if(mrabbit[i].getCurrHP() == 0)//if HP of rabbit is 0, rabbit should be dead;
        {
            worldmap[mrabbit[i].getY()][mrabbit[i].getX()] = '-';
            for(int j=i; j<100;j++)
            {
                mrabbit[j]=mrabbit[j+1];
            }
            setNofR(getNofR()-1);
            setRstarve(getRstarve()+1);
        }
        else if(mrabbit[i].getBreed() == 3 && mrabbit[i].getShape()=='R')//rabbit breeding-----------------
        {
            if(mrabbit[i].getY()==0&&mrabbit[i].getX()!=0){//1---------------------------------------------
                if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()+1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()-1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()+1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }
            else if(mrabbit[i].getY()==0&&mrabbit[i].getX()==0)//2-------------------------------------
            {
                if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('T');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()+1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('T');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()+1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//2
            else if(mrabbit[i].getY()!=0&&mrabbit[i].getX()==0)//3------------------------------------
            {
                if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()-1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 4)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()+1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()+1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//3
            else if(mrabbit[i].getY()==19&&mrabbit[i].getX()==19)//4-------------------------------------
            {
                if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()-1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()-1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//4
            else if(mrabbit[i].getY()==19&&mrabbit[i].getX()==0)//5----------------------------------------
            {
                if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()-1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()+1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                
            }//5
            else if(mrabbit[i].getY()==0&&mrabbit[i].getX()==19) //6---------------------------------------
            {
                if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()-1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()+1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                
            }//6
            
            else if(mrabbit[i].getY()!=19&&mrabbit[i].getX()==19)//7-----------------------------
            {
                if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()-1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()+1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()-1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//7
            else if(mrabbit[i].getY()==19&&mrabbit[i].getX()!=19)//8------------------------------------
            {
                if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()-1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()+1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()-1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//8
            else// 네방향---------------------------------------------
            {
                if(worldmap[mrabbit[i].getY()-1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()-1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()+1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()+1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()][mrabbit[i].getX()-1] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY());
                            mrabbit[j].setX(mrabbit[i].getX()-1);
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
                else if(worldmap[mrabbit[i].getY()+1][mrabbit[i].getX()] == '-')
                {
                    int j=0;
                    while(true)
                    {
                        if(mrabbit[j].getShape() == '\0')
                        {
                            mrabbit[j].setShape('R');
                            mrabbit[j].setCurrHP(2);
                            mrabbit[j].setY(mrabbit[i].getY()+1);
                            mrabbit[j].setX(mrabbit[i].getX());
                            mrabbit[j].setBreed(0);
                            worldmap[mrabbit[j].getY()][mrabbit[j].getX()] = mrabbit[j].getShape();
                            setRbreed(getRbreed()+1);
                            setNofR(getNofR()+1);
                            if(mrabbit[i].getBreed() == 3)
                                mrabbit[i].setBreed(0);
                            break;
                        }
                        j++;
                    }
                }
            }//9
            
        }//rabbit breeing
        
        
    }

    timestep++;
}
void Map::setNofG(int ng)
{
    NofG = ng;
}
int Map::getNofG()
{
    return NofG;
}
void Map::setNofP(int np)
{
    NofP = np;
}
int Map::getNofP()
{
    return NofP;
}
void Map::setNofPotion(int npp)
{
    Nofpotion = npp;
}
int Map::getNofPotion()
{
    return Nofpotion;
}
int Map::getNofT()
{
    return NofT;
}
void Map::setNofT(int mNofT)
{
    NofT = mNofT;
}
int Map::getTfall()
{
    return Tfall;
}
int Map::getTstarve()
{
    return Tstarve;
}
int Map::getTbreed()
{
    return Tbreed;
}
void Map::setTfall(int tf)
{
    Tfall = tf;
}
void Map::setTstarve(int ts)
{
    Tstarve = ts;
}
void Map::setTbreed(int tb)
{
    Tbreed = tb;
}
void Map::setNofR(int nnr)
{
    NofR = nnr;
}
int Map::getNofR()
{
    return NofR;
}
int Map::getTcap()
{
    return Tcaptured;
}
void Map::setTcap(int cap)
{
    Tcaptured = cap;
}
void Map::setRfall(int rf)
{
    Rfall = rf;
}
void Map::setRstarve(int rs)
{
    Rstarve = rs;
}
void Map::setRbreed(int rb)
{
    Rbreed = rb;
}
void Map::setRcaptured(int rc)
{
    Rcaptured = rc;
}
int Map::getRfall()
{
    return Rfall;
}
int Map::getRstarve()
{
    return Rstarve;
}
int Map::getRbreed()
{
    return Rbreed;
}
int Map::getRcaptured()
{
    return Rcaptured;
}
