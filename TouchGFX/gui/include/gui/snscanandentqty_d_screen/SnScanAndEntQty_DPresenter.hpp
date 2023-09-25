#ifndef SNSCANANDENTQTY_DPRESENTER_HPP
#define SNSCANANDENTQTY_DPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>

using namespace touchgfx;

class SnScanAndEntQty_DView;

class SnScanAndEntQty_DPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler
{
public:
    SnScanAndEntQty_DPresenter(SnScanAndEntQty_DView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();
    
    /**
     * Zebra Specific APIs common to all screens
     */
    virtual void UpdateAllIcons();
    virtual void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual uint8_t getScanQtyBCEditable(void);
    virtual uint8_t getScanQtyQtyEditable(void);
    virtual uint16_t getQTYToutValue(void);
    virtual void BarcodeComeIn(char * BarcodeData);
    virtual char * getBarcode(void);
    virtual void clearBarcode(void);
    virtual void sendBcQty(BarcodeRecord_t * barcode, uint16_t quantity);
    virtual char * getFnKeyRemapString(uint8_t key);
    virtual void setCurrentScreen(uint32_t CurrentScreen);
    virtual uint8_t getHomeKeyLaunch(void);
    /**
     * @brief Checks conditions to raise Bluetooth Disconnected Pop-up
     * @retval true if Bluetooth pop-up has to occur, false otherwise
     */
    virtual bool checkBTPopup(void);

    virtual ~SnScanAndEntQty_DPresenter() {};

private:
    SnScanAndEntQty_DPresenter();

    SnScanAndEntQty_DView& view;
};

#endif // SNSCANANDENTQTY_DPRESENTER_HPP
