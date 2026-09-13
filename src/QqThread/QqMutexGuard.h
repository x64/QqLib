#pragma once

#include <mutex>


namespace Qq::Thread
{


template <class TMutex>
class QqMutexGuard
{
public:
    QqMutexGuard(QqMutexGuard const &) = delete;

    QqMutexGuard(TMutex & mutex)
        : m_mutex{ mutex }
    {
        m_mutex.lock();
    }

    ~QqMutexGuard()
    {
        m_mutex.unlock();
    }

    constexpr operator bool() const noexcept
    {
        return true;
    }

    QqMutexGuard & operator = (const QqMutexGuard&) = delete;

private:
    TMutex & m_mutex;
};


} // namespace Qq::Thread
