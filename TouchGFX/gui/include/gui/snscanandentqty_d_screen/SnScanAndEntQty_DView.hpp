#ifndef SNSCANANDENTQTY_DVIEW_HPP
#define SNSCANANDENTQTY_DVIEW_HPP

#include <vector>
#include <gui_generated/snscanandentqty_d_screen/SnScanAndEntQty_DViewBase.hpp>
#include <gui/snscanandentqty_d_screen/SnScanAndEntQty_DPresenter.hpp>
#include <gui/common/ZebraApplication.hpp>
#include <gui/common/AppClasses.hpp>
#include <gui/common/ScanAndEntQty_DApp.hpp>
#include <gui/common/ConfigParam.hpp>
#include <touchgfx/Unicode.hpp>


//#include <gui/containers/BarcodeField_Loc.hpp>
//#include <gui/containers/WildcardedMenuItem.hpp>
//#include <gui/containers/TextToast.hpp>
class SnScanAndEntQty_DView : 
  public SnScanAndEntQty_DViewBase,
  public ScanAndEntQty_DApp
{
public:

    ZEBRA_APPLICATION

    SnScanAndEntQty_DView();
    virtual ~SnScanAndEntQty_DView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void selectNewItem();
    virtual void afterTransition();
    virtual void handleKeyEvent(uint8_t key);
    virtual void handleTickEvent();
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    void BarcodeComeIn(char * BarcodeData);

protected:

private:
    static const uint32_t check_value =150;
    static const uint16_t MENUITEM_MAX = 3;
    FocusableIetm * MenuItem[MENUITEM_MAX];
    uint8_t selectItem;
    static const uint16_t CUE_TIMEOUT = 60;
    uint16_t QtyView_Timeout;
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    static const uint16_t RECALL_TIMEOUT = 60;
    uint16_t cueBcTimer;    // cue timer for barcode 1st
    uint16_t cueQtyTimer;   // cue timer for quantity 1st
    uint16_t QtyInputTimer;
    uint16_t QtyInputTimerMax;
    uint16_t QtyViewTimer;
    uint16_t toastQtyViewTimer;
    uint16_t toastBcViewTimer;
    uint16_t BcInputTimer;
    uint16_t BcInputTimerMax;
    string barcode;
    BarcodeRecord_t bc_r;
    BarcodeRecord_t * bc_r_ptr;
    vector<BarcodeRecord_t> barcodeBackup;
    uint16_t quantity;
    uint16_t quantityBackup;    // for backup quantity for show submit message
    uint16_t recallTimer;
    bool screen_lock;
    uint8_t ScanQtyProgess;
    bool qty_popup = false;

    void doForBack(uint8_t key);
    void doForQtyInput(uint8_t key);
    void doForBarcodeInput(uint8_t key);
    void doForHomeKey();
    void doForRecallKey();
    void showQtySubmit(uint16_t qty);
    void resetProgress();
    void gotoReadyState();
    void showBTPopUp(void);
};

#endif // SNSCANANDENTQTY_DVIEW_HPP
