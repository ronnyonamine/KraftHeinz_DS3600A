#ifndef SNSCANANDENTLOCPRESENTER_HPP
#define SNSCANANDENTLOCPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>

using namespace touchgfx;

class SnScanAndEntLocView;

class SnScanAndEntLocPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler
{
public:
    SnScanAndEntLocPresenter(SnScanAndEntLocView& v);

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
    virtual void setCurrentScreen(uint32_t CurrentScreen);
    virtual void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual uint8_t getScanLocBCEditable(void);
    virtual uint8_t getScanLocQtyEditable(void);
    virtual void BarcodeComeIn(char * BarcodeData);
    virtual char * getBarcode(void);
    virtual void clearBarcode(void);
    
    virtual int8_t sendQty(uint16_t quantity);
    virtual int8_t sendBcQty(char * barcode, uint16_t quantity);
    virtual int8_t sendLocBcQty(LocRecord_t * location, BarcodeRecord_t * barcode, uint16_t quantity);

    virtual char * getFnKeyRemapString(uint8_t key);
    virtual uint8_t getHomeKeyLaunch(void);
    virtual bool setlocAppVar(string tmploc);
    virtual string getlocAppVar();
	virtual uint8_t getQtyTransferMode(void);

    /**
     * @brief Checks conditions to raise Bluetooth Disconnected Pop-up
     * @retval true if Bluetooth pop-up has to occur, false otherwise
     */
    virtual bool checkBTPopup(void);

    virtual ~SnScanAndEntLocPresenter() {};

private:
    SnScanAndEntLocPresenter();

    SnScanAndEntLocView& view;
};

#endif // SNSCANANDENTLOCPRESENTER_HPP
