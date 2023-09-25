/**
 ******************************************************************************
 * @file    platform_itf.h
 * @author  SIANA Systems
 * @date    01/2021
 * @brief   Defines Oxpecker Application interface
 *
 * This header abstracts the headers that comprise the Oxpecker platform/UI
 * interface.  It does so by linking all the relevant header files together
 * depending on target platform. Ideally, both sets of headers (Oxpecker or
 * Simulator) should be identical, and a distinction should only be made for
 * Simulator builds.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>© COPYRIGHT 2020 SIANA Systems</center></h2>
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
#ifndef __PLATFORM_ITF_H
#define __PLATFORM_ITF_H
 
#ifdef __cplusplus
 extern "C" {
#endif
 
/** @addtogroup SIANA
 * @{
 */
/** @addtogroup API_wrapper
 * @{
 */
/** @addtogroup platform_itf
 * @{
 */
 
#ifndef SIMULATOR /* Target Platform headers */

#include "../../../Drivers/BSP/Feature/keypad.h"
#include "../../../Drivers/BSP/Feature/blctrl.h"
#include "../../../Drivers/BSP/Feature/user_cfg.h"
#include "../../../Drivers/BSP/Feature/canopyAuto_usercfg.h"
#include "../../../Drivers/BSP/Components/ili9342c/ili9342c.h"
#include "../../../Drivers/BSP/Feature/decodeDataHandler.h"
#include "../../../Drivers/BSP/Feature/customAPIcallback.h"
#include "../../../Drivers/BSP/Feature/keycode.h"
#include "../../../Drivers/BSP/Feature/SSI_cmd.h"
#include "../../../Drivers/BSP/Feature/MenuHandler.h"
#include "../../../Drivers/BSP/Feature/status.h"
#include "../../../Drivers/BSP/Feature/strFilter.h"

#else  /* Simulator headers - should come standalone on UI Template */

#include <gui/simulator/keypad.h>
#include <gui/simulator/blctrl.h>
#include <gui/simulator/user_cfg.h>
#include <gui/simulator/ili9342c.h>
#include <gui/simulator/decodeDataHandler.h>
#include <gui/simulator/customAPIcallback.h>
#include <gui/simulator/SSI_cmd.h>
#include <gui/simulator/status.h>
#include <gui/simulator/menuHandler.h>
#include <gui/simulator/strFilter.h>

#include <gui/common/keycode.h>

#endif


 
 
/** @} */
/** @} */
/** @} */
 
#ifdef __cplusplus
}
#endif
 
#endif
