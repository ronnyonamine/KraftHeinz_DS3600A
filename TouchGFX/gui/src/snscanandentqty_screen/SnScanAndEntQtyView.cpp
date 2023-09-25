#include <gui/snscanandentqty_screen/SnScanAndEntQtyView.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/ColorPalette.hpp>
#include <gui/common/platform_itf.h>

extern uint32_t storeQty;
extern uint32_t sample_multiple_data_size;
extern  uint16_t temp_sendcount;
extern bool manualEditBarcodeFlag;
#define LAUNCH_SCREEN 2

REGISTER_APPLICATION(
    SnScanAndEntQtyView,
    "Scan & Enter Qty",
    TRANSITION_CALLBACK(gotoSnScanAndEntQtyScreenNoTransitionEx),
    LAUNCH_SCREEN - 1
)

/* Manual BC Entry */
REGISTER_DESC_BOOL(seqManBCEditDescr)
REGISTER_PARAMETER(
     seqManBCEdit,
     "Manual BC Entry",
     "Manual BC Entry",
     "Scan & Enter Qty",
     PARAM_TYPE_BOOL,
     0x00,
     1,
     false,
     seqManBCEditDescr,
     0x01,
     1,
     user_cfg_set_barcode_editable_scanqty,
     user_cfg_get_barcode_editable_scanqty)

/* Manual QTY Edit configuration */
REGISTER_DESC_BOOL(seqManQTYEditDescr)
REGISTER_PARAMETER(
     seqManQTYEdit,
     "Manual QTY Entry",
     "Manual QTY Entry",
     "Scan & Enter Qty",
     PARAM_TYPE_BOOL,
     0x00,
     1,
     false,
     seqManQTYEditDescr,
     0x01,
     2,
     user_cfg_set_qty_editable_scanqty,
     user_cfg_get_qty_editable_scanqty)



/* Timeout configuration */
REGISTER_DESC_NUM(seqToutDescr,
                  0,
                  60, 
                  true,
                  true, 
                  "Timeout",
                  NVAL(0x03, 3s),
                  NVAL(0x06,6s (Default)),
                  NVAL(0x09, 9s),
                  NVAL(0x12, 18s),
                  NVAL(0x1E, 30s),
                  NVAL(0x3C, 60s),
                  NVAL(0x00, No Timeout))
REGISTER_PARAMETER(
     seqTout,
     "Quantity Timeout",
     "Quantity Timeout",
     "Scan & Enter Qty",
     PARAM_TYPE_NUMERIC,
     0x00,
      1,
     false,
     seqToutDescr,
     0x06,
     3,
     user_cfg_set_qty_tout_scanqty,
     user_cfg_get_qty_tout_scanqty)
	 
	 /* QTY	QTY Delimiter configuration */
REGISTER_DESC_NUM(sqtyqtyDelimDescr,
				   0,
				   127,
				   true,
				   true,
                   "QTY QTY Delimiter",
                   NVAL(0x0D, CR),
                   NVAL(0x0A, LF),
                   NVAL(0x20, Space),
                   NVAL(0x09, Tab (Default)),
                   NVAL(0x2C, ,),
                   NVAL(0x3A, :),
                   NVAL(0x3B, ;),
                   NVAL(0x3D, =))			   
REGISTER_PARAMETER(
     sqtyqtyDelim,
     "QTY QTY Delimiter",
     "QTY Delimiter",
     "Scan & Enter Qty",	
     PARAM_TYPE_NUMERIC,
     0x888,
     1,
     true,
     sqtyqtyDelimDescr,
     0x09,
	 4,
     user_cfg_set_qty_qty_delimiter,
     user_cfg_get_qty_qty_delimiter)

REGISTER_DESC_NUM(confqtyToutDescr,
		  0,
		  6,
		  true,
		  true,
                  "confirm qty Msg Timeout",
                  NVAL(0x00, 0s),
                  NVAL(0x01, 1s),
                  NVAL(0x02, 2s (Default)),
                  NVAL(0x05, 5s))		   
REGISTER_PARAMETER(
     sqtyToutConf,
     "Confirm QTY Tmout",
     "Confirm QTY Tmout",
     "Scan & Enter Qty",	
     PARAM_TYPE_NUMERIC,
     0x88B,
     1,
     false,
     confqtyToutDescr,
     0x02,
	 5,
     confirm_qty_set_timeout,
     confirm_qty_get_timeout)


enum LocalFields
{
    BACK_ARROW = 0,
    BC_FIELD = 1,
    QTY_FIELD = 2,
};

SnScanAndEntQtyView::SnScanAndEntQtyView() :
//    selectItem(QTY_FIELD),
    selectItem(BC_FIELD),                                                       // change for focus to BC field
    QtySubmitTimer(0),
    cueBcTimer(CUE_TIMEOUT),
    cueQtyTimer(CUE_TIMEOUT),
    QtyInputTimer(0),
    QtyInputTimerMax(0),
    QtyViewTimer(QtyView_Timeout),
    toastQtyViewTimer(TOASTVIEW_TIMEOUT),
    toastBcViewTimer(TOASTVIEW_TIMEOUT),
    BcInputTimer(0),
    BcInputTimerMax(0),
    barcode(NULL),
    quantity(0),
    quantityBackup(0),
    recallProcessState(0),
    recallTimer(RECALL_TIMEOUT),
    BarcodecomeinFlag(false),
    screen_lock(false)
{
    MenuItem[BACK_ARROW] = &ccBack;
    MenuItem[BC_FIELD] = &ccBarcodeField;
    MenuItem[QTY_FIELD] = &ccQtyField;
}

void SnScanAndEntQtyView::setupScreen()
{
    SnScanAndEntQtyViewBase::setupScreen();
    presenter->UpdateAllIcons();
    ccBarcodeField.setFocusable(presenter->getScanQtyBCEditable() == 1);
    ccQtyField.setFocusable(presenter->getScanQtyQtyEditable() == 1);
//    selectItem = (ccQtyField.isFocusable()) ? QTY_FIELD : BACK_ARROW;
//    selectItem = (ccBarcodeField.isFocusable()) ? BC_FIELD : BACK_ARROW;        // change for focus to BC field
    selectItem = BC_FIELD;
    presenter->setCurrentScreen(SCAN_QTY_RESEND_DATA);
    selectNewItem();
    ccToastQTY.setText(0);
    ccToastBarcode.setText(1);
    QtyView_Timeout = GenericParamGetInt(sqtyToutConf_attr)*60;
    QtyViewTimer = QtyView_Timeout;
}

void SnScanAndEntQtyView::tearDownScreen()
{
    SnScanAndEntQtyViewBase::tearDownScreen();
}

//Handles when a key is pressed
void SnScanAndEntQtyView::handleKeyEvent(uint8_t key)
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
        return ;
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

void SnScanAndEntQtyView::handleTickEvent()
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

            if (barcode != NULL)
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

                if (ccBarcodeField.isEditing())
                {   
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
                    presenter->sendBcQty(barcode, quantity);
                    ccBarcodeField.setNextScan();
                    ccQtyField.setNextScan();
                  }
                }
                else if (recallDataState == 1)
                {
                    recallProcessState = 0;
                    recallDataState = 0;
                    presenter->sendBcQty(barcode, quantity);
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
            selectItem = QTY_FIELD;
            selectNewItem();
        }
    }

    if (recallTimer < RECALL_TIMEOUT)
    {
        recallTimer++;
        if (recallTimer == RECALL_TIMEOUT)  // recall timeout
        {
            recallProcessState = 0;
        }
    }
}

//Called when the screen is done with transition/load
void SnScanAndEntQtyView::afterTransition()
{
    QtyInputTimerMax = presenter->getQTYToutValue();
    QtyInputTimer = QtyInputTimerMax + 1;
    BcInputTimerMax = QtyInputTimerMax;
    BcInputTimer = QtyInputTimer;
    if (QtyInputTimerMax > 0)
        pgEnterQtyTimer.setRange(0, QtyInputTimerMax);
    barcode = presenter->getBarcode();
    if (barcode != NULL)
        BarcodeComeIn(barcode);
}

void SnScanAndEntQtyView::selectNewItem()
{
    for (int i = 0; i < MENUITEM_MAX; i++)
    {
        MenuItem[i]->setFocus(selectItem == i);
    }
}

void SnScanAndEntQtyView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnScanAndEntQtyView::BarcodeComeIn(char * BarcodeData)
{
    uint32_t minvalue = 0;
    uint32_t maxvalue = 0;

    recallProcessState = 0;
    
    if(presenter->checkBTPopup())
    {
      showBTPopUp();
      return;
    }

    if(presenter->checkBTPopup())
    {
        showBTPopUp();
        return;
    }

    if (quantity > 0)
    {
        barcode = BarcodeData;
        ccBarcodeField.setText(BarcodeData);    // get barcode data

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
            presenter->clearBarcode();
            return;
        }
        presenter->sendQty(quantity);           // send quantity
        BarcodecomeinFlag = true;
        screenTransitionToProgress();
        presenter->clearBarcode();
        quantityBackup = quantity;
        quantity = 0;                           // reset variable
        barcode = NULL;
        resetProgress();
        cueQtyTimer = 0;                        // set cue timer of Qty come 1st
        ccBarcodeField.setCue();
        ccQtyField.setCue();
        ccSuccessCue.setVisible(true);
        ccSuccessCue.invalidate();
    }
    else
    {
        gotoReadyState();
        barcode = BarcodeData;
        ccBarcodeField.setText(BarcodeData);    // get barcode data
        presenter->clearBarcode();
        MenuItem[0]->setFocus(false);           // Clean back icon focus
        cueBcTimer = 0;                         // set cue timer of barcode come 1st
        ccBarcodeField.setCue();
        ccQtyField.setCue();
        ccSuccessCue.setVisible(true);
        ccSuccessCue.invalidate();
        if (ccQtyField.isFocusable())
        {
            selectItem = QTY_FIELD;
        }
        else
        {
            barcode = NULL;
        }
    }
}

void SnScanAndEntQtyView::doForBack(uint8_t key)
{
    switch (key)
    {
    case KEYCODE_DOWN:
//        selectItem = (ccBarcodeField.isFocusable()) ? BC_FIELD :
//                     ((ccQtyField.isFocusable()) ? QTY_FIELD : BACK_ARROW);
        selectItem = BC_FIELD;
        selectNewItem();
        break;
    case KEYCODE_ENTER:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_RECALL:
        if (ccQtyField.isEditing())
            return;

        selectItem = BC_FIELD;
        selectNewItem();
        resetProgress();
        doForRecallKey();
        break;
    }
}

void SnScanAndEntQtyView::doForQtyInput(uint8_t key)
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
//        selectItem = (ccBarcodeField.isFocusable()) ? BC_FIELD : BACK_ARROW;
        selectItem = BC_FIELD;
        selectNewItem();
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_ENTER:
        quantity = ccQtyField.getNumber();
        resetProgress();
        toastQtyViewTimer = TOASTVIEW_TIMEOUT;  // Disable Qty toast view timer
        ccToastQTY.setVisible(false);
        ccToastQTY.invalidate();
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

        if (barcode != NULL)                    // if barcode is ready do
        {
            if (ccBarcodeField.isEditing()) //barcade is entering
            {
                recallProcessState = 0;
                recallDataState = 0;
                presenter->sendBcQty(barcode, quantity); //TODO: screen transition need to implement for edit barcode Qty
            }
            else
            {
                if (recallDataState == 1)
                {
                    presenter->sendBcQty(barcode, quantity);
                }
                else
                {
                    presenter->sendQty(quantity);
                }
                recallProcessState = 0;
                recallDataState = 0;
           //PE   
            }
            //showQtySubmit(quantity);            // pop QTY view and start timer
            screenTransitionToProgress(); //TODO: screen Transition 
            ccBarcodeField.setNextScan();
            ccQtyField.setNextScan();
        }
        else                                    // if barcode is not ready do
        {
            resetProgress();
            BcInputTimer = 0;                   // enable barcode input timer
            {
                selectItem = BC_FIELD;
                selectNewItem();
            }
        }
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
        if (ccQtyField.isEditing())
            return;

        selectItem = BC_FIELD;
        selectNewItem();
        resetProgress();
        doForRecallKey();
        break;
    }
}

void SnScanAndEntQtyView::doForBarcodeInput(uint8_t key)
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
        if (recallDataState == 1)
            return;

        if (ccBarcodeField.getText() == NULL)
        {
            ccBarcodeField.setNextScan();
        }

        selectItem = (ccQtyField.isFocusable()) ? QTY_FIELD : BC_FIELD;
        selectNewItem();
        break;

    case KEYCODE_ESC:
    case KEYCODE_BACK:
        application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_ENTER:       
        toastBcViewTimer = TOASTVIEW_TIMEOUT;   // Disable barcode toast view timer
        ccToastBarcode.setVisible(false);
        ccToastBarcode.invalidate();
        if (ccBarcodeField.getText() == NULL)
        {
            return;
        }

        barcode = ccBarcodeField.getText();
        if (quantity > 0)                       // if barcode is ready do
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

            recallProcessState = 0;
            recallDataState = 0;
            presenter->sendBcQty(barcode, quantity);
            //showQtySubmit(quantity);            // pop QTY view and start timer
            screenTransitionToProgress();
            ccBarcodeField.setNextScan();
            ccQtyField.setNextScan();
            if (ccQtyField.isFocusable())
            {
                selectItem = QTY_FIELD;
                selectNewItem();
            }
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
                recallTimer = RECALL_TIMEOUT + 1;
                resetProgress();
                QtyInputTimer = 0;                  // enable qty input timer
            }
            else
            {
                presenter->sendBcQty(barcode, 1);
                showQtySubmit(1);            // pop QTY view and start timer
            }
            if (GenericParamGetInt(sqtyToutConf_attr) == 0x00)
            {
              selectItem = (ccQtyField.isFocusable()) ? QTY_FIELD : BC_FIELD;
            }
            else
            {
               selectItem = (ccQtyField.isFocusable()) ? QTY_FIELD : BACK_ARROW;
            }
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
        ccBarcodeField.setNextScan();
        if (ccBarcodeField.isEditing())
            return;
        if (quantity > 0)                       // if barcode is ready do
        {
            resetProgress();
            BcInputTimer = 0;                   // Enable barcode input timer
        }

        doForRecallKey();
        break;
    }
}

void SnScanAndEntQtyView::doForRecallKey()
{
    switch (recallProcessState)
    {
    case 0:
        ccBarcodeField.setNextScan();           // reset barcode field
        recallProcessState = 1;
        recallDataState = 1;
        recallTimer = 0;    // Start recall enter timer
        resetProgress();
        BcInputTimer = 0;   // Enable barcode input timer, enable timer should after resetProgress()
        ccBarcodeField.setText(presenter->getRecallBarcode());    // get barcode data
        barcode = ccBarcodeField.getText();

        //No Data, Return
        if (ccBarcodeField.getText() == NULL)
        {
            recallProcessState = 0;
            recallDataState = 0;
            recallTimer = RECALL_TIMEOUT + 1;
            BcInputTimer = BcInputTimerMax + 1; // Disable barcode input timer
            ccBarcodeField.setNextScan();
            return;
        }
        toastBcViewTimer = 0;               // Enable Toast view timer
        ccToastBarcode.setVisible(true);
        ccToastBarcode.invalidate();
        return;

    case 1:
        recallProcessState = 0;
        recallDataState = 0;
        presenter->sendQty(2);
        showQtySubmit(1);            // pop QTY view and start timer
        selectItem = (ccQtyField.isFocusable()) ? QTY_FIELD : BACK_ARROW;
        selectNewItem();
        return;
    }
}

void SnScanAndEntQtyView::showQtySubmit(uint16_t qty)
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
      //PE
      cQTYView.setVisible(true);
      cQTYView.invalidate();
   }
   else
   {
      gotoReadyState();
   }
  
    barcode = NULL;                 // reset variable
    quantity = 0;
    recallDataState = 0;
    ccBarcodeField.setNextScan();   // reset barcode field
    ccQtyField.setNextScan();       // reset quantity field
    resetProgress();
}

void SnScanAndEntQtyView::resetProgress()
{
    QtyInputTimer = QtyInputTimerMax + 1;   // Disable QTY and barcode input timer
    BcInputTimer = QtyInputTimer;
    pgEnterQtyTimer.setValue(0);
    pgEnterQtyTimer.setColor(PRIMARY_BLUE);
    pgEnterQtyTimer.invalidate();
}

void SnScanAndEntQtyView::gotoReadyState()
{
    barcode = NULL;                         // reset variable
    quantity = 0;
    recallDataState = 0;
    ccBarcodeField.setNextScan();           // reset barcode field
    ccQtyField.setNextScan();               // reset quantity field
    resetProgress();
    QtyViewTimer = QtyView_Timeout;         // Disable QTY view timer
    cQTYView.setVisible(false);
    cQTYView.invalidate();
    toastQtyViewTimer = TOASTVIEW_TIMEOUT;  // Disable Qty toast view timer
    ccToastQTY.setVisible(false);
    ccToastQTY.invalidate();
    toastBcViewTimer = TOASTVIEW_TIMEOUT;   // Disable barcode toast view timer
    ccToastBarcode.setVisible(false);
    ccToastBarcode.invalidate();
    selectItem = BC_FIELD;                                                      //change focus for next scan to BC field
    selectNewItem();
}

void SnScanAndEntQtyView::screenTransitionToProgress() 
{
  bool barcodeFlag = false;
  bool sendQtyEnabledMode = false;
  if (presenter->getQtyTransferMode() == 2)
  {
      sendQtyEnabledMode = true;
  }
    
    if (temp_sendcount > 0 && (presenter->getqtyAppFlags() == false))
    {
        barcodeFlag = true;
        presenter->setqtyAppFlags(barcodeFlag);
    }

    storeQty = quantity;

    if (sample_multiple_data_size*storeQty >= check_value && storeQty>1 && !sendQtyEnabledMode)//&& (sendBarcodeEnabledFlag == true || manualEditBarcodeFlag))
    {   
      application().gotoSnBarcodeProgressScreenNoTransition();
    }
    else
    {
        
        if(manualEditBarcodeFlag == true)
        {
          manualEditBarcodeFlag = false;
        }
        if(presenter->getqtyAppFlags() == true) 
        {
          barcodeFlag = false;
          presenter->setqtyAppFlags(barcodeFlag);
        }
        if(!BarcodecomeinFlag)
        {
          showQtySubmit(storeQty);
        }
        
        else
        {
          BarcodecomeinFlag = false;
          return;
        }
    }
}

void SnScanAndEntQtyView::showBTPopUp(void)
{
    screen_lock = true;
    ccBTPopup.setVisible(true);
    cQTYView.setVisible(false);
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
    cQTYView.invalidate();
    ccBTPopup.invalidate();
}
