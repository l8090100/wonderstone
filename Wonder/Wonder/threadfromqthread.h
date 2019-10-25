#ifndef THREADFROMQTHREAD_H
#define THREADFROMQTHREAD_H
#include <QThread>
#include <QMutex>

class ThreadFromQThread : public QThread
{
    Q_OBJECT
signals:
    void message(const QString& info);
    void progress(int present);
public:
    ThreadFromQThread(QObject* par);
    ~ThreadFromQThread();
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

#endif // THREADFROMQTHREAD_H
