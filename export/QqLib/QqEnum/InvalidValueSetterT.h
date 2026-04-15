#pragma once

#include "./MetadataT.h"


namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
struct InvalidValueSetterT
{
    using Metadata = MetadataT<TClass,TEnum,TInt>;

    // constexpr InvalidValueSetterT(TEnum const e, Metadata & d) noexcept {
    //     d.setInvalidValue(e);
    // }
    constexpr InvalidValueSetterT(TEnum const e) noexcept {
        Metadata::setInvalidValue(e);
    }
};


} // namespace Qq::Enum
