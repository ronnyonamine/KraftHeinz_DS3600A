#ifndef SNFNKEYASSIGNVIEW_HPP
#define SNFNKEYASSIGNVIEW_HPP

#include <gui_generated/snfnkeyassign_screen/SnFnKeyAssignViewBase.hpp>
#include <gui/snfnkeyassign_screen/SnFnKeyAssignPresenter.hpp>
#include <gui/containers/WildcardedRadioBtn.hpp>
#include <gui/common/AppClasses.hpp>

class SnFnKeyAssignView : 
  public SnFnKeyAssignViewBase,
  public ConfigurationApp,
  public SettingLeaf
{
public:
    SnFnKeyAssignView();
    virtual ~SnFnKeyAssignView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void afterTransition();
    void selectNewItem();
    virtual void handleKeyEvent(uint8_t key);
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual void handleTickEvent();
    void BarcodeComeIn(char * BarcodeData);

protected:

private:
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    static const uint16_t MENUITEM_MAX = 7;
    
    FocusableIetm * MenuItem[MENUITEM_MAX];
    WildcardedRadioBtn ccMenuItems[MENUITEM_MAX-2];
    
    uint16_t stringIdx;
    uint16_t radioIdx;
    uint8_t menuElements;
    
    uint8_t selectItem;
    uint8_t RadioOnItem;
    uint8_t FnKeySelected;
    uint8_t oldSelectItem;
    uint16_t toastCfgMenuViewTimer;

    void dragScroll(int drag);
};

#endif // SNFNKEYASSIGNVIEW_HPP
