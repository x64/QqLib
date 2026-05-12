#include <QCoreApplication>

#include <QList>
#include <iostream>


#include "../export/QqLib/QqEnum/_CompileConfig.h"
#include "../export/QqLib/QqEnum/QqEnumString.h"
#include "../export/QqLib/QqEnum/Index.h"
#include "../export/QqLib/QqEnum/IteratorT.h"


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


namespace NS0
{

struct Test
{
    char const * m_str;

    Test(char const * str)
        : m_str{ str }
    {}

    static void funcName()
    {
        std::cout << __FUNCSIG__ << std::endl;
    }
};

} // namespace NS0


static bool m_isCreated;

static char const *
gfcn(char const * fcnStr)
{
    static std::string res{ fcnStr };
    if (not m_isCreated)
    { //  SS::S3::__fullName(void)
        int i = res.length() -1;
        for (; i > 2; --i)
            if (':' == res[i] && ':' == res[i-1]) break;

        --i;
        int len = 0;
        while (i > 0 && res[i] != ' ')
            --i, ++len;
        res = res.substr(i, len);
    }
    return res.c_str();
}

#define QQ_TEST                                         \
    static char const * __fullName() {                  \
        return __FUNCSIG__;                             \
    }                                                   \
    static inline NS0::Test _t{ gfcn(__fullName()) };

namespace SS {
struct S3
{
    QQ_TEST
};
}

#include "../export/QqLib/QqEnum/QqEnumStringLiteral.h"
void getArgNum_example()
{
    using Qq::Enum::StringLiteral;
    using std::cout;
    using std::endl;

    StringLiteral sl{ "%1 function %2 %1 lambda %3" };
    sl.arg(__FUNCSIG__).arg("#2").arg("#3");

    //cout << sl.toLatin1() << endl;
    NS0::Test::funcName();

}

void s3_example()
{
    using std::cout;
    using std::endl;

    SS::S3 s3;
    cout << s3._t.m_str << endl;
}

#include "../export/QqLib/QqEnum/QqEnum.m.h"

struct Enum1
{
    QQ_ENUM_CORE(Enum1,
        Unknown = 0,

        One,
        Two,
        Three,
        Four,
        Five
    )

    QQ_ENUM_INVALID_VALUE(Unknown)
    QQ_ENUM_DEFAULT_VALUE(One)
};

void Enum1_example()
{
    using namespace std;

    Enum1 e1, e2;
    cout << e1._invalid()     << endl;
    cout << e1._default()     << endl;
    cout << e1._count()       << endl;
    cout << e1().name()       << endl;
    cout << e1().value()      << endl;
    cout << e1().isInvalid()  << endl;
    cout << e1().isDefault()  << endl;
    cout << e1._invalidName() << endl;
    cout << e1._defaultName() << endl;


}

void Index_example()
{
    using namespace std;

    Qq::Enum::Index i1{0}, i2{2};

    cout << "0. i1: " << i1 << endl;
    cout << "0. i2: " << i2 << endl;

    i1 = i2;
    cout << "1. i1 = i2;" << endl;
    cout << "1. i1: " << i1 << endl;
    cout << "1. i2: " << i2 << endl;

    i1 = 10;
    ++i2;

    cout << "2. i1 = 10; ++i2" << endl;
    cout << "2. i1: " << i1 << endl;
    cout << "2. i2: " << i2 << endl;

    auto i3 = i2 +5;
    cout << "3. i3 = i2 +5\n";
    cout << "3. i3: " << i3 << endl;

    cout << "4. i3++: " << i3++ << endl;
}

void Iterator_example()
{
    using namespace std;

    Enum1 e1{0};
    cout << "e1().value(): "     << e1().value()     << endl;
    cout << "e1().name():  "     << e1().name()      << endl;
    cout << "e1().asInt(): "     << e1().asInt()     << endl;
    cout << "e1().isInvalid(): " << e1().isInvalid() << endl;
    cout << "e1().isDefault(): " << e1().isDefault() << endl;

    cout << "\n\n\n";

    Qq::Enum::IteratorT<Enum1,Enum1::_Enum,Enum1::_Int> iter;
    iter += 2;
    cout << "value: "       << iter->value()
         << "\nname: "      << iter->name()
         << "\nasInt: "     << iter->asInt()
         << "\nisInvalid: " << iter->isInvalid()
         << "\nisDefault: " << iter->isDefault()
         << endl;

    auto e2 = e1;
    Enum1 e3{0};
}

void IteratorWrapper_example()
{
    using namespace std;

    Enum1 e1;

    // variable "w" is "Qq::Enum::EnumItemWrapperT<Enum1,Enum1::_Enum,Enum1::_Int> const &"
    for (auto const & w : e1._iter(0/*e1.Two, e1.Five*/))
    {
        cout << w.name() << ", isDefault: " << w.isDefault() << ", isInvalid: " << w.isInvalid() << endl;
    }

}

void printExampleName(char const * name)
{
    using namespace std;
    cout << "--------------------------------------------------------\n"
         << "EXAMPLE: " << name << "\n"
         << "--------------------------------------------------------\n"
         ;
}

#define RUN_EXAMPLE(example)    \
    printExampleName(#example); \
    example();                  \
    putFreeLines();


void putFreeLines()
{
    std::cout << "--------------------------------------------------------\n\n\n";
}

int main(int argc, char *argv[])
{
    RUN_EXAMPLE(getArgNum_example)
    RUN_EXAMPLE(s3_example)
    RUN_EXAMPLE(Enum1_example)
    RUN_EXAMPLE(Index_example)
    RUN_EXAMPLE(Iterator_example)
    RUN_EXAMPLE(IteratorWrapper_example)

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
