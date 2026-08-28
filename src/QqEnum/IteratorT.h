#pragma once


#include "./Index.h"
#include "./MetadataT.h"
#include "./CoreT.h"
#include "./EnumItemWrapperT.h"


namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
struct IteratorT
{
//
// Public using synonyms:
//
    using Wrapper = EnumItemWrapperT<TEnum,TInt>;

//
// Iterator's using-synonyms
//
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Wrapper;
    using pointer           = Wrapper * ;
    using reference         = Wrapper & ;

//
// CTORs
//
public:
    constexpr IteratorT(int fromIndex = 0, int toIndex = Const::badIndex)
        : m_index    { fromIndex }
    {
        m_fromIndex = C::toRange(fromIndex, true);
        m_toIndex   = C::toRange(toIndex,   true);
        m_order     = m_fromIndex > m_toIndex ? -1 : +1;
    }

    constexpr IteratorT(IteratorT const & from)
        : IteratorT{ from.m_fromIndex, from.m_toIndex }
    {}

    constexpr IteratorT(TEnum from, TEnum to)
    {
        m_fromIndex = D::indexOf(from);
        m_toIndex   = D::indexOf(to);
        m_order     = m_fromIndex > m_toIndex ? -1 : +1;
    }

//
// Consistent API
//
public:
    // \b Is m_index between _range[from, to]?
    inline constexpr bool
    inIterRange() const noexcept
    {
        return Qq::Helpers::Main::inMinMax(
            m_order > 0 ? m_fromIndex : m_toIndex,
            m_index,
            m_order > 0 ? m_toIndex   : m_fromIndex
        );
    }

    // \b Is m_index in range from 0 to D::count()-1.
    inline constexpr bool
    inRange() const noexcept
    {
        return D::indexInRange(m_index);
    }

    inline constexpr int
    index() const noexcept
    {
        return m_index;
    }

public:
    //
    // Comparsion operators
    //

    friend inline constexpr bool
    operator < (IteratorT const & lh, IteratorT const & rh) {
        return lh.m_index < rh.m_index;
    }

    friend inline constexpr bool
    operator > (IteratorT const & lh, IteratorT const & rh) {
        return lh.m_index > rh.m_index;
    }

    friend inline constexpr bool
    operator <= (IteratorT const & lh, IteratorT const & rh) {
        return lh.m_index <= rh.m_index;
    }

    friend inline constexpr bool
    operator >= (IteratorT const & lh, IteratorT const & rh) {
        return lh.m_index >= rh.m_index;
    }

    friend inline constexpr bool
    operator == (IteratorT const & lh, IteratorT const & rh) noexcept {
        return lh.m_index == rh.m_index;
    }

    friend inline constexpr bool
    operator != (IteratorT const & lh, IteratorT const & rh) noexcept {
        return not (lh.m_index == rh.m_index);
    }


    //
    // Assignment operators
    //

    inline constexpr IteratorT &
    operator = (int n) noexcept
    {
        m_index = n;
        return *this;
    }

    inline constexpr IteratorT &
    operator = (IteratorT const & other) noexcept
    {
        if (other != *this)
            m_index = other.m_index;

        return *this;
    }

    //
    // ADD operators
    //

    friend inline constexpr IteratorT
    operator + (IteratorT const & lh, IteratorT const & rh) noexcept
    {
        IteratorT iter;
        iter.m_index = lh.m_index + rh.m_index;
        return iter;
    }

    friend inline constexpr IteratorT &
    operator + (IteratorT & iter, int n) noexcept
    {
        iter.m_index += n;
        return iter;
    }

    //
    // INC opertors
    //
    inline constexpr IteratorT &
    operator ++ () noexcept
    {
        m_index += m_order;
        return *this;
    }

    inline constexpr IteratorT
    operator ++ (int) noexcept
    {
        IteratorT tmp{ m_index };
        m_index += m_order;
        return tmp;
    }

    //
    // ADD & assignment operators
    //

    inline constexpr IteratorT &
    operator += (int n) noexcept
    {
        m_index += n;
        return *this;
    }

    inline constexpr IteratorT &
    operator += (IteratorT const & other) noexcept
    {
        m_index += other.m_index;
        return *this;
    }

    //
    // SUB operators
    //

    friend inline constexpr IteratorT
    operator - (IteratorT lhs, IteratorT const & rhs) noexcept
    {
        lhs -= rhs;
        return lhs;
    }

    friend inline constexpr IteratorT &
    operator - (IteratorT & iter, int n) noexcept
    {
        iter.m_index -= n;
        return iter;
    }

    //
    // DEC operators
    //

    constexpr inline IteratorT &
    operator -- () noexcept
    {
        m_index -= m_order;
        return *this;
    }

    constexpr inline IteratorT
    operator -- (int) noexcept
    {
        IteratorT tmp{ m_index };
        m_index -= m_order;
        return tmp;
    }

    //
    // SUB & assignment
    //

    inline constexpr IteratorT &
    operator -= (int n) noexcept
    {
        m_index -= n;
        return *this;
    }

    inline constexpr IteratorT &
    operator -= (IteratorT const & other) noexcept
    {
        m_index -= other.m_index;
        return *this;
    }

    //
    // Wrap operations
    //

    constexpr inline Wrapper const &
    operator * () const
    {
        C::ifIndexOutOfRangeDoThrow(m_index, QQ_FULL_FUNC_SIG, "m_index");
        return D::wrapperNoCheck(m_index);
    }

    constexpr inline Wrapper const *
    operator -> () const
    {
        C::ifIndexOutOfRangeDoThrow(m_index, QQ_FULL_FUNC_SIG, "m_index");
        return & D::wrapperNoCheck(m_index);
    }

//
// Using-synonyms
//
private:
    using C = CoreT<TClass,TEnum,TInt>;
    using D = MetadataT<TClass,TEnum,TInt>;

//
// Fields
//
private:
    Qq::Enum::Index m_index     ;
    int             m_fromIndex ;
    int             m_toIndex   ;
    int             m_order    ;
};


} // namespace Qq::Enum

