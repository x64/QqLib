#pragma once


#include "./_CompileConfig.h"

#ifdef QQ_DONT_USE_QT
    #include <string>
    using QqEnumString = std::string;
#else
    #include <QString>
    using QqEnumString = QString;
#endif
