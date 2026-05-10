#pragma once


#include "./_CompileConfig.h"
#include "./QqEnumString.h"

#include "../Macros/_MainMacro.M.h"
#include "../Macros/Variadic/ForEach.M.h"
#include "../Macros/Expand.M.h"
#include "../Macros/Cat.M.h"

#include "./EnumItemWrapperT.h"
#include "./CoreT.h"
#include "./EatAssignT.h"
#include "./InvalidValueSetterT.h"
#include "./DefaultValueSetterT.h"
#include "./Index.h"



#define QP_GET_VALUE_FROM_ITEM(ITEM)    _EatAssign{}         << ITEM  , //-V2561
#define QP_GET_NAME_FROM_ITEM(ITEM)     _H::parseEnumValueName(#ITEM) ,


#define QQ_ENUM_CORE(Class,...)         QQ_ENUM_CORE_AS(int, Class, __VA_ARGS__)
#define QQ_ENUM_AS(Int,Class,...)       QQ_ENUM_CORE_AS(Int,Class,__VA_ARGS__)
#define QQ_ENUM(Class,...)              QQ_ENUM_AS(int,Class,__VA_ARGS__)


#define QQ_ENUM_CORE_AS(Int,Class,...)                                      \
public:                                                                     \
    enum  { _0___BELOW_ENUM_API_0NLY___ };                                  \
    enum  : bool { _isQqEnum = true };                                      \
    using _Class = Class;                                                   \
    using _Int   = Int;                                                     \
    enum  _Enum  : Int { __VA_ARGS__ };                                     \
                                                                            \
    using _Wrapper = Qq::Enum::EnumItemWrapperT<_Enum,_Int>;                \
                                                                            \
private:                                                                    \
    static inline char const * __gfcn() {                                   \
        return QQ_FULL_FUNC_SIG;                                            \
    }                                                                       \
                                                                            \
protected:                                                                  \
    template <typename T_Class, typename T_Enum, typename T_Int>            \
    friend class Qq::Enum::CoreT;                                           \
                                                                            \
    using _C         = Qq::Enum::CoreT<_Class,_Enum,_Int>;                  \
    using _D         = Qq::Enum::MetadataT<_Class,_Enum,_Int>;              \
    using _H         = Qq::Enum::Helper;                                    \
    using _EatAssign = Qq::Enum::EatAssignT<_Enum, _Int>;                   \
                                                                            \
    static inline _D _d {                                                   \
        #Class,                                                             \
        #Int,                                                               \
        __gfcn(),                                                           \
        std::vector<_Enum> {                                                \
            QQ_PP_FOREACH(                                                  \
                QP_GET_VALUE_FROM_ITEM,                                     \
                __VA_ARGS__                                                 \
            )                                                               \
        },                                                                  \
        std::vector<QqEnumString> {                                         \
            QQ_PP_FOREACH(                                                  \
                QP_GET_NAME_FROM_ITEM,                                      \
                __VA_ARGS__                                                 \
            )                                                               \
        }                                                                   \
    };                                                                      \
                                                                            \
/*                                                                          \
 * Fields                                                                   \
 */                                                                         \
protected:                                                                  \
    Qq::Enum::Index m_index;                                                \
                                                                            \
/**********************                                                     \
 *                                                                          \
 * Public API                                                               \
 *                                                                          \
 **********************/                                                    \
public:                                                                     \
    /*                                                                      \
     * CTORS & DTORS                                                        \
     */                                                                     \
    QP_ENUM_CTORS_IMPL_AS(Int,Class)                                        \
                                                                            \
    QP_ENUM_OPERATORS_IMPL_AS(Int,Class)                                    \
                                                                            \
    /*                                                                      \
     * Metadata                                                             \
     */                                                                     \
    static inline char const *                                              \
    _className() noexcept {                                                 \
        return _D::className();                                             \
    }                                                                       \
                                                                            \
    static inline char const *                                              \
    _intTypeName() noexcept {                                               \
        return _D::intTypeName();                                           \
    }                                                                       \
                                                                            \
    static inline char const *                                              \
    _fullClassName() noexcept {                                             \
        return _D::fullClassName();                                         \
    }                                                                       \
                                                                            \
    /*                                                                      \
     * Names & values access                                                \
     */                                                                     \
    static inline constexpr int                                             \
    _count() noexcept {                                                     \
        return _D::count();                                                 \
    }                                                                       \
                                                                            \
    inline constexpr _Enum                                                  \
    _value() const noexcept {                                               \
        return _D::value(m_index);                                          \
    }                                                                       \
                                                                            \
    inline constexpr QqEnumString const &                                   \
    _name() const noexcept {                                                \
        return _D::name(m_index);                                           \
    }                                                                       \
                                                                            \
    static inline constexpr QqEnumString const &                            \
    _nameByValue(_Enum const e) noexcept {                                  \
        return _D::nameByValue(e);                                          \
    }                                                                       \
                                                                            \
    inline constexpr _Wrapper const &                                       \
    _wrapper() const noexcept {                                             \
        return _D::wrapper(m_index);                                        \
    }                                                                       \
                                                                            \
    inline constexpr _Wrapper const &                                       \
    operator () () const noexcept {                                         \
        return _wrapper();                                                  \
    }                                                                       \
                                                                            \
    /*                                                                      \
     * Lists                                                                \
     */                                                                     \
    static inline constexpr std::vector<_Enum> const &                      \
    _valueList() noexcept {                                                 \
        return _D::valueList();                                             \
    }                                                                       \
                                                                            \
    static inline constexpr std::vector<QqEnumString> const &               \
    _nameList() noexcept {                                                  \
        return _D::nameList();                                              \
    }                                                                       \
                                                                            \
    static inline constexpr std::vector<_Wrapper> const &                   \
    _wrapperList() noexcept {                                               \
        return _D::wrapperList();                                           \
    }                                                                       \
                                                                            \
    /*                                                                      \
     * Others                                                               \
     */                                                                     \
    inline constexpr bool                                                   \
    _isInvalid() const noexcept {                                           \
        return _D::isInvalidByIndex(m_index);                               \
    }                                                                       \
                                                                            \
    inline constexpr bool                                                   \
    _isDefault() const noexcept {                                           \
        return _D::isDefaultByIndex(m_index);                               \
    }                                                                       \
                                                                            \
    static inline constexpr bool                                            \
    _isInvalidValueDefined() noexcept {                                     \
        return _D::isInvalidValueDefined();                                 \
    }                                                                       \
                                                                            \
    static inline constexpr bool                                            \
    _isDefaultValueDefined() noexcept {                                     \
        return _D::isDefaultValueDefined();                                 \
    }                                                                       \
                                                                            \
    static inline constexpr _Enum                                           \
    _invalidValue() noexcept {                                              \
        return _D::invalidValue();                                          \
    }                                                                       \
                                                                            \
    static inline constexpr _Enum                                           \
    _defaultValue() noexcept {                                              \
        return _D::defaultValue();                                          \
    }                                                                       \
                                                                            \
    static inline constexpr QqEnumString const &                            \
    _invalidValueName() noexcept {                                          \
        return _D::invalidValueName();                                      \
    }                                                                       \
                                                                            \
    static inline constexpr QqEnumString const &                            \
    _defaultValueName() noexcept {                                          \
        return _D::defaultValueName();                                      \
    }                                                                       \


//
// CTORS
//
#define QP_ENUM_CTORS_IMPL_AS(Int,Class)                \
    inline Class() noexcept {                           \
        m_index = _D::defaultValueIndex();              \
    }                                                   \
                                                        \
    inline explicit Class(int index) noexcept {         \
        m_index = _C::ctor_index(index);                \
    }                                                   \
                                                        \
    inline Class(Class const & other) {                 \
        m_index = _C::ctor_index(other.m_index);        \
    }                                                   \



//
// Operators
//
#define QP_ENUM_OPERATORS_IMPL_AS(Int,Class)        \
                                                    \
    /* Assignment operators */                      \
                                                    \
    constexpr inline Class &                        \
    operator = (_Enum const e) {                    \
        return _C::op_assignment(*this, e);         \
    }                                               \
                                                    \
    constexpr inline Class &                        \
    operator = (Class const & c) {                  \
        return _C::op_assignment(*this, c);         \
    }                                               \


//
// Define special values
//
#define QQ_ENUM_INVALID_VALUE(INVALID_VALUE)                        \
protected:                                                          \
    static inline Qq::Enum::InvalidValueSetterT<_Class,_Enum,_Int>  \
    _invalidValueSetter{ INVALID_VALUE };                           \
public:

#define QQ_ENUM_DEFAULT_VALUE(DEFAULT_VALUE)                        \
protected:                                                          \
    static inline Qq::Enum::DefaultValueSetterT<_Class,_Enum,_Int>  \
    _defaultValueSetter{ DEFAULT_VALUE };                           \
public:
