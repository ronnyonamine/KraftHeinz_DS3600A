#ifndef SNIMAGEVIEWPRESENTER_HPP
#define SNIMAGEVIEWPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>

using namespace touchgfx;

class SnImageViewView;

class SnImageViewPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler
{
public:
    SnImageViewPresenter(SnImageViewView& v);

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
    virtual void setCurrentScreen(uint32_t CurrentScreen);
    virtual uint8_t getHomeKeyLaunch(void);
    virtual void BarcodeComeIn(char * BarcodeData);
    virtual char * getBarcode(void);
    virtual void clearBarcode(void);
    virtual uint8_t getLiveCapture(void);
    virtual void setImgViewCmd(uint16_t cmd);

    virtual ~SnImageViewPresenter() {};

private:
    SnImageViewPresenter();

    SnImageViewView& view;
};

#endif // SNIMAGEVIEWPRESENTER_HPP
