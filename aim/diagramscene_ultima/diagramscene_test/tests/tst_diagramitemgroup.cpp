#include <QTest>
#include "diagramitemgroup.h"
#include <QGraphicsScene>

class TestDiagramItemGroup : public QObject // 更改类名使其更清晰
{
    Q_OBJECT

private slots:
    void initTestCase() {
        // 在整个测试案例开始之前运行一次
        scene = new QGraphicsScene(this);
    }

    void cleanupTestCase() {
        // 在整个测试案例结束之后运行一次
        delete scene;
    }

    void testConstructor() {
        DiagramItemGroup *group = new DiagramItemGroup();
        QVERIFY(group != nullptr); // 确认构造函数正确创建了对象
        delete group;
    }

    void testAddItem() {
        DiagramItemGroup *group = new DiagramItemGroup();
        QGraphicsRectItem *rectItem = new QGraphicsRectItem(0, 0, 100, 50);
        group->addItem(rectItem);
        QCOMPARE(group->childItems().size(), 1); // 确保项目被添加到组中
        delete group;
    }

    void testBoundingRect() {
        DiagramItemGroup *group = new DiagramItemGroup();
        QGraphicsRectItem *rectItem = new QGraphicsRectItem(0, 0, 100, 50);
        group->addItem(rectItem);
        QRectF rect = group->boundingRect();
        QCOMPARE(rect.width(), 100.0); // 根据添加的矩形项检查边界矩形的宽度
        QCOMPARE(rect.height(), 50.0); // 检查高度
        delete group;
    }

private:
    QGraphicsScene *scene; // 用于管理图形项的场景
};

// QTEST_MAIN(TestDiagramItemGroup)

#include "tst_diagramitemgroup.moc"
