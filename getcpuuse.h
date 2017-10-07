#ifndef getCPUuse_h
#define getCPUuse_h

#include <iostream>
#include <sys/times.h>
#include <fstream>
#include <string>
using namespace std;

int oldUse[16];
int oldTime;

void getCPUuse(int *cpu)
{
    struct tms wtms;
    int usr, nice, sys;
    string str;
    clock_t nowTime;
    nowTime = times(&wtms);

    ifstream ifs("/proc/stat");
    getline(ifs,str);
    for(int i=0; ; i++){
        ifs >> str >> usr >> nice >> sys;
        if(str=="intr"){
            break;
        }
        cpu[i] = ((double)(usr+nice+sys - oldUse[i]) / (nowTime-oldTime)) *100;
        oldUse[i] = usr + nice + sys;
    }
    ifs.close();

    oldTime = nowTime;
}

#endif
