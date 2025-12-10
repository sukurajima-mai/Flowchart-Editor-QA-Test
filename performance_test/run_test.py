import pyautogui
import time
import subprocess
import random

pyautogui.FAILSAFE = False  # 禁止自动停止，防止报错

# ----------------------------
# 1. 修改你的 exe 路径
# ----------------------------
exe_path = r"E:/Qt/6.10.1/mingw_64/output/diagramscene.exe"

# ----------------------------
# 2. 启动软件
# ----------------------------
print("启动软件中……")
subprocess.Popen(exe_path)
time.sleep(5)

# ----------------------------
# 3. 记录菜单中【形状按钮】坐标
# ----------------------------
print("请在 5 秒内把鼠标移动到【左侧菜单某个形状按钮】上...")
time.sleep(5)
shape_button_pos = pyautogui.position()
print("形状按钮坐标：", shape_button_pos)

# ----------------------------
# 4. 记录画布左上角坐标
# ----------------------------
print("请在 5 秒内把鼠标移动到【画布左上角】位置...")
time.sleep(5)
canvas_top_left = pyautogui.position()
print("画布左上角坐标：", canvas_top_left)

# ----------------------------
# 5. 记录画布右下角坐标
# ----------------------------
print("请在 5 秒内把鼠标移动到【画布右下角】位置...")
time.sleep(5)
canvas_bottom_right = pyautogui.position()
print("画布右下角坐标：", canvas_bottom_right)

# ----------------------------
# 6. 自动插入节点
# ----------------------------
insert_count = 50
print(f"开始自动插入 {insert_count} 个节点...")

start_time = time.time()

for i in range(insert_count):

    # (1) 点击形状菜单按钮
    pyautogui.click(shape_button_pos)
    time.sleep(0.02)

    # (2) 随机生成画布点击点
    x = random.randint(canvas_top_left.x, canvas_bottom_right.x)
    y = random.randint(canvas_top_left.y, canvas_bottom_right.y)

    # (3) 在画布点击，插入图形
    pyautogui.click(x, y)

    if i % 100 == 0:
        print(f"已插入 {i} 个...")

end_time = time.time()
print(f"插入 {insert_count} 个节点耗时：{end_time - start_time:.2f} 秒")
print("测试完成！")
