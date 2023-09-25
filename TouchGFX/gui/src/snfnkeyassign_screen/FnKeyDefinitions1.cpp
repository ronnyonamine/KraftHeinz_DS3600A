
#include <gui/common/platform_itf.h>
#include <gui/common/ConfigParam.hpp>

/*  Function Key mapping - mapped to "new" app category -> Function Key */

/* F1 */
/* Manual Edit 
#ifndef _VS2022
REGISTER_DESC_STRING(gblF1StringDescr,
    true,
    true,
    "String",
    SVAL( , ))
#else
std::vector<preset_string_t> gblF1StringDescrOpts = {  };
ParamDescrString gblF1StringDescr(true, true, "String", gblF1StringDescrOpts);
#endif*/
REGISTER_DESC_STRING(gblF1StringDescr,
    true,
    true,
    "String")
REGISTER_DESC_NUM(gblF1RadioDescr,
                  0,
                  4, 
                  false,
                  true,
                  "F1",
                  NVAL(0x00, Unassigned (Default)),
                  NVAL(0x01, UserDefined),
                  NVAL(0x02, Enter),
                  NVAL(0x03, Recall),
                  NVAL(0x04, Back))
REGISTER_PARAMETER(
     gblF1Key,
     "F1",
     "F1",
     "Function Key",
     PARAM_TYPE_STRING,
     0x00,
     15,
     false,
     gblF1StringDescr,
     0x00,
     0,
     user_cfg_set_F1_string,
     user_cfg_get_F1_string)
REGISTER_PARAMETER(
     gblF1Key_radio,
     "F1_radio",
     "F1_radio",
     "Function Key",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblF1RadioDescr,
     0x00,
     0,
     user_cfg_set_F1_assignment,
     user_cfg_get_F1_assignment)

/* F2 */
/* Manual Edit */
#ifndef _VS2022
REGISTER_DESC_STRING(gblF2StringDescr,
    true,
    true,
    "String",
    SVAL( , ))
#else
std::vector<preset_string_t> gblF2StringDescrOpts = {  };
ParamDescrString gblF2StringDescr(true, true, "String", gblF2StringDescrOpts);
#endif
REGISTER_DESC_NUM(gblF2RadioDescr,
      0,
      4,
      false,
      true,
      "F2",
      NVAL(0x00, Unassigned(Default)),
      NVAL(0x01, UserDefined),
      NVAL(0x02, Enter),
      NVAL(0x03, Recall),
      NVAL(0x04, Back))
REGISTER_PARAMETER(
     gblF2Key,
     "F2",
     "F2",
     "Function Key",
     PARAM_TYPE_STRING,
     0x00,
     15,
     false,
     gblF2StringDescr,
     0x00,
     0,
     user_cfg_set_F2_string,
     user_cfg_get_F2_string)
REGISTER_PARAMETER(
     gblF2Key_radio,
     "F2_radio",
     "F2_radio",
     "Function Key",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblF2RadioDescr,
     0x00,
     0,
     user_cfg_set_F2_assignment,
     user_cfg_get_F2_assignment)

/* F3 */
/* Manual Edit */
#ifndef _VS2022
REGISTER_DESC_STRING(gblF3StringDescr,
    true,
    true,
    "String",
    SVAL( , ))
#else
std::vector<preset_string_t> gblF3StringDescrOpts = {  };
ParamDescrString gblF3StringDescr(true, true, "String", gblF3StringDescrOpts);
#endif
REGISTER_DESC_NUM(gblF3RadioDescr,
      0,
      4,
      false,
      true,
      "F3",
      NVAL(0x00, Unassigned(Default)),
      NVAL(0x01, UserDefined),
      NVAL(0x02, Enter),
      NVAL(0x03, Recall),
      NVAL(0x04, Back))
REGISTER_PARAMETER(
     gblF3Key,
     "F3",
     "F3",
     "Function Key",
     PARAM_TYPE_STRING,
     0x00,
     15,
     false,
     gblF3StringDescr,
     0x00,
     0,
     user_cfg_set_F3_string,
     user_cfg_get_F3_string)
REGISTER_PARAMETER(
     gblF3Key_radio,
     "F3_radio",
     "F3_radio",
     "Function Key",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblF3RadioDescr,
     0x00,
     0,
     user_cfg_set_F3_assignment,
     user_cfg_get_F3_assignment)