#include "ThreadFromQThread.h"
#include <QDebug>
ThreadFromQThread::ThreadFromQThread(QObject* par) : QThread(par)
,m_runCount(20)
{

}

ThreadFromQThread::~ThreadFromQThread()
{
    qDebug() << "ThreadFromQThread::~ThreadFromQThread()";
}

void ThreadFromQThread::setSomething()
{
    msleep(500);
    QString str = QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId());
    emit message(str);
}

void ThreadFromQThread::getSomething()
{
    msleep(500);
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}

void ThreadFromQThread::setRunCount(int count)
{
    m_runCount = count;
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}

void ThreadFromQThread::run()
{
    int count = 0;
    m_isCanRun = true;//标记可以运行
    QString str = QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)QThread::currentThreadId());
    emit message(str);
    while(1)
    {
        sleep(1);
        ++count;
        emit progress(((float)count / m_runCount) * 100);
        emit message(QString("ThreadFromQThread::run times:%1").arg(count));
        doSomething();
        if(m_runCount == count)
        {
            break;
        }
        {
            QMutexLocker locker(&m_lock);
            if(!m_isCanRun)//在每次循环判断是否可以运行，如果不行就退出循环
            {
                return;
            }
        }
    }
}

void ThreadFromQThread::doSomething()
{
    msleep(100);
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}

void ThreadFromQThread::stopImmediately()
{
    QMutexLocker locker(&m_lock);
    m_isCanRun = false;
}
