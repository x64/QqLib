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
    using EnumItemWrapper = EnumItemWrapperT<TEnum,TInt>;

//
// Iterator's using-synonyms
//
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = EnumItemWrapper;
    using pointer           = EnumItemWrapper * ;
    using reference         = EnumItemWrapper & ;

//
// CTORs
//
public:
    IteratorT(int index = 0)
        : m_index{ index }
    {}

    IteratorT(IteratorT const & other)
        : IteratorT{ other.m_index }
    {}

//
// Consistent API
//
public:
    inline constexpr bool
    inRange() const noexcept {
        return D::indexInRange(m_index);
    }

//
// Assignment operators
//
public:
    inline constexpr IteratorT &
    operator = (int n) noexcept
    {
        m_index = n;
        return *this;
    }

    inline constexpr IteratorT &
    operator = (IteratorT const & other) noexcept
    {
        if (other == *this)
            return *this;

        m_index = other.m_index;
        return *this;
    }

    //
    // ADD & assignment
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
        if (other == *this) return *this;
        m_index += other.m_index;
        return *this;
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
        if (other == *this) return *this;
        m_index -= other.m_index;
        return *this;
    }

//
// Comparsion operators
//
public:
    friend inline constexpr bool
    operator < (IteratorT const & it1, IteratorT const & it2) {
        return it1.m_index < it2.m_index;
    }

    friend inline constexpr bool
    operator > (IteratorT const & it1, IteratorT const & it2) {
        return it2 < it1;
    }

    friend inline constexpr bool
    operator <= (IteratorT const & it1, IteratorT const & it2) {
        return not (it1 > it2);
    }

    friend inline constexpr bool
    operator >= (IteratorT const & it1, IteratorT const & it2) {
        return not (it2 < it1);
    }

    inline constexpr bool
    operator == (IteratorT const & other) noexcept {
        return m_index == other.m_index;
    }

    inline constexpr bool
    operator != (IteratorT const & other) noexcept {
        return not (m_index == other.m_index);
    }

//
// Add operators
//
    inline constexpr IteratorT &
    operator + (IteratorT const & other) noexcept
    {
        m_index += other.m_index;
        return *this;
    }

    friend inline constexpr IteratorT
    operator + (IteratorT lhs, IteratorT const & rhs) noexcept
    {
        lhs += rhs;
        return lhs;
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
    constexpr inline IteratorT &
    operator ++ () noexcept
    {
        ++ m_index;
        return *this;
    }

    constexpr inline IteratorT
    operator ++ (int) noexcept
    {
        IteratorT tmp{ m_index };
        ++ m_index;
        return tmp;
    }

//
// Sub operators
//
    inline constexpr IteratorT &
    operator - (IteratorT const & other) noexcept
    {
        m_index -= other.m_index;
        return *this;
    }

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
        -- m_index;
        return *this;
    }

    constexpr inline IteratorT
    operator -- (int) noexcept
    {
        IteratorT tmp{ m_index };
        -- m_index;
        return tmp;
    }

//
// Wrap operations
//
public:
    constexpr inline EnumItemWrapper const &
    operator * () const noexcept
    {
        C::ifIndexOutOfRangeDoThrow(m_index, QQ_FULL_FUNC_SIG, "m_index");
        return D::wrapper(m_index);
    }

    constexpr inline EnumItemWrapper const *
    operator -> () const noexcept
    {
        C::ifIndexOutOfRangeDoThrow(m_index, QQ_FULL_FUNC_SIG, "m_index");
        return & D::wrapper(m_index);
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
    Qq::Enum::Index m_index;
};


} // namespace Qq::Enum

