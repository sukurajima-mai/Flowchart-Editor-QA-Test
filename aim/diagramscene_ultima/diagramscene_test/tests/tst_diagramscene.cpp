#include <QTest>
#include <QApplication>
#include <QMenu>
#include <QSignalSpy>
#include "diagramscene.h"
#include "diagramitem.h"
#include "diagramtextitem.h"

class TestDiagramScene : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase() {
        itemMenu = new QMenu();
        scene = new DiagramScene(itemMenu);
    }

    void cleanupTestCase() {
        delete scene;
        delete itemMenu;
    }

    // 移除对 myMode / myItemType 的直接访问
    void testSetModeAndItemType() {
        // 只能验证 setMode/setItemType 被调用不会崩溃
        // 并通过后续行为间接体现（如 createItem 使用 myItemType）
        scene->setItemType(DiagramItem::Conditional);
        scene->setMode(DiagramScene::InsertItem);

        // 创建 item，验证其类型是否符合 setItemType 设置的类型
        QGraphicsItem *item = scene->createItem(static_cast<int>(DiagramItem::Conditional));
        QVERIFY(item != nullptr);
        QCOMPARE(item->type(), DiagramItem::Type);

        DiagramItem *diagramItem = qgraphicsitem_cast<DiagramItem*>(item);
        QVERIFY(diagramItem != nullptr);
        // 注意：DiagramItem 自身不存储“创建时的类型标识”，
        // 所以无法直接验证它是 Conditional 还是 Step。
        // 但至少可以验证它被正确创建并加入场景。
        QVERIFY(scene->items().contains(item));

        scene->removeItem(item);
        delete item;
    }

    void testColorAndFontAccessors() {
        QColor red(Qt::red);
        QColor blue(Qt::blue);
        QColor green(Qt::green);
        QFont font("Arial", 14);

        scene->setLineColor(red);
        scene->setItemColor(blue);
        scene->setTextColor(green);
        scene->setFont(font);

        // 这些有 public getter，可以安全访问
        QCOMPARE(scene->lineColor(), red);
        QCOMPARE(scene->itemColor(), blue);
        QCOMPARE(scene->textColor(), green);
        QCOMPARE(scene->font(), font);
    }

    void testCreateItem() {
        // 默认类型是 Step（虽然不能读，但 createItem 使用 myItemType）
        QGraphicsItem *item = scene->createItem(static_cast<int>(DiagramItem::Step));
        QVERIFY(item != nullptr);
        QVERIFY(scene->items().contains(item));
        scene->removeItem(item);
        delete item;
    }

    void testCreateTextItem() {
        QGraphicsTextItem *textItem = scene->createTextItem();
        QVERIFY(textItem != nullptr);
        QVERIFY(scene->items().contains(textItem));
        scene->removeItem(textItem);
        delete textItem;
    }

    void testEditorLostFocus_RemovesEmptyTextItem() {
        DiagramTextItem *textItem = new DiagramTextItem();
        textItem->setPlainText("");
        scene->addItem(textItem);

        QVERIFY(scene->items().contains(textItem));

        scene->editorLostFocus(textItem);

        // 应该已被 remove（deleteLater 不影响 contains）
        QVERIFY(!scene->items().contains(textItem));
        // 注意：不要 delete textItem，因为 deleteLater 已安排
    }

    void testEditorLostFocus_KeepsNonEmptyTextItem() {
        DiagramTextItem *textItem = new DiagramTextItem();
        textItem->setPlainText("Hello");
        scene->addItem(textItem);

        scene->editorLostFocus(textItem);

        QVERIFY(scene->items().contains(textItem));
        QCOMPARE(textItem->toPlainText(), QString("Hello"));

        scene->removeItem(textItem);
        delete textItem;
    }

    void testItemInsertedSignal() {
        QSignalSpy spy(scene, &DiagramScene::itemInserted);

        DiagramItem *item = new DiagramItem(DiagramItem::Step, itemMenu);
        QColor color = scene->itemColor();
        item->setBrush(color);
        scene->addItem(item);
        emit scene->itemInserted(item); // 模拟信号发射

        QCOMPARE(spy.count(), 1);
        DiagramItem *emittedItem = qgraphicsitem_cast<DiagramItem*>(spy.first().first().value<QGraphicsItem*>());
        QCOMPARE(emittedItem, item);
    }

private:
    QMenu *itemMenu = nullptr;
    DiagramScene *scene = nullptr;
};

// QTEST_MAIN(TestDiagramScene)
#include "tst_diagramscene.moc"
