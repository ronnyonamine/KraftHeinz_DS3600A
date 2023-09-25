#ifndef SNCFGBOOLPARAMVIEW_HPP
#define SNCFGBOOLPARAMVIEW_HPP

#include <gui_generated/sncfgboolparam_screen/SnCfgBoolParamViewBase.hpp>
#include <gui/sncfgboolparam_screen/SnCfgBoolParamPresenter.hpp>
#include <gui/containers/WildcardedRadioBtn.hpp>
#include <gui/common/AppClasses.hpp>


class SnCfgBoolParamView : 
  public SnCfgBoolParamViewBase,
  public ConfigurationApp,
  public SettingLeaf
{
public:
    SnCfgBoolParamView();
    virtual ~SnCfgBoolParamView() {}
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
    void exitScreen();
    void confirmSelectedEntry();
    bool cccOverridevisiblity();
    bool cccContinuevisibility();
    void cccOverrideChange(bool change);
    void cccContinueChange(bool change);
    void cccAboutChange(bool change);
    bool cccAboutVisibility();
    std::string getCfgParamaApp();
    std::string getCfgParamName();
    bool imgRightVisible();
    
	
protected:

private:
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    static const uint16_t MENUITEM_MAX = 3;
    
    FocusableIetm * MenuItem[MENUITEM_MAX];
    WildcardedRadioBtn ccMenuItems[MENUITEM_MAX];
    
    uint8_t selectItem;
    uint8_t RadioOnItem;
    uint16_t toastCfgMenuViewTimer;
};

#endif // SNCFGBOOLPARAMVIEW_HPP
