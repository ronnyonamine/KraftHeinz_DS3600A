/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/StatusBarBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"

StatusBarBase::StatusBarBase()
{
    setWidth(320);
    setHeight(44);
    boxBackGnd.setPosition(0, 0, 320, 44);
    boxBackGnd.setColor(touchgfx::Color::getColorFrom24BitRGB(162, 202, 250));

    box1.setPosition(50, 0, 220, 40);
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(10, 50, 165));

    imgHome.setXY(8, 6);
    imgHome.setVisible(false);
    imgHome.setBitmap(touchgfx::Bitmap(BITMAP_HOME_ID));

    imgBattery.setXY(8, 6);
    imgBattery.setBitmap(touchgfx::Bitmap(BITMAP_BATTERY_HIGH_ID));

    imgBT.setXY(278, 6);
    imgBT.setVisible(false);
    imgBT.setBitmap(touchgfx::Bitmap(BITMAP_BLUETOOTH_ALT_ACTIVE_ID));

    imgBatchOn.setXY(278, 6);
    imgBatchOn.setBitmap(touchgfx::Bitmap(BITMAP_BATCHON_ID));

    imgShift.setXY(60, 6);
    imgShift.setVisible(false);
    imgShift.setBitmap(touchgfx::Bitmap(BITMAP_SHIFTGREEN_ID));

    box1_1.setPosition(0, 40, 320, 3);
    box1_1.setColor(touchgfx::Color::getColorFrom24BitRGB(10, 50, 165));

    box1_2.setPosition(0, 0, 320, 2);
    box1_2.setColor(touchgfx::Color::getColorFrom24BitRGB(162, 202, 250));

    add(boxBackGnd);
    add(box1);
    add(imgHome);
    add(imgBattery);
    add(imgBT);
    add(imgBatchOn);
    add(imgShift);
    add(box1_1);
    add(box1_2);
}

void StatusBarBase::initialize()
{

}
