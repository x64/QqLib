#pragma once

#include "./_CompileConfig.h"
#include "./QqEnumString.h"


namespace Qq::Enum
{


//
// \brief Tuple for the enum value and the name enum.
//
template <typename TEnum>
class EnumItemWrapperT
{
    TEnum                m_value;
    QqEnumString const * m_pName;

public:
    EnumItemWrapperT(TEnum aValue, QqEnumString const & aName)
        : m_value{ aValue  }
        , m_pName{ & aName }
    {}

    EnumItemWrapperT() = default;

    bool operator == (const EnumItemWrapperT & other) const noexcept {
        return m_value == other.m_value;
    }
    bool operator == (TEnum const & otherEnum) const noexcept {
        return m_value == otherEnum;
    }

    bool operator < (const EnumItemWrapperT & other) const noexcept {
        return m_value < other.m_value;
    }
    bool operator < (TEnum const & otherEnum) const noexcept {
        return m_value < otherEnum;
    }

    bool operator > (const EnumItemWrapperT & other) const noexcept {
        return m_value > other.m_value;
    }
    bool operator > (TEnum const & otherEnum) const noexcept {
        return m_value > otherEnum;
    }

    TEnum value() const noexcept {
        return m_value;
    }

    QqEnumString const & name() const noexcept {
        return * m_pName;
    }
};


} // namespace Qq::Enum
