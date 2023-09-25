#ifndef SNSCANANDENTQTYPRESENTER_HPP
#define SNSCANANDENTQTYPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>

using namespace touchgfx;

class SnScanAndEntQtyView;

class SnScanAndEntQtyPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler
{
public:
    SnScanAndEntQtyPresenter(SnScanAndEntQtyView& v);

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

    virtual void UpdateAllIcons();
    virtual void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual uint8_t getScanQtyBCEditable(void);
    virtual uint8_t getScanQtyQtyEditable(void);
    virtual uint16_t getQTYToutValue(void);
    virtual void BarcodeComeIn(char * BarcodeData);
    virtual char * getBarcode(void);
    virtual void clearBarcode(void);
    virtual int8_t sendQty(uint16_t quantity);
    virtual int8_t sendBcQty(char * barcode, uint16_t quantity);
    virtual char * getFnKeyRemapString(uint8_t key);
    virtual char * getRecallBarcode(void);
    virtual void setCurrentScreen(uint32_t CurrentScreen);
    virtual uint8_t getHomeKeyLaunch(void);
    virtual bool setqtyAppFlags(bool qtyappFlag);
    virtual bool getqtyAppFlags();
    virtual uint8_t getQtyTransferMode(void);

 
    bool checkBTPopup(void);

    virtual ~SnScanAndEntQtyPresenter() {};

private:
    SnScanAndEntQtyPresenter();

    SnScanAndEntQtyView& view;
};

#endif // SNSCANANDENTQTYPRESENTER_HPP
