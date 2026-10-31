# 寄存器版 vs HAL版 GPIO初始化对照（2026-10-31 W1 D2）

## ① 开时钟
- 寄存器：RCC_AHB1ENR |= 1<<5，直接操作位
- HAL：__HAL_RCC_GPIOF_CLK_ENABLE()，宏封装，可读性好
- 本质一样，HAL读起来像英语句子

## ② 配模式
- 寄存器：GPIOF_MODER = 1<<(2*9)，裸赋值会清掉其他引脚的模式
- HAL：填结构体(Pin/Mode/Pull/Speed) + HAL_GPIO_Init()，内部先清后设不误伤其他引脚
- HAL还多配了上拉(GPIO_PULLUP)和速度(GPIO_SPEED_HIGH)，寄存器版没碰这两个寄存器

## ③ 引脚表示
- 寄存器：魔法数字 1<<(2*9)、1<<5，不查手册看不懂
- HAL：枚举宏 GPIO_PIN_9 / GPIO_MODE_OUTPUT_PP，名字本身就是说明

## 额外发现
HAL_GPIO_WritePin 内部就是写BSRR寄存器，和 while 循环里 GPIOF_BSRR=1<<(16+9) 是一回事。
