#include "core.h"

Core :: Core(QWidget *parent) : QWidget(parent)
{
    str = "CPU";
    //str = QString(number(coreNum));
    cpuLabel = new QLabel("CPU");
    bar = new QProgressBar;
    rateLabel = new QLabel("%");

    layout = new QHBoxLayout;
    layout -> addWidget(cpuLabel);
    layout -> addWidget(bar);
    layout -> addWidget(rateLabel);
    setLayout(layout);
}
