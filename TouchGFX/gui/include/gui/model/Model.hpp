#ifndef MODEL_HPP
#define MODEL_HPP
#include <stdint.h>
#include <gui/common/platform_itf.h>
#include <string>
#include <vector>
using namespace std;

typedef struct InvtVarRecord{
   bool finishBarcodeFlaginvt = false;
    string temp_location;  //location from scan and enter inventory screen
    vector<LocRecord_t> temp_loc_list;
}invt1 ;

typedef struct DataRecordType {
    string learnBarcode;
    string verifyBarcode;
    string date;
    string time;
    string success;
    string reason;
    string initials;
}DataRecord ;

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void UpdateAllIcons(void);
    void setCurrentScreen(uint32_t CurrentScreen);
    uint32_t getCurrentScreen();
    void setBackArrowActive(bool setting) { activeBackArrow = setting;}
    bool getBackArrowActive() { return (activeBackArrow);}
    // RadioOnItem - 1:Enable, 2:Disable
    uint8_t setAutoDispBri(uint8_t RadioOnItem);
    uint8_t getAutoDispBri(void);
    // RadioOnItem - 1:3s, 2:6s, 3:12s, 4:18s, 5:No Timeout
    uint8_t setDispTout(uint8_t RadioOnItem);
    uint8_t getDispTout(void);
    // RadioOnItem - 1:F1 ~ 9:F9
    void setFnKeySelected(uint8_t RadioOnItem);
    uint8_t getFnKeySelected(void);
    // RadioOnItem - 1:String, 2:ENT, 3: Recall, 4:Back
    void setFnKeyRemap(uint8_t key, uint8_t setting, char * str);
    uint8_t getFnKeyRemap(uint8_t key);
    char * getFnKeyRemapString(uint8_t key);
    // RadioOnItem - 1:Yes, 2:No
    void setBCEditable(uint8_t RadioOnItem);
    uint8_t getBCEditable(void);
    void setScanQtyBCEditable(uint8_t RadioOnItem);
    uint8_t getScanQtyBCEditable(void);
    void setScanLocBCEditable(uint8_t RadioOnItem);
    uint8_t getScanLocBCEditable(void);
    void setScanInvtBCEditable(uint8_t RadioOnItem);
    uint8_t getScanInvtBCEditable(void);
    // RadioOnItem - 1:Yes, 2:No
    void setQtyEditable(uint8_t RadioOnItem);
    uint8_t getQtyEditable(void);
    void setScanQtyQtyEditable(uint8_t RadioOnItem);
    uint8_t getScanQtyQtyEditable(void);
    void setScanLocQtyEditable(uint8_t RadioOnItem);
    uint8_t getScanLocQtyEditable(void);
    void setScanInvtQtyEditable(uint8_t RadioOnItem);
    uint8_t getScanInvtQtyEditable(void);
    // RadioOnItem - 1:Enable, 2:Disable
    uint8_t setAutoKeypadBri(uint8_t RadioOnItem);
    uint8_t getAutoKeypadBri(void);
    // RadioOnItem - 1:user define, 2:3s, 3:6s, 4:9s, 5:no timeout
    void setQTYTout(uint8_t setting, uint8_t value);
    uint8_t getQTYToutSetting(void);
    uint8_t getQTYToutUserDefine(void);
    uint16_t getQTYToutValue(void);
    // RadioOnItem - 1:User, 2:CR, 3:LF, 4:Space, 5:Tab, 6:',', 7:':', 8:';', 9:'='
    void setQtyTransferMode(uint8_t setting);
    uint8_t getQtyTransferMode(void);
    void setQtyDelimiter(uint8_t setting, char user_define);
    uint8_t getQtyDelimiter(void);
    uint8_t getQtyDelimiterDefine(void);
    void setLocDelimiter(uint8_t setting, char user_define);
    uint8_t getLocDelimiter(void);
    uint8_t getLocDelimiterDefine(void);
    void setQtyQtyDelimiter(uint8_t setting, char user_define);
    uint8_t getQtyQtyDelimiter(void);
    uint8_t getQtyQtyDelimiterDefine(void);
    void setLocQtyDelimiter(uint8_t setting, char user_define);
    uint8_t getLocQtyDelimiter(void);
    uint8_t getLocQtyDelimiterDefine(void);
    void setLocLocDelimiter(uint8_t setting, char user_define);
    uint8_t getLocLocDelimiter(void);
    uint8_t getLocLocDelimiterDefine(void);
    void setInvtQtyDelimiter(uint8_t setting, char user_define);
    uint8_t getInvtQtyDelimiter(void);
    uint8_t getInvtQtyDelimiterDefine(void);
    void setInvtLocDelimiter(uint8_t setting, char user_define);
    uint8_t getInvtLocDelimiter(void);
    uint8_t getInvtLocDelimiterDefine(void);
	uint8_t getInvtDelimiterUserDefine(void);

    // RadioOnItem - 1:Permanent, 2:Temporary
    void setInvtStore(uint8_t RadioOnItem);
    uint8_t getInvtStore(void);
    // RadioOnItem - 1:Navigator, 2:Scan_Qty, 3:Scan_Loc, 4:Inventory, 5:Match, 6:Image_Viewer, 7:Disable
    void setHomeKeyLaunch(uint8_t RadioOnItem);
    uint8_t getHomeKeyLaunch(void);
    // RadioOnItem - 1:Yes, 2:No
    void setLiveCapture(uint8_t RadioOnItem);
    uint8_t getLiveCapture(void);
    // setting - 1:Half Full, 2:3/4 Full, 3:Full
    void setDispOnCharge(uint8_t setting);
    uint8_t getDispOnCharge(void);

    bool getScannerMsgRxStatus(void);
    void setSplashScreenActive(bool);

    // Barcode access
    char * getBarcode(void);
    void clearBarcode(void);

    int8_t sendQty(uint16_t quantity);
    int8_t sendBcQty(char * barcode, uint16_t quantity);
    int8_t sendLocBcQty(LocRecord_t * location, BarcodeRecord_t * barcode, uint16_t quantity);
    char * getRecallBarcode(void);

    // For Scan Inventory
    void setInvtRecord(LocRecord_t *location, BarcodeRecord_t *barcode, uint16_t quantity);
    Invt_Record_t* getInvtRecord(uint16_t index);
    void submitInvtList(void);
    void setInvtInProgress(bool setting);
    bool getInvtInProgress(void);
    void changeLoc(LocRecord_t *oldLoc, LocRecord_t *newLoc);
    uint16_t sendtotalqtyinvt(void);
    uint16_t sendcountinvt(void);
    void setinvtAppVar(invt1 &invtrecord);
    invt1 getinvtAppVar();
    
    
    // For Scan Qty
    bool setqtyAppFlags(bool qtyappFlag);
    bool getqtyAppFlags();
    
    // For Scan Loc
    bool setlocAppVar(std::string tmploc);
    std::string getlocAppVar();

    // For Image Viewer
    void setImgViewCmd(uint16_t cmd);
    uint8_t getBackendStatus(uint8_t key);
    uint8_t getInvListFullFlag(void);
    uint8_t getOutInListFullFlag(void);
    
    /* For config parameters storage */
    static bool getConfigParamValue(uint16_t index, uint8_t* buff);
    static bool setConfigParamValue(uint16_t index, uint8_t* buff, uint16_t len);

    /* Parameter registration initialization*/
    static void InitializeUserParam(void);

    /* Manual Edit */
    DataRecord getDataRecord(int i);
    int getDataRecordCount();
    void addDataRecord(string date, string time, string learnbarcode, string verifybarcode, string success);
    void updateDataRecordError(string errorreason, string initials);
    void clearDataRecords();
    int8_t sendDataQty(char* barcode, uint16_t quantity);
    
protected:
    ModelListener* modelListener;
    int ShiftIconState;
    int BTIconState;
    int BattIconState;
    int FnKeySelected;
    char *msg;
    int charge_status;
    int batch_status;
    int inactivity_status;
    bool activeBackArrow;
    bool init_cfg_param_store;
    int bt_autoreconnect_state;
	bool screensaver_guard;

    
private:
  static void generate_home_key_parameter(void);
  bool sendBarcodeEnabledFlag;
  std::string tempLocation;

};

#endif // MODEL_HPP
