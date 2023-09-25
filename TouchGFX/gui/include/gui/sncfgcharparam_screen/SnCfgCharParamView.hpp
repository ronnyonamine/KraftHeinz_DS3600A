#ifndef SNCFGCHARPARAMVIEW_HPP
#define SNCFGCHARPARAMVIEW_HPP

#include <gui_generated/sncfgcharparam_screen/SnCfgCharParamViewBase.hpp>
#include <gui/sncfgcharparam_screen/SnCfgCharParamPresenter.hpp>
#include <gui/containers/WildcardedRadioBtn.hpp>
#include <gui/common/AppClasses.hpp>

class SnCfgCharParamView : 
  public SnCfgCharParamViewBase,
  public ConfigurationApp,
  public SettingLeaf
{
public:
    SnCfgCharParamView();
    virtual ~SnCfgCharParamView() {}
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
    bool cccOverridevisiblity();
    bool cccContinuevisibility();
    void cccOverrideChange(bool change);
    void cccContinueChange(bool change);
    std::string getCfgParamaApp();
    std::string getCfgParamName();
	
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

#endif // SNCFGCHARPARAMVIEW_HPP
