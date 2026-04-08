#pragma once


#include "./_CompileConfig.h"
#include QQ_ENUM_QQ_STRING_INCLUDE

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
protected:
    static constexpr EnumMetadata &
    d() noexcept {
        return TClsas::_d;
    }

    static TEnum
    at(int index) {
        return d().valueAt(index);
    }

    // ret: if index in range then don't throws the exception
    static constexpr void
    ifNotRangeDoThrow(
        int       const   index,
        Qq_string const & methodName,
        Qq_string const & paramName = Qq_stringLiteral("index"))
    {
        if (inRange(index)) //-V3504
            return;

        throw std::out_of_range{
            Qq_stringLiteral("%1: the `%2` is out of range.")
                .arg(methodName)
                .arg(paramName)
                .toLatin1()
        };

    }



///////////////////////
//
// :: API ::
//
///////////////////////

//
// Types
//
public:
    using EnumMetadata = MetadataT<TClass,TEnum,TInt>;

public:



};


} // namespace Qq::Enum
