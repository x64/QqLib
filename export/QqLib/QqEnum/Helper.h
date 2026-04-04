#pragma once

#include <QMap>
#include <QList>


namespace Qq::Enum
{


///
/// \brief Methods for initializing arrays of QQ_ENUM_CORE
///
struct Helper
{
    template <typename TEnum>
    static QMap<TEnum,int>
    makeEnumToIndexMap(QList<TEnum> const & valueList) noexcept
    {
        QMap<TEnum,int> res;

        int count = static_cast<int>(valueList.count());

        for (int i = 0; i < count; ++i)
        {
            TEnum const & e = valueList[i]; //-V108
            res[e] = i;
        }

        return res;
    }

    static QString
    parseEnumValueName(char const * str) noexcept
    {
        QString res = QString{ str }
            .split('=', Qt::SplitBehaviorFlags::SkipEmptyParts)
            .first()
            .trimmed();
        res.shrink_to_fit();

        return res;
    }
};


} // namespace Qq::Enum
