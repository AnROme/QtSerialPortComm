#include <QString>
#include <QtTest>
#include <../src/arrayTemp.h>

class TestTemplateByteArray : public QObject
{
    Q_OBJECT

public:
    TestTemplateByteArray();

private Q_SLOTS:
    void testCase1();
    void testCase2();
};

TestTemplateByteArray::TestTemplateByteArray()
{

}

struct transferPacket{
    int a;
    short int b;
    short int c;

    bool operator==(struct transferPacket packet){
        return ((packet.a == this->a) && (packet.c == this->c) && (packet.b == this->b));
    }
};

void TestTemplateByteArray::testCase1()
{

    ByteArrayExtend b;
    qint8 val= 57;

    b.append_extend(val);

    qint8 vecRead;

    b.Read(0, vecRead);
    Q_ASSERT(vecRead == 57);
    QVERIFY2(true, "Failure");
}

void TestTemplateByteArray::testCase2()
{
    transferPacket packet = {1, -4, 5};
    ByteArrayExtend b;

    b.append_extend(packet);

    transferPacket reader;

    b.Read(0, reader);
    Q_ASSERT(packet == reader);
    QVERIFY2(true, "Failure");
}


QTEST_APPLESS_MAIN(TestTemplateByteArray)

#include "tst_testtemplatebytearray.moc"
