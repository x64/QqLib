#pragma once


#include <exception>


namespace Qq::Exceptions
{


class ParseException : public std::exception
{
public:
    explicit ParseException(char const * const message) noexcept
        : exception(message)
    {}
};


} //namespace Qq::Exceptions
