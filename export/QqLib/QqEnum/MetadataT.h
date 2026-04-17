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

//
// Ctors & Dtor
//
public:
    MetadataT(ValueList && valueList, NameList && nameList)
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

    static inline constexpr void
    setInvalidValue(TEnum const newInvalidValue)
    {
        auto it = eiMap().find(newInvalidValue);
        if (it == eiMap().end())
            throw std::out_of_range{
                StringLiteral{ "%1: the `%2` is out of range of QqEnum." }
                    .arg(QQ_FULL_FUNC_SIG)
                    .arg(static_cast<TInt>(newInvalidValue))
                    .toLatin1()
            };

        qq_lock
        {
            m_invalidValueDefined = true;
            m_invalidValue        = newInvalidValue;
            m_invalidValueIndex   = it->second(); //- indexOf(newInvalidValue);
        }
    }

private:
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
    value(int index) /*noexcept*/
    {
        // TODO: add bounds checking
        return m_values[index];
    }

    static inline constexpr QqEnumString const &
    name(int index) /*noexcept*/
    {
        // TODO: add bounds checking
        return m_names[index];
    }

    static inline constexpr EnumItemWrapper const &
    wrapper(int index) /*noexcept*/
    {
        // TODO: add bounds checking
        return m_wrappers[index];
    }

    static inline constexpr int
    count() noexcept
    {
        return m_values.size();
    }

//
// Fields:
//
private: //~ protected:
    static inline ValueList   m_values;
    static inline NameList    m_names;
    static inline EIMap       m_enumToIndex;
    static inline WrapperList m_wrappers;

    static inline bool        m_invalidValueDefined = false;
    static inline TEnum       m_invalidValue;
    static inline int         m_invalidValueIndex = -1;

    static inline TEnum       m_minValue;
    static inline TEnum       m_maxValue;

};


} // namespace Qq::Enum

#include "./MetadataInitializierT.h"
