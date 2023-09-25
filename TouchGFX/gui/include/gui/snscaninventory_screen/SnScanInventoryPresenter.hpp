#ifndef SNSCANINVENTORYPRESENTER_HPP
#define SNSCANINVENTORYPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>

using namespace touchgfx;

class SnScanInventoryView;

class SnScanInventoryPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler
{
public:
    SnScanInventoryPresenter(SnScanInventoryView& v);

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
    virtual uint8_t getHomeKeyLaunch(void);
    virtual uint8_t getScanInvtBCEditable(void);
    virtual uint8_t getScanInvtQtyEditable(void);
    virtual uint8_t getInvtStore(void);
    virtual void BarcodeComeIn(char * BarcodeData);
    virtual char * getBarcode(void);
    virtual void clearBarcode(void);
    virtual char * getFnKeyRemapString(uint8_t key);
    virtual void setInvtRecord(LocRecord_t *location, BarcodeRecord_t *barcode, uint16_t quantity);
    virtual Invt_Record_t* getInvtRecord(uint16_t index);
    virtual void submitInvtList(void);
    virtual void setInvtInProgress(bool setting);
    virtual bool getInvtInProgress(void);
    virtual void changeLoc(LocRecord_t *oldLoc, LocRecord_t *newLoc);
    virtual uint16_t sendtotalqtyinvt();
    virtual uint16_t sendcountinvt();
    bool checkBTPopup(void);
    virtual void setinvtAppVar(invt1 invtrecord);
    virtual invt1 getinvtAppVar();
	virtual uint8_t getQtyTransferMode(void);
    virtual void addRecord(string date, string time, string learnbarcode, string verifybarcode, string success);
    virtual void updateRecord(string errorreason, string initials);
    virtual void clearRecords(void);
    virtual DataRecord getRecord(int i);
    virtual int getRecordCount(void);

    virtual ~SnScanInventoryPresenter() {};

private:
    SnScanInventoryPresenter();

    SnScanInventoryView& view;
};

#endif // SNSCANINVENTORYPRESENTER_HPP
