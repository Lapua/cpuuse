#ifndef cpu_h
#define cpu_h

#include <QtWidgets>
#include <QAbstractSlider>
#include <QtCore/QThread>
#include <QTimer>
#include <QTimerEvent>
#include <QVBoxLayout>
#include <QLabel>
#include "core.h"

#include <sys/times.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class CpuUse : public QWidget
{
    Q_OBJECT

public :
    CpuUse(QWidget *parent = 0);

private :
    QProgressBar *topBar;
    QHBoxLayout *topLayout;
    QVBoxLayout *mainLayout;
    QLabel *rateLabel;
    QLabel *cpuLabel;
    Core *cpu;
    void timerEvent(QTimerEvent *event);
    void getCPUuse(void);
    int top(void);

    int loopTimer;
    int approachTimer;
    double topValue;

    int i;
    int oldUse[16];
    int oldTime;
    int cpuValue[16];
};

#endif
