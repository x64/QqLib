#pragma once


#include "./_CompileConfig.h"
#include QQ_ENUM_QQ_STRING_INCLUDE

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

    //- static inline constexpr EnumMetadata &
    //- d() noexcept {
    //-     return TClsas::_d;
    //- }

    static inline TEnum
    value(int index) {
        //- return d().valueAt(index);
        return D::value(index);
    }

    // ret: if index in range then don't throws the exception
    static constexpr void
    ifIndexNotValidDoThrow(
        int       const   index,
        Qq_string const & methodName,
        Qq_string const & paramName = Qq_stringLiteral{ "index" })
    {
        if (indexIsValid(index)) //-V3504
            return;

        throw std::out_of_range{
            Qq_stringLiteral{ "%1: the `%2` is out of range." }
                .arg(methodName)
                .arg(paramName)
                .toLatin1()
        };

    }

//
// Public API
//
public:
    static inline constexpr bool
    indexIsValid(int index)
    {
        int minRangeIndex = D::m_invalidValueDefined ? 1 : 0;
        int maxRangeIndex = D::valueCount()-1;

        return Qq::Helper::inMinMax(minRangeIndex, index, maxRangeIndex);
    }


};


} // namespace Qq::Enum
