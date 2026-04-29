#pragma once

// #include <QList>
// #include <QMap>
#include <QLocale>


#include "./_CompileConfig.h"
#include "./QqEnumString.h"
#include "./QqEnumStringLiteral.h"

#include "../Macros/_MainMacro.M.h"

#include "./Helper.h"
#include "../Utils/qq_throw_l.M.h"

#include "../QqThread/qq_lock.M.h"
#include "./EnumItemWrapperT.h"


namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
struct MetadataT
{
//
// Types
//
protected:
    using H               = Helper;
public:
    using ValueList       = std::vector<TEnum>;                   //QList<TEnum>;
    using NameList        = std::vector<QqEnumString>;               //QStringList;
    using EIMap           = std::map   <TEnum,int>;               //QMap<TEnum,int>;
    using EnumItemWrapper = EnumItemWrapperT<TEnum>;
    using WrapperList     = std::vector<EnumItemWrapper>;

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
                StringLiteral{ "Qq::Enum::MetadataT<%1,%2,%3> already creadted." }
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
                );

            m_values      = std::move(valueList);
            // now the count() method is aviabled
            m_names       = std::move(nameList );
            m_enumToIndex = std::move(H::makeEnumToIndexMap<TEnum>(m_values));

            m_wrappers.reserve(count());

            for (int i = 0; i < count(); ++i)
                m_wrappers.push_back(EnumItemWrapper{ m_values[i], m_names[i] });

            calcAndSetMinMaxValues();
            m_lastValidIndex = count() -1;

            m_isCreated = true;
        }
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
            int i = res.length() -1;
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

    static inline constexpr int
    indexOf(TEnum const e) noexcept
    {
        auto & m  = eiMap();
        auto   it = m.find(e);
        if (it == m.end())
            return -1;

        return it->second;
    }

    //
    // \brief Searching \arg e in values and return its index. If e in not range then do throw.
    //
    static inline constexpr int
    ifEnumInNotRangeDoThrow(TEnum const e, char const * funcName)
    {
        auto it = eiMap().find(e);
        if (it == eiMap().end())
            qq_throw_l(
                std::out_of_range,
                StringLiteral{ "%1: the `%2` is out of range of %3" }
                    .arg(funcName)
                    .arg(static_cast<TInt>(e))
                    .arg(className())
                    .toLatin1()
            );

        return it->second;
    }

private:
    static inline constexpr void
    setInvalidValue(TEnum const newInvalidValue)
    {
        int index = ifEnumInNotRangeDoThrow(newInvalidValue, QQ_FULL_FUNC_SIG);
        if (index != 0)
        {
            if (isIndexValid(index))
                qq_throw_l(
                    std::logic_error,
                    StringLiteral{ "%1: the enum '%2' must be the first string in the enum list." }
                        .arg(QQ_FULL_FUNC_SIG)
                        .arg(name(index).c_str())
                        .toLatin1()
                );
            else
                qq_throw_l(
                    std::out_of_range,
                    StringLiteral{ "%1: the `%2` is out of range of %3" }
                        .arg(QQ_FULL_FUNC_SIG)
                        .arg(static_cast<TInt>(newInvalidValue))
                        .arg(className())
                        .toLatin1()
                );
        }

        qq_lock
        {
            //- m_invalidValueDefined = true;
            //- m_invalidValue        = newInvalidValue;
            m_invalidValueIndex   = index;

            m_firstValidIndex     = 1;
        }
    }

    static inline constexpr void
    setDefaultValue(TEnum const newDefaultValue)
    {
        int index = ifEnumInNotRangeDoThrow(newDefaultValue, QQ_FULL_FUNC_SIG);
        qq_lock
        {
            //- m_defaultValueDefined = true;
            //- m_defaultValue        = newDefaultValue;
            m_defaultValueIndex   = index;
        }
    }

    static inline constexpr void
    calcAndSetMinMaxValues() noexcept
    {
        TEnum min, max;

        for (int i = 0; i < count(); ++i)
        {
            min = std::min(min, value(i));
            max = std::max(max, value(i));
        }

        m_minValue = min;
        m_maxValue = max;
    }

//
// Public API
//
public:
    //
    // Meta-info
    //
    static inline char const *
    className() {
        return m_className;
    }

    static inline char const *
    intTypeName() {
        return m_intTypeName;
    }

    static inline char const *
    fullClassName() {
        return m_fullClassName;
    }

    //
    // Access and info API
    //
    static inline constexpr int
    count() noexcept {
        return m_values.size();
    }

    static inline constexpr TEnum
    value(int index)
    {
        if (not isIndexValid(index))
            qq_throw_l(
                std::out_of_range,
                StringLiteral{ "%1: the index = %2 is out of range." }
                    .arg(QQ_FULL_FUNC_SIG)
                    .arg(index)
                    .toLatin1()
            );

        return m_values[index];
    }

    static inline constexpr QqEnumString const &
    name(int index) noexcept
    {
        if (not isIndexValid(index))
            return m_emptyString;

        return m_names[index];
    }

    static inline constexpr QqEnumString const &
    nameByValue(TEnum const e) noexcept
    {
        int index = indexOf(e);
        if (index < 0)
            return m_emptyString;

        return name(index);
    }

    static inline constexpr EnumItemWrapper const &
    wrapper(int index)
    {
        if (not isIndexValid(index))
            return m_emptyWrapper;

        return m_wrappers[index];
    }

    //
    // List and map API
    //
    static inline constexpr ValueList const &
    valueList() noexcept {
        return m_values;
    }

    static inline constexpr NameList const &
    nameList() noexcept {
        return m_names;
    }

    static inline constexpr EIMap const &
    eiMap() noexcept {
        return m_enumToIndex;
    }

    static inline constexpr WrapperList const &
    wrapperList() noexcept {
        return m_wrappers;
    }

    //
    // Invalid and Default value API
    //
    static inline constexpr bool
    isInvalidValueDefined() noexcept {
        return m_invalidValueIndex == 0;
    }

    static inline constexpr bool
    isDefaultValueDefined() noexcept {
        return m_defaultValueIndex >= 0;
    }

    static inline constexpr TEnum
    invalidValue() noexcept {
        return value(m_invalidValueIndex);
    }

    static inline constexpr TEnum
    defaultValue() noexcept {
        return value(m_defaultValueIndex);
    }

    static inline constexpr int
    defaultValueIndex() noexcept {
        return m_defaultValueIndex;
    }

    static inline constexpr QqEnumString const &
    invalidValueName() noexcept {
        return name(m_invalidValueIndex);
    }

    static inline constexpr QqEnumString const &
    defaultValueName() noexcept {
        return name(m_defaultValueIndex);
    }


    //
    // Other API
    //
    static inline constexpr bool
    isIndexValid(int index) noexcept {
        return 0 <= index && index < count();
    }

    static inline constexpr int
    firstValidindex() noexcept {
        return m_firstValidIndex; //1 + m_invalidValueIndex;
    }

    static inline constexpr int
    lastValidindex() noexcept {
        return m_lastValidIndex;
    }

//
// Fields:
//
private: //~ protected:
    static inline bool        m_isCreated = false;

    static inline ValueList   m_values;
    static inline NameList    m_names;
    static inline EIMap       m_enumToIndex;
    static inline WrapperList m_wrappers;

    static inline int         m_firstValidIndex;
    static inline int         m_lastValidIndex;

    //- static inline bool        m_invalidValueDefined = false;
    //- static inline TEnum       m_invalidValue;
    static inline int         m_invalidValueIndex = -1;

    //- static inline bool        m_defaultValueDefined = false;
    //- static inline TEnum       m_defaultValue;
    static inline int         m_defaultValueIndex = 0;

    static inline TEnum       m_minValue;
    static inline TEnum       m_maxValue;
//
// Consts:
//
    static inline const char          * m_className     = nullptr;
    static inline const char          * m_intTypeName   = nullptr;
    static inline const char          * m_fullClassName = nullptr;

    static inline const QqEnumString    m_emptyString { "" };
    static inline const EnumItemWrapper m_emptyWrapper{ TEnum{}, m_emptyString };
};


} // namespace Qq::Enum

#include "./MetadataInitializierT.h"
