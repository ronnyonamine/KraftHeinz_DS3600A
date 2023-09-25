/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_CFG_H
#define __USER_CFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "canopyAuto_usercfg.h"
#include "SSI_cmd.h"


/* Public constants ----------------------------------------------------------*/

/**
 * @brief Status codes for configuration operations
 */
typedef enum
{
    USER_CFG_OK,                  /*<! No error during operation */
    USER_CFG_STORE_ERROR,         /*<! Issue storing non-volatile value */
    USER_CFG_HASH_MISMATCH,       /*<! Hash does not match with stored value */
    USER_CFG_PARAM_DESCR_ERROR,   /*<! Issue on the parameter descriptor */
    USER_CFG_PARAM_NOT_REGISTERED,/*<! Parameter index is not registered */
    USER_CFG_FLASH_READ_ERROR,    /*<! Issues reading external flash */
    USER_CFG_FLASH_WRITE_ERROR,   /*<! Issues writing external flash */
    USER_CFG_FLASH_ERASE_ERROR,   /*<! Issues erasing external flash */
    USER_CFG_UNDEFINED_ERROR      /*<! Error not currently specified */
}e_user_cfg_status;

/**
 * @brief Descriptor for configuration parameters based on RSM API.
 */
typedef struct
{
   uint16_t idx;         /*<! Index of the parameter */
   uint8_t type;         /*<! Parameter  Attribute Type */
   uint8_t properties;   /*<! Parameter properties bitfield */
   uint16_t length;      /*<! Length of parameter storage */
   uint8_t sub_type;     /*<! SubType for arrays */
   char*   name;         /*<! Parameter Name to be copied into backend */
} t_param_descriptor;
 
/**
 * @brief Range and default value descriptor for the backend API, for integer attributes.
 */
typedef struct
{
   uint32_t def_val;     /*<! Default value on Factory reset */
   uint32_t min_val;     /*<! Minimum possible Value for attribute */
   uint32_t max_val;     /*<! Maximum possible Value for attribute */
} t_param_range;

/**
 * @brief Possible Attribute Types
 */
typedef enum
{
  USER_CFG_ATT_BYTE = 'B',
  USER_CFG_ATT_CHAR = 'C',
  USER_CFG_ATT_BITFLAG = 'F',
  USER_CFG_ATT_WORD = 'W',
  USER_CFG_ATT_INTEGER = 'I',
  USER_CFG_ATT_DOUBLE = 'D',
  USER_CFG_ATT_LONG = 'L',
  USER_CFG_ATT_ARRAY = 'A',
  USER_CFG_ATT_STRING = 'S',
  USER_CFG_ATT_ACTION = 'X'
} e_attribute_type;

/**
 * @brief bitflags for attribute properties
 */
#define USER_CFG_PROPERTY_READABLE       0x01
#define USER_CFG_PROPERTY_WRITEABLE      0x02
#define USER_CFG_PROPERTY_PERSISTENT     0x04
   
#define USER_CFG_PROPERTY_BITMASK        0x07
   
/**
 * @brief Attribute Signedness
 */ 
#define USER_CFG_SIGN_UNSIGNED           false
#define USER_CFG_SIGN_SIGNED             true
enum
{
  DispTout_3S = 0,
  DispTout_6S = 1,
  DispTout_12S = 2,
  DispTout_18S = 3,
  DispTout_NoTout = 4,
  DispTout_3S_ms = 3000,
  DispTout_6S_ms = 6000,
  DispTout_12S_ms = 12000,
  DispTout_18S_ms = 18000,
  DispTout_NoTout_ms = 20000
};

enum
{
  FuncKey_String = 1,
  FuncKey_Enter = 2,
  FuncKey_Recall = 3,
  FuncKey_Back = 4
};

enum
{
  Manual_Entry_Yes = 1,
  Manual_Entry_No =2
};

enum
{
  Auto_Disp_BRT_Enable = 1,
  Auto_Disp_BRT_Medium = 2,
  Auto_Disp_BRT_Dimmest = 3,
  Auto_Disp_BRT_Dim = 4,
  Auto_Disp_BRT_Bright = 5,
  Auto_Disp_BRT_Brightest = 6
};

enum
{
  Key_BL_Off = 0,
  Key_BL_On = 1,
  Key_BL_Auto = 2
};

enum
{
  Home_Key_Launch_Navigator = 1,
  Home_Key_Launch_Scan_Qty = 2,
  Home_Key_Launch_Scan_Loc = 3,
  Home_Key_Launch_Inventory = 4,
  Home_Key_Launch_Match = 5,
  Home_Key_Launch_Image_Viewer = 6,
  Home_Key_Launch_Disable = 7
};

enum
{
  Disp_On_Charge_Half = 1,
  Disp_On_Charge_3_quarter = 2,
  Disp_On_Charge_Full = 3,
  Disp_On_Charge_Half_Value = 41,
  Disp_On_Charge_3_quarter_Value = 66,
  Disp_On_Charge_Full_Value = 86,
};

enum
{
  Qty_Timeout_User = 1,
  Qty_Timeout_3S = 2,
  Qty_Timeout_6S = 3,
  Qty_Timeout_9S = 4,
  Qty_Timeout_18S = 5,
  Qty_Timeout_30S = 6,
  Qty_Timeout_60S = 7,
  Qty_Timeout_No_Timeout = 8
};

enum
{
  Delimiter_User = 1,
  Delimiter_CR = 2,
  Delimiter_LF = 3,
  Delimiter_Space = 4,
  Delimiter_Tab = 5,
  Delimiter_2C = 6, // ,
  Delimiter_3A = 7, // :
  Delimiter_3B = 8, // ;
  Delimiter_3D = 9  // =
};

enum
{
  Invt_Store_Permanent = 1,
  Invt_Store_Temporary = 2
};

enum
{
  BCxQTY = 1,
  BC_Delimiter_QTY = 2
};

/* Function Declarations -----------------------------------------------------*/
extern uint32_t get_display_timeout_ms(void);


extern void set_function_key(uint8_t key, uint8_t setting, char * str, bool permanent);
extern void set_function_keyRSM(uint8_t key, uint8_t setting, char * str, bool permanent);
extern uint8_t get_function_key_setting(uint8_t key);
extern uint8_t get_function_key_settingRSM(uint8_t key);
extern char * get_function_key_string(uint8_t key);

extern bool set_manual_barcode_entry(uint8_t setting, bool permanent);
extern uint8_t get_manual_barcode_entry(void);

extern bool set_manual_quantity_entry(uint8_t setting, bool permanent);
extern uint8_t get_manual_quantity_entry(void);

extern void set_home_key_launch(uint8_t setting, bool permanent);
extern uint8_t get_home_key_launch(void);

extern bool set_display_on_charge(uint8_t setting, bool permanent);
extern uint8_t get_display_on_charge(void);

extern void set_qty_manual_barcode_entry(uint8_t setting, bool permanent);
extern uint8_t get_qty_manual_barcode_entry(void);

extern void set_qty_manual_quantity_entry(uint8_t setting, bool permanent);
extern uint8_t get_qty_manual_quantity_entry(void);

extern void set_quantity_timeout(uint8_t setting, uint8_t value, bool permanent);
extern uint8_t get_quantity_timeout_setting(void);
extern uint8_t get_user_define_quantity_timeout(void);
extern uint16_t get_quantity_timeout_frame(void);

extern void set_loc_manual_barcode_entry(uint8_t setting, bool permanent);
extern uint8_t get_loc_manual_barcode_entry(void);

extern void set_loc_manual_quantity_entry(uint8_t setting, bool permanent);
extern uint8_t get_loc_manual_quantity_entry(void);

extern void set_loc_delimiter(uint8_t setting, char user_define, bool permanent);
extern uint8_t get_loc_delimiter_setting(void);
extern char get_loc_delimiter_define(void);

extern void set_invt_manual_barcode_entry(uint8_t setting, bool permanent);
extern uint8_t get_invt_manual_barcode_entry(void);

extern void set_invt_manual_quantity_entry(uint8_t setting, bool permanent);
extern uint8_t get_invt_manual_quantity_entry(void);

extern void set_invt_delimiter(uint8_t setting, char user_define, bool permanent);
extern uint8_t get_invt_delimiter_setting(void);
extern char get_invt_delimiter_define(void);

extern void set_invt_store(uint8_t setting, bool permanent);
extern uint8_t get_invt_store(void);

extern void set_live_capture(uint8_t setting, bool permanent);
extern uint8_t get_live_capture(void);

extern void set_launch_screen(uint32_t setting);
extern uint32_t get_launch_screen(void);

extern User_Config_t get_user_cfg_permanent(void);
extern User_Config_t get_user_cfg_temporary(void);

/* SIANA - Customizable parameters API */
/**
 * @brief Initializes the parameter data storage
 *        Checks if hash/footprint of configuration map matches with the one 
 *        stored previously and clears the data if it doesn't
 *
 * @param param_size size of the configuration parameter list.
 * @param param_hash footprint of the parameter list.
 * @retval Status code for operation.
 */
e_user_cfg_status user_cfg_init_store(uint16_t param_size, uint32_t param_hash);

/**
 * @brief Registers a param on the backend.
 *
 * @param param_descr descriptor of all type information for a new parameter.
 * @param range       descriptor for range and default value for int parameters.
 * @param def_array   buffer with default values for array or string parameters.
 * @param def_len     length of default array or string.
 * @retval Status code for the operation.
 */
e_user_cfg_status user_cfg_register_param(t_param_descriptor param_descr,
                                          t_param_range range,
                                          uint8_t* def_array,
                                          uint16_t def_len);
 
/**
 * @brief Removes a param on the backend.
 *
 * @param param_idx  Index of the parameter to remove
 * @retval Status code for the operation.
 */
e_user_cfg_status user_cfg_remove_param(uint16_t param_idx);

/**
 * @brief Retrieves a value from the persistent data storage
 *
 * @param index Index of the parameter to retrieve from the storage
 * @param buffer buffer to hold the stored data - caller must check size
 * @retval Status code for the operation.
 */
//e_user_cfg_status user_cfg_get_param_value(uint16_t index, uint8_t* buffer);
e_user_cfg_status zuser_cfg_get_param_value(uint16_t index, uint8_t* buffer,uint16_t length,enum param_type p);

e_user_cfg_status user_cfg_get_customdefault_parameter_value(uint16_t index, uint8_t* buffer,int length,enum param_type p);
/**
 * @brief Stores back a value on the specified parameter index
 *
 * @param Index index of the parameter corresponding to the value to store
 * @param value buffer with value to store in memory
 * @param len size of the data to store - should match the
 * @retval Status code for operation.
 */
//e_user_cfg_status  user_cfg_set_param_value(uint16_t index, RETIRED...
//                                            uint8_t* value,
//                                            uint16_t len);

e_user_cfg_status  zuser_cfg_set_param_value(uint16_t index,
   uint8_t* value,uint16_t length,enum param_type p);

e_user_cfg_status  user_cfg_set_customdefault_param_value(uint16_t index,
                                            uint8_t* value,
                                            uint16_t len,enum param_type p);



e_user_cfg_status custom_parameter_read();

e_user_cfg_status writetoflash();

/* SIANA - backend-mandated API wrappers */
void user_cfg_set_auto_disp_brg(uint32_t bright);
void user_cfg_set_display_timeout(uint32_t tout);
void user_cfg_set_barcode_editable(uint32_t bcedit);
void user_cfg_set_qty_editable(uint32_t qtyedit);
void user_cfg_set_key_backlight(uint32_t backlight);
void user_cfg_set_disp_on_charge(uint32_t on_charge);

void user_cfg_set_show_live_capture(uint32_t live);

void user_cfg_set_barcode_editable_scanloc(uint32_t bcedit);
void user_cfg_set_qty_editable_scanloc(uint32_t qtyedit);
void user_cfg_set_delimiter_scanloc(uint32_t delimiter);

void user_cfg_set_barcode_editable_scanqty(uint32_t bcedit);
void user_cfg_set_qty_editable_scanqty(uint32_t qtyedit);
void user_cfg_set_qty_tout_scanqty(uint32_t tout);

void user_cfg_set_barcode_editable_scaninv(uint32_t bcedit);
void user_cfg_set_qty_editable_scaninv(uint32_t qtyedit);
void user_cfg_set_delimiter_scaninv(uint32_t delimiter);
void user_cfg_set_invstore_scaninv(uint32_t store);


/* Function Key Wrappers */
void user_cfg_set_F1_assignment(uint32_t assign);
void user_cfg_set_F2_assignment(uint32_t assign);
void user_cfg_set_F3_assignment(uint32_t assign);
void user_cfg_set_F4_assignment(uint32_t assign);
void user_cfg_set_F5_assignment(uint32_t assign);
void user_cfg_set_F6_assignment(uint32_t assign);
void user_cfg_set_F7_assignment(uint32_t assign);
void user_cfg_set_F8_assignment(uint32_t assign);
void user_cfg_set_F9_assignment(uint32_t assign);

void user_cfg_set_F1_string(uint32_t string);
void user_cfg_set_F2_string(uint32_t string);
void user_cfg_set_F3_string(uint32_t string);
void user_cfg_set_F4_string(uint32_t string);
void user_cfg_set_F5_string(uint32_t string);
void user_cfg_set_F6_string(uint32_t string);
void user_cfg_set_F7_string(uint32_t string);
void user_cfg_set_F8_string(uint32_t string);
void user_cfg_set_F9_string(uint32_t string);

void user_cfg_set_home_key_launch(uint32_t key_launch);

/* SIANA - backend-mandated API wrappers */
void user_cfg_get_auto_disp_brg(uint32_t* bright);
void user_cfg_get_display_timeout(uint32_t* tout);
void user_cfg_get_barcode_editable(uint32_t* bcedit);
void user_cfg_get_qty_editable(uint32_t* qtyedit);
void user_cfg_get_key_backlight(uint32_t* backlight);
void user_cfg_get_disp_on_charge(uint32_t* on_charge);

void user_cfg_get_show_live_capture(uint32_t* live);

void user_cfg_get_barcode_editable_scanloc(uint32_t* bcedit);
void user_cfg_get_qty_editable_scanloc(uint32_t* qtyedit);
void user_cfg_get_delimiter_scanloc(uint32_t* delimiter);

void user_cfg_get_barcode_editable_scanqty(uint32_t* bcedit);
void user_cfg_get_qty_editable_scanqty(uint32_t* qtyedit);
void user_cfg_get_qty_tout_scanqty(uint32_t* tout);

void user_cfg_get_barcode_editable_scaninv(uint32_t* bcedit);
void user_cfg_get_qty_editable_scaninv(uint32_t* qtyedit);
void user_cfg_get_delimiter_scaninv(uint32_t* delimiter);
void user_cfg_get_invstore_scaninv(uint32_t* store);


/* Function Key Wrappers */
void user_cfg_get_F1_assignment(uint32_t* assign);
void user_cfg_get_F2_assignment(uint32_t* assign);
void user_cfg_get_F3_assignment(uint32_t* assign);
void user_cfg_get_F4_assignment(uint32_t* assign);
void user_cfg_get_F5_assignment(uint32_t* assign);
void user_cfg_get_F6_assignment(uint32_t* assign);
void user_cfg_get_F7_assignment(uint32_t* assign);
void user_cfg_get_F8_assignment(uint32_t* assign);
void user_cfg_get_F9_assignment(uint32_t* assign);

void user_cfg_get_F1_string(uint32_t* string);
void user_cfg_get_F2_string(uint32_t* string);
void user_cfg_get_F3_string(uint32_t* string);
void user_cfg_get_F4_string(uint32_t* string);
void user_cfg_get_F5_string(uint32_t* string);
void user_cfg_get_F6_string(uint32_t* string);
void user_cfg_get_F7_string(uint32_t* string);
void user_cfg_get_F8_string(uint32_t* string);
void user_cfg_get_F9_string(uint32_t* string);

void user_cfg_get_home_key_launch(uint32_t* key_launch);
/* Exported data prototypes --------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __USER_CFG_H */
