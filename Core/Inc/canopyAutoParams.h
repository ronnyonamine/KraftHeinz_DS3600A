/*                                                                                                     
 * Copyright (c) 2021 Zebra Technologies and/or its affiliates. All rights reserved                    
 */                                                                                                    
                                                                                                       
// ----------------------------------------------------------------------------------------------------
//  Canopy Param attribute definition structure                                                        
//  NOTE This file is auto-generated                                                                   
// ----------------------------------------------------------------------------------------------------
                                                                                                       
#ifndef __CANOPYAUTOPARAMS_H                                                                           
#define __CANOPYAUTOPARAMS_H                                                                           
                                                                                                       
                                                                                                       
#ifdef __cplusplus                                                                                     
extern "C" {                                                                                         
#endif                                                                                                 
                                                                                                       
#include <stdint.h>                                                                                    
#include "string.h"                                                                                  
#include <stdio.h>                                                                                     
#include <stdarg.h>                                                                                    
#include <stdbool.h>                                                                                   
                                                                                                       
                                                                                                       
typedef enum                                                                                           
{                                                                                                      
   spc_unknown,                                                                                        
   spc_zlegacy,                                                                                        
   spc_zlegacywithauto,                                                                                
   spc_zreserved,                                                                                      
   spc_vendornew                                                                                       
} SPECIAL_CASE_T;                                                                                      
                                                                                                       
const typedef struct                                                                                   
{                                                                                                      
   char                type[30];
   char                name[29];
   uint16_t            attribute_number;                                                               
   uint8_t             size;                                                                           
   char                sign[10];                                                                       
   uint32_t            default_value;                                                                  
   char                default_value_string[106]; // CONSOLIDATED_STR_MAX_SIZE + 5
   uint32_t            min_value;   // not valid for string type                                       
   uint32_t            max_value;   // not valid for string type                                       
   uint32_t            gui_value_set[10];
   SPECIAL_CASE_T      specialcase;                                                                    
   uint16_t            defaultvaluelength;                                                              
}paramfilestruct;                                                                                      
                                                                                                       
paramfilestruct allparamlines[] = {                                                              
  { "gblDispTout", "Display Timeout", 0x860, 1, "false", 0x0C, "na", 0, 18, {3, 6, 12, 18, 0}, spc_zlegacywithauto, 2 },
  { "gblF1Key_radio", "F1_radio", 0x861, 1, "false", 0x00, "na", 0, 4, {0, 1, 2, 3, 4}, spc_zlegacy, 2 },
  { "gblF2Key_radio", "F2_radio", 0x862, 1, "false", 0x00, "na", 0, 4, {0, 1, 2, 3, 4}, spc_zlegacy, 2 },
  { "gblF3Key_radio", "F3_radio", 0x863, 1, "false", 0x00, "na", 0, 4, {0, 1, 2, 3, 4}, spc_zlegacy, 2 },
  { "gblF4Key_radio", "F4_radio", 0x864, 1, "false", 0x00, "na", 0, 4, {0, 1, 2, 3, 4}, spc_zlegacy, 2 },
  { "gblF5Key_radio", "F5_radio", 0x865, 1, "false", 0x00, "na", 0, 4, {0, 1, 2, 3, 4}, spc_zlegacy, 2 },
  { "gblF6Key_radio", "F6_radio", 0x866, 1, "false", 0x00, "na", 0, 4, {0, 1, 2, 3, 4}, spc_zlegacy, 2 },
  { "gblF7Key_radio", "F7_radio", 0x867, 1, "false", 0x00, "na", 0, 4, {0, 1, 2, 3, 4}, spc_zlegacy, 2 },
  { "gblF8Key_radio", "F8_radio", 0x868, 1, "false", 0x00, "na", 0, 4, {0, 1, 2, 3, 4}, spc_zlegacy, 2 },
  { "gblF9Key_radio", "F9_radio", 0x869, 1, "false", 0x00, "na", 0, 4, {0, 1, 2, 3, 4}, spc_zlegacy, 2 },
  { "gblManBCEntry", "Manual Barcode Entry", 0x86A, 1, "false", 0x01, "na", 0, 1, { 0, 1}, spc_zlegacywithauto, 2 },
  { "gblManQtyEntry", "Manual Quantity Entry", 0x86B, 1, "false", 0x01, "na", 0, 1, { 0, 1}, spc_zlegacywithauto, 2 },
  { "gblAutoDispBrt", "Auto Display Brightness", 0x86C, 1, "false", 0x01, "na", 1, 6, {1, 2, 3, 4, 5, 6}, spc_zlegacywithauto, 2 },
  { "gblKeypadBacklight", "Keypad Backlight", 0x86D, 1, "false", 0x02, "na", 0, 3, {0, 1, 2}, spc_zlegacywithauto, 2 },
  { "gblHomeKey", "Home Key Launch", 0x86E, 1, "false", 0x01, "na", 0, 6, {0, 1, 2, 3, 4, 5, 6}, spc_zlegacywithauto, 2 },
  { "seqManBCEdit", "Manual BC Entry", 0x86F, 1, "false", 0x01, "na", 0, 1, { 0, 1}, spc_zlegacywithauto, 2 },
  { "seqManQTYEdit", "Manual QTY Entry", 0x870, 1, "false", 0x01, "na", 0, 1, { 0, 1}, spc_zlegacywithauto, 2 },
  { "seqTout", "Quantity Timeout", 0x871, 1, "false", 0x06, "na", 0, 60, {3, 6, 9, 18, 30, 60, 0}, spc_zlegacywithauto, 2 },
  { "selManBCEdit", "Manual BC Entry loc", 0x872, 1, "false", 0x01, "na", 0, 1, { 0, 1}, spc_zlegacywithauto, 2 },
  { "selManQTYEdit", "Manual QTY Entry loc", 0x873, 1, "false", 0x01, "na", 0, 1, { 0, 1}, spc_zlegacywithauto, 2 },
  { "selDelim", "Delimiter loc", 0x874, 1, "true", 0x09, "na", 0, 127, {13, 10, 32, 9, 44, 58, 59, 61}, spc_zlegacywithauto, 2 },
  { "sinvManBCEdit", "Manual BC Entry invt", 0x875, 1, "false", 0x01, "na", 0, 1, { 0, 1}, spc_zlegacywithauto, 2 },
  { "sinvManQTYEdit", "Manual QTY Entry invt", 0x876, 1, "false", 0x01, "na", 0, 1, { 0, 1}, spc_zlegacywithauto, 2 },
  { "sinvDelim", "INVT LOC Delimiter", 0x877, 1, "true", 0x09, "na", 0, 127, {13, 10, 32, 9, 44, 58, 59, 61}, spc_zlegacywithauto, 2 },
  { "sinvStore", "Inventory Store", 0x878, 1, "false", 0x00, "na", 0, 1, {0, 1}, spc_zlegacywithauto, 2 },
  { "gbDispOnCharge", "Display On Charge", 0x87A, 1, "false", 0x03, "na", 1, 3, {1, 2, 3}, spc_zlegacywithauto, 2 },
  { "gblF1Key", "F1", 0x87B, 15, "false", 0x00, "", 0, 0, { 0 }, spc_zlegacy, 0 },
  { "gblF2Key", "F2", 0x87C, 15, "false", 0x00, "", 0, 0, { 0 }, spc_zlegacy, 0 },
  { "gblF3Key", "F3", 0x87D, 15, "false", 0x00, "", 0, 0, { 0 }, spc_zlegacy, 0 },
  { "gblF4Key", "F4", 0x87E, 15, "false", 0x00, "", 0, 0, { 0 }, spc_zlegacy, 0 },
  { "gblF5Key", "F5", 0x87F, 15, "false", 0x00, "", 0, 0, { 0 }, spc_zlegacy, 0 },
  { "gblF6Key", "F6", 0x880, 15, "false", 0x00, "", 0, 0, { 0 }, spc_zlegacy, 0 },
  { "gblF7Key", "F7", 0x881, 15, "false", 0x00, "", 0, 0, { 0 }, spc_zlegacy, 0 },
  { "gblF8Key", "F8", 0x882, 15, "false", 0x00, "", 0, 0, { 0 }, spc_zlegacy, 0 },
  { "gblF9Key", "F9", 0x883, 15, "false", 0x00, "", 0, 0, { 0 }, spc_zlegacy, 0 },
  { "gblKeyboardInject", "KeyboardInject", 0x884, 1, "false", 0x00, "na", 0, 0, { 0, 1}, spc_zreserved, 2 },
  { "gblQtyXferMode", "QTY Transfer Mode", 0x885, 1, "false", 0x01, "na", 1, 2, {1, 2}, spc_vendornew, 2 },
  { "sqtyDelim", "QTY Delimiter", 0x886, 1, "true", 0x09, "na", 0, 127, {13, 10, 32, 9, 44, 58, 59, 61}, spc_vendornew, 2 },
  { "slocDelim", "Loc Delimiter", 0x887, 1, "true", 0x09, "na", 0, 127, {13, 10, 32, 9, 44, 58, 59, 61}, spc_vendornew, 2 },
  { "sqtyqtyDelim", "QTY QTY Delimiter", 0x888, 1, "true", 0x09, "na", 0, 127, {13, 10, 32, 9, 44, 58, 59, 61}, spc_vendornew, 2 },
  { "slocqtyDelim", "LOC QTY Delimiter", 0x889, 1, "true", 0x09, "na", 0, 127, {13, 10, 32, 9, 44, 58, 59, 61}, spc_vendornew, 2 },
  { "sinvtqtyDelim", "INVT QTY Delimiter", 0x88A, 1, "true", 0x09, "na", 0, 127, {13, 10, 32, 9, 44, 58, 59, 61}, spc_vendornew, 2 },
  { "sqtyToutConf", "Confirm QTY Tmout", 0x88B, 1, "false", 0x02, "na", 0, 6, {0, 1, 2, 5}, spc_vendornew, 2 },
  { "conflocTout", "Confirm LOC Tmout", 0x88C, 1, "false", 0x02, "na", 0, 6, {0, 1, 2, 5}, spc_vendornew, 2 },
  { "gblMinQtyValue", "Min Qty Value", 0x88D, 2, "false", 0x01, "na", 0, 9999, {1}, spc_vendornew, 2 },
  { "gblMaxQtyValue", "Max Qty Value", 0x88E, 2, "false", 0x270F, "na", 1, 9999, {9999}, spc_vendornew, 2 }
};                                                                                                      

#ifdef __cplusplus                                                                                      
}                                                                                                       
#endif                                                                                                  
                                                                                                        
                                                                                                        
#endif /* __CANOPYAUTOPARAMS_H */                                                                       
