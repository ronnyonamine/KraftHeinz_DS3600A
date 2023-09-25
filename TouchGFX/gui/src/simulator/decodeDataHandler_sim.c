/**
 ******************************************************************************
 * @file    decodeDataHandler_sim.c
 * @author  SIANA Systems
 * @date    02/2021
 * @brief   Implements required APIs for decodeDataHandler_sim TGFX simulator
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
 
/** @addtogroup SIANA
 * @{
 */
/** @addtogroup Controllers
 * @{
 */
/** @addtogroup decodeDataHandler_sim
 * @{
 */
/**
 * @defgroup PUBLIC_Definitions          PUBLIC constants
 * @defgroup PUBLIC_Macros               PUBLIC macros
 * @defgroup PUBLIC_Types                PUBLIC data-types
 * @defgroup PUBLIC_API                  PUBLIC API
 * @defgroup PRIVATE_TUNABLES            Private compile-time tunables
 * @defgroup PRIVATE_Definitions         Private constants
 * @defgroup PRIVATE_Macros              Private macros
 * @defgroup PRIVATE_Types               Private data-types
 * @defgroup PRIVATE_Data                Private data / variables
 * @defgroup PRIVATE_Functions           Private functions
*/
#ifdef SIMULATOR

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <gui/simulator/decodeDataHandler.h>
/** @} */
/*----------------------------------------------------------------------------*/
/** @addtogroup PRIVATE_Macros                                                */
/**@{                                                                         */
/*----------------------------------------------------------------------------*/
 
/** @} */
/*----------------------------------------------------------------------------*/
/** @addtogroup PRIVATE_Types                                                 */
/**@{                                                                         */
/*----------------------------------------------------------------------------*/

/** @} */
/*----------------------------------------------------------------------------*/
/** @addtogroup PRIVATE_Functions                                             */
/**@{                                                                         */
/*----------------------------------------------------------------------------*/

/** @} */
/*----------------------------------------------------------------------------*/
/** @addtogroup PRIVATE_Data                                                  */
/**@{                                                                         */
/*----------------------------------------------------------------------------*/

/** @} */
/*----------------------------------------------------------------------------*/
/** @addtogroup PUBLIC_API                                                    */
/**@{                                                                         */
/*----------------------------------------------------------------------------*/


/*
 * API: CST_APIsendQuantity
 */
int8_t CST_APIsendQuantity(uint16_t quantity)
{
  /* Quantity Value check  is the only thing performed in sim */
  if (quantity <= MIN_SENDQTY_LIMIT)
  {
    return APP_SEND_QTY_UNDERFLOW_ERROR;
  }

  if (quantity > MAX_SENDQTY_LIMIT)
  {
	return APP_SEND_QTY_OVERFLOW_ERROR;
  }

  return APP_SEND_QTY_SUCESS;
}

/*
 * API: CST_APIsendManualBarCodeQty
 */
int8_t CST_APIsendManualBarCodeQty(char *barcode, uint16_t quantity)
{
  int length = 0;

  /* Quantity Value check */
  if (quantity <= MIN_SENDQTY_LIMIT)
  {
    return APP_SEND_QTY_UNDERFLOW_ERROR;
  }

  if (quantity > MAX_SENDQTY_LIMIT)
  {
	return APP_SEND_QTY_OVERFLOW_ERROR;
  }
  
  if (barcode != NULL) 
  {
	/* Check string size */
	length = strlen(barcode);
	
	if(length <= MAX_EDIT_BARCODE_LENGTH) 
	{
      return APP_SEND_QTY_SUCESS;
	} 
	else
	{
	  return APP_SEND_QTY_INVALID_LENGTH;
    }
  } 
  else 
  {
	return APP_SEND_QTY_INVALID_DATA;
  }
  
  return APP_SEND_QTY_SUCESS;
}

/*
 * API: CST_APIsendLocBarCodeQty
 */
int8_t CST_APIsendLocBarCodeQty(LocRecord_t *location, BarcodeRecord_t *barcode, uint16_t quantity)
{
  return APP_SEND_QTY_SUCESS;
}

uint8_t getBatteryLevel(void)
{
  
    return 0x01; 

}

uint8_t getBatteryChargingStatus(void)
{
  return 0x01;
}

uint16_t getBatteryPercentage(void)
{
   return 99;
}

int8_t getBTStatus(void)
{
   //connect
    return 1;
}


#endif
