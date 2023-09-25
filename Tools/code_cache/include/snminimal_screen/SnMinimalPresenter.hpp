#ifndef SNMINIMALPRESENTER_HPP
#define SNMINIMALPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>

using namespace touchgfx;

class SnMinimalView;

class SnMinimalPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler
{
public:
    SnMinimalPresenter(SnMinimalView& v);

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
    
    /**
     * Zebra Specific APIs common to all screens
     */
    virtual void UpdateAllIcons();
    virtual void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual void setCurrentScreen(uint8_t CurrentScreen);
    virtual uint8_t getHomeKeyLaunch(void);
    
    virtual ~SnMinimalPresenter() {};
    
    /* Keypad Handler Reimplementation for this screen */
    void handleDownKey();
    void handleUpKey();
    void handleEnterKey();
    void handleBackKey();
    void handleEscKey();
    void handleNumericKey(uint8_t key);
    void handleLeftKey();
    void handleRightKey();
	void handleBkspKey();
    
    /* Barcode Data API - can be removed or extended as required */
    virtual int8_t sendBc(char * barcode);

private:
    SnMinimalPresenter();

    SnMinimalView& view;
};

#endif // SNMINIMALPRESENTER_HPP
