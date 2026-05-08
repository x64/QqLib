#pragma once

#include "./_CompileConfig.h"
#include "./QqEnumString.h"


//#include "./MetadataT.h"

namespace Qq::Enum
{


//
// \brief Tuple for the enum value and the name enum.
//
template <typename TEnum, typename TInt>
class EnumItemWrapperT
{
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

    EnumItemWrapperT(int index, TEnum value, QqEnumString const & name, int invalidValueIndex, int defaultValueIndex)
        : m_value{ value  }
        , m_pName{ & name }
    {
        m_index = index & c_indexMask
                  | invalidValueIndex << c_invalidValueShift
                  | defaultValueIndex << c_defaultValueShift;
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
        return * m_pName;
    }

    inline constexpr int
    index() const noexcept
    {
        return m_index & c_indexMask;
    }

    inline constexpr TInt
    asInt() const noexcept
    {
        return static_cast<TInt>(value());
    }

    inline constexpr bool
    isInvalid() const noexcept
    {
        return index() == (m_index >> c_invalidValueShift);
    }

    inline constexpr bool
    isDefault() const noexcept
    {
        return index() == (m_index >> c_defaultValueShift);
    }

//
// Consts
//
private:
    enum : int
    {
        c_invlaidValueMask  = 0x00ff0000,
        c_defaultValueMask  = 0x0000ff00,
        c_indexMask         = 0x000000ff
    };

    enum : int
    {
        c_invalidValueShift = 16,
        c_defaultValueShift = 8
    };

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
