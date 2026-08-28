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

#define qq_enum struct


#define QQ_ENUM_CORE(Class,...)         QQ_ENUM_CORE_AS(int, Class, __VA_ARGS__)
#define QQ_ENUM_AS(Int,Class,...)       QQ_ENUM_CORE_AS(Int,Class,__VA_ARGS__)
#define QQ_ENUM(Class,...)              QQ_ENUM_AS(int,Class,__VA_ARGS__)


#define QQ_ENUM_CORE_AS(Int,Class,...)                                      \
public:                                                                     \
    enum  : bool { _isQqEnum = true };                                      \
    using _Class = Class;                                                   \
    enum  _Enum  : Int { __VA_ARGS__ };                                     \
    using _Int   = Int;                                                     \
    using _      = _Enum;                                                   \
                                                                            \
    using _Wrapper         = Qq::Enum::EnumItemWrapperT<_Enum,_Int>;        \
    using _Iterator        = Qq::Enum::IteratorT<_Class,_Enum,_Int>;        \
    using _IterationRange  = Qq::Enum::IterationRangeT<_Class,_Enum,_Int>;  \
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
    /*                                                                      \
     * OPERATORS                                                            \
     */                                                                     \
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
    _fullClassName() noexcept {                                             \
        return _D::fullClassName();                                         \
    }                                                                       \
                                                                            \
    static inline char const *                                              \
    _intTypeName() noexcept {                                               \
        return _D::intTypeName();                                           \
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
    static inline constexpr size_t                                          \
    _count() noexcept {                                                     \
        return _D::count();                                                 \
    }                                                                       \
                                                                            \
    /*                                                                      \
     * Min & Max values                                                     \
     */                                                                     \
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
    _name() const {                                                         \
        return _D::name(m_index, QQ_FULL_FUNC_SIG);                         \
    }                                                                       \
                                                                            \
    static inline constexpr QqEnumString const &                            \
    _nameByValue(_Enum const e) {                                           \
        return _D::nameByValue(e, QQ_FULL_FUNC_SIG);                        \
    }                                                                       \
                                                                            \
    static constexpr _Wrapper const &                                       \
    _wrapper(int index) {                                                   \
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
    _invalid() {                                                            \
        return _D::invalidValue(QQ_FULL_FUNC_SIG);                          \
    }                                                                       \
                                                                            \
    static inline constexpr _Enum                                           \
    _default() {                                                            \
        return _D::defaultValue(QQ_FULL_FUNC_SIG);                          \
    }                                                                       \
                                                                            \
    static inline constexpr QqEnumString const &                            \
    _invalidName() {                                                        \
        return _D::invalidValueName(QQ_FULL_FUNC_SIG);                      \
    }                                                                       \
                                                                            \
    static inline constexpr QqEnumString const &                            \
    _defaultName() {                                                        \
        return _D::defaultValueName(QQ_FULL_FUNC_SIG);                      \
    }                                                                       \
                                                                            \
    /*                                                                      \
     * Indexes                                                              \
     */                                                                     \
                                                                            \
    inline int                                                              \
    _index() const noexcept {                                               \
        return m_index();                                                   \
    }                                                                       \
                                                                            \
    static inline constexpr int                                             \
    _invalidIndex() noexcept {                                              \
        return _D::invalidValueIndex();                                     \
    }                                                                       \
                                                                            \
    static inline constexpr int                                             \
    _defaultIndex() noexcept {                                              \
        return _D::defaultValueIndex();                                     \
    }                                                                       \
                                                                            \
    static inline constexpr int                                             \
    _firstValidIndex() noexcept {                                           \
        return _D::firstValidindex();                                       \
    }                                                                       \
                                                                            \
    static inline constexpr int                                             \
    _lastValidIndex() noexcept {                                            \
        return _D::lastValidIndex();                                        \
    }                                                                       \
                                                                            \
    static inline constexpr int                                             \
    _lastIndex() noexcept {                                                 \
        return _D::lastIndex();                                             \
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
        return _C::parse(str, caseInsensitive, QQ_FULL_FUNC_SIG);           \
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
    inline Class(_Enum e) noexcept {                                        \
        m_index = _C::ctor_enum(e, QQ_FULL_FUNC_SIG);                       \
    }                                                                       \



//
// Operators
//
#define QP_ENUM_OPERATORS_IMPL_AS(Int,Class)                                        \
                                                                                    \
    /* Wrapper operator */                                                          \
    inline _Wrapper const &                                                         \
    operator () (int index = Qq::Enum::Const::badIndex) const                       \
    {                                                                               \
        return _wrapper(index == Qq::Enum::Const::badIndex                          \
                                    ? static_cast<int>(m_index)                     \
                                    : index);                                       \
    }                                                                               \
                                                                                    \
    /* Assignment operators */                                                      \
                                                                                    \
    inline constexpr Class &                                                        \
    operator = (Int enumAsInt) {                                                    \
        return _C::op_assignmentInt(*this, enumAsInt, QQ_FULL_FUNC_SIG);            \
    }                                                                               \
                                                                                    \
    inline constexpr Class &                                                        \
    operator = (_Enum e) {                                                          \
        return _C::op_assignmentEnum(*this, e, QQ_FULL_FUNC_SIG);                   \
    }                                                                               \
                                                                                    \
    inline constexpr Class &                                                        \
    operator = (Class const & other) noexcept {                                     \
        return _C::op_assignmentOther(*this, other);                                \
    }                                                                               \
                                                                                    \
    /* Comparsion operators */                                                      \
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
    friend inline bool                                                              \
    operator == (Class const & c, _Enum e) noexcept {                               \
        return c._value() == e;                                                     \
    }                                                                               \
                                                                                    \
    friend inline bool                                                              \
    operator != (Class const & c, _Enum e) noexcept {                               \
        return not (c._value() == e);                                               \
    }                                                                               \
                                                                                    \
    /* operator > */                                                                \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator > (Class const & lh, Class const & rh) noexcept {                      \
        return lh._value() > rh._value();                                           \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator > (Class const & c, _Int i) noexcept {                                 \
        return c._int() > i;                                                        \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator > (_Int i, Class const & c) noexcept {                                 \
        return i > c._int();                                                        \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator > (Class const & c, _Enum e) noexcept {                                \
        return c._value() > e;                                                      \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator > (_Enum e, Class const & c) noexcept {                                \
        return e > c._value();                                                      \
    }                                                                               \
                                                                                    \
    /* operator < */                                                                \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator < (Class const & lh, Class const & rh) noexcept {                      \
        return lh._value() < rh._value();                                           \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator < (Class const & c, _Int i) noexcept {                                 \
        return c._int() < i;                                                        \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator < (_Int i, Class const & c) noexcept {                                 \
        return i < c._int();                                                        \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator < (Class const & c, _Enum e) noexcept {                                \
        return c._value() < e;                                                      \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator < (_Enum e, Class const & c) noexcept {                                \
        return e < c._value();                                                      \
    }                                                                               \
                                                                                    \
    /* operator >= */                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator >= (Class const & lh, Class const & rh) noexcept {                     \
        return lh._value() >= rh._value();                                          \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator >= (Class const & c, _Int i) noexcept {                                \
        return c._int() >= i;                                                       \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator >= (_Int i, Class const & c) noexcept {                                \
        return i >= c._int();                                                       \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator >= (Class const & c, _Enum e) noexcept {                               \
        return c._value() >= e;                                                     \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator >= (_Enum e, Class const & c) noexcept {                               \
        return e >= c._value();                                                     \
    }                                                                               \
                                                                                    \
    /* operator <= */                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator <= (Class const & lh, Class const & rh) noexcept {                     \
        return lh._value() <= rh._value();                                          \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator <= (Class const & c, _Int i) noexcept {                                \
        return c._int() <= i;                                                       \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator <= (_Int i, Class const & c) noexcept {                                \
        return i <= c._int();                                                       \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator <= (Class const & c, _Enum e) noexcept {                               \
        return c._value() <= e;                                                     \
    }                                                                               \
                                                                                    \
    friend inline constexpr bool                                                    \
    operator <= (_Enum e, Class const & c) noexcept {                               \
        return e <= c._value();                                                     \
    }                                                                               \
                                                                                    \
    /* ADD operators */                                                             \
                                                                                    \
    friend inline Class                                                             \
    operator + (Class const & lh, Class const & rh) {                               \
        Class c{ lh };                                                              \
        return _C::op_add(c, rh);                                                   \
    }                                                                               \
                                                                                    \
    friend inline Class                                                             \
    operator + (Class const & c, int n)                                             \
    {                                                                               \
        Class cc{ c };                                                              \
        return _C::op_add(cc, n, QQ_FULL_FUNC_SIG);                                 \
    }                                                                               \
                                                                                    \
    friend inline Class                                                             \
    operator + (int n, Class const & c)                                             \
    {                                                                               \
        Class cc{ c };                                                              \
        return _C::op_add(cc, n, QQ_FULL_FUNC_SIG);                                 \
    }                                                                               \
                                                                                    \
    /* ADD & assignment operators */                                                \
                                                                                    \
    inline Class &                                                                  \
    operator += (int n)                                                             \
    {                                                                               \
        _C::op_add_assignment(m_index, n, QQ_FULL_FUNC_SIG);                        \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    inline Class &                                                                  \
    operator += (Class const & other)                                               \
    {                                                                               \
        m_index = _C::op_add_assignment(m_index, other.m_index, QQ_FULL_FUNC_SIG);  \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    /* INC operators */                                                             \
                                                                                    \
    inline Class &                                                                  \
    operator ++ ()                                                                  \
    {                                                                               \
        m_index = _C::op_inc(m_index, QQ_FULL_FUNC_SIG);                            \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    inline Class                                                                    \
    operator ++ (int)                                                               \
    {                                                                               \
        Class prev{ m_index };                                                      \
        m_index = _C::op_inc(m_index, QQ_FULL_FUNC_SIG);                            \
        return prev;                                                                \
    }                                                                               \
                                                                                    \
    /* SUB operators */                                                             \
                                                                                    \
    friend inline Class                                                             \
    operator - (Class const & lh, Class const & rh) {                               \
        Class cc{ lh };                                                             \
        return _C::op_sub(cc, rh, QQ_FULL_FUNC_SIG);                                \
    }                                                                               \
                                                                                    \
    friend inline Class                                                             \
    operator - (Class const & c, int n)                                             \
    {                                                                               \
        Class cc{ c };                                                              \
        return _C::op_sub(cc, n, QQ_FULL_FUNC_SIG);                                 \
    }                                                                               \
                                                                                    \
    friend inline Class                                                             \
    operator - (int n, Class const & c)                                             \
    {                                                                               \
        Class cc{ c };                                                              \
        return _C::op_sub(cc, n, QQ_FULL_FUNC_SIG);                                 \
    }                                                                               \
                                                                                    \
    /* SUB & assignment operators */                                                \
                                                                                    \
    inline Class &                                                                  \
    operator -= (int n)                                                             \
    {                                                                               \
        _C::op_sub_assignment(m_index, n, QQ_FULL_FUNC_SIG);                        \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    inline Class &                                                                  \
    operator -= (Class const & other)                                               \
    {                                                                               \
        m_index = _C::op_sub_assignment(m_index, other.m_index, QQ_FULL_FUNC_SIG);  \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    /* DEC operators */                                                             \
                                                                                    \
    inline Class &                                                                  \
    operator -- ()                                                                  \
    {                                                                               \
        m_index = _C::op_dec(m_index, QQ_FULL_FUNC_SIG);                            \
        return *this;                                                               \
    }                                                                               \
                                                                                    \
    inline Class                                                                    \
    operator -- (int)                                                               \
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
