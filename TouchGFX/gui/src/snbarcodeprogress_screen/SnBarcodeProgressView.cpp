#include <gui/snbarcodeprogress_screen/SnBarcodeProgressView.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/ColorPalette.hpp>
#include <gui/common/Barcode.hpp>
#include <gui/common/platform_itf.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

extern uint16_t temp_sendcount;
uint16_t storeQty = 0;
extern int TransmitDecodeDataCompleteFlag;
extern bool manualEditBarcodeFlag;
extern bool bluetooth_batchmode_flag;
invt1 invtrecord1;

SnBarcodeProgressView::SnBarcodeProgressView():
    percentage(0),
    result(0),
    screen_lock(false)
{

}

void SnBarcodeProgressView::setupScreen()
{
    SnBarcodeProgressViewBase::setupScreen();
    presenter->UpdateAllIcons();
    submitview.setVisible(false);
    submitview.invalidate();
    submitviewloc.setVisible(false);
    submitviewloc.invalidate();
    submitviewinvt.setVisible(false);
    submitviewinvt.invalidate();
    confirm_timeout_qty = GenericParamGetInt(sqtyToutConf_attr);
    confirm_timeout_loc = GenericParamGetInt(conflocTout_attr);
    finishBarcodeFlag = false;
}

void SnBarcodeProgressView::tearDownScreen()
{
    SnBarcodeProgressViewBase::tearDownScreen();
}

void SnBarcodeProgressView::handleKeyEvent(uint8_t key)
{
    /* Screen Lock for Pop-up -> Only act on user input */
    if(screen_lock)
    {
        if(key == KEYCODE_ENTER)
        {
            screen_lock = false;
            finishBarcodeFlag = false;
            if( ( presenter->getCurrentScreen() & SCAN_QTY_RESEND_DATA ) == SCAN_QTY_RESEND_DATA)
            {
                #ifdef SCAN_QUANTITY_APP 
                    application().gotoSnScanAndEntQtyScreenNoTransitionEx();
                #endif
            }
            else if( ( presenter->getCurrentScreen() & SCAN_QTY_LOC_DATA ) == SCAN_QTY_LOC_DATA)
            {
                #ifdef SCAN_LOC_APP
                    application().gotoSnScanAndEntLocScreenNoTransition();
                #endif
            }
            else if( ( presenter->getCurrentScreen() & SCAN_INVENTORY_DATA ) == SCAN_INVENTORY_DATA)
            {
                #ifdef SCAN_INVENTORY_APP
                    application().gotoSnScanInventoryScreenNoTransition();
                #endif
            }
        }
        return;
    }

    if (key == KEYCODE_HOME)
    {
        application().gotoSnHomeMenuScreenNoTransition();
    }
}

void SnBarcodeProgressView::handleTickEvent()
{
    if(SubmitTimer)
    {
      uint32_t curtm;
      uint32_t lastrundiffMS;
      bool popup_disable = false;
      curtm = CST_APIGetCanopyTicks();
      if(lastTickMS == 0)
      {
            lastTickMS = curtm;
            lastrundiffMS = 0; 
      }
      else
      {
        lastrundiffMS = abs((int)curtm - (int)lastTickMS);
        popup_disable = Ontimeout(lastrundiffMS);
        if(popup_disable == true)
        {
          lastTickMS = 0;
          curtm = 0;
          lastrundiffMS = 0; 
        }
      }      
    }


    if (!finishBarcodeFlag)
    {
        ProgressionBar();
    }
    else
    {
      endOfBarcodeProgress();
    }
}

void SnBarcodeProgressView::ProgressionBar()
{
  invtrecord1 = presenter->getinvtAppVar();
   bool sendbarcodeEnabledFlag = false;
    if(presenter->checkBTPopup())
    {
        bluetooth_batchmode_flag = 0;
        finishBarcodeFlag = true;
        showBTPopUp();
        return;
    }

    if( ( presenter->getCurrentScreen() & SCAN_QTY_RESEND_DATA)  == SCAN_QTY_RESEND_DATA)                        //Scan and ent qty
    {
      
//#ifdef SCAN_QUANTITY_APP
        if( temp_sendcount || (presenter->getqtyAppFlags()/*sendBarcodeEnabledFlag*/ || manualEditBarcodeFlag))
//#endif
        {
            if(manualEditBarcodeFlag == true)
            {
                progressQty = storeQty;
            }
            else
            {
                progressQty =  storeQty - 1;
            }

            percentage = (temp_sendcount) * 100/(progressQty);
            result = (int)percentage;
            //Value for progress bar movement
            boxProgress1.setValue((result));

            if ((temp_sendcount == (progressQty)) && TransmitDecodeDataCompleteFlag )
            {
                boxProgress1.setValue(result);
                boxProgress1.invalidate();
                temp_sendcount = 0;
                
//                #ifdef SCAN_QUANTITY_APP
//                    sendBarcodeEnabledFlag = false;
//                #endif
                sendbarcodeEnabledFlag = false;
                presenter->setqtyAppFlags(sendbarcodeEnabledFlag);
                finishBarcodeFlag = true;
                manualEditBarcodeFlag = false;
                //QtySubmit(storeQty);
            }
        }
    }
    else if( ( presenter->getCurrentScreen() & SCAN_QTY_LOC_DATA) == SCAN_QTY_LOC_DATA)                   //Scan and ent loc
    {
        if(temp_sendcount)
        {
            percentage = (temp_sendcount) * 100/(storeQty);
            result = (int)percentage;
            boxProgress1.setValue((result));

            if ((temp_sendcount == (storeQty)) && TransmitDecodeDataCompleteFlag)
            {
                boxProgress1.setValue(result);
                boxProgress1.invalidate();
                temp_sendcount = 0;
               // sendBarcodeEnabledFlag = false;   //not required as this is for only scan and quantity app. this particular else will run for scan and location app
                finishBarcodeFlag = true;
                manualEditBarcodeFlag = false;
            }
        }
    }
    else if( ( presenter->getCurrentScreen() & SCAN_INVENTORY_DATA) == SCAN_INVENTORY_DATA)                   //scan invt
    {
        if(presenter->sendcountinvt() > 0)
        {
            percentage = (presenter->sendcountinvt()) * 100/(presenter->sendtotalqtyinvt());
            result = (int)percentage;
            boxProgress1.setValue((result));
        }
        if ((presenter->sendcountinvt() == (presenter->sendtotalqtyinvt())))
        {
            boxProgress1.setValue(100);
            boxProgress1.invalidate();            
//            #ifdef SCAN_INVENTORY_APP
//                finishBarcodeFlaginvt = true;
//            #endif
            invtrecord1.finishBarcodeFlaginvt = true;
            presenter->setinvtAppVar(invtrecord1);
            finishBarcodeFlag = true;
        }
    }
}

void SnBarcodeProgressView::showBTPopUp(void)
{
    screen_lock = true;
    ccBTPopup.setVisible(true);
    ccBTPopup.invalidate();
}

void SnBarcodeProgressView::QtySubmit(uint16_t qty)
{
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
    submitview.setVisible(true);
    submitview.invalidate();
}

void SnBarcodeProgressView::locsubmit(uint16_t quantity)
{
    Unicode::UnicodeChar tempStr[TEXTLOC1_SIZE];
    //#ifdef SCAN_LOC_APP
        int length = (presenter->getlocAppVar()).length();

        if (length < TEXTLOC1_SIZE)
            Unicode::strncpy(tempStr, (presenter->getlocAppVar()).c_str(), TEXTLOC1_SIZE - 1);
        else
        {
            Unicode::strncpy(tempStr, (presenter->getlocAppVar()).c_str() + (length - TEXTLOC1_SIZE + 1), TEXTLOC1_SIZE );
            tempStr[0] = 0x2025;    // show ..
        }
    //#endif

    textLocation1.setTypedText(touchgfx::TypedText(T_LOCVIEW_01));
    Unicode::snprintf(textLOC1Buffer, TEXTLOC1_SIZE, "%s", tempStr);

    if (0 == quantity)          // Qty input timeout 1 submit
    {
        textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_01));
        Unicode::snprintf(textQTY1Buffer, TEXTQTY1_SIZE, "%d", 1);
    } else if (quantity < 10)   // Qty is one digit
    {
        textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_5));
        Unicode::snprintf(textQTY1Buffer, TEXTQTY1_SIZE, "%d", quantity);
    } else if (quantity < 100)  // Qty is 2 digits
    {
        textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_5));
        Unicode::snprintf(textQTY1Buffer, TEXTQTY1_SIZE, "%d", quantity);
    } else if (quantity < 1000) // Qty is 3 digits
    {
        textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_5));
        Unicode::snprintf(textQTY1Buffer, TEXTQTY1_SIZE, "%d", quantity);
    } else                      // Qty is 4 digits
    {
        textNormal.setTypedText(touchgfx::TypedText(T_QTYVIEW_02_5));
        Unicode::snprintf(textQTY1Buffer, TEXTQTY1_SIZE, "%d", quantity);
    }

    submitviewloc.setVisible(true);
    submitviewloc.invalidate();
}

//#ifdef SCAN_INVENTORY_APP
void SnBarcodeProgressView::invtsubmit()
{
  invtrecord1 = presenter->getinvtAppVar();
    if (invtrecord1.temp_loc_list.size() == 1)
    {
        Unicode::UnicodeChar tempStr[TEXTLOC2_SIZE];
        int length = invtrecord1.temp_location.length();
        if (length < TEXTLOC2_SIZE)
            Unicode::strncpy(tempStr, invtrecord1.temp_location.c_str(), TEXTLOC2_SIZE - 1);
        else
        {
            Unicode::strncpy(tempStr, invtrecord1.temp_location.c_str() + (length - TEXTLOC2_SIZE + 1), TEXTLOC2_SIZE - 1);
            tempStr[0] = ELLIPSIS;    // show ..
        }
        Unicode::snprintf(textLoc2Buffer, TEXTLOC2_SIZE, "%s", tempStr);
        textLoc2.setXY(190,38);
        textMoreLoc2.setVisible(false);
        textNormal2.setTypedText(touchgfx::TypedText(T_INVTVIEW_01_1));
    }
    else
    {
        Unicode::UnicodeChar tempStr[TEXTLOC2_SIZE];
        invtrecord1.temp_location.assign(NonPrintCharFilter_l(&invtrecord1.temp_loc_list.front()));
        presenter->setinvtAppVar(invtrecord1);
        int length = invtrecord1.temp_location.length();
        if (length < TEXTLOC2_SIZE)
            Unicode::strncpy(tempStr, invtrecord1.temp_location.c_str(), TEXTLOC2_SIZE - 1);
        else
        {
            Unicode::strncpy(tempStr, invtrecord1.temp_location.c_str() + (length - TEXTLOC2_SIZE + 1), TEXTLOC2_SIZE - 1);
            tempStr[0] = ELLIPSIS;    // show ..
        }
        Unicode::snprintf(textLoc2Buffer, TEXTLOC2_SIZE, "%s", tempStr);
        textLoc2.setXY(52,77);
        Unicode::snprintf(textMoreLoc2Buffer, TEXTMORELOC2_SIZE, "%d", (invtrecord1.temp_loc_list.size() - 1));
        textMoreLoc2.setXY(169,77);
        textMoreLoc2.setVisible(true);
        textNormal2.setTypedText(touchgfx::TypedText(T_INVTVIEW_01_2));
    }
    submitviewinvt.setVisible(true);
    submitviewinvt.invalidate();
}
//#endif

void SnBarcodeProgressView::endOfBarcodeProgress()
{
    if(presenter->checkBTPopup())
    {
        showBTPopUp();
        return;
    }
    if (finishBarcodeFlag == true )
    {      
      if( ( presenter->getCurrentScreen() & SCAN_QTY_RESEND_DATA) == SCAN_QTY_RESEND_DATA)            //scan and ent qty
      {
        if(confirm_timeout_qty != 0x00)
        {
            SubmitTimer = true;
            QtySubmit(storeQty);
        }
        else 
          screenTransition();
      }
      else if( ( presenter->getCurrentScreen() & SCAN_QTY_LOC_DATA) == SCAN_QTY_LOC_DATA)               //scan and ent loc
      {
        if (confirm_timeout_loc != 0x00)
        {
            SubmitTimer = true;
            locsubmit(storeQty);
        }
        else 
          screenTransition();
      }
      else if ( ( presenter->getCurrentScreen() & SCAN_INVENTORY_DATA) == SCAN_INVENTORY_DATA)              //scan invt
        {
            SubmitTimer = true;
            invtsubmit();
        } 
    }
}

void SnBarcodeProgressView::screenTransition()
{
            finishBarcodeFlag = false;
            //QtySubmitTimer = 0;
            if( ( presenter->getCurrentScreen() & SCAN_QTY_RESEND_DATA) == SCAN_QTY_RESEND_DATA)
            {
              #ifdef SCAN_QUANTITY_APP 
                application().gotoSnScanAndEntQtyScreenNoTransitionEx();
              #endif
            }
            else if( ( presenter->getCurrentScreen() & SCAN_QTY_LOC_DATA) == SCAN_QTY_LOC_DATA)
            {
              #ifdef SCAN_LOC_APP
                application().gotoSnScanAndEntLocScreenNoTransition();
              #endif
            }
            else if( ( presenter->getCurrentScreen() & SCAN_INVENTORY_DATA) == SCAN_INVENTORY_DATA)
            {
              #ifdef SCAN_INVENTORY_APP
                application().gotoSnScanInventoryScreenNoTransition();
              #endif
            }
}

void SnBarcodeProgressView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

bool SnBarcodeProgressView::Ontimeout(uint32_t lastrundiffMS)
{
  bool popup_disable = false;
  uint16_t view_timer;
            if ( ( presenter->getCurrentScreen() & SCAN_QTY_RESEND_DATA) == SCAN_QTY_RESEND_DATA)                 //scan qty 
              QtySubmitView_TIMEOUT = confirm_timeout_qty;
            else if ( ( presenter->getCurrentScreen() & SCAN_QTY_LOC_DATA) == SCAN_QTY_LOC_DATA)            //scan loc 
              QtySubmitView_TIMEOUT = confirm_timeout_loc;
            else if ( ( presenter->getCurrentScreen() & SCAN_INVENTORY_DATA) == SCAN_INVENTORY_DATA)            //scan invt
              QtySubmitView_TIMEOUT = 2;
            view_timer = lastrundiffMS/1000;
            if(view_timer >= QtySubmitView_TIMEOUT)
            {
                popup_disable = true;
                view_timer = 0;
                SubmitTimer = false;
                screenTransition();
            }
     return popup_disable;
}

#ifdef UI_CHANGES

#endif
