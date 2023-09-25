/*                                                                                             
 * Copyright (c) 2021 Zebra Technologies and/or its affiliates. All rights reserved            
 */                                                                                            
/*** Note This file is auto-generated  ***/                                                    
                                                                                               
#ifndef __CANOPYAUTOUSER_CFG_H                                                                 
#define __CANOPYAUTOUSER_CFG_H                                                                 
                                                                                               
#ifdef SIMULATOR                                                                               
                                                                                               
#ifdef __cplusplus                                                                             
 extern "C" {                                                                                
#endif                                                                                         
                                                                                               
#include "user_cfg.h"                                                                        
                                                                                               
/* Public typedef  */                                                                          
#define CONSOLIDATED_STR_MAX_SIZE   101  // Larger of all max string sizes
#define USER_STR_MAX_SIZE           20  // Legacy param max string size
#define ZVENDOR_STR_MAX_SIZE        101  // Vendor param max string size
#define ZVENDOR_STR_MAX_COUNT       15
#define ZVENDOR_INT_MAX_COUNT       100
#define ZVENDOR_WORD_MAX_COUNT      40
#define ZVENDOR_WORD_MAX_SIZE        2
#define ZVENDOR_DWORD_MAX_COUNT     0
#define ZVENDOR_DWORD_MAX_SIZE       4
typedef struct                                                                                 
{                                                                                              
   uint8_t setting;                                                                            
   char    string[USER_STR_MAX_SIZE + 1];                                                      
} Function_Key_t;                                                                              
                                                                                               
                                                                                               
typedef struct                                                                                 
{                                                                                              
   uint8_t setting;                                                                            
   uint8_t user_define;                                                                        
} Quantity_Timeout_t;                                                                          
                                                                                               
typedef struct                                                                                 
{                                                                                              
   uint8_t setting;                                                                            
   char    user_define;                                                                        
} Delimiter_t;                                                                                 
                                                                                               
typedef struct                                                                                 
{                                                                                              
   uint8_t display_timeout;                                                                    
   Function_Key_t function_key[20];                                                            
   uint8_t manual_barcode_entry;                                                               
   uint8_t manual_quantity_entry;                                                              
   uint8_t auto_display_brightness;                                                            
   uint8_t keypad_backlight;                                                                   
   uint8_t home_key_launch;                                                                    
   uint8_t display_on_charge;                                                                  
                                                                                               
   uint8_t qty_manual_barcode_entry;                                                           
   uint8_t qty_manual_quantity_entry;                                                          
   Quantity_Timeout_t quantity_timeout;                                                        
                                                                                               
   uint8_t loc_manual_barcode_entry;                                                           
   uint8_t loc_manual_quantity_entry;                                                          
   Delimiter_t loc_delimiter;                                                                  
                                                                                               
   uint8_t invt_manual_barcode_entry;                                                          
   uint8_t invt_manual_quantity_entry;                                                         
   Delimiter_t invt_delimiter;                                                                 
                                                                                               
   uint8_t invt_store;                                                                         
   uint8_t live_capture;                                                                       
                                                                                               
   uint8_t  gblQtyXferMode;
   uint8_t  sqtyDelim;
   uint8_t  slocDelim;
   uint8_t  sqtyqtyDelim;
   uint8_t  slocqtyDelim;
   uint8_t  sinvtqtyDelim;
   uint8_t  sqtyToutConf;
   uint8_t  conflocTout;
   uint16_t gblMinQtyValue;
   uint16_t gblMaxQtyValue;
} User_Config_t;                                                                                     
/****************************************************************************************/           
/** callback definitions **/                                          
void user_cfg_set_qty_transfer_mode(uint32_t value);
void user_cfg_get_qty_transfer_mode(uint32_t* value);
void gblQtyXferMode_cbsetstubfn(uint32_t value); 
void gblQtyXferMode_cbgetstubfn(uint32_t* value); 
void user_cfg_set_qty_delimiter(uint32_t value);
void user_cfg_get_qty_delimiter(uint32_t* value);
void sqtyDelim_cbsetstubfn(uint32_t value); 
void sqtyDelim_cbgetstubfn(uint32_t* value); 
void user_cfg_set_loc_delimiter(uint32_t value);
void user_cfg_get_loc_delimiter(uint32_t* value);
void slocDelim_cbsetstubfn(uint32_t value); 
void slocDelim_cbgetstubfn(uint32_t* value); 
void user_cfg_set_qty_qty_delimiter(uint32_t value);
void user_cfg_get_qty_qty_delimiter(uint32_t* value);
void sqtyqtyDelim_cbsetstubfn(uint32_t value); 
void sqtyqtyDelim_cbgetstubfn(uint32_t* value); 
void user_cfg_set_loc_qty_delimiter(uint32_t value);
void user_cfg_get_loc_qty_delimiter(uint32_t* value);
void slocqtyDelim_cbsetstubfn(uint32_t value); 
void slocqtyDelim_cbgetstubfn(uint32_t* value); 
void user_cfg_set_invt_qty_delimiter(uint32_t value);
void user_cfg_get_invt_qty_delimiter(uint32_t* value);
void sinvtqtyDelim_cbsetstubfn(uint32_t value); 
void sinvtqtyDelim_cbgetstubfn(uint32_t* value); 
void confirm_qty_set_timeout(uint32_t value);
void confirm_qty_get_timeout(uint32_t* value);
void sqtyToutConf_cbsetstubfn(uint32_t value); 
void sqtyToutConf_cbgetstubfn(uint32_t* value); 
void confirm_loc_set_timeout(uint32_t value);
void confirm_loc_get_timeout(uint32_t* value);
void conflocTout_cbsetstubfn(uint32_t value); 
void conflocTout_cbgetstubfn(uint32_t* value); 
void user_cfg_set_qty_min_value(uint32_t value);
void user_cfg_get_qty_min_value(uint32_t* value);
void gblMinQtyValue_cbsetstubfn(uint32_t value); 
void gblMinQtyValue_cbgetstubfn(uint32_t* value); 
void user_cfg_set_qty_max_value(uint32_t value);
void user_cfg_get_qty_max_value(uint32_t* value);
void gblMaxQtyValue_cbsetstubfn(uint32_t value); 
void gblMaxQtyValue_cbgetstubfn(uint32_t* value); 
/****************************************************************************************/           
/**  attribute defines   **/                                          
#define gblDispTout_attr   0x860
#define gblF1Key_radio_attr   0x861
#define gblF2Key_radio_attr   0x862
#define gblF3Key_radio_attr   0x863
#define gblF4Key_radio_attr   0x864
#define gblF5Key_radio_attr   0x865
#define gblF6Key_radio_attr   0x866
#define gblF7Key_radio_attr   0x867
#define gblF8Key_radio_attr   0x868
#define gblF9Key_radio_attr   0x869
#define gblManBCEntry_attr   0x86A
#define gblManQtyEntry_attr   0x86B
#define gblAutoDispBrt_attr   0x86C
#define gblKeypadBacklight_attr   0x86D
#define gblHomeKey_attr   0x86E
#define seqManBCEdit_attr   0x86F
#define seqManQTYEdit_attr   0x870
#define seqTout_attr   0x871
#define selManBCEdit_attr   0x872
#define selManQTYEdit_attr   0x873
#define selDelim_attr   0x874
#define sinvManBCEdit_attr   0x875
#define sinvManQTYEdit_attr   0x876
#define sinvDelim_attr   0x877
#define sinvStore_attr   0x878
#define showLiveCapture_attr   0x879
#define gbDispOnCharge_attr   0x87A
#define gblF1Key_attr   0x87B
#define gblF2Key_attr   0x87C
#define gblF3Key_attr   0x87D
#define gblF4Key_attr   0x87E
#define gblF5Key_attr   0x87F
#define gblF6Key_attr   0x880
#define gblF7Key_attr   0x881
#define gblF8Key_attr   0x882
#define gblF9Key_attr   0x883
#define Reserved_KeyboardInject_attr   0x884
#define gblQtyXferMode_attr   0x885
#define sqtyDelim_attr   0x886
#define slocDelim_attr   0x887
#define sqtyqtyDelim_attr   0x888
#define slocqtyDelim_attr   0x889
#define sinvtqtyDelim_attr   0x88A
#define sqtyToutConf_attr   0x88B
#define conflocTout_attr   0x88C
#define gblMinQtyValue_attr   0x88D
#define gblMaxQtyValue_attr   0x88E
/****************************************************************************************/           
 
                                                                                                     
typedef enum                                                                                         
{                                                                                                    
   attr_unknown,                                                                                     
   attr_string,                                                                                      
   attr_int                                                                                          
} Attr_Query_t;                                                                                      
                                                                                                     
                                                                                                     
extern bool           GenericParamSetInt(uint16_t attributeNumber, uint32_t value, bool permanent);  
extern bool           GenericParamSetString(uint16_t attributeNumber, char* str, bool permanent);    
extern uint32_t       GenericParamGetInt(uint16_t attributeNumber );                                 
extern bool           GenericParamGetString(uint16_t attributeNumber, uint32_t * value);             
extern bool           GenericParamSetIntWithStubFn( uint16_t attributeNumber, uint32_t value, bool permanent); 
extern bool           GenericParamSetStringWithStubFn( uint16_t attributeNumber, char * str, bool permanent);  
extern uint32_t       GenericParamGetIntWithStubFn( uint16_t attributeNumber );                      
extern bool           GenericParamGetStringWithStubFn( uint16_t attributeNumber, uint32_t * value ); 
extern User_Config_t  user_cfg_temporary;                                                            
extern User_Config_t  user_cfg_permanent;                                                            
                                                                                                     
extern Attr_Query_t   GetAttributeQType(uint16_t attributeNumber);                                   
#ifdef __cplusplus                                                                                   
}                                                                                                    
#endif                                                                                               
                                                                                                     
#endif // SIMULATOR                                                                                  
                                                                                                     
#endif  /* __CANOPYAUTOUSER_CFG_H  */                                                                
