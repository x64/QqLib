#pragma once

#include "./_CompileConfig.h"
#include QQ_ENUM_QQ_STRING_INCLUDE

namespace Qq::Enum
{


//
// \brief Tuple for the enum value and the name enum.
//
template <typename TEnum>
class EnumItemT
{
    TEnum             m_value;
    Qq_string const * m_pName;

public:
    EnumItemT(TEnum aValue, Qq_string const & aName)
        : m_value{ aValue  }
        , m_pName{ & aName }
    {}

    EnumItemT() = default;

    bool operator == (const EnumItemT & other) const noexcept {
        return m_value == other.m_value;
    }
    bool operator == (TEnum const & otherEnum) const noexcept {
        return m_value == otherEnum;
    }

    bool operator < (const EnumItemT & other) const noexcept {
         return m_value < other.m_value;
    }
    bool operator < (TEnum const & otherEnum) const noexcept {
         return m_value < otherEnum;
    }

    bool operator > (const EnumItemT & other) const noexcept {
         return m_value > other.m_value;
    }
    bool operator > (TEnum const & otherEnum) const noexcept {
         return m_value > otherEnum;
    }

    TEnum value() const noexcept {
        return m_value;
    }

    Qq_string const & name() const noexcept {
        return * m_pName;
    }
};


} // namespace Qq::Enum
