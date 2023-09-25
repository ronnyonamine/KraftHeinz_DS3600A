#ifndef KHMAINSCREENPRESENTER_HPP
#define KHMAINSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>  //Manual Edit
using namespace touchgfx;

class KHMainScreenView;

class KHMainScreenPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler // Manual Edit
{
public:
    KHMainScreenPresenter(KHMainScreenView& v);

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

    virtual ~KHMainScreenPresenter() {};

    /* Manual Edit */
    virtual void UpdateAllIcons();
    virtual void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual void setCurrentScreen(uint8_t CurrentScreen);
    virtual uint8_t getHomeKeyLaunch(void);
    virtual void BarcodeComeIn(char* BarcodeData);
    virtual char* getBarcode(void);
    virtual void clearBarcode(void);
    virtual void addDataRecord(string date, string time, string learnbarcode, string verifybarcode, string success);
    virtual int getDataRecordCount();
    virtual void updateDataRecordError(string errorreason, string initials);
    virtual DataRecord getDataRecord(int index);
    virtual void clearDataRecords();
    virtual int8_t sendDataQty(char* barcode, uint16_t quantity);

    void handleDownKey();
    void handleUpKey();
    void handleEnterKey();
    void handleNumericKey(uint8_t key);
private:
    KHMainScreenPresenter();

    KHMainScreenView& view;
};

#endif // KHMAINSCREENPRESENTER_HPP
