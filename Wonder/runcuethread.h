#ifndef RUNCUETHREAD_H
#define RUNCUETHREAD_H
#include <QThread>
#include <QMutex>

class RunCueThread : public QThread
{
    Q_OBJECT
signals:
    void message(const QString& info);
    void progress(int present);
public:
    RunCueThread(QObject* par);
    ~RunCueThread();
    void setSomething();
    void getSomething();
    void setRunCount(int count);
    void run();
    void doSomething();
public slots:
    void stopImmediately();
private:
    int m_runCount;
    QMutex m_lock;
    bool m_isCanRun;
};

#endif // RUNCUETHREAD_H
