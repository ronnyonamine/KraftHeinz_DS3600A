#ifndef SNCFGSTRINGPARAMVIEW_HPP
#define SNCFGSTRINGPARAMVIEW_HPP

#include <gui_generated/sncfgstringparam_screen/SnCfgStringParamViewBase.hpp>
#include <gui/sncfgstringparam_screen/SnCfgStringParamPresenter.hpp>
#include <gui/containers/WildcardedRadioBtn.hpp>
#include <gui/common/AppClasses.hpp>

class SnCfgStringParamView : 
  public SnCfgStringParamViewBase,
  public ConfigurationApp,
  public SettingLeaf
{
public:
    SnCfgStringParamView();
    virtual ~SnCfgStringParamView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    virtual void afterTransition();
    void selectNewItem();
    virtual void handleKeyEvent(uint8_t key);
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual void handleTickEvent();
    void BarcodeComeIn(char * BarcodeData);
    
    void scrollListDown();
    void scrollListUp();
    uint8_t getSelectedEntry();
    void confirmSelectedEntry();
    bool isEditBarSelected();
    void selectEditBar();
    void eraseEditBarChar();
    void moveEditCursorLeft();
    void moveEditCursorRight();
    void commitEditBar();
    void cancelEditBar();
    
    void exitScreen();
    
protected:
private:
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    static const uint16_t MENUITEM_MAX = 15;
    
    FocusableIetm * MenuItem[MENUITEM_MAX];
    WildcardedRadioBtn ccMenuItems[MENUITEM_MAX];
    
    uint8_t selectItem;
    uint8_t RadioOnItem;
    uint8_t oldSelectItem;
    uint16_t toastCfgMenuViewTimer;
    uint8_t menuElements;

    void dragScroll(int drag);
};

#endif // SNCFGSTRINGPARAMVIEW_HPP
