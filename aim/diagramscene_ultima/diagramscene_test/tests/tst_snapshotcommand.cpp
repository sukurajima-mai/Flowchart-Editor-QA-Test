#include <QTest>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QPainter>
#include "snapshotcommand.h"

class snapshotcommand : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase() {
        // 创建一个简单的 pixmap（10x10 红色方块）
        m_pixmap = QPixmap(10, 10);
        m_pixmap.fill(Qt::red);

        // 创建 scene 和 view
        m_scene = new QGraphicsScene();
        m_view = new QGraphicsView(m_scene);
    }

    void cleanupTestCase() {
        delete m_view;   // 会自动删除 scene
    }

    void testConstruction() {
        SnapshotCommand cmd(m_view, m_pixmap);
        // 无法直接访问私有成员，但可通过 redo/undo 行为验证
        QVERIFY(true); // 构造不崩溃即通过
    }

    void testUndoRedoClearsSceneAndAddsSnapshot() {
        // 先往场景中添加一个 item（模拟用户操作）
        QGraphicsRectItem *originalItem = m_scene->addRect(0, 0, 50, 50);
        QCOMPARE(m_scene->items().size(), 1);

        // 创建命令（此时快照是红色 pixmap）
        SnapshotCommand cmd(m_view, m_pixmap);

        // 执行 undo（实际是恢复快照）
        cmd.undo();

        // 验证：
        // 1. 场景中应只剩一个 item（即 pixmap item）
        QCOMPARE(m_scene->items().size(), 1);

        // 2. 该项应是 QGraphicsPixmapItem
        QGraphicsItem *item = m_scene->items().first();
        QVERIFY(item->type() == QGraphicsPixmapItem::Type);

        QGraphicsPixmapItem *pixmapItem = static_cast<QGraphicsPixmapItem*>(item);
        QCOMPARE(pixmapItem->pixmap().size(), m_pixmap.size());
        // 注意：不能直接比较 pixmap 内容（除非用像素遍历），但尺寸一致可作为基本验证

        // 再执行 redo，行为应相同
        cmd.redo();
        QCOMPARE(m_scene->items().size(), 1);
        item = m_scene->items().first();
        QVERIFY(item->type() == QGraphicsPixmapItem::Type);
    }

    void testMultipleUndoRedoConsistency() {
        m_scene->addRect(0, 0, 100, 100);
        SnapshotCommand cmd(m_view, m_pixmap);

        cmd.undo();
        QCOMPARE(m_scene->items().size(), 1);

        cmd.redo();
        QCOMPARE(m_scene->items().size(), 1);

        cmd.undo();
        QCOMPARE(m_scene->items().size(), 1);
    }

private:
    QPixmap m_pixmap;
    QGraphicsScene *m_scene = nullptr;
    QGraphicsView *m_view = nullptr;
};

QTEST_MAIN(snapshotcommand)
#include "tst_snapshotcommand.moc"
