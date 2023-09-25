#include <gui/containers/MenuItem.hpp>
#include <gui/common/ColorPalette.hpp>

MenuItem::MenuItem()
{

}

void MenuItem::initialize()
{
    MenuItemBase::initialize();
}

void MenuItem::setMenuText(touchgfx::TypedText textInactive, touchgfx::TypedText textActive)
{
    textMenuItemInactive.setTypedText(textInactive);
    textMenuItemActive.setTypedText(textActive);
    invalidate();
}

bool MenuItem::setFocus(bool selected)
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

bool MenuItem::GreyItem(bool selected)
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