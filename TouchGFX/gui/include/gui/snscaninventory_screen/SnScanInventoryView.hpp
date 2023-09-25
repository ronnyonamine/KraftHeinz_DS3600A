#ifndef SNSCANINVENTORYVIEW_HPP
#define SNSCANINVENTORYVIEW_HPP

#include <vector>
#include <gui_generated/snscaninventory_screen/SnScanInventoryViewBase.hpp>
#include <gui/snscaninventory_screen/SnScanInventoryPresenter.hpp>
#include <gui/containers/InvtListField.hpp>
#include <gui/containers/InvtListField_Loc.hpp>
#include <gui/common/ZebraApplication.hpp>
#include <gui/common/AppClasses.hpp>
#include <gui/common/ConfigParam.hpp>
#include <touchgfx/Unicode.hpp>

#define SCAN_INVENTORY_APP                          //used to find if inventory app is present or not while building source

class SnScanInventoryView : 
  public SnScanInventoryViewBase,
  public ScanInventoryApp
{
public:

    ZEBRA_APPLICATION

    SnScanInventoryView();
    virtual ~SnScanInventoryView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void afterTransition();
    void selectNewItem();
    virtual void handleKeyEvent(uint8_t key);
    virtual void handleTickEvent();
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    void BarcodeComeIn(char * BarcodeData);
    void endOfBarcodeProgress();

protected:
    static const uint16_t INVT_LIST_ITEM_MAX = 1000;
    static const uint8_t INVT_LIST_LOC_ITEM_MAX = 150;
    InvtListField ccInvtList[INVT_LIST_ITEM_MAX];
    InvtListField_Loc ccInvtList_Loc[INVT_LIST_LOC_ITEM_MAX];

private:
    static const touchgfx::Unicode::UnicodeChar ELLIPSIS = 0x2025;
    static const uint16_t MENUITEM_MAX = 11;
    FocusableIetm * MenuItem[MENUITEM_MAX];
    uint16_t newSelItem;
    uint16_t oldSelItem;
    uint16_t returnItem;
    static const uint16_t CUE_TIMEOUT = 60;
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    static const uint16_t TOASTVIEW_LIST_LIMIT_TIMEOUT = 300;
    uint16_t cueLocTimer;
    uint16_t cueBcTimer;
    uint16_t toastViewTimer;
    uint16_t submitMsgTimer;
    string barcode;
    string location;
    BarcodeRecord_t bc_r;
    LocRecord_t loc_r;
    BarcodeRecord_t * bc_r_ptr;
    LocRecord_t * loc_r_ptr;
    uint16_t quantity;
    uint16_t invt_qty =0;
    vector<LocRecord_t> location_list;
    uint16_t invtListItem;
    uint16_t invtListItemMax;
    bool homekeyActive;
    bool dataInProgress;
    bool locChange;
    static const uint16_t USER_EDIT_BC_MASK = 0x8000;
    uint16_t toastInventViewTimer;
    uint16_t toastInventENTViewTimer;
    uint16_t toastInventFullViewTimer;
    uint16_t BTIconState;
      bool qty_popup = false;

    void dragScroll(int drag);
    void dragListScroll(int drag);
    void doForBack(uint8_t key);
    void doForQtyInput(uint8_t key);
    void doForBarcodeInput(uint8_t key);
    void doForLocationInput(uint8_t key);
    void doForAction(uint8_t key);
    void doForHomeKey();
    void acceptLoc();
    void acceptBarcode();
    void acceptQty();
    void showInvtList();
    void showSubmitMsg();
    void screenTransitionToProgress();
    bool LocCompare(LocRecord_t * loc_s, LocRecord_t * loc_d);
};

#endif // SNSCANINVENTORYVIEW_HPP
