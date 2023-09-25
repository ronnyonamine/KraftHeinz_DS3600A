/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MENU_HANDLER_H
#define __MENU_HANDLER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>

/* Macros --------------------------------------------------------------------*/

//#define MIN_DISPLAY_TIME_IN_MS                   (3000)
//#define MAX_DISPLAY_TIME_IN_MS                   (20000)

//#define APP_DISPLAY_INVALID_TIMEOUT             (0xFFFF)
#define CONFIG_SETTING_SUCCESS                      1
#define CONFIG_SETTING_FAIL                         0


/* Function Declarations -----------------------------------------------------*/
//multiLayer_t CST_APIgetMultiLayerKeyBoard(void);            //get multilayer keyBoard

uint8_t CST_APIsetKeypadBL(uint8_t setting,bool permanent);                   //set Keypad Backlight
uint8_t CST_APIgetKeypadBL(void);                           //get Keypad Backlight
uint8_t CST_APIsetDisplayTimeout(uint8_t setting,bool permanent);    //set DisplayTimeout
uint8_t CST_APIgetDisplayTimeout(void);                    //get DisplayTimeout
uint8_t CST_APIsetDisplayBrightness(uint8_t setting,bool permanent);   //set display brighness
uint8_t CST_APIgetDisplayBrightness(void);                    //get display brightness

/* Exported data prototypes --------------------------------------------------*/

//TODO: Implement following APIs
// void ALS_Setting(uint8_t status);               //set AutoBrightness
// int get_ALS_Status(void);                       //get AutoBrightness

#ifdef __cplusplus
}
#endif

#endif /* __MENU_HANDLER_H */
