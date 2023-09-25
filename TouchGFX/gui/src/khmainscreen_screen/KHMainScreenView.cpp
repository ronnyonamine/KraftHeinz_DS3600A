#include <gui/khmainscreen_screen/KHMainScreenView.hpp>
#include <texts/TextKeysAndLanguages.hpp> // Manual Edit
#include <gui/common/platform_itf.h> // Manual Edit
#include <gui/common/ZebraApplication.hpp> // Manual Edit
#include <touchgfx/Color.hpp> // Manual Edit
#include <gui/common/ConfigParam.hpp> // Manual Edit
#include <iostream>
#include <ctime>

REGISTER_APPLICATION(
    KHMainScreenView,
    "Kraft Heinz",
    TRANSITION_CALLBACK(gotoKHMainScreenScreenNoTransition),
    255
)

KHMainScreenView::KHMainScreenView()
{
    step = 0;
    testCounter = 0;
    sendingData = false;
    toastViewTimer = TOASTVIEW_TIMEOUT;
    cueBcTimer = CUE_TIMEOUT;
    
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
}

void KHMainScreenView::setupScreen()
{
    KHMainScreenViewBase::setupScreen();

    // get last barcode. It is stored as F1 in function keys!
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
      savedBarcode = strVal;
    }
    
    // use last barcode from NVRAM
    if (savedBarcode.length() == 0)
    {
        savedBarcode = "";
    }
    barcodeLearn.setText((char*)savedBarcode.c_str());
    barcodeMatch.setText((char*)savedBarcode.c_str());
    learnbarcode = savedBarcode;

    presenter->UpdateAllIcons();
}

void KHMainScreenView::tearDownScreen()
{
    KHMainScreenViewBase::tearDownScreen();
}


void KHMainScreenView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)  // Manual Edit
{  
    statusBar1.UpdateIcon(IconId, IconState);  
}  

void KHMainScreenView::hideAll(void)
{
    khSendData1.setVisible(false);
    khSendData1.invalidate();
    khViewData1.setVisible(false);
    khViewData1.invalidate();
    khMenu1.setVisible(false);
    khMenu1.invalidate();
    khEnterOperator1.setVisible(false);
    khEnterOperator1.invalidate();
    khErrorReason1.setVisible(false);
    khErrorReason1.invalidate();
    khSuccess1.setVisible(false);
    khSuccess1.invalidate();
    khError1.setVisible(false);
    khError1.invalidate();
    khLearnBarcode1.setVisible(false);
    khLearnBarcode1.invalidate();
    khVerifyBarcode1.setVisible(false);
    khVerifyBarcode1.invalidate();
    barcodeLearn.setVisible(false);
    barcodeLearn.invalidate();
    barcodeVerify.setVisible(false);
    barcodeVerify.invalidate();
    barcodeMatch.setVisible(false);
    barcodeMatch.invalidate();
    locationField_Loc1.setVisible(false);
    locationField_Loc1.invalidate();
    textTitle1.setVisible(false);
    textTitle1.invalidate();
    textTitle2.setVisible(false);
    textTitle2.invalidate();
    textTitle3.setVisible(false);
    textTitle3.invalidate();
    textTitle4.setVisible(false);
    textTitle4.invalidate();
    textTitle5.setVisible(false);
    textTitle5.invalidate();
    textTitle6.setVisible(false);
    textTitle6.invalidate();
    textTitle7.setVisible(false);
    textTitle7.invalidate();
    textTitle8.setVisible(false);
    textTitle8.invalidate();
    textTitle9.setVisible(false);
    textTitle9.invalidate();
    textTitle10.setVisible(false);
    textTitle10.invalidate();
    textRightYes.setVisible(false);
    textRightYes.invalidate();
    textRightBack.setVisible(false);
    textRightBack.invalidate();
    textRightMenu.setVisible(false);
    textRightMenu.invalidate();
    textRightOk.setVisible(false);
    textRightOk.invalidate();
    textLeftNo.setVisible(false);
    textLeftNo.invalidate();
    textLeftExit.setVisible(false);
    textLeftExit.invalidate();
    textLeftBack.setVisible(false);
    textLeftBack.invalidate();
    textLeftContinue.setVisible(false);
    textLeftContinue.invalidate();
    khBottomBar1.hideDot();
    khSplashScreen1.setVisible(false);
    khSplashScreen1.invalidate();
    khSendData11.setVisible(false);
    khSendData11.invalidate();
    textClearData.setVisible(false);
    textClearData.invalidate();
}

//Handles when a key is pressed
//remap KEYCODE_GREEN and KEYCODE_BLUE to KEYCODE_LEFT and KEYCODE_RIGHT
void KHMainScreenView::handleKeyEvent(uint8_t key)
{
    uint8_t rValue = 0;
    presenter->keyPressed(key);
    if (step == 0)
    {
        //handle exit key (abc)
        if (key == KEYCODE_LEFT)
        {
            application().gotoSnHomeMenuScreenNoTransition();
            return;
        }
        if (key == KEYCODE_RIGHT)
        {
            step = 1;
            hideAll();
            textRightOk.setVisible(true);
            textRightOk.invalidate();
            khLearnBarcode1.setVisible(true);
            khLearnBarcode1.invalidate();
            barcodeLearn.setVisible(true);
            barcodeLearn.invalidate();
            textTitle2.setVisible(true);
            textTitle2.invalidate();
            return;
        }
    }
    if ((step == 1) && (key == KEYCODE_RIGHT))
    {
        step = 2;
        hideAll();
        khVerifyBarcode1.setVisible(true);
        khVerifyBarcode1.invalidate();
        barcodeVerify.setVisible(true);
        barcodeVerify.invalidate();
        barcodeMatch.setVisible(true);
        barcodeMatch.invalidate();
        textTitle3.setVisible(true);
        textTitle3.invalidate();
        textRightMenu.setVisible(true);
        textRightMenu.invalidate();
        //save last barcode in NVRAM
        //presenter->storeParamValue(0, (uint8_t*)learnbarcode.c_str(), learnbarcode.length() + 1);
        if (learnbarcode.length() == 0)
        {
          /* No text -> Un assign */
          rValue = Unassigned;
          char empty[] = "";
          presenter->storeParamValue(radioIdx, &rValue, 1);
          /* For completeness, also clear the string parameter */
          presenter->storeParamValue(stringIdx, (uint8_t*)empty, 1);
        }
        else
        {
          /* Custom String */
          rValue = Custom_String;
          presenter->storeParamValue(radioIdx, &rValue, 1);
          /* For completeness, also clear the string parameter */
          presenter->storeParamValue(stringIdx, (uint8_t*)learnbarcode.c_str(), learnbarcode.length() + 1);
        }        
        return;
    }
    if ((step == 2) && (key == KEYCODE_RIGHT))
    {
        step = 7;
        hideAll();
        khMenu1.setVisible(true);
        khMenu1.invalidate();
        textTitle8.setVisible(true);
        textTitle8.invalidate();
        textRightBack.setVisible(true);
        textRightBack.invalidate();
        khBottomBar1.showDot();
        return;
    }
    if ((step == 3) && ((key == KEYCODE_RIGHT) || (key == KEYCODE_LEFT)))
    {
        presenter->addDataRecord(verifydate, verifytime, learnbarcode, verifybarcode, " Y"); 
        recordcount++;
        step = 2;
        hideAll();
        barcodeVerify.setNextScan();
        khVerifyBarcode1.setVisible(true);
        khVerifyBarcode1.invalidate();
        barcodeVerify.setVisible(true);
        barcodeVerify.invalidate();
        barcodeMatch.setVisible(true);
        barcodeMatch.invalidate();
        textTitle2.setVisible(true);
        textTitle2.invalidate();
        textRightMenu.setVisible(true);
        textRightMenu.invalidate();
        return;
    }
    if ((step == 4) && ((key == KEYCODE_RIGHT) || (key == KEYCODE_LEFT)))
    {
        presenter->addDataRecord(verifydate, verifytime, learnbarcode, verifybarcode, " N"); // capital W does not work nor does any B
        recordcount++;
        step++;
        hideAll();
        khErrorReason1.setVisible(true);
        khErrorReason1.invalidate();
        textTitle6.setVisible(true);
        textTitle6.invalidate();
        return;
    }
    if (step == 5) // error reason
    {
        khErrorReason1.handleKeyEvent(key);
    }
    if (step == 6) // initials
    {
        doForLocationInput(key);
        if (key == KEYCODE_RIGHT)
        {
            if (locationField_Loc1.getText() == NULL)
            {
                userinitials = "";
                return;
            }
            else
            {
                userinitials = locationField_Loc1.getText();
            }
            presenter->updateDataRecordError(errorreason, userinitials);
            step = 2;
            hideAll();
            textTitle2.setVisible(true);
            textTitle2.invalidate();
            barcodeVerify.setNextScan();
            khVerifyBarcode1.setVisible(true);
            khVerifyBarcode1.invalidate();
            barcodeVerify.setVisible(true);
            barcodeVerify.invalidate();
            barcodeMatch.setVisible(true);
            barcodeMatch.invalidate();
            textRightMenu.setVisible(true);
            textRightMenu.invalidate();
            return;
        }
        return;
    }
    if (step == 7) // menu
    {
        khMenu1.handleKeyEvent(key);
        if (key == KEYCODE_RIGHT)
        {
            step = 2;
            hideAll();
            khVerifyBarcode1.setVisible(true);
            khVerifyBarcode1.invalidate();
            barcodeVerify.setVisible(true);
            barcodeVerify.invalidate();
            barcodeMatch.setVisible(true);
            barcodeMatch.invalidate();
            textTitle3.setVisible(true);
            textTitle3.invalidate();
            textRightMenu.setVisible(true);
            textRightMenu.invalidate();
            return;
        }
    }
    if (step == 8) // view data
    {     
        if ((key == KEYCODE_LEFT) && (khViewData1.horizontalScrollIndex == 0))
        {
            step = 7;
            hideAll();
            khMenu1.setVisible(true);
            khMenu1.invalidate();
            textTitle8.setVisible(true);
            textTitle8.invalidate();
            khBottomBar1.showDot();
            return;
        }
        khViewData1.handleKeyEvent(key);
    }
    if ((step == 9) && (!sendingData))
    {
        if (key == KEYCODE_LEFT) //no
        {
            step = 7;
            hideAll();
            khMenu1.setVisible(true);
            khMenu1.invalidate();
            textTitle8.setVisible(true);
            textTitle8.invalidate();
            khBottomBar1.showDot();
            return;
        }
        if (key == KEYCODE_RIGHT) //yes
        {
            textLeftNo.setVisible(false);
            textLeftNo.invalidate();
            textRightYes.setVisible(false);
            textRightYes.invalidate();
            khSendData1.sendActivate();
            sendingData = true;
            sendingDataIndex = 0;
            return;
        }
    }
    if (step == 10)
    {
        if (key == KEYCODE_LEFT) //back
        {
            step = 7;
            hideAll();
            khMenu1.setVisible(true);
            khMenu1.invalidate();
            textTitle8.setVisible(true);
            textTitle8.invalidate();
            khBottomBar1.showDot();
            return;
        }
        if (key == KEYCODE_RIGHT) //yes
        {
            clearData();
            textClearData.setVisible(false);
            textClearData.invalidate();
            return;
        }
    }
    

    if (key == KEYCODE_ENTER)
    {
        // step 1 - learn barcode
        // step 2 - verify barcode
        // step 3 - success
        // step 4 - failure
        // step 5 - reason
        // step 6 - initials
        // step 7 - menu
        // step 8 - view data
        // step 9 - send data
        switch (step)
        {
        case 0:
            step = 1;
            hideAll();
            textRightOk.setVisible(true);
            textRightOk.invalidate();
            khLearnBarcode1.setVisible(true);
            khLearnBarcode1.invalidate();
            barcodeLearn.setVisible(true);
            barcodeLearn.invalidate();
            textTitle2.setVisible(true);
            textTitle2.invalidate();
            break;
        case 1: // step 1 - learn barcode
            step = 2;
            hideAll();
            khVerifyBarcode1.setVisible(true);
            khVerifyBarcode1.invalidate();
            barcodeVerify.setVisible(true);
            barcodeVerify.invalidate();
            barcodeMatch.setVisible(true);
            barcodeMatch.invalidate();
            textTitle3.setVisible(true);
            textTitle3.invalidate();
            textRightMenu.setVisible(true);
            textRightMenu.invalidate();
            break;
        case 2: // step 2 - verify barcode
            hideAll();

            if (learnbarcode == verifybarcode)
            {
                step = 3;
                khSuccess1.setVisible(true);
                khSuccess1.invalidate();
                textTitle4.setVisible(true);
                textTitle4.invalidate();
                textRightOk.setVisible(true);
                textRightOk.invalidate();
                textLeftContinue.setVisible(true);
                textLeftContinue.invalidate();
            }
            else
            {
                step = 4;
                khError1.setVisible(true);
                khError1.invalidate();
                textTitle5.setVisible(true);
                textTitle5.invalidate();
                textRightOk.setVisible(true);
                textRightOk.invalidate();
                textLeftContinue.setVisible(true);
                textLeftContinue.invalidate();
            }
            break;
        case 3: // step 3 - success
            presenter->addDataRecord(verifydate, verifytime, learnbarcode, verifybarcode, " Y"); // capital W does not work nor does any B
            recordcount++;
            step = 2;
            hideAll();
            barcodeVerify.setNextScan();
            khVerifyBarcode1.setVisible(true);
            khVerifyBarcode1.invalidate();
            barcodeVerify.setVisible(true);
            barcodeVerify.invalidate();
            barcodeMatch.setVisible(true);
            barcodeMatch.invalidate();
            textTitle2.setVisible(true);
            textTitle2.invalidate();
            textRightMenu.setVisible(true);
            textRightMenu.invalidate();
            break;
        case 4: // step 4 - failure
            presenter->addDataRecord(verifydate, verifytime, learnbarcode, verifybarcode, " N"); // capital W does not work nor does any B
            recordcount++;
            step++;
            hideAll();
            khErrorReason1.setVisible(true);
            khErrorReason1.invalidate();
            textTitle6.setVisible(true);
            textTitle6.invalidate();
            break;
        case 5: // step 5 - reason
            step++;
            if (khErrorReason1.getSelection() == 0)
            {
                errorreason = "Wrong label brought to line";
            }
            else if (khErrorReason1.getSelection() == 1)
            {
                errorreason = "Forgot to re-teach unit";
            }
            else if (khErrorReason1.getSelection() == 2)
            {
                errorreason = "Vendor issue";
            }
            else if (khErrorReason1.getSelection() == 3)
            {
                errorreason = "Other";
            }
            else
            {
                errorreason = "";
            }
            hideAll();
            khEnterOperator1.setVisible(true);
            khEnterOperator1.invalidate();
            locationField_Loc1.setVisible(true);
            locationField_Loc1.invalidate();
            textTitle7.setVisible(true);
            textTitle7.invalidate();
            textRightOk.setVisible(true);
            textRightOk.invalidate();
            break;
        case 6: // step 6 - initials
            if (locationField_Loc1.getText() == NULL)
            {
                userinitials = "";
                break;
            }
            else
            {
                userinitials = locationField_Loc1.getText();
            }
            presenter->updateDataRecordError(errorreason, userinitials); 
            step = 2;
            hideAll();
            textTitle2.setVisible(true);
            textTitle2.invalidate();
            barcodeVerify.setNextScan();
            khVerifyBarcode1.setVisible(true);
            khVerifyBarcode1.invalidate();
            barcodeVerify.setVisible(true);
            barcodeVerify.invalidate();
            barcodeMatch.setVisible(true);
            barcodeMatch.invalidate();
            textRightMenu.setVisible(true);
            textRightMenu.invalidate();
            break;
        case 7: // step 7 - menu
            step = 8;
            hideAll();
            if (khMenu1.getSelection() == 0)
            {
                step = 1;
                hideAll();
                barcodeVerify.setNextScan();
                khLearnBarcode1.setVisible(true);
                khLearnBarcode1.invalidate();
                barcodeLearn.setVisible(true);
                barcodeLearn.invalidate();
                textTitle2.setVisible(true);
                textTitle2.invalidate();
                textRightOk.setVisible(true);
                textRightOk.invalidate();
            }
            if (khMenu1.getSelection() == 1)
            {
                step = 8;
                hideAll();
                khViewData1.setVisible(true);
                khViewData1.invalidate();
                textTitle9.setVisible(true);
                textTitle9.invalidate();
                textLeftBack.setVisible(true);
                textLeftBack.invalidate();
                khBottomBar1.showDot();

                khViewData1.clearData();
                for (int i = 0; i < presenter->getDataRecordCount(); i++)
                {
                    khViewData1.addDataRow(presenter->getDataRecord(i));
                }
            }
            if (khMenu1.getSelection() == 2)
            {
                step = 9;
                hideAll();
                khBottomBar1.showDot();
                khSendData1.setVisible(true);
                khSendData1.invalidate();
                textTitle10.setVisible(true);
                textTitle10.invalidate();
                textLeftNo.setVisible(true);
                textLeftNo.invalidate();
                textRightYes.setVisible(true);
                textRightYes.invalidate();
            }
            if (khMenu1.getSelection() == 3)
            {
                step = 1;
                hideAll();
                application().gotoSnHomeMenuScreenNoTransition();                
            }
            break;
        case 8: // step 8 - view data
            step = 7;
            hideAll();
            khMenu1.setVisible(true);
            khMenu1.invalidate();
            textTitle8.setVisible(true);
            textTitle8.invalidate();
            khBottomBar1.showDot();
            break;
        case 9: // step 9 - send data
            break;
        default:
            step++;
        }
        // next screen here.
    }
}

void KHMainScreenView::BarcodeComeIn(char* BarcodeData)
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
    std::string datePart(buffer);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    std::string timePart(buffer);

    bc_r_ptr = (BarcodeRecord_t*)((void*)BarcodeData);
    barcode.assign(NonPrintCharFilter_b(bc_r_ptr));
    presenter->clearBarcode();

    switch (step)
    {
    case 1:
        learnbarcode = BarcodeData;
#ifndef _VS2022
        barcodeLearn.setText(NonPrintCharFilter_b(bc_r_ptr));// is this right?
        barcodeMatch.setText(NonPrintCharFilter_b(bc_r_ptr));// is this right?
#else
        barcodeLearn.setText(BarcodeData);
        barcodeMatch.setText(BarcodeData);
#endif
        barcodeLearn.invalidate();
        barcodeMatch.invalidate();
        barcodeVerify.setNextScan();
        break;
    case 2:
        cueBcTimer = 0;
        verifybarcode = BarcodeData;
        verifydate = datePart;
        verifytime = timePart;
#ifndef _VS2022
        barcodeVerify.setText(NonPrintCharFilter_b(bc_r_ptr));
#else
        barcodeVerify.setText(BarcodeData);
#endif      
        barcodeVerify.invalidate();
        //barcodeVerify.setNextScan();
        break;
    }
}

void KHMainScreenView::handleTickEvent()
{
    if (sendingData)
    {
        testCounter++;
        if ((testCounter % 60) == 0)
        {
            khSendData1.sendIncrement();
            if (SendingData() == 0)
            {
                khSendData1.sendDeactivate();
                textLeftNo.setVisible(false);
                textLeftNo.invalidate();
                textRightYes.setVisible(false);
                textRightYes.invalidate();
                textLeftBack.setVisible(true);
                textLeftBack.invalidate();
                sendingData = false;
                testCounter = 0;
            }
        }
    }

    if (cueBcTimer < CUE_TIMEOUT)
    {
        cueBcTimer++;
        if (cueBcTimer == CUE_TIMEOUT)
        {
            handleKeyEvent(KEYCODE_ENTER);
            //ccSuccessCue.setVisible(false);
            //ccSuccessCue.invalidate();
            //acceptBarcode();
        }
    }

    if (toastViewTimer < TOASTVIEW_TIMEOUT)
    {
        toastViewTimer++;
        if (toastViewTimer == TOASTVIEW_TIMEOUT)    // toast view timeout
        {
            //ccToastBatchOn.setVisible(false);
            //ccToastBatchOn.invalidate();
            //ccToastExitList.setVisible(false);
            //ccToastExitList.invalidate();
        }
    }
}

void KHMainScreenView::afterTransition()
{
    step = 0;
    hideAll();
    khSplashScreen1.setVisible(true);
    khSplashScreen1.invalidate();
    textTitle1.setVisible(true);
    textTitle1.invalidate();
    textLeftExit.setVisible(true);
    textLeftExit.invalidate();
    textRightOk.setVisible(true);
    textRightOk.invalidate();

    locationField_Loc1.setEditable(true);
    // clear barcode buffer when into this screen
    while (presenter->getBarcode() != NULL)
    {
        presenter->clearBarcode();
    }
    khMenu1.invalidate();
}

void KHMainScreenView::doForLocationInput(uint8_t key)
{
    if ((key >= 0x20) && (key <= 0x7E))
    {
        if (!locationField_Loc1.isEditing())
        {
            locationField_Loc1.setEdit(true);
        }
        if ((key > 96) && (key < 123))
        {
            key = key - 32;
        }
        locationField_Loc1.insCh(key);
        return;
    }

    if ((key >= 0x81) && (key <= 0xDF))     // for multi tap
    {
        if (!locationField_Loc1.isEditing())
            return;
        locationField_Loc1.modifyCh(~(key));
        return;
    }

    switch (key)
    {
    case KEYCODE_UP:
        //selectItem = 0;
        //selectNewItem();
        break;

    case KEYCODE_DOWN:
        if (locationField_Loc1.getText() == NULL)
        {
            return;
        }
        else
        {
            //location.assign(ccLocationField.getText());
            //location.copy(loc_r.data, location.length());
            //loc_r.length = location.length();
            //loc_r_ptr = &loc_r;
            //selectItem = 2;
            //selectNewItem();
        }
        break;

        //case KEYCODE_ESC:
    case KEYCODE_BACK:
        //application().gotoSnHomeMenuScreenNoTransition();
        break;

    case KEYCODE_ENTER:
        if (locationField_Loc1.getText() == NULL)  //APP can enter empty location data
        {
            userinitials = "";
        }
        else
        {
            userinitials = locationField_Loc1.getText();
        }

        break;

    case KEYCODE_LEFT:
        if (!locationField_Loc1.isEditing())
            return;
        locationField_Loc1.moveCursorLeft();
        break;

    case KEYCODE_RIGHT:
        if (!locationField_Loc1.isEditing())
            return;
        locationField_Loc1.moveCursorRight();
        break;

    case KEYCODE_BKSP:
        if (!locationField_Loc1.isEditing())
            return;
        locationField_Loc1.delCh();
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
        if (!locationField_Loc1.isEditing())
        {
            locationField_Loc1.setEdit(true);
        }
        locationField_Loc1.insStr(NULL);// presenter->getFnKeyRemapString(key - KEYCODE_F1 + 1));
        break;

    case KEYCODE_ESC:
        if (!locationField_Loc1.isEditing())
            return;
        locationField_Loc1.setNextScan();
        break;
    }
}

void KHMainScreenView::sendData()
{
    DataRecord dr;
    char tempStr[100];
    for (int i = 0; i < presenter->getDataRecordCount(); i++)
    {
        dr = presenter->getDataRecord(i);
        snprintf(tempStr, 99, "%s\t%s\t%s\t%s\t%s\t%s\t%s",dr.date.c_str(),dr.time.c_str(),dr.learnBarcode.c_str(),dr.verifyBarcode.c_str(),dr.success.c_str(),dr.reason.c_str(),dr.initials.c_str());
        presenter->sendDataQty(tempStr, 1);
        //send tempStr to serial interface
    }
    clearData();
    recordcount = 0;
}

int KHMainScreenView::SendingData()
{
    DataRecord dr;
    char tempStr[100];
    if (sendingDataIndex < presenter->getDataRecordCount())
    {
        dr = presenter->getDataRecord(sendingDataIndex);
        snprintf(tempStr, 99, "%s\t%s\t%s\t%s\t%s\t%s\t%s", dr.date.c_str(), dr.time.c_str(), dr.learnBarcode.c_str(), dr.verifyBarcode.c_str(), dr.success.c_str(), dr.reason.c_str(), dr.initials.c_str());
        presenter->sendDataQty(tempStr, 1);
        //send tempStr to serial interface
        sendingDataIndex++;
        return 1;
    }
    else
    {
        //clearData();
        hideAll();
        khSendData11.setVisible(true);
        khSendData11.invalidate();
        textClearData.setVisible(true);
        textClearData.invalidate();
        textLeftBack.setVisible(true);
        textLeftBack.invalidate();
        step = 10;
        recordcount = 0;
        sendingDataIndex = 0;
        sendingData = false;
        return 0;
    }
}

void KHMainScreenView::clearData()
{
    presenter->clearDataRecords();
}