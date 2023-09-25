/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __CUSTOM_API_CALLBACK_H
#define __CUSTOM_API_CALLBACK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

#include "SSI_cmd.h"

/* Exported data prototypes --------------------------------------------------*/


/* Function Declarations -----------------------------------------------------*/
//int8_t CST_APIcbSendDataToGUI(uint8_t *const dest);
int8_t CST_APIcbSendDataToGUI(BarcodeRecord_t *const dest);
char*  CST_APIcbGetDecodeData(char **getMsg);
int8_t CST_APIcbSendKeyToGUI(uint8_t *key);
int8_t CST_APIcbRxKeyData(uint8_t *getKey);
int8_t CST_APIcbGetBackendStatus(uint16_t *status);
int8_t CST_APIcbSendBackendStatus(uint16_t *status);
uint32_t CST_APIGetCanopyTicks();

#ifdef __cplusplus
}
#endif

#endif // __CUSTOM_API_CALLBACK_H
