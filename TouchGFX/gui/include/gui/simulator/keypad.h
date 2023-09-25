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
#include <gui/simulator/keycode.h>
/* Public typedef ------------------------------------------------------------*/
typedef enum{
  LayerPrimary = 0,
  LayerBlue,
  LayerGreen,
} multiLayer_t;

/* Function Declarations -----------------------------------------------------*/
extern multiLayer_t get_multiLayer_state(void);
void keycodeMapping(uint16_t);
/* Exported data prototypes --------------------------------------------------*/
extern uint8_t key_quantity;
extern uint8_t reset_flag;

#ifdef __cplusplus
}
#endif

#endif /* __KEYPAD_H */
