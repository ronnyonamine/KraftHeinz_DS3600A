/**
  ******************************************************************************
  * @file    ParamDescriptor.hpp
  * @author  SIANA Systems
  * @date    04/21/2021
  * @brief   Container for application parameters
  *
  * The ParamDescriptor interface is a container class that holds information
  * about the parameter type. For example, a discrete parameter that can be
  * selected from multiple choices using radio buttons should contain info
  * about the multiple choices and a default value.
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
#ifndef __PARAM_DESCRIPTOR_HPP__
#define __PARAM_DESCRIPTOR_HPP__

#include <string>
#include <vector>

/*!
 * @brief Defines an entry preset in order to fill a single entity (int/char)
 * preset list
 */
typedef struct
{
  std::string preset_name;
  uint32_t preset_value;
} preset_entry_t;

/*!
 * @brief Defines an entry preset in order to fill a multi-entity (string)
 * preset list
 */
typedef struct
{
  std::string preset_name;
  std::string preset_str;
} preset_string_t;

/*!
 * @brief ParamDescriptor interface
 *
 * The ParamDescriptor interface defines virtual methods needed
 * for external classes to get information about how the parameter
 * should be rendered.
 */
class ParamDescriptor
{
public:
  /**
  * @brief Returns the labels of radio buttons
  *
  * If the parameter includes a list of parameter choices that
  * can be selected using a radio button, each element consist
  * of a label. This method returns the selection list
  *
  * @retval List with choices names
  */
  virtual std::vector<std::string> GetRadioNames() = 0;
  /**
  * @brief Returns if the parameter can be edited
  *
  * Some parameters can be edited using a textbox (i.e. timeouts,
  * characters, etc). This function informs if the parameter
  * can be edited this way.
  *
  * @retval true if the parameter can be edited using textbox.
  * False otherwise
  */
  virtual bool isUserCofigurable() = 0;
  /**
  * @brief Returns if the parameter has predefined configuration values
  *
  * Some parameters can be edited using a radio menu. This function 
  * informs if the parameter can be edited this way.
  *
  * @retval true if the parameter can be edited using a radio menu.
  * False otherwise
  */
  virtual bool hasPresetValues() = 0;
  /**
  * @brief Informs whether the parameter has limits or not
  *
  * @retval true if the parameter contains limits. False otherwise
  */
  virtual bool hasValueRange() = 0;
  /**
  * @brief Gets the upper limit for the parameter
  * Use along with hasValueRange() to see if the
  * parameter is bounded
  *
  * @retval Maximum value possible
  */
  virtual uint32_t getRangeMin() = 0;
  /**
  * @brief Gets the lower limit for the parameter.
  * Use along with hasValueRange() to see if the
  * parameter is bounded
  *
  * @retval Minimum value possible
  */
  virtual uint32_t getRangeMax() = 0;
  /**
  * @brief Gets the string name of the parameter
  *
  * @retval Name of the parameter
  */
  virtual std::string getParamLabel() = 0;
  /**
  * @brief Returns a list of preset values. Valid only
  * if the parameter allows multiple single-entity options.
  *
  * @retval List with available preset values
  */
  virtual std::vector<uint32_t> GetPresetValues() = 0;
  
  /**
  * @brief Returns a list of preset strings. Valid only
  * if the parameter allows multiple string options.
  *
  * @retval List with available preset strings
  */
  virtual std::vector<std::string> GetPresetStrings() = 0;
  /**
  * @brief ParamDescriptor constructor
  */
  ParamDescriptor() { };
  /**
  * @brief ParamDescriptor destructor
  */
  virtual ~ParamDescriptor() = default;
};
/*!
 * @brief ParamDescrBool concrete class
 *
 * The ParamDescriptorBool implements ParamDescriptor
 * to describe a boolean parameter. This parameter is
 * represented as a radio button with Yes/No options
 */
class ParamDescrBool: public ParamDescriptor
{
public:
  /**
  * @brief ParamDescrBool constructor
  */
  ParamDescrBool()
  {

  }
  /**
  * @brief ParamDescrBool destructor
  */
  ~ParamDescrBool() throw() { }
  /*! @copydoc ParamDescriptor::isUserConfigurable() */
  bool isUserCofigurable()
  {
    return false;
  }
  /*! @copydoc ParamDescriptor::hasPresetValues() */
  bool hasPresetValues()
  {
    return true; /* It is the only way to configure a bool*/
  }
  /*! @copydoc ParamDescriptor::hasValueRange() */
  bool hasValueRange()
  {
    return false;
  }
  /*! @copydoc ParamDescriptor::getRangeMin() */
  uint32_t getRangeMin()
  {
    return 0;
  }
  /*! @copydoc ParamDescriptor::getRangeMax() */
  uint32_t getRangeMax()
  {
    return 0x01;
  }
  /*! @copydoc ParamDescriptor::GetRadioNames() */
  std::vector<std::string> GetRadioNames()
  {
    std::vector<std::string> retval = {"None"};
    return retval;
  }
  /*! @copydoc ParamDescriptor::getParamLabel() */
  std::string getParamLabel()
  {
    std::string retval = {"None"};
    return retval;
  }
  /*! @copydoc ParamDescriptor::GetPresetValues() */
  std::vector<uint32_t> GetPresetValues()
  {
    std::vector<uint32_t> retval = {0x00};
    return retval;
  }
  /*! @copydoc ParamDescriptor::GetPresetStrings() */
  std::vector<std::string> GetPresetStrings()
  {
    std::vector<std::string> radioValues = {""};
    return radioValues;
  }
};
/*!
 * @brief ParamDescrNumeric concrete class
 *
 * The ParamDescriptorNumeric implements ParamDescriptor
 * to describe an integer parameter. This parameter can
 * be edited using a text box or can be selected from a 
 * list of presets. Its representation is a textbox plus
 * a radio button list with all presets.
 */
class ParamDescrNumeric: public ParamDescriptor
{
public:
  /*! @copydoc ParamDescriptor::GetRadioNames() */
  std::vector<std::string> GetRadioNames()
  {
    std::vector<std::string> radioNames;
    for(preset_entry_t preset : this->presets)
    {
      radioNames.push_back(preset.preset_name);
    }
    return radioNames;
  }
  /*! @copydoc ParamDescriptor::isUserConfigurable() */
  bool isUserCofigurable()
  {
    return is_edit;
  }
  /*! @copydoc ParamDescriptor::hasPresetValues() */
  bool hasPresetValues()
  {
    return has_preset; 
  }
  /*! @copydoc ParamDescriptor::hasValueRange() */
  bool hasValueRange()
  {
    return true;
  }
  /*! @copydoc ParamDescriptor::getRangeMin() */
  uint32_t getRangeMin()
  {
    return this->min;
  }
  /*! @copydoc ParamDescriptor::getRangeMax() */
  uint32_t getRangeMax()
  {
    return this->max;
  }
  /*! @copydoc ParamDescriptor::getParamLabel() */
  std::string getParamLabel()
  {
    return val_name;
  }
  /*! @copydoc ParamDescriptor::GetPresetValues() */
  std::vector<uint32_t> GetPresetValues()
  {
    std::vector<uint32_t> preValues;
    for(preset_entry_t preset : this->presets)
    {
      preValues.push_back(preset.preset_value);
    }
    return preValues;
  }
  /*! @copydoc ParamDescriptor::GetPresetStrings() */
  std::vector<std::string> GetPresetStrings()
  {
    std::vector<std::string> radioValues = {""};
    return radioValues;
  }
  /**
  * @brief Min boundary of the number
  */
  uint32_t min;
  /**
  * @brief Max boundary of the number
  */
  uint32_t max;
  /**
  * @brief Defines if the parameter is editable
  */
  bool is_edit;
    /**
  * @brief Defines if the parameter can show presets
  */
  bool has_preset;
  /**
  * @brief Parameter name
  */
  std::string val_name;
  /**
  * @brief List of numeric presets
  */
  std::vector<preset_entry_t> presets;
  /**
  * @brief ParamDescrNumeric constructor
  *
  * @param minval Min boundary of the number
  * @param maxval Max boundary of the number
  * @param valname Parameter name
  * @param prevect List of numeric presets
  */
  ParamDescrNumeric(
    uint32_t minval, 
    uint32_t maxval,
    bool editable,
	bool has_presets,
    std::string valname, 
    std::vector<preset_entry_t> prevect)
  {
    min = minval;
    max = maxval;
    val_name = valname;
    presets = prevect;
    is_edit = editable;
	has_preset = has_presets;
  }
  /**
  * @brief ParamDescrNumeric constructor
  */
  ~ParamDescrNumeric() throw() { }
};
/*!
 * @brief ParamDescrCharacter concrete class
 *
 * The ParamDescriptorCharacter implements ParamDescriptor
 * to describe a character parameter. Similar to ParamDescrNumeric,
 * the character can be edited using the textbox or can be selected
 * from a list of presets.
 */
class ParamDescrCharacter: public ParamDescriptor
{
public:
  /*! @copydoc ParamDescriptor::GetRadioNames() */
  std::vector<std::string> GetRadioNames()
  {
    std::vector<std::string> radioNames;
    for(preset_entry_t preset : this->presets)
    {
      radioNames.push_back(preset.preset_name);
    }
    return radioNames;
  }
  /*! @copydoc ParamDescriptor::isUserConfigurable() */ 
  bool isUserCofigurable()
  {
    return is_edit;
  }
  /*! @copydoc ParamDescriptor::hasPresetValues() */
  bool hasPresetValues()
  {
    return has_preset; 
  }
  /*! @copydoc ParamDescriptor::hasValueRange() */
  bool hasValueRange()
  {
    return false;
  }
  /*! @copydoc ParamDescriptor::getRangeMin() */
  uint32_t getRangeMin()
  {
    return 0x00;
  }
  /*! @copydoc ParamDescriptor::getRangeMax() */
  uint32_t getRangeMax()
  {
    return 0xFF;
  }
  /*! @copydoc ParamDescriptor::getParamLabel() */
  std::string getParamLabel()
  {
    return val_name;
  }
  /*! @copydoc ParamDescriptor::GetPresetValues() */
  std::vector<uint32_t> GetPresetValues()
  {
    std::vector<uint32_t> preValues;
    for(preset_entry_t preset : this->presets)
    {
      preValues.push_back(preset.preset_value);
    }
    return preValues;
  }
  /*! @copydoc ParamDescriptor::GetPresetStrings() */
  std::vector<std::string> GetPresetStrings()
  {
    std::vector<std::string> radioValues = {""};
    return radioValues;
  }
  /**
  * @brief Defines if the parameter is editable
  */
  bool is_edit;
  /**
  * @brief Defines if the parameter can show presets
  */
  bool has_preset;
  /**
  * @brief String name of the parameter
  */
  std::string val_name;
  /**
  * @brief List of presets used to display on screen
  */
  std::vector<preset_entry_t> presets;
  /**
  * @brief ParamDescrCharacter constructor
  *
  * @param valname Name of the variable
  * @param prevect Vector with presets
  */
  ParamDescrCharacter(bool editable,
                      bool has_presets,
                      std::string valname, 
                      std::vector<preset_entry_t> prevect)
  {
    val_name = valname;
    presets = prevect;
    is_edit = editable;
	has_preset = has_presets;
  }
  /**
  * @brief ParamDescrCharacter destructor
  */
  ~ParamDescrCharacter() throw() { }
};


/*!
 * @brief ParamDescrString concrete class
 *
 * The ParamDescriptorString implements ParamDescriptor
 * to describe a parameter that stores arrays of characters.
 * It provides a list of preset arrays and alternatively can
 * also allow the option for the user to provide their own
 * editable array.
 */
class ParamDescrString: public ParamDescriptor
{
public:
  /**
  * @brief ParamDescrString constructor
  *
  * @param name List with all selectable options
  */
  ParamDescrString(bool user_conf, bool has_presets, std::string pname, std::vector<preset_string_t> preset_list)
  {

    presets = preset_list; 
    parameter_name = pname;
    user_configurable = user_conf;
	has_preset = has_presets;
  }
  /**
  * @brief ParamDescrString destructor
  */
  ~ParamDescrString() throw() { }
  /*! @copydoc ParamDescriptor::isUserConfigurable() */    
  bool isUserCofigurable()
  {
    return user_configurable;
  }
  /*! @copydoc ParamDescriptor::hasPresetValues() */
  bool hasPresetValues()
  {
    return has_preset; 
  }
  /*! @copydoc ParamDescriptor::hasValueRange() */ 
  bool hasValueRange()
  {
    return false;
  }
  /*! @copydoc ParamDescriptor::getRangeMin() */
  uint32_t getRangeMin()
  {
    return 0;
  }
  /*! @copydoc ParamDescriptor::getRangeMax() */
  uint32_t getRangeMax()
  {
    return 0xFF;
  }
  /*! @copydoc ParamDescriptor::GetRadioNames() */
  std::vector<std::string> GetRadioNames()
  {
    std::vector<std::string> radioNames;
    for(preset_string_t preset : this->presets)
    {
      radioNames.push_back(preset.preset_name);
    }
    return radioNames;
  }
  /*! @copydoc ParamDescriptor::getParamLabel() */
  std::string getParamLabel()
  {
    return parameter_name;
  }
  /*! @copydoc ParamDescriptor::GetPresetValues() */
  std::vector<uint32_t> GetPresetValues()
  {
    std::vector<uint32_t> retval = {0x00};
    return retval;
  }
  
  /*! @copydoc ParamDescriptor::GetPresetStrings() */
  std::vector<std::string> GetPresetStrings()
  {
    std::vector<std::string> radioValues;
    for(preset_string_t preset : this->presets)
    {
      radioValues.push_back(preset.preset_str);
    }
    return radioValues;
  }
private:
  /**
  * @brief List with all selectable options
  */
  std::vector<preset_string_t> presets;
  /**
  * @brief Unique name of the ParamDescriptor
  */
  std::string parameter_name;
  /**
  * @brief Defines if the string is user configurable.
  */
  bool user_configurable;
  /**
  * @brief Defines if the parameter can show presets
  */
  bool has_preset;
};

#endif
