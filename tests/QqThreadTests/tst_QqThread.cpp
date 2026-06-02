#include <QTest>


// add necessary includes here
#include "../../src/QqThread/QqMutexGuard.h"
#include "./WorkerThread02.h"

class QqThread : public QObject
{
    Q_OBJECT

public:
    QqThread();
    ~QqThread();

private slots:
    void multithreadGlobalVarLock_test01();
    void multithreadGlobalVarLock_test02();
};

QqThread::QqThread()
{}

QqThread::~QqThread()
{}

//
// multithreadLockingTest
//

static volatile int global_var = 0;

void mod_global_var(int delta)
{
    qq_lock
    {
        QThread::msleep(1300);
        global_var += delta;
    }
}


class WorkerThread01 : public QThread
{
    Q_OBJECT

    void run() override
    {
        QString result;
        for (int i = 0; i < 10; ++i)
        {
            //QThread::msleep(1300);
            mod_global_var(-1);
            qDebug() << "-1: global_var = " << global_var;
        }

        emit resultReady(result);
    }

signals:
    void resultReady(const QString &s);
};



void QqThread::multithreadGlobalVarLock_test01()
{
    WorkerThread01 * workerThread = new WorkerThread01();
    // connect(workerThread, &WorkerThread::resultReady, this,         &MyObject::handleResults);
    // connect(workerThread, &WorkerThread::finished,    workerThread, &QObject::deleteLater);
    workerThread->start();

    qDebug() << "sizeof QAtomicInt = " << sizeof QAtomicInt;

    for (int i = 0; i < 10; ++i)
    {
        //QThread::msleep(2300);
        mod_global_var(+1);
        qDebug() << "+1: global_var = " << global_var;
    }
}



#include "./WorkerThread02.h"
void QqThread::multithreadGlobalVarLock_test02()
{
    volatile int value = 0;

    int workerNum = 1;

    WorkerThread02 worker1( workerNum++, &value, +1 );
    WorkerThread02 worker2( workerNum++, &value, -1 );
    WorkerThread02 worker3( workerNum++, &value, +2 );
    WorkerThread02 worker4( workerNum++, &value, -2 );

    worker1.start();
    worker2.start();
    worker3.start();
    worker4.start();

    QThread::msleep(20000);
}


QTEST_APPLESS_MAIN(QqThread)

#include "tst_QqThread.moc"
