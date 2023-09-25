#include <gui/snscreensaver_screen/SnScreensaverView.hpp>
#include <gui/snscreensaver_screen/SnScreensaverPresenter.hpp>
#include "BitmapDatabase.hpp"

SnScreensaverPresenter::SnScreensaverPresenter(SnScreensaverView& v)
    : view(v)
{

}

void SnScreensaverPresenter::activate()
{

}

void SnScreensaverPresenter::deactivate()
{

}

void SnScreensaverPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnScreensaverPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
  if(IconId == BatteryIcon)
  {
    switch(IconState)
    {
        case Batt_Low:
            view.setBatteryAsset(BITMAP_BATTERY_LOW5X_ID);
            break;
        case Batt_Med_Low:
            view.setBatteryAsset(BITMAP_BATTERY_MED_LOW5X_ID);
            break;
        case Batt_Med:
            view.setBatteryAsset(BITMAP_BATTERY_MED5X_ID);
            break;
        case Batt_Med_High:
            view.setBatteryAsset(BITMAP_BATTERY_MED_HIGH5X_ID);
            break;
        case Batt_Full:
            view.setBatteryAsset(BITMAP_BATTERY_HIGH5X_ID);
            break;
        default:
            break;
    }
  }
}

void SnScreensaverPresenter::MoveToHomeScreen(void)
{

}

void SnScreensaverPresenter::BarcodeComeIn(char * BarcodeData)
{
    model->clearBarcode();
}
