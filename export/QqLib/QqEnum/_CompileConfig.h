#pragma once

//
// define QQ_DONT_USE_QT_CONTAINERS for switch to std types
//

#define QQ_DONT_USE_QT
//#undef QQ_DONT_USE_QT


#ifdef QQ_DONT_USE_QT
    #define QqMap                      std::map
    #define QqList                     std::vector
#else
    #define QqMap                      QMap
    #define QqList                     QList
    // #define Qq_string                  QString
    // #define Qq_stringLiteral(TEXT)     QStringLiteral(TEXT)
    // #define QQ_ENUM_STRING_INCLUDE     <QString>
#endif
