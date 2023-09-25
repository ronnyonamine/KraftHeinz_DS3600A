/**
 ******************************************************************************
 * @file    oxpecker_platform.h
 * @author  SIANA Systems
 * @date    02/2021
 * @brief   Defines the general API for the oxpecker platform code
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>© COPYRIGHT 2021 SIANA Systems</center></h2>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 ******************************************************************************
 */
#ifndef __HEADER_H
#define __HEADER_H
 
#ifdef __cplusplus
 extern "C" {
#endif
 
/** @addtogroup SIANA
 * @{
 */
/** @addtogroup Controllers
 * @{
 */
/** @addtogroup oxpecker_platform
 * @{
 */
 
#include <stdbool.h>
#include <stdint.h>
#include "stm32l4xx_hal.h"
 
/*----------------------------------------------------------------------------*/
/** @addtogroup PUBLIC_Macros                                                 */
/**@{                                                                         */
/*----------------------------------------------------------------------------*/
 
/** @} */
/*----------------------------------------------------------------------------*/
/** @addtogroup PUBLIC_Definitions                                            */
/**@{                                                                         */
/*----------------------------------------------------------------------------*/
 

/** @} */
/*----------------------------------------------------------------------------*/
/** @addtogroup PUBLIC_Types                                                  */
/**@{                                                                         */
/*----------------------------------------------------------------------------*/
 
/**
  * @brief defines the BLE peripheral controller status code
  */
typedef enum {
  PLATFORM_OK,                                  /*< No issues on call */
  PLATFORM_INIT_ERROR,                          /*< Init routine failed */
  PLATFORM_NOT_IMPLEMENTED                      /*< API Call not implemented */
} t_oxpecker_status;

 
/** @} */
/*----------------------------------------------------------------------------*/
/** @addtogroup PUBLIC_API                                                    */
/**@{                                                                         */
/*----------------------------------------------------------------------------*/
 
/**
 * @brief Performs all initialization of the hardware and platform level code
 *
 * @param None
 *
 * @retval status code for operation. See @t_oxpecker_status
 */
t_oxpecker_status oxpecker_platform_init(void);

/**
 * @brief Callback for Idle Line Detection UART interrupt.
 * 
 * Should be called directly on the corresponding USARTx_IRQHandler()
 *
 * @param huart Handle for the uart corresponding to the caller ISR
 *
 * @retval none
 */
void oxpecker_UART_IDLECallback(UART_HandleTypeDef *huart);

/**
 * @brief Callback for Idle Line Detection UART interrupt.
 * 
 * Should be called directly on the corresponding USARTx_IRQHandler()
 *
 * @param huart Handle for the uart corresponding to the caller ISR
 *
 * @retval none
 */
void oxpecker_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
 
/*----------------------------------------------------------------------------*/
/** @} */
/*--->> END: PUBLIC API <<----------------------------------------------------*/
 
/** @} */
/** @} */
/** @} */
 
#ifdef __cplusplus
}
#endif
 
#endif