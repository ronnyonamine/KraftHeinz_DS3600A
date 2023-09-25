#include <gui/containers/StatusBar.hpp>
#include "BitmapDatabase.hpp"

StatusBar::StatusBar()
{

}

void StatusBar::initialize()
{
    StatusBarBase::initialize();
}

void StatusBar::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    switch (IconId)
    {
    case ShiftIcon:
        switch (IconState)
        {
        case Shift_None:
            imgShift.setVisible(false);
            break;

        case Shift_Blue:
            imgShift.setBitmap(touchgfx::Bitmap(BITMAP_SHIFTBLUE_ID));
            imgShift.setVisible(true);
            break;

        case Shift_Green:
            imgShift.setBitmap(touchgfx::Bitmap(BITMAP_SHIFTGREEN_ID));
            imgShift.setVisible(true);
            break;

        default:
            break;
        }
        imgShift.invalidate();
        break;

    case BatchOnIcon:
        switch (IconState)
        {
        case Batch_Off:
            imgBatchOn.setVisible(false);
            break;

        case Batch_On:
            imgBatchOn.setVisible(true);
            break;

        default:
            break;
        }
        imgBatchOn.invalidate();
        break;

    case BTIcon:
        switch (IconState)
        {
        case BLUETOOTH_DISCONNECT:
            imgBT.setBitmap(touchgfx::Bitmap(BITMAP_BLUETOOTH_ALT_ID));
            break;

        case BLUETOOTH_CONNECT:
            imgBT.setBitmap(touchgfx::Bitmap(BITMAP_BLUETOOTH_ALT_ACTIVE_ID));
            break;

        default:
            break;
        }
        imgBT.invalidate();
        break;

    case BatteryIcon:
        switch (IconState)
        {
        case Batt_Full:
            imgBattery.setBitmap(touchgfx::Bitmap(BITMAP_BATTERY_HIGH_ID));
            break;

        case Batt_Med_High:
            imgBattery.setBitmap(touchgfx::Bitmap(BITMAP_BATTERY_MED_HIGH_ID));
            break;

        case Batt_Med:
            imgBattery.setBitmap(touchgfx::Bitmap(BITMAP_BATTERY_MED_ID));
            break;

        case Batt_Med_Low:
            imgBattery.setBitmap(touchgfx::Bitmap(BITMAP_BATTERY_MED_LOW_ID));
            break;

        case Batt_Low:
            imgBattery.setBitmap(touchgfx::Bitmap(BITMAP_BATTERY_LOW_ID));
            break;

        case Batt_Full_EOL:
            imgBattery.setBitmap(touchgfx::Bitmap(BITMAP_BATTERY_HIGH_EOL_ID));
            break;

        case Batt_Med_High_EOL:
            imgBattery.setBitmap(touchgfx::Bitmap(BITMAP_BATTERY_MED_HIGH_EOL_ID));
            break;

        case Batt_Med_EOL:
            imgBattery.setBitmap(touchgfx::Bitmap(BITMAP_BATTERY_MED_EOL_ID));
            break;

        case Batt_Med_Low_EOL:
            imgBattery.setBitmap(touchgfx::Bitmap(BITMAP_BATTERY_MED_LOW_EOL_ID));
            break;

        case Batt_Low_EOL:
            imgBattery.setBitmap(touchgfx::Bitmap(BITMAP_BATTERY_LOW_EOL_ID));
            break;

        default:
            break;
        }
        imgBattery.invalidate();
        break;

    default:
        break;
    }
}
