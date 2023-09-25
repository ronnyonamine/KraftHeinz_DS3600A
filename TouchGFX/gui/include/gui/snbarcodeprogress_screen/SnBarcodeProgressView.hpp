#ifndef SNBARCODEPROGRESSVIEW_HPP
#define SNBARCODEPROGRESSVIEW_HPP

#include <gui_generated/snbarcodeprogress_screen/SnBarcodeProgressViewBase.hpp>
#include <gui/snbarcodeprogress_screen/SnBarcodeProgressPresenter.hpp>

#include <gui/common/AppClasses.hpp>

#if __has_include (<gui/snscanandentqty_screen/SnScanAndEntQtyView.hpp>)
#include <gui/snscanandentqty_screen/SnScanAndEntQtyView.hpp>
#endif

#if __has_include (<gui/snscanandentloc_screen/SnScanAndEntLocView.hpp>)
#include <gui/snscanandentloc_screen/SnScanAndEntLocView.hpp>
#endif

#if __has_include (<gui/snscaninventory_screen/SnScanInventoryView.hpp>)
#include <gui/snscaninventory_screen/SnScanInventoryView.hpp>
#endif

class SnBarcodeProgressView : 
  public SnBarcodeProgressViewBase, 
  public DefaultApp
{
public:
    SnBarcodeProgressView();
    virtual ~SnBarcodeProgressView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleKeyEvent(uint8_t key);
    virtual void handleTickEvent();
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    void ProgressionBar();
    void showBTPopUp(void);
protected:
    uint16_t percentage;
    uint16_t result;
    bool screen_lock;
private:
    static const touchgfx::Unicode::UnicodeChar ELLIPSIS = 0x2025;
    static const uint16_t submitviewTimeout = 360;
    uint16_t submitviewTimer;
    void QtySubmit(uint16_t qty);
    void locsubmit(uint16_t qty);
    void invtsubmit();
    void endOfBarcodeProgress();
    uint8_t QtySubmitView_TIMEOUT;
    bool SubmitTimer = false;
    void screenTransition();
    uint8_t confirm_timeout_qty;
    uint8_t confirm_timeout_loc;
    bool Ontimeout(uint32_t lastrundiffMS);
    bool finishBarcodeFlag = false;
    uint16_t progressQty = 0;
    uint32_t lastTickMS = 0;
};

#endif // SNBARCODEPROGRESSVIEW_HPP
