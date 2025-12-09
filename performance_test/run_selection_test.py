import pyautogui
import time

pyautogui.FAILSAFE = True

selection_count = 10  # 框选次数

# --------------------------------------------------
# 引导用户准备
# --------------------------------------------------
pyautogui.alert(
    "框选性能测试开始。\n\n"
    "请手动打开流程图程序，保持画布上已有大量节点（例如 1000 个）。\n"
    "程序窗口置于前台后点击【OK】继续。"
)

# --------------------------------------------------
# 获取框选起点（画布内左上区域）
# --------------------------------------------------
pyautogui.alert(
    "步骤 1：\n\n"
    "请将鼠标移动到【你希望开始框选的左上角位置】（画布内），\n"
    "然后点击本对话框的【OK】。"
)
start_pos = pyautogui.position()
pyautogui.alert(f"已记录框选左上角：{start_pos}\n\n点击【OK】继续。")

# --------------------------------------------------
# 获取框选终点（画布内右下区域）
# --------------------------------------------------
pyautogui.alert(
    "步骤 2：\n\n"
    "请将鼠标移动到【你希望框选到的右下角位置】（画布内，确保框到大量节点），\n"
    "然后点击本对话框的【OK】。"
)
end_pos = pyautogui.position()
pyautogui.alert(
    f"已记录框选右下角：{end_pos}\n\n"
    "接下来将自动执行多次框选操作，请勿操作鼠标键盘。\n\n"
    "如需紧急停止，请将鼠标移动到屏幕任意角落。"
)

# --------------------------------------------------
# 执行多次框选
# --------------------------------------------------
start_time = time.time()

for i in range(selection_count):
    # 移动到起点
    pyautogui.moveTo(start_pos.x, start_pos.y)
    pyautogui.mouseDown()
    time.sleep(0.05)

    # 拖到终点
    pyautogui.moveTo(end_pos.x, end_pos.y, duration=0.2)
    time.sleep(0.05)

    # 松开鼠标，完成框选
    pyautogui.mouseUp()
    time.sleep(0.1)

    if i % 2 == 0:
        print(f"已完成 {i} 次框选...")

end_time = time.time()
total_time = end_time - start_time

pyautogui.alert(
    f"框选测试完成！\n\n"
    f"共执行 {selection_count} 次完整框选，总耗时 {total_time:.2f} 秒。\n\n"
    "请将控制台输出复制给测试报告生成器。"
)

print(f"[框选性能结果] 框选 {selection_count} 次，总耗时：{total_time:.2f} 秒")
