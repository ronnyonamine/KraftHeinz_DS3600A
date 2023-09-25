#include <gui/sncfgboolparam_screen/SnCfgBoolParamView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/ConfigParam.hpp>
#include <gui/common/platform_itf.h>

#define LAUNCH_SCREEN 7

SnCfgBoolParamView::SnCfgBoolParamView():
    selectItem(1),
    RadioOnItem(2),
    toastCfgMenuViewTimer(TOASTVIEW_TIMEOUT)
{
    /* Add Back button manually */
    MenuItem[0] = &ccBack;
    
    /* Retrive index of parameter to handle */
    uint16_t idx = application().retrieveParamIndex();
    /* Retrieve parameter to handle */
    ConfigParam param = ConfigParam::GetParameters()[idx];
    if(param.default_value == 0x01)
    {
      ccMenuItems[0].setText("No");
      ccMenuItems[1].setText("Yes (Default)");
    }
    else
    {
      ccMenuItems[0].setText("No (Default)");
      ccMenuItems[1].setText("Yes");
    }
    
    MenuItem[1] = &ccMenuItems[0];
    MenuItem[2] = &ccMenuItems[1];
    listLayout.add(ccMenuItems[0]);
    listLayout.add(ccMenuItems[1]);
}

void SnCfgBoolParamView::setupScreen()
{
    SnCfgBoolParamViewBase::setupScreen();
    
    selectItem = 1;
    /* Retrive index of parameter to handle */
    uint16_t idx = application().retrieveParamIndex();
    /* Retrieve parameter to handle */
    ConfigParam param = ConfigParam::GetParameters()[idx];
    uint8_t paramValue;
    presenter->retrieveParamValue(idx, &paramValue);
    
    /* Check for out of range */
    if(paramValue > 0x01 )
    {
      paramValue = param.default_value;
      presenter->storeParamValue(idx, &paramValue, 1);
    }
    RadioOnItem = paramValue +1;
    
    MenuItem[RadioOnItem]->setRadioOn(true);
    presenter->UpdateAllIcons();
    presenter->setCurrentScreen(NO_SPL_FEATURE);
    presenter->setBackArrowActive(false);
    selectNewItem();
 //   if(getCfgParamaApp() != "Global" )
    {
      if(getCfgParamName() == "Manual BC Entry" || getCfgParamName() == "Manual QTY Entry")
      {
        imgRight.setVisible(true);
        labelAbout.setVisible(true);      
      }
    }
}

void SnCfgBoolParamView::tearDownScreen()
{
    SnCfgBoolParamViewBase::tearDownScreen();
}

void SnCfgBoolParamView::BarcodeComeIn(char * BarcodeData)
{
    presenter->clearBarcode();

    toastCfgMenuViewTimer = 0;                  // Enable Toast view timer
    cccfgMenuToast.setVisible(true);
    cccfgMenuToast.invalidate();
    SendAvoidTransmissionDecodeDataCommand();  //Beeper 0x49
}

void SnCfgBoolParamView::handleKeyEvent(uint8_t key)
{
    presenter->keyPressed(key);
}

void SnCfgBoolParamView::handleTickEvent()
{
    if (toastCfgMenuViewTimer < TOASTVIEW_TIMEOUT)
    {
        toastCfgMenuViewTimer++;
        if (toastCfgMenuViewTimer == TOASTVIEW_TIMEOUT)    // toast view timeout
        {
            cccfgMenuToast.setVisible(false);
            cccfgMenuToast.invalidate();
        }
    }
}

//Called when the screen is done with transition/load
void SnCfgBoolParamView::afterTransition()
{

}

void SnCfgBoolParamView::selectNewItem()
{
    for (int i = 0; i < MENUITEM_MAX; i++)
    {
        MenuItem[i]->setFocus(selectItem == i);
    }
}

void SnCfgBoolParamView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnCfgBoolParamView::scrollListDown()
{
  selectItem = (selectItem == (MENUITEM_MAX - 1)) ? (MENUITEM_MAX - 1) : selectItem + 1;
  selectNewItem();
}

void SnCfgBoolParamView::scrollListUp()
{
  selectItem = (selectItem == 0) ? 0 : selectItem - 1;
  selectNewItem();
}

uint8_t SnCfgBoolParamView::getSelectedEntry()
{
    return selectItem;
}

void SnCfgBoolParamView::exitScreen()
{
  application().gotoSnCfgAppSubMenuScreenNoTransition();
}

void SnCfgBoolParamView::confirmSelectedEntry()
{
  MenuItem[RadioOnItem]->setRadioOn(false);
  RadioOnItem = selectItem;
  MenuItem[RadioOnItem]->setRadioOn(true);
  selectNewItem();
  uint16_t idx = application().retrieveParamIndex();
  uint8_t val = RadioOnItem-1;
  presenter->storeParamValue(idx, &val, 1);
}

bool SnCfgBoolParamView::cccOverridevisiblity()
{
  if(cOverride.isVisible())
    return true;
  else
    return false;
}

void SnCfgBoolParamView::cccOverrideChange(bool change)
{
  if(change)
  {
    cOverride.setVisible(true);
    cOverride.invalidate();
  }
  else 
  {
    cOverride.setVisible(false);
    cOverride.invalidate();
  }
}

bool SnCfgBoolParamView::cccContinuevisibility()
{
  if (cContinue.isVisible())
    return true;
  else
    return false;
}

void SnCfgBoolParamView::cccContinueChange(bool change)
{
  if(change)
  {
     if(getCfgParamaApp() == "Scan & Enter Qty" )
     {
        textNormal_Continue_2.setWildcard(touchgfx::TypedText(T_TEXTVIEW_05_H2).getText());
     }
      else if (getCfgParamaApp() == "Scan & Ent Loc")
      {
        textNormal_Continue_2.setWildcard(touchgfx::TypedText(T_TEXTVIEW_05_H3).getText());
      }
     else if (getCfgParamaApp() == "Scan Inventory")
     {
       textNormal_Continue_2.setWildcard(touchgfx::TypedText(T_TEXTVIEW_05_H4).getText());
     }
        cContinue.setVisible(true);
        cContinue.invalidate();
        
  }
  else 
  {
    cContinue.setVisible(false);
    cContinue.invalidate();
  }
}

bool SnCfgBoolParamView::cccAboutVisibility()
{
  if(cAbout.isVisible())
    return true;
  else 
    return false;
}

void SnCfgBoolParamView::cccAboutChange(bool change)
{
  if(change)
  {
      if(getCfgParamName() == "Manual BC Entry")
      {
        textNormal_About.setWildcard(touchgfx::TypedText(T_TEXTVIEW_02).getText());
      }
      else if(getCfgParamName() == "Manual QTY Entry")
      {
        textNormal_About.setWildcard(touchgfx::TypedText(T_TEXTVIEW_03).getText());
      }
      cAbout.setVisible(change);
      cAbout.invalidate();
  }
   else
   {
      cAbout.setVisible(change);
      cAbout.invalidate();
   }
}

std::string SnCfgBoolParamView::getCfgParamaApp()
{
    uint8_t index = 0;
    std::string app = application().retrieveAppName();
    ConfigParam conf = ConfigParam::GetAppParameters(app)[index];
    return conf.app_name;
}

std::string SnCfgBoolParamView::getCfgParamName()
{
  
  uint16_t idx = application().retrieveParamIndex();
  ConfigParam param = ConfigParam::GetParameters()[idx];
  return param.short_name;
}

bool SnCfgBoolParamView::imgRightVisible()
{
  if(imgRight.isVisible() && labelAbout.isVisible())
    return true;
  return false;
}
