#include <gui/sncfgstringparam_screen/SnCfgStringParamView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/platform_itf.h>
#include <gui/common/ConfigParam.hpp>

#define LAUNCH_SCREEN 7

SnCfgStringParamView::SnCfgStringParamView():
    selectItem(1),
    RadioOnItem(2),
    oldSelectItem(1),
    toastCfgMenuViewTimer(TOASTVIEW_TIMEOUT)
{
    listLayout.remove(ccEntField);
    MenuItem[0] = &ccBack;
    menuElements = 1;

    /* Retrive index of parameter to handle */
    uint16_t idx = application().retrieveParamIndex();
    /* Retrieve parameter to handle */
    ConfigParam param = ConfigParam::GetParameters()[idx];
    
    /* Check if the user can enter custom strings */
    uint8_t user_editable = 0;
    if(param.param_descr->isUserCofigurable())
    {
      user_editable = 1;
      MenuItem[1] = &ccEntField;
      listLayout.add(ccEntField);
      menuElements++;
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
        ccMenuItems[menuElements - 1 - user_editable].setText(val_name.c_str());
        MenuItem[menuElements] = &ccMenuItems[menuElements - 1 - user_editable];
        listLayout.add(ccMenuItems[menuElements - 1 - user_editable]);
        menuElements++;
      }
    }
    /* Hide OR text if not */
    else
    {
      ccEntField.setTextORVisible(false);
    }
}

void SnCfgStringParamView::setupScreen()
{
  SnCfgStringParamViewBase::setupScreen();
  selectItem = 0;
  /* Retrive index of parameter to handle */
  uint16_t idx = application().retrieveParamIndex();
  /* Retrieve parameter to handle */
  ConfigParam param = ConfigParam::GetParameters()[idx];
  char paramValBuff[CONSOLIDATED_STR_MAX_SIZE + 1];
  presenter->retrieveParamValue(idx, (uint8_t*)paramValBuff);
  std::string paramValue(paramValBuff);

  ccEntField.setDefaultText("Enter " + param.param_descr->getParamLabel());
  /* Check only first byte for empty param - should have been handled on init */
  if( (uint8_t)paramValue[0] == 0xFF )
  {
    std::string def_string = param.param_descr->GetPresetStrings()[param.default_value]; 
    paramValue = def_string;
    presenter->storeParamValue(idx, const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(&paramValue)), paramValue.length());
  }
  /* Check if the string is part of the radio parameters */
  uint8_t user_editable = param.param_descr->isUserCofigurable()? 1:0;
  bool is_custom = true;
  /* Check only if show preset values is true */
  if (param.param_descr->hasPresetValues())
  {
    uint8_t i = 0;
    for(std::string presetValue: param.param_descr->GetPresetStrings())
    {
      /* IF value is equal to a preset, then the preset is the actual selection */
      if(presetValue.compare(paramValue)==0)
      {
        RadioOnItem = i + 1 + user_editable;
        is_custom = false;
        MenuItem[RadioOnItem]->setRadioOn(true);
        selectItem = 1 + user_editable;
        break;
      }
      i++;
    }
  }
  /* If it is user configurble and a custom value, set value in edit field */
  if(user_editable && is_custom)
  {
    ccEntField.clearText();
    ccEntField.setDefaultText(paramValue);
    ccEntField.setText(paramValue);
    RadioOnItem = 1;
    MenuItem[RadioOnItem]->setRadioOn(true);
    selectItem = RadioOnItem;
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

void SnCfgStringParamView::tearDownScreen()
{
    SnCfgStringParamViewBase::tearDownScreen();
}

//Called when the screen is done with transition/load
void SnCfgStringParamView::afterTransition()
{

}

void SnCfgStringParamView::handleKeyEvent(uint8_t key)
{
    if (ccEntField.isEditing())
    {
      if ((key >= 0x20) && (key <= 0x7E))
      {
        ccEntField.insCh(key);
      }
      if ((key >= 0x81) && (key <= 0xDF))     // for multi tap
      {
        ccEntField.modifyCh(~(key));
      }
    }
    presenter->keyPressed(key);
}

void SnCfgStringParamView::handleTickEvent()
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

void SnCfgStringParamView::BarcodeComeIn(char * BarcodeData)
{
    presenter->clearBarcode();

    toastCfgMenuViewTimer = 0;                  // Enable Toast view timer
    cccfgMenuToast.setVisible(true);
    cccfgMenuToast.invalidate();
    SendAvoidTransmissionDecodeDataCommand();  //Beeper 0x49
}

void SnCfgStringParamView::scrollListUp()
{
    selectItem = (selectItem == 0) ? 0 : selectItem - 1;
    dragScroll(oldSelectItem - selectItem);
    selectNewItem();
    oldSelectItem = selectItem;
}

void SnCfgStringParamView::scrollListDown()
{
    selectItem = (selectItem == (menuElements -1 )) ? (menuElements -1) : selectItem + 1;
    dragScroll(oldSelectItem - selectItem);
    selectNewItem();
    oldSelectItem = selectItem;
}

uint8_t SnCfgStringParamView::getSelectedEntry()
{
    return selectItem;
}

void SnCfgStringParamView::confirmSelectedEntry()
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
  
  std::string val = param.param_descr->GetPresetStrings()[selectItem-offset];
  presenter->storeParamValue(idx, const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(val.c_str())), val.size()+1);
}

void SnCfgStringParamView::selectNewItem()
{
    for (int i = 0; i < menuElements; i++)
    {
        MenuItem[i]->setFocus(selectItem == i);
    }
}

void SnCfgStringParamView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnCfgStringParamView::dragScroll(int drag)
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

void SnCfgStringParamView::exitScreen()
{
  application().gotoSnCfgAppSubMenuScreenNoTransition();
}

void SnCfgStringParamView::selectEditBar()
{
  MenuItem[RadioOnItem]->setRadioOn(false);
  RadioOnItem = selectItem;
  selectNewItem();
  ccEntField.setEdit(true);
}

bool SnCfgStringParamView::isEditBarSelected()
{
  return ccEntField.isEditing();
}

void SnCfgStringParamView::moveEditCursorLeft()
{
  ccEntField.moveCursorLeft();
}

void SnCfgStringParamView::moveEditCursorRight()
{
  ccEntField.moveCursorRight();
}

void SnCfgStringParamView::eraseEditBarChar()
{
  ccEntField.delCh();
}

void SnCfgStringParamView::commitEditBar()
{
  ccEntField.setEdit(false);
  
  uint16_t idx = application().retrieveParamIndex();
  ConfigParam param = ConfigParam::GetParameters()[idx];
  std::string input(ccEntField.getText());
  /* If input is empty, restore default */
  if(input.length() == 0)
  {
    ccEntField.setDefaultText("Enter " + param.param_descr->getParamLabel());
    return;
  }
  /* Send string + null terminator to backend */
  presenter->storeParamValue(idx, const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(input.c_str())), input.length()+1);
  
  selectNewItem();
}

void SnCfgStringParamView::cancelEditBar()
{
  ccEntField.setNextScan();
  MenuItem[RadioOnItem]->setRadioOn(false);
  selectNewItem();
}
