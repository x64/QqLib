// #include <QCoreApplication>

 #include <vector>
// #include <iostream>


#include "../src/QqEnum/_CompileConfig.h"
#include "../src/QqEnum/QqEnumString.h"
#include "../src/QqEnum/Index.h"
#include "../src/QqEnum/IteratorT.h"


static char const * const
boolToStr(bool res)
{
    return res ? "true" : "false";
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


enum TEnum : int
{a0,b0,c0,d0,e0,f0,g0};



class EnumItem
{
    TEnum       m_value;
    std::string m_name;

public:
    EnumItem(TEnum aValue, std::string const & aName)
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

    std::string const & name() const noexcept {
        return m_name;
    }
};


std::vector<TEnum>       enums{ TEnum::a0, TEnum::b0, TEnum::c0, TEnum::d0, TEnum::e0, TEnum::f0, TEnum::g0 };
std::vector<std::string> names{ "TEnum::a0", "TEnum::b0", "TEnum::c0", "TEnum::d0", "TEnum::e0", "TEnum::f0", "TEnum::g0" };


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

#include "../src/QqEnum/QqEnumStringLiteral.h"
void getArgNum_example()
{
    using std::cout;
    using std::endl;

    QqEnumStringLiteral sl{ "%1 function %2 %1 lambda %3" };
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

#include "../src/QqEnum/QqEnum.M.h"

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

#ifdef QQ_DONT_USE_QT
    #define TO_STD_STRING
#else
    #define TO_STD_STRING .toStdString()
#endif

void Enum1_example()
{
    using namespace std;

    Enum1 e1, e2;
    cout << e1._invalid()                  << endl;
    cout << e1._default()                  << endl;
    cout << e1._count()                    << endl;
    cout << e1().value()                   << endl;
    cout << e1().isInvalid()               << endl;
    cout << e1().isDefault()               << endl;
    cout << e1().name()TO_STD_STRING       << endl;
    cout << e1._invalidName()TO_STD_STRING << endl;
    cout << e1._defaultName()TO_STD_STRING << endl;
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
    cout << "e1().value(): "     << e1().value()             << endl;
    cout << "e1().name():  "     << e1().name()TO_STD_STRING << endl;
    cout << "e1().asInt(): "     << e1().asInt()             << endl;
    cout << "e1().isInvalid(): " << e1().isInvalid()         << endl;
    cout << "e1().isDefault(): " << e1().isDefault()         << endl;

    cout << "\n\n\n";

    Qq::Enum::IteratorT<Enum1,Enum1::_Enum,Enum1::_Int> iter1, iter2{4}, iter3;
    iter1 += 2;
    cout << "value: "       << iter1->value()
         << "\nname: "      << iter1->name()TO_STD_STRING
         << "\nasInt: "     << iter1->asInt()
         << "\nisInvalid: " << iter1->isInvalid()
         << "\nisDefault: " << iter1->isDefault()
         << endl;

    iter3 = iter1+iter2;
    cout << "iter3.index(): " << iter3.index() << endl;

    auto e2 = e1;
    Enum1 e3{ 0 };
}

void IteratorWrapper_example()
{
    using namespace std;

    Enum1 e1;

    // variable "w" is "Qq::Enum::EnumItemWrapperT<Enum1,Enum1::_Enum,Enum1::_Int> const &"
    for (auto const & w : Enum1::_range(0,3/*e1.Two, e1.Five*/))
    {
        cout << w.name()TO_STD_STRING << ", isDefault: " << w.isDefault() << ", isInvalid: " << w.isInvalid() << endl;
    }

}

void TryParse_example()
{
    using namespace std;

    Enum1 e1;

    bool res;

    res = Enum1::_tryParse("one");
    cout << "Enum1::_tryeParse('one') is " << boolToStr(res) << endl;

    res = Enum1::_tryParse("one", nullptr, false);
    cout << "Enum1::_tryeParse('one', nullptr, false) is " << boolToStr(res) << endl;

    res = Enum1::_tryParse("One", nullptr, false);
    cout << "Enum1::_tryeParse('One', nullptr, false) is " << boolToStr(res) << endl;

    res = Enum1::_tryParse("Ones");
    cout << "Enum1::_tryeParse('Ones') is " << boolToStr(res) << endl;
}

void Parse_example()
{
    using namespace std;

    auto e1 = Enum1::_parse("Two");
    cout << "e1 = Enum1::_parse(''Two''); e1._name(): " << e1._name()TO_STD_STRING << endl;

    cout << "BEFORE auto e2 = Enum1::_parse(''five'');..." << endl;
    auto e2 = Enum1::_parse("five");
    cout << "e2 = Enum1::_parse(''five''); e2._name(): " << e2._name()TO_STD_STRING << endl;
}

void Enum_arithmetics_example()
{
    using namespace std;

    Enum1 e1, e2{1}, e3;

    cout << "initial e1 = " << e1().asInt() << ", " << e1().name() << endl;
    cout << "++e1 = " << (++e1)().asInt() << endl;
    cout << "--e1 = " << (--e1)().asInt() << endl;
    cout << "e1++ = " << (e1++)().asInt() << endl;
    cout << "e1-- = " << (e1++)().asInt() << endl;

    e1 += 2;
    cout << "e1 += 2 = " << e1().asInt() << endl;

    e1 -= 2;
    cout << "e1 -= 2 = " << e1().asInt() << endl;

    e3 = e1+e2;
    cout << "e3 = e1 + e2: " << e3().asInt() << endl;

    e3 = e1-e2;
    cout << "e3 = e1 - e2: " << e3().asInt() << endl;

    e1 = Enum1::One;
    cout << "e1 == Enum1::One, is true? " << boolToStr(Enum1::One == e1) << endl;

    e3 = 10;
    e3 = static_cast<Enum1::_Enum>(10);
}

void Enum1_comparsion_example()
{
    using namespace std;

    Enum1 e1, e2{5};

    cout << "e1 == e2: " << boolToStr(e1 == e2) << " (" << e1._int() << ", " << e2._int() << ")" << endl;
    cout << "e1 != e2: " << boolToStr(e1 != e2) << " (" << e1._int() << ", " << e2._int() << ")" << endl;
    cout << "\n";
    cout << "e1 < e2: " << boolToStr(e1 < e2) << " (" << e1._int() << ", " << e2._int() << ")" << endl;
    cout << "e1 > e2: " << boolToStr(e1 > e2) << " (" << e1._int() << ", " << e2._int() << ")" << endl;
    cout << "\n";
    cout << "e1 <= e2: " << boolToStr(e1 <= e2) << " (" << e1._int() << ", " << e2._int() << ")" << endl;
    cout << "e1 >= e2: " << boolToStr(e1 >= e2) << " (" << e1._int() << ", " << e2._int() << ")" << endl;
    cout << "\n";
    cout << "e2 > 3: " << boolToStr(e2 > 3) << endl;
    cout << "3 < e2: " << boolToStr(3 < e2) << endl;
    cout << "\n";
    cout << "e2 > Enum1::Three : " << boolToStr(e2 > Enum1::Three) << endl;
    cout << "Enum1::Three < e2 : " << boolToStr(Enum1::Three < e2) << endl;

}

void Enum1_methods_example()
{
    using namespace std;

    Enum1 e1{Enum1::Unknown};

    cout << "e1._className(): "                 << e1._className()                          << endl;
    cout << "e1._intTypeName(): "               << e1._intTypeName()                        << endl;
    cout << "e1._fullClassName(): "             << e1._fullClassName()                      << endl;
    cout << "e1._first(): "                     << e1._first()                              << endl;
    cout << "e1._last(): "                      << e1._last()                               << endl;
    cout << "e1._count(): "                     << e1._count()                              << endl;
    cout << "e1._min(): "                       << e1._min()                                << endl;
    cout << "e1._max(): "                       << e1._max()                                << endl;
    cout << "e1._int(): "                       << e1._int()                                << endl;
    cout << "e1._value(): "                     << e1._value()                              << endl;
    cout << "e1._name(): "                      << e1._name()                               << endl;
    cout << "Enum1::_nameByValue(Enum1::One): " << Enum1::_nameByValue(Enum1::One)          << endl;
    cout << "e1(): "                                                   << endl
                << "  .value(): "    << e1().value()                   << endl
                << "  .name(): "     << e1().name()                    << endl
                << "  .index(): "    << e1().index()                   << endl
                << "  .asInt(): "    << e1().asInt()                   << endl
                << "  .isInvalid(): "<< boolToStr(e1().isInvalid())    << endl
                << "  .isDefault(): "<< boolToStr(e1().isDefault())    << endl
                << endl;
    cout << "e1._isInvalid(): "                 << boolToStr(e1._isInvalid())               << endl;
    cout << "e1._isDefault(): "                 << boolToStr(e1._isDefault())               << endl;
    cout << "e1._isInvalidDefined(): "          << boolToStr(e1._isInvalidDefined())        << endl;
    cout << "e1._isDefaultDefined(): "          << boolToStr(e1._isDefaultDefined())        << endl;
    cout << "e1._invalid(): "                   << e1._invalid()                            << endl;
    cout << "e1._default(): "                   << e1._default()                            << endl;
    cout << "e1._invalidIndex(): "              << e1._invalidIndex()                       << endl;
    cout << "e1._defaultIndex(): "              << e1._defaultIndex()                       << endl;
    cout << "e1._invalidName(): "               << e1._invalidName()                        << endl;
    cout << "e1._defaultName(): "               << e1._defaultName()                        << endl;
}

void Wrapper_conversion_example()
{
    using namespace std;

    auto w1 = Enum1::_wrapper(1);
    auto w2 = Enum1::_wrapper(5);

    cout << " w1 = " << w1.value() << " w2 = " << w2.value() << endl;
    cout << " w2 = " << w1.value() << " w2 = " << w2.value() << endl;
    cout << endl;

    cout << " w1 >  w2:         " << boolToStr(w1 >  w2        ) << endl;
    cout << " w1 >  w2.value(): " << boolToStr(w1 >  w2.value()) << endl;
    cout << " w1 <  w2:         " << boolToStr(w1 <  w2        ) << endl;
    cout << " w1 <  w2.value(): " << boolToStr(w1 <  w2.value()) << endl;
    cout << endl;
    cout << " w1 >= w2:         " << boolToStr(w1 >= w2        ) << endl;
    cout << " w1 >= w2.value(): " << boolToStr(w1 >= w2.value()) << endl;
    cout << " w1 <= w2:         " << boolToStr(w1 <= w2        ) << endl;
    cout << " w1 <= w2.value(): " << boolToStr(w1 <= w2.value()) << endl;
    cout << endl;
    cout << " w1 == w2:         " << boolToStr(w1 == w2        ) << endl;
    cout << " w1 == w2.value(): " << boolToStr(w1 == w2.value()) << endl;
    cout << " w1 != w2:         " << boolToStr(w1 != w2        ) << endl;
    cout << " w1 != w2.value(): " << boolToStr(w1 != w2.value()) << endl;
}

void IterationByIterator_example()
{
    using namespace std;

    cout << "--------------------------------\n"
         << "direct order  example: _range()\n"
         << "--------------------------------\n"
         << "\n";
    for ( auto const & w : Enum1::_range())
    {
        cout << "wrapper by _range(): " << endl;
        cout << "   .name(): "      << w.name()                     << endl;
        cout << "   .value(): "     << w.value()                    << endl;
        cout << "   .asInt(): "     << w.asInt()                    << endl;
        cout << "   .isInvalid(): " << boolToStr(w.isInvalid())     << endl;
        cout << "   .isDefault(): " << boolToStr(w.isDefault())     << endl;
        cout << endl;
    }

    cout << "-----------------------------------\n"
         << "reverse order example: _range_r()\n"
         << "-----------------------------------\n"
         << "\n";
    for ( auto const & w : Enum1::_range_r())
    {
        cout << "wrapper by _range_r(): "                           << endl;
        cout << "   .name(): "      << w.name()                     << endl;
        cout << "   .value(): "     << w.value()                    << endl;
        cout << "   .asInt(): "     << w.asInt()                    << endl;
        cout << "   .isInvalid(): " << boolToStr(w.isInvalid())     << endl;
        cout << "   .isDefault(): " << boolToStr(w.isDefault())     << endl;
        cout << endl;
    }

    cout << "------------------------------------------------------------\n"
         << "direct order example: _range(Enum1::Unknown, Enum1::Three)\n"
         << "------------------------------------------------------------\n"
         << "\n";
    for ( auto const & w : Enum1::_range(Enum1::Unknown, Enum1::Three))
    {
        cout << "wrapper by _range(Enum1::Unknown, Enum1::Three): " << endl;
        cout << "   .name(): "      << w.name()                     << endl;
        cout << "   .value(): "     << w.value()                    << endl;
        cout << "   .asInt(): "     << w.asInt()                    << endl;
        cout << "   .isInvalid(): " << boolToStr(w.isInvalid())     << endl;
        cout << "   .isDefault(): " << boolToStr(w.isDefault())     << endl;
        cout << endl;
    }

    cout << "---------------------------------------------------------------\n"
         << "reverse order example: _range_r(Enum1::Unknown, Enum1::Three)\n"
         << "---------------------------------------------------------------\n"
         << "\n";
    for ( auto const & w : Enum1::_range_r(Enum1::Unknown, Enum1::Three))
    {
        cout << "wrapper by _range_r(Enum1::Unknown, Enum1::Three): " << endl;
        cout << "   .name(): "      << w.name()                     << endl;
        cout << "   .value(): "     << w.value()                    << endl;
        cout << "   .asInt(): "     << w.asInt()                    << endl;
        cout << "   .isInvalid(): " << boolToStr(w.isInvalid())     << endl;
        cout << "   .isDefault(): " << boolToStr(w.isDefault())     << endl;
        cout << endl;
    }

    cout << "-------------------------------------------------------------\n"
         << "reverse order  example: _range(Enum1::Three, Enum1::Unknown)\n"
         << "-------------------------------------------------------------\n"
         << "\n";
    for ( auto const & w : Enum1::_range(Enum1::Three, Enum1::Unknown))
    {
        cout << "wrapper by _range(Enum1::Three, Enum1::Unknown): " << endl;
        cout << "   .name(): "      << w.name()                     << endl;
        cout << "   .value(): "     << w.value()                    << endl;
        cout << "   .asInt(): "     << w.asInt()                    << endl;
        cout << "   .isInvalid(): " << boolToStr(w.isInvalid())     << endl;
        cout << "   .isDefault(): " << boolToStr(w.isDefault())     << endl;
        cout << endl;
    }

}

int main(int argc, char *argv[])
{
    RUN_EXAMPLE(Enum_arithmetics_example)
    RUN_EXAMPLE(Enum1_comparsion_example)
    RUN_EXAMPLE(Enum1_methods_example)
    RUN_EXAMPLE(Wrapper_conversion_example)
    RUN_EXAMPLE(IteratorWrapper_example)
    RUN_EXAMPLE(IterationByIterator_example)
    return 0;
    RUN_EXAMPLE(Parse_example)
    RUN_EXAMPLE(TryParse_example)
    RUN_EXAMPLE(getArgNum_example)
    RUN_EXAMPLE(s3_example)
    RUN_EXAMPLE(Enum1_example)
    RUN_EXAMPLE(Index_example)
    RUN_EXAMPLE(Iterator_example)


    return 0;

    //Qq_string s{ "" };

    //QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    //-
    // int itemCount = enums.size();
    // std::vector<EnumItem> items{ itemCount };

    // for (int i = 0; i < itemCount; ++i)
    // {
    //     items[i] = EnumItem{ enums[i], names[i] };
    // }

    return 0; //a.exec();
}
