#pragma once

// #include <QList>
// #include <QMap>
#include <QLocale>


#include "./_CompileConfig.h"
#include QQ_ENUM_QQ_STRING_INCLUDE

#include "./Helper.h"


namespace Qq::Enum
{


template <typename TClass, typename TEnum, typename TInt =int>
struct MetadataT
{
//
// Types
//
protected:
    using H             = Helper;
public:
    using ValueList     = std::vector<TEnum>;       //QList<TEnum>;
    using NameList      = std::vector<Qq_string>;   //QStringList;
    using EIMap         = std::map   <TEnum,int>;   //QMap<TEnum,int>;

//
// Friends
//
private:
    template <typename T_Class, typename T_Enum, typename T_Int>
    friend struct MetadataInitializierT;

    template <typename T_Class, typename T_Enum, typename T_Int>
    friend class CoreT;

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
    }

//
// Internal API
//
protected:
    static inline constexpr int
    indexOf(TEnum const e) noexcept {
        return m_enumToIndex[e];
    }

//
// Public API
//
public:
    static inline constexpr ValueList const &
    values() noexcept {
        return m_values;
    }

    static inline constexpr NameList const &
    names() noexcept {
        return m_names;
    }

    static inline constexpr EIMap const &
    eiMap() noexcept {
        return m_enumToIndex;
    }

    static inline constexpr TEnum
    value(int index) noexcept
    {
        // TODO: add bounds checking
        return m_values[index];
    }

    static inline constexpr Qq_string const &
    name(int index) noexcept
    {
        // TODO: add bounds checking
        return m_names[index];
    }

    static inline constexpr int
    valueCount() noexcept {
        return m_values.size();
    }

//
// Fields:
//
protected:
    static inline ValueList m_values;
    static inline NameList  m_names;
    static inline EIMap     m_enumToIndex;
};


} // namespace Qq::Enum

#include "./MetadataInitializierT.h"
