#ifndef SNSCANANDENTLOCVIEW_HPP
#define SNSCANANDENTLOCVIEW_HPP

#include <gui_generated/snscanandentloc_screen/SnScanAndEntLocViewBase.hpp>
#include <gui/snscanandentloc_screen/SnScanAndEntLocPresenter.hpp>
#include <gui/common/ZebraApplication.hpp>
#include <gui/common/AppClasses.hpp>
#include <gui/common/ConfigParam.hpp>
#include <touchgfx/Unicode.hpp>

#define SCAN_LOC_APP                              //used to find if location app is present or not while building source

class SnScanAndEntLocView : 
  public SnScanAndEntLocViewBase,
  public ScanAndEnterLocApp
{
public:

    ZEBRA_APPLICATION

    SnScanAndEntLocView();
    virtual ~SnScanAndEntLocView() {}
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
    static const uint16_t check_value = 150;
    static const uint16_t MENUITEM_MAX = 4;
    FocusableIetm * MenuItem[MENUITEM_MAX];
    uint8_t selectItem;
    static const uint16_t CUE_TIMEOUT = 60;
    uint16_t QtyView_Timeout;
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    uint16_t QtySubmitTimer;
    static const uint16_t QtySubmitView_TIMEOUT = 10;
    uint16_t cueTimer;
    uint16_t QtyViewTimer;
    uint16_t toastLocViewTimer;
    uint16_t toastQtyViewTimer;
    uint16_t toastBcViewTimer;
    string barcode;
    string location;
    BarcodeRecord_t bc_r;
    LocRecord_t loc_r;
    BarcodeRecord_t * bc_r_ptr;
    LocRecord_t * loc_r_ptr;
    uint16_t quantity;
    static const uint16_t USER_EDIT_BC_MASK = 0x8000;
    bool screen_lock;
    bool qty_popup = false;

    void doForBack(uint8_t key);
    void doForQtyInput(uint8_t key);
    void doForBarcodeInput(uint8_t key);
    void doForLocationInput(uint8_t key);
    void showQtySubmit(uint16_t quantity);
    void gotoReadyState();
    void screenTransitionToProgress();
    void endOfBarcodeProgress();
    void showBTPopUp(void);
};

#endif // SNSCANANDENTLOCVIEW_HPP
