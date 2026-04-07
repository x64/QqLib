#pragma once

//
// define QQ_DONT_USE_QT_CONTAINERS for switch to std types
//

#define QQ_DONT_USE_QT_CONTAINERS


#ifdef QQ_DONT_USE_QT_CONTAINERS
    #define QqMap                      std::map
    #define QqList                     std::vector
    #define Qq_string                  std::string
    #define QQ_ENUM_QQ_STRING_INCLUDE  <string>
#else
    #define QqMap                      QMap
    #define QqList                     QList
    #define Qq_string                  QString
    #define QQ_ENUM_STRING_INCLUDE     <QString>
#endif
