# project-f407-daq

普中战神F407 数据采集系统项目仓库（2028届嵌入式求职 · 阶段1起点）
配套：《嵌入式学习计划_2026-10修订版》｜ 主线：普中HAL库版教程

## W1 D1 首灯（2026-10-29）

![首灯](docs/led_first_blink.jpg)

- 代码：`User/main.c` 寄存器三件套 —— `RCC_AHB1ENR|=1<<5` 合GPIOF空开 → `GPIOF_MODER=1<<(2*9)` 给PF9发输出工作证 → `GPIOF_BSRR` 按钮式翻转（DS0红灯，低电平点亮）
- 编译：Keil5 MDK-Community + STM32F4xx_DFP 2.14.0，`0 Error(s), 0 Warning(s)`，Code=204
- 链路：ST-Link V2(WinUSB) SWD@1MHz + 板USB2侧口 CH340=COM3

### 踩坑日志（首灯四坑）
1. **白线插GND**：SWDIO进GND槽 → "Cannot enter Debug Mode"；核线必须逐色对丝印，"我以为"不算核对；
2. **Keil误选CMSIS-DAP**：Debug页右下拉=选司机，克隆ST-Link要选 ST-Link Debugger；
3. **SWD 4MHz失败**：杜邦长线信号完整性不够，降1MHz即稳（CubeProgrammer 950kHz旁证）；
4. **烧录后需复位**：Flash写完内核不会自动换节目；勾 Flash Download→Reset and Run 一劳永逸。另：烧录半途失败会留下"半擦Flash"假死态，现象=白屏+寄存器全0，对策=重烧。

### 接线档案
棕=ST-Link pin2(SWCLK)→J4 CLK(最右)；白=pin4(SWDIO)→J4 DIO(左2)；黑=pin5(GND)→J4 GND(左3)；J4 3V3空；板子自供电。

## TODO
- [ ] W2：按键消抖+EXTI + fp状态机微课
- [ ] 延时改SysTick；LED引脚宏化（PF9魔法数字清零）

## W1 周总结（2026-10-29 ~ 11-01）

### 三版对照

| 版本 | 代码位置 | 核心写法 | 代码量 |
|---|---|---|---|
| 寄存器版 | LED_HAL/User/main.c | RCC_AHB1ENR\|=1<<5 / GPIOF_MODER=1<<(2*9) / GPIOF_BSRR翻转 | 8行 |
| HAL例程版 | 普中资料led.c | __HAL_RCC_GPIOF_CLK_ENABLE() + GPIO_InitTypeDef结构体 + HAL_GPIO_Init() | ~10行 |
| CubeMX版 | LED_CubeMX/Core/Src/main.c | MX_GPIO_Init()自动生成 + HAL_GPIO_TogglePin() | while里2行 |

### 三版差异结论
1. **时钟**：寄存器裸写bit5 / HAL宏封装 / CubeMX自动生成SystemClock_Config——本质都是RCC_AHB1ENR bit5
2. **模式配置**：寄存器裸赋值MODER(会清其他引脚) / HAL填结构体+掩码先清后设(SET_FIELD) / CubeMX同HAL但全自动
3. **引脚表示**：魔法数字1<<(2*9) / 枚举宏GPIO_PIN_9+GPIO_MODE_OUTPUT_PP / CubeMX用User Label自动生成LED0_Pin宏

### 调试器课三条观察
1. F10单步：RCC_AHB1ENR 0x00100000→0x00100020(bit5亮)，GPIOF_MODER 0→0x00040000(PF9输出)——寄存器跳变亲眼可见
2. ODR bit9暂停间交替含/不含0x0200——BSRR翻转ODR驱动引脚电平
3. 注释RCC行→灯灭→取消→灯活——不开时钟=外设睡着=写寄存器白写

### 本周踩坑汇总（8条）
1. 白线插GND→SWDIO短路→Cannot enter Debug Mode
2. Keil误选CMSIS-DAP→No Debug Unit found
3. SWD 4MHz杜邦线信号不够→降1MHz
4. 烧录后需复位→勾Reset and Run
5. 半擦Flash假死→重烧
6. #definne拼写错→编译报错先查拼写
7. SET_FIELD先掩后移vs先移后掩→顺序反结果全错
8. CubeMX Clock Wizard自动切HSI→弹窗点Cancel手动填M=8/N=336/P=2

### 工具链定稿
Keil5 MDK-Community + DFP 2.14.0 + ST-Link V2(WinUSB, SWD@1MHz) + CubeProgrammer v2.22(D:\STM32CubeProgrammer) + CubeMX(本地FW V1.25.0+在线V1.28.0) + CH340=COM3
