#include <gui/sncfgcharparam_screen/SnCfgCharParamView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/platform_itf.h>
#include <gui/common/ConfigParam.hpp>

#define LAUNCH_SCREEN 7


SnCfgCharParamView::SnCfgCharParamView():
    selectItem(1),
    RadioOnItem(2),
    oldSelectItem(1),
    toastCfgMenuViewTimer(TOASTVIEW_TIMEOUT)
{
    /* Retrive index of parameter to handle */
    uint16_t idx = application().retrieveParamIndex();
    /* Retrieve parameter to handle */
    ConfigParam param = ConfigParam::GetParameters()[idx];
    uint8_t offset = 1;
    
    menuElements = 0;
    MenuItem[menuElements] = &ccBack;
    menuElements++;
    
    /* We only need it on the scrolling list if we intend to show it */
    listLayout.remove(ccEntField);
    
    /* Check if the parameter iself is allower to be user-editable */
    if(param.param_descr->isUserCofigurable())
    {
      listLayout.add(ccEntField);
      MenuItem[menuElements] = &ccEntField;
      menuElements++;
      offset = 2;
    }
    
    for(std::string val_name : param.param_descr->GetRadioNames())
    {        
        if (val_name.size() >= 20)
        {
          val_name.erase(19, std::string::npos);
        }
        ccMenuItems[menuElements - offset].setText(val_name.c_str());
        MenuItem[menuElements] = &ccMenuItems[menuElements - offset];
        listLayout.add(ccMenuItems[menuElements - offset]);
        menuElements++;
    }
    
}

void SnCfgCharParamView::setupScreen()
{
  SnCfgCharParamViewBase::setupScreen();
  selectItem = 2;
  /* Retrive index of parameter to handle */
  uint16_t idx = application().retrieveParamIndex();
  /* Retrieve parameter to handle */
  ConfigParam param = ConfigParam::GetParameters()[idx];
  uint8_t offset = 1;
  
  uint8_t paramValue;
  presenter->retrieveParamValue(idx, &paramValue);
  
   /* Only edit entry field if needed */
  if(param.param_descr->isUserCofigurable())
  {
    offset = 2;
    ccEntField.setDefaultText("Enter " + param.param_descr->getParamLabel());
  }
    
  
  /* Check for out of range/empty */
  if( paramValue == 0xFF || paramValue == 0 )
  {
    paramValue = param.default_value;
    presenter->storeParamValue(idx, &paramValue, 1);
  }
  /* Check if the value corresponds to any preset */
  uint8_t i = 0;
  
  /* Assume nothing */
  RadioOnItem = 0;
  
  for(uint8_t presetValue: param.param_descr->GetPresetValues())
  {
    /* If it is equal to a preset, set that one instead */
    if(presetValue == paramValue)
    {
      RadioOnItem = i+offset;
      break;
    }
    i++;
  }
  
  /* If not equal to a preset and is user configurable */
  if(param.param_descr->isUserCofigurable())
  {
    if(RadioOnItem == 0)
    {
      ccEntField.insCh(paramValue);
    }
    else
    {
      ccEntField.setLabel(param.param_descr->getParamLabel());
    } 
  }
  
  if(RadioOnItem)
  {
    MenuItem[RadioOnItem]->setRadioOn(true);
  }
  
  presenter->UpdateAllIcons();
  presenter->setCurrentScreen(NO_SPL_FEATURE);
  presenter->setBackArrowActive(false);
  selectNewItem();
  scrollCnt.setScrollbarWidth(4);
  dragScroll(-1);
  dragScroll(1);
  scrollCnt.invalidate();
}

void SnCfgCharParamView::tearDownScreen()
{
    SnCfgCharParamViewBase::tearDownScreen();
}


void SnCfgCharParamView::BarcodeComeIn(char * BarcodeData)
{
    presenter->clearBarcode();

    toastCfgMenuViewTimer = 0;                  // Enable Toast view timer
    cccfgMenuToast.setVisible(true);
    cccfgMenuToast.invalidate();
    SendAvoidTransmissionDecodeDataCommand();  //Beeper 0x49
}

void SnCfgCharParamView::handleKeyEvent(uint8_t key)
{
    if (ccEntField.isEditing())
    {
      if ((key >= 0x20) && (key <= 0x7E))
      {
        ccEntField.modifyCh(key);
      }
      if ((key >= 0x81) && (key <= 0xDF))     // for multi tap
      {
        ccEntField.modifyCh(~(key));
      }
    }
    presenter->keyPressed(key);
}

void SnCfgCharParamView::scrollListUp()
{
    selectItem = (selectItem == 0) ? 0 : selectItem - 1;
    dragScroll(oldSelectItem - selectItem);
    selectNewItem();
    oldSelectItem = selectItem;
}

void SnCfgCharParamView::scrollListDown()
{
    selectItem = (selectItem == (menuElements -1 )) ? (menuElements -1) : selectItem + 1;
    dragScroll(oldSelectItem - selectItem);
    selectNewItem();
    oldSelectItem = selectItem;
}

uint8_t SnCfgCharParamView::getSelectedEntry()
{
    return selectItem;
}

void SnCfgCharParamView::confirmSelectedEntry()
{
  /* Retrive index of parameter to handle */
  uint16_t idx = application().retrieveParamIndex();
  /* Retrieve parameter to handle */
  ConfigParam param = ConfigParam::GetParameters()[idx];
  uint8_t offset = 1;
  if(param.param_descr->isUserCofigurable())
  {
    offset = 2;
  }
  
  MenuItem[RadioOnItem]->setRadioOn(false);
  RadioOnItem = selectItem;
  MenuItem[RadioOnItem]->setRadioOn(true);
  selectNewItem();
  
  /* Check for Editable Case */
  if((selectItem == 1)&&(offset == 2))
  {
    selectEditBar();
    return;
  }

  uint8_t val = param.param_descr->GetPresetValues()[selectItem-offset];
  presenter->storeParamValue(idx, &val, 1); 
}

void SnCfgCharParamView::handleTickEvent()
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
void SnCfgCharParamView::afterTransition()
{

}

void SnCfgCharParamView::selectNewItem()
{
    for (int i = 0; i < menuElements; i++)
    {
        MenuItem[i]->setFocus(selectItem == i);
    }
}

void SnCfgCharParamView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnCfgCharParamView::dragScroll(int drag)
{
    if (oldSelectItem == 0)
    {
        if (selectItem < 4)
            return;
        else
            drag += 2;
    }

    int16_t xPos = scrollCnt.getScrolledX();
    int16_t yOldPos = scrollCnt.getScrolledY();
    int16_t yNewPos = yOldPos + (64 * drag);
    DragEvent relative(DragEvent::DRAGGED, xPos, yOldPos, xPos, yNewPos);
    scrollCnt.handleDragEvent(relative);
}

void SnCfgCharParamView::exitScreen()
{
  application().gotoSnCfgAppSubMenuScreenNoTransition();
}

void SnCfgCharParamView::selectEditBar()
{
  MenuItem[RadioOnItem]->setRadioOn(false);
  RadioOnItem = selectItem;
  selectNewItem();
  ccEntField.setEdit(true);
}

bool SnCfgCharParamView::isEditBarSelected()
{
  return ccEntField.isEditing();
}

void SnCfgCharParamView::moveEditCursorLeft()
{
  ccEntField.moveCursorLeft();
}

void SnCfgCharParamView::moveEditCursorRight()
{
  ccEntField.moveCursorRight();
}

void SnCfgCharParamView::eraseEditBarChar()
{
  ccEntField.delCh();
}

void SnCfgCharParamView::commitEditBar()
{
  ccEntField.setEdit(false);
  
  uint16_t idx = application().retrieveParamIndex();
  ConfigParam param = ConfigParam::GetParameters()[idx];
  char input = *ccEntField.getText();
  /* If input is empty, restore default */
  if(!input)
  {
    input = param.default_value;
  }
  
  presenter->storeParamValue(idx, (uint8_t*)&input, 1);
  
  selectNewItem();
}

void SnCfgCharParamView::cancelEditBar()
{
  ccEntField.setNextScan();
  MenuItem[RadioOnItem]->setRadioOn(false);
  RadioOnItem = 5;
  presenter->setLocDelimiter(RadioOnItem, 0);
  MenuItem[RadioOnItem]->setRadioOn(true);
  selectNewItem();
}

bool SnCfgCharParamView::cccOverridevisiblity()
{
  if(cOverride.isVisible())
    return true;
  else
    return false;
}

void SnCfgCharParamView::cccOverrideChange(bool change)
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

bool SnCfgCharParamView::cccContinuevisibility()
{
  if (cContinue.isVisible())
    return true;
  else
    return false;
}

void SnCfgCharParamView::cccContinueChange(bool change)
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

std::string SnCfgCharParamView::getCfgParamaApp()
{
    uint8_t index = 0;
    std::string app = application().retrieveAppName();
    ConfigParam conf = ConfigParam::GetAppParameters(app)[index];
    return conf.app_name;
}

std::string SnCfgCharParamView::getCfgParamName()
{
  
  uint16_t idx = application().retrieveParamIndex();
  ConfigParam param = ConfigParam::GetParameters()[idx];
  return param.short_name;
}