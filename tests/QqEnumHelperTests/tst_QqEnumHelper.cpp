#include <QTest>

// add necessary includes here
#include "QDebug"

#include "../../export/QqLib/QqEnum/Helper.h"


class QqEnumHelper : public QObject
{
    Q_OBJECT

public:
    QqEnumHelper();
    ~QqEnumHelper();

private slots:
    void parseEnumValueName_test();
};



QqEnumHelper::QqEnumHelper()
{}

QqEnumHelper::~QqEnumHelper()
{}

void QqEnumHelper::parseEnumValueName_test()
{
    using H = Qq::Enum::Helper;

    qDebug() << "01:" << H::parseEnumValueName("  EnumValue= 10");
    qDebug() << "02:" << H::parseEnumValueName("  EnumValue    =1+ 10");
}

QTEST_APPLESS_MAIN(QqEnumHelper)

#include "tst_QqEnumHelper.moc"
