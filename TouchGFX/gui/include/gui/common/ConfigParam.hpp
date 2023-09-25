/**
  ******************************************************************************
  * @file    ConfigParam.hpp
  * @author  SIANA Systems
  * @date    04/21/2021
  * @brief   Main class for Zebra application parameter registering.
  *
  * The ConfigParam header contains all the classes and methods needed to
  * subscribe parameter information to be public. The approach followed by
  * this class is similar to the used on ZebraApplication.
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
#ifndef __CONFIG_PARAM_HPP__
#define __CONFIG_PARAM_HPP__

#include <string>
#include <vector>
#include <algorithm>
#include <gui/common/FrontendApplication.hpp>
#include <gui/common/ParamDescriptor.hpp>
#include <gui/common/param_types.h>
#ifndef SIMULATOR
#include "canopyAuto_usercfg.h"
#else
#include <gui/simulator/canopyAuto_usercfg.h>
#endif


/**
 * @brief Forward declaration for ParamData class.
 *
 * ParamData class resides below ConfigParam, and
 * currently there is a circular dependency between ParamData
 * and ConfigParam.
 */
class ParamData;

/*!
 * @brief ConfigParam static class
 *
 * Main registration class for the Zebra Application API.
 * This class contains a static parameter list with links
 * to certain applications, that can be used to generate 
 * dynamic configuration menus easily!
 */
class ConfigParam
{
public:
  /**
  * @brief Registers a new parameter
  *
  * Appends the parameter to a static list that can be consulted
  * globally before runtime. This parameter contains enough info
  * to be used to dynamically populate a configuration menu.
  *
  * @param param Parameter details
  */
  inline static void RegisterParam(ConfigParam param)
  {
    parameters().push_back(param);
  }
  /**
  * @brief Gets the configuration parameters of a specific application
  *
  * @param app_name the name of the application
  * @retval std::vector<ConfigParam>
  */
  inline static std::vector<ConfigParam> GetAppParameters(std::string app_name)
  {
    std::vector<ConfigParam> params;
  
    for(ConfigParam param : parameters())
    {
      if(!(param.app_name.compare(app_name)))
      {
        params.push_back(param);
      }
    }
    return params;
  }
  /**
  * @brief Gets the configuration parameters of all application
  *
  * @retval std::vector<ConfigParam>
  */
  inline static std::vector<ConfigParam> GetParameters(void)
  {
    return parameters();
  }
  /**
  * @brief Gets the names of all applications that have registered at
  * least one parameter
  *
  * @retval std::vector<std::string> List with all application names
  * that have registered at least one parameter
  */
  inline static std::vector<std::string> GetConfigAppList(void)
  {
    std::vector<std::string> apps;
    std::vector<std::string>::iterator it;
    
    for(ConfigParam param : parameters())
    {
      it = find (apps.begin(), apps.end(), param.app_name);
      if (it == apps.end())
      {
        /* Application is not listed already, add to list */
        apps.push_back(param.app_name);
      }
    }
    return apps;
  }
  /**
  * @brief Computes a hash of all registered parameters. Used to
  * detect potential changes.
  *
  * @retval uint32_t hash
  */
  inline static uint32_t GetParameterHash(void)
  {
    uint32_t cs = 0;
    /* Generates a semi-unique hash based on the description of the 
        parameters */
    for(ConfigParam param : parameters())
    {
      for(uint8_t i = 0; i < param.param_name.length(); i++)
      {
        cs *= 13;
        cs += param.param_name[i];
        cs *= 7;
        cs %= 0x7FFFFFFF;
      }
      for(uint8_t i = 0; i < param.app_name.length(); i++)
      {
        cs *= 7;
        cs += param.app_name[i];
        cs *= 13;
        cs %= 0x7FFFFFFf;
      }
      cs += (uint32_t)(param.default_value + (param.param_type << 16));
    }
    return cs;
  }
  /**
  * @brief Gets the total amount of registered parameters
  *
  * @retval Number of registered parameters
  */
  inline static uint16_t GetParametersSize(void)
  {
    return parameters().size();
  }
  /**
  * @brief Gets the parameter reference
  *
  * @param app_name the name of the application
  * @param param_name Name of the parameter
  * @retval parameter index
  */
   inline static uint16_t GetParamIndex(std::string param_name, std::string app_name)
  {
    uint16_t sz = parameters().size();
      for(uint16_t i = 0; i < sz; i++)
      {
        ConfigParam param = parameters()[i];
        if((!(param.param_name.compare(param_name))) &&
            (!(param.app_name.compare(app_name))))
        {
          return i;
        }
      }
      return 0xFFFF;
  }
  
  /**
  * @brief Gets the attribute number of a parameter by the index
  *
  * @param idx Index of the parameter
  * @retval Attribute number, or 0xFFFF if index not valid
  */
  inline static uint16_t GetAttByIndex (uint16_t idx)
  {
    if (idx < parameters().size())
    {
      return parameters()[idx].att_number;
    }
    return 0xFFFF;
  }
  
  /**
  * @brief Gets the index of a parameter by the attribute number
  * Note: attribute numbers may repeat between parameters, so the first index
  * found is returned
  *
  * @param att_number Attribute number of the parameter
  * @retval parameter index, or 0xFFFF if not found
  */
  inline static uint16_t GetIndexByAtt(uint16_t att_number)
  {
    uint16_t sz = parameters().size();
    for(uint16_t i = 0; i < sz; i++)
    {
      ConfigParam param = parameters()[i];
      if(param.att_number == att_number)
      {
        return i;
      }
    }
    return 0xFFFF;
  }
  
  /**
  * @brief Gets the param_type of a parameter by the index
  *
  * @param idx Index of the parameter
  * @retval param_type
  */
  inline static param_type_t GetParamType (uint16_t idx)
  {
      return parameters()[idx].param_type;
  }
  
  /**
  * @brief Modifies the attribute number of a specific ConfigParam
  *
  * @param app_name the name of the application
  * @param param_name Name of the parameter
  * @retval None
  */
  inline static void ModifyAttNumber(uint16_t idx, uint16_t att_number)
  {
    if (idx < parameters().size())
    {
      parameters()[idx].att_number = att_number;
    }
  }

 /**
  * @brief Modifies any of the names of a specific ConfigParam
  *
  * @param att_number attribute number of the parameter to modify
  * @param name New name of the parameter
  * @param name_type Any of the values specified in param_name_type
  * @retval true if name was replaced. False if att number doesn't exist
  */
  inline static bool ModifyParamName(uint16_t att_number,
                                     std::string name,
                                     e_name_type name_type)
  {
    for(uint16_t i = 0; i < parameters().size(); i++)
    {
      if (parameters()[i].att_number == att_number)
      {
        switch(name_type)
        {
        case NAME_TYPE_PARAM:
          parameters()[i].param_name.assign(name);
          break;
        case NAME_TYPE_SHORT:
          parameters()[i].short_name.assign(name);
          break;
        case NAME_TYPE_APP:
          parameters()[i].app_name.assign(name);
          break;
        }
        return true;
      }
    }
    return false;
  }
  
 /**
  * @brief Modifies any of the names of a specific ConfigParam
  *
  * @param att_number attribute number of the parameter to modify
  * @param type Update parameter type for the parameter
  * @param param_descr Updates parameter descriptor
  * @retval true if type was replaced. False if att number doesn't exist
  */
  inline static bool ModifyParamType(uint16_t att_number,
                                     param_type_t param_type,
                                     ParamDescriptor * param_descr)
  {
    for(uint16_t i = 0; i < parameters().size(); i++)
    {
      if (parameters()[i].att_number == att_number)
      {
        parameters()[i].param_type = param_type;
        ParamDescriptor* old_desc = parameters()[i].param_descr;
        parameters()[i].param_descr = param_descr;
        if(parameters()[i].custom_descriptor)
        {
          delete old_desc;
        }
        parameters()[i].custom_descriptor = true;
        return true;
      }
    }
    return false;
  }

 /**
  * @brief Modifies a specific parameter's on edit callback
  *
  * @param att_number Attribute number of the parameter to edit
  * @param callback function pointer of the callback
  * @retval true if callback was replaced. False if att number doesn't exist
  */
  inline static bool ModifyParamSetCallback(uint16_t att_number,
                                         void set_callback(uint32_t))
  {
    for(uint16_t i = 0; i < parameters().size(); i++)
    {
      if (parameters()[i].att_number == att_number)
      {
        parameters()[i].set_callback = set_callback;
        return true;
      }
    }
    return false;
  }
  
 /**
  * @brief Sorts the parameter vector
  *
  * @retval None
  */
  inline static void Sort(void)
  {
    /* Sort by priority */
    std::sort(
      parameters().begin(), 
      parameters().end(), 
      ConfigParam::priority_sorter
    );
  }
  
  /**
  * @brief Creates a new ConfigParam object. The object contains
  * all information needed to be used to render dynamically
  * configuration lists
  *
  * @param param_name Parameter name
  * @param short_name Short version of the parameter name. Used
  * for renders that need less space
  * @param app_name Name of the application that requires this
  * parameter
  * @param param_type Type of parameter. Used to display widgets
  * related to the parameter
  * @param att_number Attribute number for Host API
  * @param param_size Size of the parameter in bytes.
  * @param param_descr Container that holds specific information
  * about what to display
  * @param default_value Default value of the parameter
  * @param priority Priority of the parameter
  * @param callback Pointer to function that updates the parameter
  * in case it's changed
  * @retval std::vector<ConfigParam>
  */
  ConfigParam(std::string param_name,
              std::string short_name,
              std::string app_name, 
              param_type_t param_type,
              uint16_t att_number,
              uint16_t param_size,
              bool param_sign,
              ParamDescriptor * param_descr,
              uint32_t default_value,
              uint16_t priority,
              void set_callback(uint32_t),
              void get_callback(uint32_t*)) : 
  param_name(param_name),
  short_name(short_name),
  app_name(app_name),
  param_type(param_type),
  att_number(att_number),
  param_size(param_size),
  param_sign(param_sign),
  param_descr(param_descr),
  default_value(default_value),
  priority(priority),
  set_callback(set_callback),
  get_callback(get_callback){ this->custom_descriptor = false; }
  /**
  * @brief Parameter name
  */
  std::string param_name;
  /**
  * @brief Short version of the parameter name. Used
  * for renders that need less space
  */
  std::string short_name;
  /**
  * @brief Name of the application that requires this
  * parameter
  */
  std::string app_name;
  /**
  * @brief Type of parameter. Used to display widgets
  * related to the parameter
  */
  param_type_t param_type;
  /**
  * @brief Attribute Number for Host API.
  */
  uint16_t att_number;
  /**
  * @brief Size of parameter in bytes.
  */
  uint16_t param_size;
 /**
  * @param param_sign True if a numeric param is signed.
  */
  bool param_sign;
  /**
  * @brief Container that holds specific information
  * about what to display
  */
  ParamDescriptor * param_descr;
  /**
  * @brief Default value of the parameter - for string parameters, index of the
  * default value in the Parameter Descriptor
  */
  uint32_t default_value;
  /**
   * @brief Internal flag for custom Descriptor
   */
  bool custom_descriptor;
  /**
  * @brief Priority
  *
  * This number is a priority weight for the parameter.
  * It can be used to sort the parameters displayed on config menu
  */
  uint16_t priority;
  /**
   * @brief Pointer to function that updates the parameter in backend.
   */
  void (*set_callback)(uint32_t);
  /**
   * @brief Pointer to function that retrieves the parameter from backend.
   */
  void (*get_callback)(uint32_t*);
  
private:
  /**
  * @brief Static list that contains the description of all
  * parameters
  */ 
  static std::vector<ConfigParam> & parameters();
  /**
  * @brief Compares two ConfigParam priorities
  *
  * @param a ConfigParam with priority
  * @param b ConfigParam with priority
  * @retval true if a priority is lower. False otherwise
  */
  static bool priority_sorter(ConfigParam a, ConfigParam b)
  {
    return a.priority < b.priority;
  }
};
/**
 * @brief Helper class for static constructor
 * 
 * The ParamData class implements a C++ static constructor by
 * instantiating it before runtime.
 */
class ParamData
{
public:
/**
  *
  * @brief ParamData constructor
  *
  * Initializes the ConfigParam description values statically
  *
  * @param param_name Parameter name
  * @param short_name Short version of the parameter name. Used
  * for renders that need less space
  * @param app_name Name of the application that requires this
  * parameter
  * @param param_type Type of parameter. Used to display widgets
  * related to the parameter
  * @param att_number Attribute number for Host API
  * @param param_size Size of the parameter in bytes.
  * @param param_sign True if a numeric param is signed.
  * @param param_descr Container that holds specific information
  * about what to display
  * @param default_value Default value/index of the parameter
  * @param priority Priority value of the parameter 
  * @param callback Pointer to function that updates the parameter
  * in case it's changed
  * @retval std::vector<ConfigParam>
  */
  ParamData(
    std::string       param_name,
    std::string       short_name,
    std::string       app_name,
    param_type_t      param_type,
    uint16_t          att_number,
    uint16_t          param_size,
    bool              param_sign,
    ParamDescriptor * param_descr,
    uint32_t          default_value,
    uint16_t          priority,
    void              set_callback(uint32_t),
    void              get_callback(uint32_t*)
  )
  {
    ConfigParam::RegisterParam(
      ConfigParam(param_name,
        short_name,
        app_name, 
        param_type,
        att_number,
        param_size,
        param_sign,
        param_descr, 
        default_value,
        priority,
        set_callback,
        get_callback
      )
    );    
  }
};
/**
 * @brief Adds a ConfigParam to the static list.
 */

#define REGISTER_PARAMETER(type, name, short_name, app_name, param_type, att_number, param_size, param_sign, param_descr, default_value, priority, set_callback, get_callback) \
                                class type {public: static ParamData RegisterParam;}; \
                                  ParamData type::RegisterParam(name, short_name, app_name, param_type, att_number, param_size, param_sign, &param_descr, default_value, priority, set_callback, get_callback);
                                  
#define REGISTER_DESC_BOOL(name) ParamDescrBool name;

/* Manual Edit */
#ifdef _VS2022 
#define CVAL(ch, val) { #val , ch }
#else
#define CVAL(ch, val...) { #val , ch }
#endif
#define REGISTER_DESC_CHAR(name, edit, show_preset, valname, ...) \
                                  std::vector<preset_entry_t> name##Opts = {__VA_ARGS__};\
                                  ParamDescrCharacter name ( edit, show_preset, valname, name##Opts );
/* Manual Edit */
#ifdef _VS2022
#define NVAL(ch, val) { #val , ch }
#else
#define NVAL(ch, val...) { #val , ch }
#endif                           

#define REGISTER_DESC_NUM(name, min, max, edit, show_preset, valname, ...) \
                                  std::vector<preset_entry_t> name##Opts = {__VA_ARGS__};\
                                  ParamDescrNumeric name ( min, max, edit, show_preset, valname, name##Opts );

#define _STR(...) #__VA_ARGS__ //quotes around __VA_ARGS__ e.g. 'arg1,arg2,arg3'
#define SVAL(str, val) { _STR(val) , _STR(str) } // SVAL(1,one) => 'one','1'
#define REGISTER_DESC_STRING(name, edit, show_preset, valname, ...) \
                                  std::vector<preset_string_t> name##Opts = {__VA_ARGS__};\
                                  ParamDescrString name ( edit, show_preset, valname, name##Opts ); 
#endif
