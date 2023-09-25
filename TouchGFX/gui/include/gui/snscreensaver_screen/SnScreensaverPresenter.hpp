#ifndef SNSCREENSAVERPRESENTER_HPP
#define SNSCREENSAVERPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/platform_itf.h>

using namespace touchgfx;

class SnScreensaverView;

class SnScreensaverPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SnScreensaverPresenter(SnScreensaverView& v);

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

    virtual ~SnScreensaverPresenter() {};
    /**
     * Updates the battery level on the front-end
     */
    virtual void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual void UpdateAllIcons();
    void MoveToHomeScreen(void);
    void BarcodeComeIn(char * BarcodeData);

    void ActivateInactivityScreensaver(void);


private:
    SnScreensaverPresenter();

    SnScreensaverView& view;
};

#endif // SNSCREENSAVERPRESENTER_HPP
