#include <gui/sncfgmenu_screen/SnCfgMenuView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/platform_itf.h>
#include <gui/common/ConfigParam.hpp>

#define LAUNCH_SCREEN 1

REGISTER_APPLICATION(
    SnCfgMenuView,
    "Configuration",
    TRANSITION_CALLBACK(gotoSnCfgMenuScreenNoTransition),
    255
)

REGISTER_DESC_NUM(dispToutDescr,
                  0,
                  18,
                  false,
                  true,
                  "Display Timeout", 
                  NVAL(0x03, 3s),
                  NVAL(0x06, 6s),
                  NVAL(0x0C, 12s (Default)),
                  NVAL(0x12, 18s),
                  NVAL(0x00, No Timeout))
REGISTER_PARAMETER(
     gblDispTout,
     "Display Timeout",
     "Display Timeout",
     "Global",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     dispToutDescr,
     0x0C,
     1,
     user_cfg_set_display_timeout,
     user_cfg_get_display_timeout)


REGISTER_DESC_BOOL(gblManBCEntDescr)
REGISTER_PARAMETER(
     gblManBCEntry,
     "Manual Barcode Entry",
     "Manual BC Entry",
     "Global",
     PARAM_TYPE_BOOL,
     0x00,
     1,
     false,
     gblManBCEntDescr,
     0x01,
     3,
     user_cfg_set_barcode_editable,
     user_cfg_get_barcode_editable)

REGISTER_DESC_BOOL(gblManQtyEntDescr)
REGISTER_PARAMETER(
     gblManQtyEntry,
     "Manual Quantity Entry",
     "Manual QTY Entry",
     "Global",
     PARAM_TYPE_BOOL,
     0x00,
     1,
     false,
     gblManQtyEntDescr,
     0x01,
     4,
     user_cfg_set_qty_editable,
     user_cfg_get_qty_editable)


REGISTER_DESC_NUM(autoDispBrtDescr,
                  1,
                  6,
                  false,
                  true,
                  "Auto Display Brightness",
                  NVAL(0x01, Enable (Default)),
                  NVAL(0x02, Disable medium),
                  NVAL(0x03, Disable dimmest),
                  NVAL(0x04, Disable dim),
                  NVAL(0x05, Disable bright),
                  NVAL(0x06, Disable brightest))
REGISTER_PARAMETER(
     gblAutoDispBrt,
     "Auto Display Brightness",
     "Auto Display BRT",
     "Global",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     autoDispBrtDescr,
     0x01,
     5,
     user_cfg_set_auto_disp_brg,
     user_cfg_get_auto_disp_brg)

REGISTER_DESC_NUM(gblKeypadBacklightDescr,
                  0,
                  3,
                  false,
                  true,
                  "Keypad Backlight",
                  NVAL(0x00, Off),
                  NVAL(0x01, On), 
                  NVAL(0x02, Auto (Default)))
REGISTER_PARAMETER(
     gblKeypadBacklight,
     "Keypad Backlight",
     "Keypad Backlight",
     "Global",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblKeypadBacklightDescr,
     0x02,
     6,
     user_cfg_set_key_backlight,
     user_cfg_get_key_backlight)


REGISTER_DESC_NUM(gblDispOnChargeDescr,
                  1,
                  3,
                  false,
                  true,
                  "Display On Charge",
                  NVAL(0x01, Half Full),
                  NVAL(0x02, 3/4 Full),
                  NVAL(0x03, Full (Default)))
REGISTER_PARAMETER(
     gbDispOnCharge,
     "Display On Charge",
     "Display On Charge",
     "Global",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblDispOnChargeDescr,
     0x03,
     8,
     user_cfg_set_disp_on_charge,
     user_cfg_get_disp_on_charge)


REGISTER_DESC_NUM(gblQtyXferModeDescr,
                  1,
                  2,
                  false,
				  true,
                  "QTY Transfer Mode",
                  NVAL(0x01, BCxQTY (Default)),
                  NVAL(0x02, BC(Delimiter)QTY))
REGISTER_PARAMETER(
     gblQtyXferMode,
     "QTY Transfer Mode",
     "QTY Transfer Mode",
     "Global",
     PARAM_TYPE_NUMERIC,
     0x885,
     1,
     false,
     gblQtyXferModeDescr,
     0x01,
	 9,
     user_cfg_set_qty_transfer_mode,
     user_cfg_get_qty_transfer_mode)

/* QTY Delimiter configuration */
REGISTER_DESC_NUM(sqtyDelimDescr,
				   0,
				   127,
				   true,
				   true,
                   "QTY Delimiter",
                   NVAL(0x0D, CR),
                   NVAL(0x0A, LF),
                   NVAL(0x20, Space),
                   NVAL(0x09, Tab (Default)),
                   NVAL(0x2C, ,),
                   NVAL(0x3A, :),
                   NVAL(0x3B, ;),
                   NVAL(0x3D, =))			   
REGISTER_PARAMETER(
     sqtyDelim,
     "QTY Delimiter",
     "QTY Delimiter",
     "Global",	
     PARAM_TYPE_NUMERIC,
     0x886,
     1,
     true,
     sqtyDelimDescr,
     0x09,
	 10,
     user_cfg_set_qty_delimiter,
     user_cfg_get_qty_delimiter)
  
/* Location Delimiter configuration */
REGISTER_DESC_NUM(slocDelimDescr,
				   0,
				   127,
				   true,
				   true,
                   "Delimiter",
                   NVAL(0x0D, CR),
                   NVAL(0x0A, LF),
                   NVAL(0x20, Space),
                   NVAL(0x09, Tab (Default)),
                   NVAL(0x2C, ,),
                   NVAL(0x3A, :),
                   NVAL(0x3B, ;),
                   NVAL(0x3D, =))			   
REGISTER_PARAMETER(
     slocDelim,
     "Loc Delimiter",
     "Loc Delimiter",
     "Global",	
     PARAM_TYPE_NUMERIC,
     0x887,
     1,
     true,
     slocDelimDescr,
     0x09,
	 11,
     user_cfg_set_loc_delimiter,
     user_cfg_get_loc_delimiter) 

REGISTER_DESC_NUM(MinQtyValueDescr,
                  0,
                  9999,
                  true,
                  false,
                  "Min Qty Value",
                  NVAL(0x01, 1, (Default)))
                  
REGISTER_PARAMETER(
           gblMinQtyValue,
           "Min Qty Value",
           "Min Qty Value",
           "Hidden",
           PARAM_TYPE_NUMERIC,
           0x00,
           2,
           false,
           MinQtyValueDescr,
           0x01,
           12,
           user_cfg_set_qty_min_value,
           user_cfg_get_qty_min_value)

REGISTER_DESC_NUM(MaxQtyValueDescr,
                  1,
                  9999,
                  true,
                  false,
                  "Max Qty Value",
                  NVAL(0x270F, 9999, (Default)))
                  
REGISTER_PARAMETER(
           gblMaxQtyValue,
           "Max Qty Value",
           "Max Qty Value",
           "Global",
           PARAM_TYPE_NUMERIC,
           0x00,
           2,
           false,
           MaxQtyValueDescr,
           0x270F,
           13,
           user_cfg_set_qty_max_value,
           user_cfg_get_qty_max_value)

SnCfgMenuView::SnCfgMenuView() :
    selectItem(1),
    oldSelectItem(1),
    toastCfgMenuViewTimer(TOASTVIEW_TIMEOUT)
{
  menuElementsCount = 0;
  std::vector<std::string>::iterator it;
  std::vector<std::string> configs = ConfigParam::GetConfigAppList();
  MenuItem[0] = &ccBack;
  
  /* Check if there is actually any ConfigParam that is set to "global" */
  if( ConfigParam::GetAppParameters("Global").size() > 0)
  {
    ccMenuItems[menuElementsCount].setText(std::to_string(menuElementsCount+1) + " Global");
    MenuItem[menuElementsCount+1] = &ccMenuItems[menuElementsCount];
    listLayout.add(ccMenuItems[menuElementsCount]);
    menuElementsCount++;
  }

  for(uint8_t i = 0; i < ZebraApplication::GetApplications().size(); i++)
  {
    ZebraApplication app = ZebraApplication::GetApplications()[i];
    it = find(configs.begin(), configs.end(), app.name);
    if(it != configs.end()) /* There ARE configurations to this application */
    {
      /* list it on the menu */
      ccMenuItems[menuElementsCount].setText(std::to_string(menuElementsCount+1) + " " + app.name);
      MenuItem[menuElementsCount+1] = &ccMenuItems[menuElementsCount];
      listLayout.add(ccMenuItems[menuElementsCount]);
      menuElementsCount++;
    }
  }   
}

void SnCfgMenuView::setupScreen()
{
    SnCfgMenuViewBase::setupScreen();
    presenter->UpdateAllIcons();
    presenter->setCurrentScreen(NO_SPL_FEATURE);
    selectItem = 1;
    presenter->setBackArrowActive(false);
    selectNewItem();
    scrollCnt.setScrollbarWidth(4);
    dragScroll(-1);
    dragScroll(1);
    scrollCnt.invalidate();
}

void SnCfgMenuView::tearDownScreen()
{
    SnCfgMenuViewBase::tearDownScreen();
}

void SnCfgMenuView::BarcodeComeIn(char * BarcodeData)
{
    presenter->clearBarcode();
    toastCfgMenuViewTimer = 0;                  // Enable Toast view timer
    cccfgMenuToast.setVisible(true);
    cccfgMenuToast.invalidate();
    SendAvoidTransmissionDecodeDataCommand();  //Beeper 0x49
}

void SnCfgMenuView::handleKeyEvent(uint8_t key)
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

        selectItem = (selectItem == menuElementsCount) ? menuElementsCount : selectItem + 1;
        dragScroll(oldSelectItem - selectItem);
        selectNewItem();
        oldSelectItem = selectItem;
        break;

    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        if((key -'0') <= menuElementsCount)
        {
          selectItem = key -'0';
          dragScroll(oldSelectItem - selectItem);
          selectNewItem();
          oldSelectItem = selectItem;
        }
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        presenter->setBackArrowActive(false);
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    }
}

void SnCfgMenuView::handleTickEvent()
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
void SnCfgMenuView::afterTransition()
{

}

void SnCfgMenuView::selectNewItem()
{
  for (uint8_t i = 0; i < menuElementsCount+1; i++)
    {
        MenuItem[i]->setFocus(selectItem == i);
    }
}

void SnCfgMenuView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnCfgMenuView::dragScroll(int drag)
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

uint8_t SnCfgMenuView::getSelectedEntry()
{
  return selectItem;
}

void SnCfgMenuView::jumpToHomeMenu()
{
  application().gotoSnHomeMenuScreenNoTransition();
}

void SnCfgMenuView::jumpToConfigSubmenu()
{
  std::string appname = ccMenuItems[selectItem-1].getString();
  application().storeAppName(appname);
  application().gotoSnCfgAppSubMenuScreenNoTransition();
}
