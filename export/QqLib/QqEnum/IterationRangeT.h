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

    constexpr IterationRangeT(int fromIndex, int toIndex = Const::badIndex)
    {
        using C = CoreT<TClass,TEnum,TInt>;
        using D = MetadataT<TClass,TEnum,TInt>;

        C::makePositiveIndex(fromIndex);
        C::makePositiveIndex(toIndex);

        if (std::abs(fromIndex) >= D::count())
            throw std::out_of_range("IterationRangeT::.ctor(...): `int fromIndex` is out of range.");

        if (std::abs(toIndex) >= D::count())
            throw std::out_of_range("IterationRangeT::.ctor(...): `int toIndex` is out of range.");

        m_fromIndex = fromIndex;
        m_toIndex   = toIndex;
        m_order     = m_fromIndex > m_toIndex ? -1 : +1;
    }

    constexpr IterationRangeT(TEnum from, TEnum to)
    {
        using D = MetadataT<TClass,TEnum,TInt>;

        int fromIndex = D::indexOf(from);
        int toIndex   = D::indexOf(to);

        if (Const::badIndex == fromIndex)
            throw std::out_of_range("IterationRangeT::.ctor(...): `_Enum from` is out of range.");

        if (Const::badIndex == toIndex)
            throw std::out_of_range("IterationRangeT::.ctor(...): `_Enum to` is out of range.");

        m_fromIndex = fromIndex;
        m_toIndex   = toIndex;
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
