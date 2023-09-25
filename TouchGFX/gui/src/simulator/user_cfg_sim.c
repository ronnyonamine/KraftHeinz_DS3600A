#ifdef SIMULATOR

#include <gui/simulator/user_cfg.h>
#include <gui/simulator/menuHandler.h>
#include <gui/simulator/SSI_cmd.h>
#include <gui/simulator/canopyAuto_usercfg.h>

#include <stdio.h>
#include <string.h>


/* SIANA - Customizable parameters API */

#define PARAM_STORE_MAX_SIZE   300
typedef struct
{
  /* Static allocation for values buffer for reference -> 
     another idea would be to dynamically allocate it on param registration */
  uint32_t param_hash;
  t_param_descriptor param_descr[PARAM_STORE_MAX_SIZE];
  t_param_range param_range[PARAM_STORE_MAX_SIZE];
  uint8_t  param_values[PARAM_STORE_MAX_SIZE*4]; /* Sized for average uint32_t*/
} usr_cfg_param_store_t;

/* SIANA - Customizable parameters API */
usr_cfg_param_store_t  param_store;

static uint8_t home_hey_launch = 1; 
static uint8_t launch_screen = 1;

// special handling vars
bool virtual_cfg_menu_lock = 0;
bool bluetooth_batchmode_flag = 1;



uint32_t get_display_timeout_ms(void)
{
    return (2);
}

void set_function_key(uint8_t key, uint8_t setting, const char * str, bool permanent)
{
    // Do nothing...
}

uint8_t get_function_key_setting(uint8_t key)
{
    return (2);
}

char * get_function_key_string(uint8_t key)
{
    return NULL;
}

void set_manual_barcode_entry(uint8_t setting, bool permanent)
{
    // Do nothing...
}

uint8_t get_manual_barcode_entry(void)
{
    return (2);
}

void set_manual_quantity_entry(uint8_t setting, bool permanent)
{
    // Do nothing...
}

uint8_t get_manual_quantity_entry(void)
{
    return (2);
}

void set_home_key_launch(uint8_t setting, bool permanent)
{
    home_hey_launch = setting;
}

uint8_t get_home_key_launch(void)
{
    return home_hey_launch;
}

void set_display_on_charge(uint8_t setting, bool permanent)
{
    // Do nothing...
}

uint8_t get_display_on_charge(void)
{
    return (2);
}

void set_qty_manual_barcode_entry(uint8_t setting, bool permanent)
{
    // Do nothing...
}

uint8_t get_qty_manual_barcode_entry(void)
{
    return (2);
}

void set_qty_manual_quantity_entry(uint8_t setting, bool permanent)
{
    // Do nothing...
}

uint8_t get_qty_manual_quantity_entry(void)
{
    return (2);
}

void set_quantity_timeout(uint8_t setting, uint8_t value, bool permanent)
{
    // Do nothing...
}

uint8_t get_quantity_timeout_setting(void)
{
    return (2);
}

uint8_t get_user_define_quantity_timeout(void)
{
    return (2);
}

uint16_t get_quantity_timeout_frame(void)
{
    return (2);
}

void set_loc_manual_barcode_entry(uint8_t setting, bool permanent)
{
    // Do nothing...
}

uint8_t get_loc_manual_barcode_entry(void)
{
    return (2);
}

void set_loc_manual_quantity_entry(uint8_t setting, bool permanent)
{
    // Do nothing...
}

uint8_t get_loc_manual_quantity_entry(void)
{
    return (2);
}

void set_loc_delimiter(uint8_t setting, char user_define, bool permanent)
{
    // Do nothing...
}

uint8_t get_loc_delimiter_setting(void)
{
    return (2);
}

char get_loc_delimiter_define(void)
{
    return (2);
}

void set_invt_manual_barcode_entry(uint8_t setting, bool permanent)
{
    // Do nothing...
}

uint8_t get_invt_manual_barcode_entry(void)
{
    return (2);
}

void set_invt_manual_quantity_entry(uint8_t setting, bool permanent)
{
    // Do nothing...
}

uint8_t get_invt_manual_quantity_entry(void)
{
    return (2);
}

void set_invt_delimiter(uint8_t setting, char user_define, bool permanent)
{
    // Do nothing...
}

uint8_t get_invt_delimiter_setting(void)
{
    return (2);
}

char get_invt_delimiter_define(void)
{
    return (2);
}

void set_invt_store(uint8_t setting, bool permanent)
{
    // Do nothing...
}

uint8_t get_invt_store(void)
{
    return (2);
}

void set_live_capture(uint8_t setting, bool permanent)
{
    // Do nothing...
}

uint8_t get_live_capture(void)
{
    return 0;
}

void set_launch_screen(uint32_t setting)
{
    launch_screen = setting;
}

uint32_t get_launch_screen(void)
{
    return launch_screen;
}

/* SIANA - Customizable parameters API */
/* Example code - managing all on RAM for reference - simulator*/
e_user_cfg_status user_cfg_register_param(t_param_descriptor in_descr,
                                          t_param_range in_range,
                                          uint8_t* def_array,
                                          uint16_t def_len)
{
  /* Here we register the parameter given the index */
  uint16_t idx = in_descr.idx;
  
  /* Sanity checks on descriptor/properties */
  if((in_descr.type != 'B')&& 
     (in_descr.type != 'C')&& 
     (in_descr.type != 'F')&& 
     (in_descr.type != 'W')&& 
     (in_descr.type != 'I')&& 
     (in_descr.type != 'D')&& 
     (in_descr.type != 'L')&& 
     (in_descr.type != 'X') )
  {
    return USER_CFG_PARAM_DESCR_ERROR;
  }
  /* Check properties bitmask */
  if(in_descr.properties &(~(USER_CFG_PROPERTY_BITMASK)))
  {
    return USER_CFG_PARAM_DESCR_ERROR;
  }
  /* Check for correct length */
  if(((in_descr.type == 'B') && (in_descr.length < sizeof(uint8_t))) ||
     ((in_descr.type == 'C') && (in_descr.length < sizeof(uint8_t))) ||
     ((in_descr.type == 'F') && (in_descr.length < sizeof(uint8_t))) ||
     ((in_descr.type == 'X') && (in_descr.length < sizeof(uint8_t))) ||
     ((in_descr.type == 'W') && (in_descr.length < sizeof(uint16_t))) ||
     ((in_descr.type == 'I') && (in_descr.length < sizeof(uint16_t))) ||
     ((in_descr.type == 'D') && (in_descr.length < sizeof(uint32_t))) ||
     ((in_descr.type == 'L') && (in_descr.length < sizeof(uint32_t))) )
  {
    return USER_CFG_PARAM_DESCR_ERROR;
  }
    
  /* here we check the parameter type to see how do we interpret the default */
  if ( (in_descr.type == 'S') || (in_descr.type == 'A') )
  {
    /* TODO: String/Array handling */
  }
  else
  {
    /* TODO: Handle parameter name storage */
    memcpy((void*)&(param_store.param_descr[idx]),
           (void*)&in_descr, 
           sizeof(in_descr));
    memcpy((void*)&(param_store.param_range[idx]),
           (void*)&in_range,
           sizeof(in_range)); 
  }
  return USER_CFG_OK;
}

e_user_cfg_status user_cfg_init_store(uint16_t param_size, uint32_t param_hash)
{
  /* TODO - retrieve data from flash */
  /* we compare the hash received against the hash stored to check if the 
   * configuration parameter definition has changed */
  if(param_hash != param_store.param_hash)
  {
    /* We reset the stored values, since the mapping might have changed*/
    memset(param_store.param_values,0xFF,PARAM_STORE_MAX_SIZE);
    param_store.param_hash = param_hash;
    return USER_CFG_HASH_MISMATCH;
    /* TODO - if required, store change in flash again */
  }
  return USER_CFG_OK;
}

e_user_cfg_status user_cfg_get_param_value(uint16_t index, uint8_t* buffer)
{
  /* TODO: Implement for all supported types */
  buffer[0] = param_store.param_values[index];
  return USER_CFG_OK;
}

e_user_cfg_status  user_cfg_set_param_value(uint16_t index,
                                            uint8_t* value,
                                            uint16_t len)
{
  /* TODO - Implement proper for all supported types */
  param_store.param_values[index] = value[0];
  
  /* TODO - store in Flash */
  return USER_CFG_OK; /* return false if flash operation fails */
}

/* Wrappers for CST_API to link to Frontend Config Data-Store API */
void user_cfg_set_auto_disp_brg(uint32_t bright)
{
  CST_APIsetDisplayBrightness((uint8_t)bright, true);
}

void user_cfg_set_display_timeout(uint32_t tout)
{
  CST_APIsetDisplayTimeout((uint8_t)tout, true);
}

void user_cfg_set_barcode_editable(uint32_t bcedit)
{
  set_manual_barcode_entry((uint8_t)bcedit, true);
}

void user_cfg_set_qty_editable(uint32_t qtyedit)
{
  set_manual_quantity_entry((uint8_t)qtyedit, true);
}

void user_cfg_set_key_backlight(uint32_t backlight)
{
  CST_APIsetKeypadBL((uint8_t)backlight, true);
}

void user_cfg_set_disp_on_charge(uint32_t on_charge)
{
  set_display_on_charge((uint8_t)on_charge, true);
}

void user_cfg_set_show_live_capture(uint32_t live)
{
  set_live_capture((uint8_t)live, true);
}

void user_cfg_set_barcode_editable_scanloc(uint32_t bcedit)
{
  set_loc_manual_barcode_entry((uint8_t)bcedit, true);
}

void user_cfg_set_qty_editable_scanloc(uint32_t qtyedit)
{
  set_loc_manual_quantity_entry((uint8_t)qtyedit, true);
}

void user_cfg_set_delimiter_scanloc(uint32_t delimiter)
{
  set_loc_delimiter(Delimiter_User, (uint8_t)delimiter, true);
}

void user_cfg_set_barcode_editable_scanqty(uint32_t bcedit)
{
   set_qty_manual_barcode_entry((uint8_t)bcedit, true);
}

void user_cfg_set_qty_editable_scanqty(uint32_t qtyedit)
{
  set_qty_manual_quantity_entry((uint8_t)qtyedit, true);
}

void user_cfg_set_qty_tout_scanqty(uint32_t tout)
{
  set_quantity_timeout(Qty_Timeout_User, (uint8_t)tout, true);
}

void user_cfg_set_barcode_editable_scaninv(uint32_t bcedit)
{
  set_invt_manual_barcode_entry((uint8_t)bcedit, true);
}

void user_cfg_set_qty_editable_scaninv(uint32_t qtyedit)
{
  set_invt_manual_quantity_entry((uint8_t)qtyedit, true);
}

void user_cfg_set_delimiter_scaninv(uint32_t delimiter)
{
  set_invt_delimiter(Delimiter_User, (uint8_t)delimiter, true);
}

void user_cfg_set_invstore_scaninv(uint32_t store)
{
  set_invt_store((uint8_t)store, true);
}

void user_cfg_set_F1_assignment(uint32_t assign)
{
  set_function_key(KeyF1, assign, "", true);
}

void user_cfg_set_F2_assignment(uint32_t assign)
{
  set_function_key(KeyF2, assign, "", true);
}

void user_cfg_set_F3_assignment(uint32_t assign)
{
  set_function_key(KeyF3, assign, "", true);
}

void user_cfg_set_F4_assignment(uint32_t assign)
{
  set_function_key(KeyF4, assign, "", true);
}

void user_cfg_set_F5_assignment(uint32_t assign)
{
  set_function_key(KeyF5, assign, "", true);
}

void user_cfg_set_F6_assignment(uint32_t assign)
{
  set_function_key(KeyF6, assign, "", true);
}

void user_cfg_set_F7_assignment(uint32_t assign)
{
  set_function_key(KeyF7, assign, "", true);
}

void user_cfg_set_F8_assignment(uint32_t assign)
{
  set_function_key(KeyF8, assign, "", true);
}

void user_cfg_set_F9_assignment(uint32_t assign)
{
  set_function_key(KeyF9, assign, "", true);
}

void user_cfg_set_F1_string(uint32_t string)
{
  set_function_key(KeyF1, Custom_String, (const char*)string , true);
}

void user_cfg_set_F2_string(uint32_t string)
{
  set_function_key(KeyF2, Custom_String, (const char*)string , true);
}

void user_cfg_set_F3_string(uint32_t string)
{
  set_function_key(KeyF3, Custom_String, (const char*)string , true);
}

void user_cfg_set_F4_string(uint32_t string)
{
  set_function_key(KeyF4, Custom_String, (const char*)string , true);
}

void user_cfg_set_F5_string(uint32_t string)
{
  set_function_key(KeyF5, Custom_String, (const char*)string , true);
}

void user_cfg_set_F6_string(uint32_t string)
{
  set_function_key(KeyF6, Custom_String, (const char*)string , true);
}

void user_cfg_set_F7_string(uint32_t string)
{
  set_function_key(KeyF7, Custom_String, (const char*)string , true);
}

void user_cfg_set_F8_string(uint32_t string)
{
  set_function_key(KeyF8, Custom_String, (const char*)string , true);
}

void user_cfg_set_F9_string(uint32_t string)
{
  set_function_key(KeyF9, Custom_String, (const char*)string , true);
}

void user_cfg_set_home_key_launch(uint32_t key_launch)
{
    set_home_key_launch(key_launch, true);
}

/* Wrappers for CST_API to link to Frontend Config Data-Store API */
void user_cfg_get_auto_disp_brg(uint32_t* bright)
{
  *bright = CST_APIgetDisplayBrightness();
}

void user_cfg_get_display_timeout(uint32_t* tout)
{
  *tout = CST_APIgetDisplayTimeout();
}

void user_cfg_get_barcode_editable(uint32_t* bcedit)
{
  *bcedit = get_manual_barcode_entry();
}

void user_cfg_get_qty_editable(uint32_t* qtyedit)
{
  *qtyedit = get_manual_quantity_entry();
}

void user_cfg_get_key_backlight(uint32_t* backlight)
{
  *backlight = CST_APIgetKeypadBL();
}

void user_cfg_get_disp_on_charge(uint32_t* on_charge)
{
  *on_charge = get_display_on_charge();
}

void user_cfg_get_show_live_capture(uint32_t* live)
{
  *live = get_live_capture();
}

void user_cfg_get_barcode_editable_scanloc(uint32_t* bcedit)
{
  *bcedit = get_loc_manual_barcode_entry();
}

void user_cfg_get_qty_editable_scanloc(uint32_t* qtyedit)
{
  *qtyedit = get_loc_manual_quantity_entry();
}

void user_cfg_get_delimiter_scanloc(uint32_t* delimiter)
{
  *delimiter = get_loc_delimiter_define();
}

void user_cfg_get_barcode_editable_scanqty(uint32_t* bcedit)
{
  *bcedit = get_qty_manual_barcode_entry();
}

void user_cfg_get_qty_editable_scanqty(uint32_t* qtyedit)
{
  *qtyedit = get_qty_manual_quantity_entry();
}

void user_cfg_get_qty_tout_scanqty(uint32_t* tout)
{
  *tout = get_user_define_quantity_timeout();
}

void user_cfg_get_barcode_editable_scaninv(uint32_t* bcedit)
{
  *bcedit = get_invt_manual_barcode_entry();
}

void user_cfg_get_qty_editable_scaninv(uint32_t* qtyedit)
{
  *qtyedit = get_invt_manual_quantity_entry();
}

void user_cfg_get_delimiter_scaninv(uint32_t* delimiter)
{
  *delimiter = get_invt_delimiter_define();
}

void user_cfg_get_invstore_scaninv(uint32_t* store)
{
  *store = get_invt_store();
}

void user_cfg_get_F1_assignment(uint32_t* assign)
{
  *assign = get_function_key_setting(KeyF1);
}

void user_cfg_get_F2_assignment(uint32_t* assign)
{
  *assign = get_function_key_setting(KeyF2);
}

void user_cfg_get_F3_assignment(uint32_t* assign)
{
  *assign = get_function_key_setting(KeyF3);
}

void user_cfg_get_F4_assignment(uint32_t* assign)
{
  *assign = get_function_key_setting(KeyF4);
}

void user_cfg_get_F5_assignment(uint32_t* assign)
{
  *assign = get_function_key_setting(KeyF5);
}

void user_cfg_get_F6_assignment(uint32_t* assign)
{
  *assign = get_function_key_setting(KeyF6);
}

void user_cfg_get_F7_assignment(uint32_t* assign)
{
  *assign = get_function_key_setting(KeyF7);
}

void user_cfg_get_F8_assignment(uint32_t* assign)
{
  *assign = get_function_key_setting(KeyF8);
}

void user_cfg_get_F9_assignment(uint32_t* assign)
{
  *assign = get_function_key_setting(KeyF9);
}

void user_cfg_get_F1_string(uint32_t* string)
{
  *string = (uint32_t)get_function_key_string(KeyF1);
}

void user_cfg_get_F2_string(uint32_t* string)
{
  *string = (uint32_t)get_function_key_string(KeyF2);
}

void user_cfg_get_F3_string(uint32_t* string)
{
  *string = (uint32_t)get_function_key_string(KeyF3);
}

void user_cfg_get_F4_string(uint32_t* string)
{
  *string = (uint32_t)get_function_key_string(KeyF4);
}

void user_cfg_get_F5_string(uint32_t* string)
{
  *string = (uint32_t)get_function_key_string(KeyF5);
}

void user_cfg_get_F6_string(uint32_t* string)
{
  *string = (uint32_t)get_function_key_string(KeyF6);
}

void user_cfg_get_F7_string(uint32_t* string)
{
  *string = (uint32_t)get_function_key_string(KeyF7);
}

void user_cfg_get_F8_string(uint32_t* string)
{
  *string = (uint32_t)get_function_key_string(KeyF8);
}

void user_cfg_get_F9_string(uint32_t* string)
{
  *string = (uint32_t)get_function_key_string(KeyF9);
}

void user_cfg_get_home_key_launch(uint32_t* key_launch)
{
   *key_launch = get_home_key_launch();
}

#endif // SIMULATOR
