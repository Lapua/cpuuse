#ifndef TOP_H
#define TOP_H

#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int top(void)
{
    string str;
    double idle;
    system("top -b -n 2 -d 0.1 | grep Cpu > top.log");
    system("sed -e '1d' top.log > sedtop.log");

    ifstream file("sedtop.log");
    file >>str>>str>>str>>str>>str>>str>>str>>idle;
    file.close();

    if(str!="ni,"){
        return -1;
    }

    return 100-(int)idle;
}


#endif // TOP_H
