/**
 ******************************************************************************
 * @file    user_cfg_wrapper.hpp
 * @author  SIANA Systems
 * @date    06/07/2021
 * @brief   Wrapper layer to call cpp config param. init. code in C context
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

/*--->> Includes <<-----------------------------------------------------------*/

#include "user_cfg_wrapper.hpp"
#include <gui/model/Model.hpp>
#include <gui/common/ConfigParam.hpp>
#include "canopyAuto_usercfg.h"
#include <iostream>
#include <string>

int boot_up =0;   //after reboot boot_up will be 0 and then once user_cfg structure for new parameters is filled with config object values from flash then boot_up becomes 1

/*--->> API Implementation <<-------------------------------------------------*/

/**
 * API: user_cfg_initialize_platform()
 */
e_user_cfg_status user_cfg_initialize_platform(void)
{
  
  Model::InitializeUserParam();
  //initialize_object_attribute();
  initialize_object_attributeEx();
  boot_up = 1;
  //update_usercfg_structure_from_config_object(); // handled by initialize_object_attributeEx().
  return USER_CFG_OK;
}

void initialize_object_attributeEx()
{
   uint16_t param_list_size = ConfigParam::GetParametersSize();
   char     str_value[CONSOLIDATED_STR_MAX_SIZE + 1];
   memset (str_value, 0, (CONSOLIDATED_STR_MAX_SIZE + 1));
   uint8_t* str_pvalue = (uint8_t*)str_value;
   uint16_t i_value = 0;
   uint16_t cpIdx = 0; // ConfigParam Index
   uint16_t canopyIdx = 0; // Canopy Index 
   uint16_t bucketIdx = 0;
   uint16_t attrid = 0;
   uint8_t  error = 0;
   Attr_Query_t attrqtype = attr_unknown;

   for (cpIdx = 0; cpIdx < param_list_size; cpIdx++)
   {
      attrid = GenericGetAttributeByName((char *) ConfigParam::GetParameters()[cpIdx].param_name.c_str());

      if (attrid == 0)
      {
         debug_printf(debug_level1, "\r\nError initialize_object_attributeEx bad attributeid name: %s index: %d\n",
            ConfigParam::GetParameters()[cpIdx].param_name.c_str(), cpIdx);
         continue;
      }

      ConfigParam::ModifyAttNumber(cpIdx, attrid); // inject attributeId into TouchGFX Platform
      canopyIdx = GetCanopyIndexFromAttrNum(attrid, &error);
      if ( error != 0 )
      {
         debug_printf(debug_level1, "\r\nError initialize_object_attributeEx 2 attrid: %d\n", attrid);
         continue;
      }

      if ( IsCanopyAttributeVendorType(canopyIdx, &error) == true )
      {
         if ( error != 0 )
         {
            debug_printf(debug_level1, "\r\nError initialize_object_attributeEx 3 attrid: %d\n", attrid);
            continue;
         }
         bucketIdx = GetBucketIndex(attrid);
         if (bucketIdx == 0xFF)
         {
            debug_printf(debug_level1, "\r\nError initialize_object_attributeEx 4 attrid: %d\n", attrid);
            continue;
         }
         attrqtype = GetAttributeQType(attrid);
         if (attrqtype == attr_unknown)
         {
            debug_printf(debug_level1, "\r\nError initialize_object_attributeEx 5 attrid: %d\n", attrid);
            continue;
         }
         if (attr_string != attrqtype)
         {
            if (attrqtype == attr_intbyte)
            {
               if (USER_CFG_OK != zuser_cfg_get_param_value(bucketIdx, (uint8_t *)&i_value, 1, numeric_type))
               {
                  debug_printf(debug_level1, "\r\nError initialize_object_attributeEx 6 attrid: %d\n", attrid);
                  continue;
               }
               i_value = (uint8_t) (i_value & 0x00FF);
               GenericParamSetInt(attrid, i_value, false);
            }
            else if (attrqtype == attr_intword)
            {
               if (USER_CFG_OK != zuser_cfg_get_param_value(bucketIdx, (uint8_t *)&i_value, 2, numeric_type))
               {
                  debug_printf(debug_level1, "\r\nError initialize_object_attributeEx 7 attrid: %d\n", attrid);
                  continue;
               }
               GenericParamSetInt(attrid, i_value, false);
            }
            else
            {
               debug_printf(debug_level1, "initialize_object_attributeEx: unsupported attribute type attr: %d\n", attrid);
               continue;
            }
         }
         else
         {
            if ( USER_CFG_OK != zuser_cfg_get_param_value(bucketIdx, str_pvalue, ZVENDOR_STR_MAX_SIZE, string_type))
            {
               debug_printf(debug_level1, "\r\nError initialize_object_attributeEx 4 attrid: %d\n", attrid);
               continue;
            }
            GenericParamSetString(attrid, (char*)str_pvalue, false);
         }
      }
   } // for
}

//during boot-up update user_cfg structure value with config object values for new parameters
// This method is retired.
void update_usercfg_structure_from_config_object()
{
  uint8_t error = 0;
  uint16_t attributeNumber = 0;
  uint16_t bucketIdx = 0;
  uint16_t canopyIdx = 0;
  char     str_value[ZVENDOR_STR_MAX_SIZE + 5];
  uint8_t * str_pvalue = (uint8_t *)str_value;
  uint16_t i_value = 0;
  Attr_Query_t attrqtype = attr_unknown;
  
  for(canopyIdx=0; canopyIdx < GetCanopyParamCount(); canopyIdx++)
  {
    if ( IsCanopyAttributeVendorType( canopyIdx, &error) == true)
    {
      if ( error != 0)
      {
         debug_printf(debug_level1, "\r\nupdate_usercfg_structure_from_config_object error 1\n");
         continue;
      }
      attributeNumber = GetCanopyAttrNumFromIndex( canopyIdx, &error);
      if ( error != 0 )
      {
        debug_printf(debug_level1, "\r\nupdate_usercfg_structure_from_config_object error 2\n");
        continue;
      }
      bucketIdx = GetBucketIndex(attributeNumber);
      if ( bucketIdx == 0xFF )
      {
         debug_printf(debug_level1, "\r\nupdate_usercfg_structure_from_config_object error 3\n");
         continue;
      }
      attrqtype = GetAttributeQType(attributeNumber);
      if (attrqtype == attr_unknown)
      {
         debug_printf(debug_level1, "\r\nupdate_usercfg_structure_from_config_object error 4 attr:%d\n", attributeNumber);
         continue;
      }
      if (attr_string != attrqtype)
      {
         if (attrqtype == attr_intbyte)
         {
            if (USER_CFG_OK != zuser_cfg_get_param_value(bucketIdx, (uint8_t *)&i_value, 1, numeric_type))
            {
               debug_printf(debug_level1, "\r\nupdate_usercfg_structure_from_config_object error 5 attr:%d\n", attributeNumber);
               continue;
            }
            GenericParamSetInt(attributeNumber, i_value, false);
         }
         else if (attrqtype == attr_intword)
         {
            if (USER_CFG_OK != zuser_cfg_get_param_value(bucketIdx, (uint8_t *)&i_value, 2, numeric_type))
            {
               debug_printf(debug_level1, "\r\nupdate_usercfg_structure_from_config_object error 6 attr:%d\n", attributeNumber);
               continue;
            }
            GenericParamSetInt(attributeNumber, i_value, false);
         }
         else
         {
            debug_printf(debug_level1, "\r\nupdate_user_cfg_structure_from_config_object error unsupported param int type attr:%d\n", attributeNumber);
            continue;
         }
      }
      else
      {
         uint8_t slen = strlen(str_value);
         
         if ( USER_CFG_OK != zuser_cfg_get_param_value(bucketIdx, str_pvalue, slen, string_type) )
         {
            debug_printf(debug_level1, "\r\nupdate_usercfg_structure_from_config_object error 7\n");
            continue;
         }
         GenericParamSetString(attributeNumber, (char *)str_pvalue, true);
      }
      boot_up = 1;
    }
  }
}

void update_config_object_new_param_str(uint16_t att_num, uint8_t * value)
{
   uint16_t bucketIdx = 0;
   uint8_t error = 0;
   Attr_Query_t attrqtype = attr_unknown;

   if ( boot_up == 1)
   {
      bucketIdx = GetBucketIndex(att_num);
      if (bucketIdx == 0xFF)
      {
         debug_printf(debug_level1, "\r\nupdate_config_object_new_param_str : bad attr: %d\n", att_num);
         error = 1;
      }
      if (error == 0)
      {
         attrqtype = GetAttributeQType(att_num);
         if (attrqtype == attr_unknown)
         {
            debug_printf(debug_level1, "\r\nupdate_config_object_new_param_str: error 1 attr:%d\n", att_num);
            error = 1;
         }
      }
      if (error == 0)
      {
         if (attrqtype != attr_string)
         {
            debug_printf(debug_level1, "\r\nupdate_config_object_new_param_str: attr:%d is not a string attribute\n", att_num);
            error = 1;
         }
      }
      if ( error == 0)
      {
         uint8_t slen = 0;
         slen = strlen((char*)value);
         if (USER_CFG_OK != zuser_cfg_set_param_value(bucketIdx, value, slen, string_type))
         {
            debug_printf(debug_level1,"\r\nupdate_config_object_new_param_st error for string idx: %d attr: %d\n", bucketIdx, att_num);
         }
      }
   }
}


//update config object value for new parameters. as updating value in each screen now updates user_cfg structure value
void update_config_object_new_param_int(uint16_t att_num, uint32_t value)
{
   uint16_t bucketIdx = GetBucketIndex(att_num);
   Attr_Query_t attrqtype = attr_unknown;

   if (boot_up == 1)
   {
      attrqtype = GetAttributeQType(att_num);
      if ( attrqtype == attr_string || attrqtype == attr_unknown)
      {
         debug_printf(debug_level1,"\r\n Error update_config_object_new_param_int str not valid Qtype for attr:%d\n", att_num); 
      }
      else
      {
         if (attrqtype == attr_intbyte)
         {
            uint8_t * lv = (uint8_t*)&value;
            if ( USER_CFG_OK != zuser_cfg_set_param_value(bucketIdx, lv, 1, numeric_type))
              debug_printf(debug_level1, "\r\nError update_config_object_new_param_int error 1 attr:%d\n", att_num);
         }
         else if (attrqtype == attr_intword) 
         {
            uint8_t * lv = (uint8_t*)&value;
            if ( USER_CFG_OK != zuser_cfg_set_param_value(bucketIdx, lv, 2, numeric_type))
              debug_printf(debug_level1, "\r\nError update_config_object_new_param_int error 2 attr:%d\n", att_num);
         }
         else
         {
            debug_printf(debug_level1,"\r\nupdate_config_object_new_param_int error for int idx: %d attr: %d\n", bucketIdx, value);
         }
      }
   }
}

// write custom default value to flash for new parameters
// This function is only for vendor type params.
void write_custom_default_new_parameter(void)
{
  uint16_t  attributeNumber = 0;
  uint8_t   error = 0;
  uint16_t  param_list_size = 0;
  char      ctemp[ZVENDOR_STR_MAX_SIZE + 1];
  uint32_t  i_value = 0;
  uint16_t  cpIdx = 0;
  uint16_t  canopyIdx = 0;
  uint16_t  bucketIdx = 0;
  Attr_Query_t attrqtype = attr_unknown;

  param_list_size = ConfigParam::GetParametersSize();

  for ( cpIdx = 0; cpIdx < param_list_size; cpIdx ++)
  {
     attributeNumber = GenericGetAttributeByName((char *)ConfigParam::GetParameters()[cpIdx].param_name.c_str());
     if ( attributeNumber == 0 )
     {
        debug_printf(debug_level1, "\r\nwrite_custom_default_new_parameter error 0\n");
        continue;
     }
     canopyIdx = GetCanopyIndexFromAttrNum(attributeNumber, &error);
     if ( error != 0 )
     {
        debug_printf(debug_level1, "\r\nwrite_custom_default_new_parameter error 1 attr: %d\n", attributeNumber);
        continue;
     }
     if (IsCanopyAttributeVendorType( canopyIdx, &error))
     {
        if ( error != 0) 
        {
           debug_printf(debug_level1, "\r\nwrite_custom_default_new_parameter error 2 attr: %d\n", attributeNumber);
           continue;
        }
        attrqtype = GetAttributeQType(attributeNumber);
        if (attrqtype == attr_unknown)
        {
           debug_printf(debug_level1, "\r\nwrite_custom_default_new_parameter error 2 attr: %d\n", attributeNumber);
           continue;
        }
        bucketIdx = GetBucketIndex( attributeNumber );
        if ( attr_string != attrqtype )
        {
           i_value = GenericParamGetInt( attributeNumber );
           if ( attr_intbyte == attrqtype )
           {
              uint8_t * lv = (uint8_t*)&i_value;
              user_cfg_set_customdefault_param_value (bucketIdx, lv, 1, numeric_type);
           }
           else if (attr_intword == attrqtype)
           {
              uint8_t * lv = (uint8_t*)&i_value;
              user_cfg_set_customdefault_param_value(bucketIdx, lv, 2, numeric_type);
           }
           else
           {
              debug_printf(debug_level1, "\r\nwrite_custom_default_new_parameter unsupported int type attr:%d\n", attributeNumber);
              continue;
           }
        }
        else
        {
           if ( GenericParamGetString( attributeNumber, (uint32_t *)&ctemp ) == false )
           {
              debug_printf(debug_level1, "\r\nwrite_custom_default_new_parameter error 3 attr: %d\n", attributeNumber);
              continue;
           }
           uint8_t slen = strlen((char *)ctemp);
           if (slen > ZVENDOR_STR_MAX_SIZE)
           {
              debug_printf(debug_level1, "\r\nwrite_custom_default_new_parameter error 4 slen:%d attr:%d\n", slen, attributeNumber);
              slen = ZVENDOR_STR_MAX_SIZE;
           }
           user_cfg_set_customdefault_param_value(bucketIdx, (uint8_t*)&ctemp, slen, string_type );
        }
     }
  } // for
  writetoflash();
}

// read custom default value from flash for vendor parameters
// and places value into bucket memory.
void read_custom_default_new_parameter(void)
{
  uint8_t    error = 0;
  uint16_t   attributeNumber = 0;
  uint16_t   param_list_size = 0;
  uint16_t   cpIdx = 0;
  uint16_t   bucketIdx = 0;
  uint16_t   canopyIdx = 0;
  uint16_t    i_value = 0;
  char       str_value[ZVENDOR_STR_MAX_SIZE + 1 ];
  uint8_t *  str_pvalue = (uint8_t *) str_value;
  Attr_Query_t attrqtype = attr_unknown;

  //read custom default value from flash
  custom_parameter_read();

  param_list_size = ConfigParam::GetParametersSize();

  for (cpIdx = 0; cpIdx < param_list_size; cpIdx++)
  {
     attributeNumber = GenericGetAttributeByName((char *)ConfigParam::GetParameters()[cpIdx].param_name.c_str());
     if ( attributeNumber == 0)
     {
        debug_printf(debug_level1, "\r\nread_custom_default_new_parameter error 1\n");
        continue;
     }
     canopyIdx = GetCanopyIndexFromAttrNum(attributeNumber, &error);
     if ( error != 0 )
     {
        debug_printf(debug_level1, "\r\nread_custom_default_new_parameter error 1 attr:%d\n", attributeNumber);
        continue;
     }
     if (IsCanopyAttributeVendorType(canopyIdx, &error))
     {
        if ( error != 0 )
        {
           debug_printf(debug_level1, "\r\nread_custom_default_new_parameter error 2 attr:%d\n", attributeNumber);
           continue;
        }
        attrqtype = GetAttributeQType(attributeNumber);
        if (attrqtype == attr_unknown)
        {
           debug_printf(debug_level1, "\r\nread_custom_default_new_parameter error 3 attr:%d\n", attributeNumber);
           continue;
        }
        bucketIdx = GetBucketIndex( attributeNumber );
        if ( attr_string != attrqtype ) 
        {
           if (attr_intbyte == attrqtype)
           {
              if ( USER_CFG_OK != user_cfg_get_customdefault_parameter_value(bucketIdx, (uint8_t *)&i_value, 1, numeric_type))
              {
                debug_printf(debug_level1, "\r\nread_custom_default_new_parameter_error error 1 attr:%d\n", attributeNumber);
              }
              i_value = (uint8_t) (i_value & 0x00FF);
           }
           else if (attr_intword == attrqtype)
           {
              if ( USER_CFG_OK != user_cfg_get_customdefault_parameter_value(bucketIdx, (uint8_t *)&i_value, 2, numeric_type))
                debug_printf(debug_level1, "\r\nread_custom_default_new_parameter_error error 2 attr:%d\n", attributeNumber);
           }
           else
           {
              debug_printf(debug_level1, "\r\nread_custom_default_new_parameter_error unsupported numerictype attr:%d\n", attributeNumber);
              continue;
           }
           GenericParamSetInt(attributeNumber, i_value, false);
        }
        else
        {
           uint8_t slen = strlen(str_value);
           if ( USER_CFG_OK != user_cfg_get_customdefault_parameter_value(bucketIdx, str_pvalue, slen, string_type))
           {
              debug_printf(debug_level1, "\r\nread_custom_default_new_parameter error 4 attr:%d\n", attributeNumber);
              continue;
           }
           GenericParamSetString(attributeNumber, (char *) str_pvalue, false);
        }
     }
  }
}

/**
 * API: user_cfg_update_att_number()
 */
e_user_cfg_status user_cfg_update_att_number(uint16_t idx, uint16_t att_number)
{
  uint16_t param_list_size = ConfigParam::GetParametersSize();
  if(idx > param_list_size)
  {
    return USER_CFG_UNDEFINED_ERROR;
  }
  ConfigParam::ModifyAttNumber(idx, att_number);
  return USER_CFG_OK;
}

/**
 * API: user_cfg_update_att_name()
 */
e_user_cfg_status user_cfg_update_name(uint16_t att_num,
                                       char* name, 
                                       uint8_t len,
                                       e_name_type type)
{
  std::string new_string(name, len);
  if(ConfigParam::ModifyParamName(att_num, name, type))
  {
    return USER_CFG_OK;
  }
  return USER_CFG_PARAM_NOT_REGISTERED;
}

/**
 * API: user_cfg_update_att_name()
 */

e_user_cfg_status user_cfg_update_type(uint16_t att_num,
                                       param_type_t type, 
                                       c_param_descr_t* param_descr)
{
  ParamDescriptor* cpp_param_descr;
  
  /* Parse param descriptor into c++ Polymorphic descriptor */
  switch(type)
  {
  case PARAM_TYPE_BOOL:
    ParamDescrBool* bDescr = new ParamDescrBool;
    cpp_param_descr = bDescr;
    break;
    
  case PARAM_TYPE_NUMERIC:   
    std::vector<preset_entry_t>* radio_vals = new std::vector<preset_entry_t>;
    for(uint16_t i = 0; i < param_descr->preset_len; i++)
    {
      preset_entry_t rad_val = {param_descr->presets[i].preset_name,
                                param_descr->presets[i].preset_val};
      radio_vals->push_back(rad_val);
    }
    ParamDescrNumeric* nDescr = new ParamDescrNumeric(param_descr->min_val,
                                                      param_descr->max_val,
                                                      param_descr->user_edit,
                                                      param_descr->show_preset,
                                                      param_descr->name,
                                                      *radio_vals);
    cpp_param_descr = nDescr;
    break;
    
  case PARAM_TYPE_CHARACTER:
    std::vector<preset_entry_t>* radio_chars = new std::vector<preset_entry_t>;
    for(uint16_t i = 0; i < param_descr->preset_len; i++)
    {
      preset_entry_t rad_val = {param_descr->presets[i].preset_name,
                                param_descr->presets[i].preset_val};
      radio_chars->push_back(rad_val);
    }
    ParamDescrCharacter* cDescr = new ParamDescrCharacter(param_descr->user_edit,
                                                          param_descr->show_preset,
                                                          param_descr->name,
                                                         *radio_chars);
    cpp_param_descr = cDescr;
    break;
    
  default:
    break;
  }
  
  if(ConfigParam::ModifyParamType(att_num, type, cpp_param_descr))
  {
    return USER_CFG_OK;
  }
  return USER_CFG_PARAM_NOT_REGISTERED;
  
}


/**
 * API: user_cfg_update_att_name()
 */
e_user_cfg_status user_cfg_update_callback(uint16_t att_num,
                                           void     callback(uint32_t))
{
  if(ConfigParam::ModifyParamSetCallback(att_num, callback))
  {
    return USER_CFG_OK;
  }
  return USER_CFG_PARAM_NOT_REGISTERED;
}
  

/**
 * API: user_cfg_add_parameter()
 */
e_user_cfg_status user_cfg_add_parameter(user_cfg_name_t  param_name,
                                         user_cfg_name_t  short_name,
                                         user_cfg_name_t  app_name,
                                         param_type_t     param_type,
                                         uint16_t         att_number,
                                         uint16_t         param_size,
                                         bool             param_sign,
                                         c_param_descr_t* param_descr,
                                         void             set_callback(uint32_t),
                                         void             get_callback(uint32_t*))
{
  
  /* Translate C types into C++ types and classes as safely as possible*/
  
  /* Strings -> direct constructor call fro buffer+length */
  
  std::string cpp_param_name(param_name.name, param_name.len);
  std::string cpp_short_name(short_name.name, short_name.len);
  std::string cpp_app_name(app_name.name, app_name.len);
  
  /* Param descriptor -> based on param_type, manually generate new descriptor*/
  
  ParamDescriptor* cpp_param_descr;

  switch(param_type)
  {
  case PARAM_TYPE_BOOL:
    ParamDescrBool* bDescr = new ParamDescrBool;
    cpp_param_descr = bDescr;
    break;
    
  case PARAM_TYPE_NUMERIC:   
    std::vector<preset_entry_t>* radio_vals = new std::vector<preset_entry_t>;
    for(uint16_t i = 0; i < param_descr->preset_len; i++)
    {
      preset_entry_t rad_val = {param_descr->presets[i].preset_name,
                                param_descr->presets[i].preset_val};
      radio_vals->push_back(rad_val);
    }
    ParamDescrNumeric* nDescr = new ParamDescrNumeric(param_descr->min_val,
                                                      param_descr->max_val,
                                                      param_descr->user_edit,
                                                      param_descr->show_preset,
                                                      param_descr->name,
                                                      *radio_vals);
    cpp_param_descr = nDescr;
    break;
    
  case PARAM_TYPE_CHARACTER:
    std::vector<preset_entry_t>* radio_chars = new std::vector<preset_entry_t>;
    for(uint16_t i = 0; i < param_descr->preset_len; i++)
    {
      preset_entry_t rad_val = {param_descr->presets[i].preset_name,
                                param_descr->presets[i].preset_val};
      radio_chars->push_back(rad_val);
    }
    ParamDescrCharacter* cDescr = new ParamDescrCharacter(param_descr->user_edit,
                                                          param_descr->show_preset,
                                                          param_descr->name,
                                                         *radio_chars);
    cpp_param_descr = cDescr;
    break;
    
  default:
    break;
  }
  
  /* Default value -> direct retrieval from C descriptor */
  uint32_t defval = param_descr->def_val;
  
  ConfigParam::RegisterParam(ConfigParam(cpp_param_name,
                                         cpp_short_name,
                                         cpp_app_name, 
                                         param_type,
                                         att_number,
                                         param_size,
                                         param_sign,
                                         cpp_param_descr, 
                                         defval,
                                         0,
                                         set_callback,
                                         get_callback));
  
  return USER_CFG_OK;
}

/**
 * API: user_cfg_get_att_by_index()
 */
e_user_cfg_status user_cfg_get_att_by_index(uint16_t *att_num, uint16_t idx)
{
  *att_num = ConfigParam::GetAttByIndex(idx);
  if(*att_num != 0xFFFF)
  {
    return USER_CFG_OK;
  }
  return USER_CFG_PARAM_NOT_REGISTERED;
}

/**
 * API: user_cfg_get_index_by_att()
 */
e_user_cfg_status user_cfg_get_index_by_att(uint16_t *idx, uint16_t att_num)
{
  *idx = ConfigParam::GetIndexByAtt(att_num);
  if(*idx != 0xFFFF)
  {
    return USER_CFG_OK;
  }
  return USER_CFG_PARAM_NOT_REGISTERED;
}
void sqtyDelim_cbsetstubfn( uint32_t value )
{
   GenericParamSetInt(0x0888, (uint32_t)value, true);
   GenericParamSetInt(0x0889, (uint32_t)value, true);
   GenericParamSetInt(0x088A, (uint32_t)value, true);
}

void slocDelim_cbsetstubfn( uint32_t value )
{
   GenericParamSetInt(0x0874, (uint32_t)value, true);
   GenericParamSetInt(0x0877, (uint32_t)value, true);
}

void gblMinQtyValue_cbsetstubfn(uint32_t value)
{ 
    uint32_t minqtyvalue = GenericParamGetInt(gblMinQtyValue_attr);
    uint32_t maxqtyvalue = GenericParamGetInt(gblMaxQtyValue_attr);
    uint8_t error = 0;
    uint32_t min_qty_default_value = GetCanopyDefaultValueIntFromAttr(gblMinQtyValue_attr,&error);
    if (error != 0)
    {
      debug_printf(debug_level1, "\r\nMin quantity attribute error 1");
    }
    if(minqtyvalue > maxqtyvalue)
    {
      GenericParamSetInt(gblMinQtyValue_attr,min_qty_default_value,true);
    }

                                                  
} 

void gblMaxQtyValue_cbsetstubfn(uint32_t value)
{
  uint32_t minqtyvalue = GenericParamGetInt(gblMinQtyValue_attr);
  uint32_t maxqtyvalue = GenericParamGetInt(gblMaxQtyValue_attr);
  uint8_t error = 0;
  uint32_t max_qty_default_value = GetCanopyDefaultValueIntFromAttr(gblMaxQtyValue_attr,&error);
  if (error != 0)
  {
    debug_printf(debug_level1, "\r\nMax quantity attribute error 1");
  }
  if(maxqtyvalue < minqtyvalue)
  {
    GenericParamSetInt(gblMaxQtyValue_attr,max_qty_default_value,true);
  }

} 
