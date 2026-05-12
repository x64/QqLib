#pragma once


#include "./IteratorT.h"


namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
struct IteratorWrapperT
{
    using Iterator = IteratorT<TClass,TEnum,TInt>;
    enum : int { c_toIndex = -1 };
//
// CTORs
//
    constexpr IteratorWrapperT()
        : IteratorWrapperT{ 0 }
    {}

    constexpr IteratorWrapperT(int fromIndex, int toIndex = c_toIndex)
    {
        using C = CoreT<TClass,TEnum,TInt>;

        m_fromIndex = C::toRange(fromIndex, true);
        m_toIndex   = C::toRange(toIndex,   true);
    }

    constexpr IteratorWrapperT(TEnum from, TEnum to)
    {
        using D = MetadataT<TClass,TEnum,TInt>;

        m_fromIndex = D::indexOf(from);
        m_toIndex   = D::indexOf(to);
    }

    Iterator begin() const noexcept
    {
        return Iterator{ m_fromIndex };
    }

    Iterator end() const noexcept
    {
        return Iterator{ 1 + m_toIndex };
    }

private:
    int m_fromIndex;
    int m_toIndex;
};


} // namespace Qq::Enum
