#include <gui/snscanandentloc_screen/SnScanAndEntLocView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/ColorPalette.hpp>
#include <gui/common/platform_itf.h>

extern bool finishBarcodeFlag;
extern uint16_t storeQty;
extern uint32_t sample_multiple_data_size;
extern bool sendLocbarcodeFlag;
#define LAUNCH_SCREEN 3

REGISTER_APPLICATION(
    SnScanAndEntLocView,
    "Scan & Ent Loc",
    TRANSITION_CALLBACK(gotoSnScanAndEntLocScreenNoTransition),
    LAUNCH_SCREEN - 1
)

/* Manual Barcode Edit configuration */
REGISTER_DESC_BOOL(selManBCEditDescr)
REGISTER_PARAMETER(
     selManBCEdit,
     "Manual BC Entry loc",
     "Manual BC Entry",
     "Scan & Ent Loc",
     PARAM_TYPE_BOOL,
     0x00,
     1,
     false,
     selManBCEditDescr,
     0x01,
     1,
     user_cfg_set_barcode_editable_scanloc,
     user_cfg_get_barcode_editable_scanloc)

/* Manual QTY Edit configuration */
REGISTER_DESC_BOOL(selManQTYEditDescr)
REGISTER_PARAMETER(
     selManQTYEdit,
     "Manual QTY Entry loc",
     "Manual QTY Entry",
     "Scan & Ent Loc",
     PARAM_TYPE_BOOL,
     0x00,
     1,
     false,
     selManQTYEditDescr,
     0x01,
     2,
     user_cfg_set_qty_editable_scanloc,
     user_cfg_get_qty_editable_scanloc)

/* Delimiter configuration */
REGISTER_DESC_NUM(selDelimDescr,
                   0,
				   127,
				   true,
				   true,
                   "LOC Delimiter",
                   NVAL(0x0D, CR),
                   NVAL(0x0A, LF),
                   NVAL(0x20, Space),
                   NVAL(0x09, Tab (Default)),
                   NVAL(0x2C, ,),
                   NVAL(0x3A, :),
                   NVAL(0x3B, ;),
                   NVAL(0x3D, =))		
REGISTER_PARAMETER(
     selDelim,
     "Delimiter loc",
     "Loc Delimiter",
     "Scan & Ent Loc",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     true,
     selDelimDescr,
     0x09,
     3,
     user_cfg_set_delimiter_scanloc,
     user_cfg_get_delimiter_scanloc)

/* LOC QTY Delimiter configuration */
REGISTER_DESC_NUM(slocqtyDelimDescr,
				   0,
				   127,
				   true,
				   true,
                   "LOC QTY Delimiter",
                   NVAL(0x0D, CR),
                   NVAL(0x0A, LF),
                   NVAL(0x20, Space),
                   NVAL(0x09, Tab (Default)),
                   NVAL(0x2C, ,),
                   NVAL(0x3A, :),
                   NVAL(0x3B, ;),
                   NVAL(0x3D, =))			   
REGISTER_PARAMETER(
     slocqtyDelim,
     "LOC QTY Delimiter",
     "QTY Delimiter",
     "Scan & Ent Loc",	
     PARAM_TYPE_NUMERIC,
     0x889,
     1,
     true,
     slocqtyDelimDescr,
     0x09,
	 4,
     user_cfg_set_loc_qty_delimiter,
     user_cfg_get_loc_qty_delimiter)

REGISTER_DESC_NUM(conflocToutDescr,
		  0,
		  6,
		  true,
		  true,
                  "confirm loc Msg Timeout",
                  NVAL(0x00, 0s),
                  NVAL(0x01, 1s),
                  NVAL(0x02, 2s (Default)),
                  NVAL(0x05, 5s))		   		   
REGISTER_PARAMETER(
     conflocTout,
     "Confirm LOC Tmout",
     "Confirm LOC Tmout",
     "Scan & Ent Loc",	
     PARAM_TYPE_NUMERIC,
     0x88C,
     1,
     false,
     conflocToutDescr,
     0x02,
	 5,
     confirm_loc_set_timeout,
     confirm_loc_get_timeout)

SnScanAndEntLocView::SnScanAndEntLocView() :
    selectItem(1),
    cueTimer(CUE_TIMEOUT),
    QtyViewTimer(QtyView_Timeout),
    toastLocViewTimer(TOASTVIEW_TIMEOUT),
    toastQtyViewTimer(TOASTVIEW_TIMEOUT),
    toastBcViewTimer(TOASTVIEW_TIMEOUT),
    barcode(""),
    location(""),
    bc_r_ptr(NULL),
    loc_r_ptr(NULL),
    quantity(0),
    screen_lock(false)
{
    MenuItem[0] = &ccBack;
    MenuItem[1] = &ccLocationField;
    MenuItem[2] = &ccBarcodeField;
    MenuItem[3] = &ccQtyField;
}

void SnScanAndEntLocView::setupScreen()
{
    SnScanAndEntLocViewBase::setupScreen();
    presenter->UpdateAllIcons();
    presenter->setCurrentScreen(SCAN_QTY_LOC_DATA);
    ccLocationField.setEditable(true);
    ccBarcodeField.setEditable(presenter->getScanLocBCEditable() == 1);
    ccQtyField.setEditable(presenter->getScanLocQtyEditable() == 1);
    selectItem = 1;
    selectNewItem();
    ccToastQTY.setText(0);
    ccToastBarcode.setText(1);
    ccToastLocation.setText(4);
    QtyView_Timeout = GenericParamGetInt(conflocTout_attr)*60;
    QtyViewTimer = QtyView_Timeout;
}

void SnScanAndEntLocView::tearDownScreen()
{
    SnScanAndEntLocViewBase::tearDownScreen();
}

//Handles when a key is pressed
void SnScanAndEntLocView::handleKeyEvent(uint8_t key)
{
  presenter->keyPressed(key);
  /* Screen Lock for Pop-up -> Only act on user input */
  if(screen_lock)
  {
    if(key == KEYCODE_ENTER)
    {
      screen_lock = false;
      ccBTPopup.setVisible(false);
      ccBTPopup.invalidate();
    }
    return;
  }

    if(qty_popup)
    {
        qTYAdjust.setVisible(false);
        qTYAdjust.invalidate();
        qty_popup = false;
        return ;
    }

    switch (selectItem)
    {
    case 0:
        doForBack(key);
        break;

    case 1:
        doForLocationInput(key);
        break;

    case 2:
        doForBarcodeInput(key);
        break;

    case 3:
        doForQtyInput(key);
        break;
    }
}

void SnScanAndEntLocView::handleTickEvent()
{
    if (cueTimer < CUE_TIMEOUT)
    {
        cueTimer++;
        if (cueTimer == CUE_TIMEOUT)  // SuccessCue timeout start QTY input timer
        {
            ccSuccessCue.setVisible(false);
            ccSuccessCue.invalidate();
            selectNewItem();
        }
    }

    if (QtyViewTimer < QtyView_Timeout)
    {
        QtyViewTimer++;
        if (QtyViewTimer == QtyView_Timeout)    // QTY view timeout
        {
            gotoReadyState();
        }
    }

    if (toastLocViewTimer < TOASTVIEW_TIMEOUT)
    {
        toastLocViewTimer++;
        if (toastLocViewTimer == TOASTVIEW_TIMEOUT)    // toast view timeout
        {
            ccToastLocation.setVisible(false);
            ccToastLocation.invalidate();
        }
    }

    if (toastQtyViewTimer < TOASTVIEW_TIMEOUT)
    {
        toastQtyViewTimer++;
        if (toastQtyViewTimer == TOASTVIEW_TIMEOUT)    // toast view timeout
        {
            ccToastQTY.setVisible(false);
            ccToastQTY.invalidate();
        }
    }

    if (toastBcViewTimer < TOASTVIEW_TIMEOUT)
    {
        toastBcViewTimer++;
        if (toastBcViewTimer == TOASTVIEW_TIMEOUT)    // toast view timeout
        {
            ccToastBarcode.setVisible(false);
            ccToastBarcode.invalidate();
        }
    }
}


//Called when the screen is done with transition/load
void SnScanAndEntLocView::afterTransition()
{
    while (presenter->getBarcode() != NULL)
    {
        presenter->clearBarcode();
    }
}

void SnScanAndEntLocView::selectNewItem()
{
    for (int i = 0; i < MENUITEM_MAX; i++)
    {
        MenuItem[i]->setFocus(selectItem == i);
    }
}

void SnScanAndEntLocView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnScanAndEntLocView::BarcodeComeIn(char * BarcodeData)
{
  uint32_t minvalue = 0;
  uint32_t maxvalue = 0;

  if(screen_lock)
  {
    return;
  }
  
    switch (selectItem)
    {
    case 1:
        bc_r_ptr = (BarcodeRecord_t *)((void *)BarcodeData);
        loc_r.length = (bc_r_ptr->length > 20) ? 20 : bc_r_ptr->length;
        memset(loc_r.data, 0, sizeof(loc_r.data));
        memcpy(loc_r.data, bc_r_ptr->data, loc_r.length);
        loc_r_ptr = &loc_r;
        ccLocationField.setNextScan();
        ccLocationField.setText(NonPrintCharFilter_l(loc_r_ptr));
        presenter->clearBarcode();
        cueTimer = 0;                         // set cue timer of barcode come 1st
        ccLocationField.setCue();
        ccQtyField.setCue();
        ccSuccessCue.setCueColor(PRIMARY_BLUE);
        ccSuccessCue.setVisible(true);
        ccSuccessCue.invalidate();
        selectItem = 2;
        break;

    case 2:
        bc_r_ptr = (BarcodeRecord_t *)((void *)BarcodeData);
        ccBarcodeField.setNextScan();
        ccBarcodeField.setText(NonPrintCharFilter_b(bc_r_ptr));
        presenter->clearBarcode();
        cueTimer = 0;                         // set cue timer of barcode come 1st
        ccBarcodeField.setCue();
        ccQtyField.setCue();
        ccSuccessCue.setCueColor(STATES_SUCCESS);
        ccSuccessCue.setVisible(true);
        ccSuccessCue.invalidate();
        if (!ccQtyField.isEditable())
        {
          if(presenter->checkBTPopup())
          {
            showBTPopUp();
            return;
          }

          quantity = ccQtyField.getNumber();
          minvalue = GenericParamGetInt(gblMinQtyValue_attr);
          maxvalue = GenericParamGetInt(gblMaxQtyValue_attr);
          if((quantity < minvalue) || (quantity > maxvalue))
          {
            Unicode::itoa(minvalue, textArea1Buffer1, 10, 10);
            Unicode::itoa(maxvalue, textArea1Buffer2, 10, 10);
            textArea1.resizeToCurrentText();
            qTYAdjust.setVisible(true);
            qTYAdjust.invalidate();
            qty_popup = true;
            return;
          } 
            quantity = 1;

            presenter->sendLocBcQty(loc_r_ptr, bc_r_ptr, quantity);
            screenTransitionToProgress();
            //showQtySubmit(quantity);            // pop QTY view and start timer
            selectItem = 1;
        }
        else
        {
            selectItem = 3;
        }
        break;

    default:
        presenter->clearBarcode();
        break;
    }
}

void SnScanAndEntLocView::doForBack(uint8_t key)
{
    // This part need to reset all data
    switch (key)
    {
    case KEYCODE_DOWN:
        selectItem = 1;
        selectNewItem();
        break;

    case KEYCODE_ENTER:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        application().gotoSnHomeMenuScreenNoTransition();
        break;
    }
}

void SnScanAndEntLocView::doForQtyInput(uint8_t key)
{
    uint32_t minvalue = 0;
    uint32_t maxvalue = 0;

    if ((key >= '0') && (key <= '9'))
    {
        if (!ccQtyField.isEditing())
        {
            ccQtyField.setEdit(true);
            toastQtyViewTimer = 0;                  // Enable Toast view timer
            ccToastQTY.setVisible(true);
            ccToastQTY.invalidate();
        }
        ccQtyField.insCh(key);
        return;
    }

    switch (key)
    {
    case KEYCODE_UP:
        selectItem = 2;
        selectNewItem();
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_ENTER:
        quantity = ccQtyField.getNumber();
        toastQtyViewTimer = TOASTVIEW_TIMEOUT;  // Disable Qty toast view timer
        ccToastQTY.setVisible(false);
        ccToastQTY.invalidate();

        if (ccQtyField.isEditing())
        {
            if (quantity == 0)  //Enter num key and QTY is 0
                return;
        }
        else
        {
            quantity = 1;
        }
        
                
        if(presenter->checkBTPopup())
        {
          showBTPopUp();
          return;
        }

        minvalue = GenericParamGetInt(gblMinQtyValue_attr);
        maxvalue = GenericParamGetInt(gblMaxQtyValue_attr);
        if((quantity < minvalue) || (quantity > maxvalue))
        {
            Unicode::itoa(minvalue, textArea1Buffer1, 10, 10);
            Unicode::itoa(maxvalue, textArea1Buffer2, 10, 10);
            textArea1.resizeToCurrentText();
            qTYAdjust.setVisible(true);
            qTYAdjust.invalidate();
            qty_popup = true;
            return;
        }

        // for fix send worng data when use DONE key to move Qty field
        if (NULL == bc_r_ptr)
        {
            selectItem = 2;
            selectNewItem();
            return;
        }
        // End of Fix
        presenter->sendLocBcQty(loc_r_ptr, bc_r_ptr, quantity);
        //showQtySubmit(quantity);            // pop QTY view and start timer
        screenTransitionToProgress();
        selectItem = 1;
        selectNewItem();
        break;

    case KEYCODE_LEFT:
        if (!ccQtyField.isEditing())
            return;
        ccQtyField.moveCursorLeft();
        break;

    case KEYCODE_RIGHT:
        if (!ccQtyField.isEditing())
            return;
        ccQtyField.moveCursorRight();
        break;

    case KEYCODE_BKSP:
        if (!ccQtyField.isEditing())
            return;
        ccQtyField.delCh();
        break;

//    case KEYCODE_ESC:
//        if (!ccQtyField.isEditing())
//            return;
//        ccQtyField.setNextScan();
//        break;
    }
}

void SnScanAndEntLocView::doForBarcodeInput(uint8_t key)
{
    uint32_t minvalue = 0;
    uint32_t maxvalue = 0;

    if ((key >= 0x20) && (key <= 0x7E))
    {
        if (!ccBarcodeField.isEditable())
            return;

        if (!ccBarcodeField.isEditing())
        {
            ccBarcodeField.setEdit(true);
            toastBcViewTimer = 0;           // Enable Toast view timer
            ccToastBarcode.setVisible(true);
            ccToastBarcode.invalidate();
        }
        ccBarcodeField.insCh(key);
        return;
    }

    if ((key >= 0x81) && (key <= 0xDF))     // for multi tap
    {
        if (!ccBarcodeField.isEditing())
            return;
        ccBarcodeField.modifyCh(~(key));
        return;
    }

    switch (key)
    {
    case KEYCODE_UP:
        selectItem = 1;
        selectNewItem();
        break;

    case KEYCODE_DOWN:
        if (ccBarcodeField.getText() == NULL)
        {
            return;
        }
        else
        {
            selectItem = 3;
            selectNewItem();
        }
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_ENTER:
        toastBcViewTimer = TOASTVIEW_TIMEOUT;   // Disable barcode toast view timer
        ccToastBarcode.setVisible(false);
        ccToastBarcode.invalidate();
        if (!ccBarcodeField.isEditing())
        {
            if (ccBarcodeField.getText() == NULL)
            {
                return;
            }
            else
            {
                selectItem = 3;
                selectNewItem();
            }
        }

        if (ccBarcodeField.getText() == NULL)
            return;

        barcode.assign(ccBarcodeField.getText());
        barcode.copy(bc_r.data, barcode.length());
        bc_r.length = barcode.length();
        bc_r.type = 0x03;
        bc_r_ptr = &bc_r;

        if (!ccQtyField.isEditable())
        {
          if(presenter->checkBTPopup())
          {
            showBTPopUp();
            return;
          }
        quantity = ccQtyField.getNumber();
        minvalue = GenericParamGetInt(gblMinQtyValue_attr);
        maxvalue = GenericParamGetInt(gblMaxQtyValue_attr);
        if((quantity < minvalue) || (quantity > maxvalue))
        {
            Unicode::itoa(minvalue, textArea1Buffer1, 10, 10);
            Unicode::itoa(maxvalue, textArea1Buffer2, 10, 10);
            textArea1.resizeToCurrentText();
            qTYAdjust.setVisible(true);
            qTYAdjust.invalidate();
            qty_popup = true;
            return;
        } 
            quantity = 1;

            presenter->sendLocBcQty(loc_r_ptr, bc_r_ptr, quantity);
            screenTransitionToProgress();
            //showQtySubmit(quantity);        // pop QTY view and start timer
            selectItem = 1;
            selectNewItem();
        }
        else
        {
            selectItem = 3;
            selectNewItem();
        }
        break;

    case KEYCODE_LEFT:
        if (!ccBarcodeField.isEditing())
            return;
        ccBarcodeField.moveCursorLeft();
        break;

    case KEYCODE_RIGHT:
        if (!ccBarcodeField.isEditing())
            return;
        ccBarcodeField.moveCursorRight();
        break;

    case KEYCODE_BKSP:
        if (!ccBarcodeField.isEditing())
            return;
        ccBarcodeField.delCh();
        break;

    case KEYCODE_F1:
    case KEYCODE_F2:
    case KEYCODE_F3:
    case KEYCODE_F4:
    case KEYCODE_F5:
    case KEYCODE_F6:
    case KEYCODE_F7:
    case KEYCODE_F8:
    case KEYCODE_F9:
        if (!ccBarcodeField.isEditable())
            return;
        if (!ccBarcodeField.isEditing())
        {
            ccBarcodeField.setEdit(true);
            toastBcViewTimer = 0;               // Enable Toast view timer
            ccToastBarcode.setVisible(true);
            ccToastBarcode.invalidate();
        }
        ccBarcodeField.insStr(presenter->getFnKeyRemapString(key - KEYCODE_F1 + 1));
        break;

//    case KEYCODE_ESC:
//        if (!ccBarcodeField.isEditing())
//            return;
//        ccBarcodeField.setNextScan();
//        break;
    }
}

void SnScanAndEntLocView::doForLocationInput(uint8_t key)
{
    if ((key >= 0x20) && (key <= 0x7E))
    {
        if (!ccLocationField.isEditing())
        {
            ccLocationField.setEdit(true);
            toastLocViewTimer = 0;          // Enable Toast view timer
            ccToastLocation.setVisible(true);
            ccToastLocation.invalidate();
        }
        ccLocationField.insCh(key);
        return;
    }

    if ((key >= 0x81) && (key <= 0xDF))     // for multi tap
    {
        if (!ccLocationField.isEditing())
            return;
        ccLocationField.modifyCh(~(key));
        return;
    }

    switch (key)
    {
    case KEYCODE_UP:
        selectItem = 0;
        selectNewItem();
        break;

    case KEYCODE_DOWN:
        if (ccLocationField.getText() == NULL)
        {
            return;
        }
        else
        {
            location.assign(ccLocationField.getText());
            location.copy(loc_r.data, location.length());
            loc_r.length = location.length();
            loc_r_ptr = &loc_r;
            selectItem = 2;
            selectNewItem();
        }
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_ENTER:
        if (ccLocationField.getText() == NULL)  //APP can enter empty location data
        {
            loc_r_ptr = NULL;
        }
        else
        {
            location.assign(ccLocationField.getText());
            location.copy(loc_r.data, location.length());
            loc_r.length = location.length();
            loc_r_ptr = &loc_r;
        }
        selectItem = 2;
        selectNewItem();
        toastLocViewTimer = TOASTVIEW_TIMEOUT;  // Disable Qty toast view timer
        ccToastLocation.setVisible(false);
        ccToastLocation.invalidate();
        break;

    case KEYCODE_LEFT:
        if (!ccLocationField.isEditing())
            return;
        ccLocationField.moveCursorLeft();
        break;

    case KEYCODE_RIGHT:
        if (!ccLocationField.isEditing())
            return;
        ccLocationField.moveCursorRight();
        break;

    case KEYCODE_BKSP:
        if (!ccLocationField.isEditing())
            return;
        ccLocationField.delCh();
        break;

    case KEYCODE_F1:
    case KEYCODE_F2:
    case KEYCODE_F3:
    case KEYCODE_F4:
    case KEYCODE_F5:
    case KEYCODE_F6:
    case KEYCODE_F7:
    case KEYCODE_F8:
    case KEYCODE_F9:
        if (!ccLocationField.isEditing())
        {
            ccLocationField.setEdit(true);
            toastLocViewTimer = 0;          // Enable Toast view timer
            ccToastLocation.setVisible(true);
            ccToastLocation.invalidate();
        }
        ccLocationField.insStr(presenter->getFnKeyRemapString(key - KEYCODE_F1 + 1));
        break;

//    case KEYCODE_ESC:
//        if (!ccLocationField.isEditing())
//            return;
//        ccLocationField.setNextScan();
//        break;
    }
}

void SnScanAndEntLocView::showQtySubmit(uint16_t quantity)
{
  if(GenericParamGetInt(conflocTout_attr)!= 0x00)
  {
    QtyViewTimer = 0;
    Unicode::UnicodeChar tempStr[TEXTLOC_SIZE];
    int length = (presenter->getlocAppVar()).length();

    if (length < TEXTLOC_SIZE)
        Unicode::strncpy(tempStr, (presenter->getlocAppVar()).c_str(), TEXTLOC_SIZE - 1);
    else
    {
        Unicode::strncpy(tempStr, (presenter->getlocAppVar()).c_str() + (length - TEXTLOC_SIZE + 1), TEXTLOC_SIZE - 1);
        tempStr[0] = 0x2025;    // show ..
    }

    textLocation.setTypedText(touchgfx::TypedText(T_LOCVIEW_01));
    Unicode::snprintf(textLOCBuffer, TEXTLOC_SIZE, "%s", tempStr);

    if (0 == quantity)          // Qty input timeout 1 submit
    {
        textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_01));
        Unicode::snprintf(textQTYBuffer, TEXTQTY_SIZE, "%d", 1);
    } else if (quantity < 10)   // Qty is one digit
    {
        textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_5));
        Unicode::snprintf(textQTYBuffer, TEXTQTY_SIZE, "%d", quantity);
    } else if (quantity < 100)  // Qty is 2 digits
    {
        textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_5));
        Unicode::snprintf(textQTYBuffer, TEXTQTY_SIZE, "%d", quantity);
    } else if (quantity < 1000) // Qty is 3 digits
    {
        textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_5));
        Unicode::snprintf(textQTYBuffer, TEXTQTY_SIZE, "%d", quantity);
    } else                      // Qty is 4 digits
    {
        textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_5));
        Unicode::snprintf(textQTYBuffer, TEXTQTY_SIZE, "%d", quantity);
    }

    cQTYView.setVisible(true);
    cQTYView.invalidate();
  }
  else
  {
    gotoReadyState();
  }
}

void SnScanAndEntLocView::gotoReadyState()
{
    loc_r_ptr = NULL;                        // reset variable
    bc_r_ptr = NULL;
    memset(loc_r.data, 0, sizeof(loc_r.data));
    memset(bc_r.data, 0, sizeof(bc_r.data));
    quantity = 0;
    ccBarcodeField.setNextScan();           // reset barcode field
    ccLocationField.setNextScan();          // reset location field
    ccQtyField.setNextScan();               // reset quantity field
    QtyViewTimer = QtyView_Timeout;         // Disable QTY view timer
    cQTYView.setVisible(false);
    cQTYView.invalidate();
    toastQtyViewTimer = TOASTVIEW_TIMEOUT;  // Disable Qty toast view timer
    ccToastQTY.setVisible(false);
    ccToastQTY.invalidate();
    toastBcViewTimer = TOASTVIEW_TIMEOUT;   // Disable barcode toast view timer
    ccToastBarcode.setVisible(false);
    ccToastBarcode.invalidate();
    toastLocViewTimer = TOASTVIEW_TIMEOUT;  // Disable location toast view timer
    ccToastLocation.setVisible(false);
    ccToastLocation.invalidate();
}

void SnScanAndEntLocView::screenTransitionToProgress()
{
  string tempLocation;
    storeQty = quantity;
    tempLocation.assign(NonPrintCharFilter_l(loc_r_ptr));
    presenter->setlocAppVar(tempLocation);
    if (sample_multiple_data_size*storeQty >= check_value && sendLocbarcodeFlag)
  
    {
      sendLocbarcodeFlag = false;
      application().gotoSnBarcodeProgressScreenNoTransition();
    }
    else
    {
        showQtySubmit(storeQty);
        if(sendLocbarcodeFlag == true)
            sendLocbarcodeFlag = false;
    }
}

void SnScanAndEntLocView::showBTPopUp(void)
{
  screen_lock = true;
  ccBTPopup.setVisible(true);
  ccSuccessCue.setVisible(false);
  ccToastLocation.setVisible(false);
  ccToastQTY.setVisible(false);
  cQTYView.setVisible(false);
  
  presenter->clearBarcode();
  
  toastLocViewTimer = TOASTVIEW_TIMEOUT;
  toastBcViewTimer = TOASTVIEW_TIMEOUT;
  toastQtyViewTimer = TOASTVIEW_TIMEOUT;
  
  cQTYView.invalidate();
  ccToastQTY.invalidate();
  ccToastLocation.invalidate();
  ccSuccessCue.invalidate();
  ccBTPopup.invalidate();
  
  SendAvoidTransmissionDecodeDataCommand();  //Beeper 0x49
}

