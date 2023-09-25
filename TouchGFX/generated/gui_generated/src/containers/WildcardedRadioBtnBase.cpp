/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/WildcardedRadioBtnBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include "BitmapDatabase.hpp"

WildcardedRadioBtnBase::WildcardedRadioBtnBase()
{
    setWidth(320);
    setHeight(64);
    boxBackGnd.setPosition(0, 0, 320, 64);
    boxBackGnd.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));

    textRadioBtnInactive.setPosition(56, 16, 256, 32);
    textRadioBtnInactive.setColor(touchgfx::Color::getColorFrom24BitRGB(76, 76, 76));
    textRadioBtnInactive.setLinespacing(0);
    textRadioBtnInactiveBuffer[0] = 0;
    textRadioBtnInactive.setWildcard(textRadioBtnInactiveBuffer);
    textRadioBtnInactive.setTypedText(touchgfx::TypedText(T_SINGLEUSEID18));

    textRadioBtnActive.setPosition(56, 10, 256, 44);
    textRadioBtnActive.setVisible(false);
    textRadioBtnActive.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textRadioBtnActive.setLinespacing(0);
    textRadioBtnActiveBuffer[0] = 0;
    textRadioBtnActive.setWildcard(textRadioBtnActiveBuffer);
    textRadioBtnActive.setTypedText(touchgfx::TypedText(T_SINGLEUSEID17));

    imgRadioBtn.setXY(16, 16);
    imgRadioBtn.setBitmap(touchgfx::Bitmap(BITMAP_RADIOOFF_ID));

    add(boxBackGnd);
    add(textRadioBtnInactive);
    add(textRadioBtnActive);
    add(imgRadioBtn);
}

void WildcardedRadioBtnBase::initialize()
{

}
