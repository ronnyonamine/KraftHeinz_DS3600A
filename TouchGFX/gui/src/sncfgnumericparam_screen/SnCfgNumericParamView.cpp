#include <gui/sncfgnumericparam_screen/SnCfgNumericParamView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/platform_itf.h>
#include <gui/common/ConfigParam.hpp>

#define LAUNCH_SCREEN 7

SnCfgNumericParamView::SnCfgNumericParamView():
    selectItem(2),
    RadioOnItem(2),
    oldSelectItem(2),
    toastCfgMenuViewTimer(TOASTVIEW_TIMEOUT)
{
    /* Retrive index of parameter to handle */
    uint16_t idx = application().retrieveParamIndex();
    /* Retrieve parameter to handle */
    ConfigParam param = ConfigParam::GetParameters()[idx];
    uint8_t offset = 1;
    
    menuElements = 0;
    totalItem[menuElements] = &ccBack;
    menuElements++;
    
    /* We only need it on the scrolling list if we intend to show it */
    listLayout.remove(ccEntField);
    
    /* Check if the parameter iself is allower to be user-editable */
    if(param.param_descr->isUserCofigurable())
    {
      listLayout.add(ccEntField);
      totalItem[menuElements] = &ccEntField;
      menuElements++;
      offset = 2;
    }
    
    /* Check if presets will be shown */
    if (param.param_descr->hasPresetValues())
    {
        for(std::string val_name : param.param_descr->GetRadioNames())
        {        
            if (val_name.size() >= 20)
            {
              val_name.erase(19, std::string::npos);
            }
            ccMenuItems[menuElements - offset].setText(val_name.c_str());
            totalItem[menuElements] = &ccMenuItems[menuElements - offset];
            listLayout.add(ccMenuItems[menuElements - offset]);
            menuElements++;
        }
    }
    /* Hide OR text if not */
    else
    {
      ccEntField.setTextORVisible(false);
    }
}

void SnCfgNumericParamView::setupScreen()
{
  SnCfgNumericParamViewBase::setupScreen();
  selectItem = 0;  
  /* Retrive index of parameter to handle */
  uint16_t idx = application().retrieveParamIndex();
  /* Retrieve parameter to handle */
  ConfigParam param = ConfigParam::GetParameters()[idx];
  uint8_t offset = 1;
  
  /* Allocate for worse case scenario */
  uint32_t paramValue = 0;
  presenter->retrieveParamValue(idx, (uint8_t*)&paramValue);
  
  uint32_t param_min = param.param_descr->getRangeMin();
  uint32_t param_max = param.param_descr->getRangeMax();
  
  /* Only edit entry field if needed */
  if(param.param_descr->isUserCofigurable())
  {
    offset = 2;
    ccEntField.setDefaultText(param.param_descr->getParamLabel()+ '\0');
    ccEntField.setLabel("(" +std::to_string(param_min) +
                        " - " + 
                        std::to_string(param_max) +
                        ")" + '\0'  );
  }
  
  /* Check for out of range/empty */
  if(( paramValue == 0xFFFFFFFF ) ||
     ( paramValue < param_min  ) ||
     ( paramValue > param_max  ) )
  {
    paramValue = param.default_value;
    presenter->storeParamValue(idx, (uint8_t*) &paramValue, param.param_size);
  }
  /* Check if the value corresponds to any preset */
  uint8_t i = 0;
  
  /* Assume nothing */
  RadioOnItem = 0;
  
  /* Check only if show preset values is true */
  if (param.param_descr->hasPresetValues())
  {
    for(uint8_t presetValue: param.param_descr->GetPresetValues())
    {
      /* If it is equal to a preset, set that one instead */
      if(presetValue == paramValue)
      {
        RadioOnItem = i+offset;
        selectItem = offset;
        break;
      }
      i++;
    }
  }
  
  /* If not equal to a preset and is user configurable */
  if((RadioOnItem == 0)&&(param.param_descr->isUserCofigurable()))
  {
    ccEntField.insNumber(paramValue);
    RadioOnItem = 1;
    selectItem = 1;
  }
  
  if(RadioOnItem)
  {
    totalItem[RadioOnItem]->setRadioOn(true);
  }
  
  presenter->UpdateAllIcons();
  presenter->setCurrentScreen(NO_SPL_FEATURE);
  presenter->setBackArrowActive(false);
  selectNewItem();
  scrollCnt.setScrollbarWidth(4);
  dragScroll(-1);
  dragScroll(1);
  scrollCnt.invalidate();
  oldSelectItem = selectItem;
}

void SnCfgNumericParamView::tearDownScreen()
{
    SnCfgNumericParamViewBase::tearDownScreen();
}


void SnCfgNumericParamView::BarcodeComeIn(char * BarcodeData)
{
    presenter->clearBarcode();

    toastCfgMenuViewTimer = 0;                  // Enable Toast view timer
    cccfgMenuToast.setVisible(true);
    cccfgMenuToast.invalidate();
    SendAvoidTransmissionDecodeDataCommand();  //Beeper 0x49
}

void SnCfgNumericParamView::handleKeyEvent(uint8_t key)
{
    if (ccEntField.isEditing())
    {
      if ((key >= '0') && (key <= '9'))
      {
        ccEntField.insDigit(key);
      }
    }
    presenter->keyPressed(key);
}

void SnCfgNumericParamView::scrollListUp()
{
    selectItem = (selectItem == 0) ? 0 : selectItem - 1;
    dragScroll(oldSelectItem - selectItem);
    selectNewItem();
    oldSelectItem = selectItem;
}

void SnCfgNumericParamView::scrollListDown()
{
    selectItem = (selectItem == (menuElements -1 )) ? (menuElements -1) : selectItem + 1;
    dragScroll(oldSelectItem - selectItem);
    selectNewItem();
    oldSelectItem = selectItem;
}

uint8_t SnCfgNumericParamView::getSelectedEntry()
{
    return selectItem;
}

void SnCfgNumericParamView::confirmSelectedEntry()
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
  
  totalItem[RadioOnItem]->setRadioOn(false);
  RadioOnItem = selectItem;
  totalItem[RadioOnItem]->setRadioOn(true);
  selectNewItem();
  /* Check for Editable Case */
  if((selectItem == 1)&&(offset == 2))
  {
    selectEditBar();
    return;
  }

  uint32_t val =  param.param_descr->GetPresetValues()[selectItem-offset];
  presenter->storeParamValue(idx, (uint8_t*)&val , param.param_size);
}

void SnCfgNumericParamView::handleTickEvent()
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
void SnCfgNumericParamView::afterTransition()
{

}

void SnCfgNumericParamView::selectNewItem()
{
    for (int i = 0; i < menuElements; i++)
    {
        totalItem[i]->setFocus(selectItem == i);
    }
}

void SnCfgNumericParamView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnCfgNumericParamView::dragScroll(int drag)
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

void SnCfgNumericParamView::exitScreen()
{
  application().gotoSnCfgAppSubMenuScreenNoTransition();
}

void SnCfgNumericParamView::selectEditBar()
{
  totalItem[RadioOnItem]->setRadioOn(false);
  RadioOnItem = selectItem;
  selectNewItem();
  ccEntField.setEdit(true);
}

bool SnCfgNumericParamView::isEditBarSelected()
{
  return ccEntField.isEditing();
}

void SnCfgNumericParamView::moveEditCursorLeft()
{
  ccEntField.moveCursorLeft();
}

void SnCfgNumericParamView::moveEditCursorRight()
{
  ccEntField.moveCursorRight();
}

void SnCfgNumericParamView::eraseEditBarChar()
{
  ccEntField.delDigit();
}

void SnCfgNumericParamView::commitEditBar()
{
  ccEntField.setEdit(false);
  
  uint16_t idx = application().retrieveParamIndex();
  ConfigParam param = ConfigParam::GetParameters()[idx];
  uint32_t input = ccEntField.getText();
  
  /* Set input within bounds - check signedness for min*/
  if(param.param_sign)
  {
    int32_t rangeMin = (int32_t)param.param_descr->getRangeMin();
    if( (int32_t)input < rangeMin )
    {
      input = param.param_descr->getRangeMin();
      ccEntField.insNumber(input);
    }
  }
  else
  {
    if( input < param.param_descr->getRangeMin() )
    {
      input = param.param_descr->getRangeMin();
      ccEntField.insNumber(input);
    }
  }
  if( input > param.param_descr->getRangeMax() )
  {
    input = param.param_descr->getRangeMax();
    ccEntField.insNumber(input);
  }
  
  presenter->storeParamValue(idx, (uint8_t*)&input, param.param_size);
}

void SnCfgNumericParamView::cancelEditBar()
{
  //ccEntField.setNextScan();                     //fix for DC-28025
  totalItem[RadioOnItem]->setRadioOn(false);
  RadioOnItem = 5;
  presenter->setLocDelimiter(RadioOnItem, 0);
  totalItem[RadioOnItem]->setRadioOn(true);
  selectNewItem();
}

bool SnCfgNumericParamView::cccOverridevisiblity()
{
  if(cOverride.isVisible())
    return true;
  else
    return false;
}

void SnCfgNumericParamView::cccOverrideChange(bool change)
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

bool SnCfgNumericParamView::cccContinuevisibility()
{
  if (cContinue.isVisible())
    return true;
  else
    return false;
}

void SnCfgNumericParamView::cccContinueChange(bool change)
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

std::string SnCfgNumericParamView::getCfgParamaApp()
{
    uint8_t index = 0;
    std::string app = application().retrieveAppName();
    ConfigParam conf = ConfigParam::GetAppParameters(app)[index];
    return conf.app_name;
}

std::string SnCfgNumericParamView::getCfgParamName()
{
  
  uint16_t idx = application().retrieveParamIndex();
  ConfigParam param = ConfigParam::GetParameters()[idx];
  return param.short_name;
}
