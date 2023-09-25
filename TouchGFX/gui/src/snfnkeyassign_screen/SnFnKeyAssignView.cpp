#include <gui/snfnkeyassign_screen/SnFnKeyAssignView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/platform_itf.h>
#include <gui/common/ConfigParam.hpp>

#define LAUNCH_SCREEN 7

/*  Function Key mapping - mapped to "new" app category -> Function Key */

SnFnKeyAssignView::SnFnKeyAssignView() :
    stringIdx(0),
    radioIdx(0),
    menuElements(0),
    selectItem(1),
    RadioOnItem(1),
    FnKeySelected(1),
    oldSelectItem(1),
    toastCfgMenuViewTimer(TOASTVIEW_TIMEOUT)
{
  /* Build the default part of the screen */
    MenuItem[0] = &ccBack;
    MenuItem[1] = &ccEntStrField;
    
    /* Retrive index of parameter to handle */
    stringIdx = application().retrieveParamIndex();
    /* Retrieve parameter to handle */
    ConfigParam param = ConfigParam::GetParameters()[stringIdx];
    
    /* Seek the "paired" radio parameter */
    int i = 0;
    radioIdx = 0;
    for(ConfigParam pairedParam : ConfigParam::GetParameters())
    {
      if(pairedParam.param_name.find(param.param_name+"_radio") != std::string::npos)
      {
        radioIdx = i;
        break;
      }
      i++;
    }
    ConfigParam param_radio = ConfigParam::GetParameters()[radioIdx];
    i = 0;
    menuElements = 2;
    std::vector<uint32_t> preset_values =  param_radio.param_descr->GetPresetValues();
    int j = 0;
    /* Populate Radio Menu for Function Key non-custom assignments */
    for(std::string val_name : param_radio.param_descr->GetRadioNames())
    {
      /* Unassigned and custom options are hidden */
      if((preset_values[j] == Unassigned) || (preset_values[j] == Custom_String))
      {
        j++;
        continue;
      }
      j++;
      if (val_name.size() >= 20)
      {
        val_name.erase(19, string::npos);
      }
      ccMenuItems[i].setText(val_name);
      MenuItem[i+2] = &ccMenuItems[i];
      listLayout.add(ccMenuItems[i]);
      i++;
      menuElements++;
    }
}

void SnFnKeyAssignView::setupScreen()
{
    SnFnKeyAssignViewBase::setupScreen();
    
    uint8_t rParamValue = 0;
    char sParamValue[20] = {0};
    
    ConfigParam sParam = ConfigParam::GetParameters()[stringIdx];
    ConfigParam rParam = ConfigParam::GetParameters()[radioIdx];
                      
    /* Get current state of the radio parameter */       
    presenter->retrieveParamValue(radioIdx, &rParamValue);
    
    /* Check for out of range */
    if( rParamValue > rParam.param_descr->GetRadioNames().size() )
    {
      rParamValue = rParam.default_value; /* Default for these is unassigned */
      presenter->storeParamValue(radioIdx, &rParamValue, 1);
    }
    
    /* Check for Custom String */
    if (rParamValue == Custom_String)
    {
      /* Retrieve and populate */
      char *cp = sParamValue;
      presenter->retrieveParamValue(stringIdx, (uint8_t*)&cp);
      std::string strVal(cp);
      ccEntStrField.setDefaultText(strVal);
    }
    
    /* Set value to whatever is assigned - 2 hidden options*/
    MenuItem[rParamValue]->setRadioOn(true);
        
    presenter->UpdateAllIcons();
    presenter->setCurrentScreen(NO_SPL_FEATURE);
    selectItem = (presenter->getBackArrowActive()) ? 0 : 1;
    presenter->setBackArrowActive(false);
    selectNewItem();
    scrollCnt.setScrollbarWidth(4);
    dragScroll(-1);
    dragScroll(1);
    scrollCnt.invalidate();
    
    cView.setVisible(false);
    cView.invalidate();
}

void SnFnKeyAssignView::tearDownScreen()
{
    SnFnKeyAssignViewBase::tearDownScreen();
}

void SnFnKeyAssignView::BarcodeComeIn(char * BarcodeData)
{
    presenter->clearBarcode();
    toastCfgMenuViewTimer = 0;                  // Enable Toast view timer
    cccfgMenuToast.setVisible(true);
    cccfgMenuToast.invalidate();
    SendAvoidTransmissionDecodeDataCommand();  //Beeper 0x49
}

void SnFnKeyAssignView::handleKeyEvent(uint8_t key)
{
    ConfigParam sParam = ConfigParam::GetParameters()[stringIdx];
    ConfigParam rParam = ConfigParam::GetParameters()[radioIdx];
    uint8_t rValue = 0;
    
    if (ccEntStrField.isEditing())
    {
        presenter->keyPressed(key);

        switch (key)
        {
        case KEYCODE_LEFT:
            ccEntStrField.moveCursorLeft();
            return;

        case KEYCODE_RIGHT:
            ccEntStrField.moveCursorRight();
            return;

        case KEYCODE_BKSP:
            ccEntStrField.delCh();
            return;

        case KEYCODE_ENTER:
           /* Committed text (or lack thereof). Unassigned/Custom String */
            if (ccEntStrField.getText() == NULL)
            {
              /* No text -> Un assign */
              rValue = Unassigned;
              char empty[] = "";
              presenter->storeParamValue(radioIdx, &rValue, 1);
              /* For completeness, also clear the string parameter */
              presenter->storeParamValue(stringIdx, (uint8_t*)empty, 1);
              Unicode::snprintf(textKeyAssignedBuffer, TEXTKEYASSIGNED_SIZE, "%s", 
                              touchgfx::TypedText(T_KEYASSIGNVIEW_UNASSIGNED).getText());
            }
            else
            {
              /* Custom String */
              rValue = Custom_String;
              presenter->storeParamValue(radioIdx, &rValue, 1);
              /* For completeness, also clear the string parameter */
              presenter->storeParamValue(stringIdx, (uint8_t*)ccEntStrField.getText(), strlen(ccEntStrField.getText())+1);
              Unicode::fromUTF8((uint8_t*)ccEntStrField.getText(), textKeyAssignedBuffer, TEXTKEYASSIGNED_SIZE);
            }
            textKeyAssigned.invalidate();
            ccEntStrField.setEdit(false);
            cView.setVisible(true);
            cView.invalidate();
            return;

        case KEYCODE_ESC:
            application().gotoSnCfgAppSubMenuScreenNoTransition();
            return;
        }

        if ((key >= 0x20) && (key <= 0x7E))
        {
            ccEntStrField.insCh(key);
        }

        if ((key >= 0x81) && (key <= 0xDF))     // for multi tap
        {
            ccEntStrField.modifyCh(~(key));
        }
        return;
    }

    if (cView.isVisible())
    {
        switch (key)
        {
        case KEYCODE_ENTER:
            cView.setVisible(false);
            cView.invalidate();
            application().gotoSnCfgAppSubMenuScreenNoTransition();
            break;
        }
        return;
    }

    presenter->keyPressed(key);
    
    switch (key)
    {
    case KEYCODE_UP:
        selectItem = (selectItem == 0) ? 0 : selectItem - 1;
        dragScroll(oldSelectItem - selectItem);
        selectNewItem();
        oldSelectItem = selectItem;
        break;

    case KEYCODE_DOWN:
        selectItem = (selectItem == (menuElements-1)) ? (menuElements-1) : selectItem + 1;
        dragScroll(oldSelectItem - selectItem);
        selectNewItem();
        oldSelectItem = selectItem;
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        presenter->setBackArrowActive(false);
        application().gotoSnCfgAppSubMenuScreenNoTransition();
        break;

    case KEYCODE_ENTER:
        switch (selectItem)
        {
        case 0:
            presenter->setBackArrowActive(true);
            application().gotoSnCfgAppSubMenuScreenNoTransition();
            break;

        case 1:
            MenuItem[RadioOnItem]->setRadioOn(false);
            RadioOnItem = selectItem;
            selectNewItem();
            ccEntStrField.setEdit(true);
            break;

        case 2:
        case 3:
        case 4:
            /* For completeness, also clear the string parameter */
            char empty[] = "";
            presenter->storeParamValue(stringIdx, (uint8_t*)empty, 1);
            MenuItem[RadioOnItem]->setRadioOn(false);
            RadioOnItem = selectItem;
            presenter->storeParamValue(radioIdx, &RadioOnItem, 1);
            MenuItem[RadioOnItem]->setRadioOn(true);
            selectNewItem();
            Unicode::snprintf(textKeyAssignedBuffer, TEXTKEYASSIGNED_SIZE, "%s", 
                              touchgfx::TypedText(T_KEYASSIGNVIEW_UNASSIGNED + selectItem - 1).getText());
            textKeyAssigned.invalidate();
            cView.setVisible(true);
            cView.invalidate();
            break;
        }
        break;
    }
}

void SnFnKeyAssignView::handleTickEvent()
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
void SnFnKeyAssignView::afterTransition()
{
  uint8_t diff = ConfigParam::GetParameters()[stringIdx].param_name[1] - '0';
    textFnKey.setTypedText(touchgfx::TypedText(T_KEYASSIGNVIEW_F0 + diff));
    textFnKey.invalidate();
}

void SnFnKeyAssignView::selectNewItem()
{
    ConfigParam rParam = ConfigParam::GetParameters()[radioIdx];
    std::vector<std::string> wea = rParam.param_descr->GetRadioNames();
    
    for (unsigned int i = 0; i < rParam.param_descr->GetRadioNames().size(); i++)
    {
        MenuItem[i]->setFocus(selectItem == i);
    }
}

void SnFnKeyAssignView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnFnKeyAssignView::dragScroll(int drag)
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
