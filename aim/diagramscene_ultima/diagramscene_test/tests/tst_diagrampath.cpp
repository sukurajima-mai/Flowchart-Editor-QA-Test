#include <QTest>
#include <QApplication>
#include <QGraphicsScene>
#include <QMenu>
#include "diagrampath.h"
#include "diagramitem.h"

class TestDiagramPath : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase() {
        // QTEST_MAIN 保证 QApplication 存在
        scene = new QGraphicsScene();
    }

    void cleanupTestCase() {
        delete scene;
    }

    void testDiagramPathConstructionAndUpdate() {
        // 创建空上下文菜单（DiagramItem 构造必需）
        QMenu *menu = new QMenu();

        // 创建两个 DiagramItem
        DiagramItem *startItem = new DiagramItem(DiagramItem::Step, menu);
        DiagramItem *endItem = new DiagramItem(DiagramItem::Conditional, menu);

        // 必须加入 scene，否则 mapToScene 崩溃！
        scene->addItem(startItem);
        scene->addItem(endItem);

        // 设置位置避免重叠
        startItem->setPos(0, 0);
        endItem->setPos(200, 100);

        // 使用 linkWhere() 中实际存在的 key（根据 DiagramItem::rectWhere/linkWhere 实现）
        // 根据你提供的 DiagramItemGroup 代码，TransformState 如 TF_Right 是合法的
        auto startState = DiagramItem::TF_Right;
        auto endState = DiagramItem::TF_Left;

        // 验证 linkWhere 包含这些状态（避免越界）
        QVERIFY(startItem->linkWhere().contains(startState));
        QVERIFY(endItem->linkWhere().contains(endState));

        // 构造 DiagramPath —— 应不崩溃
        DiagramPath path(startItem, endItem, startState, endState);

        // 验证基本属性
        QCOMPARE(path.getStartItem(), startItem);
        QCOMPARE(path.getEndItem(), endItem);

        // 调用 updatePath —— 应成功生成路径
        path.updatePath();

        // 路径不应为空
        QVERIFY(!path.path().isEmpty());

        // 清理
        scene->removeItem(startItem);
        scene->removeItem(endItem);
        delete startItem;
        delete endItem;
        delete menu;
    }

    void testDifferentTransformStates() {
        QMenu *menu = new QMenu();
        DiagramItem *item1 = new DiagramItem(DiagramItem::StartEnd, menu);
        DiagramItem *item2 = new DiagramItem(DiagramItem::Io, menu);

        scene->addItem(item1);
        scene->addItem(item2);

        item1->setPos(50, 50);
        item2->setPos(300, 200);

        // 测试多种组合
        QList<QPair<DiagramItem::TransformState, DiagramItem::TransformState>> states = {
            {DiagramItem::TF_Top, DiagramItem::TF_Bottom},
            {DiagramItem::TF_Left, DiagramItem::TF_Right},
            {DiagramItem::TF_TopL, DiagramItem::TF_BottomR},
            {DiagramItem::TF_BottomL, DiagramItem::TF_TopR}
        };

        for (const auto &pair : states) {
            if (!item1->linkWhere().contains(pair.first)) continue;
            if (!item2->linkWhere().contains(pair.second)) continue;

            DiagramPath path(item1, item2, pair.first, pair.second);
            path.updatePath();
            QVERIFY(!path.path().isEmpty());
        }

        scene->removeItem(item1);
        scene->removeItem(item2);
        delete item1;
        delete item2;
        delete menu;
    }

private:
    QGraphicsScene *scene = nullptr;

};


// QTEST_MAIN(TestDiagramPath)
#include "tst_diagrampath.moc"
