#include <QTest>

#include <vector>

// add necessary includes here

class MacrosTests : public QObject
{
    Q_OBJECT

public:
    MacrosTests();
    ~MacrosTests();

private slots:
    void initTestCase();
    void test_case1();
};


MacrosTests::MacrosTests()
{}

MacrosTests::~MacrosTests()
{}

void MacrosTests::initTestCase()
{}


// enum TEnum : int
// {a0,b0,c0,d0,e0,f0,g0};

// std::vector<TEnum> list{ a0,b0,c0,d0,e0,f0,g0 };

// TEnum getEnum(int index) {
//     return list[index];
// }

// void MacrosTests::test_case1()
// {
//     //QVERIFY(1 == 0);

//     TEnum e1 = getEnum(10);
//     qDebug() << "before, [1] =" << e1;

//     e1 = TEnum::c0;
//     qDebug() << "after, [1] = " << getEnum(1);

//     //TEnum e2 = getEnum(1);
// }

#include "../../export/QqLib/QqEnum/_CompileConfig.h"
#include "../../export/QqLib/QqEnum/QqEnumString.h"


//
// \brief Tuple for the enum value and the name enum.
//
template < typename TEnum >
class EnumItemT
{
    TEnum             m_value;
    QqEnumString const * m_pName;

public:
    EnumItemT(TEnum aValue, QqEnumString const & aName)
        : m_value{ aValue   }
        , m_pName{ & aName  }
    {}

    EnumItemT() = default;

    bool operator == (const EnumItemT & other) const noexcept {
        return m_value == other.m_value;
    }
    bool operator == (TEnum const & otherEnum) const noexcept {
        return m_value == otherEnum;
    }

    bool operator < (const EnumItemT & other) const noexcept {
         return m_value < other.m_value;
    }
    bool operator < (TEnum const & otherEnum) const noexcept {
         return m_value < otherEnum;
    }

    bool operator > (const EnumItemT & other) const noexcept {
         return m_value > other.m_value;
    }
    bool operator > (TEnum const & otherEnum) const noexcept {
         return m_value > otherEnum;
    }

    TEnum value() const noexcept {
        return m_value;
    }

    QqEnumString const & name() const noexcept {
        return * m_pName;
    }
};


enum TEnum2
{a0,b0,c0,d0,e0,f0,g0};


void MacrosTests::test_case1()
{
    using _EnumItem = EnumItemT<TEnum2>;

    // Qq_string name{ "a0" };
    // _EnumItem en1{ a0, name };
    _EnumItem en1{ a0, "a0" };
    _EnumItem en2 = en1;

    qDebug() << "value:" << en2.value() << "name:" << en2.name();
    //qDebug() << "value:" << en1.value() << "name:" << en1.name();
}





QTEST_APPLESS_MAIN(MacrosTests)

#include "tst_Macros.moc"
