/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SENDQTY_API_H
#define __SENDQTY_API_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
   
#include "SSI_cmd.h"

/* Macros --------------------------------------------------------------------*/

#define MIN_SENDQTY_LIMIT                   (0) //change it to 0 to 1
#define MAX_SENDQTY_LIMIT                   (9999)
#define MAX_EDIT_BARCODE_LENGTH             (200)
#define MAX_EDIT_LOCATION_LENGTH            (20)
#define MAX_SCANNED_BARCODE_LENGTH          (3073)

#define APP_SEND_QTY_FAIL                   (0)
#define APP_SEND_QTY_SUCESS                 (1)
#define APP_SEND_QTY_UNDERFLOW_ERROR        (-1L)
#define APP_SEND_QTY_OVERFLOW_ERROR         (-2L)
#define APP_SEND_QTY_INVALID_DATA           (-3L)
#define APP_SEND_QTY_INVALID_LENGTH         (-4L)
#define APP_SEND_QTY_IN_PROGRESS            (-5L)

/* Public typedef ------------------------------------------------------------*/

/* Exported data prototypes --------------------------------------------------*/

/* Function Declarations -----------------------------------------------------*/

int8_t CST_APIsendQuantity(uint16_t quantity);
int8_t CST_APIsendManualBarCodeQty(char *barcode, uint16_t quantity);
int8_t CST_APIsendLocBarCodeQty(LocRecord_t *location, BarcodeRecord_t *barcode, uint16_t quantity);
uint8_t getBatteryLevel(void);
uint8_t getBatteryChargingStatus(void);
uint16_t getBatteryPercentage(void);
int8_t getBTStatus(void);

#ifdef __cplusplus
}
#endif

#endif /* __SENDQTY_API_H */
