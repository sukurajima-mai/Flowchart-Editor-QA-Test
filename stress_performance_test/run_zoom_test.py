import pyautogui
import time

pyautogui.FAILSAFE = True

zoom_in_steps = 20   # 放大次数
zoom_out_steps = 20  # 缩小次数

# --------------------------------------------------
# 引导用户准备
# --------------------------------------------------
pyautogui.alert(
    "缩放性能测试开始。\n\n"
    "请手动打开流程图程序，确保画布上已经有较多节点（例如之前的 1000 个）。\n"
    "将程序窗口切到前台，准备好后点击【OK】。"
)

# --------------------------------------------------
# 获取缩放操作位置（一般为画布中心）
# --------------------------------------------------
pyautogui.alert(
    "步骤 1：\n\n"
    "请将鼠标移动到【画布中间位置】（程序中缩放对你来说最直观的区域），\n"
    "然后点击本对话框的【OK】。"
)
canvas_center = pyautogui.position()
pyautogui.alert(f"已记录缩放中心位置：{canvas_center}\n\n点击【OK】开始缩放测试。")

# --------------------------------------------------
# 执行缩放测试（滚轮模拟）
# --------------------------------------------------
start_time = time.time()

# 放大
for i in range(zoom_in_steps):
    pyautogui.moveTo(canvas_center.x, canvas_center.y)
    pyautogui.scroll(120)   # 正值一般为向上滚动 = 放大
    time.sleep(0.05)

# 缩小
for i in range(zoom_out_steps):
    pyautogui.moveTo(canvas_center.x, canvas_center.y)
    pyautogui.scroll(-120)  # 负值一般为向下滚动 = 缩小
    time.sleep(0.05)

end_time = time.time()
total_time = end_time - start_time

pyautogui.alert(
    f"缩放测试完成！\n\n"
    f"放大 {zoom_in_steps} 次 + 缩小 {zoom_out_steps} 次，总耗时 {total_time:.2f} 秒。\n\n"
    "请将控制台输出复制给测试报告生成器。"
)

print(f"[缩放性能结果] 放大 {zoom_in_steps} 次 + 缩小 {zoom_out_steps} 次，总耗时：{total_time:.2f} 秒")
