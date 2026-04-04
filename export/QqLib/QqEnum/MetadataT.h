#pragma once

#include <QList>
#include <QMap>
#include <QString>
#include <QLocale>


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
    using ValueList     = QList<TEnum>;
    using NameList      = QStringList;
    using EIMap         = QMap<TEnum,int>;

};


} // end of namespace Qq::Enum

#include "./MetadataInitializierT.h"
