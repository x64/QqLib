#include <QCoreApplication>

#include <QList>
#include <iostream>


#include "../export/QqLib/QqEnum/_CompileConfig.h"
#include QQ_ENUM_QQ_STRING_INCLUDE


enum TEnum : int
{a0,b0,c0,d0,e0,f0,g0};



class EnumItem
{
    TEnum   m_value;
    QString m_name;

public:
    EnumItem(TEnum aValue, QString const & aName)
        : m_value{ aValue }
        , m_name { aName  }
    {}

    EnumItem() = default;

    bool operator < (const EnumItem & other) const noexcept {
         return m_value < other.m_value;
    }

    TEnum value() const noexcept {
        return m_value;
    }

    QString const & name() const noexcept {
        return m_name;
    }
};


QList<TEnum>   enums{ TEnum::a0, TEnum::b0, TEnum::c0, TEnum::d0, TEnum::e0, TEnum::f0, TEnum::g0 };
QList<QString> names{ "TEnum::a0", "TEnum::b0", "TEnum::c0", "TEnum::d0", "TEnum::e0", "TEnum::f0", "TEnum::g0" };


#include "P:/Projects/Free/QqLib/export/QqLib/QqEnum/QqEnumStringLiteral.h"
void getArgNum_test()
{
    using Qq::Enum::QqEnumStringLiteral;
    using std::cout;
    using std::endl;

    QqEnumStringLiteral sl{ "%1 function %2 %1 lambda %3" };
    sl.arg(__FUNCTION__).arg("#2").arg("#3");

    cout << sl.toLatin1() << endl;
}


int main(int argc, char *argv[])
{
    getArgNum_test();
    return 0;

    //Qq_string s{ "" };

    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    int itemCount = enums.size();
    QList<EnumItem> items{ itemCount };

    for (int i = 0; i < itemCount; ++i)
    {
        items[i] = EnumItem{ enums[i], names[i] };
    }

    return 0; //a.exec();
}
