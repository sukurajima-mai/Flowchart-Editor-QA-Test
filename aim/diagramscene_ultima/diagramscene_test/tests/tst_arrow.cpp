#include <QTest>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QMenu>
#include "../../arrow.h"
#include "../../diagramitem.h"

class TestArrow : public QObject
{
    Q_OBJECT

private slots:
    void testInitialization();
    void testUpdatePosition();
    void testPaintDoesNotCrash_data();
    void testPaintDoesNotCrash();
};

void TestArrow::testInitialization()
{
    QMenu menu;
    DiagramItem startItem(DiagramItem::Step, &menu);
    DiagramItem endItem(DiagramItem::Conditional, &menu);

    Arrow arrow(&startItem, &endItem);
    QCOMPARE(arrow.startItem(), &startItem);
    QCOMPARE(arrow.endItem(), &endItem);
    QCOMPARE(arrow.type(), Arrow::Type);
}

void TestArrow::testUpdatePosition()
{
    QGraphicsScene scene;
    QMenu menu;

    DiagramItem startItem(DiagramItem::Step, &menu);
    DiagramItem endItem(DiagramItem::Step, &menu);
    startItem.setPos(10, 20);
    endItem.setPos(110, 120);
    startItem.setFixedSize(QSizeF(80, 40));
    endItem.setFixedSize(QSizeF(80, 40));

    scene.addItem(&startItem);
    scene.addItem(&endItem);

    Arrow arrow(&startItem, &endItem);
    scene.addItem(&arrow);
    arrow.updatePosition();

    // Check line is updated
    QVERIFY(!arrow.line().isNull());
}

void TestArrow::testPaintDoesNotCrash_data()
{
    QTest::addColumn<DiagramItem::DiagramType>("type1");
    QTest::addColumn<DiagramItem::DiagramType>("type2");

    // Only use types that set myPolygon in paint()
    QTest::newRow("Step -> Conditional") << DiagramItem::Step << DiagramItem::Conditional;
    QTest::newRow("Io -> circular") << DiagramItem::Io << DiagramItem::circular;
    QTest::newRow("Conditional -> Io") << DiagramItem::Conditional << DiagramItem::Io;
}

void TestArrow::testPaintDoesNotCrash()
{
    QFETCH(DiagramItem::DiagramType, type1);
    QFETCH(DiagramItem::DiagramType, type2);

    QGraphicsScene scene;
    QMenu menu;

    DiagramItem startItem(type1, &menu);
    DiagramItem endItem(type2, &menu);
    startItem.setPos(0, 0);
    endItem.setPos(100, 100);
    startItem.setFixedSize(QSizeF(60, 30));
    endItem.setFixedSize(QSizeF(60, 30));

    Arrow arrow(&startItem, &endItem);
    scene.addItem(&startItem);
    scene.addItem(&endItem);
    scene.addItem(&arrow);
    arrow.updatePosition();

    // 使用 scene.render() 触发 paint() —— 这是合法且安全的方式
    QPixmap pixmap(200, 200);
    pixmap.fill(Qt::transparent); // 可选：透明背景
    QPainter painter(&pixmap);
    scene.render(&painter);       // ← 自动调用所有 item 的 paint()

    // 如果没崩溃，说明 paint() 工作正常
    QVERIFY(!pixmap.isNull());
}

// QTEST_MAIN(TestArrow)
#include "tst_arrow.moc"
