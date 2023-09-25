#ifndef SNOUTINMATCHPRESENTER_HPP
#define SNOUTINMATCHPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>

using namespace touchgfx;

class SnOutInMatchView;

class SnOutInMatchPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler
{
public:
    SnOutInMatchPresenter(SnOutInMatchView& v);

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
    virtual uint8_t getOutInMatchListFullFlag(void);

    virtual ~SnOutInMatchPresenter() {};

private:
    SnOutInMatchPresenter();

    SnOutInMatchView& view;
};

#endif // SNOUTINMATCHPRESENTER_HPP
