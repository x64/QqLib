#include <QTest>

// add necessary includes here
#include <QDebug>

#include "../../src/Helpers/Main.h"



class QqHelper : public QObject
{
    Q_OBJECT

public:
    QqHelper();
    ~QqHelper();

private slots:
    void trim_test01();
    void trim_test02();

    void inMinMax_test01();
    void inMinMax_test02();
    void inMinMax_test03();
    void inMinMax_test04();
};

QqHelper::QqHelper()
{}

QqHelper::~QqHelper()
{}

void QqHelper::trim_test01()
{
    const char * str = "  +lastPos+ ";

    qDebug() << "01:"<< Qq::Helpers::Main::trim(str);
}

void QqHelper::trim_test02()
{
    const char * str = "+lastPos+";

    qDebug() << "02:"<< Qq::Helpers::Main::trim(str);
}


void QqHelper::inMinMax_test01()
{
    int min = 1;
    int max = 10;
    int x   = 0;

    bool res = Qq::Helpers::Main::inMinMax(min, x, max);

    QVERIFY( res);
}

void QqHelper::inMinMax_test02()
{
    int min = 1;
    int max = 10;
    int x   = 1;

    bool res = Qq::Helpers::Main::inMinMax(min, x, max);

    QVERIFY( res);
}

void QqHelper::inMinMax_test03()
{
    int min = 1;
    int max = 10;
    int x   = 11;

    bool res = Qq::Helpers::Main::inMinMax(min, x, max);

    QVERIFY( res );
}

void QqHelper::inMinMax_test04()
{
    int min = 10;
    int max = 1;
    int x   = 1;

    bool res = Qq::Helpers::Main::inMinMax(min, x, max);

    QVERIFY( res );
}


QTEST_APPLESS_MAIN(QqHelper)

#include "tst_QqHelper.moc"
