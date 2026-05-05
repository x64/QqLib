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

//
// Public API
//
public:
    //
    // Range API
    //
    static inline int
    toRange(int index, bool negativeIsAllow = true) noexcept
    {
        // TODO:
        // static_assert(
        //     qqIsNonConstEnumIndexType<TIndex>,
        //     "The type of the `index` is not non-const enum index type."
        // );

        if (negativeIsAllow)
            toPositiveRange(index);

        index = std::max( 0, std::min(index, D::lastValidIndex()) );
        return index;
    }

    static constexpr void
    toPositiveRange(int & index) noexcept
    {
        // TODO:
        // static_assert(
        //     qqIsNonConstEnumIndexType<TIndex>,
        //     "The type of the `index` is not non-const enum index type."
        // );

        index = index < 0
            ? D::lastValidIndex() + index +1
            : index;
    }

    //
    // \brief Searching \arg e in values and return its index. If e in not range then do throw.
    //
    static inline constexpr int
    ifEnumInNotRangeDoThrow(TEnum e, char const * methodName)
    {
        auto it = D::eiMap().find(e);
        if (it == D::eiMap().end())
            qq_throw_l(
                std::out_of_range,
                StringLiteral{ "The %1(as int) is not a member of enumeration %2\nMETHOD: %3" }
                    .arg(static_cast<TInt>(e))
                    .arg(D::className())
                    .arg(methodName)
                    .toLatin1()
            )

        return it->second;
    }

    // ret: if index in range then don't throws the exception
    static constexpr void
    ifIndexOutOfRangeDoThrow(
        int          index,
        char const * methodName,
        char const * paramName = "index")
    {
        if (D::indexInRange(index)) //-V3504
            return;

        qq_throw_l(
            std::out_of_range,
            StringLiteral{ "The %1 = %2 is out of range.\nMETHOD: %3" }
                .arg(paramName)
                .arg(index)
                .arg(methodName)
                .toLatin1()
        );
    }
};


} // namespace Qq::Enum
