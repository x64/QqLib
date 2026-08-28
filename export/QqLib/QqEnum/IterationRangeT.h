#pragma once


#include "./IteratorT.h"


namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
struct IterationRangeT
{
    using Iterator = IteratorT<TClass,TEnum,TInt>;

//
// CTORs
//
    constexpr IterationRangeT() noexcept
        : IterationRangeT{ 0 }
    {}

    constexpr IterationRangeT(int fromIndex, int toIndex = Const::badIndex) noexcept
    {
        using C = CoreT<TClass,TEnum,TInt>;

        m_fromIndex = C::toRange(fromIndex, true);
        m_toIndex   = C::toRange(toIndex,   true);
        m_order     = m_fromIndex > m_toIndex ? -1 : +1;
    }

    constexpr IterationRangeT(TEnum from, TEnum to) noexcept
    {
        using D = MetadataT<TClass,TEnum,TInt>;

        m_fromIndex = D::indexOf(from);
        m_toIndex   = D::indexOf(to);
        m_order     = m_fromIndex > m_toIndex ? -1 : +1;
    }

    Iterator begin() const noexcept
    {
        return Iterator{ m_fromIndex, m_toIndex };
    }

    Iterator end() const noexcept
    {
        return Iterator{ m_order + m_toIndex };
    }

private:
    int m_fromIndex;
    int m_toIndex;
    int m_order;
};


} // namespace Qq::Enum
