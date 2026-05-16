#pragma once

#include "./MetadataT.h"


namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
class DefaultValueSetterT
{
public:
    constexpr DefaultValueSetterT(TEnum const e) noexcept
    {
        MetadataT<TClass,TEnum,TInt>::setDefaultValue(e);
    }
};


} // namespace Qq::Enum
