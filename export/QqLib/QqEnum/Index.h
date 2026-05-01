#pragma once

#include <atomic>
#include <xatomic.h>

namespace Qq::Enum
{

class Index : public std::atomic<int>
{
//
// CTORS
//
public:
    inline constexpr Index(const int initValue = 0) noexcept
        : std::atomic<int>(initValue)
    {}

//
// Operators
//
public:
    inline int operator () () const noexcept {
        return load(std::memory_order_acquire);
    }

    inline Index & operator = (Index const & other) noexcept {
        store(other(), std::memory_order_release);
        return *this;
    }
};


} // namespace Qq::Enum
