import pyautogui
import time

pyautogui.FAILSAFE = True

move_count = 50   # 产生 50 个 undo 记录
undo_count = 50   # Undo 50 次
redo_count = 50   # Redo 50 次

# --------------------------------------------------
# 准备
# --------------------------------------------------
pyautogui.alert(
    "Undo/Redo 性能测试开始。\n\n"
    "请打开流程图程序，并确保画布中已有大量节点（如 1000 个）。\n"
    "在画布中心放置并选中一个节点，然后点击【OK】继续。"
)

# --------------------------------------------------
# 记录节点中心位置（用于移动）
# --------------------------------------------------
pyautogui.alert(
    "步骤 1：\n\n请将鼠标移动到【某个可拖拽节点的中心位置】（不要点击），\n然后点击【OK】。"
)
node_pos = pyautogui.position()
pyautogui.alert(f"已记录节点位置：{node_pos}\n\n点击【OK】继续运行测试。")

# --------------------------------------------------
# Step 1: 自动移动节点，生成 undo 记录
# --------------------------------------------------
start_time = time.time()

for i in range(move_count):
    pyautogui.moveTo(node_pos.x, node_pos.y)
    pyautogui.dragRel(20, 0, duration=0.1)  # 向右移动
    pyautogui.dragRel(-20, 0, duration=0.1) # 拖回原位
    time.sleep(0.02)

move_end = time.time()
move_time = move_end - start_time

print(f"[Move] 产生 {move_count} 个可撤销动作耗时：{move_time:.2f} 秒")

# --------------------------------------------------
# Step 2: 执行 Undo
# --------------------------------------------------
undo_start = time.time()

for i in range(undo_count):
    pyautogui.hotkey('ctrl', 'z')
    time.sleep(0.02)

undo_end = time.time()
undo_time = undo_end - undo_start

print(f"[Undo] Undo {undo_count} 次耗时：{undo_time:.2f} 秒")

# --------------------------------------------------
# Step 3: 执行 Redo
# --------------------------------------------------
redo_start = time.time()

for i in range(redo_count):
    pyautogui.hotkey('ctrl', 'y')
    time.sleep(0.02)

redo_end = time.time()
redo_time = redo_end - redo_start

print(f"[Redo] Redo {redo_count} 次耗时：{redo_time:.2f} 秒")

pyautogui.alert(
    f"Undo/Redo 测试完成！\n\n"
    f"生成 {move_count} 次移动耗时：{move_time:.2f} 秒\n"
    f"Undo {undo_count} 次耗时：{undo_time:.2f} 秒\n"
    f"Redo {redo_count} 次耗时：{redo_time:.2f} 秒\n\n"
    "请将控制台输出内容复制给性能报告生成器。"
)
