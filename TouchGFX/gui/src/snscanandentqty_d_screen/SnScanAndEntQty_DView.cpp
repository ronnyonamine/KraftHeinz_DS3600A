#include <gui/snscanandentqty_d_screen/SnScanAndEntQty_DView.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/platform_itf.h>
#include <gui/common/ConfigParam.hpp>


/* This defines the position priority of the application in the main menu */
#define LAUNCH_SCREEN 2

 
enum LocalFields
{
    BACK_ARROW = 0,
    BC_FIELD = 1,
    QTY_FIELD = 2,
};

enum SCAN_n_QTY_PROGESS
{
    READY_STATE = 0,
    BARCODE_1ST = 1,
    QUANTITY_1ST = 2,
    RECALL_KEY = 3
};
SnScanAndEntQty_DView::SnScanAndEntQty_DView() :
    selectItem(BC_FIELD),
    cueBcTimer(CUE_TIMEOUT),
    cueQtyTimer(CUE_TIMEOUT),
    QtyInputTimer(0),
    QtyInputTimerMax(0),
    QtyViewTimer(QtyView_Timeout),
    toastQtyViewTimer(TOASTVIEW_TIMEOUT),
    toastBcViewTimer(TOASTVIEW_TIMEOUT),
    BcInputTimer(0),
    BcInputTimerMax(0),
    barcode(""),
    bc_r_ptr(NULL),
    quantity(0),
    quantityBackup(0),
    recallTimer(RECALL_TIMEOUT),
    screen_lock(false),
    ScanQtyProgess(READY_STATE)
{
    MenuItem[BACK_ARROW] = &ccBack;
    MenuItem[BC_FIELD] = &ccBarcodeField;
    MenuItem[QTY_FIELD] = &ccQtyField;
}

void SnScanAndEntQty_DView::setupScreen()
{
    SnScanAndEntQty_DViewBase::setupScreen();
    presenter->UpdateAllIcons();
    ccBarcodeField.setFocusable(presenter->getScanQtyBCEditable() == Manual_Entry_Yes);
    ccQtyField.setFocusable(presenter->getScanQtyQtyEditable() == Manual_Entry_Yes);
    presenter->setCurrentScreen(SCAN_QTY_RESEND_DATA);
    selectNewItem();
    ccToastQTY.setText(0);
    ccToastBarcode.setText(1);
    QtyView_Timeout = GenericParamGetInt(sqtyToutConf_attr)*60;
    QtyViewTimer = QtyView_Timeout;
}

void SnScanAndEntQty_DView::tearDownScreen()
{
    SnScanAndEntQty_DViewBase::tearDownScreen();
}

//Handles when a key is pressed
void SnScanAndEntQty_DView::handleKeyEvent(uint8_t key)
{
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

    presenter->keyPressed(key);

    if(qty_popup)
    {
        qTYAdjust.setVisible(false);
        qTYAdjust.invalidate();
        qty_popup = false;
        return;
    }

    switch (selectItem)
    {
    case BACK_ARROW:
        doForBack(key);
        break;

    case BC_FIELD:
        doForBarcodeInput(key);
        break;

    case QTY_FIELD:
        doForQtyInput(key);
        break;
    }
}

void SnScanAndEntQty_DView::handleTickEvent()
{
    uint32_t minvalue = 0;
    uint32_t maxvalue = 0;

    if (cueBcTimer < CUE_TIMEOUT)
    {
        cueBcTimer++;
        if (cueBcTimer == CUE_TIMEOUT)  // SuccessCue timeout start QTY input timer
        {
            ccSuccessCue.setVisible(false);
            ccSuccessCue.invalidate();
            selectNewItem();
            resetProgress();
            if (ccQtyField.isFocusable())
            {
                QtyInputTimer = 0;
            }
            else
            {
                showQtySubmit(1);
                ccBarcodeField.setNextScan();           // reset barcode field
            }
        }
    }

    if (cueQtyTimer < CUE_TIMEOUT)
    {
        cueQtyTimer++;
        if (cueQtyTimer == CUE_TIMEOUT)  // SuccessCue timeout start QTY input timer
        {
            ccSuccessCue.setVisible(false);
            ccSuccessCue.invalidate();
            selectNewItem();
            showQtySubmit(quantityBackup);  // pop QTY view and start timer
        }
    }

    if (QtyInputTimerMax > 0)
    {
        if (QtyInputTimer < QtyInputTimerMax)
        {
            QtyInputTimer++;
            if ((QtyInputTimer % 60) == 0)
            {
                if ((QtyInputTimerMax - QtyInputTimer) < 180)
                    pgEnterQtyTimer.setColor(STATES_ERROR);
                pgEnterQtyTimer.setValue(QtyInputTimer);
                pgEnterQtyTimer.invalidate();
                ili9342c_StopTimeoutDimming(); //Wait QTY Timer finish, then display timeout
            }
            if (QTY_FIELD != selectItem)
                resetProgress();
        }
        else if (QtyInputTimer == QtyInputTimerMax) // QTY input timeout start QTY view timer
        {
            resetProgress();
            ili9342c_DisplayOn(); //Wait QTY Timer finish, then display timeout

            if (bc_r_ptr != NULL)
            {
                if(presenter->checkBTPopup())
                {
                    showBTPopUp();
                    return;
                }

                if(qty_popup)
				{
                    //this check is just to not show/avoid qty submitted message when we are in qty error message popupscreen
                    return ;
                }

                if (!barcodeBackup.empty())
                    barcodeBackup.clear();
                barcodeBackup.push_back(*bc_r_ptr);

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
                else
                {
                    presenter->sendBcQty(bc_r_ptr, quantity);
                    ccBarcodeField.setNextScan();
                    ccQtyField.setNextScan();
                }
                showQtySubmit(quantity);   // 0 for timeout
            }
            else
                gotoReadyState();
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

    if (toastQtyViewTimer < TOASTVIEW_TIMEOUT)
    {
        toastQtyViewTimer++;
        if (toastQtyViewTimer == TOASTVIEW_TIMEOUT)    // toast view timeout
        {
            ccToastQTY.setVisible(false);
            ccToastQTY.invalidate();
            resetProgress();
            if (QTY_FIELD == selectItem)
                QtyInputTimer = 0;
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

    if (BcInputTimerMax > 0)
    {
        if (BcInputTimer < BcInputTimerMax)
        {
            BcInputTimer++;
            if ((BcInputTimer % 60) == 0)
            {
                if ((BcInputTimerMax - BcInputTimer) < 180)
                    pgEnterQtyTimer.setColor(STATES_ERROR);
                pgEnterQtyTimer.setValue(BcInputTimer);
                pgEnterQtyTimer.invalidate();
            }
        }
        else if (BcInputTimer == BcInputTimerMax) // QTY input timeout start QTY view timer
        {
            gotoReadyState();
            selectItem = BC_FIELD;
            selectNewItem();
        }
    }

    if (recallTimer < RECALL_TIMEOUT)
    {
        recallTimer++;
        if (recallTimer == RECALL_TIMEOUT)  // recall timeout
        {
            // gotoReadyState();
            ScanQtyProgess = BARCODE_1ST;
        }
    }
}

//Called when the screen is done with transition/load
void SnScanAndEntQty_DView::afterTransition()
{
    QtyInputTimerMax = presenter->getQTYToutValue();
    QtyInputTimer = QtyInputTimerMax + 1;
    BcInputTimerMax = QtyInputTimerMax;
    BcInputTimer = QtyInputTimer;
    if (QtyInputTimerMax > 0)
        pgEnterQtyTimer.setRange(0, QtyInputTimerMax);
    char * bc_temp_ptr = presenter->getBarcode();
    if (bc_temp_ptr != NULL)
        BarcodeComeIn(bc_temp_ptr);
}

void SnScanAndEntQty_DView::selectNewItem()
{
    for (int i = 0; i < MENUITEM_MAX; i++)
    {
        MenuItem[i]->setFocus(selectItem == i);
    }
}

void SnScanAndEntQty_DView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnScanAndEntQty_DView::BarcodeComeIn(char * BarcodeData)
{
    uint32_t minvalue = 0;
    uint32_t maxvalue = 0;

    if(presenter->checkBTPopup())
    {
        showBTPopUp();
        return;
    }
	
    if (QtyViewTimer < QtyView_Timeout)
    {
        QtyViewTimer = QtyView_Timeout; // stop timer
        gotoReadyState();
    }

    if ((ScanQtyProgess == BARCODE_1ST) && (!ccBarcodeField.isEditing()))
    {
        if (!barcodeBackup.empty())
            barcodeBackup.clear();
        barcodeBackup.push_back(*bc_r_ptr);
        presenter->sendBcQty(bc_r_ptr, 1);
        gotoReadyState();
    }
    else if ((ScanQtyProgess == BARCODE_1ST) ||
             ((ScanQtyProgess == QUANTITY_1ST) && (quantity == 0)) ||
             (ScanQtyProgess == RECALL_KEY))
    {
        gotoReadyState();
    }

    bc_r_ptr = (BarcodeRecord_t *)((void *)BarcodeData);
    bc_r_ptr->length = strlen(BarcodeData); //not set properly in simulation mode
    ccBarcodeField.setText(NonPrintCharFilter_b(bc_r_ptr));
    presenter->clearBarcode();
    ccBarcodeField.setCue();
    ccQtyField.setCue();
    ccSuccessCue.setVisible(true);
    ccSuccessCue.invalidate();
    if (ScanQtyProgess == READY_STATE)
    {
        cueBcTimer = 0;                 // set cue timer of barcode come 1st
        if (ccQtyField.isFocusable())
        {
            ScanQtyProgess = BARCODE_1ST;
            selectItem = QTY_FIELD;
        }
        else
        {
            if (!barcodeBackup.empty())
                barcodeBackup.clear();
            barcodeBackup.push_back(*bc_r_ptr);
            presenter->sendBcQty(bc_r_ptr, 1);
        }
    }
    else if ((ScanQtyProgess == QUANTITY_1ST) && (quantity > 0))
    {
        resetProgress();
        cueQtyTimer = 0;                        // set cue timer of Qty come 1st
        ScanQtyProgess = READY_STATE;
        if (!barcodeBackup.empty())
            barcodeBackup.clear();
        barcodeBackup.push_back(*bc_r_ptr);

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

        presenter->sendBcQty(bc_r_ptr, quantity);
        quantityBackup = quantity;
        barcode.clear();                 // reset variable
        bc_r_ptr = NULL;
        memset(bc_r.data, 0, sizeof(bc_r.data));
        quantity = 0;
    }
}

void SnScanAndEntQty_DView::doForBack(uint8_t key)
{
    switch (key)
    {
    case KEYCODE_DOWN:
        selectItem = BC_FIELD;
        selectNewItem();
        break;

    case KEYCODE_HOME:
        doForHomeKey();
        break;

    case KEYCODE_ENTER:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_RECALL:
        doForRecallKey();
        break;
    }
}

void SnScanAndEntQty_DView::doForQtyInput(uint8_t key)
{
    uint32_t minvalue = 0;
    uint32_t maxvalue = 0;
    if ((key >= '0') && (key <= '9'))
    {
        resetProgress();
        QtyInputTimer = 0;                          // restart QTY input timer
        if (!ccQtyField.isEditing())
        {
            ccQtyField.setEdit(true);
            toastQtyViewTimer = 0;                  // Enable Toast view timer
            ccToastQTY.setVisible(true);
            ccToastQTY.invalidate();
            QtyInputTimer = QtyInputTimerMax + 1;   // Disable QTY input timer
        }
        ccQtyField.insCh(key);
        return;
    }

    switch (key)
    {
    case KEYCODE_UP:
        selectItem = BC_FIELD;
        selectNewItem();
        break;

    case KEYCODE_HOME:
        doForHomeKey();
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_ENTER:
        quantity = ccQtyField.getNumber();
        if (quantity == 0)
            quantity = 1;
        resetProgress();
        toastQtyViewTimer = TOASTVIEW_TIMEOUT;  // Disable Qty toast view timer
        ccToastQTY.setVisible(false);
        ccToastQTY.invalidate();
        if(presenter->checkBTPopup())
        {
            showBTPopUp();
            return;
        }

        if (bc_r_ptr != NULL)                    // if barcode is ready do
        {
            if (!barcodeBackup.empty())
                barcodeBackup.clear();
            barcodeBackup.push_back(*bc_r_ptr);

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

            presenter->sendBcQty(bc_r_ptr, quantity);
            showQtySubmit(quantity);            // pop QTY view and start timer
            ccBarcodeField.setNextScan();
            ccQtyField.setNextScan();
		    ScanQtyProgess = READY_STATE;
        }
        else                                    // if barcode is not ready do
        {
            BcInputTimer = 0;                   // enable barcode input timer
            if (ScanQtyProgess == READY_STATE)
                ScanQtyProgess = QUANTITY_1ST;
        }
        selectItem = BC_FIELD;
        selectNewItem();
        break;

    case KEYCODE_LEFT:
        if (!ccQtyField.isEditing())
            return;
        resetProgress();
        QtyInputTimer = 0;                      // restart QTY input timer
        ccQtyField.moveCursorLeft();
        break;

    case KEYCODE_RIGHT:
        if (!ccQtyField.isEditing())
            return;
        resetProgress();
        QtyInputTimer = 0;                      // restart QTY input timer
        ccQtyField.moveCursorRight();
        break;

    case KEYCODE_BKSP:
        if (!ccQtyField.isEditing())
            return;
        resetProgress();
        QtyInputTimer = 0;                      // restart QTY input timer
        ccQtyField.delCh();
        break;

    case KEYCODE_RECALL:
        doForRecallKey();
        break;
    }
}

void SnScanAndEntQty_DView::doForBarcodeInput(uint8_t key)
{
    uint32_t minvalue = 0;
    uint32_t maxvalue = 0;

    if (cueBcTimer < CUE_TIMEOUT)
        return;

    if (ccBarcodeField.isFocusable())
    {
        if ((key >= 0x20) && (key <= 0x7E))
        {
            if (!ccBarcodeField.isEditing())
            {
                ccBarcodeField.setEdit(true);
                toastBcViewTimer = 0;               // Enable Toast view timer
                ccToastBarcode.setVisible(true);
                ccToastBarcode.invalidate();
                resetProgress();
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
    }

    switch (key)
    {
    case KEYCODE_UP:
        selectItem = BACK_ARROW;
        selectNewItem();
        break;

    case KEYCODE_DOWN:
        if (ccBarcodeField.getText() == NULL)
        {
            ccBarcodeField.setNextScan();
        }

        selectItem = (ccQtyField.isFocusable()) ? QTY_FIELD : BC_FIELD;
        selectNewItem();
        break;

    case KEYCODE_HOME:
        doForHomeKey();
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_ENTER:
        if (ccBarcodeField.getText() == NULL)
        {
            return;
        }
        toastBcViewTimer = TOASTVIEW_TIMEOUT;   // Disable barcode toast view timer
        ccToastBarcode.setVisible(false);
        ccToastBarcode.invalidate();

        barcode.assign(ccBarcodeField.getText());
        barcode.copy(bc_r.data, barcode.length());
        bc_r.length = barcode.length();
        bc_r.type = 0x03;
        bc_r_ptr = &bc_r;

        if (quantity > 0)                       // if barcode is ready do
        {
            if(presenter->checkBTPopup())
            {
                showBTPopUp();
                return;
            }

            if (!barcodeBackup.empty())
                barcodeBackup.clear();
            barcodeBackup.push_back(*bc_r_ptr);

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

            presenter->sendBcQty(bc_r_ptr, quantity);
            showQtySubmit(quantity);            // pop QTY view and start timer
            ccBarcodeField.setNextScan();
            ccQtyField.setNextScan();
        }
        else                                    // if barcode is not ready do
        {
            if(presenter->checkBTPopup())
            {
                showBTPopUp();
                return;
            }

            if (ccQtyField.isFocusable())
            {
                recallTimer = RECALL_TIMEOUT;   // skip recall timer become to barcode 1st 
                resetProgress();
                QtyInputTimer = 0;                  // enable qty input timer
                if (ScanQtyProgess == READY_STATE)
                    ScanQtyProgess = BARCODE_1ST;
                selectItem = QTY_FIELD;
                selectNewItem();
            }
            else
            {
                if (!barcodeBackup.empty())
                    barcodeBackup.clear();
                barcodeBackup.push_back(*bc_r_ptr);
                presenter->sendBcQty(bc_r_ptr, 1);
                showQtySubmit(1);            // pop QTY view and start timer
            }
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
        if (ccBarcodeField.isFocusable())
        {
            if (!ccBarcodeField.isEditing())
            {
                ccBarcodeField.setEdit(true);
                toastBcViewTimer = 0;               // Enable Toast view timer
                ccToastBarcode.setVisible(true);
                ccToastBarcode.invalidate();
                resetProgress();
            }
            ccBarcodeField.insStr(presenter->getFnKeyRemapString(key - KEYCODE_F1 + 1));
        }
        break;

    case KEYCODE_RECALL:
        doForRecallKey();
        break;
    }
}

void SnScanAndEntQty_DView::doForRecallKey()
{
    if(presenter->checkBTPopup())
    {
        showBTPopUp();
        return;
    }

    if (recallTimer < RECALL_TIMEOUT)
    {
        recallTimer = RECALL_TIMEOUT;
        bc_r_ptr = &barcodeBackup.back();
        presenter->sendBcQty(bc_r_ptr, 1);
        showQtySubmit(1);            // pop QTY view and start timer
        ccBarcodeField.setNextScan();
        ccQtyField.setNextScan();
    }
    else
    {
        if (ScanQtyProgess != READY_STATE)
        {
            if ((ScanQtyProgess == BARCODE_1ST) && (!ccBarcodeField.isEditing()))
            {
                if (!barcodeBackup.empty())
                    barcodeBackup.clear();
                barcodeBackup.push_back(*bc_r_ptr);
                presenter->sendBcQty(bc_r_ptr, 1);
            }
            gotoReadyState();
        }
        if (barcodeBackup.empty())
            return;
        bc_r_ptr = &barcodeBackup.back();
        ccBarcodeField.setText(NonPrintCharFilter_b(bc_r_ptr));
        // bc_r_ptr = NULL;
        recallTimer = 0;
        
        BcInputTimer = 0;   // Enable barcode input timer, enable timer should after resetProgress()
        toastBcViewTimer = 0;               // Enable Toast view timer
        ccToastBarcode.setVisible(true);
        ccToastBarcode.invalidate();

        ScanQtyProgess = RECALL_KEY;
    }
}

void SnScanAndEntQty_DView::showQtySubmit(uint16_t qty)
{
   if(GenericParamGetInt(sqtyToutConf_attr)!= 0x00)
   {
       QtyViewTimer = 0;
       if (0 == qty)           // Qty input timeout
       {
          textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_01));
          Unicode::snprintf(textQTYBuffer, TEXTQTY_SIZE, "%d", 1);
       } else if (qty < 10)    // Qty is one digit
       {
          textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_1));
          Unicode::snprintf(textQTYBuffer, TEXTQTY_SIZE, "%d", qty);
       } else if (qty < 100)   // Qty is 2 digits
       {
          textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_2));
          Unicode::snprintf(textQTYBuffer, TEXTQTY_SIZE, "%d", qty);
       } else if (qty < 1000)  // Qty is 3 digits
       {
          textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_3));
          Unicode::snprintf(textQTYBuffer, TEXTQTY_SIZE, "%d", qty);
       } else                  // Qty is 4 digits
       {
          textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_4));
          Unicode::snprintf(textQTYBuffer, TEXTQTY_SIZE, "%d", qty);
       }

       ccQTYView.setVisible(true);
       ccQTYView.invalidate();
   }
   else
   {
     gotoReadyState();
   }

   barcode.clear();                 // reset variable
   bc_r_ptr = NULL;
   memset(bc_r.data, 0, sizeof(bc_r.data));
   quantity = 0;
   // recallDataState = 0;
   ccBarcodeField.setNextScan();   // reset barcode field
   ccQtyField.setNextScan();       // reset quantity field
   resetProgress();
}

void SnScanAndEntQty_DView::resetProgress()
{
    QtyInputTimer = QtyInputTimerMax + 1;   // Disable QTY and barcode input timer
    BcInputTimer = QtyInputTimer;
    pgEnterQtyTimer.setValue(0);
    pgEnterQtyTimer.setColor(PRIMARY_BLUE);
    pgEnterQtyTimer.invalidate();
}

void SnScanAndEntQty_DView::gotoReadyState()
{
    barcode.clear();                 // reset variable
    bc_r_ptr = NULL;
    memset(bc_r.data, 0, sizeof(bc_r.data));
    quantity = 0;
    ccBarcodeField.setNextScan();           // reset barcode field
    ccQtyField.setNextScan();               // reset quantity field
    resetProgress();
    QtyViewTimer = QtyView_Timeout;         // Disable QTY view timer
    ccQTYView.setVisible(false);
    ccQTYView.invalidate();
    toastQtyViewTimer = TOASTVIEW_TIMEOUT;  // Disable Qty toast view timer
    ccToastQTY.setVisible(false);
    ccToastQTY.invalidate();
    toastBcViewTimer = TOASTVIEW_TIMEOUT;   // Disable barcode toast view timer
    ccToastBarcode.setVisible(false);
    ccToastBarcode.invalidate();
    selectItem = BC_FIELD;
    selectNewItem();
    ScanQtyProgess = READY_STATE;
}

void SnScanAndEntQty_DView::showBTPopUp(void)
{
    screen_lock = true;
    ccBTPopup.setVisible(true);
    ccQTYView.setVisible(false);
    ccToastBarcode.setVisible(false);
    ccToastQTY.setVisible(false);
    presenter->clearBarcode();
    toastBcViewTimer = TOASTVIEW_TIMEOUT;   // Disable barcode toast view timer
    toastQtyViewTimer = TOASTVIEW_TIMEOUT;  // Disable Qty toast view timer
    QtyViewTimer = QtyView_Timeout;
    QtyInputTimer = QtyInputTimerMax + 1;   // Disable QTY and barcode input timer
    BcInputTimer = QtyInputTimer;

    ccToastQTY.invalidate();
    ccToastBarcode.invalidate();
    ccQTYView.invalidate();
    ccBTPopup.invalidate();
}

void SnScanAndEntQty_DView::doForHomeKey()
{
    presenter->keyPressed(KEYCODE_HOME);
}
