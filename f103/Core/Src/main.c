/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* ===== 6x8 ASCII 字库 + 文字显示 ===== */
static const uint8_t font6x8[95][6] = {  {0x00,0x00,0x00,0x00,0x00,0x00},  /* SP */
  {0x00,0x00,0x2F,0x00,0x00,0x00},  /* ! */
  {0x00,0x03,0x00,0x03,0x00,0x00},  /* " */
  {0x0A,0x3A,0x3F,0x0F,0x0A,0x00},  /* # */
  {0x00,0x26,0x75,0x2F,0x39,0x00},  /* $ */
  {0x27,0x15,0x3F,0x2A,0x39,0x00},  /* % */
  {0x3F,0x2D,0x33,0x28,0x00,0x00},  /* & */
  {0x00,0x00,0x03,0x00,0x00,0x00},  /* ' */
  {0x00,0x3E,0x41,0x80,0x00,0x00},  /* ( */
  {0x00,0x80,0x41,0x3E,0x00,0x00},  /* ) */
  {0x00,0x06,0x0F,0x06,0x00,0x00},  /* * */
  {0x08,0x08,0x3E,0x08,0x08,0x00},  /* + */
  {0x00,0x80,0x60,0x00,0x00,0x00},  /* , */
  {0x00,0x08,0x08,0x08,0x00,0x00},  /* - */
  {0x00,0x00,0x20,0x00,0x00,0x00},  /* . */
  {0x00,0x40,0x38,0x06,0x01,0x00},  /* / */
  {0x1E,0x29,0x25,0x1E,0x00,0x00},  /* 0 */
  {0x00,0x22,0x3F,0x20,0x00,0x00},  /* 1 */
  {0x00,0x22,0x31,0x29,0x27,0x00},  /* 2 */
  {0x00,0x21,0x25,0x25,0x1B,0x00},  /* 3 */
  {0x18,0x14,0x13,0x3F,0x10,0x00},  /* 4 */
  {0x00,0x27,0x25,0x25,0x19,0x00},  /* 5 */
  {0x00,0x1E,0x27,0x25,0x1D,0x00},  /* 6 */
  {0x00,0x01,0x31,0x0D,0x03,0x00},  /* 7 */
  {0x00,0x3B,0x25,0x25,0x1B,0x00},  /* 8 */
  {0x2E,0x29,0x29,0x1E,0x00,0x00},  /* 9 */
  {0x00,0x00,0x24,0x00,0x00,0x00},  /* : */
  {0x00,0x80,0x64,0x00,0x00,0x00},  /* ; */
  {0x00,0x08,0x14,0x22,0x00,0x00},  /* < */
  {0x00,0x14,0x14,0x14,0x14,0x00},  /* = */
  {0x00,0x22,0x14,0x08,0x00,0x00},  /* > */
  {0x00,0x29,0x09,0x0E,0x00,0x00},  /* ? */
  {0x7C,0x82,0xBD,0x9D,0x3E,0x00},  /* @ */
  {0x00,0x3E,0x11,0x3E,0x00,0x00},  /* A */
  {0x00,0x3F,0x25,0x25,0x1B,0x00},  /* B */
  {0x1E,0x21,0x21,0x21,0x00,0x00},  /* C */
  {0x3F,0x21,0x21,0x1E,0x00,0x00},  /* D */
  {0x00,0x3F,0x25,0x25,0x00,0x00},  /* E */
  {0x00,0x3F,0x05,0x05,0x00,0x00},  /* F */
  {0x1E,0x21,0x25,0x3D,0x00,0x00},  /* G */
  {0x3F,0x04,0x04,0x3F,0x00,0x00},  /* H */
  {0x00,0x21,0x3F,0x21,0x00,0x00},  /* I */
  {0x00,0x21,0x21,0x3F,0x00,0x00},  /* J */
  {0x00,0x3F,0x0C,0x12,0x21,0x00},  /* K */
  {0x00,0x3F,0x20,0x20,0x00,0x00},  /* L */
  {0x06,0x08,0x06,0x3F,0x00,0x00},  /* M */
  {0x00,0x3F,0x0C,0x3F,0x00,0x00},  /* N */
  {0x1E,0x21,0x21,0x21,0x1E,0x00},  /* O */
  {0x00,0x3F,0x09,0x09,0x06,0x00},  /* P */
  {0x1E,0x21,0x61,0xA1,0x9E,0x00},  /* Q */
  {0x00,0x3F,0x09,0x09,0x36,0x00},  /* R */
  {0x00,0x26,0x25,0x29,0x19,0x00},  /* S */
  {0x01,0x01,0x3F,0x01,0x01,0x00},  /* T */
  {0x1F,0x20,0x20,0x1F,0x00,0x00},  /* U */
  {0x00,0x1F,0x20,0x1F,0x00,0x00},  /* V */
  {0x00,0x3F,0x04,0x3F,0x00,0x00},  /* W */
  {0x21,0x12,0x0C,0x12,0x21,0x00},  /* X */
  {0x01,0x06,0x38,0x06,0x01,0x00},  /* Y */
  {0x21,0x39,0x27,0x21,0x00,0x00},  /* Z */
  {0x00,0xFF,0x81,0x00,0x00,0x00},  /* [ */
  {0x00,0x01,0x0E,0x30,0x40,0x00},  /* \ */
  {0x00,0x00,0x81,0xFF,0x00,0x00},  /* ] */
  {0x00,0x06,0x01,0x06,0x00,0x00},  /* ^ */
  {0x80,0x80,0x80,0x80,0x80,0x00},  /* _ */
  {0x00,0x00,0x01,0x00,0x00,0x00},  /* ` */
  {0x00,0x34,0x34,0x34,0x3C,0x00},  /* a */
  {0x00,0x3F,0x24,0x24,0x1C,0x00},  /* b */
  {0x00,0x38,0x24,0x24,0x00,0x00},  /* c */
  {0x38,0x24,0x24,0x3F,0x00,0x00},  /* d */
  {0x00,0x18,0x2C,0x2C,0x2C,0x00},  /* e */
  {0x04,0x04,0x3F,0x05,0x01,0x00},  /* f */
  {0xFC,0xD4,0xD4,0xDC,0x00,0x00},  /* g */
  {0x00,0x3F,0x04,0x04,0x3C,0x00},  /* h */
  {0x00,0x24,0x24,0x3D,0x20,0x00},  /* i */
  {0x00,0x84,0x84,0xFD,0x00,0x00},  /* j */
  {0x00,0x3F,0x08,0x14,0x20,0x00},  /* k */
  {0x00,0x21,0x21,0x3F,0x20,0x00},  /* l */
  {0x3C,0x04,0x3C,0x04,0x3C,0x00},  /* m */
  {0x00,0x3C,0x04,0x04,0x3C,0x00},  /* n */
  {0x18,0x24,0x24,0x18,0x00,0x00},  /* o */
  {0x00,0xFC,0x24,0x24,0x1C,0x00},  /* p */
  {0x38,0x24,0x24,0xFC,0x00,0x00},  /* q */
  {0x00,0x3C,0x04,0x04,0x0C,0x00},  /* r */
  {0x00,0x2C,0x2C,0x34,0x34,0x00},  /* s */
  {0x04,0x3E,0x24,0x24,0x00,0x00},  /* t */
  {0x00,0x3C,0x20,0x20,0x3C,0x00},  /* u */
  {0x00,0x1C,0x20,0x1C,0x00,0x00},  /* v */
  {0x0C,0x30,0x18,0x38,0x04,0x00},  /* w */
  {0x24,0x18,0x08,0x18,0x24,0x00},  /* x */
  {0x80,0x9C,0x60,0x1C,0x00,0x00},  /* y */
  {0x00,0x24,0x3C,0x24,0x00,0x00},  /* z */
  {0x00,0x08,0xF7,0x81,0x00,0x00},  /* { */
  {0x00,0x00,0xFF,0x00,0x00,0x00},  /* | */
  {0x00,0x81,0xF7,0x08,0x00,0x00},  /* } */
  {0x08,0x18,0x10,0x18,0x00,0x00},  /* ~ */};
static void oled_setpos(uint8_t page, uint8_t col);
static void oled_putchar(char c);
static void oled_puts(uint8_t page, uint8_t col, const char *s);
/* ===== SSD1306 OLED 最小驱动 ===== */
#define OLED_ADDR   0x78
static void oled_cmd(uint8_t c);
static void oled_dat(const uint8_t *buf, uint16_t len);
static void oled_init(void);
static void oled_fill(uint8_t val);
typedef enum { ST_IDLE = 0, ST_PRESS, ST_LONG } touch_state_t;

static touch_state_t st_touch = ST_IDLE;   /* 当前状态 */
static uint32_t t_press = 0;               /* 按下时刻 */
static uint32_t g_short_cnt = 0;           /* 短按次数 */
static uint32_t g_long_cnt  = 0;           /* 长按次数 */
static void touch_fsm(void);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  /* ===== I2C 探测：OLED 地址 0x78 或 0x7A ===== */
  uint8_t g_oled_addr = 0;
  if (HAL_I2C_IsDeviceReady(&hi2c1, 0x78, 3, 100) == HAL_OK)      g_oled_addr = 1;
  else if (HAL_I2C_IsDeviceReady(&hi2c1, 0x7A, 3, 100) == HAL_OK) g_oled_addr = 2;
  if (g_oled_addr)
  {
    oled_init();
    oled_fill(0x00);                    /* 清屏 */
    oled_puts(1, 4, "Group 25");
    oled_puts(3, 4, "OLED OK");
    oled_puts(5, 4, "F103C8T6");
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    /* 调试 OLED 期间暂停 touch_fsm，避免抢 LED；查完恢复 */
    /* touch_fsm(); */
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    HAL_Delay(1000);   /* 1s 心跳：程序在跑 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/* ---------- SSD1306 驱动 ---------- */
static void oled_cmd(uint8_t c)
{
  uint8_t buf[2] = { 0x00, c };           /* 0x00 = 命令 */
  HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, buf, 2, 100);
}

static void oled_dat(const uint8_t *buf, uint16_t len)
{
  uint8_t tmp[129];
  if (len > 128) len = 128;
  tmp[0] = 0x40;                          /* 0x40 = 数据 */
  for (uint16_t i = 0; i < len; i++) tmp[1 + i] = buf[i];
  HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, tmp, len + 1, 100);
}

static void oled_init(void)
{
  HAL_Delay(100);
  oled_cmd(0xAE);          /* 关显示 */
  oled_cmd(0xD5); oled_cmd(0x80);
  oled_cmd(0xA8); oled_cmd(0x3F);   /* 64 行 */
  oled_cmd(0xD3); oled_cmd(0x00);
  oled_cmd(0x40);
  oled_cmd(0x8D); oled_cmd(0x14);   /* 电荷泵开 */
  oled_cmd(0x20); oled_cmd(0x00);   /* 水平寻址 */
  oled_cmd(0xA1);                   /* 左右不镜像 */
  oled_cmd(0xC8);                   /* 上下不镜像 */
  oled_cmd(0xDA); oled_cmd(0x12);
  oled_cmd(0x81); oled_cmd(0xCF);   /* 亮度 */
  oled_cmd(0xD9); oled_cmd(0xF1);
  oled_cmd(0xDB); oled_cmd(0x40);
  oled_cmd(0xA4);
  oled_cmd(0xA6);                   /* 正常显示 */
  oled_cmd(0xAF);                   /* 开显示 */
}

static void oled_setpos(uint8_t page, uint8_t col)
{
  oled_cmd(0xB0 + page);
  oled_cmd(col & 0x0F);
  oled_cmd(0x10 | (col >> 4));
}

static void oled_putchar(char c)
{
  if (c < 32 || c > 126) c = ' ';
  oled_dat(font6x8[c - 32], 6);
}

static void oled_puts(uint8_t page, uint8_t col, const char *s)
{
  oled_setpos(page, col);
  while (*s) { oled_putchar(*s++); }
}
static void oled_fill(uint8_t val)
{
  uint8_t line[128];
  for (uint8_t i = 0; i < 128; i++) line[i] = val;
  for (uint8_t page = 0; page < 8; page++)
  {
    oled_cmd(0xB0 + page);          /* 选页 */
    oled_cmd(0x00);                 /* 列低位 */
    oled_cmd(0x10);                 /* 列高位 */
    oled_dat(line, 128);
  }
}
/* 触摸按键状态机：每 5ms 调用一次 */
static void touch_fsm(void)
{
  uint32_t now = HAL_GetTick();
  uint8_t  lv  = (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);  /* 0=按下 1=松开 */

  switch (st_touch)
  {
    case ST_IDLE:
      if (lv == 0) { t_press = now; st_touch = ST_PRESS; }
      break;

    case ST_PRESS:
      if (lv == 1) {
        if (now - t_press < 1000) {
          g_short_cnt++;
          HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);   /* 短按：翻转 */
        }
        st_touch = ST_IDLE;
      } else if (now - t_press >= 1000) {
        g_long_cnt++;
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);  /* 长按：强制关 */
        st_touch = ST_LONG;
      }
      break;

    case ST_LONG:
      if (lv == 1) st_touch = ST_IDLE;
      break;
  }
}
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}
/* 说明：旧的 EXTI 回调已移除，按键事件统一由 touch_fsm 轮询处理 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
