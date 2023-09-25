#include <gui/containers/RadioBtn.hpp>
#include <gui/common/ColorPalette.hpp>
#include "BitmapDatabase.hpp"

RadioBtn::RadioBtn() :
    bRadioOn(false)
{

}

void RadioBtn::initialize()
{
    RadioBtnBase::initialize();
}

void RadioBtn::setMenuText(touchgfx::TypedText textInactive, touchgfx::TypedText textActive)
{
    textRadioBtnInactive.setTypedText(textInactive);
    textRadioBtnActive.setTypedText(textActive);
    invalidate();
}

bool RadioBtn::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        textRadioBtnActive.setVisible(true);
        textRadioBtnInactive.setVisible(false);
        imgRadioBtn.setBitmap( (bRadioOn) ? touchgfx::Bitmap(BITMAP_FOCUSRADIOON_ID) :
                                            touchgfx::Bitmap(BITMAP_FOCUSRADIOOFF_ID));
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textRadioBtnActive.setVisible(false);
        textRadioBtnInactive.setVisible(true);
        imgRadioBtn.setBitmap( (bRadioOn) ? touchgfx::Bitmap(BITMAP_RADIOON_ID) :
                                            touchgfx::Bitmap(BITMAP_RADIOOFF_ID));
    }
    invalidate();
    return (true);
}

bool RadioBtn::setRadioOn(bool on)
{
    bRadioOn = on;
    return (bRadioOn);
}

