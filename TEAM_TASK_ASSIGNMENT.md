# 团队任务分配（QA&测试课程项目）

## 项目背景
FreeCharts 流程图编辑器的完整软件测试实践。目标：从设计规划阶段已有的分析基础出发，补齐**实际运行/执行的测试证据**，满足课程"功能度、易用性、文档、静态、动态"五个测试维度的要求。

---

## ⚡ 关键说明：任务可以并行执行

**之前我标注 P0（优先级 0）的意思是"重要"，但不代表 T3/T4 必须等 T1/T2 完成。**

实际情况：
- **T1（编译）**→ **T2（运行日志）** 有依赖关系（必须线性）
- **T3（功能测试）** 和 **T4（易用性调查）** 可以**立即开始**，无需等 T1/T2
- **T5（性能测试）** 也可并行执行

**建议执行策略**：
```
Day 1:
  ├─ 组员 A 开始 T1（修复编译） [预计 4h]
  ├─ 组员 B 同时开始 T3（功能测试） [预计 6h，可分成多个 1h 时段]
  └─ 组员 C 同时开始 T4（邀请用户反馈） [预计 4h，主要是等待反馈回复]

Day 2:
  ├─ 组员 A 完成 T1 后，立即开始 T2（运行测试） [预计 2h]
  ├─ 组员 B/C 继续完成各自任务
  └─ 汇总所有结果，生成最终报告
```

总墙钟时间：1-2 天（而非 4+6+4=14 天的串联）。

---

## 任务总表

| 任务 ID | 任务名称 | 优先级 | 工作量 | 负责人 | 依赖关系 | 输出物 |
|--------|--------|--------|-------|--------|--------|--------|
| T1 | 修复单元测试编译 | P0 | 4h | **组员 A** | 无 | compile.log + 可执行文件 |
| T2 | 运行单元测试并收集日志 | P0 | 2h | **组员 A** | 依赖 T1 | test_run.txt + 分析 |
| T3 | 手动执行功能测试（20 用例） | P1 | 6h | **组员 B** | 无（可与 T1 并行） | 截屏 5+ 张 + 用例运行表 |
| T4 | 易用性测试调查 | P1 | 4h | **组员 C** | 无（可与 T1 并行） | 用户反馈表 + 汇总分析 |
| T5 | 压力/性能测试 | P2 | 3h | 可选 | 无（可与 T1-T4 并行） | 性能指标 + 日志 |

---

## 详细任务说明

### Task T1：修复单元测试编译
**负责人**：组员 A  
**优先级**：P0（阻塞其他工作）  
**预计工作量**：4 小时  

**背景**
- 位置：`aim/diagramscene_ultima/tests/test_diagramscene_real.cpp`
- 编译命令已提供（见 `build_and_run.ps1`）
- 当前状态：编译失败（头文件依赖或链接问题）

**具体步骤**
1. 在 PowerShell 中运行编译命令（见下方），收集错误信息
2. 根据编译错误排查：
   - 是否缺少头文件？→ 检查 Qt include 路径，添加缺失 .h
   - 是否链接符号未定义？→ 检查是否缺少源文件编译或 .pro/.cmake 配置
   - 是否 moc 文件未生成？→ 如果用 Q_OBJECT，需要运行 moc 预处理
3. 修改测试代码或编译命令直到成功生成 `.exe`
4. 记录最终可行的编译命令

**编译命令（在 tests 目录执行）**
```powershell
$QtPath = 'D:/Software/Qt6.10/6.10.1/mingw_64'
$GppPath = 'D:\msys2\mingw64\bin\g++.exe'
& $GppPath -O2 -std=gnu++17 `
  -I$QtPath/include -I$QtPath/include/QtCore -I$QtPath/include/QtGui -I$QtPath/include/QtWidgets `
  -L$QtPath/lib `
  -I. -I.. `
  test_diagramscene_real.cpp ..\diagramscene.cpp ..\diagramitem.cpp ..\diagramtextitem.cpp `
  ..\diagramitemgroup.cpp ..\arrow.cpp ..\diagrampath.cpp ..\deletecommand.cpp `
  ..\snapshotcommand.cpp ..\mainwindow.cpp ..\mygraphicsview.cpp ..\findreplacedialog.cpp `
  -lQt6Core -lQt6Gui -lQt6Widgets -o test_diagramscene_real.exe 2>&1
```

**完成标志**
- [ ] test_diagramscene_real.exe 成功生成
- [ ] 没有链接错误或编译错误
- [ ] 把最终可行的编译命令记录在 `COMPILATION_NOTES.md`

**输出物**
- `test_diagramscene_real.exe`（可执行文件）
- `COMPILATION_NOTES.md`（记录解决的问题与最终命令）

---

### Task T2：运行单元测试并收集日志
**负责人**：组员 A（T1 完成后接手）  
**优先级**：P0  
**预计工作量**：2 小时  

**背景**
- T1 完成后，执行编译生成的测试程序
- 收集运行日志并分析测试结果

**具体步骤**
1. 在 PowerShell 中运行：
   ```powershell
   cd 'D:\work\homework\programming\codes\SoftwareQA&testing\aim\diagramscene_ultima\tests'
   .\test_diagramscene_real.exe 2>&1 | Tee-Object -FilePath '..\\test_run_log.txt'
   ```
2. 检查 exit code：
   - `0` = 所有断言通过
   - 非 0 = 某些测试失败，查看输出定位问题
3. 解析输出，统计"PASS / FAIL"数量
4. 如有失败，记录失败的具体测试点和错误信息
5. 把日志保存为 `TEST_DIAGRAMSCENE_REAL_RUN.log`，并在 `UNIT_TEST_RESULTS.md` 中汇总

**完成标志**
- [ ] 测试程序成功运行（无崩溃）
- [ ] 运行日志已收集（exit code 已记录）
- [ ] 测试结果已分析（通过率、失败点）

**输出物**
- `test_run_log.txt`（原始运行输出）
- `UNIT_TEST_RESULTS.md`（分析报告，包含通过/失败统计和说明）

---

### Task T3：手动执行功能测试（20 用例）
**负责人**：组员 B  
**优先级**：P1  
**预计工作量**：6 小时（约 ~18 分钟/用例，部分并行）  

**背景**
- 用例清单已准备好（见 `TEST_REPORT_FUNCTIONAL.md` 的 20 个功能点）
- 需要在实际 GUI 上逐一执行，并截屏/记录结果
- 目标：补齐"实际 GUI 交互"的证据

**具体步骤**
1. 启动 FreeCharts 应用程序（需要能看到 GUI；若看不到，先联系组员 A 排查 Qt 运行环境）
2. 对照 `TEST_REPORT_FUNCTIONAL.md` 的用例表，逐一执行：
   - **示例用例 1**："启动与主界面" → 运行程序 → 截屏主窗口 → 记录 ✓
   - **示例用例 2**："新建流程图" → 点击 File > New → 截屏空白场景 → 记录 ✓
   - **示例用例 3**："插入图形" → 选择矩形工具 → 点击场景 → 截屏 → 记录 ✓
   - ...以此类推 20 个用例
3. 对每个用例：
   - 记录是否"通过"、"失败"或"部分通过"
   - 如有异常（崩溃、错误对话框），截屏并记录
   - 把关键截屏保存为 `TC_00X_<用例名>_<时间戳>.png`
4. 把所有结果汇总到 `FUNCTIONAL_TEST_EXECUTION.md`（表格形式）

**用例清单（摘自 TEST_REPORT_FUNCTIONAL.md）**
| # | 功能 | 测试操作 | 预期 | 实际 |
| - | ---- | ------- | ---- | ---- |
| 1 | 启动与主界面 | 运行程序 | 窗口显示 | ✓/✗ |
| 2 | 新建流程图 | File → New | 空白场景 | ✓/✗ |
| 3 | 插入图形（20 种） | 选工具 → 点击 | 图形出现 | ✓/✗ |
| 4 | 图形移动 | 拖拽图形 | 位置变化 | ✓/✗ |
| ... | ... | ... | ... | ... |

**完成标志**
- [ ] 20 个用例均已测试
- [ ] 关键截屏至少 5 张（展示不同功能）
- [ ] 所有结果记录在 `FUNCTIONAL_TEST_EXECUTION.md`
- [ ] 若有失败，已描述失败原因

**输出物**
- `TC_001_<用例>.png`～`TC_020_<用例>.png`（关键截屏，至少 5 张）
- `FUNCTIONAL_TEST_EXECUTION.md`（用例执行表 + 分析）

---

### Task T4：易用性测试调查
**负责人**：组员 C  
**优先级**：P1  
**预计工作量**：4 小时  

**背景**
- 易用性测试需要收集用户反馈，而非仅单人操作
- 目标：邀请 5+ 人（同学、朋友、师兄师姐等）实际使用程序并记录反馈

**具体步骤**
1. 准备用户调查问卷（问卷模板已生成，见下方）
2. 邀请 5+ 测试员，给他们一个简单的任务：
   - "请用这个程序画一个简单的流程图（3 个图形 + 2 条连线）"
   - "请尽量在不看文档的情况下完成"
3. 在他们操作时观察：
   - 是否能快速找到工具？
   - 是否对某些功能感到困惑？
   - 是否遇到意外行为？
   - UI 是否美观/专业？
4. 操作后，请他们填写问卷（5 分制或开放式反馈）
5. 统计结果并汇总为 `USABILITY_TEST_REPORT_UPDATED.md`

**用户问卷模板**
```
=== 易用性反馈问卷 ===
测试员编号: ___
使用时间: ___ 分钟
是否第一次使用: 是 / 否

1. 工具栏布局是否清晰？(1-5) ___
   反馈：___

2. 操作是否直观？(1-5) ___
   反馈：___

3. 图形绘制是否简便？(1-5) ___
   反馈：___

4. 颜色/样式选择是否容易找到？(1-5) ___
   反馈：___

5. 保存/加载功能是否清楚？(1-5) ___
   反馈：___

6. 总体满意度（1-5）: ___

7. 最喜欢的功能：___
8. 最需要改进的地方：___
9. 其他建议：___
```

**完成标志**
- [ ] 至少 5 个用户反馈已收集
- [ ] 问卷已填写并保存
- [ ] 数据已汇总（平均分、常见反馈）

**输出物**
- `USABILITY_SURVEY_RESPONSES.md`（原始反馈记录）
- `USABILITY_TEST_REPORT_UPDATED.md`（汇总分析）

---

### Task T5：压力/性能测试（可选，时间允许）
**负责人**：可选  
**优先级**：P2  
**预计工作量**：3 小时  

**背景**
- 验证程序在大量数据下的性能表现
- 可手动测试或编写自动化脚本

**具体步骤**
1. 编写或录制一个脚本，批量插入 1000+ 个图形
2. 记录：
   - 插入时间
   - 内存占用
   - 是否卡顿/崩溃
3. 测试保存/加载大文件的性能

**输出物**
- `PERFORMANCE_TEST_RESULTS.md`（性能指标和分析）

---

## 提交与汇总

### 最终交付物清单
- [ ] T1: `test_diagramscene_real.exe` + `COMPILATION_NOTES.md`
- [ ] T2: `test_run_log.txt` + `UNIT_TEST_RESULTS.md`
- [ ] T3: 截屏 5+ 张 + `FUNCTIONAL_TEST_EXECUTION.md`
- [ ] T4: `USABILITY_SURVEY_RESPONSES.md` + `USABILITY_TEST_REPORT_UPDATED.md`
- [ ] T5: `PERFORMANCE_TEST_RESULTS.md`（可选）

### 提交流程
1. 每个任务完成后，在对应 `.md` 文件中标注"完成日期"和"负责人"
2. 把所有输出物推送到 GitHub `main` 分支
3. 更新 `HONEST_TEST_STATUS.md` 中的状态表（从 🔴 改为 🟢）
4. 主要负责人（或 leader）审阅并在 `FINAL_TEST_SUMMARY.md` 中生成最终报告

---

## 时间表与 Milestone

### 并行执行策略
- **第 1 天**：T1, T3, T4 同时开始（互不阻塞）
- **第 1 天晚 / 第 2 天**：T2（T1 完成后开始）
- **第 2 天**：汇总 T1-T4 结果，可选执行 T5

### 关键节点
| 里程碑 | 目标完成日期 | 涉及任务 | 说明 |
|-------|-----------|---------|------|
| M1: T1 完成 | [日期] | T1 | 单元测试编译成功；解除 T2 阻塞 |
| M2: T2 完成 | [日期] | T2 | 单元测试运行结果反馈 |
| M3: T3 完成 | [日期] | T3 | 功能测试证据完整（可与 M1-M2 并行完成） |
| M4: T4 完成 | [日期] | T4 | 用户反馈收集完成（可与 M1-M2 并行完成） |
| M5: 最终报告 | [日期] | 所有 | 综合所有证据生成最终测试报告 |

---

## 联系与支持

- **技术问题**（编译、运行）：组员 A
- **功能测试**问题：组员 B
- **用户调查**问题：组员 C
- **总体协调**：项目 leader

---

## 附录：快速参考

### 启动应用
```powershell
cd 'D:\work\homework\programming\codes\SoftwareQA&testing\aim\diagramscene_ultima\build\Desktop_Qt_6_10_1_MinGW_64_bit-Debug\debug'
.\FreeCharts.exe
```

### 编译测试
```powershell
cd 'D:\work\homework\programming\codes\SoftwareQA&testing\aim\diagramscene_ultima\tests'
.\build_and_run.ps1
```

### 文档位置
- 项目分析：`PROJECT_ANALYSIS.md`
- 功能用例清单：`TEST_REPORT_FUNCTIONAL.md`（表中的 20 个用例）
- 代码位置：`aim/diagramscene_ultima/`

