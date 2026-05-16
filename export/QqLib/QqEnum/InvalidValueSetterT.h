#pragma once

#include "./MetadataT.h"


namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
class InvalidValueSetterT
{
public:
    constexpr InvalidValueSetterT(TEnum const e) noexcept
    {
        MetadataT<TClass,TEnum,TInt>::setInvalidValue(e);
    }
};


} // namespace Qq::Enum
