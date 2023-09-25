#ifndef WILDCARDEDMENUITEM_HPP
#define WILDCARDEDMENUITEM_HPP

#include <gui_generated/containers/WildcardedMenuItemBase.hpp>
#include <string>
#include <gui/common/FocusableIetm.hpp>

class WildcardedMenuItem : public WildcardedMenuItemBase, public FocusableIetm
{
public:
    WildcardedMenuItem();
    virtual ~WildcardedMenuItem() {}

    virtual void initialize();

    void setText(std::string text);
    virtual bool setFocus(bool selected);
    virtual bool GreyItem(bool selected);
    std::string getString();

protected:
  std::string activeTextString;
};

#endif // WILDCARDEDMENUITEM_HPP
