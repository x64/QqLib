#pragma once

#include <QThread>
#include <QDebug>

#include "../../export/QqLib/QqThread/QqMutexGuard.h"


class WorkerThread02 : public QThread
{
    Q_OBJECT

public:
    WorkerThread02(int workerNum, int volatile * value, int delta, QObject * parent = nullptr)
        : QThread(parent)
        , m_workerNum{ workerNum }
        , m_pValue   { value     }
        , m_delta    { delta     }
    {}

private:
    void run() override
    {
        const char * signStr = m_delta > 0 ? "+" : "";

        for (int i = 0; i < 10; ++i)
            qq_lock
            {
                *m_pValue += m_delta;
                qDebug() << "[" << m_workerNum << "] " << signStr << m_delta << ": value = " << *m_pValue;
                QThread::msleep(1300);
            }

        // QString result;
        // for (int i = 0; i < 10; ++i)
        // {
        //     //QThread::msleep(1300);
        //     mod_global_var(-1);
        //     qDebug() << "-1: global_var = " << global_var;
        // }

        // emit resultReady(result);
    }

// signals:
//     void resultReady(const QString &s);

protected:
    int            m_workerNum;
    int volatile * m_pValue;
    int            m_delta;
};
