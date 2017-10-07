#include "cpuuse.h"
#include <QThread>
//#include "top.h"
//#include "getcpuuse.h"

CpuUse :: CpuUse(QWidget *parent) : QWidget(parent)
{
    this -> setWindowTitle("CPU use rate");

    rateLabel = new QLabel("%");
    cpuLabel = new QLabel("CPU");
    topBar = new QProgressBar;

    string str;
    ifstream file("/proc/stat");
    for(i=-1; str!="intr"; ++i){
        getline(file,str);
        file >> str;
    }
    file.close();

    topLayout = new QHBoxLayout;
    topLayout -> addWidget(cpuLabel);
    topLayout -> addWidget(topBar);
    topLayout -> addWidget(rateLabel);

    cpu = new Core[16];

    mainLayout = new QVBoxLayout;
    mainLayout -> addLayout(topLayout);
    for(int j=0; j<i; j++){
        mainLayout -> addWidget(&cpu[j]);
    }
    setLayout(mainLayout);

    loopTimer = startTimer(1000);
    approachTimer = startTimer(10);
}

void CpuUse :: timerEvent(QTimerEvent *event)
{
    if(event->timerId() == loopTimer){
        int judge = this->top();
        if(judge != -1){
            topValue = judge;
        }

        this->getCPUuse();
        for(int j=0; j<=i; j++){
            cpu[j].bar->setValue(cpuValue[j]);
        }
    }
    if(event -> timerId() == approachTimer){
        if(topValue > topBar->value()){
            topBar -> setValue(topBar->value()+1);
            if(topValue < topBar->value()){
                topBar -> setValue(topValue);
            }
        }else if(topValue < topBar->value()){
            topBar -> setValue(topBar->value()-1);
            if(topValue > topBar->value()){
                topBar -> setValue(topValue);
            }
        }

        for(int j=0; j<i; j++){
            if(cpuValue[j] > cpu[j].bar->value()){
                cpu[j].bar -> setValue(cpu[j].bar->value()+1);
                if(cpuValue[j] < cpu[j].bar->value()){
                    cpu[j].bar -> setValue(cpuValue[j]);
                }
            }else if(cpuValue[j] < cpu[j].bar->value()){
                cpu[j].bar -> setValue(cpu[j].bar->value()-1);
                if(cpuValue[j] > cpu[j].bar->value()){
                    cpu[j].bar -> setValue(cpuValue[j]);
                }
            }
        }
    }
}

void CpuUse :: getCPUuse(void)
{
    struct tms wtms;
    int usr, nice, sys;
    string str;
    clock_t nowTime;
    nowTime = times(&wtms);

    ifstream ifs("/proc/stat");
    for(int i=0; ; i++){
        getline(ifs,str);
        ifs >> str >> usr >> nice >> sys;
        if(str=="intr"){
            break;
        }
        this->cpuValue[i] = ((double)(usr+nice+sys - oldUse[i]) / (nowTime-oldTime)) *100;
        this->oldUse[i] = usr + nice + sys;
    }
    ifs.close();

    oldTime = nowTime;
}

int CpuUse :: top(void)
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
