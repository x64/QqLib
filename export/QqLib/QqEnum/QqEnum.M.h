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
#include "./IterationRangeT.h"
#include "./Consts.h"



#define QP_GET_VALUE_FROM_ITEM(ITEM)    _EatAssign{}         << ITEM  , //-V2561

#ifdef QQ_DONT_USE_QT
    #define QP_GET_NAME_FROM_ITEM(ITEM) _H::parseEnumValueName(#ITEM) ,
#else
    #define QP_GET_NAME_FROM_ITEM(ITEM) QString{ _H::parseEnumValueName(#ITEM).c_str() } ,
#endif


#define QQ_ENUM_CORE(Class,...)         QQ_ENUM_CORE_AS(int, Class, __VA_ARGS__)
#define QQ_ENUM_AS(Int,Class,...)       QQ_ENUM_CORE_AS(Int,Class,__VA_ARGS__)
#define QQ_ENUM(Class,...)              QQ_ENUM_AS(int,Class,__VA_ARGS__)


#define QQ_ENUM_CORE_AS(Int,Class,...)                                      \
public:                                                                     \
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
    using _C               = Qq::Enum::CoreT<_Class,_Enum,_Int>;            \
    using _D               = Qq::Enum::MetadataT<_Class,_Enum,_Int>;        \
    using _H               = Qq::Enum::Helper;                              \
    using _EatAssign       = Qq::Enum::EatAssignT<_Enum, _Int>;             \
    using _Iterator        = Qq::Enum::IteratorT<_Class,_Enum,_Int>;        \
    using _IterationRange  = Qq::Enum::IterationRangeT<_Class,_Enum,_Int>; \
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
                                                                            \
    QP_ENUM_CTORS_IMPL_AS(Int,Class)                                        \
                                                                            \
    QP_ENUM_OPERATORS_IMPL_AS(Int,Class)                                    \
                                                                            \
    /*                                                                      \
     * Metadata                                                             \
     */                                                                     \
                                                                            \
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
     * Bounds API                                                           \
     */                                                                     \
                                                                            \
    static inline _Enum                                                     \
    _first() noexcept {                                                     \
        return _D::firstValue();                                            \
    }                                                                       \
                                                                            \
    static inline _Enum                                                     \
    _last() noexcept {                                                      \
        return _D::lastValue();                                             \
    }                                                                       \
                                                                            \
    static inline constexpr int                                             \
    _count() noexcept {                                                     \
        return _D::count();                                                 \
    }                                                                       \
                                                                            \
    static inline constexpr _Enum                                           \
    _min() noexcept {                                                       \
        return _D::minValue();                                              \
    }                                                                       \
                                                                            \
    static inline constexpr _Enum                                           \
    _max() noexcept {                                                       \
        return _D::maxValue();                                              \
    }                                                                       \
                                                                            \
    /*                                                                      \
     * Names & values access                                                \
     */                                                                     \
                                                                            \
    inline constexpr _Int                                                   \
    _int() const noexcept {                                                 \
        return static_cast<_Int>(_value());                                 \
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
    static constexpr _Wrapper const &                                       \
    _wrapper(int index) noexcept {                                          \
        return _D::wrapper(index, QQ_FULL_FUNC_SIG);                        \
    }                                                                       \
                                                                            \
    /*                                                                      \
     * Lists                                                                \
     */                                                                     \
                                                                            \
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
     * Invalid & Default                                                    \
     */                                                                     \
                                                                            \
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
    _isInvalidDefined() noexcept {                                          \
        return _D::isInvalidValueDefined();                                 \
    }                                                                       \
                                                                            \
    static inline constexpr bool                                            \
    _isDefaultDefined() noexcept {                                          \
        return _D::isDefaultValueDefined();                                 \
    }                                                                       \
                                                                            \
    static inline constexpr _Enum                                           \
    _invalid() noexcept {                                                   \
        return _D::invalidValue();                                          \
    }                                                                       \
                                                                            \
    static inline constexpr _Enum                                           \
    _default() noexcept {                                                   \
        return _D::defaultValue();                                          \
    }                                                                       \
                                                                            \
    static inline constexpr QqEnumString const &                            \
    _invalidName() noexcept {                                               \
        return _D::invalidValueName();                                      \
    }                                                                       \
                                                                            \
    static inline constexpr QqEnumString const &                            \
    _defaultName() noexcept {                                               \
        return _D::defaultValueName();                                      \
    }                                                                       \
                                                                            \
    /*                                                                      \
     * Indexes                                                              \
     */                                                                     \
                                                                            \
    inline constexpr bool                                                   \
    _index() const noexcept {                                               \
        return m_index();                                                   \
    }                                                                       \
                                                                            \
    inline constexpr bool                                                   \
    _invalidIndex() const noexcept {                                        \
        return _D::invalidValueIndex();                                     \
    }                                                                       \
                                                                            \
    inline constexpr bool                                                   \
    _defaultIndex() const noexcept {                                        \
        return _D::defaultValueIndex();                                     \
    }                                                                       \
                                                                            \
    inline constexpr bool                                                   \
    _firstValidIndex() const noexcept {                                     \
        return _D::firstValidIndex();                                       \
    }                                                                       \
                                                                            \
    inline constexpr bool                                                   \
    _lastIndex() const noexcept {                                           \
        return _D::lastValidIndex();                                        \
    }                                                                       \
                                                                            \
    /*                                                                      \
     * Iteration                                                            \
     */                                                                     \
                                                                            \
    inline constexpr _Iterator                                              \
    _iterator() noexcept                                                    \
    {                                                                       \
        return _Iterator{ m_index, Qq::Enum::Const::badIndex };             \
    }                                                                       \
                                                                            \
    static inline constexpr _Iterator                                       \
    _iterator(                                                              \
        int fromIndex,                                                      \
        int toIndex   = Qq::Enum::Const::badIndex                           \
    )                                                                       \
        noexcept                                                            \
    {                                                                       \
        return _Iterator{ fromIndex, toIndex };                             \
    }                                                                       \
                                                                            \
    static inline constexpr _Iterator                                       \
    _iterator(                                                              \
        _Enum from,                                                         \
        _Enum to                                                            \
    )                                                                       \
        noexcept                                                            \
    {                                                                       \
        return _Iterator{ from, to };                                       \
    }                                                                       \
                                                                            \
    static inline constexpr _IterationRange                                 \
    _range() noexcept {                                                     \
        return _IterationRange{ };                                          \
    }                                                                       \
                                                                            \
    static inline constexpr _IterationRange                                 \
    _range(                                                                 \
        int fromIndex,                                                      \
        int toIndex = Qq::Enum::Const::badIndex                             \
    )                                                                       \
        noexcept                                                            \
    {                                                                       \
        return _IterationRange{ fromIndex, toIndex };                       \
    }                                                                       \
                                                                            \
    static inline constexpr _IterationRange                                 \
    _range(                                                                 \
        _Enum from,                                                         \
        _Enum to                                                            \
    )                                                                       \
        noexcept                                                            \
    {                                                                       \
        return _IterationRange{ from, to };                                 \
    }                                                                       \
                                                                            \
                                                                            \
    static inline constexpr _IterationRange                                 \
    _range_r() noexcept {                                                   \
        return _IterationRange{ Qq::Enum::Const::badIndex, 0 };             \
    }                                                                       \
                                                                            \
    static inline constexpr _IterationRange                                 \
    _range_r(                                                               \
        int fromIndex,                                                      \
        int toIndex = Qq::Enum::Const::badIndex                             \
    )                                                                       \
        noexcept                                                            \
    {                                                                       \
        return _IterationRange{ toIndex, fromIndex };                       \
    }                                                                       \
                                                                            \
    static inline constexpr _IterationRange                                 \
    _range_r(                                                               \
        _Enum from,                                                         \
        _Enum to                                                            \
    )                                                                       \
        noexcept                                                            \
    {                                                                       \
        return _IterationRange{ to, from };                                 \
    }                                                                       \
                                                                            \
    /*                                                                      \
     * Parsing                                                              \
     */                                                                     \
                                                                            \
    static inline bool                                                      \
    _tryParse(                                                              \
        char const * str,                                                   \
        Class      * out             = nullptr,                             \
        bool         caseInsensitive = true                                 \
    )                                                                       \
        noexcept                                                            \
    {                                                                       \
        return _C::tryParse(str, out, caseInsensitive);                     \
    }                                                                       \
                                                                            \
    static inline Class                                                     \
    _parse(char const * str, bool caseInsensitive = true)                   \
    {                                                                       \
        return _C::parse(str, caseInsensitive);                             \
    }                                                                       \



//
// CTORS
//
#define QP_ENUM_CTORS_IMPL_AS(Int,Class)                                    \
    inline Class() noexcept {                                               \
        m_index = _D::defaultValueIndex();                                  \
    }                                                                       \
                                                                            \
    inline explicit Class(int index) noexcept {                             \
        m_index = _C::ctor_index(index, QQ_FULL_FUNC_SIG);                  \
    }                                                                       \
                                                                            \
    inline Class(Class const & other) noexcept {                            \
        m_index = _C::ctor_index(other.m_index, QQ_FULL_FUNC_SIG);          \
    }                                                                       \
                                                                            \
    explicit inline Class(_Enum e) noexcept {                               \
        m_index = _C::ctor_enum(e, QQ_FULL_FUNC_SIG);                       \
    }                                                                       \



//
// Operators
//
#define QP_ENUM_OPERATORS_IMPL_AS(Int,Class)                                        \
                                                                                    \
    /* Wrapper operator */                                                          \
    inline _Wrapper const &                                                         \
    operator () (int index = Qq::Enum::Const::badIndex) const noexcept              \
    {                                                                               \
        return _wrapper(index == Qq::Enum::Const::badIndex                          \
                                    ? static_cast<int>(m_index)                     \
                                    : index);                                       \
    }                                                                               \
                                                                                    \
    /* Assignment operators */                                                      \
                                                                                    \
    inline constexpr Class &                                                        \
    operator = (Int i) noexcept {                                                   \
        return _C::op_assignmentInt(*this, i, QQ_FULL_FUNC_SIG);                    \
    }                                                                               \
                                                                                    \
    inline constexpr Class &                                                        \
    operator = (_Enum const e) noexcept {                                           \
        return _C::op_assignmentEnum(*this, e, QQ_FULL_FUNC_SIG);                   \
    }                                                                               \
                                                                                    \
    inline constexpr Class &                                                        \
    operator = (Class const & other) noexcept {                                     \
        return _C::op_assignmentOther(*this, other, QQ_FULL_FUNC_SIG);              \
    }                                                                               \
                                                                                    \
    /* Comparsion operators */                                                      \
                                                                                    \
    friend inline bool                                                              \
    operator == (Class const & lh, _Enum e) noexcept {                              \
        return _C::op_compare(lh.m_index, e);                                       \
    }                                                                               \
                                                                                    \
    friend inline bool                                                              \
    operator == (_Enum e, Class const & rh) noexcept {                              \
        return _C::op_compare(rh.m_index, e);                                       \
    }                                                                               \
                                                                                    \
    friend inline bool                                                              \
    operator != (Class const & lh, _Enum e) noexcept {                              \
        return not _C::op_compare(lh.m_index, e);                                   \
    }                                                                               \
                                                                                    \
    friend inline bool                                                              \
    operator != (_Enum e, Class const & rh) noexcept {                              \
        return not _C::op_compare(rh.m_index, e);                                   \
    }                                                                               \
                                                                                    \
    friend inline bool                                                              \
    operator == (Class const & lh, Class const & rh) noexcept {                     \
        return lh.m_index == rh.m_index;                                            \
    }                                                                               \
                                                                                    \
    friend inline bool                                                              \
    operator != (Class const & lh, Class const & rh) noexcept {                     \
        return not (lh.m_index == rh.m_index);                                      \
    }                                                                               \
                                                                                    \
    /* operator > */                                                                \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator > (Class const & lh, Class const & rh) noexcept {                      \
        return _D::value(lh.m_index) > _D::value(rh.m_index);                       \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator > (Class const & lh, _Int i) noexcept {                                \
        return _D::value(lh.m_index) > i;                                           \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator > (_Int i, Class const & rh) noexcept {                                \
        return i > _D::value(rh.m_index);                                           \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator > (Class const & lh, _Enum e) noexcept {                               \
        return _D::value(lh.m_index) > e;                                           \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator > (_Enum e, Class const & rh) noexcept {                               \
        return e > _D::value(rh.m_index);                                           \
    }                                                                               \
                                                                                    \
    /* operator < */                                                                \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator < (Class const & lh, Class const & rh) noexcept {                      \
        return _D::value(lh.m_index) < _D::value(rh.m_index);                       \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator < (Class const & lh, _Int i) noexcept {                                \
        return _D::value(lh.m_index) < i;                                           \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator < (_Int i, Class const & rh) noexcept {                                \
        return i < _D::value(rh.m_index);                                           \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator < (Class const & lh, _Enum e) noexcept {                               \
        return _D::value(lh.m_index) < e;                                           \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator < (_Enum e, Class const & rh) noexcept {                               \
        return e < _D::value(rh.m_index);                                           \
    }                                                                               \
                                                                                    \
    /* operator >= */                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator >= (Class const & lh, Class const & rh) noexcept {                     \
        return _D::value(lh.m_index) >= _D::value(rh.m_index);                      \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator >= (Class const & lh, _Int i) noexcept {                               \
        return _D::value(lh.m_index) >= i;                                          \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator >= (_Int i, Class const & rh) noexcept {                               \
        return i >= _D::value(rh.m_index);                                          \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator >= (Class const & lh, _Enum e) noexcept {                              \
        return _D::value(lh.m_index) >= e;                                          \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator >= (_Enum e, Class const & rh) noexcept {                              \
        return e >= _D::value(rh.m_index);                                          \
    }                                                                               \
                                                                                    \
    /* operator <= */                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator <= (Class const & lh, Class const & rh) noexcept {                     \
        return _D::value(lh.m_index) <= _D::value(rh.m_index);                      \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator <= (Class const & lh, _Int i) noexcept {                               \
        return _D::value(lh.m_index) <= i;                                          \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator <= (_Int i, Class const & rh) noexcept {                               \
        return i <= _D::value(rh.m_index);                                          \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator <= (Class const & lh, _Enum e) noexcept {                              \
        return _D::value(lh.m_index) <= e;                                          \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator <= (_Enum e, Class const & rh) noexcept {                              \
        return e <= _D::value(rh.m_index);                                          \
    }                                                                               \
                                                                                    \
    /* ADD operators */                                                             \
                                                                                    \
    friend inline Class                                                             \
    operator + (Class lh, Class const & rh) noexcept {                              \
        return _C::op_add(lh, rh, QQ_FULL_FUNC_SIG);                                \
    }                                                                      \
                                                                                    \
    friend inline Class                                                             \
    operator + (Class lh, int n) noexcept {                                         \
        return _C::op_add(lh, n, QQ_FULL_FUNC_SIG);                        \
    }                                                                               \
                                                                                    \
    /* ADD & assignment operators */                                                \
                                                                                    \
    inline Class &                                                                  \
    operator += (int n) noexcept {                                                  \
        _C::op_add_assignment(m_index, n, QQ_FULL_FUNC_SIG);                        \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    inline Class &                                                                  \
    operator += (Class const & other) noexcept {                                    \
        m_index = _C::op_add_assignment(m_index, other.m_index, QQ_FULL_FUNC_SIG);  \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    /* INC operators */                                                             \
                                                                                    \
    inline Class &                                                                  \
    operator ++ () noexcept                                                         \
    {                                                                               \
        m_index = _C::op_inc(m_index, QQ_FULL_FUNC_SIG);                            \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    inline Class                                                                    \
    operator ++ (int) noexcept                                                      \
    {                                                                               \
        Class prev{ m_index };                                                      \
        m_index = _C::op_inc(m_index, QQ_FULL_FUNC_SIG);                            \
        return prev;                                                                \
    }                                                                               \
                                                                                    \
    /* SUB operators */                                                             \
                                                                                    \
    friend inline Class                                                             \
    operator - (Class lh, Class const & rh) noexcept {                              \
        return _C::op_sub(lh, rh, QQ_FULL_FUNC_SIG);                                \
    }                                                                               \
                                                                                    \
    friend inline Class                                                             \
    operator - (Class lh, int n) noexcept {                                         \
        return _C::op_sub(lh, n, QQ_FULL_FUNC_SIG);                                 \
    }                                                                               \
                                                                                    \
    /* SUB & assignment operators */                                                \
                                                                                    \
    inline Class &                                                                  \
    operator -= (int n) noexcept {                                                  \
        _C::op_sub_assignment(m_index, n, QQ_FULL_FUNC_SIG);                        \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    inline Class &                                                                  \
    operator -= (Class const & other) noexcept {                                    \
        m_index = _C::op_sub_assignment(m_index, other.m_index, QQ_FULL_FUNC_SIG);  \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    /* DEC operators */                                                             \
                                                                                    \
    inline Class &                                                                  \
    operator -- () noexcept                                                         \
    {                                                                               \
        m_index = _C::op_dec(m_index, QQ_FULL_FUNC_SIG);                            \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    inline Class                                                                    \
    operator -- (int) noexcept                                                      \
    {                                                                               \
        Class prev{ m_index };                                                      \
        m_index = _C::op_dec(m_index, QQ_FULL_FUNC_SIG);                            \
        return prev;                                                                \
    }                                                                               \
                                                                                    \



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
