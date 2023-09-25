/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Includes ------------------------------------------------------------------*/

#ifdef SIMLATOR
#include <gui/simulator/blctrl.h>

/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

int DimmingFlag = 0;

int ALS_Status = 1; //ALS Default Enable


/* External variables --------------------------------------------------------*/

/******************************************************
 *               Function Declarations
 ******************************************************/

/******************************************************
 *               Function Definitions
 ******************************************************/

void ALS_Setting(uint8_t status)
{
  ALS_Status = status;
}

int get_ALS_Status(void)
{
  return ALS_Status;
}

void ili9342c_DisplayClear(void)
{
  DimmingFlag = 0;
  return;
}

void ili9342c_DisplayClear_Chargemode(void)
{
  DimmingFlag = 0;
  return;
}

void ili9342c_DisplayDim(void)
{
  DimmingFlag = 1;
  return;
}

#endif
