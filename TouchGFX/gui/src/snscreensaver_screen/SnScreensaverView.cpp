#include <gui/snscreensaver_screen/SnScreensaverView.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gui/common/platform_itf.h>

/* Defines values of alpha step changes at different alpha thresholds*/
#define FACTOR_HIGH 255
#define FACTOR_MID  255
#define FACTOR_LOW  255
#define FACTOR_VLOW 255

/* Thresholds for alpha change curve */
#define THRESHOLD_HIGH 190
#define THRESHOLD_MID   80
#define THRESHOLD_LOW    6

/* Number of frames where the battery is at maximum or minimu brightness */
#define EMPTY_FRAMES    0
#define FULL_FRAMES   120

/**
 * @brief defines alpha change direction
 */
#define DIR_RISE 1
#define DIR_FALL 2

SnScreensaverView::SnScreensaverView() : SnScreensaverViewBase()
{
    srand(1);
}
void SnScreensaverView::handleTickEvent()
{
    static int16_t inc_factor = -FACTOR_HIGH;
    static int8_t inc_dir= DIR_FALL;
    static int8_t stop_frames = 3;
    /* SnScreensaverView::alpha is an uint16_t number. 
     * We care only the last byte 
     */
    updateAlpha((uint8_t) (alpha & 0x00FF));
    /* Implement a brief customizable stop on animation completio */
    if(stop_frames)
    {
      stop_frames--;
      return;
    }
    alpha += inc_factor;
    if(inc_dir == DIR_RISE)
    {
      if(alpha >= THRESHOLD_LOW)
      {
        inc_factor = FACTOR_LOW;
      }
      if(alpha >= THRESHOLD_MID)
      {
        inc_factor = FACTOR_MID;
      }
      if(alpha >= THRESHOLD_HIGH)
      {
        inc_factor = FACTOR_HIGH;
      }
      if(alpha >= 255)
      {
        inc_factor = -FACTOR_HIGH;
        alpha = 255;
        stop_frames = FULL_FRAMES;
        inc_dir = DIR_FALL;
      }
    }
    else
    {
      if(alpha <= THRESHOLD_HIGH)
      {
        inc_factor = -FACTOR_MID;
      }
      if(alpha <= THRESHOLD_MID)
      {
        inc_factor = -FACTOR_LOW;
      }
      if(alpha <= THRESHOLD_LOW)
      {
        inc_factor = -FACTOR_VLOW;
      }
      if(alpha <= 0)
      {
       /* Saturate alpha... Upon 0 value, randomize position... */
        inc_factor = FACTOR_VLOW;
        inc_dir = DIR_RISE;
        alpha = 0;
        stop_frames = EMPTY_FRAMES;
        randomizeIconPosition();
        updateAlpha((uint8_t) 0);
      }
    }
}
/*
 * API: SnScreenSaverView::setBatteryAsset
 * (see header file for details)
 */
void SnScreensaverView::setBatteryAsset(uint16_t asset_id)
{
    battStatusImage.invalidate();
    battStatusImage.setBitmap(touchgfx::Bitmap(asset_id));
    battStatusImage.invalidate();
}

void SnScreensaverView::setupScreen()
{
    SnScreensaverViewBase::setupScreen();
    presenter->UpdateAllIcons();
}

void SnScreensaverView::tearDownScreen()
{
    SnScreensaverViewBase::tearDownScreen();
}
/*
 * API: SnScreenSaverView::randomizeIconPosition
 * (see header file for details)
 */
void SnScreensaverView::randomizeIconPosition()
{
    /* To avoid overlapping, find a random number in the widest
     * empty interval in the X axis that doesn't contain the icon
     */ 

    int left_int = battStatusImage.getX();
    int right_int = 320 - battStatusImage.getWidth() - battStatusImage.getX();

    int x = ( left_int >= right_int ) ? 
        rand() % (left_int - battStatusImage.getWidth()) : 
        rand() % right_int + (battStatusImage.getX() + battStatusImage.getWidth());

    // Saturate X coordinate if it passes screen width...
    x = ( x >= 320 - battStatusImage.getWidth() ) ?
        320 - battStatusImage.getWidth() :
        x;
    int y = rand() % (240 - battStatusImage.getHeight());

    battStatusImage.moveTo(x, y);
    battStatusImage.invalidate();
}
/*
 * API: SnScreenSaverView::updateAlpha
 * (see header file for details)
 */
void SnScreensaverView::updateAlpha(uint8_t alpha)
{
    battStatusImage.setAlpha(alpha);
    battStatusImage.invalidate();
}void SnScreensaverView::backToHomeScreen(uint8_t home_screen)
{
   application().gotoSnHomeMenuScreenNoTransition();
}
