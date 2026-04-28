#pragma once


#include "./_CompileConfig.h"
#include "./QqEnumString.h"
#include "./QqEnumStringLiteral.h"

#include "./MetadataT.h"


namespace Qq::Enum
{


///
/// \brief The core class for the QQ_ENUM macro.
/// All work with QqEnum should be here.
///
template <typename TClass, typename TEnum, typename TInt =int>
class CoreT
{
//
// Types
//
public:
    using EnumMetadata = MetadataT<TClass,TEnum,TInt>;

//
// Internal API
//
protected:
    using D = MetadataT<TClass,TEnum,TInt>;

    static inline TEnum
    value(int index) {
        return D::value(index);
    }

    // ret: if index in range then don't throws the exception
    static constexpr void
    ifIndexNotValidDoThrow(
        int          const   index,
        QqEnumString const & methodName,
        QqEnumString const & paramName = StringLiteral{ "index" })
    {
        if (indexIsValid(index)) //-V3504
            return;

        throw std::out_of_range{
            StringLiteral{ "%1: the `%2` is out of range." }
                .arg(methodName)
                .arg(paramName)
                .toLatin1()
        };

    }

//
// Public API
//
public:
    //
    // Range API
    //
    static inline constexpr bool
    indexIsValid(int index)
    {
        int minRangeIndex = D::isInvalidValueDefined() ? 1 : 0;
        int maxRangeIndex = D::lastValidindex();

        return Qq::Helper::inMinMax(minRangeIndex, index, maxRangeIndex);
    }

    static inline int
    toRange(int index, bool negativeIsAllow = true) noexcept {  //-V2565
        return toRange<int>(index, negativeIsAllow);            //-V2565
    }

    template <typename TIndex>
    static inline int
    toRange(TIndex & index, bool negativeIsAllow = true) noexcept
    {
        // TODO:
        // static_assert(
        //     qqIsNonConstEnumIndexType<TIndex>,
        //     "The type of the `index` is not non-const enum index type."
        // );

        if (negativeIsAllow)
            toPositiveRange(index);

        index = std::max( 0, std::min(index, D::lastValidindex()) );
        return index;
    }

    template <typename TIndex>
    static constexpr void
    toPositiveRange(TIndex & index) noexcept
    {
        // TODO:
        // static_assert(
        //     qqIsNonConstEnumIndexType<TIndex>,
        //     "The type of the `index` is not non-const enum index type."
        // );

        index = index < 0
            ? D::lastValidindex() + index +1
            : index;
    }
};


} // namespace Qq::Enum
