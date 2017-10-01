#ifndef getCPUuse_h
#define getCPUuse_h

#include <iostream>
#include <sys/times.h>
#include <fstream>
#include <string>
using namespace std;

int oldUse,oldTime;

double getCPUuse(void)
{
    struct tms wtms;
    int usr, nice, sys;
    int result;
    string str;
    clock_t nowTime = times(&wtms);
    int nowUse;

    ifstream ifs("/proc/stat");
    ifs >> str >> usr >> nice >> sys;
    nowUse = usr + nice + sys;
    ifs.close();

    result =  ((double)(nowUse-oldUse) / (nowTime-oldTime)) * 100;
    if(result > 100){
        result = 100;
    }

    oldTime = nowTime;
    oldUse = nowUse;

    return result;
}

#endif
