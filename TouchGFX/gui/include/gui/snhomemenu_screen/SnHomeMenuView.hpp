#ifndef SNHOMEMENUVIEW_HPP
#define SNHOMEMENUVIEW_HPP

#include <gui_generated/snhomemenu_screen/SnHomeMenuViewBase.hpp>
#include <gui/snhomemenu_screen/SnHomeMenuPresenter.hpp>
#include <gui/common/FocusableIetm.hpp>
#include <gui/containers/WildcardedMenuItem.hpp>
#include <gui/containers/SnBackGnd.hpp>
#include <gui/containers/StatusBar.hpp>
#include <gui/common/AppClasses.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/containers/ListLayout.hpp>

class SnHomeMenuView : 
  public SnHomeMenuViewBase,
  public ZebraPlatformScreen
{
public:
    SnHomeMenuView();
    virtual ~SnHomeMenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void afterTransition();
    void selectNewItem();
    virtual void handleKeyEvent(uint8_t key);
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    void ChangeScreen();
    

    void scrollListDown();
    void scrollListUp();
    void scrollToItem(uint8_t key);
    uint8_t getSelectedEntry();

protected:

private:
    static const uint16_t MENUITEM_MAX = 10;
    FocusableIetm * MenuItem[MENUITEM_MAX];
    WildcardedMenuItem ccMenuItems[MENUITEM_MAX];

    uint8_t selectItem;
    uint8_t oldSelectItem;

    void dragScroll(int drag);
};

#endif // SNHOMEMENUVIEW_HPP
