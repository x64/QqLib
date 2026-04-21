#pragma once

// #include <QList>
// #include <QMap>
#include <QLocale>


#include "./_CompileConfig.h"
#include "./QqEnumString.h"
#include "./QqEnumStringLiteral.h"

#include "../Macros/_MainMacro.M.h"

#include "./Helper.h"
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
        char const *  className,
        char const *  intTypeName,
        char const *  fullClassName,
        ValueList  && valueList,
        NameList   && nameList
    )
        : m_className    { className     }
        , m_intTypeName  { intTypeName   }
        , m_fullClassName{ fullClassName }
    {
        if (nameList.size() != valueList.size())
            throw std::length_error("The lenght of value list is not equal lenght of the name list.");

        m_values      = std::move(valueList);
        m_names       = std::move(nameList );
        m_enumToIndex = std::move(H::makeEnumToIndexMap<TEnum>(m_values));

        m_wrappers.reserve(nameList.size());

        for (int i = 0; i < nameList.size(); ++i)
            m_wrappers.push_back(EnumItemWrapper{ m_values[i], m_names[i] });

        calcAndSetMinMaxValues();
        m_lastValidIndex = count() -1;
    }

//
// Internal API
//
protected:
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
    ifEnumInNotRangeDoThrow(TEnum const e)
    {
        auto it = eiMap().find(e);
        if (it == eiMap().end())
            throw std::out_of_range{
                StringLiteral{ "%1: the `%2` is out of range of %3" }
                    .arg(QQ_FULL_FUNC_SIG)
                    .arg(static_cast<TInt>(e))
                    .arg(className())
                    .toLatin1()
            };

        return it->second();
    }

private:
    static inline constexpr void
    setInvalidValue(TEnum const newInvalidValue)
    {
        int index = ifEnumInNotRangeDoThrow(newInvalidValue);
        if (index != 0)
            throw std::logic_error(
                StringLiteral{ "%1: the enum '%2' must be the first string in the enum list." }
                    .arg(QQ_FULL_FUNC_SIG)
                    .arg(name(index))
                    .toLatin1()
            );

        qq_lock
        {
            m_invalidValueDefined = true;
            m_invalidValue        = newInvalidValue;
            m_invalidValueIndex   = index;

            m_firstValidIndex     = 1;
        }
    }

    static inline constexpr void
    setDefaultValue(TEnum const newDefaultValue)
    {
        int index = ifEnumInNotRangeDoThrow(newDefaultValue);
        qq_lock
        {
            m_defaultValueDefined = true;
            m_defaultValue        = newDefaultValue;
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
    static inline const char *
    className() {
        return m_className;
    }

    static inline const char *
    intTypeName() {
        return m_intTypeName;
    }

    static inline const char *
    fullClassName() {
        return m_fullClassName;
    }

    //
    // Access and info API
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

    static inline constexpr TEnum
    value(int index)
    {
        if (not isValidIndex(index))
            throw std::out_of_range(
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
        if (not isValidIndex(index))
            return m_emptyString;

        return m_names[index];
    }

    static inline constexpr QqEnumString const &
    nameByValue(const TEnum e) noexcept
    {
        int index = indexOf(e);
        if (index < 0)
            return m_emptyString;

        return name(index);
    }

    static inline constexpr EnumItemWrapper const &
    wrapper(int index)
    {
        if (not isValidIndex(index))
            return m_emptyWrapper;

        return m_wrappers[index];
    }

    static inline constexpr int
    count() noexcept
    {
        return m_values.size();
    }

    static inline constexpr bool
    isValidIndex(int index) noexcept
    {
        return 0 <= index && index < count();
    }

    static inline constexpr char *
    className() noexcept {
        return m_className;
    }

    static inline constexpr char *
    intTypeName() noexcept {
        return m_intTypeName;
    }

    static inline constexpr char *
    fullClassName() noexcept {
        return m_fullClassName;
    }




//
// Fields:
//
private: //~ protected:
    static inline ValueList   m_values;
    static inline NameList    m_names;
    static inline EIMap       m_enumToIndex;
    static inline WrapperList m_wrappers;

    static inline TEnum       m_firstValidIndex;
    static inline TEnum       m_lastValidIndex;

    static inline bool        m_invalidValueDefined = false;
    static inline TEnum       m_invalidValue;
    static inline int         m_invalidValueIndex = -1;

    static inline bool        m_defaultValueDefined = false;
    static inline TEnum       m_defaultValue;
    static inline int         m_defaultValueIndex = -1;

    static inline TEnum       m_minValue;
    static inline TEnum       m_maxValue;
//
// Consts:
//
    static inline const char          * m_className     = nullptr;
    static inline const char          * m_intTypeName   = nullptr;
    static inline const char          * m_fullClassName = nullptr;

    static inline const QqEnumString    m_emptyString { "" };
    static inline const EnumItemWrapper m_emptyWrapper{ 0, m_emptyString };
};


} // namespace Qq::Enum

#include "./MetadataInitializierT.h"
