#pragma once

#include <string>


namespace Qq
{


struct Helper
{
    static std::string
    trim(char const * str)
    {
        size_t count = std::strlen(str);

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
