#pragma once


#include "./_CompileConfig.h"


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
        char const * toLatin1() const noexcept
        {
            return m_str.c_str();
        }

        StringLiteral & arg(char const * argStr) noexcept
        {
            return * replaceAllEntries(m_currentArgNum++, argStr, this);
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

            for (int i = str.size() -1; i >= 0; --i)
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
                * replaceCharCount = buff.size();

            return std::atoi(buff.data());
        }

    };


} // namespace Qq::Enum

using QqEnumStringLiteral = Qq::Enum::StringLiteral;

#else

using QqEnumStringLiteral = QStringLiteral;

#endif
