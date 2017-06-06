#include "Hunter.h"

Hunter::Hunter()
{ }
Hunter::Hunter(int X, int Y)
{
    x = X;
    y = Y;
    maxHP = 3;
    currentHP = 3;
    name = 'H';
    stop = true;
    potion = 0;
}
void Hunter::move(string m)
{
    bool a = true;
    while(a)
    {
        if(m=="a")
        {
            if(x-1>=0)
            {
                x--;
            }
            else{
                cout << "you can not move this direction"<<endl;
                cout << endl;
            }
            break;
        }
        else if(m=="d")
        {
            if(x+1<=19)
            {
                x++;
            }
            else{
                cout << "you can not move this direction"<<endl;
                cout << endl;
            }
            break;
        }
        else if(m=="w")
        {
            if(y-1>=0)
            {
                y--;
            }
            else{
                cout << "you can not move this direction"<<endl;
                cout << endl;
            }
            break;
        }
        else if(m=="s")
        {
            if(y+1<=19)
            {
                y++;
            }
            else{
                cout << "you can not move this direction"<<endl;
                cout << endl;
            }
            break;
        }
        else if(m=="wa")
        {
            if((x-1>=0) && (y-1>=0))
            {
                y--;
                x--;
            }
            else
            {
                cout << "you can not move this direction";
                cout << endl;
            }
            break;
        }
        else if(m=="wd")
        {
            if((y-1>=0) && (x+1<=19))
            {
                y--;
                x++;
            }
            else{
                cout << "you can not move this direction"<<endl;
                cout << endl;
            }
            break;
        }
        else if(m=="sa")
        {
            if((y+1<=19) && (x-1>=0))
            {
                y++;
                x--;
            }
            else{
                cout << "you can not move this direction"<<endl;
                cout << endl;
            }
            break;
        }
        else if(m=="sd")
        {
            if((y+1<=19) && (x+1<=19))
            {
                y++;
                x++;
            }
            else{
                cout << "you can not move this direction"<<endl;
                cout << endl;
            }
            break;
        }
        else{
            cout << "you input wrongly"<<endl;
            break;
        }
    }
}
void Hunter::setX(int mX)
{
    x = mX;
}
int Hunter::getX()
{
    return x;
}
void Hunter::setY(int mY)
{
    y = mY;
}
int Hunter::getY()
{
    return y;
}
void Hunter::setCHP(int curhp)
{
    if(curhp>=3)
        currentHP = 3;
    else
        currentHP = curhp;
}
int Hunter::getCHP()
{
    return currentHP;
}
void Hunter::setPoint(int Point)
{
    point = Point;
}
int Hunter::getPoint()
{
    return point;
}
int Hunter::getMaxHP()
{
    return maxHP;
}
char Hunter::getN()
{
    return name;
}
void Hunter::inputmove()
{
    bool a =true;
    string input;
    
    while(a)
    {
        cout << "Input the moving direction( Up: 'W', Down: 's', Left: 'a', Right: 'd'):";
        cin >> input;
        if((input=="w")||(input=="s")||(input=="a")||(input=="d")||(input=="wa")||(input=="wd")||(input=="sa")||(input=="sd"))
        {
            move(input);
            break;
        }
        else
        {
            continue;
        }
    }
}
void Hunter::inputpotion()
{
    string YorNo;
    bool a=true;
    while(a)
    {
        cout << "Are you going to use potion( Yes: 'y', No: 'n') :";
        cin >> YorNo;
        if(YorNo == "y")
        {
            setPotion(getPotion()-1);
            setCHP(3);
            break;
        }
        else if(YorNo =="n")
        {
            break;
        }
        else{
            continue;
        }
    }
}
int Hunter::getPotion()
{
    return potion;
}
void Hunter::setPotion(int water)
{
    potion = water;
}
bool Hunter::getStop()
{
    return stop;
}
void Hunter::setStop(bool ss)
{
    stop = ss;
}
void Hunter::startinputpotion()
{
    int sp;
    cout << "Enter initial number of potions : ";
    cin >> sp;
    setPotion(sp);
}
void Hunter::setN(char hn)
{
    name = hn;
}

