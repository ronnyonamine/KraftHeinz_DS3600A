
#include <gui/common/platform_itf.h>
#include <gui/common/ConfigParam.hpp>

/*  Function Key mapping - mapped to "new" app category -> Function Key */

/* F7 */
/* Manual Edit */
#ifndef _VS2022
REGISTER_DESC_STRING(gblF7StringDescr,
    true,
    true,
    "String",
    SVAL( , ))
#else
std::vector<preset_string_t> gblF7StringDescrOpts = {  };
ParamDescrString gblF7StringDescr(true, true, "String", gblF7StringDescrOpts); 
#endif
REGISTER_DESC_NUM(gblF7RadioDescr,
      0,
      4,
      false,
      true,
      "F7",
      NVAL(0x00, Unassigned(Default)),
      NVAL(0x01, UserDefined),
      NVAL(0x02, Enter),
      NVAL(0x03, Recall),
      NVAL(0x04, Back))
REGISTER_PARAMETER(
     gblF7Key,
     "F7",
     "F7",
     "Function Key",
     PARAM_TYPE_STRING,
     0x00,
     15,
     false,
     gblF7StringDescr,
     0x00,
     0,
     user_cfg_set_F7_string,
     user_cfg_get_F7_string)
REGISTER_PARAMETER(
     gblF7Key_radio,
     "F7_radio",
     "F7_radio",
     "Function Key",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblF7RadioDescr,
     0x00,
     0,
     user_cfg_set_F7_assignment,
     user_cfg_get_F7_assignment)

/* F8 */
/* Manual Edit */
#ifndef _VS2022
REGISTER_DESC_STRING(gblF8StringDescr,
    true,
    true,
    "String",
    SVAL( , ))
#else
std::vector<preset_string_t> gblF8StringDescrOpts = {  };
ParamDescrString gblF8StringDescr(true, true, "String", gblF8StringDescrOpts);
#endif
REGISTER_DESC_NUM(gblF8RadioDescr,
      0,
      4,
      false,
      true,
      "F8",
      NVAL(0x00, Unassigned(Default)),
      NVAL(0x01, UserDefined),
      NVAL(0x02, Enter),
      NVAL(0x03, Recall),
      NVAL(0x04, Back))
REGISTER_PARAMETER(
     gblF8Key,
     "F8",
     "F8",
     "Function Key",
     PARAM_TYPE_STRING,
     0x00,
     15,
     false,
     gblF8StringDescr,
     0x00,
     0,
     user_cfg_set_F8_string,
     user_cfg_get_F8_string)
REGISTER_PARAMETER(
     gblF8Key_radio,
     "F8_radio",
     "F8_radio",
     "Function Key",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblF8RadioDescr,
     0x00,
     0,
     user_cfg_set_F8_assignment,
     user_cfg_get_F8_assignment)

/* F9 */
/* Manual Edit */
#ifndef _VS2022
REGISTER_DESC_STRING(gblF9StringDescr,
    true,
    true,
    "String",
    SVAL( , ))
#else
std::vector<preset_string_t> gblF9StringDescrOpts = {  };
ParamDescrString gblF9StringDescr(true, true, "String", gblF9StringDescrOpts);
#endif
REGISTER_DESC_NUM(gblF9RadioDescr,
      0,
      4,
      false,
      true,
      "F9",
      NVAL(0x00, Unassigned(Default)),
      NVAL(0x01, UserDefined),
      NVAL(0x02, Enter),
      NVAL(0x03, Recall),
      NVAL(0x04, Back))
REGISTER_PARAMETER(
     gblF9Key,
     "F9",
     "F9",
     "Function Key",
     PARAM_TYPE_STRING,
     0x00,
     15,
     false,
     gblF9StringDescr,
     0x00,
     0,
     user_cfg_set_F9_string,
     user_cfg_get_F9_string)
REGISTER_PARAMETER(
     gblF9Key_radio,
     "F9_radio",
     "F9_radio",
     "Function Key",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblF9RadioDescr,
     0x00,
     0,
     user_cfg_set_F9_assignment,
     user_cfg_get_F9_assignment)