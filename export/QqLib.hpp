// Automatically generated using `amalgamate.py`
#pragma once

// >>> START OF FILE: QqEnum.h <<<

// >>> START OF FILE: QqEnum/QqEnum.M.h <<<


// >>> START OF FILE: QqEnum/_CompileConfig.h <<<

//
// define QQ_DONT_USE_QT_CONTAINERS for switch to std types
//

#define QQ_DONT_USE_QT
//#undef QQ_DONT_USE_QT


#ifdef QQ_DONT_USE_QT
    #define QqMap                      std::map
    #define QqList                     std::vector
#else
    #define QqMap                      QMap
    #define QqList                     QList
    // #define Qq_string                  QString
    // #define Qq_stringLiteral(TEXT)     QStringLiteral(TEXT)
    // #define QQ_ENUM_STRING_INCLUDE     <QString>
#endif
// <<< END OF FILE: QqEnum/_CompileConfig.h <<<

// >>> START OF FILE: QqEnum/QqEnumString.h <<<



#ifdef QQ_DONT_USE_QT
    #include <string>
    using QqEnumString = std::string;
#else
    #include <QString>
    using QqEnumString = QString;
#endif
// <<< END OF FILE: QqEnum/QqEnumString.h <<<


// >>> START OF FILE: Macros/_MainMacro.M.h <<<

//
// This file must be included first for all MACRO files
//

// Variadics macro:
//#define BOOST_PP_LIMIT_VARIADIC 124

# if defined _MSC_VER && _MSC_VER >= 1400 && !defined(__clang__) && (defined(__INTELLISENSE__) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1700) || !(defined __EDG__ || defined __GCCXML__ || defined __PATHSCALE__ || defined __DMC__ || defined __CODEGEARC__ || defined __BORLANDC__ || defined __MWERKS__ || defined __SUNPRO_CC || defined __HP_aCC || defined __MRC__ || defined __SC__ || defined __IBMCPP__ || defined __PGI)) && (!defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL)
#     define QQ_PP_VARIADICS_MSVC 1
# else
#     define QQ_PP_VARIADICS_MSVC 0
# endif


#if defined _MSC_VER
    #define QQ_FULL_FUNC_SIG    __FUNCSIG__
#else
    #define QQ_FULL_FUNC_SIG    __PRETTY_FUNCTION__
#endif
// <<< END OF FILE: Macros/_MainMacro.M.h <<<

// >>> START OF FILE: Macros/Variadic/ForEach.M.h <<<


// BASED ON: https://www.scs.stanford.edu/~dm/blog/va-opt.html
// On MSVC 2017  you need to add the "/experimental:preprocessor" compiler option
// On MSVC 2019+ you need to add the "/Zc:preprocessor" compiler option


#define QP_FOREACH_PARENS ()

#define QP_FOREACH_EXPAND(...)              QP_FOREACH_EXPAND4(QP_FOREACH_EXPAND4(QP_FOREACH_EXPAND4(QP_FOREACH_EXPAND4(__VA_ARGS__))))
#define QP_FOREACH_EXPAND4(...)             QP_FOREACH_EXPAND3(QP_FOREACH_EXPAND3(QP_FOREACH_EXPAND3(QP_FOREACH_EXPAND3(__VA_ARGS__))))
#define QP_FOREACH_EXPAND3(...)             QP_FOREACH_EXPAND2(QP_FOREACH_EXPAND2(QP_FOREACH_EXPAND2(QP_FOREACH_EXPAND2(__VA_ARGS__))))
#define QP_FOREACH_EXPAND2(...)             QP_FOREACH_EXPAND1(QP_FOREACH_EXPAND1(QP_FOREACH_EXPAND1(QP_FOREACH_EXPAND1(__VA_ARGS__))))
#define QP_FOREACH_EXPAND1(...)             __VA_ARGS__

#define QQ_PP_FOREACH(macro,...)            __VA_OPT__(QP_FOREACH_EXPAND(QP_FOREACH_HELPER(macro,__VA_ARGS__)))

#define QP_FOREACH_HELPER(macro,a1,...)     macro(a1) __VA_OPT__(QP_FOREACH_AGAIN QP_FOREACH_PARENS(macro,__VA_ARGS__))
//#define QP_FOREACH(macro,...)             QP_FOREACH_EXPAND(QP_FOREACH_HELPER(macro,__VA_ARGS__))
//#define QP_FOREACH_HELPER(macro,a1,...)   macro(a1) QP_FOREACH_AGAIN QP_FOREACH_PARENS(macro,__VA_ARGS__)

#define QP_FOREACH_AGAIN()                  QP_FOREACH_HELPER

//
// Example: QP_PP_FOREACH(macro, a1, a2, a3, a4) => macro(a1), macro(a2), macro(a3), macro(a4)
// Note: the last element of the macro body must be "," (comma)
//



//
// With payload 'data':
//
#define QQ_PP_FOREACH_PL(macro,data,...)            __VA_OPT__(QP_FOREACH_EXPAND(QP_FOREACH_PL_HELPER(macro,data,__VA_ARGS__)))

#define QP_FOREACH_PL_HELPER(macro,data,a1,...)     macro(data,a1) __VA_OPT__(QP_FOREACH_PL_AGAIN QP_FOREACH_PARENS(macro,data,__VA_ARGS__))
#define QQ_PP_FOREACH_PL2(data,macro,...)           __VA_OPT__(QP_FOREACH_EXPAND(QP_FOREACH_PL_HELPER(macro,data,__VA_ARGS__)))
#define QP_FOREACH_PL2_HELPER(macro,data,a1,...)    macro(data,a1) __VA_OPT__(QP_FOREACH_PL_AGAIN QP_FOREACH_PARENS(macro,data,__VA_ARGS__))

#define QP_FOREACH_PL_AGAIN()                       QP_FOREACH_PL_HELPER

//
// Example: QQ_PP_FOREACH_PL(macro, data, a1, a2, a3, a4) => macro(data,a1), macro(data,a2), macro(data,a3), macro(data,a4)
// Note: the last element of the macro body must be "," (comma)
//
// <<< END OF FILE: Macros/Variadic/ForEach.M.h <<<

// >>> START OF FILE: Macros/Variadic/Size.M.h <<<


// >>> START OF FILE: Macros/Cat.M.h <<<



#define QQ_PP_CAT(a, b) QP_PP_CAT_I(a, b)

#define QP_PP_CAT_I(a, b) QP_PP_CAT_II(~, a ## b) //~ #define QP_PP_CAT_I(a, b) a ## b

#define QP_PP_CAT_II(p, res) res
// <<< END OF FILE: Macros/Cat.M.h <<<

// >>> START OF FILE: Macros/Expand.M.h <<<



#define QQ_PP_EXPAND(x)     QQ_PP_EXPAND_I(x)
#define QQ_PP_EXPAND_I(x)   x
// <<< END OF FILE: Macros/Expand.M.h <<<



// # if QQ_PP_VARIADICS_MSVC
// #   define QQ_PP_VARIADIC_SIZE(...)                                                                     \
//         QQ_PP_CAT(QQ_PP_VARIADIC_SIZE_I(                                                                \
//                     __VA_ARGS__,       124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113,      \
//                    112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98,  97,      \
//                     96,  95,  94,  93,  92,  91,  90,  89,  88,  87,  86,  85,  84,  83,  82,  81,      \
//                     80,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66,  65,      \
//                     64,  63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  52,  51,  50,  49,      \
//                     48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,  37,  36,  35,  34,  33,      \
//                     32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,      \
//                     16,  15,  14,  13,  12,  11,  10,   9,   8,   7,   6,   5,   4,   3,   2,   1,),)
// # else
// #   define QQ_PP_VARIADIC_SIZE(...)                                                                     \
//     QQ_PP_VARIADIC_SIZE_I(                                                                              \
//         __VA_ARGS__,        124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113,                 \
//         112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98,  97,                 \
//          96,  95,  94,  93,  92,  91,  90,  89,  88,  87,  86,  85,  84,  83,  82,  81,                 \
//          80,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66,  65,                 \
//          64,  63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  52,  51,  50,  49,                 \
//          48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,  37,  36,  35,  34,  33,                 \
//          32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,                 \
//          16,  15,  14,  13,  12,  11,  10,   9,   8,   7,   6,   5,   4,   3,   2,   1,)
// # endif

# define QQ_PP_VARIADIC_SIZE_I(                                                                         \
      e0,   e1,   e2,   e3,   e4,   e5,   e6,   e7,   e8,   e9,  e10,  e11,  e12,  e13,  e14,  e15,     \
     e16,  e17,  e18,  e19,  e20,  e21,  e22,  e23,  e24,  e25,  e26,  e27,  e28,  e29,  e30,  e31,     \
     e32,  e33,  e34,  e35,  e36,  e37,  e38,  e39,  e40,  e41,  e42,  e43,  e44,  e45,  e46,  e47,     \
     e48,  e49,  e50,  e51,  e52,  e53,  e54,  e55,  e56,  e57,  e58,  e59,  e60,  e61,  e62,  e63,     \
     e64,  e65,  e66,  e67,  e68,  e69,  e70,  e71,  e72,  e73,  e74,  e75,  e76,  e77,  e78,  e79,     \
     e80,  e81,  e82,  e83,  e84,  e85,  e86,  e87,  e88,  e89,  e90,  e91,  e92,  e93,  e94,  e95,     \
     e96,  e97,  e98,  e99, e100, e101, e102, e103, e104, e105, e106, e107, e108, e109, e110, e111,     \
    e112, e113, e114, e115, e116, e117, e118, e119, e120, e121, e122, e123,                             \
    size, ...) size

#define QQ_PP_VARIADIC_SIZE_HELPER(...)    QQ_PP_EXPAND(QQ_PP_VARIADIC_SIZE_I(__VA_ARGS__))

#define QQ_PP_VARIADIC_SIZE(...)           (QQ_PP_EXPAND(QQ_PP_VARIADIC_SIZE_HELPER(0, ##__VA_ARGS__,       \
                                       124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113,          \
                   112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98,  97,          \
                    96,  95,  94,  93,  92,  91,  90,  89,  88,  87,  86,  85,  84,  83,  82,  81,          \
                    80,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66,  65,          \
                    64,  63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  52,  51,  50,  49,          \
                    48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,  37,  36,  35,  34,  33,          \
                    32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,          \
                    16,  15,  14,  13,  12,  11,  10,   9,   8,   7,   6,   5,   4,   3,   2,   1, 0)) -1)  \
// <<< END OF FILE: Macros/Variadic/Size.M.h <<<


// >>> START OF FILE: QqEnum/EnumItemWrapperT.h <<<



// >>> START OF FILE: QqEnum/Consts.h <<<


//
// Consts for m_wrappers.m_index
//

namespace Qq::Enum::Const
{

enum Index : int
{
    badIndex = -1
};

enum Mask : int
{
    invlaidValueMask  = 0x00ff0000,
    defaultValueMask  = 0x0000ff00,
    indexMask         = 0x000000ff
};

enum Shift : int
{
    invalidValueShift = 16,
    defaultValueShift = 8
};



} // namespace Qq::Enum::Const
// <<< END OF FILE: QqEnum/Consts.h <<<


namespace Qq::Enum
{


//
// \brief Tuple for the enum value and the name enum.
//
template <typename TEnum, typename TInt>
class EnumItemWrapperT
{
//
// Friends
//
    template <typename T_Class, typename T_Enum, typename T_Int>
    friend struct MetadataT;

//
// CTORs
//
public:
    EnumItemWrapperT(int index, TEnum value, QqEnumString const & name)
        : m_index{ index  }
        , m_value{ value  }
        , m_pName{ & name }
    {}

    EnumItemWrapperT(
        int                  index,
        TEnum                value,
        QqEnumString const & name,
        int                  invalidValueIndex,
        int                  defaultValueIndex
    )
        : m_value{ value  }
        , m_pName{ & name }
    {
        m_index = index & Const::indexMask
                  | invalidValueIndex << Const::invalidValueShift
                  | defaultValueIndex << Const::defaultValueShift;
    }

    EnumItemWrapperT() = default;

//
// Operators
//
public:
    //
    // Comparsions
    //
    inline constexpr bool
    operator == (EnumItemWrapperT const & other) const noexcept
    {
        return m_value == other.m_value;
    }

    inline constexpr bool
    operator == (TEnum const & otherEnum) const noexcept
    {
        return m_value == otherEnum;
    }

    inline constexpr bool
    operator != (EnumItemWrapperT const & other) const noexcept
    {
        return not (m_value == other.m_value);
    }

    inline constexpr bool
    operator != (TEnum const & otherEnum) const noexcept
    {
        return not (m_value == otherEnum);
    }

    inline constexpr bool
    operator < (EnumItemWrapperT const & other) const noexcept
    {
        return m_value < other.m_value;
    }

    inline constexpr bool
    operator < (TEnum const & otherEnum) const noexcept
    {
        return m_value < otherEnum;
    }

    inline constexpr bool
    operator > (EnumItemWrapperT const & other) const noexcept
    {
        return m_value > other.m_value;
    }

    inline constexpr bool
    operator > (TEnum const & otherEnum) const noexcept
    {
        return m_value > otherEnum;
    }

    //
    // Comparsion & assignment
    //
    inline constexpr bool
    operator <= (EnumItemWrapperT const & other) const noexcept
    {
        return m_value <= other.m_value;
    }

    inline constexpr bool
    operator <= (TEnum const & otherEnum) const noexcept
    {
        return m_value <= otherEnum;
    }

    inline constexpr bool
    operator >= (EnumItemWrapperT const & other) const noexcept
    {
        return m_value >= other.m_value;
    }

    inline constexpr bool
    operator >= (TEnum const & otherEnum) const noexcept
    {
        return m_value >= otherEnum;
    }

//
// Const Data API
//
public:
    inline constexpr TEnum
    value() const noexcept
    {
        return m_value;
    }

    inline constexpr QqEnumString const &
    name() const noexcept
    {
        return *m_pName;
    }

    inline constexpr int
    index() const noexcept
    {
        return m_index & Const::indexMask;
    }

    inline constexpr TInt
    asInt() const noexcept
    {
        return static_cast<TInt>(value());
    }

    inline constexpr bool
    isInvalid() const noexcept
    {
        return index() == (m_index >> Const::invalidValueShift);
    }

    inline constexpr bool
    isDefault() const noexcept
    {
        return index() == (m_index >> Const::defaultValueShift);
    }

//
// Fields
//
    int                  m_index;
    TEnum                m_value;
    QqEnumString const * m_pName = nullptr;

};


} // namespace Qq::Enum

// >>> START OF FILE: QqEnum/MetadataT.h <<<

// >>> START OF FILE: QqEnum/QqEnumStringLiteral.h <<<


#include <vector>


#ifdef QQ_DONT_USE_QT
namespace Qq::Enum
{


class StringLiteral
{
protected:
    std::string m_str;
    int         m_currentArgNum = 1;

//
// ctor & dtor
//
public:
    StringLiteral(char const * str)
        : m_str{ str }
    {
        m_str.reserve(m_str.size() * 2);
    }

//
// Public API
//
public:
    inline char const * toLatin1() const noexcept
    {
        return m_str.c_str();
    }

//
// arg(*) methods
//
    inline StringLiteral & arg(int const arg) noexcept
    {
        return argCore(std::to_string(arg).c_str());
    }

    inline StringLiteral & arg(unsigned int const arg) noexcept
    {
        return argCore(std::to_string(arg).c_str());
    }

    inline StringLiteral & arg(long const arg) noexcept
    {
        return argCore(std::to_string(arg).c_str());
    }

    inline StringLiteral & arg(unsigned long const arg) noexcept
    {
        return argCore(std::to_string(arg).c_str());
    }

    inline StringLiteral & arg(long long const arg) noexcept
    {
        return argCore(std::to_string(arg).c_str());
    }

    inline StringLiteral & arg(unsigned long long const arg) noexcept
    {
        return argCore(std::to_string(arg).c_str());
    }

    inline StringLiteral & arg(double const arg) noexcept
    {
        return argCore(std::to_string(arg).c_str());
    }

    inline StringLiteral & arg(float const arg) noexcept
    {
        return argCore(std::to_string(arg).c_str());
    }

    inline StringLiteral & arg(long double const arg) noexcept
    {
        return argCore(std::to_string(arg).c_str());
    }

    inline StringLiteral & arg(char const * argStr) noexcept
    {
        return argCore(argStr);
    }

    inline StringLiteral & arg(std::string const & argStr) noexcept
    {
        return argCore(argStr.c_str());
    }

protected:
    inline StringLiteral & argCore(char const * str) noexcept
    {
        return * replaceAllEntries(m_currentArgNum++, str, this);
    }


//
// Non public API
//
protected:
    static StringLiteral *
    replaceAllEntries(int argNum, char const * replaceStr, StringLiteral * esl)
    {
        auto & sl  = * esl;
        auto & str = sl.m_str;

        for (int i = static_cast<int>(str.size()) -1; i >= 0; --i)
        {
            if ('%' == str[i] && i < str.size()-1)
            {
                int replaceCharCount;
                if (argNum != getArgNum(i+1, str, & replaceCharCount))
                    continue;

                str.replace(i, 1+replaceCharCount, replaceStr);
            }
        }

        return esl;
    }

    static int
    getArgNum(int const beginPos, std::string const str, int * replaceCharCount) noexcept
    {
        int               i = beginPos;
        std::vector<char> buff;

        buff.reserve(8);

        char ch;
        while ( std::isdigit(ch = str[i]) )
        {
            buff.push_back(ch);
            ++i;
        }

        if (nullptr != replaceCharCount)
            *replaceCharCount = static_cast<int>(buff.size());

        return std::atoi(buff.data());
    }

};


} // namespace Qq::Enum

using QqEnumStringLiteral = Qq::Enum::StringLiteral;

#else

#include <QStringLiteral>
using QqEnumStringLiteral = QString;

#endif
// <<< END OF FILE: QqEnum/QqEnumStringLiteral.h <<<



// >>> START OF FILE: QqEnum/Helper.h <<<

#include <vector>
#include <map>



// >>> START OF FILE: Helpers/Main.h <<<

#include <string>


namespace Qq::Helpers
{


struct Main
{
    static std::string
    trim(char const * str)
    {
        int count = static_cast<int>(std::strlen(str));

        int i = 0;

        for (; std::isspace(str[i]) && i < count; ++i)
        ;
        int beginPos = i;

        i = count - 1;
        for (; std::isspace(str[i]) && i >=0 ; --i)
        ;
        int lastPos = i;

        int         len = 1 + lastPos - beginPos;
        std::string res(str + beginPos, len);

        return res;
    }

    static std::string &
    toUpper(std::string && str)
    {
        for (auto & ch : str)
            ch = std::toupper(ch);

        return str;
    }

    static std::string &
    toUpper(std::string & str)
    {
        return toUpper(std::move(str));
    }

    static std::string &
    toLower(std::string && str)
    {
        for (auto & ch : str)
            ch = std::tolower(ch);

        return str;
    }

    static std::string &
    toLower(std::string & str)
    {
        return toLower(std::move(str));
    }


    template <typename TInt,
              std::enable_if_t<std::is_integral<TInt>::value, bool> = true>
    static bool
    inMinMax(TInt min, TInt x, TInt max, bool minInclude =true, bool maxInclude =true)
    {
        min = minInclude ? min : min+1;
        max = maxInclude ? max : max+1;

        return min <= x && x <= max;
    }

    // This method itself normalizes the minimum and maximum values
    template <typename TInt,
              std::enable_if_t<std::is_integral<TInt>::value, bool> = true>
    static bool
    inMinMaxNorm(TInt min, TInt x, TInt max, bool minInclude =true, bool maxInclude =true)
    {
        min = std::min(min, max);
        max = std::max(min, max);

        min = minInclude ? min : min+1;
        max = maxInclude ? max : max+1;

        return min <= x && x <= max;
    }
};


} // namespace Qq
// <<< END OF FILE: Helpers/Main.h <<<



namespace Qq::Enum
{


///
/// \brief Methods for initializing arrays of QQ_ENUM_CORE
///
struct Helper
{
    template <typename TEnum>
    static std::map<TEnum,int>
    makeEnumToIndexMap(std::vector<TEnum> const & valueList) noexcept
    {
        std::map<TEnum,int> res;

        int count = static_cast<int>(valueList.size());

        for (int i = 0; i < count; ++i)
        {
            TEnum const & e = valueList[i]; //-V108
            res[e] = i;
        }

        return res;
    }

    static std::string
    parseEnumValueName(char const * str) noexcept
    {
        using H = Qq::Helpers::Main;

        std::string res{ str };

        int pos = static_cast<int>(res.find('='));
        if (std::string::npos != pos)
            res = res.substr(0, pos);

        res = H::trim(res.c_str());

        return res;
    }
};


} // namespace Qq::Enum
// <<< END OF FILE: QqEnum/Helper.h <<<

// >>> START OF FILE: Utils/qq_throw_l.M.h <<<

#include <iostream>


#define qq_throw_l(EXCEPTION,TEXT)                      \
    {                                                   \
        std::cerr << "\nEXCEPTION: ";                   \
        std::cerr << TEXT << std::endl;                 \
        throw EXCEPTION{ TEXT };                        \
    }
// <<< END OF FILE: Utils/qq_throw_l.M.h <<<


// >>> START OF FILE: QqThread/qq_lock.M.h <<<

// >>> START OF FILE: QqThread/QqMutexGuard.h <<<

#include <mutex>


namespace Qq::Thread
{


template <class TMutex>
class QqMutexGuard
{
public:
    QqMutexGuard(QqMutexGuard const &) = delete;

    QqMutexGuard(TMutex & mutex)
        : m_mutex{ mutex }
    {
        m_mutex.lock();
    }

    ~QqMutexGuard()
    {
        m_mutex.unlock();
    }

    constexpr operator bool() const noexcept
    {
        return true;
    }

    QqMutexGuard & operator = (QqMutexGuard const &) = delete;

private:
    TMutex & m_mutex;
};


} // namespace Qq::Thread
// <<< END OF FILE: QqThread/QqMutexGuard.h <<<


#ifndef QQ_LOCK_MUTEX_TYPE
    #define QQ_LOCK_MUTEX_TYPE  std::mutex
#else
    #define QQ_LOCK_MUTEX_TYPE  QMutex
#endif


#define qq_lock          if ( static QQ_LOCK_MUTEX_TYPE __qq_mutex; Qq::Thread::QqMutexGuard{ __qq_mutex } )
#define qq_lock_m(MUTEX) if ( Qq::Thread::QqMutexGuard{ MUTEX } )
// <<< END OF FILE: QqThread/qq_lock.M.h <<<


#include <cassert>



namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
struct MetadataT
{
//
// Types
//
protected:
    using H          = Helper;
public:
    using ValueList  = std::vector     <TEnum>;
    using NameList   = std::vector     <QqEnumString>;
    using EIMap      = std::map        <TEnum,int>;
    using Wrapper    = EnumItemWrapperT<TEnum,TInt>;
    using WrapperList= std::vector     <Wrapper>;

//
// Friends
//
private:
    template <typename T_Class, typename T_Enum, typename T_Int>
    friend struct MetadataInitializierT;

    template <typename T_Class, typename T_Enum, typename T_Int>
    friend class CoreT;

    template <typename T_Class, typename T_Enum, typename T_Int>
    friend class InvalidValueSetterT;

    template <typename T_Class, typename T_Enum, typename T_Int>
    friend class DefaultValueSetterT;

//
// Ctors & Dtor
//
public:
    MetadataT(
        char const  * className,
        char const  * intTypeName,
        char const  * fullClassName,
        ValueList  && valueList,
        NameList   && nameList)
    {
        if (m_isCreated)
            qq_throw_l(
                std::logic_error,
                QqEnumStringLiteral{ "Qq::Enum::MetadataT<%1,%2,%3> already creadted." }
                    .arg(className)
                    .arg("TEnum")
                    .arg(intTypeName)
                    .toLatin1()
            );

        if (not valueList.size())
            qq_throw_l(
                std::logic_error,
                QqEnumStringLiteral{ "The Qq::Enum::MetadataT<%1,%2,%3>::ctor() doesn't work with empty list of value." }
                    .arg(className)
                    .arg("TEnum")
                    .arg(intTypeName)
                    .toLatin1()
            );

        qq_lock
        {
            m_className     = className;
            m_intTypeName   = intTypeName;
            m_fullClassName = gfcn(fullClassName);

            if (nameList.size() != valueList.size())
                qq_throw_l(
                    std::length_error,
                    "The lenght of value list is not equal lenght of the name list."
                )

            m_values      = std::move(valueList);
            // now the count() method is aviabled
            m_names       = std::move(nameList );
            m_enumToIndex = std::move(H::makeEnumToIndexMap<TEnum>(m_values));

            m_wrappers.reserve(count());

            for (int i = 0; i < count(); ++i)
                m_wrappers.push_back(Wrapper{ i, m_values[i], m_names[i] });

            calcAndSetMinMaxValues();
            m_lastValidIndex = count() -1;

            m_isCreated = true;
        }
    }

//
// Public API
//
public:

    //
    // Meta-info
    //

    static inline char const *
    className() noexcept
    {
        return m_className;
    }

    static inline char const *
    intTypeName() noexcept
    {
        return m_intTypeName;
    }

    static inline char const *
    fullClassName() noexcept
    {
        return m_fullClassName;
    }

    //
    // Range API
    //

    static inline constexpr TEnum
    firstValue() noexcept
    {
        assert(m_values.size() > 0 && "m_values.size() can't be zero or less!");
        return m_values.front();
    }

    static inline constexpr TEnum
    lastValue()
    {
        assert(m_values.size() > 0 && "m_values.size() can't be zero or less!");
        return m_values.back();
    }

    static inline constexpr size_t
    count() noexcept
    {
        return m_values.size();
    }

    static inline constexpr TEnum
    minValue() noexcept
    {
        return m_minValue;
    }

    static inline constexpr TEnum
    maxValue() noexcept
    {
        return m_maxValue;
    }

    //
    // Access API
    //

    static inline constexpr TEnum
    value(int index, char const * exceptionMethodName = nullptr)
    {
        C::ThrowIfIndexOutOfRange(index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
        return m_values[index];
    }

    static inline constexpr QqEnumString const &
    name(int index, char const * exceptionMethodName = nullptr)
    {
        C::ThrowIfIndexOutOfRange(index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
        return m_names[index];
    }

    static inline constexpr QqEnumString const &
    nameByValue(TEnum e, char const * exceptionMethodName = nullptr)
    {
        int index = C::ThrowIfEnumOutOfRange(e, exceptionMethodName);
        return m_names[index];
    }

    static inline constexpr Wrapper const &
    wrapper(int index, char const * exceptionMethodName = nullptr)
    {
        C::ThrowIfIndexOutOfRange(index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
        return m_wrappers[index];
    }

    static inline constexpr Wrapper const &
    wrapperNoCheck(int index) noexcept
    {
        return m_wrappers[index];
    }

    static inline constexpr bool
    isValueDefined(TEnum e) noexcept
    {
        return indexOf(e) != Const::badIndex;
    }


    static inline constexpr int
    indexOf(TEnum e) noexcept
    {
        auto & m  = eiMap();
        auto   it = m.find(e);
        if (it == m.end())
            return Const::badIndex;

        return it->second;
    }

    static inline constexpr TEnum
    valueByInt(TInt i, char const * exceptionMethodName = nullptr)
    {
        TEnum e = static_cast<TEnum>(i);
        C::ThrowIfEnumOutOfRange(e, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
        return e;
    }

    //
    // List and map API
    //

    static inline constexpr ValueList const &
    valueList() noexcept
    {
        return m_values;
    }

    static inline constexpr NameList const &
    nameList() noexcept
    {
        return m_names;
    }

    static inline constexpr EIMap const &
    eiMap() noexcept
    {
        return m_enumToIndex;
    }

    static inline constexpr WrapperList const &
    wrapperList() noexcept
    {
        return m_wrappers;
    }

    //
    // Invalid and Default value API
    //

    static inline constexpr bool
    isInvalidValueDefined() noexcept
    {
        return 0 == m_invalidValueIndex;
    }

    static inline constexpr bool
    isDefaultValueDefined() noexcept
    {
        return m_defaultValueIndex >= 0;
    }

    static inline constexpr TEnum
    invalidValue(char const * exceptionMethodName = nullptr)
    {
        return value(m_invalidValueIndex, exceptionMethodName);
    }

    static inline constexpr int
    invalidValueIndex() noexcept
    {
        return m_invalidValueIndex;
    }

    static inline constexpr TEnum
    defaultValue(char const * exceptionMethodName = nullptr)
    {
        return value(m_defaultValueIndex, exceptionMethodName);
    }

    static inline constexpr int
    defaultValueIndex() noexcept
    {
        return m_defaultValueIndex;
    }

    static inline constexpr QqEnumString const &
    defaultValueName(char const * exceptionMethodName = nullptr)
    {
        return name(m_defaultValueIndex, exceptionMethodName);
    }

    static inline constexpr QqEnumString const &
    invalidValueName(char const * exceptionMethodName = nullptr)
    {
        return name(m_invalidValueIndex, exceptionMethodName);
    }

    static inline constexpr bool
    isInvalidByIndex(int index)
    {
        return index == invalidValueIndex();
    }

    static inline constexpr bool
    isDefaultByIndex(int index)
    {
        return index == defaultValueIndex();
    }

    static inline constexpr bool
    isValueInvalid(TEnum e)
    {
        return isInvalidValueDefined() && e == invalidValue();
    }

    static inline constexpr bool
    isValueDefault(TEnum e)
    {
        return e == defaultValue();
    }

    //
    // Other API
    //

    static inline constexpr bool
    indexInValidRange(int index) noexcept
    {
        int minIndex = isInvalidValueDefined() ? 1 : 0;

        return minIndex <= index && index < count();
    }

    static inline constexpr bool
    indexInRange(int index) noexcept
    {
        return 0 <= index && index < count();
    }

    static inline constexpr int
    firstValidindex() noexcept
    {
        return m_firstValidIndex; //1 + m_invalidValueIndex;
    }

    static inline constexpr int
    lastValidIndex() noexcept
    {
        return m_lastValidIndex;
    }

    static inline constexpr int
    lastIndex() noexcept
    {
        return count() - 1;
    }

    static inline constexpr int
    beyondIndex() noexcept
    {
        return count();
    }

//
// Internal API
//
protected:
    static inline char const *
    gfcn(char const * fcnStr)
    {
        static std::string res{ fcnStr };
        if (not m_isCreated)
        {
            int i = static_cast<int>(res.length()) -1;
            for (; i > 2; --i)
                if (':' == res[i] && ':' == res[i-1]) break;

            --i;
            int len = 0;
            while (i > 0 && res[i] != ' ')
                --i, ++len;

            res = res.substr(i, len);
        }

        return res.c_str();
    }

private:
    static inline constexpr void
    setInvalidValue(TEnum newInvalidValue)
    {
        int index = C::ThrowIfEnumOutOfRange(newInvalidValue, QQ_FULL_FUNC_SIG);
        if (index != 0)
        {
            if (indexInRange(index))
                qq_throw_l(
                    std::logic_error,
                    QqEnumStringLiteral{ "The invalid enum '%2' must be the first string in the enum list (QQ_ENUM).\nMETHOD: %1" }
                        .arg(QQ_FULL_FUNC_SIG)
                        .arg(name(index))
                        .toLatin1()
                )
            else
                qq_throw_l(
                    std::out_of_range,
                    QqEnumStringLiteral{ "The %1 (as int) is out of range of %2.\nMETHOD:%3" }
                        .arg(static_cast<TInt>(newInvalidValue))
                        .arg(className())
                        .arg(QQ_FULL_FUNC_SIG)
                        .toLatin1()
                )
        }

        if (0 == m_wrappers.size())
            qq_throw_l(
                std::logic_error,
                QqEnumStringLiteral{ "Unable to set the newInvalidValue because EnumItemWrappers is empty." }
                    .toLatin1()
            );

        if (index > Const::indexMask)
            qq_throw_l(
                std::out_of_range,
                QqEnumStringLiteral{ "The index value in QQ_ENUM can't exceed %1." }
                    .arg(Const::indexMask)
                    .toLatin1()
            );

        qq_lock
        {
            m_invalidValueIndex = index;
            m_firstValidIndex   = 1;

            int shiftedInvalidValueIndex = index << Const::invalidValueShift;

            for (int i = 0; i < m_wrappers.size(); ++i)
            {
                auto & w = m_wrappers[i];
                w.m_index |= shiftedInvalidValueIndex;
            }
        }
    }

    static inline constexpr void
    setDefaultValue(TEnum newDefaultValue)
    {
        int index = C::ThrowIfEnumOutOfRange(newDefaultValue, QQ_FULL_FUNC_SIG);

        if (0 == m_wrappers.size())
            qq_throw_l(
                std::logic_error,
                QqEnumStringLiteral{ "Unable to set the newDefaultValue because EnumItemWrappers is empty." }
                    .toLatin1()
            );

        if (index > Const::indexMask)
            qq_throw_l(
                std::out_of_range,
                QqEnumStringLiteral{ "The index value in QQ_ENUM can't exceed %1." }
                    .arg(Const::indexMask)
                    .toLatin1()
            );

        qq_lock
        {
            m_defaultValueIndex = index;

            int shiftedDefaultValueIndex = index << Const::defaultValueShift;

            for (int i=0; i < m_wrappers.size(); ++i)
            {
                auto & w = m_wrappers[i];
                w.m_index |= shiftedDefaultValueIndex;
            }

        }
    }

    static inline constexpr void
    calcAndSetMinMaxValues() noexcept
    {
        TEnum min{}, max{};

        for (int i = 0; i < count(); ++i)
        {
            min = std::min(min, value(i));
            max = std::max(max, value(i));
        }

        m_minValue = min;
        m_maxValue = max;
    }

private: //~ protected:
//
// Fields
//
    static inline bool        m_isCreated = false;

    static inline ValueList   m_values;
    static inline NameList    m_names;
    static inline EIMap       m_enumToIndex;
    static inline WrapperList m_wrappers;

    static inline int         m_firstValidIndex   = 0;
    static inline int         m_lastValidIndex    = Const::badIndex;

    static inline int         m_invalidValueIndex = Const::badIndex;

    static inline int         m_defaultValueIndex = 0;

    static inline TEnum       m_minValue;
    static inline TEnum       m_maxValue;

//
// Const-data
//
    static inline char const          * m_className     = nullptr;
    static inline char const          * m_intTypeName   = nullptr;
    static inline char const          * m_fullClassName = nullptr;

    static inline QqEnumString    const c_emptyString { "" };
    static inline Wrapper const c_emptyWrapper{ -1, TEnum{}, c_emptyString };

//
// Using-synonyms
//
private:
    using C = CoreT<TClass,TEnum,TInt>;
};


} // namespace Qq::Enum

// >>> START OF FILE: QqEnum/CoreT.h <<<


// >>> START OF FILE: Exceptions/ParseException.h <<<


#include <exception>


namespace Qq::Exceptions
{


class ParseException : public std::exception
{
public:
    explicit ParseException(char const * const message) noexcept
        : exception(message)
    {}
};


} //namespace Qq::Exceptions
// <<< END OF FILE: Exceptions/ParseException.h <<<



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
// Internal API
//
protected:

//
// Public API
//
public:

    //
    // Range API
    //

    static inline constexpr int
    toRange(int index, bool negativeIsAllow = true) noexcept
    {
        if (negativeIsAllow)
            toPositiveRange(index);

        index = std::max( 0, std::min(index, D::lastValidIndex()) );
        return index;
    }

    static inline constexpr int
    toPositiveRange(int index) noexcept
    {
        return index < 0
            ? D::lastValidIndex() + index +1
            : index;
    }

    static inline constexpr void
    makePositiveRange(int & index) noexcept
    {
        index = toPositiveRange(index);
    }

    static inline constexpr int
    toPositiveIndex(int index) noexcept
    {
        return index < 0
            ? D::lastValidIndex() + index +1
            : index;

    }

    static inline constexpr void
    makePositiveIndex(int & index) noexcept
    {
        index = toPositiveIndex(index);
    }

    //
    // \brief Searching \arg e in values and return its index. If e in not range then make throw.
    //
    static inline constexpr int
    ThrowIfEnumOutOfRange(
        TEnum        e,
        char const * exceptionMethodName = nullptr)
    {
        auto it = D::eiMap().find(e);
        if (it == D::eiMap().end())
            qq_throw_l(
                std::out_of_range,
                QqEnumStringLiteral{ "The %1(as int) is not a member of enumeration %2\nMETHOD: %3" }
                    .arg(static_cast<TInt>(e))
                    .arg(D::className())
                    .arg(exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG)
                    .toLatin1()
            )

        return it->second;
    }

    //
    // \ret: if index in range then don't throws the exception
    //
    static inline constexpr int
    ThrowIfIndexOutOfRange(
        int          index,
        char const * exceptionMethodName,
        char const * paramName = "index")
    {
        if (D::indexInRange(index)) //-V3504
            return index;

        qq_throw_l(
            std::out_of_range,
            QqEnumStringLiteral{ "The %1 = %2 is out of range.\nMETHOD: %3" }
                .arg(paramName)
                .arg(index)
                .arg(exceptionMethodName)
                .toLatin1()
        );
    }

    //
    // CTORs
    //

    static inline constexpr int
    ctor_index(int index, char const * exceptionMethodName = nullptr)
    {
        return ThrowIfIndexOutOfRange(index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
    }

    static inline constexpr int
    ctor_enum(TEnum e, char const * exceptionMethodName = nullptr)
    {
        return ThrowIfEnumOutOfRange(e, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
    }

    //
    // Assignment operators
    //

    static inline constexpr TClass &
    op_assignmentInt(TClass & c, TInt i, char const * exceptionMethodName = nullptr)
    {
        return op_assignmentEnum(c, static_cast<TEnum>(i), exceptionMethodName);
    }

    static inline constexpr TClass &
    op_assignmentEnum(TClass & c, TEnum e, char const * exceptionMethodName = nullptr)
    {
        c.m_index = D::indexOf(e);
        if (Const::badIndex == c.m_index)
            qq_throw_l(
                std::out_of_range,
                QqEnumStringLiteral{ "The %1(as int) is not a member of enumeration %2\nMETHOD: %3" }
                    .arg(static_cast<TInt>(e))
                    .arg(D::className())
                    .arg(exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG)
                    .toLatin1()
            )

        return c;
    }

    static inline constexpr TClass &
    //- op_assignmentOther(TClass & lh, TClass const & rh, char const * exceptionMethodName = nullptr)
    op_assignmentOther(TClass & lh, TClass const & rh) noexcept
    {
        lh.m_index = rh.m_index;
        //- ifIndexOutOfRangeDoThrow(lh.m_index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
        return lh;
    }

    //
    // ADD operators
    //

    static inline constexpr TClass &
    //- op_add(TClass & lh, TClass const & rh, char const * exceptionMethodName = nullptr)
    op_add(TClass & lh, TClass const & rh) noexcept
    {
        lh.m_index += rh.m_index;
        //- ifIndexOutOfRangeDoThrow(lh.m_index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
        return lh;
    }

    static inline constexpr TClass &
    op_add(TClass & lh, int n, char const * exceptionMethodName = nullptr)
    {
        lh.m_index += n;
        ThrowIfIndexOutOfRange(lh.m_index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);

        return lh;
    }

    //
    // ADD & assignment operators
    //

    static inline constexpr int
    op_add_assignment(int index, int n, char const * exceptionMethodName = nullptr)
    {
        index += n;
        return ThrowIfIndexOutOfRange(index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
    }

    //
    // INC operator (only prefix)
    //

    static inline constexpr int
    op_inc(int index, char const * exceptionMethodName = nullptr)
    {
        ++index;
        return ThrowIfIndexOutOfRange(index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
    }

    //
    // SUB operators
    //

    static inline constexpr TClass &
    op_sub(TClass & lh, TClass const & rh, char const * exceptionMethodName = nullptr)
    {
        lh.m_index -= rh.m_index;
        ThrowIfIndexOutOfRange(lh.m_index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);

        return lh;
    }

    static inline constexpr TClass &
    op_sub/*_asFriend*/(TClass & lh, int n, char const * exceptionMethodName = nullptr)
    {
        lh.m_index -= n;
        ThrowIfIndexOutOfRange(lh.m_index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);

        return lh;
    }

    //
    // ADD & assignment operators
    //

    static inline constexpr int
    op_sub_assignment(int index, int n, char const * exceptionMethodName = nullptr)
    {
        index -= n;
        return ThrowIfIndexOutOfRange(index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
    }

    //
    // DEC operator (only prefix)
    //

    static inline constexpr int
    op_dec(int index, char const * exceptionMethodName = nullptr)
    {
        --index;
        return ThrowIfIndexOutOfRange(index, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
    }

    //
    // Comparsion operators
    //
    static inline constexpr bool
    op_compare(int index, TEnum e, char const * exceptionMethodName = nullptr)
    {
        return index == ThrowIfEnumOutOfRange(e, exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG);
    }

    // static inline constexpr bool
    // op_great(TClass const c, TInt i, char const * exceptionMethodName = nullptr) noexcept
    // {
    //     return c._value() > D::valueByInt(i, exceptionMethodName);
    // }

    //
    // Other
    //

    static constexpr int
    findNameIndex(char const * nameStr, bool caseInsensitive = true)
    {
        if (not nameStr) return -1;

        int index   = -1;
        int counter = 0;

    #ifdef QQ_DONT_USE_QT
        using H = Qq::Helpers::Main;
        std::string sFind{
            caseInsensitive
                ? H::toLower(H::trim(nameStr))
                : H::trim(nameStr)
        };

        for(auto const & name : D::nameList())
        {
            if (caseInsensitive)
            {
                std::string lowName{ name };
                if (sFind == H::toLower(lowName))
                {
                    index = counter;
                    break;
                }
            }
            else
            {
                if (sFind == name)
                {
                    index = counter;
                    break;
                }
            }

            ++counter;
        }
    #else
        QString sFind = QString{ nameStr }.trimmed();
        sFind = not caseInsensitive ? sFind : sFind.toLower();

        for(auto const & name : D::nameList())
        {
            if (caseInsensitive)
                if (sFind == name.toLower())
                {
                    index = counter;
                    break;
                }
            else
            {
                if (sFind == name)
                {
                    index = counter;
                    break;
                }
            }

            ++counter;
        }
    #endif

        return index;
    }

    static constexpr bool
    tryParse(
        char const * name,
        TClass     * out             = nullptr,
        bool         caseInsensitive = true
    )
        noexcept
    {
        int idx = findNameIndex(name, caseInsensitive);

        if (Const::badIndex == idx) return false;

        if (out) out->m_index = idx;

        return true;
    }

    static constexpr TClass
    parse(
        char const * name,
        bool         caseInsensitive     = true,
        char const * exceptionMethodName = nullptr)
    {
        int idx = findNameIndex(name, caseInsensitive);

        if (Const::badIndex == idx)
            qq_throw_l(
                Qq::Exceptions::ParseException,
                QqEnumStringLiteral{ "The string `%1` was not found in the list of names of the `%2` enum when parsing.\nMETHOD: %3" }
                    .arg(name)
                    .arg(D::className())
                    .arg(exceptionMethodName ? exceptionMethodName : QQ_FULL_FUNC_SIG)
                    .toLatin1()
            );

        TClass res{ idx };

        return res;
    }

//
// Using-synonyms
//
private:
    using D = MetadataT<TClass,TEnum,TInt>;
};


} // namespace Qq::Enum
// <<< END OF FILE: QqEnum/CoreT.h <<<

// >>> START OF FILE: QqEnum/MetadataInitializierT.h <<<



namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
struct MetadataInitializierT
{
    constexpr MetadataInitializierT()
    {
        using D = MetadataT<TClass,TEnum,TInt>;
    }
};


} // namespace Qq::Enum
// <<< END OF FILE: QqEnum/MetadataInitializierT.h <<<

// <<< END OF FILE: QqEnum/MetadataT.h <<<

//#include "./CoreT.h"
// <<< END OF FILE: QqEnum/EnumItemWrapperT.h <<<

// >>> START OF FILE: QqEnum/EatAssignT.h <<<


namespace Qq::Enum
{


template <typename TEnum, typename TInt =int>
struct EatAssignT
{
    constexpr EatAssignT() noexcept
    {}

    constexpr TInt toInt() const noexcept {
        return static_cast<TInt>(value);
    }

    constexpr operator TEnum () const noexcept {
        return value;
    }

    constexpr TEnum operator = (TInt) noexcept {
        return value;
    }

    constexpr EatAssignT & operator << (TEnum value)
    {
        this->value = value;
        return *this;
    }

    TEnum value{};
};


} // namespace Qq::Enum
// <<< END OF FILE: QqEnum/EatAssignT.h <<<

// >>> START OF FILE: QqEnum/InvalidValueSetterT.h <<<



namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
class InvalidValueSetterT
{
public:
    constexpr InvalidValueSetterT(TEnum const e) noexcept
    {
        MetadataT<TClass,TEnum,TInt>::setInvalidValue(e);
    }
};


} // namespace Qq::Enum
// <<< END OF FILE: QqEnum/InvalidValueSetterT.h <<<

// >>> START OF FILE: QqEnum/DefaultValueSetterT.h <<<



namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
class DefaultValueSetterT
{
public:
    constexpr DefaultValueSetterT(TEnum const e) noexcept
    {
        MetadataT<TClass,TEnum,TInt>::setDefaultValue(e);
    }
};


} // namespace Qq::Enum
// <<< END OF FILE: QqEnum/DefaultValueSetterT.h <<<

// >>> START OF FILE: QqEnum/Index.h <<<

#include <atomic>
#include <xatomic.h>

namespace Qq::Enum
{

class Index : public std::atomic<int>
{
//
// CTORS
//
public:
    inline constexpr Index(const int initValue = 0) noexcept
        : std::atomic<int>(initValue)
    {}

//
// Operators
//
public:
    inline int operator () () const noexcept {
        return load(std::memory_order_acquire);
    }

    inline Index & operator = (Index const & other) noexcept {
        store(other(), std::memory_order_release);
        return *this;
    }
};


} // namespace Qq::Enum
// <<< END OF FILE: QqEnum/Index.h <<<

// >>> START OF FILE: QqEnum/IterationRangeT.h <<<


// >>> START OF FILE: QqEnum/IteratorT.h <<<




namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
struct IteratorT
{
//
// Public using synonyms:
//
    using Wrapper = EnumItemWrapperT<TEnum,TInt>;

//
// Iterator's using-synonyms
//
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Wrapper;
    using pointer           = Wrapper * ;
    using reference         = Wrapper & ;

//
// CTORs
//
public:
    constexpr IteratorT(int fromIndex = 0, int toIndex = Const::badIndex)
        : m_index { fromIndex }
    {
        m_fromIndex = C::toRange(fromIndex, true);
        m_toIndex   = C::toRange(toIndex,   true);
        m_order     = m_fromIndex > m_toIndex ? -1 : +1;
    }

    constexpr IteratorT(IteratorT const & from)
        : IteratorT{ from.m_fromIndex, from.m_toIndex }
    {}

    constexpr IteratorT(TEnum from, TEnum to)
    {
        m_fromIndex = D::indexOf(from);
        m_toIndex   = D::indexOf(to);
        m_order     = m_fromIndex > m_toIndex ? -1 : +1;
    }

//
// Consistent API
//
public:
    // \b Is m_index between _range[from, to]?
    inline constexpr bool
    inIterRange() const noexcept
    {
        return Qq::Helpers::Main::inMinMax(
            m_order > 0 ? m_fromIndex : m_toIndex,
            m_index,
            m_order > 0 ? m_toIndex   : m_fromIndex
        );
    }

    // \b Is m_index in range from 0 to D::count()-1.
    inline constexpr bool
    inRange() const noexcept
    {
        return D::indexInRange(m_index);
    }

    inline constexpr int
    index() const noexcept
    {
        return m_index;
    }

public:
    //
    // Comparsion operators
    //

    friend inline constexpr bool
    operator < (IteratorT const & lh, IteratorT const & rh) {
        return lh.m_index < rh.m_index;
    }

    friend inline constexpr bool
    operator > (IteratorT const & lh, IteratorT const & rh) {
        return lh.m_index > rh.m_index;
    }

    friend inline constexpr bool
    operator <= (IteratorT const & lh, IteratorT const & rh) {
        return lh.m_index <= rh.m_index;
    }

    friend inline constexpr bool
    operator >= (IteratorT const & lh, IteratorT const & rh) {
        return lh.m_index >= rh.m_index;
    }

    friend inline constexpr bool
    operator == (IteratorT const & lh, IteratorT const & rh) noexcept {
        return lh.m_index == rh.m_index;
    }

    friend inline constexpr bool
    operator != (IteratorT const & lh, IteratorT const & rh) noexcept {
        return not (lh.m_index == rh.m_index);
    }


    //
    // Assignment operators
    //

    inline constexpr IteratorT &
    operator = (int n) noexcept
    {
        m_index = n;
        return *this;
    }

    inline constexpr IteratorT &
    operator = (IteratorT const & other) noexcept
    {
        if (other != *this)
            m_index = other.m_index;

        return *this;
    }

    //
    // ADD operators
    //

    friend inline constexpr IteratorT
    operator + (IteratorT const & lh, IteratorT const & rh) noexcept
    {
        IteratorT iter;
        iter.m_index = lh.m_index + rh.m_index;
        return iter;
    }

    friend inline constexpr IteratorT &
    operator + (IteratorT & iter, int n) noexcept
    {
        iter.m_index += n;
        return iter;
    }

    //
    // INC opertors
    //
    inline constexpr IteratorT &
    operator ++ () noexcept
    {
        m_index += m_order;
        return *this;
    }

    inline constexpr IteratorT
    operator ++ (int) noexcept
    {
        IteratorT tmp{ m_index };
        m_index += m_order;
        return tmp;
    }

    //
    // ADD & assignment operators
    //

    inline constexpr IteratorT &
    operator += (int n) noexcept
    {
        m_index += n;
        return *this;
    }

    inline constexpr IteratorT &
    operator += (IteratorT const & other) noexcept
    {
        m_index += other.m_index;
        return *this;
    }

    //
    // SUB operators
    //

    friend inline constexpr IteratorT
    operator - (IteratorT lhs, IteratorT const & rhs) noexcept
    {
        lhs -= rhs;
        return lhs;
    }

    friend inline constexpr IteratorT &
    operator - (IteratorT & iter, int n) noexcept
    {
        iter.m_index -= n;
        return iter;
    }

    //
    // DEC operators
    //

    constexpr inline IteratorT &
    operator -- () noexcept
    {
        m_index -= m_order;
        return *this;
    }

    constexpr inline IteratorT
    operator -- (int) noexcept
    {
        IteratorT tmp{ m_index };
        m_index -= m_order;
        return tmp;
    }

    //
    // SUB & assignment
    //

    inline constexpr IteratorT &
    operator -= (int n) noexcept
    {
        m_index -= n;
        return *this;
    }

    inline constexpr IteratorT &
    operator -= (IteratorT const & other) noexcept
    {
        m_index -= other.m_index;
        return *this;
    }

    //
    // Wrap operations
    //

    constexpr inline Wrapper const &
    operator * () const
    {
        C::ThrowIfIndexOutOfRange(m_index, QQ_FULL_FUNC_SIG, "m_index");
        return D::wrapperNoCheck(m_index);
    }

    constexpr inline Wrapper const *
    operator -> () const
    {
        C::ThrowIfIndexOutOfRange(m_index, QQ_FULL_FUNC_SIG, "m_index");
        return & D::wrapperNoCheck(m_index);
    }

//
// Using-synonyms
//
private:
    using C = CoreT<TClass,TEnum,TInt>;
    using D = MetadataT<TClass,TEnum,TInt>;

//
// Fields
//
private:
    Qq::Enum::Index m_index     ;
    int             m_fromIndex ;
    int             m_toIndex   ;
    int             m_order    ;
};


} // namespace Qq::Enum

// <<< END OF FILE: QqEnum/IteratorT.h <<<



namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
struct IterationRangeT
{
    using Iterator = IteratorT<TClass,TEnum,TInt>;

//
// CTORs
//
    constexpr IterationRangeT() noexcept
        : IterationRangeT{ 0 }
    {}

    constexpr IterationRangeT(int fromIndex, int toIndex = Const::badIndex)
    {
        using C = CoreT<TClass,TEnum,TInt>;
        using D = MetadataT<TClass,TEnum,TInt>;

        C::makePositiveIndex(fromIndex);
        C::makePositiveIndex(toIndex);

        if (std::abs(fromIndex) >= D::count())
            throw std::out_of_range("IterationRangeT::.ctor(...): `int fromIndex` is out of range.");

        if (std::abs(toIndex) >= D::count())
            throw std::out_of_range("IterationRangeT::.ctor(...): `int toIndex` is out of range.");

        m_fromIndex = fromIndex;
        m_toIndex   = toIndex;
        m_order     = m_fromIndex > m_toIndex ? -1 : +1;
    }

    constexpr IterationRangeT(TEnum from, TEnum to)
    {
        using D = MetadataT<TClass,TEnum,TInt>;

        int fromIndex = D::indexOf(from);
        int toIndex   = D::indexOf(to);

        if (Const::badIndex == fromIndex)
            throw std::out_of_range("IterationRangeT::.ctor(...): `_Enum from` is out of range.");

        if (Const::badIndex == toIndex)
            throw std::out_of_range("IterationRangeT::.ctor(...): `_Enum to` is out of range.");

        m_fromIndex = fromIndex;
        m_toIndex   = toIndex;
        m_order     = m_fromIndex > m_toIndex ? -1 : +1;
    }

    Iterator begin() const noexcept
    {
        return Iterator{ m_fromIndex, m_toIndex };
    }

    Iterator end() const noexcept
    {
        return Iterator{ m_order + m_toIndex };
    }

private:
    int m_fromIndex;
    int m_toIndex;
    int m_order;
};


} // namespace Qq::Enum
// <<< END OF FILE: QqEnum/IterationRangeT.h <<<




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
    static inline void __va_args__isNull()                                  \
    {                                                                       \
        static_assert(                                                      \
            0 < QQ_PP_VARIADIC_SIZE(__VA_ARGS__),                           \
            "QQ_ENUM connot be contain 0 elements."                         \
        );                                                                  \
    }                                                                       \
                                                                            \
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
    static inline constexpr bool                                            \
    _isDefined(_Enum e) noexcept                                            \
    {                                                                       \
        return _D::isValueDefined(e);                                       \
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
// <<< END OF FILE: QqEnum/QqEnum.M.h <<<

         // <<< END OF FILE: QqEnum.h <<<

// >>> START OF FILE: Macros/Variadic/Elem.M.h <<<


# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* Revised by Edward Diener (2020) */
#
# /* See http://www.boost.org for most recent version. */
#



# if QQ_PP_VARIADICS_MSVC
#     define QQ_PP_VARIADIC_ELEM(n, ...)   QQ_PP_VARIADIC_ELEM_I(n,__VA_ARGS__)
#     define QQ_PP_VARIADIC_ELEM_I(n, ...) QQ_PP_CAT(QQ_PP_CAT(QQ_PP_VARIADIC_ELEM_, n)(__VA_ARGS__,),)
# else
//#~     define QQ_PP_VARIADIC_ELEM(n, ...) QQ_PP_CAT(QQ_PP_VARIADIC_ELEM_, n)(__VA_ARGS__,)
# endif
#
# define QQ_PP_VARIADIC_ELEM_0(e0, ...) e0
# define QQ_PP_VARIADIC_ELEM_1(e0, e1, ...) e1
# define QQ_PP_VARIADIC_ELEM_2(e0, e1, e2, ...) e2
# define QQ_PP_VARIADIC_ELEM_3(e0, e1, e2, e3, ...) e3
# define QQ_PP_VARIADIC_ELEM_4(e0, e1, e2, e3, e4, ...) e4
# define QQ_PP_VARIADIC_ELEM_5(e0, e1, e2, e3, e4, e5, ...) e5
# define QQ_PP_VARIADIC_ELEM_6(e0, e1, e2, e3, e4, e5, e6, ...) e6
# define QQ_PP_VARIADIC_ELEM_7(e0, e1, e2, e3, e4, e5, e6, e7, ...) e7
# define QQ_PP_VARIADIC_ELEM_8(e0, e1, e2, e3, e4, e5, e6, e7, e8, ...) e8
# define QQ_PP_VARIADIC_ELEM_9(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, ...) e9
# define QQ_PP_VARIADIC_ELEM_10(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, ...) e10
# define QQ_PP_VARIADIC_ELEM_11(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, ...) e11
# define QQ_PP_VARIADIC_ELEM_12(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, ...) e12
# define QQ_PP_VARIADIC_ELEM_13(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, ...) e13
# define QQ_PP_VARIADIC_ELEM_14(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, ...) e14
# define QQ_PP_VARIADIC_ELEM_15(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, ...) e15
# define QQ_PP_VARIADIC_ELEM_16(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, ...) e16
# define QQ_PP_VARIADIC_ELEM_17(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, ...) e17
# define QQ_PP_VARIADIC_ELEM_18(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, ...) e18
# define QQ_PP_VARIADIC_ELEM_19(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, ...) e19
# define QQ_PP_VARIADIC_ELEM_20(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, ...) e20
# define QQ_PP_VARIADIC_ELEM_21(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, ...) e21
# define QQ_PP_VARIADIC_ELEM_22(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, ...) e22
# define QQ_PP_VARIADIC_ELEM_23(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, ...) e23
# define QQ_PP_VARIADIC_ELEM_24(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, ...) e24
# define QQ_PP_VARIADIC_ELEM_25(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, ...) e25
# define QQ_PP_VARIADIC_ELEM_26(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, ...) e26
# define QQ_PP_VARIADIC_ELEM_27(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, ...) e27
# define QQ_PP_VARIADIC_ELEM_28(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, ...) e28
# define QQ_PP_VARIADIC_ELEM_29(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, ...) e29
# define QQ_PP_VARIADIC_ELEM_30(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, ...) e30
# define QQ_PP_VARIADIC_ELEM_31(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, ...) e31
# define QQ_PP_VARIADIC_ELEM_32(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, ...) e32
# define QQ_PP_VARIADIC_ELEM_33(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, ...) e33
# define QQ_PP_VARIADIC_ELEM_34(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, ...) e34
# define QQ_PP_VARIADIC_ELEM_35(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, ...) e35
# define QQ_PP_VARIADIC_ELEM_36(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, ...) e36
# define QQ_PP_VARIADIC_ELEM_37(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, ...) e37
# define QQ_PP_VARIADIC_ELEM_38(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, ...) e38
# define QQ_PP_VARIADIC_ELEM_39(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, ...) e39
# define QQ_PP_VARIADIC_ELEM_40(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, ...) e40
# define QQ_PP_VARIADIC_ELEM_41(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, ...) e41
# define QQ_PP_VARIADIC_ELEM_42(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, ...) e42
# define QQ_PP_VARIADIC_ELEM_43(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, ...) e43
# define QQ_PP_VARIADIC_ELEM_44(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, ...) e44
# define QQ_PP_VARIADIC_ELEM_45(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, ...) e45
# define QQ_PP_VARIADIC_ELEM_46(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, ...) e46
# define QQ_PP_VARIADIC_ELEM_47(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, ...) e47
# define QQ_PP_VARIADIC_ELEM_48(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, ...) e48
# define QQ_PP_VARIADIC_ELEM_49(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, ...) e49
# define QQ_PP_VARIADIC_ELEM_50(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, ...) e50
# define QQ_PP_VARIADIC_ELEM_51(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, ...) e51
# define QQ_PP_VARIADIC_ELEM_52(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, ...) e52
# define QQ_PP_VARIADIC_ELEM_53(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, ...) e53
# define QQ_PP_VARIADIC_ELEM_54(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, ...) e54
# define QQ_PP_VARIADIC_ELEM_55(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, ...) e55
# define QQ_PP_VARIADIC_ELEM_56(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, ...) e56
# define QQ_PP_VARIADIC_ELEM_57(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, ...) e57
# define QQ_PP_VARIADIC_ELEM_58(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, ...) e58
# define QQ_PP_VARIADIC_ELEM_59(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, ...) e59
# define QQ_PP_VARIADIC_ELEM_60(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, ...) e60
# define QQ_PP_VARIADIC_ELEM_61(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, ...) e61
# define QQ_PP_VARIADIC_ELEM_62(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, ...) e62
# define QQ_PP_VARIADIC_ELEM_63(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, ...) e63

# define QQ_PP_VARIADIC_ELEM_64(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, e64, ...) e64
# define QQ_PP_VARIADIC_ELEM_65(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, e64, e65, ...) e65
# define QQ_PP_VARIADIC_ELEM_66(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, e64, e65, e66, ...) e66
# define QQ_PP_VARIADIC_ELEM_67(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, e64, e65, e66, e67, ...) e67
// <<< END OF FILE: Macros/Variadic/Elem.M.h <<<

