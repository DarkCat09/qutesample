#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "QThread"
#include "QProgressBar"

class MyThread : public QThread
{
    Q_OBJECT

public:
    explicit MyThread(QObject *parent);
    void run();

signals:
    void progressChanged(int progress);
};

#endif // MYTHREAD_H
