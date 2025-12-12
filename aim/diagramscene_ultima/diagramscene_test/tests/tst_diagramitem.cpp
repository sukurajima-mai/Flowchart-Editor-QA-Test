#include <QCoreApplication>
#include <QTest>
#include <QMenu>
#include <QGraphicsScene>
#include "diagramitem.h"

class TestDiagramitem : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();   // 可选：测试前初始化
    void cleanupTestCase(); // 可选：测试后清理

    void testConstructorAndType();
    void testBoundingRect();
    void testCustomType();
    void testSetBrush();
    void testSetFixedSize();
};

void TestDiagramitem::initTestCase()
{
    // 可在此创建全局资源（如 QApplication），但 Qt Test 通常不需要
}

void TestDiagramitem::cleanupTestCase()
{
    // 清理资源
}

void TestDiagramitem::testConstructorAndType()
{
    QMenu contextMenu;
    DiagramItem item(DiagramItem::Step, &contextMenu);

    QCOMPARE(item.diagramType(), DiagramItem::Step);
    QVERIFY(!item.boundingRect().isEmpty());
}

void TestDiagramitem::testBoundingRect()
{
    QMenu contextMenu;
    DiagramItem item(DiagramItem::Conditional, &contextMenu);

    QRectF rect = item.boundingRect();
    QVERIFY(rect.width() > 0);
    QVERIFY(rect.height() > 0);
}

void TestDiagramitem::testCustomType()
{
    QMenu contextMenu;
    DiagramItem item(DiagramItem::StartEnd, &contextMenu);

    QCOMPARE(item.type(), QGraphicsItem::UserType + 15);
}

void TestDiagramitem::testSetBrush()
{
    QMenu contextMenu;
    DiagramItem item(DiagramItem::Io, &contextMenu);

    QColor red(Qt::red);
    item.setBrush(red);

    QCOMPARE(item.m_color, red);  // 检查成员变量是否更新
}

void TestDiagramitem::testSetFixedSize()
{
    QMenu contextMenu;
    DiagramItem item(DiagramItem::Document, &contextMenu);

    QSizeF newSize(200, 150);
    item.setFixedSize(newSize);

    // 注意：m_grapSize 是私有成员，无法直接访问
    // 所以我们通过 boundingRect 间接验证（或修改类暴露 getter）
    // 但你已提供 getSize()，所以可以直接用！

    QCOMPARE(item.getSize(), newSize);
}

// QTEST_MAIN(TestDiagramitem)
#include "tst_diagramitem.moc"
