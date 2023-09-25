#ifndef SNSPLASHVIEW_HPP
#define SNSPLASHVIEW_HPP

#include <gui_generated/snsplash_screen/SnSplashViewBase.hpp>
#include <gui/snsplash_screen/SnSplashPresenter.hpp>
#include <gui/common/AppClasses.hpp>

class SnSplashView : 
  public SnSplashViewBase,
  public ZebraPlatformScreen
{
public:
    SnSplashView();
    virtual ~SnSplashView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
    virtual void afterTransition();

protected:

private:

    /*
     * Delay Variable Declarations
     */
    static const uint16_t INTERACTION_DURATION = 240;
    uint16_t interactionCounter;
    uint8_t  splashCounter;
};

#endif // SNSPLASHVIEW_HPP
