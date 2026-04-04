#pragma once

#include "../Macros/Variadic/ForEach.M.h"
#include "../Macros/Expand.M.h"
#include "../Macros/Cat.M.h"



#define QQ_ENUM_CORE_AS(Int,Class,...)                                      \
public:                                                                     \
    enum  : bool { _isQqEnum = true };                                      \
    using _Class = Class;                                                   \
    using _Int   = Int;                                                     \
    enum  _Enum  : Int { __VA_ARGS__ };                                     \
                                                                            \
    /* TODO: move to Metadata and make access throught methods */           \
    /* TODO: make throught QLatin1StringView                   */           \
    static inline QString const _className   { #Class };                    \
    static inline QString const _intTypeName { #Int   };                    \

