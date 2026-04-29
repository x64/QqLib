#pragma once

#include <iostream>


#define qq_throw_l(EXCEPTION,TEXT)      \
    {                                   \
        std::cerr << TEXT << std::endl; \
        throw EXCEPTION{ TEXT };        \
    }
