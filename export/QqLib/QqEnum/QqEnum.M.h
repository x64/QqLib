#pragma once


#include "./_CompileConfig.h"
#include QQ_ENUM_QQ_STRING_INCLUDE

#include "../Macros/Variadic/ForEach.M.h"
#include "../Macros/Expand.M.h"
#include "../Macros/Cat.M.h"

#include "./EnumItemT.h"
#include "./CoreT.h"
#include "./EatAssignT.h"



#define QP_GET_VALUE_FROM_ENUM_ITEM(ITEM)   _EatAssign{}         << ITEM  , //-V2561
#define QP_GET_NAME_FROM_ENUM_ITEM(ITEM)    _H::parseEnumValueName(#ITEM) ,


#define QQ_ENUM_CORE_AS(Int,Class,...)                                      \
public:                                                                     \
    enum  : bool { _isQqEnum = true };                                      \
    using _Class = Class;                                                   \
    using _Int   = Int;                                                     \
    enum  _Enum  : Int { __VA_ARGS__ };                                     \
                                                                            \
    static char const * _className    () { return #Class };                 \
    static char const * _intTypeName  () { return #Int   };                 \
    static char const * _fullClassName()                                    \
    {                                                                       \
        #ifdef _MSC_VER                                                     \
            return __FUNCTION__;                                            \
        #elif                                                               \
            return __func__                                                 \
        #endif                                                              \
    }                                                                       \
                                                                            \
    using _EnumItem = Qq::Enum::EnumItemT<TEnum>;                           \
                                                                            \
protected:                                                                  \
    template <typename T_Class, typename T_Enum, typename T_Int>            \
    friend class Qq::Enum::CoreT;                                           \
                                                                            \
    using _C         = Qq::Enum::CoreT<_Class,_Enum,_Int>;                  \
    using _D         = Qq::Enum::MetadataT<_Class,_Enum,_Int>;              \
    using _H         = Qq::Enum::Helper;                                    \
    using _EatAssign = Qq::Enum::EatAssign<_Enum, _Int>;                    \
                                                                            \
    static inline _D _d {                                                   \
        std::vector<_Enum> {                                                \
            QQ_PP_FOREACH(                                                  \
                QP_GET_VALUE_FROM_ENUM_ITEM,                                \
                __VA_ARGS__                                                 \
            )                                                               \
        },                                                                  \
        std::vector<Qq_string> {                                            \
            QQ_PP_FOREACH(                                                  \
                QP_GET_NAME_FROM_ENUM_ITEM,                                 \
                __VA_ARGS__                                                 \
            )                                                               \
        }                                                                   \
    };                                                                      \
