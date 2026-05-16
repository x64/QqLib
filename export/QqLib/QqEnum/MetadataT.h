#pragma once

#include "./_CompileConfig.h"
#include "./QqEnumString.h"
#include "./QqEnumStringLiteral.h"

#include "../Macros/_MainMacro.M.h"

#include "./Helper.h"
#include "../Utils/qq_throw_l.M.h"

#include "../QqThread/qq_lock.M.h"
#include "./EnumItemWrapperT.h"
#include "./Consts.h"


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
    using ValueList       = std::vector     <TEnum>;
    using NameList        = std::vector     <QqEnumString>;
    using EIMap           = std::map        <TEnum,int>;
    using EnumItemWrapper = EnumItemWrapperT<TEnum,TInt>;
    using WrapperList     = std::vector     <EnumItemWrapper>;

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
            )

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
                m_wrappers.push_back(EnumItemWrapper{ i, m_values[i], m_names[i] });

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
    className()
    {
        return m_className;
    }

    static inline char const *
    intTypeName()
    {
        return m_intTypeName;
    }

    static inline char const *
    fullClassName()
    {
        return m_fullClassName;
    }

    //
    // Range API
    //

    static inline constexpr TEnum
    firstValue() noexcept
    {
        return m_values.front();
    }

    static inline constexpr TEnum
    lastValue() noexcept
    {
        return m_values.back();
    }

    static inline constexpr int
    count() noexcept
    {
        return static_cast<int>(m_values.size());
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
    value(int index) noexcept
    {
        C::ifIndexOutOfRangeDoThrow(index, QQ_FULL_FUNC_SIG);
        return m_values[index];
    }

    static inline constexpr QqEnumString const &
    name(int index) noexcept
    {
        if (not indexInRange(index))
            return c_emptyString;

        return m_names[index];
    }

    static inline constexpr QqEnumString const &
    nameByValue(TEnum e) noexcept
    {
        int index = indexOf(e);
        if (index < 0)
            return c_emptyString;

        return name(index);
    }

    static inline constexpr EnumItemWrapper const &
    wrapper(int index, char const * methodName = nullptr) noexcept
    {
        //TODO: -
        // if (not indexInRange(index))
        //     return c_emptyWrapper;

        C::ifIndexOutOfRangeDoThrow(index, methodName ? methodName : QQ_FULL_FUNC_SIG);
        return m_wrappers[index];
    }

    static inline constexpr int
    indexOf(TEnum e) noexcept
    {
        auto & m  = eiMap();
        auto   it = m.find(e);
        if (it == m.end())
            return -1;

        return it->second;
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
    invalidValue() noexcept
    {
        return value(m_invalidValueIndex);
    }

    static inline constexpr int
    invalidValueIndex() noexcept
    {
        return m_invalidValueIndex;
    }

    static inline constexpr TEnum
    defaultValue() noexcept
    {
        return value(m_defaultValueIndex);
    }

    static inline constexpr int
    defaultValueIndex() noexcept
    {
        return m_defaultValueIndex;
    }

    static inline constexpr QqEnumString const &
    defaultValueName() noexcept
    {
        return name(m_defaultValueIndex);
    }

    static inline constexpr QqEnumString const &
    invalidValueName() noexcept
    {
        return name(m_invalidValueIndex);
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
        int index = C::ifEnumInNotRangeDoThrow(newInvalidValue, QQ_FULL_FUNC_SIG);
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
        int index = C::ifEnumInNotRangeDoThrow(newDefaultValue, QQ_FULL_FUNC_SIG);

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
    static inline EnumItemWrapper const c_emptyWrapper{ -1, TEnum{}, c_emptyString };

//
// Using-synonyms
//
private:
    using C = CoreT<TClass,TEnum,TInt>;
};


} // namespace Qq::Enum

#include "./CoreT.h"
#include "./MetadataInitializierT.h"
