#ifndef SNCFGMENUVIEW_HPP
#define SNCFGMENUVIEW_HPP

#include <gui_generated/sncfgmenu_screen/SnCfgMenuViewBase.hpp>
#include <gui/sncfgmenu_screen/SnCfgMenuPresenter.hpp>
#include <gui/common/ZebraApplication.hpp>
#include <gui/containers/WildcardedMenuItem.hpp>
#include <gui/common/AppClasses.hpp>

class SnCfgMenuView : 
  public SnCfgMenuViewBase,
  public ConfigurationApp
{
public:
        
    ZEBRA_APPLICATION

    SnCfgMenuView();
    virtual ~SnCfgMenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void afterTransition();
    void selectNewItem();
    virtual void handleKeyEvent(uint8_t key);
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual void handleTickEvent();
    void BarcodeComeIn(char * BarcodeData);
    uint8_t getSelectedEntry();
    void jumpToHomeMenu();
    void jumpToConfigSubmenu(void);
    

protected:

private:
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    
    static const uint16_t MENUITEM_MAX = 10;
    FocusableIetm * MenuItem[MENUITEM_MAX];
    WildcardedMenuItem ccMenuItems[MENUITEM_MAX];
    
    uint8_t selectItem;
    uint8_t oldSelectItem;
    uint16_t toastCfgMenuViewTimer;
    uint8_t menuElementsCount;

    void dragScroll(int drag);
};

#endif // SNCFGMENUVIEW_HPP
