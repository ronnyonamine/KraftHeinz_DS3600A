#ifndef SNSCREENSAVERVIEW_HPP
#define SNSCREENSAVERVIEW_HPP

#include <gui_generated/snscreensaver_screen/SnScreensaverViewBase.hpp>
#include <gui/snscreensaver_screen/SnScreensaverPresenter.hpp>

#define SPEED_FACTOR  (7.0)

class SnScreensaverView : public SnScreensaverViewBase
{
public:
    SnScreensaverView();
    virtual ~SnScreensaverView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    void setBatteryAsset(uint16_t asset_id);
    void backToHomeScreen(uint8_t home_screen);

protected:
private:
    /**
     * @brief On called, moves the battery icon on a random position. 
     * Function is implemented to avoid to move battery outside the screen
     */
    void randomizeIconPosition();
    /**
     * @brief Changes the transparency value of the image
     *
     * @param alpha Transparency value (0 - 255)
     */
    void updateAlpha(uint8_t alpha);
    /**
     * @brief Current alpha value of the image
     */
    int16_t alpha = 255;
};

#endif // SNSCREENSAVERVIEW_HPP