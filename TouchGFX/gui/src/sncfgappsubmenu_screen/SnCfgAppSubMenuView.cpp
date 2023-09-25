#include <gui/sncfgappsubmenu_screen/SnCfgAppSubMenuView.hpp>

/* Hardcoded "Function Key" submenu position in the "Global" list */
/* If lesser than 1 it will be set as 1 */
/* If greater than the number of items in "Global", it will be set last in the list */
#define FUNCTION_KEY_LIST_POSITION    2

#define LAUNCH_SCREEN 5
SnCfgAppSubMenuView::SnCfgAppSubMenuView():
    selectItem(1),
    oldSelectItem(1),
    toastCfgMenuViewTimer(TOASTVIEW_TIMEOUT),
    keyClickTimer(KEY_SELECTION_TIMEOUT),
    newSelectItem(0),
    FirstKeyPressed(false)
{
    menuElements = 0;
    MenuItem[0] = &ccBack;
    std::string app = application().retrieveAppName();
    menuElements = 1;
    
    /* Check if we need to add the Function Key menu */
    /* If not, the -1 value will assure that it will not be added to the list */
    FnKeyMenuCfgIdx = -1;
    if(app == "Global")
    {
      /* Check if parameters assigned to the application "Function Key" exist */
      if(ConfigParam::GetAppParameters("Function Key").size())
      {
        /* If they exist, we set the index position of the "Function Key" submenu */
        FnKeyMenuCfgIdx = FUNCTION_KEY_LIST_POSITION;
        /* The index shall be equal or greater than 1 */
        if (FnKeyMenuCfgIdx < 1)
        {
          FnKeyMenuCfgIdx = 1;
        }
      }
    }
    
    /* Check specific Parameters Specific to the application*/
    for(unsigned int i = 0; i < ConfigParam::GetAppParameters(app).size(); i++)
    {
        /* Add the "Function Key" element if required */ 
        if (menuElements == FnKeyMenuCfgIdx)
        {
          ccMenuItems[menuElements-1].setText(std::to_string(menuElements) + " Function Key");
          MenuItem[menuElements] = &ccMenuItems[menuElements-1];
          listLayout.add(ccMenuItems[menuElements-1]);
          menuElements++;
        }
        
        ConfigParam conf = ConfigParam::GetAppParameters(app)[i];
        /* Special Case - Function Key (Dual Implementation) */
        /* We must ignore the second element which is defined as _radio */
        if((app == "Function Key")&&(conf.param_name.find("_radio") != std::string::npos))
        {
          continue;
        }
        /* TODO - Handle text for name and short_name separately */
        ccMenuItems[menuElements-1].setText(std::to_string(menuElements) + " " + conf.short_name);

        MenuItem[menuElements] = &ccMenuItems[menuElements-1];

        listLayout.add(ccMenuItems[menuElements-1]);
        menuElements++;
    }
    /* Add the "Function Key" element if required, at the end of the list */ 
    if (menuElements <= FnKeyMenuCfgIdx)
    {
      ccMenuItems[menuElements-1].setText(std::to_string(menuElements) + " Function Key");
      MenuItem[menuElements] = &ccMenuItems[menuElements-1];
      listLayout.add(ccMenuItems[menuElements-1]);
      /* Set the position as the last in the list */
      FnKeyMenuCfgIdx = menuElements;
      menuElements++;
    }
    
    application().saveScreen(&FrontendApplication::gotoSnCfgAppSubMenuScreenNoTransition);
}


void SnCfgAppSubMenuView::setupScreen()
{
    SnCfgAppSubMenuViewBase::setupScreen();
    presenter->UpdateAllIcons();
    presenter->setCurrentScreen(NO_SPL_FEATURE);
    selectItem = 1;
    presenter->setBackArrowActive(false);
    selectNewItem();
    selectNewItem();
    scrollCnt.setScrollbarWidth(4);
    dragScroll(-1);
    dragScroll(1);
    scrollCnt.invalidate();
}

void SnCfgAppSubMenuView::tearDownScreen()
{
    SnCfgAppSubMenuViewBase::tearDownScreen();
}


void SnCfgAppSubMenuView::BarcodeComeIn(char * BarcodeData)
{
    presenter->clearBarcode();

    toastCfgMenuViewTimer = 0;                  // Enable Toast view timer
    cccfgMenuToast.setVisible(true);
    cccfgMenuToast.invalidate();
    SendAvoidTransmissionDecodeDataCommand();  //Beeper 0x49
}

void SnCfgAppSubMenuView::handleKeyEvent(uint8_t key)
{
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
        selectItem = (selectItem == menuElements-1) ? (menuElements-1) : selectItem + 1;
        dragScroll(oldSelectItem - selectItem);
        selectNewItem();
        oldSelectItem = selectItem;
        break;

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
	    if(menuElements >= 10)
		{
        if (FirstKeyPressed)
        {
            newSelectItem = newSelectItem * 10 + (key -'0');
            FirstKeyPressed = false;
            keyClickTimer = KEY_SELECTION_TIMEOUT;  // Disable timer

            if ((0 == newSelectItem) || (newSelectItem >= menuElements))
            {
                newSelectItem = 0;
                return;
            }
            selectItem = newSelectItem;
            dragScroll(oldSelectItem - selectItem);
            selectNewItem();
            oldSelectItem = selectItem;
        }
        else
        {
            newSelectItem = key -'0';
            FirstKeyPressed = true; // 1st key pressed
            keyClickTimer = 0;      // Enable timer
        }
		}
		else if((key -'0') < menuElements)
        {                  
          selectItem = key -'0';
          dragScroll(oldSelectItem - selectItem);
          selectNewItem();
          oldSelectItem = selectItem;
        }
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        jumpToPrevScreen();
        break;
    }
}

void SnCfgAppSubMenuView::handleTickEvent()
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

    if (keyClickTimer < KEY_SELECTION_TIMEOUT)
    {
        keyClickTimer++;
        if (keyClickTimer == KEY_SELECTION_TIMEOUT)    // key click timeout
        {
            FirstKeyPressed = false;

            if ((0 == newSelectItem) || (newSelectItem >= menuElements))
            {
                newSelectItem = 0;
                return;
            }
            selectItem = newSelectItem;
            dragScroll(oldSelectItem - selectItem);
            selectNewItem();
            oldSelectItem = selectItem;
        }
    }
}

//Called when the screen is done with transition/load
void SnCfgAppSubMenuView::afterTransition()
{

}

void SnCfgAppSubMenuView::selectNewItem()
{
    for (unsigned int i = 0; i < menuElements; i++)
    {
        MenuItem[i]->setFocus(selectItem == i);
    }
}

void SnCfgAppSubMenuView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnCfgAppSubMenuView::dragScroll(int drag)
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

uint8_t SnCfgAppSubMenuView::getSelectedEntry()
{
    return selectItem;
}

void SnCfgAppSubMenuView::jumpToPrevScreen()
{
  /* Handle Special Case -> If current app is "Function Key",
   * We re-enter this screen with "Global" app instead" */
  if(application().retrieveAppName() == "Function Key")
  {
    std::string appname = "Global";
    application().storeAppName(appname);
    application().gotoSnCfgAppSubMenuScreenNoTransition();
    return;
  }
  /* General Case */
  application().gotoSnCfgMenuScreenNoTransition();
}

void SnCfgAppSubMenuView::jumpToParamConfig()
{
  std::string app = application().retrieveAppName();
  /* Special Case - We re-enter this Menu, with new app name = Function Key */
  if((selectItem == FnKeyMenuCfgIdx)&&(app == "Global"))
  {
    std::string appname = "Function Key";
    application().storeAppName(appname);
    application().gotoSnCfgAppSubMenuScreenNoTransition();
    return;
  }
  
  uint8_t index = 0;
  /*Special handling of Function Key case, since ithas to mask the _radio */
  if(app == "Function Key")
  {
    index =(selectItem-1)*2;
  }
  else
  {
    /* Check if we need to substract the Function key position from the index */
    /* FnKeyMenuCfgIdx is only positive when Function key submenu is present */
    if ((FnKeyMenuCfgIdx > 0) && (selectItem > FnKeyMenuCfgIdx))
    {
      selectItem--;
    }
    index =(selectItem-1);
  }
  ConfigParam conf = ConfigParam::GetAppParameters(app)[index];
  uint16_t idx = ConfigParam::GetParamIndex(conf.param_name, conf.app_name);
  
  application().storeParamIndex(idx);

  switch (conf.param_type)
  {
  case PARAM_TYPE_BOOL:
    application().gotoSnCfgBoolParamScreenNoTransition();
    break;
  case PARAM_TYPE_NUMERIC:
    application().gotoSnCfgNumericParamScreenNoTransition();
    break;
  case PARAM_TYPE_CHARACTER:
    application().gotoSnCfgCharParamScreenNoTransition();
    break;
  case PARAM_TYPE_STRING:
    /* Special Case -> Functions keys go to their own hardcoded screen */
    if(app == "Function Key")
    {
      application().gotoSnFnKeyAssignScreenNoTransition();
      break;
    }
    application().gotoSnCfgStringParamScreenNoTransition();
  default:
    /* Should never reach here */
    break;
  }
}
