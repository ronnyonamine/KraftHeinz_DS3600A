#ifndef SNQTYSENDMODEPRESENTER_HPP
#define SNQTYSENDMODEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SnQtySendModeView;

class SnQtySendModePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SnQtySendModePresenter(SnQtySendModeView& v);

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
    virtual void BarcodeComeIn(char * BarcodeData);
    virtual char * getBarcode(void);
    virtual void clearBarcode(void);
    virtual void setQtyTransferMode(uint8_t RadioOnItem);
    virtual uint8_t getQtyTransferMode(void);
    virtual void setCurrentScreen(uint32_t CurrentScreen);
    virtual uint8_t getHomeKeyLaunch(void);
    virtual void setBackArrowActive(bool setting);

    virtual ~SnQtySendModePresenter() {};

private:
    SnQtySendModePresenter();

    SnQtySendModeView& view;
};

#endif // SNQTYSENDMODEPRESENTER_HPP
