#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include <gui_generated/containers/MenuItemBase.hpp>
#include <gui/common/FocusableIetm.hpp>

class MenuItem : public MenuItemBase, public FocusableIetm
{
public:
    MenuItem();
    virtual ~MenuItem() {}

    virtual void initialize();

    void setMenuText(touchgfx::TypedText textInactive, touchgfx::TypedText textActive);
    virtual bool setFocus(bool selected);
    virtual bool GreyItem(bool selected);

protected:
};

#endif // MENUITEM_HPP
