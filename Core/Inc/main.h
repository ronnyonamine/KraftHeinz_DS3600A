/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "keypad.h"


// stack protection check - turn on for debugging
//
//extern uint32_t  __stack_chk_guard;


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
//Debug level definition
typedef enum
{
  debug_basic = 0,
  debug_level1 = 1,
  debug_level2 = 2
} Debug_Level;

#ifdef DEBUG_LEVEL1
  #define DEBUG_LEVEL 1
#elif defined DEBUG_LEVEL2
  #define DEBUG_LEVEL 2
#else
  #define DEBUG_LEVEL 0
#endif

#define debug_printf(DebugLevel,fmt, ...)  if(DebugLevel >= DEBUG_LEVEL) printf(fmt, ##__VA_ARGS__);
/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KYP_LEFT_Pin GPIO_PIN_2
#define KYP_LEFT_GPIO_Port GPIOH
#define KYP_NUM5_Pin GPIO_PIN_0
#define KYP_NUM5_GPIO_Port GPIOI
#define KYP_NUM3_Pin GPIO_PIN_14
#define KYP_NUM3_GPIO_Port GPIOH
#define TFT_RST_Pin GPIO_PIN_7
#define TFT_RST_GPIO_Port GPIOI
#define TFT_PWR_EN_MCU_Pin GPIO_PIN_5
#define TFT_PWR_EN_MCU_GPIO_Port GPIOB
#define KYP_NUM7_Pin GPIO_PIN_2
#define KYP_NUM7_GPIO_Port GPIOI
#define KYP_NUM6_Pin GPIO_PIN_1
#define KYP_NUM6_GPIO_Port GPIOI
#define KYP_NUM4_Pin GPIO_PIN_15
#define KYP_NUM4_GPIO_Port GPIOH
#define KYP_NUM1_Pin GPIO_PIN_12
#define KYP_NUM1_GPIO_Port GPIOH
#define ICON_LS_EN_MCU_Pin GPIO_PIN_8
#define ICON_LS_EN_MCU_GPIO_Port GPIOB
#define TFT_LS_EN_MCU_Pin GPIO_PIN_6
#define TFT_LS_EN_MCU_GPIO_Port GPIOB
#define KYP_NUM2_Pin GPIO_PIN_13
#define KYP_NUM2_GPIO_Port GPIOH
#define KYP_NUM8_Pin GPIO_PIN_3
#define KYP_NUM8_GPIO_Port GPIOI
#define KYP_NUM9_Pin GPIO_PIN_4
#define KYP_NUM9_GPIO_Port GPIOI
#define KYP_BKSP_Pin GPIO_PIN_7
#define KYP_BKSP_GPIO_Port GPIOH
#define MCU_WKUP_1P8_Pin GPIO_PIN_13
#define MCU_WKUP_1P8_GPIO_Port GPIOC
#define MCU_WKUP_1P8_EXTI_IRQn EXTI15_10_IRQn
#define KYP_HOME_Pin GPIO_PIN_5
#define KYP_HOME_GPIO_Port GPIOI
#define KYP_DOWN_Pin GPIO_PIN_6
#define KYP_DOWN_GPIO_Port GPIOH
#define MCU_ALS_IRQ_Pin GPIO_PIN_6
#define MCU_ALS_IRQ_GPIO_Port GPIOC
#define KPD_LED_Pin GPIO_PIN_7
#define KPD_LED_GPIO_Port GPIOC
#define KYP_BLUE_Pin GPIO_PIN_4
#define KYP_BLUE_GPIO_Port GPIOC
#define SYS_CONFIG3_Pin GPIO_PIN_0
#define SYS_CONFIG3_GPIO_Port GPIOC
#define SYS_CONFIG2_Pin GPIO_PIN_1
#define SYS_CONFIG2_GPIO_Port GPIOC
#define SYS_CONFIG1_Pin GPIO_PIN_2
#define SYS_CONFIG1_GPIO_Port GPIOC
#define KYP_ENTER_Pin GPIO_PIN_5
#define KYP_ENTER_GPIO_Port GPIOC
#define KYP_GREEN_Pin GPIO_PIN_3
#define KYP_GREEN_GPIO_Port GPIOC
#define ANYKEY_WKUP_Pin GPIO_PIN_0
#define ANYKEY_WKUP_GPIO_Port GPIOA
#define ANYKEY_WKUP_EXTI_IRQn EXTI0_IRQn
#define TFT_BKL_Pin GPIO_PIN_0
#define TFT_BKL_GPIO_Port GPIOB
#define KYP_UP_Pin GPIO_PIN_4
#define KYP_UP_GPIO_Port GPIOH
#define KYP_RIGHT_Pin GPIO_PIN_5
#define KYP_RIGHT_GPIO_Port GPIOH
#define SYS_CONFIG0_Pin GPIO_PIN_11
#define SYS_CONFIG0_GPIO_Port GPIOF
#define KYP_NUM0_Pin GPIO_PIN_11
#define KYP_NUM0_GPIO_Port GPIOH
#define CD_Pin GPIO_PIN_14
#define CD_GPIO_Port GPIOB
#define ST_WKUP_ICON_Pin GPIO_PIN_1
#define ST_WKUP_ICON_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
#define EXTERNAL_32MB   //Reserved
#define UART1_TX_BUFFER_SIZE  1024
#define UART1_RX_BUFFER_SIZE  1024
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
