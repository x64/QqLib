#pragma once

#include "./_CompileConfig.h"
#include "./QqEnumString.h"


#include "./Consts.h"

namespace Qq::Enum
{


//
// \brief Tuple for the enum value and the name enum.
//
template <typename TEnum, typename TInt>
class EnumItemWrapperT
{
//
// Friends
//
    template <typename T_Class, typename T_Enum, typename T_Int>
    friend struct MetadataT;

//
// CTORs
//
public:
    EnumItemWrapperT(int index, TEnum value, QqEnumString const & name)
        : m_index{ index  }
        , m_value{ value  }
        , m_pName{ & name }
    {}

    EnumItemWrapperT(
        int                  index,
        TEnum                value,
        QqEnumString const & name,
        int                  invalidValueIndex,
        int                  defaultValueIndex
    )
        : m_value{ value  }
        , m_pName{ & name }
    {
        m_index = index & Const::indexMask
                  | invalidValueIndex << Const::invalidValueShift
                  | defaultValueIndex << Const::defaultValueShift;
    }

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

//
// Const Data API
//
    inline constexpr TEnum
    value() const noexcept
    {
        return m_value;
    }

    inline constexpr QqEnumString const &
    name() const noexcept
    {
        return *m_pName;
    }

    inline constexpr int
    index() const noexcept
    {
        return m_index & Const::indexMask;
    }

    inline constexpr TInt
    asInt() const noexcept
    {
        return static_cast<TInt>(value());
    }

    inline constexpr bool
    isInvalid() const noexcept
    {
        return index() == (m_index >> Const::invalidValueShift);
    }

    inline constexpr bool
    isDefault() const noexcept
    {
        return index() == (m_index >> Const::defaultValueShift);
    }

//
// Fields
//
    int                  m_index;
    TEnum                m_value;
    QqEnumString const * m_pName = nullptr;

};


} // namespace Qq::Enum

#include "./MetadataT.h"
//#include "./CoreT.h"
