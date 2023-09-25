
#include <gui/common/platform_itf.h>
#include <gui/common/ConfigParam.hpp>

/*  Function Key mapping - mapped to "new" app category -> Function Key */

/* F4 */
/* Manual Edit */
#ifndef _VS2022
REGISTER_DESC_STRING(gblF4StringDescr,
    true,
    true,
    "String",
    SVAL( , ))
#else
std::vector<preset_string_t> gblF4StringDescrOpts = {  };
ParamDescrString gblF4StringDescr(true, true, "String", gblF4StringDescrOpts);
#endif
REGISTER_DESC_NUM(gblF4RadioDescr,
      0,
      4,
      false,
      true,
      "F4",
      NVAL(0x00, Unassigned(Default)),
      NVAL(0x01, UserDefined),
      NVAL(0x02, Enter),
      NVAL(0x03, Recall),
      NVAL(0x04, Back))
REGISTER_PARAMETER(
     gblF4Key,
     "F4",
     "F4",
     "Function Key",
     PARAM_TYPE_STRING,
     0x00,
     15,
     false,
     gblF4StringDescr,
     0x00,
     0,
     user_cfg_set_F4_string,
     user_cfg_get_F4_string)
REGISTER_PARAMETER(
     gblF4Key_radio,
     "F4_radio",
     "F4_radio",
     "Function Key",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblF4RadioDescr,
     0x00,
     0,
     user_cfg_set_F4_assignment,
     user_cfg_get_F4_assignment)

/* F5 */
/* Manual Edit */
#ifndef _VS2022
REGISTER_DESC_STRING(gblF5StringDescr,
    true,
    true,
    "String",
    SVAL( , ))
#else
std::vector<preset_string_t> gblF5StringDescrOpts = {  };
ParamDescrString gblF5StringDescr(true, true, "String", gblF5StringDescrOpts); 
#endif
REGISTER_DESC_NUM(gblF5RadioDescr,
      0,
      4,
      false,
      true,
      "F5",
      NVAL(0x00, Unassigned(Default)),
      NVAL(0x01, UserDefined),
      NVAL(0x02, Enter),
      NVAL(0x03, Recall),
      NVAL(0x04, Back))
REGISTER_PARAMETER(
     gblF5Key,
     "F5",
     "F5",
     "Function Key",
     PARAM_TYPE_STRING,
     0x00,
     15,
     false,
     gblF5StringDescr,
     0x00,
     0,
     user_cfg_set_F5_string,
     user_cfg_get_F5_string)
REGISTER_PARAMETER(
     gblF5Key_radio,
     "F5_radio",
     "F5_radio",
     "Function Key",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblF5RadioDescr,
     0x00,
     0,
     user_cfg_set_F5_assignment,
     user_cfg_get_F5_assignment)

/* F6 */
/* Manual Edit */
#ifndef _VS2022
REGISTER_DESC_STRING(gblF6StringDescr,
    true,
    true,
    "String",
    SVAL( , ))
#else
std::vector<preset_string_t> gblF6StringDescrOpts = {  };
ParamDescrString gblF6StringDescr(true, true, "String", gblF6StringDescrOpts); 
#endif
REGISTER_DESC_NUM(gblF6RadioDescr,
      0,
      4,
      false,
      true,
      "F6",
      NVAL(0x00, Unassigned(Default)),
      NVAL(0x01, UserDefined),
      NVAL(0x02, Enter),
      NVAL(0x03, Recall),
      NVAL(0x04, Back))
REGISTER_PARAMETER(
     gblF6Key,
     "F6",
     "F6",
     "Function Key",
     PARAM_TYPE_STRING,
     0x00,
     15,
     false,
     gblF6StringDescr,
     0x00,
     0,
     user_cfg_set_F6_string,
     user_cfg_get_F6_string)
REGISTER_PARAMETER(
     gblF6Key_radio,
     "F6_radio",
     "F6_radio",
     "Function Key",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblF6RadioDescr,
     0x00,
     0,
     user_cfg_set_F6_assignment,
     user_cfg_get_F6_assignment)