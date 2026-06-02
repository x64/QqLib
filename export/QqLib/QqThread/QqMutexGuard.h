#pragma once


#include <mutex>
// #include <QMutex>
// #include <QDebug>


namespace Qq::Thread
{


template <class TMutex>
struct QqMutexGuard
{
    QqMutexGuard(TMutex & mutex) noexcept
        : m_mutex{ mutex }
    {
        m_mutex.lock();
        // qDebug() << "QqMutexGuard::mutex locked";
    }

    virtual ~QqMutexGuard() noexcept
    {
        m_mutex.unlock();
        // qDebug() << "QqMutexGuard::mutex unlocked";
    }

    constexpr operator bool() const noexcept
    {
        return true;
    }

    TMutex & m_mutex;
};


} // namespace Qq::Thread
