#ifndef SNHOMEMENUPRESENTER_HPP
#define SNHOMEMENUPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>

using namespace touchgfx;

class SnHomeMenuView;

class SnHomeMenuPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler
{
public:
    SnHomeMenuPresenter(SnHomeMenuView& v);

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
    virtual void BarcodeComeIn(char * BarcodeData);

    void handleDownKey();
    void handleUpKey();
    void handleEnterKey();
    void handleNumericKey(uint8_t key);

    virtual ~SnHomeMenuPresenter() {};

private:
    SnHomeMenuPresenter();

    SnHomeMenuView& view;
};

#endif // SNHOMEMENUPRESENTER_HPP
