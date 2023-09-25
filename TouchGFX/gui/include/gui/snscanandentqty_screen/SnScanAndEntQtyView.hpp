#ifndef SNSCANANDENTQTYVIEW_HPP
#define SNSCANANDENTQTYVIEW_HPP

#include <gui_generated/snscanandentqty_screen/SnScanAndEntQtyViewBase.hpp>
#include <gui/snscanandentqty_screen/SnScanAndEntQtyPresenter.hpp>
#include <gui/common/ZebraApplication.hpp>
#include <gui/common/AppClasses.hpp>
#include <gui/common/ConfigParam.hpp>
#include <touchgfx/Unicode.hpp>

#define SCAN_QUANTITY_APP                         //used to find if scan and quantity app is present or not while building source

class SnScanAndEntQtyView : 
  public SnScanAndEntQtyViewBase,
  public ScanAndEnterQtyApp
{
public:

    ZEBRA_APPLICATION

    SnScanAndEntQtyView();
    virtual ~SnScanAndEntQtyView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void afterTransition();
    void selectNewItem();
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
    static const uint16_t QtySubmitView_TIMEOUT = 10;
    static const uint16_t RECALL_TIMEOUT = 60;
    uint16_t QtySubmitTimer;
    uint16_t cueBcTimer;    // cue timer for barcode 1st
    uint16_t cueQtyTimer;   // cue timer for quantity 1st
    uint16_t QtyInputTimer;
    uint16_t QtyInputTimerMax;
    uint16_t QtyViewTimer;
    uint16_t toastQtyViewTimer;
    uint16_t toastBcViewTimer;
    uint16_t BcInputTimer;
    uint16_t BcInputTimerMax;
    char *barcode;
    uint16_t quantity;
    uint16_t quantityBackup;    // for backup quantity for show submit message
    uint8_t recallProcessState;
    uint8_t recallDataState;
    uint16_t recallTimer;
    bool BarcodecomeinFlag;
    bool screen_lock;
    bool qty_popup = false;

    void doForBack(uint8_t key);
    void doForQtyInput(uint8_t key);
    void doForBarcodeInput(uint8_t key);
    void doForRecallKey();
    void showQtySubmit(uint16_t qty);
    void resetProgress();
    void gotoReadyState();
    void screenTransitionToProgress();
    void endOfBarcodeProgress();
    void showBTPopUp(void);
};

#endif // SNSCANANDENTQTYVIEW_HPP
