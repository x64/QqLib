#include <QTest>

// add necessary includes here
#include "../../export/QqLib/QqEnum/CoreT.h"


class QqEnumCoreT : public QObject
{
    Q_OBJECT

public:
    QqEnumCoreT();
    ~QqEnumCoreT();

private slots:
    void test_case1();
};

QqEnumCoreT::QqEnumCoreT()
{}

QqEnumCoreT::~QqEnumCoreT()
{}

void QqEnumCoreT::test_case1()
{
    struct Enum
    {
        enum _Enum { a,b,c };

    };

    //Qq::Enum::CoreT<>
}

QTEST_APPLESS_MAIN(QqEnumCoreT)

#include "tst_QqEnumCoreT.moc"
