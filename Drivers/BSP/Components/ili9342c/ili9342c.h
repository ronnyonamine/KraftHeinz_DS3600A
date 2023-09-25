/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ILI9342C_H
#define __ILI9342C_H

#ifdef __cplusplus
extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported types -----------------------------------------------------------*/

/* Exported constants -------------------------------------------------------*/
extern short int displayon_timeout_set_flag;

/* Macros --------------------------------------------------------------------*/
#define INACTIVITY_SCREEN_SAVER_TIMEOUT 300000
#define CHARGING_SCREEN_SAVER_TIMEOUT   60000

/* Exported macro -----------------------------------------------------------*/

/* Exported functions prototypes --------------------------------------------*/
void     ili9342c_Init(void);
uint16_t ili9342c_ReadID(void);
void     ili9342c_DisplayOn(void);
void     ili9342c_DisplayOff(void);
void     ili9342c_DisplayOn_Chargemode(void);
void     ili9342c_TimeoutDimming(void);
void     ili9342c_StopTimeoutDimming(void);
void     ili9342c_WriteReg(uint8_t LCD_Reg);
void     ili9342c_WriteData(uint8_t RegValue);
void     ili9342c_WriteMultipleData(uint16_t *pData, uint32_t Size);
uint32_t ili9342c_ReadData(uint16_t RegValue, uint8_t ReadSize);
void     ili9342c_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
uint16_t ili9342c_GetLcdPixelWidth(void);
uint16_t ili9342c_GetLcdPixelHeight(void);

/* Exported data prototypes -------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __ILI9342C_H */

