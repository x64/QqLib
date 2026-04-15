#include <QTest>

// add necessary includes here
#include <iostream>


// #include "P:/Projects/Free/QqLib/export/QqLib/QqEnum/_CompileConfig.h"
// #include QQ_ENUM_QQ_STRING_INCLUDE

#include "P:/Projects/Free/QqLib/export/QqLib/QqEnum/QqEnumStringLiteral.h"

class QqEnumStringLiteralTests : public QObject
{
    Q_OBJECT

public:
    QqEnumStringLiteralTests();
    ~QqEnumStringLiteralTests();

private slots:
    void getArgNum_test();
};

QqEnumStringLiteralTests::QqEnumStringLiteralTests() {}

QqEnumStringLiteralTests::~QqEnumStringLiteralTests() {}

void QqEnumStringLiteralTests::getArgNum_test()
{
    using Qq::Enum::StringLiteral;
    using std::cout;
    using std::endl;

    StringLiteral sl{ "%1 function %2 %1 lambda %3" };
    sl.arg(__FUNCTION__).arg("#2").arg("#3");

    cout << sl.toLatin1() << endl;
}

QTEST_APPLESS_MAIN(QqEnumStringLiteralTests)

#include "tst_QqEnumStringLiteral.moc"
