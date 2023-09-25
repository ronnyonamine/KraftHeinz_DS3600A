/**
  ******************************************************************************
  * @file    user_cfg_wrapper.hpp
  * @author  SIANA Systems
  * @date    06/07/2021
  * @brief   C compatible API to wrap Config.Parameter registration process
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2021 SIANA Systems</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USER_CFG_WRAPPER_HPP_
#define _USER_CFG_WRAPPER_HPP_

#ifdef __cplusplus
extern "C" {
#endif

/*--->> Includes <<-----------------------------------------------------------*/

#include <stdint.h>
#include <string.h>
#include "user_cfg.h"
#include "SSI_cmd.h"
#include <gui/common/param_types.h>
  
/*--->> Defines <<------------------------------------------------------------*/


/*--->> Data Types <<---------------------------------------------------------*/

/**
  * @brief Short type to identify names as strings
  */
typedef struct
{
  char*   name;
  uint8_t  len;
} user_cfg_name_t;

/**
  * @brief Preset entry to generate a possible preset list
  */
typedef struct
{
  char*            preset_name;
  uint32_t          preset_val;
}param_preset_t;

/**
  * @brief Parameter Descriptor  type to convert into c++ polymorphic ParamDescr
  */
typedef struct
{
  uint32_t        def_val;
  uint32_t        min_val;
  uint32_t        max_val;
  char*              name;
  bool          user_edit;
  bool        show_preset;
  param_preset_t* presets;
  uint16_t     preset_len;
}c_param_descr_t;


/*--->> Externs <<------------------------------------------------------------*/


/*--->> API <<----------------------------------------------------------------*/

/**
 * @brief Starts the custom parameter registration process in backend
 *
 * @param none
 * @retval Status code for operation.
 */
e_user_cfg_status user_cfg_initialize_platform(void);



void write_custom_default_new_parameter(void);
void read_custom_default_new_parameter(void);


/**
 * @brief Changes the attribute number on a specified parameter
 *
 * @param idx index of the configparam object to modify
 * @param att_number attribute number of the configuration parameter
 * @retval Status code for operation.
 */
e_user_cfg_status user_cfg_update_att_number(uint16_t idx, uint16_t att_number);


/**
 * Fills attribute number for all config object parameters during scanner boot-up.
   Attribute number for all config parameter object will be 0 by default.

*/

void initialize_object_attributeEx();


/**
 * during boot-up update user_cfg structure value with config object values from reading flash for new parameters
 */
 void update_usercfg_structure_from_config_object();

 /**
 * update config object value for new parameters. as updating value in each screen now updates user_cfg structure value
 */
 void update_config_object_new_param_str(uint16_t att_num, uint8_t * value);
 void update_config_object_new_param_int(uint16_t att_num, uint32_t value);

/**
 * @brief Changes the internal name for an attribute on the UI Side
 *
 * @param att_num attribute number of the parameter to edit
 * @param name pointer to array holding new name
 * @param len length of the new name
 * @param type specifies the Type of name to change
 * @retval Status code for operation.
 */
e_user_cfg_status user_cfg_update_name(uint16_t att_num,
                                       char* name, 
                                       uint8_t len,
                                       e_name_type type);

/**
 * @brief Changes the parameter type and/or descriptor of a specific parameter
 *
 * @param att_num attribute number of the parameter to edit
 * @param type new parameter type. can be the same to only update descriptor
 * @param param_descr c-type param descriptor matching param type
 * @retval Status code for operation.
 */
e_user_cfg_status user_cfg_update_type(uint16_t att_num,
                                       param_type_t type, 
                                       c_param_descr_t* param_descr);

/**
 * @brief Changes the parameter on.edit callback if required
 *
 * @param att_num attribute number of the parameter to edit
 * @param callback function pointer to new callback
 * @retval Status code for operation.
 */
e_user_cfg_status user_cfg_update_callback(uint16_t att_num,
                                           void     callback(uint32_t));

/**
 * @brief Adds a new parameter to the list of parameters on the UI code.
 *
 * @param  param_name structure holding the parameter name info
 * @param  short_name struct. holding the shorthened name of the parameter
 * @param  app_name struct. holding the name of the Application for the param.
 * @param  param_type enumeration for the type of parameter being added
 * @param  att_number attribute number to assign to the parameter
 * @param  param_size size of the parameter storage in bytes 
 * @param  param_sign true if the parameter stores a signed value
 * @param  param_descr Descriptor of the value characteristics of the param.
 * @param  callback function pointer to function to call on param.modify
 * @retval Status code for operation.
 */
e_user_cfg_status user_cfg_add_parameter(user_cfg_name_t  param_name,
                                         user_cfg_name_t  short_name,
                                         user_cfg_name_t  app_name,
                                         param_type_t     param_type,
                                         uint16_t         att_number,
                                         uint16_t         param_size,
                                         bool             param_sign,
                                         c_param_descr_t* param_descr,
                                         void             callback(uint32_t) );

/**
 * @brief Gets the attribute number of a parameter by the index
 *
 * @param att_num Pointer were to store the attribute number
 * @param idx Index of the parameter
 * @retval Status code for operation.
 */
e_user_cfg_status user_cfg_get_att_by_index(uint16_t *att_num, uint16_t idx);

/**
 * @brief Gets the index of a parameter by the attribute number
 * Note: attribute numbers may repeat between parameters, so the first index
 * found is returned
 *
 * @param idx Pointer were to store the index
 * @param att_number Attribute number of the parameter
 * @retval Status code for operation.
 */
e_user_cfg_status user_cfg_get_index_by_att(uint16_t *idx, uint16_t att_num);

#ifdef __cplusplus
}
#endif

#endif /* _USER_CFG_WRAPPER_HPP_ */
