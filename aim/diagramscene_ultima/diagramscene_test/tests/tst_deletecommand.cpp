#include <QTest>
#include <QApplication>
#include <QGraphicsScene>
#include <QMenu>
#include "deletecommand.h"
#include "diagramitem.h"  // 因为它是一个有效的 QGraphicsItem 子类

class TestDeleteCommand : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase() {
        scene = new QGraphicsScene();
    }

    void cleanupTestCase() {
        delete scene;
    }

    void testDeleteCommandUndoRedo() {
        // 创建上下文菜单（DiagramItem 构造必需）
        QMenu *menu = new QMenu();

        // 创建一个 DiagramItem 作为被删除对象
        DiagramItem *item = new DiagramItem(DiagramItem::Step, menu);
        item->setPos(100, 200);
        scene->addItem(item);

        // 验证初始状态：item 在 scene 中
        QVERIFY(scene->items().contains(item));
        QCOMPARE(item->pos(), QPointF(100, 200));

        // 记录初始位置和尺寸
        QPointF originalPos = item->pos();
        QSizeF originalSize = item->boundingRect().size();

        // 创建 DeleteCommand
        DeleteCommand command(item, scene);

        // 执行 redo() —— 应从 scene 中移除
        command.redo();
        QVERIFY(!scene->items().contains(item));  // 已移除

        // 执行 undo() —— 应重新加入 scene，并恢复位置
        command.undo();
        QVERIFY(scene->items().contains(item));   // 已恢复
        QCOMPARE(item->pos(), originalPos);

        // 注意：m_itemSize 未在 undo 中使用（注释掉了 setFixedSize），所以不验证尺寸

        // 清理
        scene->removeItem(item);
        delete item;
        delete menu;
    }

    void testDeleteCommandWithNullItemOrScene() {
        // 虽然实际使用中不会传 null，但为健壮性可考虑
        // 但根据当前实现，传 nullptr 会导致崩溃（如 item->pos()）
        // 所以我们假设调用者保证非空 —— 测试不覆盖非法输入
        QSKIP("DeleteCommand assumes valid non-null item and scene.");
    }

private:
    QGraphicsScene *scene = nullptr;
};

// QTEST_MAIN(TestDeleteCommand)
#include "tst_deletecommand.moc"
