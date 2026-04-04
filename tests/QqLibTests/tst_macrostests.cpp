#include <QTest>

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

void MacrosTests::test_case1()
{
    QVERIFY(1 == 0);
}

QTEST_APPLESS_MAIN(MacrosTests)

#include "tst_macrostests.moc"
