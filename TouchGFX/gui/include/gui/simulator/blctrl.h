/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __BLCTRL_H
#define __BLCTRL_H

#ifdef __cplusplus
extern "C" {
#endif

#define DELAY_BLCtrl            3000
#define DELAY_BL_PWM            50
#define DELAY_ALS_READ          1000
#define ALS_ARRAY_MAX_NUM       3
#define FCD_MAX                 8000

extern void ili9342c_DisplayClear(void);
extern void ili9342c_DisplayClear_Chargemode(void);
extern void ili9342c_DisplayDim(void);

extern void ALS_Setting(uint8_t);
extern int get_ALS_Status(void);

extern int DimmingFlag;
#ifdef __cplusplus
}
#endif

#endif // __BLCTRL_H
