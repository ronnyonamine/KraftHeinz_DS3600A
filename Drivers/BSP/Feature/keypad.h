/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEYPAD_H
#define __KEYPAD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Public typedef ------------------------------------------------------------*/
typedef enum{
  LayerPrimary = 0,
  LayerBlue,
  LayerGreen,
} multiLayer_t;

//Key Code
typedef enum{
  scancode_KEY_NONE = 0,
  scancode_KYP_UP,
  scancode_KYP_DOWN,
  scancode_KYP_LEFT,
  scancode_KYP_RIGHT,
  scancode_KYP_ENTER,
  scancode_KYP_BLUE,
  scancode_KYP_GREEN,
  scancode_KYP_NUM1,
  scancode_KYP_NUM2,
  scancode_KYP_NUM3,
  scancode_KYP_NUM4,
  scancode_KYP_NUM5,
  scancode_KYP_NUM6,
  scancode_KYP_NUM7,
  scancode_KYP_NUM8,
  scancode_KYP_NUM9,
  scancode_KYP_NUM0,
  scancode_KYP_BKSP,
  scancode_KYP_HOME
} keyScancode_t;

/* Function Declarations -----------------------------------------------------*/
extern multiLayer_t get_multiLayer_state(void);
extern keyScancode_t getScancode(void);

/* Callback for the keypad_scroll_timer */
void keypad_scroll_cb (void *argument);

/* Exported data prototypes --------------------------------------------------*/
extern uint8_t key_quantity;
extern uint8_t reset_flag;

//KEY code
extern keyScancode_t key_state;

#ifdef __cplusplus
}
#endif

#endif /* __KEYPAD_H */
