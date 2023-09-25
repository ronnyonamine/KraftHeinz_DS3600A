#include <gui/snscaninventory_screen/SnScanInventoryView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/platform_itf.h>
#include <gui/common/Barcode.hpp>
#include <iostream>
#include <ctime>


uint16_t invt_qty =0;
uint32_t threshhold_invt = 30;
//extern uint16_t prev_screen_index;
//uint16_t invt_sendcount = 0;
//bool toastviewFlag = false;
invt1 invtrecord;
string learnBarcode = "";

#define LAUNCH_SCREEN 4


REGISTER_APPLICATION(
    SnScanInventoryView,
    "Scan Inventory",
    TRANSITION_CALLBACK(gotoSnScanInventoryScreenNoTransition),
    LAUNCH_SCREEN - 1
)
/* Manual BC Entry */
REGISTER_DESC_BOOL(sinvManBCEditDescr)
REGISTER_PARAMETER(
     sinvManBCEdit,
     "Manual BC Entry invt",
     "Manual BC Entry",
     "Scan Inventory",
     PARAM_TYPE_BOOL,
     0x00,
     1,
     false,
     sinvManBCEditDescr,
     0x01,
     1,
     user_cfg_set_barcode_editable_scaninv,
     user_cfg_get_barcode_editable_scaninv)

/* Manual QTY Edit configuration */
REGISTER_DESC_BOOL(sinvManQTYEditDescr)
REGISTER_PARAMETER(
     sinvManQTYEdit,
     "Manual QTY Entry invt",
     "Manual QTY Entry",
     "Scan Inventory",
     PARAM_TYPE_BOOL,
     0x00,
     1,
     false,
     sinvManQTYEditDescr,
     0x01,
     2,
     user_cfg_set_qty_editable_scaninv,
     user_cfg_get_qty_editable_scaninv)

/* Delimiter configuration */
REGISTER_DESC_NUM(sinvDelimDescr,
                   0,
				   127,
				   true,
				   true,
                   "INVT LOC Delimiter",
                   NVAL(0x0D, CR),
                   NVAL(0x0A, LF),
                   NVAL(0x20, Space),
                   NVAL(0x09, Tab (Default)),
                   NVAL(0x2C, ,),
                   NVAL(0x3A, :),
                   NVAL(0x3B, ;),
                   NVAL(0x3D, =))			 
REGISTER_PARAMETER(
     sinvDelim,
     "INVT LOC Delimiter",
     "LOC Delimiter",
     "Scan Inventory",	
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     true,
     sinvDelimDescr,
     0x09,
	 3,
     user_cfg_set_delimiter_scaninv,
     user_cfg_get_delimiter_scaninv)
REGISTER_DESC_NUM(sinvStoreDescr,
                  0,
                  1, 
                  false,
                  true,
                  "Inventory Store",
                  NVAL(0x00, Temporary (Default)),
                  NVAL(0x01, Permanent))
REGISTER_PARAMETER(
     sinvStore,
     "Inventory Store",
     "Inventory Store",
     "Scan Inventory",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     sinvStoreDescr,
     0x00,
     4,
     user_cfg_set_invstore_scaninv,
     user_cfg_get_invstore_scaninv)

/* LOC QTY Delimiter configuration */
REGISTER_DESC_NUM(sinvtqtyDelimDescr,
				   0,
				   127,
				   true,
				   true,
                   "INVT QTY Delimiter",
                   NVAL(0x0D, CR),
                   NVAL(0x0A, LF),
                   NVAL(0x20, Space),
                   NVAL(0x09, Tab (Default)),
                   NVAL(0x2C, ,),
                   NVAL(0x3A, :),
                   NVAL(0x3B, ;),
                   NVAL(0x3D, =))			   
REGISTER_PARAMETER(
     sinvtqtyDelim,
     "INVT QTY Delimiter",
     "QTY Delimiter",
     "Scan Inventory",	
     PARAM_TYPE_NUMERIC,
     0x88A,
     1,
     true,
     sinvtqtyDelimDescr,
     0x09,
	 5,
     user_cfg_set_invt_qty_delimiter,
     user_cfg_get_invt_qty_delimiter)

enum LocalFields
{
    BACK_ARROW_0 = 0,
    LOC_FIELD = 1,
    BACK_ARROW_2 = 2,
    BC_FIELD = 3,
    QTY_FIELD = 4,
    BACK_ARROW_5 = 5,
    ACTION_ITEM_1 = 6,
    ACTION_ITEM_2 = 7,
    ACTION_ITEM_3 = 8,
    ACTION_ITEM_4 = 9,
    BACK_ARROW_10 = 10,
};

SnScanInventoryView::SnScanInventoryView() :
    newSelItem(LOC_FIELD),
    oldSelItem(ACTION_ITEM_1),
    returnItem(LOC_FIELD),
    cueLocTimer(CUE_TIMEOUT),
    cueBcTimer(CUE_TIMEOUT),
    toastViewTimer(TOASTVIEW_TIMEOUT),
    submitMsgTimer(TOASTVIEW_TIMEOUT),
    barcode(""),
    location(""),
    bc_r_ptr(NULL),
    loc_r_ptr(NULL),
    quantity(0),
    invtListItem(0),
    invtListItemMax(0),
    homekeyActive(false),
    dataInProgress(false),
    locChange(false),
    toastInventViewTimer(TOASTVIEW_TIMEOUT),
    toastInventENTViewTimer(TOASTVIEW_TIMEOUT),
    toastInventFullViewTimer(TOASTVIEW_TIMEOUT),
    BTIconState(0)
{
    MenuItem[BACK_ARROW_0] = &ccBack;
    MenuItem[LOC_FIELD] = &ccLocField;
    MenuItem[BACK_ARROW_2] = &ccBack;
    MenuItem[BC_FIELD] = &ccBarcodeField;
    MenuItem[QTY_FIELD] = &ccQtyField;
    MenuItem[BACK_ARROW_5] = &ccBack;
    MenuItem[ACTION_ITEM_1] = &ccMenuItem_1;
    MenuItem[ACTION_ITEM_2] = &ccMenuItem_2;
    MenuItem[ACTION_ITEM_3] = &ccMenuItem_3;
    MenuItem[ACTION_ITEM_4] = &ccMenuItem_4;
    MenuItem[BACK_ARROW_10] = &ccBack;

    learnBarcode = application().getSavedBarcode();
}

void SnScanInventoryView::setupScreen()
{
    SnScanInventoryViewBase::setupScreen();
    ccMenuItem_1.setMenuText(touchgfx::TypedText(T_INVTACTIONMENU_01), touchgfx::TypedText(T_INVTACTIONMENUACT_01));
    ccMenuItem_2.setMenuText(touchgfx::TypedText(T_INVTACTIONMENU_02), touchgfx::TypedText(T_INVTACTIONMENUACT_02));
    ccMenuItem_3.setMenuText(touchgfx::TypedText(T_INVTACTIONMENU_03), touchgfx::TypedText(T_INVTACTIONMENUACT_03));
    ccMenuItem_4.setMenuText(touchgfx::TypedText(T_INVTACTIONMENU_04), touchgfx::TypedText(T_INVTACTIONMENUACT_04));
    presenter->UpdateAllIcons();
    presenter->setCurrentScreen(SCAN_INVENTORY_DATA);
    ccLocField.setEditable(true);
    ccBarcodeField.setEditable(presenter->getScanInvtBCEditable() == 1);
    ccQtyField.setEditable(presenter->getScanInvtQtyEditable() == 1);
    selectNewItem();
    ccToastBatchOn.setText(2);
    ccToastExitList.setText(3);
    scrollCnt.setScrollbarWidth(4);
    dragScroll(-1);
    dragScroll(1);
    scrollCnt.invalidate();
    scrollCntList.setScrollbarWidth(4);
    dragListScroll(-1);
    dragListScroll(1);
    scrollCntList.invalidate();
}

void SnScanInventoryView::tearDownScreen()
{
    SnScanInventoryViewBase::tearDownScreen();
}

void SnScanInventoryView::handleKeyEvent(uint8_t key)
{
    if (cQuitCfm.isVisible())
    {
        switch (key)
        {
        case KEYCODE_BKSP:
            cQuitCfm.setVisible(false);
            cQuitCfm.invalidate();
            break;

        case KEYCODE_ENTER:
            dataInProgress = false;
            presenter->clearRecords();
            presenter->setInvtInProgress(dataInProgress);
            application().gotoSnHomeMenuScreenNoTransition();
            break;
        }
        return;
    }

    if (cList.isVisible())
    {
        if (newSelItem == BACK_ARROW_10)
        {
            doForBack(key);
            return;
        }
        switch (key)
        {
        case KEYCODE_UP:
            if (invtListItem != 0)
            {
                int drag = (ccInvtList[invtListItem].getY() - ccInvtList[invtListItem - 1].getY()) / 56;
                dragListScroll(drag);
                ccInvtList[invtListItem].setFocus(false);
                invtListItem--;
                ccInvtList[invtListItem].setFocus(true);
                cList.invalidate();
            }
            else
            {
                dragListScroll(1);
                ccInvtList[invtListItem].setFocus(false);
                cList.invalidate();
                newSelItem = BACK_ARROW_10;
                selectNewItem();
            }
            break;

        case KEYCODE_DOWN:
            if (invtListItem < invtListItemMax)
            {
                int drag = (ccInvtList[invtListItem].getY() - ccInvtList[invtListItem + 1].getY()) / 56;
                dragListScroll(drag);
                ccInvtList[invtListItem].setFocus(false);
                invtListItem++;
                ccInvtList[invtListItem].setFocus(true);
                cList.invalidate();
            }
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            dragListScroll(INVT_LIST_ITEM_MAX);
            newSelItem = ACTION_ITEM_3;
            selectNewItem();
            cList.setVisible(false);
            cList.invalidate();
            scrollCntList.removeAll();
            invtListItem = 0;
            invtListItemMax = 0;
            break;
        }
        return;
    }

    if (textN1_InventBTView.isVisible())
    {
        switch (key)
        {
        case KEYCODE_ENTER:
            cActions.setVisible(true);  //Enable Actions page
            cActions.invalidate();
            textN1_InventBTView.setVisible(false);
            textN1_InventBTView.invalidate();
            textH1_InventBTView.setVisible(false);
            textH1_InventBTView.invalidate();
            textH2_InventBTView.setVisible(false);
            textH2_InventBTView.invalidate();

            imgRight.setAlpha(255);
            imgRight.invalidate();
            labelActions.setAlpha(255);
            labelActions.invalidate();
            ccLocField.setVisible(true);
            ccBarcodeField.setVisible(true);
            ccQtyField.setVisible(true);

            imgLoc.setVisible(true);
            imgLoc.invalidate();
            labelLoc.setVisible(true);
            labelLoc.invalidate();
            break;
        }
        return;
    }

    if (cActions.isVisible())
    {
        doForAction(key);
        return;
    }

      if(qty_popup)
      {
        qTYAdjust.setVisible(false);
        qTYAdjust.invalidate();
        qty_popup =false;
        return ;
      }

    switch (newSelItem)
    {
    case BACK_ARROW_0:
    case BACK_ARROW_2:
        doForBack(key);
        break;

    case LOC_FIELD:
        doForLocationInput(key);
        break;

    case BC_FIELD:
        doForBarcodeInput(key);
        break;

    case QTY_FIELD:
        doForQtyInput(key);
        break;
    }
}

void SnScanInventoryView::handleTickEvent()
{
    if (cueLocTimer < CUE_TIMEOUT)
    {
        cueLocTimer++;
        if (cueLocTimer == CUE_TIMEOUT)
        {
            ccSuccessCue.setVisible(false);
            ccSuccessCue.invalidate();
            acceptLoc();
        }
    }

    if (cueBcTimer < CUE_TIMEOUT)
    {
        cueBcTimer++;
        if (cueBcTimer == CUE_TIMEOUT)
        {
            ccSuccessCue.setVisible(false);
            ccSuccessCue.invalidate();
            acceptBarcode();
        }
    }

    if (toastViewTimer < TOASTVIEW_TIMEOUT)
    {
        toastViewTimer++;
        if (toastViewTimer == TOASTVIEW_TIMEOUT)    // toast view timeout
        {
            ccToastBatchOn.setVisible(false);
            ccToastBatchOn.invalidate();
            ccToastExitList.setVisible(false);
            ccToastExitList.invalidate();
        }
    }

    if (submitMsgTimer < TOASTVIEW_TIMEOUT)
    {
        submitMsgTimer++;
        if (submitMsgTimer == TOASTVIEW_TIMEOUT)    // submitMsg timeout
        {
            cSubmitMsg.setVisible(false);
            cSubmitMsg.invalidate();
        }
    }

    if (toastInventViewTimer < TOASTVIEW_TIMEOUT)
    {
        toastInventViewTimer++;
        if (toastInventViewTimer == TOASTVIEW_TIMEOUT)    // toast view timeout
        {
            ccinventToast.setVisible(false);
            ccinventToast.invalidate();
        }
    }

    if (toastInventENTViewTimer < TOASTVIEW_TIMEOUT)
    {
        toastInventENTViewTimer++;
        if (toastInventENTViewTimer == TOASTVIEW_TIMEOUT)    // toast view timeout
        {
            ccinventToastENT.setVisible(false);
            ccinventToastENT.invalidate();
        }
    }

    if (toastInventFullViewTimer < TOASTVIEW_LIST_LIMIT_TIMEOUT)
    {
        toastInventFullViewTimer++;
        if (toastInventFullViewTimer == TOASTVIEW_LIST_LIMIT_TIMEOUT)    // toast view timeout
        {
            ccinventToastFull.setVisible(false);
            ccinventToastFull.invalidate();
        }
    }
}

//Called when the screen is done with transition/load
void SnScanInventoryView::afterTransition()
{
invtrecord = presenter->getinvtAppVar();
    // show batch mode toast and icon
  if(invtrecord.finishBarcodeFlaginvt == false )
  {
    toastViewTimer = 0;                 // show toast
    ccToastBatchOn.setVisible(true);
    ccToastBatchOn.invalidate();
  }
    UpdateIcon(BatchOnIcon, Batch_On);
    invtrecord.finishBarcodeFlaginvt = false;
    presenter->setinvtAppVar(invtrecord);

    // clear barcode buffer when into this screen
    while (presenter->getBarcode() != NULL)
    {
        presenter->clearBarcode();
    }

    // check Inventory Progress been interrupt
    dataInProgress = presenter->getInvtInProgress();
    if (dataInProgress)
    {
        uint16_t RecoedIndex = 0;
        Invt_Record_t * ptr_invt_record_temp = presenter->getInvtRecord(RecoedIndex);
        while (ptr_invt_record_temp != NULL)
        {
            memset(loc_r.data, 0, sizeof(loc_r.data));
            memcpy(loc_r.data, ptr_invt_record_temp->location, ptr_invt_record_temp->LocationLength);
            loc_r.length = ptr_invt_record_temp->LocationLength;
            loc_r_ptr = &loc_r;
            location.assign(NonPrintCharFilter_l(loc_r_ptr));
            invtrecord.temp_location.assign(NonPrintCharFilter_l(loc_r_ptr));
            presenter->setinvtAppVar(invtrecord);

            if (location_list.empty())
            {
                location_list.push_back(*loc_r_ptr);
            }
            else
            {
                if (!LocCompare(&location_list.back(), loc_r_ptr))
                    location_list.push_back(*loc_r_ptr);
            }
            RecoedIndex++;
            ptr_invt_record_temp = presenter->getInvtRecord(RecoedIndex);
        }

        // jump to barcode if location had data
        if (!location_list.empty())
        {
            ccLocField.setText(const_cast<char *>(invtrecord.temp_location.c_str()));
            acceptLoc();
        }

        imgRight.setAlpha(255);
        imgRight.invalidate();
        labelActions.setAlpha(255);
        labelActions.invalidate();
    }
    if (invtrecord.finishBarcodeFlaginvt == true )
    {
        endOfBarcodeProgress();
    }
}

void SnScanInventoryView::selectNewItem()
{
    for (int i = 0; i < MENUITEM_MAX; i++)
    {
        MenuItem[i]->setFocus(false);
    }
    MenuItem[newSelItem]->setFocus(true);
}

void SnScanInventoryView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);

    if (IconId == BTIcon)
    {
        BTIconState = IconState;
    }
}

void SnScanInventoryView::BarcodeComeIn(char * BarcodeData)
{
    char datePart[11];
    char timePart[11];
    DataRecord readRecord;
    int count;

  invtrecord = presenter->getinvtAppVar();
    if (cActions.isVisible())
    {
        presenter->clearBarcode();
        toastInventViewTimer = 0;                  // Enable Toast view timer
        ccinventToast.setVisible(true);
        ccinventToast.invalidate();
        SendAvoidTransmissionDecodeDataCommand();  //Beeper 0x49
        return;
    }

    if (cueLocTimer < CUE_TIMEOUT)  // Still running when next barcode comein
    {
        cueLocTimer = CUE_TIMEOUT;  // stop timer
        ccSuccessCue.setVisible(false);
        ccSuccessCue.invalidate();
        acceptLoc();
    }

    if (cueBcTimer < CUE_TIMEOUT)   // Still running when next barcode comein
    {
        cueBcTimer = CUE_TIMEOUT;   // stop timer
        ccSuccessCue.setVisible(false);
        ccSuccessCue.invalidate();
        acceptBarcode();
    }

    switch (newSelItem)
    {
    case LOC_FIELD:
        bc_r_ptr = (BarcodeRecord_t *)((void *)BarcodeData);
        loc_r.length = (bc_r_ptr->length > 20) ? 20 : bc_r_ptr->length;
        memset(loc_r.data, 0, sizeof(loc_r.data));
        memcpy(loc_r.data, bc_r_ptr->data, loc_r.length);
        loc_r_ptr = &loc_r;
        ccLocField.setNextScan();
        location.assign(NonPrintCharFilter_l(loc_r_ptr));
        invtrecord.temp_location.assign(NonPrintCharFilter_l(loc_r_ptr));
        presenter->setinvtAppVar(invtrecord);
        ccLocField.setText(NonPrintCharFilter_l(loc_r_ptr));
        presenter->clearBarcode();
        cueLocTimer = 0;                    // set cue timer
        ccLocField.setCue(STATES_SUCCESS);
        ccSuccessCue.setVisible(true);
        ccSuccessCue.invalidate();
        break;

    case BC_FIELD:
        application().setSavedBarcode(BarcodeData);
        bc_r_ptr = (BarcodeRecord_t *)((void *)BarcodeData);
        bc_r_ptr->length = strlen(BarcodeData); //not set properly in simulation mode
        ccBarcodeField.setNextScan();
        barcode.assign(NonPrintCharFilter_b(bc_r_ptr));
        ccBarcodeField.setText(NonPrintCharFilter_b(bc_r_ptr));// get barcode data
        presenter->clearBarcode();
        cueBcTimer = 0;                     // set cue timer
        ccBarcodeField.setCue();
        ccSuccessCue.setVisible(true);
        ccSuccessCue.invalidate();

        time_t rawtime;
        struct tm* timeinfo;
        char buffer[80];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
        strcpy(datePart, buffer);
        strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
        strcpy(timePart, buffer);
        presenter->addRecord(datePart, timePart, BarcodeData, BarcodeData, "Y");
        presenter->updateRecord("oops", "RIY");
        count = presenter->getRecordCount();
        readRecord = presenter->getRecord(count);
        break;

    default:
        presenter->clearBarcode();
        break;
    }
}

void SnScanInventoryView::dragScroll(int drag)
{
    if (oldSelItem == BACK_ARROW_5)
    {
        if (newSelItem < ACTION_ITEM_3)
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

void SnScanInventoryView::dragListScroll(int drag)
{
    int16_t xPos = scrollCntList.getScrolledX();
    int16_t yOldPos = scrollCntList.getScrolledY();
    int16_t yNewPos = yOldPos + (56 * drag);
    DragEvent relative(DragEvent::DRAGGED, xPos, yOldPos, xPos, yNewPos);
    scrollCntList.handleDragEvent(relative);
}

void SnScanInventoryView::doForBack(uint8_t key)
{
    switch (newSelItem)
    {
    case BACK_ARROW_0:
        switch (key)
        {
        case KEYCODE_DOWN:
            newSelItem = LOC_FIELD;
            selectNewItem();
            break;

        case KEYCODE_HOME:
            if (dataInProgress)
            {
                homekeyActive = true;
                cQuitCfm.setVisible(true);
                cQuitCfm.invalidate();
            }
            else
            {
                doForHomeKey();
            }
            break;

        case KEYCODE_ENTER:
        case KEYCODE_ESC:
        case KEYCODE_BACK:
            if (dataInProgress)
            {
                homekeyActive = false;
                cQuitCfm.setVisible(true);
                cQuitCfm.invalidate();
            }
            else
            {
                application().gotoSnHomeMenuScreenNoTransition();
            }
            break;

        case KEYCODE_RIGHT:
            if (dataInProgress)
            {
                returnItem = BACK_ARROW_0;
                oldSelItem = ACTION_ITEM_1;
                newSelItem = ACTION_ITEM_1;
                selectNewItem();
                cActions.setVisible(true);
                cActions.invalidate();
            }
            break;
        }
        break;

    case BACK_ARROW_2:
        switch (key)
        {
        case KEYCODE_DOWN:
            newSelItem = BC_FIELD;
            selectNewItem();
            break;

        case KEYCODE_HOME:
            if (dataInProgress)
            {
                homekeyActive = true;
                cQuitCfm.setVisible(true);
                cQuitCfm.invalidate();
            }
            else
            {
                doForHomeKey();
            }
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
        case KEYCODE_ENTER:
            locChange = true;
            ccLocField.setVisible(true);
            ccBarcodeField.setVisible(false);
            ccQtyField.setVisible(false);
            labelLoc.setVisible(false);
            labelLoc.invalidate();
            imgLoc.setVisible(false);
            imgLoc.invalidate();
            newSelItem = BACK_ARROW_0;
            selectNewItem();
            break;

        case KEYCODE_RIGHT:
            if (dataInProgress)
            {
                returnItem = BACK_ARROW_2;
                oldSelItem = ACTION_ITEM_1;
                newSelItem = ACTION_ITEM_1;
                selectNewItem();
                cActions.setVisible(true);
                cActions.invalidate();
            }
            break;
        }
        break;

    case BACK_ARROW_10:
        switch (key)
        {
        case KEYCODE_DOWN:
            newSelItem = ACTION_ITEM_3;
            selectNewItem();
            invtListItem = 0;
            ccInvtList[invtListItem].setFocus(true);
            cList.invalidate();
            break;

        case KEYCODE_ENTER:
            dragListScroll(INVT_LIST_ITEM_MAX);
            newSelItem = ACTION_ITEM_3;
            selectNewItem();
            cList.setVisible(false);
            cList.invalidate();
            scrollCntList.removeAll();
            invtListItem = 0;
            invtListItemMax = 0;
            break;
        }
    }
}

void SnScanInventoryView::doForQtyInput(uint8_t key)
{
    if ((key >= '0') && (key <= '9'))
    {
        if (!ccQtyField.isEditable())
            return;
        if (!ccQtyField.isEditing())
        {
            ccQtyField.setEdit(true);
        }
        ccQtyField.insCh(key);
        return;
    }

    switch (key)
    {
    case KEYCODE_UP:
        newSelItem = BC_FIELD;
        selectNewItem();
        break;

    case KEYCODE_HOME:
        if (dataInProgress)
        {
            homekeyActive = true;
            cQuitCfm.setVisible(true);
            cQuitCfm.invalidate();
        }
        else
        {
            doForHomeKey();
        }
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        locChange = true;
        ccLocField.setVisible(true);
        ccBarcodeField.setVisible(false);
        ccQtyField.setVisible(false);
        labelLoc.setVisible(false);
        labelLoc.invalidate();
        imgLoc.setVisible(false);
        imgLoc.invalidate();
        newSelItem = LOC_FIELD;
        selectNewItem();
        break;

    case KEYCODE_ENTER:
        if (ccQtyField.isEditing())
        {
            quantity = ccQtyField.getNumber();
            if (quantity == 0)
            {
                ccQtyField.setNextScan();
                return;
            }

            uint32_t minvalue = GenericParamGetInt(gblMinQtyValue_attr);
            uint32_t maxvalue = GenericParamGetInt(gblMaxQtyValue_attr);
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

            acceptQty();
        }
        else
        {
            quantity = 1;
            acceptQty();
        }
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
    }
}

void SnScanInventoryView::doForBarcodeInput(uint8_t key)
{
    if ((key >= 0x20) && (key <= 0x7E))
    {
        if (!ccBarcodeField.isEditable())   // Barcode is not editable
            return;
        if (!ccBarcodeField.isEditing())
        {
            ccBarcodeField.setEdit(true);
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
        newSelItem = BACK_ARROW_2;
        selectNewItem();
        break;

    case KEYCODE_DOWN:
        newSelItem = QTY_FIELD;
        selectNewItem();
        break;

    case KEYCODE_HOME:
        if (dataInProgress)
        {
            homekeyActive = true;
            cQuitCfm.setVisible(true);
            cQuitCfm.invalidate();
        }
        else
        {
            doForHomeKey();
        }
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        locChange = true;
        ccLocField.setVisible(true);
        ccBarcodeField.setVisible(false);
        ccQtyField.setVisible(false);
        labelLoc.setVisible(false);
        labelLoc.invalidate();
        imgLoc.setVisible(false);
        imgLoc.invalidate();
        newSelItem = LOC_FIELD;
        selectNewItem();
        break;

    case KEYCODE_ENTER:
        if (!ccBarcodeField.isEditing())
            return;
        if (ccBarcodeField.getText() == NULL)
        {
            ccBarcodeField.setNextScan();
            return;
        }
        barcode.assign(ccBarcodeField.getText());
        memset(bc_r.data, 0, sizeof(bc_r.data));
        barcode.copy(bc_r.data, barcode.length());
        bc_r.length = barcode.length();
        bc_r.type = 0x03;
        bc_r_ptr = &bc_r;
        acceptBarcode();
        break;

    case KEYCODE_LEFT:
        if (!ccBarcodeField.isEditing())
            return;
        ccBarcodeField.moveCursorLeft();
        break;

    case KEYCODE_RIGHT:
        if (!ccBarcodeField.isEditing())
        {
            if (dataInProgress)
            {
                returnItem = BC_FIELD;
                oldSelItem = ACTION_ITEM_1;
                newSelItem = ACTION_ITEM_1;
                selectNewItem();
                cActions.setVisible(true);
                cActions.invalidate();
            }
            return;
        }
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
        if (!ccBarcodeField.isEditable())  // Barcode is not editable
            return;
        if (!ccBarcodeField.isEditing())
        {
            ccBarcodeField.setEdit(true);
        }
        ccBarcodeField.insStr(presenter->getFnKeyRemapString(key - KEYCODE_F1 + 1));
        break;
    }
}

void SnScanInventoryView::doForLocationInput(uint8_t key)
{
  invtrecord = presenter->getinvtAppVar();
    if ((key >= 0x20) && (key <= 0x7E))
    {
        if (!ccLocField.isEditing())
        {
            ccLocField.setEdit(true);
        }
        ccLocField.insCh(key);
        return;
    }
    if ((key >= 0x81) && (key <= 0xDF))     // for multi tap
    {
        if (!ccLocField.isEditing())
            return;
        ccLocField.modifyCh(~(key));
        return;
    }

    switch (key)
    {
    case KEYCODE_UP:
        if (ccLocField.isEditing())
            return;
        newSelItem = BACK_ARROW_0;
        selectNewItem();
        break;

    case KEYCODE_HOME:
        if (dataInProgress)
        {
            homekeyActive = true;
            cQuitCfm.setVisible(true);
            cQuitCfm.invalidate();
        }
        else
        {
            doForHomeKey();
        }
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        if (dataInProgress)
        {
            homekeyActive = false;
            cQuitCfm.setVisible(true);
            cQuitCfm.invalidate();
        }
        else
        {
            application().gotoSnHomeMenuScreenNoTransition();
        }
        break;

    case KEYCODE_ENTER:
        if (!ccLocField.isEditing())
            return;
        if (ccLocField.getText() == NULL)
        {
            ccLocField.setNextScan();
            return;
        }
        location.assign(ccLocField.getText());
        invtrecord.temp_location.assign(ccLocField.getText());
        presenter->setinvtAppVar(invtrecord);
        memset(loc_r.data, 0, sizeof(loc_r.data));
        location.copy(loc_r.data, location.length());
        loc_r.length = location.length();
        loc_r_ptr = &loc_r;
        acceptLoc();
        break;

    case KEYCODE_LEFT:
        if (!ccLocField.isEditing())
            return;
        ccLocField.moveCursorLeft();
        break;

    case KEYCODE_RIGHT:
        if (!ccLocField.isEditing())
        {
            if (dataInProgress)
            {
                returnItem = LOC_FIELD;
                oldSelItem = ACTION_ITEM_1;
                newSelItem = ACTION_ITEM_1;
                selectNewItem();
                cActions.setVisible(true);
                cActions.invalidate();
            }
            return;
        }
        ccLocField.moveCursorRight();
        break;

    case KEYCODE_BKSP:
        if (!ccLocField.isEditing())
            return;
        ccLocField.delCh();
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
        if (!ccLocField.isEditing())
        {
            ccLocField.setEdit(true);
        }
        ccLocField.insStr(presenter->getFnKeyRemapString(key - KEYCODE_F1 + 1));
        break;
    }
}

void SnScanInventoryView::doForAction(uint8_t key)
{
    switch (key)
    {
    case KEYCODE_UP:
        newSelItem = (newSelItem == BACK_ARROW_5) ? BACK_ARROW_5 : newSelItem - 1;
        dragScroll(oldSelItem - newSelItem);
        selectNewItem();
        oldSelItem = newSelItem;
        break;

    case KEYCODE_DOWN:
        newSelItem = (newSelItem == ACTION_ITEM_4) ? ACTION_ITEM_4 : newSelItem + 1;
        dragScroll(oldSelItem - newSelItem);
        selectNewItem();
        oldSelItem = newSelItem;
        break;

    case '1':
    case '2':
    case '3':
    case '4':
        newSelItem = key - '0' + BACK_ARROW_5;
        dragScroll(oldSelItem - newSelItem);
        selectNewItem();
        oldSelItem = newSelItem;
        break;

    case KEYCODE_ENTER:
        switch (newSelItem)
        {
        case BACK_ARROW_5:
            dragScroll(4);
            newSelItem = returnItem;
            selectNewItem();
            cActions.setVisible(false);
            cActions.invalidate();
            break;

        case ACTION_ITEM_1:
            location.clear();
            barcode.clear();
            dragScroll(4);
            labelLoc.setVisible(false);
            labelLoc.invalidate();
            imgLoc.setVisible(false);
            imgLoc.invalidate();
            ccLocField.setVisible(true);
            ccBarcodeField.setVisible(false);
            ccQtyField.setVisible(false);
            ccLocField.setNextScan();
            newSelItem = LOC_FIELD;
            selectNewItem();
            cActions.setVisible(false);
            cActions.invalidate();
            break;

        case ACTION_ITEM_2:
            if(presenter->checkBTPopup())
            {
                SendAvoidTransmissionDecodeDataCommand();  //Beeper
                cActions.setVisible(false);  //Disable Actions page
                cActions.invalidate();

                imgRight.setAlpha(0);
                imgRight.invalidate();
                labelActions.setAlpha(0);
                labelActions.invalidate();
                ccLocField.setVisible(false);
                ccBarcodeField.setVisible(false);
                ccQtyField.setVisible(false);

                imgLoc.setVisible(false);
                imgLoc.invalidate();
                labelLoc.setVisible(false);
                labelLoc.invalidate();

                textN1_InventBTView.setVisible(true);
                textN1_InventBTView.invalidate();
                textH1_InventBTView.setVisible(true);
                textH1_InventBTView.invalidate();
                textH2_InventBTView.setVisible(true);
                textH2_InventBTView.invalidate();
                toastInventENTViewTimer = 0;                  // Enable Toast view timer
                ccinventToastENT.setVisible(true);
                ccinventToastENT.invalidate();
                return;
            }

            presenter->submitInvtList();
            invt_qty = presenter->sendtotalqtyinvt();
            screenTransitionToProgress();
            dataInProgress = false;
            imgRight.setAlpha(102);
            imgRight.invalidate();
            labelActions.setAlpha(102);
            labelActions.invalidate();
            //showSubmitMsg();
            location_list.clear();
            location.clear();
            barcode.clear();
            dragScroll(4);
            labelLoc.setVisible(false);
            labelLoc.invalidate();
            imgLoc.setVisible(false);
            imgLoc.invalidate();
            ccLocField.setVisible(true);
            ccBarcodeField.setVisible(false);
            ccQtyField.setVisible(false);
            ccLocField.setNextScan();
            newSelItem = LOC_FIELD;
            selectNewItem();
            cActions.setVisible(false);
            cActions.invalidate();
            break;

        case ACTION_ITEM_3:
            toastViewTimer = 0;                 // show toast
            ccToastExitList.setVisible(true);
            ccToastExitList.invalidate();
            showInvtList();
            break;

        case ACTION_ITEM_4:
            if (dataInProgress)
            {
                homekeyActive = false;
                cQuitCfm.setVisible(true);
                cQuitCfm.invalidate();
            }
            else
            {
                application().gotoSnHomeMenuScreenNoTransition();
            }
            return;
        }
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        dragScroll(4);
        newSelItem = returnItem;
        selectNewItem();
        cActions.setVisible(false);
        cActions.invalidate();
        break;
    }
}

void SnScanInventoryView::doForHomeKey()
{
    presenter->clearRecords();
    presenter->keyPressed(KEYCODE_HOME);
}

void SnScanInventoryView::acceptLoc()
{
    invtrecord = presenter->getinvtAppVar();
    Unicode::UnicodeChar tempStr[LABELLOC_SIZE];
    int length = invtrecord.temp_location.length();
    if (length < LABELLOC_SIZE)
        Unicode::strncpy(tempStr, invtrecord.temp_location.c_str(), LABELLOC_SIZE - 1);
    else
    {
        Unicode::strncpy(tempStr, invtrecord.temp_location.c_str() + (length - LABELLOC_SIZE + 1), LABELLOC_SIZE - 1);
        tempStr[0] = ELLIPSIS;    // show ..
    }
    Unicode::snprintf(labelLocBuffer, LABELLOC_SIZE, "%s", tempStr);
    labelLoc.setVisible(true);
    labelLoc.invalidate();
    imgLoc.setVisible(true);
    imgLoc.invalidate();

    if (locChange)
    {
        presenter->changeLoc(&location_list.back(), loc_r_ptr);
        location_list.pop_back();
        locChange = false;
    }
    if (location_list.empty())
    {
        location_list.push_back(*loc_r_ptr);
    }
    else
    {
        if (!LocCompare(&location_list.back(), loc_r_ptr))
            location_list.push_back(*loc_r_ptr);
    }

    invtrecord.temp_loc_list = location_list;
    presenter->setinvtAppVar(invtrecord);
    ccLocField.setVisible(false);
    ccBarcodeField.setVisible(true);
    ccQtyField.setVisible(true);
    newSelItem = BC_FIELD;
    selectNewItem();
}

void SnScanInventoryView::acceptBarcode()
{
    if (!ccQtyField.isEditable())      // Qty is not editable
    {
        quantity = 1;
        presenter->setInvtRecord(loc_r_ptr, bc_r_ptr, quantity);
        if (!dataInProgress)
        {
            dataInProgress = true;
            presenter->setInvtInProgress(dataInProgress);
            imgRight.setAlpha(255);
            imgRight.invalidate();
            labelActions.setAlpha(255);
            labelActions.invalidate();
        }
        barcode.clear();
        ccBarcodeField.setNextScan();
        newSelItem = BC_FIELD;
    }
    else
    {
        newSelItem = QTY_FIELD;
    }
    selectNewItem();

    if (InventListFullFlag == 1)
    {
        presenter->clearBarcode();
        toastInventFullViewTimer = 0;                  // Enable Toast view timer
        ccinventToastFull.setVisible(true);
        ccinventToastFull.invalidate();
        SendInventoryListFullCommand(); // Beeper 0x35
    }
}

void SnScanInventoryView::acceptQty()
{
    if (barcode.empty())
    {
        newSelItem = BC_FIELD;
        selectNewItem();
        return;
    }

    presenter->setInvtRecord(loc_r_ptr, bc_r_ptr, quantity);
    if (!dataInProgress)
    {
        dataInProgress = true;
        presenter->setInvtInProgress(dataInProgress);
        imgRight.setAlpha(255);
        imgRight.invalidate();
        labelActions.setAlpha(255);
        labelActions.invalidate();
    }
    barcode.clear();
    ccBarcodeField.setNextScan();
    ccQtyField.setNextScan();
    newSelItem = BC_FIELD;
    selectNewItem();

    if (InventListFullFlag == 1)
    {
        toastInventFullViewTimer = 0;   // Enable Toast view timer
        ccinventToastFull.setVisible(true);
        ccinventToastFull.invalidate();
        SendInventoryListFullCommand(); // Beeper 0x35
    }
}

void SnScanInventoryView::showInvtList()
{
    uint16_t indexInvtList = 0;
    uint16_t indexInvtRecord = 0;
    Invt_Record_t * tempInvtRecord = presenter->getInvtRecord(indexInvtRecord);
    memset(loc_r.data, 0, sizeof(loc_r.data));
    memcpy(loc_r.data, tempInvtRecord->location, tempInvtRecord->LocationLength);
    loc_r.length = tempInvtRecord->LocationLength;
    loc_r_ptr = &loc_r;
    memset(bc_r.data, 0, sizeof(bc_r.data));
    memcpy(bc_r.data, tempInvtRecord->barcode, tempInvtRecord->BardcodeLength);
    bc_r.length = tempInvtRecord->BardcodeLength;
    bc_r_ptr = &bc_r;

    for (uint16_t i = 0;(i < location_list.size()) && (i < INVT_LIST_LOC_ITEM_MAX);i++)
    {
        ccInvtList_Loc[i].setXY(0, 56 * indexInvtList);
        ccInvtList_Loc[i].setText(NonPrintCharFilter_l(&location_list[i]));
        scrollCntList.add(ccInvtList_Loc[i]);
        indexInvtList++;

        while ((tempInvtRecord != NULL) &&
               (indexInvtRecord < INVT_LIST_ITEM_MAX) &&
               (LocCompare(&location_list[i], loc_r_ptr)))
        {
            Barcode tempBC;
            tempBC.setText(NonPrintCharFilter_b(bc_r_ptr));
            ccInvtList[indexInvtRecord].setXY(0, 56 * indexInvtList);
            ccInvtList[indexInvtRecord].setText(tempBC.getEllipsis(), tempBC.getSfont(),
                                            tempBC.getLfont(), tempInvtRecord->quantity);
            scrollCntList.add(ccInvtList[indexInvtRecord]);
            indexInvtList++;
            indexInvtRecord++;
            tempInvtRecord = presenter->getInvtRecord(indexInvtRecord);
            if (tempInvtRecord != NULL)
            {
                memset(loc_r.data, 0, sizeof(loc_r.data));
                memcpy(loc_r.data, tempInvtRecord->location, tempInvtRecord->LocationLength);
                loc_r.length = tempInvtRecord->LocationLength;
                loc_r_ptr = &loc_r;
                memset(bc_r.data, 0, sizeof(bc_r.data));
                memcpy(bc_r.data, tempInvtRecord->barcode, tempInvtRecord->BardcodeLength);
                bc_r.length = tempInvtRecord->BardcodeLength;
                bc_r_ptr = &bc_r;
            }
        }
    }
    invtListItemMax = indexInvtRecord - 1;
    invtListItem = 0;
    ccInvtList[invtListItem].setFocus(true);
    dragListScroll(-(invtListItemMax));
    dragListScroll(invtListItemMax);
    cList.setVisible(true);
    cList.invalidate();
}

void SnScanInventoryView::showSubmitMsg()
{
    invtrecord = presenter->getinvtAppVar();
    if (invtrecord.temp_loc_list.size() == 1)
    {
        Unicode::UnicodeChar tempStr[TEXTLOC_SIZE];
        int length = invtrecord.temp_location.length();
        if (length < TEXTLOC_SIZE)
            Unicode::strncpy(tempStr, invtrecord.temp_location.c_str(), TEXTLOC_SIZE - 1);
        else
        {
            Unicode::strncpy(tempStr, invtrecord.temp_location.c_str() + (length - TEXTLOC_SIZE + 1), TEXTLOC_SIZE - 1);
            tempStr[0] = ELLIPSIS;    // show ..
        }
        Unicode::snprintf(textLocBuffer, TEXTLOC_SIZE, "%s", tempStr);
        textLoc.setXY(190,38);
        textMoreLoc.setVisible(false);
        textNormal.setTypedText(touchgfx::TypedText(T_INVTVIEW_01_1));
    }
    else 
    {
        Unicode::UnicodeChar tempStr[TEXTLOC_SIZE];
        invtrecord.temp_location.assign(NonPrintCharFilter_l(&invtrecord.temp_loc_list.front()));
        presenter->setinvtAppVar(invtrecord);
        int length = invtrecord.temp_location.length();
        if (length < TEXTLOC_SIZE)
            Unicode::strncpy(tempStr, invtrecord.temp_location.c_str(), TEXTLOC_SIZE - 1);
        else
        {
            Unicode::strncpy(tempStr, invtrecord.temp_location.c_str() + (length - TEXTLOC_SIZE + 1), TEXTLOC_SIZE - 1);
            tempStr[0] = ELLIPSIS;    // show ..
        }
        Unicode::snprintf(textLocBuffer, TEXTLOC_SIZE, "%s", tempStr);
        textLoc.setXY(52,77);
        Unicode::snprintf(textMoreLocBuffer, TEXTMORELOC_SIZE, "%d", (invtrecord.temp_loc_list.size() - 1));
        textMoreLoc.setXY(169,77);
        textMoreLoc.setVisible(true);
        textNormal.setTypedText(touchgfx::TypedText(T_INVTVIEW_01_2));
    }

    cSubmitMsg.setVisible(true);
    cSubmitMsg.invalidate();
    submitMsgTimer = 0;
}

void SnScanInventoryView::screenTransitionToProgress()
{
    bool sendQtyEnabledMode = false;
    if (dataInProgress)
    {
        if (presenter->getQtyTransferMode() == 2)
        {
            sendQtyEnabledMode = true;
        }
        if(invt_qty >= threshhold_invt && !sendQtyEnabledMode)
        {
            //prev_screen_index = 3;
            application().gotoSnBarcodeProgressScreenNoTransition();
        }
        else
        {
            showSubmitMsg();
        }
    }
}

void SnScanInventoryView::endOfBarcodeProgress()
{
    invtrecord = presenter->getinvtAppVar();
    showSubmitMsg();
    invtrecord.finishBarcodeFlaginvt = false;
    presenter->setinvtAppVar(invtrecord);
    
}

bool SnScanInventoryView::LocCompare(LocRecord_t * loc_s, LocRecord_t * loc_d)
{
    if (loc_s->length != loc_d->length)
        return false;
    if (memcmp(loc_s->data, loc_d->data, loc_s->length) == 0)
        return true;
    return false;
}

