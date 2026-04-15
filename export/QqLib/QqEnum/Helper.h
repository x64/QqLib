#pragma once

// #include <QMap>
// #include <QList>
#include <vector>
#include <map>


#include "./_CompileConfig.h"
#include "../QqEnum/QqEnumString.h"

#include "../Helper.h"


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
        using H = Qq::Helper;

        std::string res{ str };

        int pos = res.find('=');
        if (std::string::npos != pos)
            res = res.substr(0, pos);

        res = H::trim(res.c_str());

        return res;
    }

    // static std::string
    // parseEnumValueName2(char const * str) noexcept
    // {
    //     using H = Qq::Helper;

    //     std::string res;
    //     size_t      len = std::strlen(str);

    //     if (len == 0)
    //         return res;

    //     int i;
    //     for (i = 0; i < len; ++i)
    //         if ('=' == str[i]) break;

    //     if (i < len)
    //         res = std::string(str, i);

    //     res = H::trim(res.c_str());

    //     return res;
    // }
};


} // namespace Qq::Enum
