import pyautogui
import time

pyautogui.FAILSAFE = True

drag_count = 20  # 先拖拽 20 次，确认动作无误后可改大数字

# --------------------------------------------------
# 引导用户准备
# --------------------------------------------------
pyautogui.alert(
    "拖拽性能测试开始。\n\n"
    "请手动打开你的流程图软件，并将一个节点放到画布中央附近。\n\n"
    "然后点击 OK 继续。"
)

# --------------------------------------------------
# 获取“可拖拽节点”的位置
# --------------------------------------------------
pyautogui.alert(
    "步骤 1：\n\n"
    "请把鼠标移动到【你想拖拽的节点中心位置】（不要点击），\n"
    "然后点击 OK。"
)
drag_start = pyautogui.position()
pyautogui.alert(f"记录到拖拽起点：{drag_start}\n\n点击 OK 继续。")

# --------------------------------------------------
# 开始拖拽测试
# --------------------------------------------------
start_time = time.time()

for i in range(drag_count):
    # 向右拖
    pyautogui.moveTo(drag_start.x, drag_start.y)
    pyautogui.dragRel(120, 0, duration=0.2)  # 右
    time.sleep(0.05)

    # 向左拖回
    pyautogui.dragRel(-120, 0, duration=0.2)  # 左
    time.sleep(0.05)

    if i % 5 == 0:
        print(f"已完成 {i} 次拖拽...")

end_time = time.time()

total_time = end_time - start_time

pyautogui.alert(
    f"拖拽测试完成！\n"
    f"总共执行 {drag_count} 次往返拖动。\n"
    f"耗时 {total_time:.2f} 秒。\n\n"
    "请将控制台中的结果提供给测试文档生成器。"
)

print(f"[拖拽性能结果] 拖拽 {drag_count} 次耗时：{total_time:.2f} 秒")
