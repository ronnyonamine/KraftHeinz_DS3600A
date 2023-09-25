/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

#ifndef __OPT3001_H
#define __OPT3001_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @defgroup OPT3001_Exported_Constants
  * @{
  */

/** 
  * @brief OPT3001 chip IDs  
  */ 
#define OPT3001_DevID                  0x3001
#define OPT3001_MfgID                  0x5449

/** 
  * @brief  OPT3001 Registers  
  */
#define Reg_Result             0x00   /* Result Register */
#define Reg_Configuration      0x01   /* Configuration Register */
#define Reg_LowLimit           0x02   /* Low-Limit */
#define Reg_HighLimit          0x03   /* High-Limit */
#define Reg_MfgID              0x7E   /* Manufacturer ID */
#define Reg_DevID              0x7F   /* Device ID */

#define WAF     2.4 /* Window Attenuation Factor*/
/**
  * @}
  */
  
/** @defgroup OPT3001_Exported_Functions
  * @{
  */ 
void OPT3001_Init(void);
void OPT3001_Shutdown(void);
uint16_t OPT3001_ReadID(void);
double OPT3001_ReadLux(void);

#ifdef __cplusplus
}
#endif

#endif /* __OPT3001_H */

/**
  * @}
  */ 

