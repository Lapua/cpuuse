#ifndef CORE_H
#define CORE_H

#include <QLabel>
#include <QProgressBar>
#include <QString>
#include <QHBoxLayout>
#include <QWidget>

class Core : public QWidget
{
public:
    Core(QWidget *parent = 0);
    QProgressBar *bar;

private:
    QString str;
    QLabel *cpuLabel;
    QLabel *rateLabel;
    QHBoxLayout *layout;
};

#endif // CORE_H
