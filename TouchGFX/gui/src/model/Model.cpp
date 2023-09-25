#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/common/ConfigParam.hpp>
#include <gui/common/ZebraApplication.hpp>
#include <gui/common/platform_itf.h>
#include <string>
#include <vector>

extern int TransmitDecodeDataCompleteFlag;
invt1 invtrecordmodel;
vector<DataRecord> DataRecords;
int DataRecordCount;

Model::Model() : modelListener(0),
                 ShiftIconState(0),
                 BTIconState(0),
                 BattIconState(0),
                 FnKeySelected(1),
                 msg(NULL)
{
    DataRecords.push_back(DataRecord());
    DataRecordCount = 0;
}

void Model::clearDataRecords(void)
{
    DataRecords.clear();
    vector<DataRecord>().swap(DataRecords);
    DataRecords.push_back(DataRecord());
    DataRecordCount = 0;
}

DataRecord Model::getDataRecord(int i)
{
    return DataRecords[i];
}

int Model::getDataRecordCount(void)
{
    return DataRecordCount;
}

void Model::addDataRecord(string date, string time, string learnbarcode, string verifybarcode, string success)
{
    DataRecords[DataRecordCount].date = date;
    DataRecords[DataRecordCount].time = time;
    DataRecords[DataRecordCount].learnBarcode = learnbarcode;
    DataRecords[DataRecordCount].verifyBarcode = verifybarcode;
    DataRecords[DataRecordCount].success = success;
    DataRecords[DataRecordCount].reason = "        ";
    DataRecords[DataRecordCount].initials = "   ";
    DataRecords.push_back(DataRecord());
    DataRecordCount++;
}

void Model::updateDataRecordError(string errorreason, string initials)
{
    DataRecords[DataRecordCount-1].reason = errorreason;
    DataRecords[DataRecordCount-1].initials = initials;
}

void Model::tick()
{
    multiLayer_t new_multiLayer_state = get_multiLayer_state();
    uint16_t gui_status = 0;
    
    if (new_multiLayer_state != ShiftIconState)
    {
        ShiftIconState = new_multiLayer_state;

        // Shift Icon Changed
        modelListener->UpdateIcon(ShiftIcon, (IconStateID_t) ShiftIconState);
    }

    if (CST_APIcbGetBackendStatus(&gui_status) == true)
    {
        switch ((gui_status >> 8))
        {
        case STATUS_EVT_BLUETOOTH:
          BTIconState = gui_status & 0x00FF;
          modelListener->UpdateIcon(BTIcon, (IconStateID_t) BTIconState);
          break;

        case STATUS_EVT_BATTERY:
          BattIconState = gui_status & 0x00FF;
          modelListener->UpdateIcon(BatteryIcon, (IconStateID_t) BattIconState);
          if((charge_status == CHARGE_MODE_ON) &&
             (BattIconState <= Batt_Med)        )
          {
            /* We are charging and battery is up -> start screen saver */
            //modelListener->ActivateScreensaver();
          }
          break;
          
        case STATUS_EVT_CHARGE_MODE:
          charge_status = gui_status & 0x00FF;
          if((charge_status == CHARGE_MODE_ON) &&
             (BattIconState <= Batt_Med)        )
          {
            /* We are charging and battery is up -> start screen saver */
            //modelListener->ActivateScreensaver();
            //screensaver_guard = true;
          }
          if(charge_status == CHARGE_MODE_OFF)
          {
          	if(screensaver_guard == true)
          	{
                   //modelListener->DeactivateScreensaver();
                   //screensaver_guard = false;
            }
          }
          break;
        case STATUS_EVT_INACTIVE:
            inactivity_status = gui_status & 0xFF;

            if(inactivity_status == INACTIVITY_ON)
            {
                //modelListener->ActivateScreensaver();
            }
            if(inactivity_status == INACTIVITY_OFF)
            {
                //modelListener->DeactivateScreensaver();
            }
            break;
        case STATUS_EVT_BATCH_MODE:
          /* Just internal update of batch mode - no diret action on UI */
          batch_status = gui_status & 0x00FF;
          break;
          
        case STATUS_EVT_AUTORECONNECT:
          bt_autoreconnect_state = gui_status & 0x00FF;
          break;

        }
    }

    if (msg == NULL)
    {
        if (CST_APIcbGetDecodeData(&msg) != NULL)
        {
            modelListener->BarcodeComeIn(msg);
        }
    }
    
    /* Parameter Data Processing - Can be called somewhere else on UI processing
     * if it possible to make sure it will be called close, but after, backend
     * initialization */
}

void Model::UpdateAllIcons(void)
{
    modelListener->UpdateIcon(ShiftIcon, (IconStateID_t)ShiftIconState);
    modelListener->UpdateIcon(BatchOnIcon, (IconStateID_t)Batch_Off);
    modelListener->UpdateIcon(BTIcon, (IconStateID_t)BTIconState);
    modelListener->UpdateIcon(BatteryIcon, (IconStateID_t)BattIconState);
}

void Model::setCurrentScreen(uint32_t CurrentScreen)
{
    set_launch_screen(CurrentScreen);
}

uint32_t Model::getCurrentScreen()
{
    return get_launch_screen();
}

uint8_t  Model::setAutoDispBri(uint8_t RadioOnItem)
{
   return(CST_APIsetDisplayBrightness(RadioOnItem, true));
}

uint8_t Model::getAutoDispBri(void)
{
    return (CST_APIgetDisplayBrightness());
}

uint8_t Model::setDispTout(uint8_t RadioOnItem)
{
    return(CST_APIsetDisplayTimeout(RadioOnItem, true));
}

uint8_t Model::getDispTout(void)
{
    return (CST_APIgetDisplayTimeout());
}

void Model::setFnKeySelected(uint8_t RadioOnItem)
{
    FnKeySelected = RadioOnItem;
}

uint8_t Model::getFnKeySelected(void)
{
    return (FnKeySelected);
}

void Model::setFnKeyRemap(uint8_t key, uint8_t setting, char * str)
{
    set_function_key(key, setting, str, true);
}

uint8_t Model::getFnKeyRemap(uint8_t key)
{
    return (get_function_key_setting(key));
}

char * Model::getFnKeyRemapString(uint8_t key)
{
    return (get_function_key_string(key));
}

void Model::setBCEditable(uint8_t RadioOnItem)
{
    set_manual_barcode_entry(RadioOnItem, true);
}


uint8_t Model::getBCEditable(void)
{
    return (get_manual_barcode_entry());
}

void Model::setScanQtyBCEditable(uint8_t RadioOnItem)
{
    set_qty_manual_barcode_entry(RadioOnItem, true);
}

uint8_t Model::getScanQtyBCEditable(void)
{
    return (get_qty_manual_barcode_entry());
}

void Model::setScanLocBCEditable(uint8_t RadioOnItem)
{
    set_loc_manual_barcode_entry(RadioOnItem, true);
}

uint8_t Model::getScanLocBCEditable(void)
{
    return (get_loc_manual_barcode_entry());
}

void Model::setScanInvtBCEditable(uint8_t RadioOnItem)
{
    set_invt_manual_barcode_entry(RadioOnItem, true);
}

uint8_t Model::getScanInvtBCEditable(void)
{
    return (get_invt_manual_barcode_entry());
}

void Model::setQtyEditable(uint8_t RadioOnItem)
{
    set_manual_quantity_entry(RadioOnItem, true);
}

uint8_t Model::getQtyEditable(void)
{
    return (get_manual_quantity_entry());
}

void Model::setScanQtyQtyEditable(uint8_t RadioOnItem)
{
    set_qty_manual_quantity_entry(RadioOnItem, true);
}

uint8_t Model::getScanQtyQtyEditable(void)
{
    return (get_qty_manual_quantity_entry());
}

void Model::setScanLocQtyEditable(uint8_t RadioOnItem)
{
    set_loc_manual_quantity_entry(RadioOnItem, true);
}

uint8_t Model::getScanLocQtyEditable(void)
{
    return (get_loc_manual_quantity_entry());
}

void Model::setScanInvtQtyEditable(uint8_t RadioOnItem)
{
    set_invt_manual_quantity_entry(RadioOnItem, true);
}

uint8_t Model::getScanInvtQtyEditable(void)
{
    return (get_invt_manual_quantity_entry());
}

uint8_t Model::setAutoKeypadBri(uint8_t RadioOnItem)
{
    return(CST_APIsetKeypadBL(RadioOnItem, true));
}

uint8_t Model::getAutoKeypadBri(void)
{
    return (CST_APIgetKeypadBL());
}

void Model::setQTYTout(uint8_t setting, uint8_t value)
{
    set_quantity_timeout(setting, value, true);
}

uint8_t Model::getQTYToutSetting(void)
{
    return (get_quantity_timeout_setting());
}

uint8_t Model::getQTYToutUserDefine(void)
{
    return (get_user_define_quantity_timeout());
}

uint16_t Model::getQTYToutValue(void)
{
    return (get_quantity_timeout_frame());
}

void Model::setQtyTransferMode(uint8_t setting)
{
    GenericParamSetInt(0x0885, (uint32_t)setting, true);
}

uint8_t Model::getQtyTransferMode(void)
{
    uint32_t QtyTransferMode;
    QtyTransferMode = GenericParamGetInt(0x0885);
    return (QtyTransferMode);
}
void Model::setQtyDelimiter(uint8_t setting, char user_define)
{
    GenericParamSetInt(0x0886, (uint32_t)setting, true);
}

uint8_t Model::getQtyDelimiter(void)
{
    uint32_t QtyDelimiter;
    QtyDelimiter = GenericParamGetInt(0x0886);
    return (QtyDelimiter);
}
/*
uint8_t Model::getQtyDelimiterDefine(void)
{
    return (get_qty_delimiter_define());
}
*/
void Model::setLocDelimiter(uint8_t setting, char user_define)
{
    GenericParamSetInt(0x0887, (uint32_t)setting, true);
}
uint8_t Model::getLocDelimiter(void)
{
    uint32_t LocDelimiter;
    LocDelimiter = GenericParamGetInt(0x0887);
    return (LocDelimiter);
}

uint8_t Model::getLocDelimiterDefine(void)
{
    return (get_loc_delimiter_define());
}

void Model::setQtyQtyDelimiter(uint8_t setting, char user_define)
{
    GenericParamSetInt(0x0888, (uint32_t)setting, true);
}

uint8_t Model::getQtyQtyDelimiter(void)
{
    uint32_t QtyQtyDelimiter;
    QtyQtyDelimiter = GenericParamGetInt(0x0888);
    return (QtyQtyDelimiter);
}
/*
uint8_t Model::getQtyQtyDelimiterDefine(void)
{
    return (get_qty_qty_delimiter_define());
}*/

void Model::setLocQtyDelimiter(uint8_t setting, char user_define)
{
    GenericParamSetInt(0x0889, (uint32_t)setting, true);
}
uint8_t Model::getLocQtyDelimiter(void)
{
   uint32_t LocQtyDelimiter;
   LocQtyDelimiter = GenericParamGetInt(0x0889);
   return (LocQtyDelimiter);
}
/*
uint8_t Model::getLocQtyDelimiterDefine(void)
{
    return (get_loc_qty_delimiter_define());
}
*/
void Model::setLocLocDelimiter(uint8_t setting, char user_define)
{
    set_loc_delimiter(setting, user_define, true);
}

uint8_t Model::getLocLocDelimiter(void)
{
     return (get_loc_delimiter_setting());
}

uint8_t Model::getLocLocDelimiterDefine(void)
{
    return (get_loc_delimiter_define());
}

void Model::setInvtQtyDelimiter(uint8_t setting, char user_define)
{
   GenericParamSetInt(0x088A, (uint32_t)setting, true);
}
uint8_t Model::getInvtQtyDelimiter(void)
{
   uint32_t InvtQtyDelimiter;
   InvtQtyDelimiter = GenericParamGetInt(0x088A);
   return (InvtQtyDelimiter);
}
/*
uint8_t Model::getInvtQtyDelimiterDefine(void)
{
    return (get_invt_qty_delimiter_define());
}
*/
void Model::setInvtLocDelimiter(uint8_t setting, char user_define)
{
    set_invt_delimiter(setting, user_define, true);
}

uint8_t Model::getInvtLocDelimiter(void)
{
    return (get_invt_delimiter_setting());
}

uint8_t Model::getInvtDelimiterUserDefine(void)
{
    return (get_invt_delimiter_define());
}

void Model::setInvtStore(uint8_t RadioOnItem)
{
    set_invt_store(RadioOnItem, true);
}

uint8_t Model::getInvtStore(void)
{
    return (get_invt_store());
}

void Model::setHomeKeyLaunch(uint8_t RadioOnItem)
{
    set_home_key_launch(RadioOnItem, true);
}

uint8_t Model::getHomeKeyLaunch(void)
{
    return (get_home_key_launch());
}

void Model::setLiveCapture(uint8_t RadioOnItem)
{
    set_live_capture(RadioOnItem, true);
}

uint8_t Model::getLiveCapture(void)
{
    return (get_live_capture());
}

void Model::setDispOnCharge(uint8_t setting)
{
    set_display_on_charge(setting, true);
}

uint8_t Model::getDispOnCharge(void)
{
    return (get_display_on_charge());
}

char * Model::getBarcode(void)
{
    return (msg);
}

void Model::clearBarcode(void)
{
    msg = NULL;
}

int8_t Model::sendQty(uint16_t quantity)
{
    return CST_APIsendQuantity(quantity);
}

int8_t Model::sendBcQty(char * barcode, uint16_t quantity)
{
    return (CST_APIsendManualBarCodeQty(barcode, quantity));
}


int8_t Model::sendLocBcQty(LocRecord_t * location, BarcodeRecord_t * barcode, uint16_t quantity)
{
    return CST_APIsendLocBarCodeQty(location, barcode, quantity);
}

char * Model::getRecallBarcode(void)
{
    return (Recall_Barcode());
}

void Model::setInvtRecord(LocRecord_t *location, BarcodeRecord_t *barcode, uint16_t quantity)
{
    set_invt_record(location, barcode, quantity);
}

Invt_Record_t* Model::getInvtRecord(uint16_t index)
{
    return (get_invt_record(index));
}

void Model::submitInvtList(void)
{
    submit_invt_list();
}

void Model::setInvtInProgress(bool setting)
{
    set_invt_in_progress(setting);
}

bool Model::getInvtInProgress(void)
{
    return (get_invt_in_progress());
}

void Model::changeLoc(LocRecord_t *oldLoc, LocRecord_t *newLoc)
{
    change_loc(oldLoc, newLoc);
}

uint16_t Model::sendtotalqtyinvt(void)// rm later
{
   return (send_total_qty_invt());// rm later
}

uint16_t Model::sendcountinvt(void)
{
  return (send_count_invt());
}
void Model::setImgViewCmd(uint16_t cmd)
{
    set_img_view_cmd(cmd);
}
uint8_t Model::getBackendStatus(uint8_t key)
{
    switch(key)
    {
    case STATUS_EVT_BLUETOOTH:
        return (uint8_t)BTIconState;
        break;
    
    case STATUS_EVT_BATTERY:
        return (uint8_t)BattIconState;
        break;
        
    case STATUS_EVT_CHARGE_MODE:
        return (uint8_t)charge_status;
        break;
        
    case STATUS_EVT_BATCH_MODE:
        return (uint8_t)batch_status;
        break;
        
    case STATUS_EVT_AUTORECONNECT:
        return(uint8_t)bt_autoreconnect_state;
    }
    return 0xFF;
}

uint8_t Model::getInvListFullFlag(void)
{
  return (get_inv_list_full_flag());
}

uint8_t Model::getOutInListFullFlag(void)
{
  return (get_out_in_list_full_flag());
}

bool Model::getConfigParamValue(uint16_t index, uint8_t* buff)
{
  /* Check if the parameter is handled with a callback/legacy */
  if(ConfigParam::GetParameters()[index].get_callback != NULL)
  {
    ConfigParam::GetParameters()[index].get_callback((uint32_t*)buff);
    return true;
  }
  // else
  // {
  //  /* We call the generic storage */
  //  if( user_cfg_get_param_value(index, buff) == USER_CFG_OK)
  //  {
  //    return true;
  //  }
  // }

  return false;
}
bool Model::setConfigParamValue(uint16_t index, uint8_t* buff, uint16_t len)
{
  /* Check if the parameter is handled with a callback/legacy */
  if(ConfigParam::GetParameters()[index].set_callback != NULL)
  {
    //if (ConfigParam::GetParamType(index) == PARAM_TYPE_STRING)
    //{
      ConfigParam::GetParameters()[index].set_callback((uint32_t)buff);
    //}
    //else
    //{
    //  ConfigParam::GetParameters()[index].set_callback((uint32_t)*buff);
    //}
    return true;
  }
  // else
  // {
  //  /* We use the generic storage */
  //  if( user_cfg_set_param_value(index, buff, len) == USER_CFG_OK)
  //  {
  //    return true;
  //  }
  // }
  return false;
}

bool  Model::setqtyAppFlags(bool qtyappFlag)
{
  if (sendBarcodeEnabledFlag!= qtyappFlag )
     sendBarcodeEnabledFlag = qtyappFlag;
  return true;
}

bool  Model::getqtyAppFlags()
{
  return sendBarcodeEnabledFlag;
}

bool Model::setlocAppVar(std::string tmploc)
{
  if (tempLocation !=  tmploc)
     tempLocation = tmploc;
  return true;
}

string Model::getlocAppVar()
{
  return tempLocation;
}

void Model::setinvtAppVar(invt1 &invtrecord)
{
    invtrecordmodel = invtrecord;
}
invt1 Model::getinvtAppVar()
{
  return invtrecordmodel;
}

void Model::setSplashScreenActive(bool state)
{
    set_splashscreen_active(state);
}


void Model::InitializeUserParam(void)
{
    /* First we generate the Home Key Parameter */
    generate_home_key_parameter();

    uint16_t param_list_size = ConfigParam::GetParametersSize();
    uint32_t param_hash = ConfigParam::GetParameterHash();
    char param_name_buff[30] = { 0 };
    t_param_descriptor att_descr = { 0,0,0,0,0,0 };
    t_param_range att_range = { 0,0,0 };

    /* We register all parameters */
    for (uint16_t i = 0; i < param_list_size; i++)
    {
        /* All parameters that are processed identically for every  attribute */
        att_descr.idx = i;

        strcpy(param_name_buff,
            ConfigParam::GetParameters()[i].param_name.c_str());
        att_descr.name = param_name_buff;
        /* For now, we give all properties to config param */
        att_descr.properties = USER_CFG_PROPERTY_READABLE |
            USER_CFG_PROPERTY_WRITEABLE |
            USER_CFG_PROPERTY_PERSISTENT;
        att_descr.length = ConfigParam::GetParameters()[i].param_size;

        /* Range parameters do not make much sense for strings, but can be
           processed here for completeness - default should be handled later */
        att_range.max_val = ConfigParam::GetParameters()[i].param_descr->getRangeMax();
        att_range.min_val = ConfigParam::GetParameters()[i].param_descr->getRangeMin();
        att_range.def_val = ConfigParam::GetParameters()[i].default_value;

        switch (ConfigParam::GetParameters()[i].param_type)
        {
        case PARAM_TYPE_BOOL:
            att_descr.type = USER_CFG_ATT_BITFLAG;
            break;
        case PARAM_TYPE_CHARACTER:
            att_descr.type = USER_CFG_ATT_CHAR;
            break;
        case PARAM_TYPE_NUMERIC:
            switch (att_descr.length)
            {
            case 1:
                att_descr.type = (ConfigParam::GetParameters()[i].param_sign) ?
                    USER_CFG_ATT_CHAR : USER_CFG_ATT_BYTE;
                break;
            case 2:
                att_descr.type = (ConfigParam::GetParameters()[i].param_sign) ?
                    USER_CFG_ATT_INTEGER : USER_CFG_ATT_WORD;
                break;
            case 4:
                att_descr.type = (ConfigParam::GetParameters()[i].param_sign) ?
                    USER_CFG_ATT_LONG : USER_CFG_ATT_DOUBLE;
                break;
            default:
                /* Shouldn't reach here */
                break;
            }
            break;
        case PARAM_TYPE_STRING:
            att_descr.type = USER_CFG_ATT_STRING;
            break;
        default:
            /* Shouldn't reach here -> unsuported type */
            break;
        }
        /* For now, since strings/arrays are still not supported, len = 0 */
        user_cfg_register_param(att_descr, att_range, NULL, 0);
    }

    /* A signal for backend data-store to signal all parameters have been
     * registered. Hash/Footprint still being used to identify changes in
     * ConfigParam list. */
    e_user_cfg_status retval = user_cfg_init_store(param_list_size, param_hash);
    if (retval == USER_CFG_HASH_MISMATCH)
    {
        uint32_t data;
        uint16_t size;
        /* Default Initialization of the entire param storage */
        for (uint16_t i = 0; i < param_list_size; i++)
        {
            /* TODO: Logic to pass data for all types */
            data = ConfigParam::GetParameters()[i].default_value;
            size = ConfigParam::GetParameters()[i].param_size;
            setConfigParamValue(i, (uint8_t*)&data, size);
        }
    }
}


void Model::generate_home_key_parameter(void)
{
    static std::vector<preset_entry_t>  appList;
    uint32_t preset_value = 1;
    /* Check that there are parameters for Global */
    for (ConfigParam param : ConfigParam::GetAppParameters("Global"))
    {
        /* Check that the Home Key Launch Param exists */
        if (param.param_name == "Home Key Launch")
        {
            appList.push_back({ "No Action", 0 });
            appList.push_back({ "Home Menu", 1 });
            /* It exists, generate the Descriptor based on registered applications */
            for (uint8_t i = 0; i < ZebraApplication::GetApplications().size(); i++)
            {
                ZebraApplication app = ZebraApplication::GetApplications()[i];
                preset_value++;
                appList.push_back({ app.name, preset_value });
            }

            /* We have the list, now we update the parameter itself */
            ParamDescrNumeric* appDescr = new ParamDescrNumeric(0, preset_value, false, true, "None", appList);

            uint16_t att_idx = ConfigParam::GetParamIndex("Home Key Launch",
                "Global");
            ConfigParam::ModifyAttNumber(att_idx, 0x086E);

            ConfigParam::ModifyParamType(0x086E, PARAM_TYPE_NUMERIC, appDescr);
        }
    }
}

bool Model:: getScannerMsgRxStatus(void)
{
  return get_scannerMsgRx_status();
}

int8_t Model::sendDataQty(char* barcode, uint16_t quantity)
{
    return (CST_APIsendManualBarCodeQty(barcode, quantity));
}