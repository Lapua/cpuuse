#include "cpuuse.h"
#include "getcpuuse.h"
#include <QThread>

CpuUse :: CpuUse(QWidget *parent) : QWidget(parent)
{
    cpuuse = new QDial;
    cpuuse -> setNotchesVisible(true);
    cpuuse -> setRange(0,100);

    button = new QPushButton("Button");
    number = new QLCDNumber;

    layout = new QVBoxLayout;
    layout -> addWidget(cpuuse);
    layout -> addWidget(number);
    layout -> addWidget(button);
    setLayout(layout);

    connect(cpuuse, SIGNAL(valueChanged(int)), number, SLOT(display(int)));
    loopTimer = startTimer(500);
    approachTimer = startTimer(5);
}

void CpuUse::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == loopTimer){
        cpuuseValue = getCPUuse();
    }
    if(event -> timerId() == approachTimer){
        if(cpuuseValue > cpuuse->value()){
            cpuuse -> setValue(cpuuse->value()+1);
            if(cpuuseValue < cpuuse->value()){
                    cpuuse -> setValue(cpuuseValue);
            }
        }else if(cpuuseValue < cpuuse->value()){
            cpuuse -> setValue(cpuuse->value()-1);
            if(cpuuseValue > cpuuse->value()){
                    cpuuse -> setValue(cpuuseValue);
            }
        }
    }
}
