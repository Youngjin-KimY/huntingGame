#include <iostream>
using namespace std;
#include "Map.h"

int main()
{
    Map m;
    m.print();
    while(m.hunter.getStop())
    {
        m.worldmapchange();
        m.print();
    }
    return 0;
}
