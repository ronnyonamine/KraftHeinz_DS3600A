#ifndef SNBARCODEPROGRESSPRESENTER_HPP
#define SNBARCODEPROGRESSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>

using namespace touchgfx;

class SnBarcodeProgressView;

class SnBarcodeProgressPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler
{
public:
    SnBarcodeProgressPresenter(SnBarcodeProgressView& v);

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
    virtual uint16_t sendtotalqtyinvt(void);
    virtual uint16_t sendcountinvt(void);
    virtual bool getInvtInProgress(void);
    virtual ~SnBarcodeProgressPresenter() {};
    bool checkBTPopup(void);
    virtual bool setqtyAppFlags(bool qtyappFlag);
    virtual bool getqtyAppFlags();
    virtual bool setlocAppVar(string tmploc);
    virtual string getlocAppVar();
    virtual void setinvtAppVar(invt1 invtrecord);
    virtual invt1 getinvtAppVar();
    uint8_t getCurrentScreen();

private:
    SnBarcodeProgressPresenter();

    SnBarcodeProgressView& view;
};

#endif // SNBARCODEPROGRESSPRESENTER_HPP
