#ifndef SNCFGAPPSUBMENUVIEW_HPP
#define SNCFGAPPSUBMENUVIEW_HPP

#include <gui_generated/sncfgappsubmenu_screen/SnCfgAppSubMenuViewBase.hpp>
#include <gui/sncfgappsubmenu_screen/SnCfgAppSubMenuPresenter.hpp>
#include <gui/containers/WildcardedMenuItem.hpp>
#include <gui/common/AppClasses.hpp>
#include <gui/common/ConfigParam.hpp>

class SnCfgAppSubMenuView : 
  public SnCfgAppSubMenuViewBase,
  public ConfigurationApp
{
public:
    SnCfgAppSubMenuView();
    virtual ~SnCfgAppSubMenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    virtual void afterTransition();
    void selectNewItem();
    virtual void handleKeyEvent(uint8_t key);
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual void handleTickEvent();
    void BarcodeComeIn(char * BarcodeData);
    
    uint8_t getSelectedEntry();
    void jumpToPrevScreen();
    void jumpToParamConfig();
    
protected:
private:
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    static const uint16_t MENUITEM_MAX = 20;
    FocusableIetm * MenuItem[MENUITEM_MAX];
    WildcardedMenuItem ccMenuItems[MENUITEM_MAX];
    
    
    uint8_t selectItem;
    uint8_t oldSelectItem;
    uint16_t toastCfgMenuViewTimer;
    uint8_t menuElements;
    
    uint8_t homeMenuCfgIdx;
    int16_t FnKeyMenuCfgIdx;
	static const uint16_t KEY_SELECTION_TIMEOUT = 40;	
    uint16_t keyClickTimer;
    uint8_t newSelectItem;
    bool FirstKeyPressed;

    
    void dragScroll(int drag);
};

#endif // SNCFGAPPSUBMENUVIEW_HPP
