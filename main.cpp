#include <QApplication>
#include "cpuuse.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CpuUse *mainWindow = new CpuUse;
    mainWindow -> show();

    return app.exec();
}
