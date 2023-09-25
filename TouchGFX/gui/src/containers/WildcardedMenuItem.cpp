#include <gui/containers/WildcardedMenuItem.hpp>
#include <gui/common/ColorPalette.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <cstdio>

WildcardedMenuItem::WildcardedMenuItem()
{

}

void WildcardedMenuItem::initialize()
{
    WildcardedMenuItemBase::initialize();
}

void WildcardedMenuItem::setText(const std::string text)
{
    /* We need to transform ASCII array to unicode. In C++,
     * transform an uint8_t array to uint16_t
     */
    Unicode::UnicodeChar unicode_text[CONSOLIDATED_STR_MAX_SIZE + 1];

    for(uint8_t i = 0; i < text.size() + 1; i++)
    {
        unicode_text[i] = text[i];
    }
    activeTextString = text;
    activeTextString.erase(0,2);
    Unicode::snprintf(textMenuItemActiveBuffer, text.size() + 1, "%s", unicode_text);
    Unicode::snprintf(textMenuItemInactiveBuffer, text.size() + 1, "%s", unicode_text);

    textMenuItemActive.resizeToCurrentText();
    textMenuItemActive.invalidate();
    
    textMenuItemInactive.resizeToCurrentText();
    textMenuItemInactive.invalidate();
    invalidate();
}

bool WildcardedMenuItem::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        textMenuItemActive.setVisible(true);
        textMenuItemInactive.setVisible(false);
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textMenuItemActive.setVisible(false);
        textMenuItemInactive.setVisible(true);
    }
    invalidate();
    return (true);
}

bool WildcardedMenuItem::GreyItem(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(DARK_GREY);
        textMenuItemActive.setVisible(true);
        textMenuItemInactive.setVisible(false);
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textMenuItemActive.setVisible(false);
        textMenuItemInactive.setVisible(true);
    }
    invalidate();
    return (true);
}

std::string WildcardedMenuItem::getString()
{
  return activeTextString;
}
