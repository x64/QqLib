#pragma once

#include "./MetadataT.h"


namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
struct MetadataInitializierT
{
    constexpr MetadataInitializierT()
    {
        using D = MetadataT<TClass,TEnum,TInt>;
    }
};


} // namespace Qq::Enum
