/*                                                                                             
 * Copyright (c) 2021 Zebra Technologies and/or its affiliates. All rights reserved            
 */                                                                                            
/*** Note This file is auto-generated  ***/                                                    
                                                                                               
#ifndef SIMULATOR                                                                              
                                                                                               
//-----------------------------------------------------------------------                      
//  Canopy Parameter helper routines                                                           
//-----------------------------------------------------------------------                      
                                                                                               
#include <stdio.h>                                                                             
#include <stdbool.h>                                                                             
#include <string.h>                                                                             
#include <stdint.h>                                                                             
#include "user_cfg.h"                                                                        
#include "canopyAuto_usercfg.h"                                                              
#include "user_cfg_wrapper.hpp"                                                              
                                                                                               
User_Config_t  user_cfg_temporary = {                                                          
   .function_key = {                                                                           
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""}                                              
   },                                                                                          
   .live_capture = Manual_Entry_No,                                                            
   .display_timeout = 0x0C,
   .manual_barcode_entry = 0x01,
   .manual_quantity_entry = 0x01,
   .auto_display_brightness = 0x01,
   .keypad_backlight = 0x02,
   .home_key_launch = 0x01,
   .qty_manual_barcode_entry = 0x01,
   .qty_manual_quantity_entry = 0x01,
   .quantity_timeout = {.setting = 0x06, .user_define = 0},
   .loc_manual_barcode_entry = 0x01,
   .loc_manual_quantity_entry = 0x01,
   .loc_delimiter = {.setting = 0x09, .user_define = 0},
   .invt_manual_barcode_entry = 0x01,
   .invt_manual_quantity_entry = 0x01,
   .invt_delimiter = {.setting = 0x09, .user_define = 0},
   .invt_store = 0x00,
   .display_on_charge = 0x03,
   .gblQtyXferMode = 0x01,
   .sqtyDelim = 0x09,
   .slocDelim = 0x09,
   .sqtyqtyDelim = 0x09,
   .slocqtyDelim = 0x09,
   .sinvtqtyDelim = 0x09,
   .sqtyToutConf = 0x02,
   .conflocTout = 0x02,
   .gblMinQtyValue = 0x01,
   .gblMaxQtyValue = 0x270F,
};                                                                                             
                                                                                               
User_Config_t  user_cfg_permanent = {                                                          
   .function_key = {                                                                           
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""},                                             
      {.setting = FuncKey_String, .string = ""}                                              
   },                                                                                          
   .live_capture = Manual_Entry_No,                                                            
   .display_timeout = 0x0C,
   .manual_barcode_entry = 0x01,
   .manual_quantity_entry = 0x01,
   .auto_display_brightness = 0x01,
   .keypad_backlight = 0x02,
   .home_key_launch = 0x01,
   .qty_manual_barcode_entry = 0x01,
   .qty_manual_quantity_entry = 0x01,
   .quantity_timeout = {.setting = 0x06, .user_define = 0},
   .loc_manual_barcode_entry = 0x01,
   .loc_manual_quantity_entry = 0x01,
   .loc_delimiter = {.setting = 0x09, .user_define = 0},
   .invt_manual_barcode_entry = 0x01,
   .invt_manual_quantity_entry = 0x01,
   .invt_delimiter = {.setting = 0x09, .user_define = 0},
   .invt_store = 0x00,
   .display_on_charge = 0x03,
   .gblQtyXferMode = 0x01,
   .sqtyDelim = 0x09,
   .slocDelim = 0x09,
   .sqtyqtyDelim = 0x09,
   .slocqtyDelim = 0x09,
   .sinvtqtyDelim = 0x09,
   .sqtyToutConf = 0x02,
   .conflocTout = 0x02,
   .gblMinQtyValue = 0x01,
   .gblMaxQtyValue = 0x270F,
};                                                                                             
// Private Get - method for gblDispTout
uint32_t   get_gblDispTout(void)
{                                                   
    return user_cfg_temporary.display_timeout;
}                                                   
// Private Set - method for gblDispTout
void   set_gblDispTout(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.display_timeout = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.display_timeout = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for gblManBCEntry
uint32_t   get_gblManBCEntry(void)
{                                                   
    return user_cfg_temporary.manual_barcode_entry;
}                                                   
// Private Set - method for gblManBCEntry
void   set_gblManBCEntry(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.manual_barcode_entry = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.manual_barcode_entry = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for gblManQtyEntry
uint32_t   get_gblManQtyEntry(void)
{                                                   
    return user_cfg_temporary.manual_quantity_entry;
}                                                   
// Private Set - method for gblManQtyEntry
void   set_gblManQtyEntry(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.manual_quantity_entry = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.manual_quantity_entry = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for gblAutoDispBrt
uint32_t   get_gblAutoDispBrt(void)
{                                                   
    return user_cfg_temporary.auto_display_brightness;
}                                                   
// Private Set - method for gblAutoDispBrt
void   set_gblAutoDispBrt(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.auto_display_brightness = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.auto_display_brightness = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for gblKeypadBacklight
uint32_t   get_gblKeypadBacklight(void)
{                                                   
    return user_cfg_temporary.keypad_backlight;
}                                                   
// Private Set - method for gblKeypadBacklight
void   set_gblKeypadBacklight(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.keypad_backlight = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.keypad_backlight = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for gblHomeKey
uint32_t   get_gblHomeKey(void)
{                                                   
    return user_cfg_temporary.home_key_launch;
}                                                   
// Private Set - method for gblHomeKey
void   set_gblHomeKey(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.home_key_launch = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.home_key_launch = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for seqManBCEdit
uint32_t   get_seqManBCEdit(void)
{                                                   
    return user_cfg_temporary.qty_manual_barcode_entry;
}                                                   
// Private Set - method for seqManBCEdit
void   set_seqManBCEdit(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.qty_manual_barcode_entry = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.qty_manual_barcode_entry = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for seqManQTYEdit
uint32_t   get_seqManQTYEdit(void)
{                                                   
    return user_cfg_temporary.qty_manual_quantity_entry;
}                                                   
// Private Set - method for seqManQTYEdit
void   set_seqManQTYEdit(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.qty_manual_quantity_entry = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.qty_manual_quantity_entry = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for seqTout
uint32_t   get_seqTout(void)
{                                                   
    return user_cfg_temporary.quantity_timeout.setting;
}                                                   
// Private Set - method for seqTout
void   set_seqTout(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.quantity_timeout.setting = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.quantity_timeout.setting = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for selManBCEdit
uint32_t   get_selManBCEdit(void)
{                                                   
    return user_cfg_temporary.loc_manual_barcode_entry;
}                                                   
// Private Set - method for selManBCEdit
void   set_selManBCEdit(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.loc_manual_barcode_entry = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.loc_manual_barcode_entry = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for selManQTYEdit
uint32_t   get_selManQTYEdit(void)
{                                                   
    return user_cfg_temporary.loc_manual_quantity_entry;
}                                                   
// Private Set - method for selManQTYEdit
void   set_selManQTYEdit(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.loc_manual_quantity_entry = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.loc_manual_quantity_entry = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for selDelim
uint32_t   get_selDelim(void)
{                                                   
    return user_cfg_temporary.loc_delimiter.setting;
}                                                   
// Private Set - method for selDelim
void   set_selDelim(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.loc_delimiter.setting = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.loc_delimiter.setting = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for sinvManBCEdit
uint32_t   get_sinvManBCEdit(void)
{                                                   
    return user_cfg_temporary.invt_manual_barcode_entry;
}                                                   
// Private Set - method for sinvManBCEdit
void   set_sinvManBCEdit(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.invt_manual_barcode_entry = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.invt_manual_barcode_entry = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for sinvManQTYEdit
uint32_t   get_sinvManQTYEdit(void)
{                                                   
    return user_cfg_temporary.invt_manual_quantity_entry;
}                                                   
// Private Set - method for sinvManQTYEdit
void   set_sinvManQTYEdit(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.invt_manual_quantity_entry = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.invt_manual_quantity_entry = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for sinvDelim
uint32_t   get_sinvDelim(void)
{                                                   
    return user_cfg_temporary.invt_delimiter.setting;
}                                                   
// Private Set - method for sinvDelim
void   set_sinvDelim(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.invt_delimiter.setting = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.invt_delimiter.setting = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for sinvStore
uint32_t   get_sinvStore(void)
{                                                   
    return user_cfg_temporary.invt_store;
}                                                   
// Private Set - method for sinvStore
void   set_sinvStore(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.invt_store = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.invt_store = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// Private Get - method for gbDispOnCharge
uint32_t   get_gbDispOnCharge(void)
{                                                   
    return user_cfg_temporary.display_on_charge;
}                                                   
// Private Set - method for gbDispOnCharge
void   set_gbDispOnCharge(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.display_on_charge = setting;
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.display_on_charge = setting;
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update GuiConfigurationData  and Flash                       
         SetGuiConfigurationToFlash();                                   
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// -------------------------------------------    
// Methods for gblQtyXferMode
// callback method for gblQtyXferMode
void user_cfg_set_qty_transfer_mode(uint32_t value)   
{ 
   Attr_Query_t attrqtype = attr_unknown;            
   uint32_t     cvalue = 0;                          
   uint8_t      error = 0;                           
   attrqtype = GetAttributeQType(0x885);
   if ( attrqtype == attr_unknown || attrqtype == attr_string || attrqtype == attr_intdword )  
      error = 1;                                     
   if ( error == 0 )                                 
   {                                                 
      if ( attrqtype == attr_intbyte )                  
      {                                                 
         uint8_t pv = *(uint8_t *) value;               
         cvalue = (uint32_t)pv;                         
      }                                                 
      else if (attrqtype == attr_intword )              
      {                                                 
         uint16_t pv = *(uint16_t *) value;             
         cvalue = (uint32_t)pv;                         
      }                                                 
      GenericParamSetInt(0x885, cvalue, true); 
      gblQtyXferMode_cbsetstubfn( cvalue );
   }                                                 
}
 
void user_cfg_get_qty_transfer_mode(uint32_t* value)  
{ 
   *value = GenericParamGetInt(0x885 ); 
   gblQtyXferMode_cbgetstubfn( value );
}
// Private Get - method for gblQtyXferMode
uint32_t   get_gblQtyXferMode(void)
{                                                   
   return user_cfg_temporary.gblQtyXferMode;
}                                                   
// Get Stub Function for gblQtyXferMode
void gblQtyXferMode_cbgetstubfn(uint32_t * value)
{                                                   
}                                                   
// Set Stub Function for gblQtyXferMode
void gblQtyXferMode_cbsetstubfn(uint32_t value)
{                                                   
}                                                   
// Private Set - method for gblQtyXferMode
void   set_gblQtyXferMode(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.gblQtyXferMode = setting;               
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.gblQtyXferMode = setting;            
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update bucket structure and Flash                            
         update_config_object_new_param_int(0x885, setting); 
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// -------------------------------------------    
// Methods for sqtyDelim
// callback method for sqtyDelim
void user_cfg_set_qty_delimiter(uint32_t value)   
{ 
   Attr_Query_t attrqtype = attr_unknown;            
   uint32_t     cvalue = 0;                          
   uint8_t      error = 0;                           
   attrqtype = GetAttributeQType(0x886);
   if ( attrqtype == attr_unknown || attrqtype == attr_string || attrqtype == attr_intdword )  
      error = 1;                                     
   if ( error == 0 )                                 
   {                                                 
      if ( attrqtype == attr_intbyte )                  
      {                                                 
         uint8_t pv = *(uint8_t *) value;               
         cvalue = (uint32_t)pv;                         
      }                                                 
      else if (attrqtype == attr_intword )              
      {                                                 
         uint16_t pv = *(uint16_t *) value;             
         cvalue = (uint32_t)pv;                         
      }                                                 
      GenericParamSetInt(0x886, cvalue, true); 
      sqtyDelim_cbsetstubfn( cvalue );
   }                                                 
}
 
void user_cfg_get_qty_delimiter(uint32_t* value)  
{ 
   *value = GenericParamGetInt(0x886 ); 
   sqtyDelim_cbgetstubfn( value );
}
// Private Get - method for sqtyDelim
uint32_t   get_sqtyDelim(void)
{                                                   
   return user_cfg_temporary.sqtyDelim;
}                                                   
// Get Stub Function for sqtyDelim
void sqtyDelim_cbgetstubfn(uint32_t * value)
{                                                   
}                                                   
// Private Set - method for sqtyDelim
void   set_sqtyDelim(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.sqtyDelim = setting;               
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.sqtyDelim = setting;            
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update bucket structure and Flash                            
         update_config_object_new_param_int(0x886, setting); 
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// -------------------------------------------    
// Methods for slocDelim
// callback method for slocDelim
void user_cfg_set_loc_delimiter(uint32_t value)   
{ 
   Attr_Query_t attrqtype = attr_unknown;            
   uint32_t     cvalue = 0;                          
   uint8_t      error = 0;                           
   attrqtype = GetAttributeQType(0x887);
   if ( attrqtype == attr_unknown || attrqtype == attr_string || attrqtype == attr_intdword )  
      error = 1;                                     
   if ( error == 0 )                                 
   {                                                 
      if ( attrqtype == attr_intbyte )                  
      {                                                 
         uint8_t pv = *(uint8_t *) value;               
         cvalue = (uint32_t)pv;                         
      }                                                 
      else if (attrqtype == attr_intword )              
      {                                                 
         uint16_t pv = *(uint16_t *) value;             
         cvalue = (uint32_t)pv;                         
      }                                                 
      GenericParamSetInt(0x887, cvalue, true); 
      slocDelim_cbsetstubfn( cvalue );
   }                                                 
}
 
void user_cfg_get_loc_delimiter(uint32_t* value)  
{ 
   *value = GenericParamGetInt(0x887 ); 
   slocDelim_cbgetstubfn( value );
}
// Private Get - method for slocDelim
uint32_t   get_slocDelim(void)
{                                                   
   return user_cfg_temporary.slocDelim;
}                                                   
// Get Stub Function for slocDelim
void slocDelim_cbgetstubfn(uint32_t * value)
{                                                   
}                                                   
// Private Set - method for slocDelim
void   set_slocDelim(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.slocDelim = setting;               
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.slocDelim = setting;            
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update bucket structure and Flash                            
         update_config_object_new_param_int(0x887, setting); 
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// -------------------------------------------    
// Methods for sqtyqtyDelim
// callback method for sqtyqtyDelim
void user_cfg_set_qty_qty_delimiter(uint32_t value)   
{ 
   Attr_Query_t attrqtype = attr_unknown;            
   uint32_t     cvalue = 0;                          
   uint8_t      error = 0;                           
   attrqtype = GetAttributeQType(0x888);
   if ( attrqtype == attr_unknown || attrqtype == attr_string || attrqtype == attr_intdword )  
      error = 1;                                     
   if ( error == 0 )                                 
   {                                                 
      if ( attrqtype == attr_intbyte )                  
      {                                                 
         uint8_t pv = *(uint8_t *) value;               
         cvalue = (uint32_t)pv;                         
      }                                                 
      else if (attrqtype == attr_intword )              
      {                                                 
         uint16_t pv = *(uint16_t *) value;             
         cvalue = (uint32_t)pv;                         
      }                                                 
      GenericParamSetInt(0x888, cvalue, true); 
      sqtyqtyDelim_cbsetstubfn( cvalue );
   }                                                 
}
 
void user_cfg_get_qty_qty_delimiter(uint32_t* value)  
{ 
   *value = GenericParamGetInt(0x888 ); 
   sqtyqtyDelim_cbgetstubfn( value );
}
// Private Get - method for sqtyqtyDelim
uint32_t   get_sqtyqtyDelim(void)
{                                                   
   return user_cfg_temporary.sqtyqtyDelim;
}                                                   
// Get Stub Function for sqtyqtyDelim
void sqtyqtyDelim_cbgetstubfn(uint32_t * value)
{                                                   
}                                                   
// Set Stub Function for sqtyqtyDelim
void sqtyqtyDelim_cbsetstubfn(uint32_t value)
{                                                   
}                                                   
// Private Set - method for sqtyqtyDelim
void   set_sqtyqtyDelim(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.sqtyqtyDelim = setting;               
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.sqtyqtyDelim = setting;            
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update bucket structure and Flash                            
         update_config_object_new_param_int(0x888, setting); 
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// -------------------------------------------    
// Methods for slocqtyDelim
// callback method for slocqtyDelim
void user_cfg_set_loc_qty_delimiter(uint32_t value)   
{ 
   Attr_Query_t attrqtype = attr_unknown;            
   uint32_t     cvalue = 0;                          
   uint8_t      error = 0;                           
   attrqtype = GetAttributeQType(0x889);
   if ( attrqtype == attr_unknown || attrqtype == attr_string || attrqtype == attr_intdword )  
      error = 1;                                     
   if ( error == 0 )                                 
   {                                                 
      if ( attrqtype == attr_intbyte )                  
      {                                                 
         uint8_t pv = *(uint8_t *) value;               
         cvalue = (uint32_t)pv;                         
      }                                                 
      else if (attrqtype == attr_intword )              
      {                                                 
         uint16_t pv = *(uint16_t *) value;             
         cvalue = (uint32_t)pv;                         
      }                                                 
      GenericParamSetInt(0x889, cvalue, true); 
      slocqtyDelim_cbsetstubfn( cvalue );
   }                                                 
}
 
void user_cfg_get_loc_qty_delimiter(uint32_t* value)  
{ 
   *value = GenericParamGetInt(0x889 ); 
   slocqtyDelim_cbgetstubfn( value );
}
// Private Get - method for slocqtyDelim
uint32_t   get_slocqtyDelim(void)
{                                                   
   return user_cfg_temporary.slocqtyDelim;
}                                                   
// Get Stub Function for slocqtyDelim
void slocqtyDelim_cbgetstubfn(uint32_t * value)
{                                                   
}                                                   
// Set Stub Function for slocqtyDelim
void slocqtyDelim_cbsetstubfn(uint32_t value)
{                                                   
}                                                   
// Private Set - method for slocqtyDelim
void   set_slocqtyDelim(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.slocqtyDelim = setting;               
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.slocqtyDelim = setting;            
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update bucket structure and Flash                            
         update_config_object_new_param_int(0x889, setting); 
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// -------------------------------------------    
// Methods for sinvtqtyDelim
// callback method for sinvtqtyDelim
void user_cfg_set_invt_qty_delimiter(uint32_t value)   
{ 
   Attr_Query_t attrqtype = attr_unknown;            
   uint32_t     cvalue = 0;                          
   uint8_t      error = 0;                           
   attrqtype = GetAttributeQType(0x88A);
   if ( attrqtype == attr_unknown || attrqtype == attr_string || attrqtype == attr_intdword )  
      error = 1;                                     
   if ( error == 0 )                                 
   {                                                 
      if ( attrqtype == attr_intbyte )                  
      {                                                 
         uint8_t pv = *(uint8_t *) value;               
         cvalue = (uint32_t)pv;                         
      }                                                 
      else if (attrqtype == attr_intword )              
      {                                                 
         uint16_t pv = *(uint16_t *) value;             
         cvalue = (uint32_t)pv;                         
      }                                                 
      GenericParamSetInt(0x88A, cvalue, true); 
      sinvtqtyDelim_cbsetstubfn( cvalue );
   }                                                 
}
 
void user_cfg_get_invt_qty_delimiter(uint32_t* value)  
{ 
   *value = GenericParamGetInt(0x88A ); 
   sinvtqtyDelim_cbgetstubfn( value );
}
// Private Get - method for sinvtqtyDelim
uint32_t   get_sinvtqtyDelim(void)
{                                                   
   return user_cfg_temporary.sinvtqtyDelim;
}                                                   
// Get Stub Function for sinvtqtyDelim
void sinvtqtyDelim_cbgetstubfn(uint32_t * value)
{                                                   
}                                                   
// Set Stub Function for sinvtqtyDelim
void sinvtqtyDelim_cbsetstubfn(uint32_t value)
{                                                   
}                                                   
// Private Set - method for sinvtqtyDelim
void   set_sinvtqtyDelim(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.sinvtqtyDelim = setting;               
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.sinvtqtyDelim = setting;            
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update bucket structure and Flash                            
         update_config_object_new_param_int(0x88A, setting); 
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// -------------------------------------------    
// Methods for sqtyToutConf
// callback method for sqtyToutConf
void confirm_qty_set_timeout(uint32_t value)   
{ 
   Attr_Query_t attrqtype = attr_unknown;            
   uint32_t     cvalue = 0;                          
   uint8_t      error = 0;                           
   attrqtype = GetAttributeQType(0x88B);
   if ( attrqtype == attr_unknown || attrqtype == attr_string || attrqtype == attr_intdword )  
      error = 1;                                     
   if ( error == 0 )                                 
   {                                                 
      if ( attrqtype == attr_intbyte )                  
      {                                                 
         uint8_t pv = *(uint8_t *) value;               
         cvalue = (uint32_t)pv;                         
      }                                                 
      else if (attrqtype == attr_intword )              
      {                                                 
         uint16_t pv = *(uint16_t *) value;             
         cvalue = (uint32_t)pv;                         
      }                                                 
      GenericParamSetInt(0x88B, cvalue, true); 
      sqtyToutConf_cbsetstubfn( cvalue );
   }                                                 
}
 
void confirm_qty_get_timeout(uint32_t* value)  
{ 
   *value = GenericParamGetInt(0x88B ); 
   sqtyToutConf_cbgetstubfn( value );
}
// Private Get - method for sqtyToutConf
uint32_t   get_sqtyToutConf(void)
{                                                   
   return user_cfg_temporary.sqtyToutConf;
}                                                   
// Get Stub Function for sqtyToutConf
void sqtyToutConf_cbgetstubfn(uint32_t * value)
{                                                   
}                                                   
// Set Stub Function for sqtyToutConf
void sqtyToutConf_cbsetstubfn(uint32_t value)
{                                                   
}                                                   
// Private Set - method for sqtyToutConf
void   set_sqtyToutConf(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.sqtyToutConf = setting;               
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.sqtyToutConf = setting;            
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update bucket structure and Flash                            
         update_config_object_new_param_int(0x88B, setting); 
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// -------------------------------------------    
// Methods for conflocTout
// callback method for conflocTout
void confirm_loc_set_timeout(uint32_t value)   
{ 
   Attr_Query_t attrqtype = attr_unknown;            
   uint32_t     cvalue = 0;                          
   uint8_t      error = 0;                           
   attrqtype = GetAttributeQType(0x88C);
   if ( attrqtype == attr_unknown || attrqtype == attr_string || attrqtype == attr_intdword )  
      error = 1;                                     
   if ( error == 0 )                                 
   {                                                 
      if ( attrqtype == attr_intbyte )                  
      {                                                 
         uint8_t pv = *(uint8_t *) value;               
         cvalue = (uint32_t)pv;                         
      }                                                 
      else if (attrqtype == attr_intword )              
      {                                                 
         uint16_t pv = *(uint16_t *) value;             
         cvalue = (uint32_t)pv;                         
      }                                                 
      GenericParamSetInt(0x88C, cvalue, true); 
      conflocTout_cbsetstubfn( cvalue );
   }                                                 
}
 
void confirm_loc_get_timeout(uint32_t* value)  
{ 
   *value = GenericParamGetInt(0x88C ); 
   conflocTout_cbgetstubfn( value );
}
// Private Get - method for conflocTout
uint32_t   get_conflocTout(void)
{                                                   
   return user_cfg_temporary.conflocTout;
}                                                   
// Get Stub Function for conflocTout
void conflocTout_cbgetstubfn(uint32_t * value)
{                                                   
}                                                   
// Set Stub Function for conflocTout
void conflocTout_cbsetstubfn(uint32_t value)
{                                                   
}                                                   
// Private Set - method for conflocTout
void   set_conflocTout(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.conflocTout = setting;               
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.conflocTout = setting;            
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update bucket structure and Flash                            
         update_config_object_new_param_int(0x88C, setting); 
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// -------------------------------------------    
// Methods for gblMinQtyValue
// callback method for gblMinQtyValue
void user_cfg_set_qty_min_value(uint32_t value)   
{ 
   Attr_Query_t attrqtype = attr_unknown;            
   uint32_t     cvalue = 0;                          
   uint8_t      error = 0;                           
   attrqtype = GetAttributeQType(0x88D);
   if ( attrqtype == attr_unknown || attrqtype == attr_string || attrqtype == attr_intdword )  
      error = 1;                                     
   if ( error == 0 )                                 
   {                                                 
      if ( attrqtype == attr_intbyte )                  
      {                                                 
         uint8_t pv = *(uint8_t *) value;               
         cvalue = (uint32_t)pv;                         
      }                                                 
      else if (attrqtype == attr_intword )              
      {                                                 
         uint16_t pv = *(uint16_t *) value;             
         cvalue = (uint32_t)pv;                         
      }                                                 
      GenericParamSetInt(0x88D, cvalue, true); 
      gblMinQtyValue_cbsetstubfn( cvalue );
   }                                                 
}
 
void user_cfg_get_qty_min_value(uint32_t* value)  
{ 
   *value = GenericParamGetInt(0x88D ); 
   gblMinQtyValue_cbgetstubfn( value );
}
// Private Get - method for gblMinQtyValue
uint32_t   get_gblMinQtyValue(void)
{                                                   
   return user_cfg_temporary.gblMinQtyValue;
}                                                   
// Get Stub Function for gblMinQtyValue
void gblMinQtyValue_cbgetstubfn(uint32_t * value)
{                                                   
}                                                   
// Private Set - method for gblMinQtyValue
void   set_gblMinQtyValue(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.gblMinQtyValue = setting;               
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.gblMinQtyValue = setting;            
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update bucket structure and Flash                            
         update_config_object_new_param_int(0x88D, setting); 
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// -------------------------------------------    
// Methods for gblMaxQtyValue
// callback method for gblMaxQtyValue
void user_cfg_set_qty_max_value(uint32_t value)   
{ 
   Attr_Query_t attrqtype = attr_unknown;            
   uint32_t     cvalue = 0;                          
   uint8_t      error = 0;                           
   attrqtype = GetAttributeQType(0x88E);
   if ( attrqtype == attr_unknown || attrqtype == attr_string || attrqtype == attr_intdword )  
      error = 1;                                     
   if ( error == 0 )                                 
   {                                                 
      if ( attrqtype == attr_intbyte )                  
      {                                                 
         uint8_t pv = *(uint8_t *) value;               
         cvalue = (uint32_t)pv;                         
      }                                                 
      else if (attrqtype == attr_intword )              
      {                                                 
         uint16_t pv = *(uint16_t *) value;             
         cvalue = (uint32_t)pv;                         
      }                                                 
      GenericParamSetInt(0x88E, cvalue, true); 
      gblMaxQtyValue_cbsetstubfn( cvalue );
   }                                                 
}
 
void user_cfg_get_qty_max_value(uint32_t* value)  
{ 
   *value = GenericParamGetInt(0x88E ); 
   gblMaxQtyValue_cbgetstubfn( value );
}
// Private Get - method for gblMaxQtyValue
uint32_t   get_gblMaxQtyValue(void)
{                                                   
   return user_cfg_temporary.gblMaxQtyValue;
}                                                   
// Get Stub Function for gblMaxQtyValue
void gblMaxQtyValue_cbgetstubfn(uint32_t * value)
{                                                   
}                                                   
// Private Set - method for gblMaxQtyValue
void   set_gblMaxQtyValue(uint32_t setting, bool permanent)
{                                                                     
   user_cfg_temporary.gblMaxQtyValue = setting;               
   if ( permanent )                                                   
   {                                                                  
      user_cfg_permanent.gblMaxQtyValue = setting;            
      if (!GetFlashConfigurationToGUIFlag)                            
      {                                                               
         // update bucket structure and Flash                            
         update_config_object_new_param_int(0x88E, setting); 
      }                                                                  
   }                                                                  
}
// ---------------------------------------------
// returns true - Success                                        
// returns false - Error
bool GenericParamSetInt(uint16_t attributeNumber, uint32_t value, bool permanent)
{                                                                
   bool retval = false;                                          
   switch(attributeNumber)  
   {                        
      case 0x860:  // "Display Timeout"
         if (  value > 18) 
            break;                                               
         if ( false == true )  // editflag == true check 
         {                                                                              
            set_gblDispTout( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 3:
               case 6:
               case 12:
               case 18:
               case 0:
                  set_gblDispTout( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x86A:  // "Manual Barcode Entry"
         if (  value > 1) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_gblManBCEntry( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
                  set_gblManBCEntry( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x86B:  // "Manual Quantity Entry"
         if (  value > 1) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_gblManQtyEntry( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
                  set_gblManQtyEntry( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x86C:  // "Auto Display Brightness"
         if ( value < 1 || value > 6) 
            break;                                               
         if ( false == true )  // editflag == true check 
         {                                                                              
            set_gblAutoDispBrt( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 1:
               case 2:
               case 3:
               case 4:
               case 5:
               case 6:
                  set_gblAutoDispBrt( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x86D:  // "Keypad Backlight"
         if (  value > 3) 
            break;                                               
         if ( false == true )  // editflag == true check 
         {                                                                              
            set_gblKeypadBacklight( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
               case 2:
                  set_gblKeypadBacklight( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x86E:  // "Home Key Launch"
         if (  value > 6) 
            break;                                               
         if ( false == true )  // editflag == true check 
         {                                                                              
            set_gblHomeKey( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
               case 2:
               case 3:
               case 4:
               case 5:
               case 6:
                  set_gblHomeKey( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x86F:  // "Manual BC Entry"
         if (  value > 1) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_seqManBCEdit( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
                  set_seqManBCEdit( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x870:  // "Manual QTY Entry"
         if (  value > 1) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_seqManQTYEdit( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
                  set_seqManQTYEdit( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x871:  // "Quantity Timeout"
         if (  value > 60) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_seqTout( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 3:
               case 6:
               case 9:
               case 18:
               case 30:
               case 60:
               case 0:
                  set_seqTout( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x872:  // "Manual BC Entry loc"
         if (  value > 1) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_selManBCEdit( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
                  set_selManBCEdit( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x873:  // "Manual QTY Entry loc"
         if (  value > 1) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_selManQTYEdit( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
                  set_selManQTYEdit( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x874:  // "Delimiter loc"
         if (  value > 127) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_selDelim( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 13:
               case 10:
               case 32:
               case 9:
               case 44:
               case 58:
               case 59:
               case 61:
                  set_selDelim( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x875:  // "Manual BC Entry invt"
         if (  value > 1) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_sinvManBCEdit( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
                  set_sinvManBCEdit( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x876:  // "Manual QTY Entry invt"
         if (  value > 1) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_sinvManQTYEdit( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
                  set_sinvManQTYEdit( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x877:  // "INVT LOC Delimiter"
         if (  value > 127) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_sinvDelim( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 13:
               case 10:
               case 32:
               case 9:
               case 44:
               case 58:
               case 59:
               case 61:
                  set_sinvDelim( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x878:  // "Inventory Store"
         if (  value > 1) 
            break;                                               
         if ( false == true )  // editflag == true check 
         {                                                                              
            set_sinvStore( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
                  set_sinvStore( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x87A:  // "Display On Charge"
         if ( value < 1 || value > 3) 
            break;                                               
         if ( false == true )  // editflag == true check 
         {                                                                              
            set_gbDispOnCharge( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 1:
               case 2:
               case 3:
                  set_gbDispOnCharge( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x885:  // "QTY Transfer Mode"
         if ( value < 1 || value > 2) 
            break;                                               
         if ( false == true )  // editflag == true check 
         {                                                                              
            set_gblQtyXferMode( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 1:
               case 2:
                  set_gblQtyXferMode( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x886:  // "QTY Delimiter"
         if (  value > 127) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_sqtyDelim( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 13:
               case 10:
               case 32:
               case 9:
               case 44:
               case 58:
               case 59:
               case 61:
                  set_sqtyDelim( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x887:  // "Loc Delimiter"
         if (  value > 127) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_slocDelim( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 13:
               case 10:
               case 32:
               case 9:
               case 44:
               case 58:
               case 59:
               case 61:
                  set_slocDelim( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x888:  // "QTY QTY Delimiter"
         if (  value > 127) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_sqtyqtyDelim( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 13:
               case 10:
               case 32:
               case 9:
               case 44:
               case 58:
               case 59:
               case 61:
                  set_sqtyqtyDelim( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x889:  // "LOC QTY Delimiter"
         if (  value > 127) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_slocqtyDelim( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 13:
               case 10:
               case 32:
               case 9:
               case 44:
               case 58:
               case 59:
               case 61:
                  set_slocqtyDelim( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x88A:  // "INVT QTY Delimiter"
         if (  value > 127) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_sinvtqtyDelim( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 13:
               case 10:
               case 32:
               case 9:
               case 44:
               case 58:
               case 59:
               case 61:
                  set_sinvtqtyDelim( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x88B:  // "Confirm QTY Tmout"
         if (  value > 6) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_sqtyToutConf( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
               case 2:
               case 5:
                  set_sqtyToutConf( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x88C:  // "Confirm LOC Tmout"
         if (  value > 6) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_conflocTout( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 0:
               case 1:
               case 2:
               case 5:
                  set_conflocTout( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x88D:  // "Min Qty Value"
         if (  value > 9999) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_gblMinQtyValue( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 1:
                  set_gblMinQtyValue( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
      case 0x88E:  // "Max Qty Value"
         if ( value < 1 || value > 9999) 
            break;                                               
         if ( true == true )  // editflag == true check 
         {                                                                              
            set_gblMaxQtyValue( value, permanent );
            retval = true;                                                              
         }                                                                              
         else                                                    
         {                                                       
            switch(value)                                     
            {                                                 
               case 9999:
                  set_gblMaxQtyValue( value, permanent );
                  retval = true;                           
                  break;                                   
                                                         
               default:                                    
                  break; // error  
            } // switch                                 
         }  // else                                     
         break;                                         
   }                                                         
   return retval;                                            
}                                                            
// returns true - Success                                        
// returns false - Error
bool GenericParamSetString(uint16_t attributeNumber, char * str, bool permanent)
{                                                                
   bool       retval = false;                                    
   uint16_t   strmaxlen = 0;                                     
   switch(attributeNumber)  
   {                        
   }                                                         
   return retval;                                            
}                                                            
// -----------------------------------                           
uint32_t GenericParamGetInt(uint16_t attributeNumber )
{                           
   switch(attributeNumber)  
   {                        
      case 0x860:  // "Display Timeout"
           return get_gblDispTout();
      case 0x86A:  // "Manual Barcode Entry"
           return get_gblManBCEntry();
      case 0x86B:  // "Manual Quantity Entry"
           return get_gblManQtyEntry();
      case 0x86C:  // "Auto Display Brightness"
           return get_gblAutoDispBrt();
      case 0x86D:  // "Keypad Backlight"
           return get_gblKeypadBacklight();
      case 0x86E:  // "Home Key Launch"
           return get_gblHomeKey();
      case 0x86F:  // "Manual BC Entry"
           return get_seqManBCEdit();
      case 0x870:  // "Manual QTY Entry"
           return get_seqManQTYEdit();
      case 0x871:  // "Quantity Timeout"
           return get_seqTout();
      case 0x872:  // "Manual BC Entry loc"
           return get_selManBCEdit();
      case 0x873:  // "Manual QTY Entry loc"
           return get_selManQTYEdit();
      case 0x874:  // "Delimiter loc"
           return get_selDelim();
      case 0x875:  // "Manual BC Entry invt"
           return get_sinvManBCEdit();
      case 0x876:  // "Manual QTY Entry invt"
           return get_sinvManQTYEdit();
      case 0x877:  // "INVT LOC Delimiter"
           return get_sinvDelim();
      case 0x878:  // "Inventory Store"
           return get_sinvStore();
      case 0x87A:  // "Display On Charge"
           return get_gbDispOnCharge();
      case 0x885:  // "QTY Transfer Mode"
           return get_gblQtyXferMode();
      case 0x886:  // "QTY Delimiter"
           return get_sqtyDelim();
      case 0x887:  // "Loc Delimiter"
           return get_slocDelim();
      case 0x888:  // "QTY QTY Delimiter"
           return get_sqtyqtyDelim();
      case 0x889:  // "LOC QTY Delimiter"
           return get_slocqtyDelim();
      case 0x88A:  // "INVT QTY Delimiter"
           return get_sinvtqtyDelim();
      case 0x88B:  // "Confirm QTY Tmout"
           return get_sqtyToutConf();
      case 0x88C:  // "Confirm LOC Tmout"
           return get_conflocTout();
      case 0x88D:  // "Min Qty Value"
           return get_gblMinQtyValue();
      case 0x88E:  // "Max Qty Value"
           return get_gblMaxQtyValue();
   }                                                         
   // should not get here                                    
   return 999;  // error return                              
}                                                            
// -----------------------------------                           
// returns false on error                                        
bool GenericParamGetString(uint16_t attributeNumber, uint32_t * value )
{                                                                
   bool     retval = false;                                      
   switch(attributeNumber)  
   {                        
   }                                                         
   return retval;                                            
}                                                            
Attr_Query_t GetAttributeQType(uint16_t attributeNumber)         
{                                                                
   Attr_Query_t retval = attr_unknown;                                          
   switch(attributeNumber)  
   {                        
      case 0x860:  // "Display Timeout"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x86A:  // "Manual Barcode Entry"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x86B:  // "Manual Quantity Entry"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x86C:  // "Auto Display Brightness"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x86D:  // "Keypad Backlight"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x86E:  // "Home Key Launch"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x86F:  // "Manual BC Entry"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x870:  // "Manual QTY Entry"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x871:  // "Quantity Timeout"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x872:  // "Manual BC Entry loc"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x873:  // "Manual QTY Entry loc"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x874:  // "Delimiter loc"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x875:  // "Manual BC Entry invt"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x876:  // "Manual QTY Entry invt"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x877:  // "INVT LOC Delimiter"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x878:  // "Inventory Store"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x87A:  // "Display On Charge"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x885:  // "QTY Transfer Mode"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x886:  // "QTY Delimiter"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x887:  // "Loc Delimiter"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x888:  // "QTY QTY Delimiter"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x889:  // "LOC QTY Delimiter"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x88A:  // "INVT QTY Delimiter"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x88B:  // "Confirm QTY Tmout"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x88C:  // "Confirm LOC Tmout"
         retval = attr_intbyte;                                         
         break;                                                           
      case 0x88D:  // "Min Qty Value"
         retval = attr_intword;                                         
         break;                                                           
      case 0x88E:  // "Max Qty Value"
         retval = attr_intword;                                         
         break;                                                           
   }                                                         
   return retval;                                            
}                                                            
uint16_t  GetBucketIndex(uint16_t attributeNumber )                         
{                                                                           
   uint16_t retval = 0xFF;                                                  
                                                                            
   switch(attributeNumber)                                                  
   {                                                                        
      case 0x885: // "QTY Transfer Mode" PARAM_TYPE_NUMERIC ps_byte
         retval = 0;
         break; 
      case 0x886: // "QTY Delimiter" PARAM_TYPE_NUMERIC ps_byte
         retval = 1;
         break; 
      case 0x887: // "Loc Delimiter" PARAM_TYPE_NUMERIC ps_byte
         retval = 2;
         break; 
      case 0x888: // "QTY QTY Delimiter" PARAM_TYPE_NUMERIC ps_byte
         retval = 5;
         break; 
      case 0x889: // "LOC QTY Delimiter" PARAM_TYPE_NUMERIC ps_byte
         retval = 3;
         break; 
      case 0x88A: // "INVT QTY Delimiter" PARAM_TYPE_NUMERIC ps_byte
         retval = 7;
         break; 
      case 0x88B: // "Confirm QTY Tmout" PARAM_TYPE_NUMERIC ps_byte
         retval = 6;
         break; 
      case 0x88C: // "Confirm LOC Tmout" PARAM_TYPE_NUMERIC ps_byte
         retval = 4;
         break; 
      case 0x88D: // "Min Qty Value" PARAM_TYPE_NUMERIC ps_word
         retval = 0;
         break; 
      case 0x88E: // "Max Qty Value" PARAM_TYPE_NUMERIC ps_word
         retval = 1;
         break; 
   }                                                                          
   return retval;                                                             
}                                                                             
   // Takes a name and returns the attribute Number              
   // Returns 0 on error                                         
   //                                                            
uint16_t GenericGetAttributeByName(char * attrname)              
{                                                                
   uint16_t retval = 0;                                          
   uint32_t attrscode = 0;                                       
                                                                 
   attrscode = GetSCode( attrname );                             
   switch(attrscode)                                             
   {                                                             
      case 1501:// "Display Timeout"
         retval = 0x860;
         break; 
      case 741:// "F1_radio"
         retval = 0x861;
         break; 
      case 742:// "F2_radio"
         retval = 0x862;
         break; 
      case 743:// "F3_radio"
         retval = 0x863;
         break; 
      case 744:// "F4_radio"
         retval = 0x864;
         break; 
      case 745:// "F5_radio"
         retval = 0x865;
         break; 
      case 746:// "F6_radio"
         retval = 0x866;
         break; 
      case 747:// "F7_radio"
         retval = 0x867;
         break; 
      case 748:// "F8_radio"
         retval = 0x868;
         break; 
      case 749:// "F9_radio"
         retval = 0x869;
         break; 
      case 1888:// "Manual Barcode Entry"
         retval = 0x86A;
         break; 
      case 2063:// "Manual Quantity Entry"
         retval = 0x86B;
         break; 
      case 2248:// "Auto Display Brightness"
         retval = 0x86C;
         break; 
      case 1543:// "Keypad Backlight"
         retval = 0x86D;
         break; 
      case 1357:// "Home Key Launch"
         retval = 0x86E;
         break; 
      case 1333:// "Manual BC Entry"
         retval = 0x86F;
         break; 
      case 1454:// "Manual QTY Entry"
         retval = 0x870;
         break; 
      case 1638:// "Quantity Timeout"
         retval = 0x871;
         break; 
      case 1683:// "Manual BC Entry loc"
         retval = 0x872;
         break; 
      case 1804:// "Manual QTY Entry loc"
         retval = 0x873;
         break; 
      case 1277:// "Delimiter loc"
         retval = 0x874;
         break; 
      case 1814:// "Manual BC Entry invt"
         retval = 0x875;
         break; 
      case 1935:// "Manual QTY Entry invt"
         retval = 0x876;
         break; 
      case 1534:// "INVT LOC Delimiter"
         retval = 0x877;
         break; 
      case 1531:// "Inventory Store"
         retval = 0x878;
         break; 
      case 1565:// "Display On Charge"
         retval = 0x87A;
         break; 
      case 119:// "F1"
         retval = 0x87B;
         break; 
      case 120:// "F2"
         retval = 0x87C;
         break; 
      case 121:// "F3"
         retval = 0x87D;
         break; 
      case 122:// "F4"
         retval = 0x87E;
         break; 
      case 123:// "F5"
         retval = 0x87F;
         break; 
      case 124:// "F6"
         retval = 0x880;
         break; 
      case 125:// "F7"
         retval = 0x881;
         break; 
      case 126:// "F8"
         retval = 0x882;
         break; 
      case 127:// "F9"
         retval = 0x883;
         break; 
      case 1544:// "QTY Transfer Mode"
         retval = 0x885;
         break; 
      case 1213:// "QTY Delimiter"
         retval = 0x886;
         break; 
      case 1245:// "Loc Delimiter"
         retval = 0x887;
         break; 
      case 1499:// "QTY QTY Delimiter"
         retval = 0x888;
         break; 
      case 1467:// "LOC QTY Delimiter"
         retval = 0x889;
         break; 
      case 1566:// "INVT QTY Delimiter"
         retval = 0x88A;
         break; 
      case 1573:// "Confirm QTY Tmout"
         retval = 0x88B;
         break; 
      case 1541:// "Confirm LOC Tmout"
         retval = 0x88C;
         break; 
      case 1183:// "Min Qty Value"
         retval = 0x88D;
         break; 
      case 1185:// "Max Qty Value"
         retval = 0x88E;
         break; 
      default: 
         break;                                                                 
   }                                                                          
   return retval;                                                             
}                                                                             
   // Takes a Attribute and returns the Max Len                  
   // Returns 0 on error                                         
   //                                                            
uint16_t GenericGetAttributeMaxLen(uint16_t attributeNumber)     
{                                                                
   uint16_t retval = 0;                                          
                                                                 
   switch(attributeNumber)                                       
   {                                                             
      case 0x860: // "Display Timeout" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x861: // "F1_radio" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x862: // "F2_radio" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x863: // "F3_radio" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x864: // "F4_radio" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x865: // "F5_radio" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x866: // "F6_radio" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x867: // "F7_radio" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x868: // "F8_radio" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x869: // "F9_radio" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x86A: // "Manual Barcode Entry" PARAM_TYPE_BOOL
         retval = 1;
         break; 
      case 0x86B: // "Manual Quantity Entry" PARAM_TYPE_BOOL
         retval = 1;
         break; 
      case 0x86C: // "Auto Display Brightness" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x86D: // "Keypad Backlight" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x86E: // "Home Key Launch" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x86F: // "Manual BC Entry" PARAM_TYPE_BOOL
         retval = 1;
         break; 
      case 0x870: // "Manual QTY Entry" PARAM_TYPE_BOOL
         retval = 1;
         break; 
      case 0x871: // "Quantity Timeout" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x872: // "Manual BC Entry loc" PARAM_TYPE_BOOL
         retval = 1;
         break; 
      case 0x873: // "Manual QTY Entry loc" PARAM_TYPE_BOOL
         retval = 1;
         break; 
      case 0x874: // "Delimiter loc" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x875: // "Manual BC Entry invt" PARAM_TYPE_BOOL
         retval = 1;
         break; 
      case 0x876: // "Manual QTY Entry invt" PARAM_TYPE_BOOL
         retval = 1;
         break; 
      case 0x877: // "INVT LOC Delimiter" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x878: // "Inventory Store" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x87A: // "Display On Charge" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x87B: // "F1" PARAM_TYPE_STRING
         retval = 15;
         if ( retval > USER_STR_MAX_SIZE )
         {                                      
            printf("\r\nInternal Error: max size for attr:0x87B reduced to 20 from %d", retval);
            retval = USER_STR_MAX_SIZE;      
         }     
         break; 
      case 0x87C: // "F2" PARAM_TYPE_STRING
         retval = 15;
         if ( retval > USER_STR_MAX_SIZE )
         {                                      
            printf("\r\nInternal Error: max size for attr:0x87C reduced to 20 from %d", retval);
            retval = USER_STR_MAX_SIZE;      
         }     
         break; 
      case 0x87D: // "F3" PARAM_TYPE_STRING
         retval = 15;
         if ( retval > USER_STR_MAX_SIZE )
         {                                      
            printf("\r\nInternal Error: max size for attr:0x87D reduced to 20 from %d", retval);
            retval = USER_STR_MAX_SIZE;      
         }     
         break; 
      case 0x87E: // "F4" PARAM_TYPE_STRING
         retval = 15;
         if ( retval > USER_STR_MAX_SIZE )
         {                                      
            printf("\r\nInternal Error: max size for attr:0x87E reduced to 20 from %d", retval);
            retval = USER_STR_MAX_SIZE;      
         }     
         break; 
      case 0x87F: // "F5" PARAM_TYPE_STRING
         retval = 15;
         if ( retval > USER_STR_MAX_SIZE )
         {                                      
            printf("\r\nInternal Error: max size for attr:0x87F reduced to 20 from %d", retval);
            retval = USER_STR_MAX_SIZE;      
         }     
         break; 
      case 0x880: // "F6" PARAM_TYPE_STRING
         retval = 15;
         if ( retval > USER_STR_MAX_SIZE )
         {                                      
            printf("\r\nInternal Error: max size for attr:0x880 reduced to 20 from %d", retval);
            retval = USER_STR_MAX_SIZE;      
         }     
         break; 
      case 0x881: // "F7" PARAM_TYPE_STRING
         retval = 15;
         if ( retval > USER_STR_MAX_SIZE )
         {                                      
            printf("\r\nInternal Error: max size for attr:0x881 reduced to 20 from %d", retval);
            retval = USER_STR_MAX_SIZE;      
         }     
         break; 
      case 0x882: // "F8" PARAM_TYPE_STRING
         retval = 15;
         if ( retval > USER_STR_MAX_SIZE )
         {                                      
            printf("\r\nInternal Error: max size for attr:0x882 reduced to 20 from %d", retval);
            retval = USER_STR_MAX_SIZE;      
         }     
         break; 
      case 0x883: // "F9" PARAM_TYPE_STRING
         retval = 15;
         if ( retval > USER_STR_MAX_SIZE )
         {                                      
            printf("\r\nInternal Error: max size for attr:0x883 reduced to 20 from %d", retval);
            retval = USER_STR_MAX_SIZE;      
         }     
         break; 
      case 0x884: // "KeyboardInject" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x885: // "QTY Transfer Mode" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x886: // "QTY Delimiter" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x887: // "Loc Delimiter" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x888: // "QTY QTY Delimiter" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x889: // "LOC QTY Delimiter" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x88A: // "INVT QTY Delimiter" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x88B: // "Confirm QTY Tmout" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x88C: // "Confirm LOC Tmout" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x88D: // "Min Qty Value" PARAM_TYPE_NUMERIC
         retval = 2;
         break; 
      case 0x88E: // "Max Qty Value" PARAM_TYPE_NUMERIC
         retval = 2;
         break; 
   } // switch  
   return retval;                          
} 
uint16_t  GetCanopyIndexFromAttrNum(uint16_t attributeNumber, uint8_t *error )  
{                                                                           
   uint16_t retval = 0;                                                     
   *error = 0;                                                              
                                                                            
   switch(attributeNumber)                                                  
   {                                                                        
      case 0x860: // "Display Timeout" PARAM_TYPE_NUMERIC
         retval = 0;
         break; 
      case 0x861: // "F1_radio" PARAM_TYPE_NUMERIC
         retval = 1;
         break; 
      case 0x862: // "F2_radio" PARAM_TYPE_NUMERIC
         retval = 2;
         break; 
      case 0x863: // "F3_radio" PARAM_TYPE_NUMERIC
         retval = 3;
         break; 
      case 0x864: // "F4_radio" PARAM_TYPE_NUMERIC
         retval = 4;
         break; 
      case 0x865: // "F5_radio" PARAM_TYPE_NUMERIC
         retval = 5;
         break; 
      case 0x866: // "F6_radio" PARAM_TYPE_NUMERIC
         retval = 6;
         break; 
      case 0x867: // "F7_radio" PARAM_TYPE_NUMERIC
         retval = 7;
         break; 
      case 0x868: // "F8_radio" PARAM_TYPE_NUMERIC
         retval = 8;
         break; 
      case 0x869: // "F9_radio" PARAM_TYPE_NUMERIC
         retval = 9;
         break; 
      case 0x86A: // "Manual Barcode Entry" PARAM_TYPE_BOOL
         retval = 10;
         break; 
      case 0x86B: // "Manual Quantity Entry" PARAM_TYPE_BOOL
         retval = 11;
         break; 
      case 0x86C: // "Auto Display Brightness" PARAM_TYPE_NUMERIC
         retval = 12;
         break; 
      case 0x86D: // "Keypad Backlight" PARAM_TYPE_NUMERIC
         retval = 13;
         break; 
      case 0x86E: // "Home Key Launch" PARAM_TYPE_NUMERIC
         retval = 14;
         break; 
      case 0x86F: // "Manual BC Entry" PARAM_TYPE_BOOL
         retval = 15;
         break; 
      case 0x870: // "Manual QTY Entry" PARAM_TYPE_BOOL
         retval = 16;
         break; 
      case 0x871: // "Quantity Timeout" PARAM_TYPE_NUMERIC
         retval = 17;
         break; 
      case 0x872: // "Manual BC Entry loc" PARAM_TYPE_BOOL
         retval = 18;
         break; 
      case 0x873: // "Manual QTY Entry loc" PARAM_TYPE_BOOL
         retval = 19;
         break; 
      case 0x874: // "Delimiter loc" PARAM_TYPE_NUMERIC
         retval = 20;
         break; 
      case 0x875: // "Manual BC Entry invt" PARAM_TYPE_BOOL
         retval = 21;
         break; 
      case 0x876: // "Manual QTY Entry invt" PARAM_TYPE_BOOL
         retval = 22;
         break; 
      case 0x877: // "INVT LOC Delimiter" PARAM_TYPE_NUMERIC
         retval = 23;
         break; 
      case 0x878: // "Inventory Store" PARAM_TYPE_NUMERIC
         retval = 24;
         break; 
      case 0x87A: // "Display On Charge" PARAM_TYPE_NUMERIC
         retval = 25;
         break; 
      case 0x87B: // "F1" PARAM_TYPE_STRING
         retval = 26;
         break; 
      case 0x87C: // "F2" PARAM_TYPE_STRING
         retval = 27;
         break; 
      case 0x87D: // "F3" PARAM_TYPE_STRING
         retval = 28;
         break; 
      case 0x87E: // "F4" PARAM_TYPE_STRING
         retval = 29;
         break; 
      case 0x87F: // "F5" PARAM_TYPE_STRING
         retval = 30;
         break; 
      case 0x880: // "F6" PARAM_TYPE_STRING
         retval = 31;
         break; 
      case 0x881: // "F7" PARAM_TYPE_STRING
         retval = 32;
         break; 
      case 0x882: // "F8" PARAM_TYPE_STRING
         retval = 33;
         break; 
      case 0x883: // "F9" PARAM_TYPE_STRING
         retval = 34;
         break; 
      case 0x884: // "KeyboardInject" PARAM_TYPE_NUMERIC
         retval = 35;
         break; 
      case 0x885: // "QTY Transfer Mode" PARAM_TYPE_NUMERIC
         retval = 36;
         break; 
      case 0x886: // "QTY Delimiter" PARAM_TYPE_NUMERIC
         retval = 37;
         break; 
      case 0x887: // "Loc Delimiter" PARAM_TYPE_NUMERIC
         retval = 38;
         break; 
      case 0x888: // "QTY QTY Delimiter" PARAM_TYPE_NUMERIC
         retval = 39;
         break; 
      case 0x889: // "LOC QTY Delimiter" PARAM_TYPE_NUMERIC
         retval = 40;
         break; 
      case 0x88A: // "INVT QTY Delimiter" PARAM_TYPE_NUMERIC
         retval = 41;
         break; 
      case 0x88B: // "Confirm QTY Tmout" PARAM_TYPE_NUMERIC
         retval = 42;
         break; 
      case 0x88C: // "Confirm LOC Tmout" PARAM_TYPE_NUMERIC
         retval = 43;
         break; 
      case 0x88D: // "Min Qty Value" PARAM_TYPE_NUMERIC
         retval = 44;
         break; 
      case 0x88E: // "Max Qty Value" PARAM_TYPE_NUMERIC
         retval = 45;
         break; 
      default:                                                               
         *error = 1;                                                         
         break;                                                              
  } // switch                                                                
  return retval;                                                             
}                                                                            
uint32_t  GetSCode(char * str)                                   
{                                                                
   uint32_t retval = 0;                                          
                                                                 
   uint16_t len = strlen(str);                                   
   uint16_t i = 0;                                               
   for( i = 0; i < len; i++ )                                    
   {                                                             
      retval += (uint32_t)str[i];                                
   }                                                             
   return retval;                                                
}                                                                
                                                                                         
                                                                                         
                                                                                         
bool  GenericParamSetIntWithStubFn( uint16_t attributeNumber, uint32_t value, bool permanent) 
{                                                                                        
   bool retval = false;                                                                  
                                                                                         
   switch( attributeNumber )                                                             
   {                                                                                     
      case 0x885: // "QTY Transfer Mode" gblQtyXferMode
         retval = GenericParamSetInt( attributeNumber, value, permanent);                 
         if ( retval != false )                                                           
         {                                                                                
            gblQtyXferMode_cbsetstubfn( value );
         }                                                                                
                                                                                          
         break;                                                                          
      case 0x886: // "QTY Delimiter" sqtyDelim
         retval = GenericParamSetInt( attributeNumber, value, permanent);                 
         if ( retval != false )                                                           
         {                                                                                
            sqtyDelim_cbsetstubfn( value );
         }                                                                                
                                                                                          
         break;                                                                          
      case 0x887: // "Loc Delimiter" slocDelim
         retval = GenericParamSetInt( attributeNumber, value, permanent);                 
         if ( retval != false )                                                           
         {                                                                                
            slocDelim_cbsetstubfn( value );
         }                                                                                
                                                                                          
         break;                                                                          
      case 0x888: // "QTY QTY Delimiter" sqtyqtyDelim
         retval = GenericParamSetInt( attributeNumber, value, permanent);                 
         if ( retval != false )                                                           
         {                                                                                
            sqtyqtyDelim_cbsetstubfn( value );
         }                                                                                
                                                                                          
         break;                                                                          
      case 0x889: // "LOC QTY Delimiter" slocqtyDelim
         retval = GenericParamSetInt( attributeNumber, value, permanent);                 
         if ( retval != false )                                                           
         {                                                                                
            slocqtyDelim_cbsetstubfn( value );
         }                                                                                
                                                                                          
         break;                                                                          
      case 0x88A: // "INVT QTY Delimiter" sinvtqtyDelim
         retval = GenericParamSetInt( attributeNumber, value, permanent);                 
         if ( retval != false )                                                           
         {                                                                                
            sinvtqtyDelim_cbsetstubfn( value );
         }                                                                                
                                                                                          
         break;                                                                          
      case 0x88B: // "Confirm QTY Tmout" sqtyToutConf
         retval = GenericParamSetInt( attributeNumber, value, permanent);                 
         if ( retval != false )                                                           
         {                                                                                
            sqtyToutConf_cbsetstubfn( value );
         }                                                                                
                                                                                          
         break;                                                                          
      case 0x88C: // "Confirm LOC Tmout" conflocTout
         retval = GenericParamSetInt( attributeNumber, value, permanent);                 
         if ( retval != false )                                                           
         {                                                                                
            conflocTout_cbsetstubfn( value );
         }                                                                                
                                                                                          
         break;                                                                          
      case 0x88D: // "Min Qty Value" gblMinQtyValue
         retval = GenericParamSetInt( attributeNumber, value, permanent);                 
         if ( retval != false )                                                           
         {                                                                                
            gblMinQtyValue_cbsetstubfn( value );
         }                                                                                
                                                                                          
         break;                                                                          
      case 0x88E: // "Max Qty Value" gblMaxQtyValue
         retval = GenericParamSetInt( attributeNumber, value, permanent);                 
         if ( retval != false )                                                           
         {                                                                                
            gblMaxQtyValue_cbsetstubfn( value );
         }                                                                                
                                                                                          
         break;                                                                          
                                                                                         
   }                                                                                     
   return retval;                                                                        
}                                                                                        
                                                                                         
                                                                                         
                                                                                         
bool  GenericParamSetStringWithStubFn( uint16_t attributeNumber, char * str, bool permanent) 
{                                                                                        
   bool retval = false;                                                                  
                                                                                         
   switch( attributeNumber )                                                             
   {                                                                                     
                                                                                         
   }                                                                                     
   return retval;                                                                        
}                                                                                        
                                                                                         
                                                                                         
                                                                                         
uint32_t  GenericParamGetIntWithStubFn( uint16_t attributeNumber )                                
{                                                                                        
   uint32_t value = 0;                                                                 
                                                                                         
   switch( attributeNumber )                                                             
   {                                                                                     
      case 0x885: // "QTY Transfer Mode" gblQtyXferMode
         value = GenericParamGetInt( attributeNumber );                                   
         gblQtyXferMode_cbgetstubfn( &value );
         break;                                                                           
      case 0x886: // "QTY Delimiter" sqtyDelim
         value = GenericParamGetInt( attributeNumber );                                   
         sqtyDelim_cbgetstubfn( &value );
         break;                                                                           
      case 0x887: // "Loc Delimiter" slocDelim
         value = GenericParamGetInt( attributeNumber );                                   
         slocDelim_cbgetstubfn( &value );
         break;                                                                           
      case 0x888: // "QTY QTY Delimiter" sqtyqtyDelim
         value = GenericParamGetInt( attributeNumber );                                   
         sqtyqtyDelim_cbgetstubfn( &value );
         break;                                                                           
      case 0x889: // "LOC QTY Delimiter" slocqtyDelim
         value = GenericParamGetInt( attributeNumber );                                   
         slocqtyDelim_cbgetstubfn( &value );
         break;                                                                           
      case 0x88A: // "INVT QTY Delimiter" sinvtqtyDelim
         value = GenericParamGetInt( attributeNumber );                                   
         sinvtqtyDelim_cbgetstubfn( &value );
         break;                                                                           
      case 0x88B: // "Confirm QTY Tmout" sqtyToutConf
         value = GenericParamGetInt( attributeNumber );                                   
         sqtyToutConf_cbgetstubfn( &value );
         break;                                                                           
      case 0x88C: // "Confirm LOC Tmout" conflocTout
         value = GenericParamGetInt( attributeNumber );                                   
         conflocTout_cbgetstubfn( &value );
         break;                                                                           
      case 0x88D: // "Min Qty Value" gblMinQtyValue
         value = GenericParamGetInt( attributeNumber );                                   
         gblMinQtyValue_cbgetstubfn( &value );
         break;                                                                           
      case 0x88E: // "Max Qty Value" gblMaxQtyValue
         value = GenericParamGetInt( attributeNumber );                                   
         gblMaxQtyValue_cbgetstubfn( &value );
         break;                                                                           
                                                                                         
   }                                                                                     
   return value;                                                                         
}                                                                                        
                                                                                         
                                                                                         
                                                                                         
bool  GenericParamGetStringWithStubFn( uint16_t attributeNumber, uint32_t * value )           
{                                                                                        
   bool retval = false;                                                                 
                                                                                         
   switch( attributeNumber )                                                             
   {                                                                                     
                                                                                         
   }                                                                                     
   return retval;                                                                         
}                                                                                        
                                                                                      
                                                                                      
#endif // NOT SIMULATOR                                                                                      
