#include <gui/containers/WildcardedRadioBtn.hpp>
#include <gui/common/ColorPalette.hpp>
#include "BitmapDatabase.hpp"

WildcardedRadioBtn::WildcardedRadioBtn() :
    bRadioOn(false)
{

}

void WildcardedRadioBtn::initialize()
{
    WildcardedRadioBtnBase::initialize();
}

void WildcardedRadioBtn::setText(const std::string text)
{
    /* We need to transform ASCII array to unicode. In C++,
     * transform an uint8_t array to uint16_t
     */
    Unicode::UnicodeChar unicode_text[20];

    for(uint8_t i = 0; i < text.size() + 1; i++)
    {
        unicode_text[i] = text[i];
    }

    Unicode::snprintf(textRadioBtnActiveBuffer, text.size() + 1, "%s", unicode_text);
    Unicode::snprintf(textRadioBtnInactiveBuffer, text.size() + 1, "%s", unicode_text);

    textRadioBtnActive.resizeToCurrentText();
    textRadioBtnActive.invalidate();
    
    textRadioBtnInactive.resizeToCurrentText();
    textRadioBtnInactive.invalidate();
    invalidate();
}

bool WildcardedRadioBtn::setFocus(bool selected)
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

bool WildcardedRadioBtn::setRadioOn(bool on)
{
    bRadioOn = on;
    return (bRadioOn);
}