#pragma once

#include "./_CompileConfig.h"
#include "./QqEnumString.h"


namespace Qq::Enum
{


//
// \brief Tuple for the enum value and the name enum.
//
template <typename TEnum, typename TInt>
class EnumItemWrapperT
{
    TEnum                m_value;
    QqEnumString const * m_pName = nullptr;

//
// CTORs
//
public:
    EnumItemWrapperT(TEnum aValue, QqEnumString const & aName)
        : m_value{ aValue  }
        , m_pName{ & aName }
    {}

    EnumItemWrapperT() = default;

//
// Operators
//
public:
    inline constexpr bool
    operator == (EnumItemWrapperT const & other) const noexcept
    {
        return m_value == other.m_value;
    }

    inline constexpr bool
    operator == (TEnum const & otherEnum) const noexcept
    {
        return m_value == otherEnum;
    }

    inline constexpr bool
    operator < (EnumItemWrapperT const & other) const noexcept
    {
        return m_value < other.m_value;
    }

    inline constexpr bool
    operator < (TEnum const & otherEnum) const noexcept
    {
        return m_value < otherEnum;
    }

    inline constexpr bool
    operator > (EnumItemWrapperT const & other) const noexcept
    {
        return m_value > other.m_value;
    }

    inline constexpr bool
    operator > (TEnum const & otherEnum) const noexcept
    {
        return m_value > otherEnum;
    }

    inline constexpr TEnum
    value() const noexcept
    {
        return m_value;
    }

    inline constexpr QqEnumString const &
    name() const noexcept
    {
        return * m_pName;
    }

    inline constexpr TInt
    asInt() const noexcept
    {
        return static_cast<TInt>(value());
    }
};


} // namespace Qq::Enum
