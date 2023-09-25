#ifndef SNFNKEYASSIGNPRESENTER_HPP
#define SNFNKEYASSIGNPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>

using namespace touchgfx;

class SnFnKeyAssignView;

class SnFnKeyAssignPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler
{
public:
    SnFnKeyAssignPresenter(SnFnKeyAssignView& v);

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
    virtual void setFnKeyRemap(uint8_t key, uint8_t setting, char * str);
    virtual uint8_t getFnKeyRemap(uint8_t key);
    virtual uint8_t getFnKeySelected(void);
    virtual void setCurrentScreen(uint32_t CurrentScreen);
    virtual uint8_t getHomeKeyLaunch(void);
    virtual void setBackArrowActive(bool setting);
    virtual bool getBackArrowActive();

    virtual ~SnFnKeyAssignPresenter() {};

private:
    SnFnKeyAssignPresenter();

    SnFnKeyAssignView& view;
};

#endif // SNFNKEYASSIGNPRESENTER_HPP
