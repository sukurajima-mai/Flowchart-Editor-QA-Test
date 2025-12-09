import pyautogui
import time

pyautogui.FAILSAFE = True

filename = "test_perf.flow"

# --------------------------------------------------
# 准备
# --------------------------------------------------
pyautogui.alert(
    "保存/加载 性能测试将开始。\n\n"
    "请打开流程图程序，确保画布中有大量节点（例如 1000 个）。\n"
    "然后点击【OK】继续。"
)

# --------------------------------------------------
# Step 1: 保存测试
# --------------------------------------------------
save_start = time.time()

pyautogui.hotkey('ctrl', 's')
time.sleep(1)

# 输入文件名
pyautogui.typewrite(filename, interval=0.02)
pyautogui.press('enter')

save_end = time.time()
save_time = save_end - save_start

print(f"[Save] 保存文件耗时：{save_time:.2f} 秒")

pyautogui.alert(f"保存完成，耗时 {save_time:.2f} 秒。\n接下来将进行加载测试。点击【OK】继续。")

# --------------------------------------------------
# Step 2: 加载测试
# --------------------------------------------------
load_start = time.time()

pyautogui.hotkey('ctrl', 'o')
time.sleep(1)

pyautogui.typewrite(filename, interval=0.02)
pyautogui.press('enter')

load_end = time.time()
load_time = load_end - load_start

print(f"[Load] 加载文件耗时：{load_time:.2f} 秒")

pyautogui.alert(
    f"保存/加载测试完成！\n\n"
    f"保存耗时：{save_time:.2f} 秒\n"
    f"加载耗时：{load_time:.2f} 秒\n\n"
    "请将控制台输出内容复制给性能报告生成器。"
)
