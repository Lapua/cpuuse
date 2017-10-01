#ifndef cpu_h
#define cpu_h

//#include <QtGui>
#include <QtWidgets>
#include <QDial>
#include <QAbstractSlider>
#include <QtCore/QThread>
#include <QPushButton>
#include <QTimer>	//QT += core
#include <QTimerEvent>
#include <QVBoxLayout>
#include <QLCDNumber>
//#include "getCPUuse.h"

class CpuUse : public QWidget
{
    Q_OBJECT

public :
    CpuUse(QWidget *parent = 0);

private :
    QWidget *window;
    QDial *cpuuse;
    QPushButton *button;
    QVBoxLayout *layout;
    QLCDNumber *number;

    void timerEvent(QTimerEvent *event);
    int loopTimer;
    int approachTimer;
    double cpuuseValue;
};

#endif
