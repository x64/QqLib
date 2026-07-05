#pragma once

#include <mutex>


namespace Qq::Thread
{


template <class TMutex>
struct QqMutexGuard
{
    QqMutexGuard(TMutex & mutex) noexcept
        : m_mutex{ mutex }
    {
        m_mutex.lock();
    }

    virtual ~QqMutexGuard() noexcept
    {
        m_mutex.unlock();
    }

    constexpr operator bool() const noexcept
    {
        return true;
    }

    TMutex & m_mutex;
};


} // namespace Qq::Thread
