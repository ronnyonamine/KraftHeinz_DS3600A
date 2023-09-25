#include <gui/common/FrontendApplication.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <gui/common/ZebraApplication.hpp>
#ifdef SNSCANANDENTQTYPRESENTER_HPP
#include <gui/snscanandentqty_screen/SnScanAndEntQtyView.hpp>
#include <gui/snscanandentqty_screen/SnScanAndEntQtyPresenter.hpp>
#endif
#include <gui/snscreensaver_screen/SnScreensaverView.hpp>
#include <gui/snscreensaver_screen/SnScreensaverPresenter.hpp>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap) :
    FrontendApplicationBase(m, heap),
    transitionCallback(),
    frontendHeap(heap),
    model(m),
    paramIndex(0),
    lastTransition(&FrontendApplication::gotoSnHomeMenuScreenNoTransition)
{
    
}
/*
 * API: FrontendApplication::gotoSnScreenSaverScreenNoTransition 
 * (see header file for details)
 */
void FrontendApplication::gotoSnScreensaverScreenNoTransition()
{   
    transitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoSnScreensaverScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}
/*
 * API: FrontendApplication::gotoSnScreenSaverScreenNoTransitionImpl 
 * (see header file for details)
 */
// SnScanAndEntQty
#ifdef SNSCANANDENTQTYPRESENTER_HPP
void FrontendApplication::gotoSnScanAndEntQtyScreenNoTransitionEx()
{
  //  lastTransition = &FrontendApplication::gotoSnScanAndEntQtyScreenNoTransition;
    if (model.getQtyTransferMode() == BCxQTY)
    {
        FrontendApplicationBase::gotoSnScanAndEntQtyScreenNoTransition();
    }
    else
    {
#ifdef SNSCANANDENTQTY_DPRESENTER_HPP
        FrontendApplicationBase::gotoSnScanAndEntQty_DScreenNoTransition();
#else
        FrontendApplicationBase::gotoSnScanAndEntQtyScreenNoTransition();
#endif
    }
}
#endif
void FrontendApplication::gotoSnScreensaverScreenNoTransitionImpl()
{
    touchgfx::makeTransition<SnScreensaverView, SnScreensaverPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
/*
 * API: FrontendApplication::restoreLastScreen 
 * (see header file for details)
 */
void FrontendApplication::restoreLastScreen()
{
    if(!FrontendApplicationBase::transitionCallback.isValid())
      return;
    FrontendApplicationBase::transitionCallback.execute();
}
/*
 * API: FrontendApplication::saveScreen
 * (see header file for details)
 */
void FrontendApplication::saveScreen(void (FrontendApplication::*pfunc)())
{
  lastScreenCallback = touchgfx::Callback<FrontendApplication>(this, pfunc);
}
/*
 * API: FrontendApplication::restoreScreen 
 * (see header file for details)
 */
void FrontendApplication::restoreScreen()
{
    if(!FrontendApplication::lastScreenCallback.isValid())
      return;
    lastScreenCallback.execute();
}
/*
 * API: FrontendApplication::storeParamIndex 
 * (see header file for details)
 */
void FrontendApplication::storeParamIndex(uint16_t index)
{
  paramIndex = index;
}
/*
 * API: FrontendApplication::retrieveParamIndex 
 * (see header file for details)
 */
uint16_t FrontendApplication::retrieveParamIndex(void)
{
  return paramIndex;
}
/*
 * API: FrontendApplication::storeAppName 
 * (see header file for details)
 */
void FrontendApplication::storeAppName(std::string app)
{
  app_name = app;
}
/*
 * API: FrontendApplication::retrieveAppName 
 * (see header file for details)
 */
std::string FrontendApplication::retrieveAppName(void)
{
  return app_name;
}

void FrontendApplication::setSavedBarcode(std::string barcode)
{
    savedBarcode = barcode;
}

std::string FrontendApplication::getSavedBarcode(void)
{
    return savedBarcode;
}

#ifdef SIMULATOR
/*
 * API: FrontendApplication::gotoSnHomeMenuScreenNoTransition 
 * (see header file for details)
 */
void FrontendApplication::handleKeyEvent(uint8_t c)
{
    static int charge_mode = CHARGE_MODE_OFF;
    static uint8_t battery_val = 0;
    static uint8_t bluetooth_val = BLUETOOTH_DISCONNECT;
    static uint8_t batch_mode = BATCH_MODE_OFF;
    restoreTimer();

    if(triggered_timer)
    {
        /* Simulate inactivity timer triggered */
        uint8_t inactivity_mode = INACTIVITY_OFF;

        uint16_t inactivity_evt = ((STATUS_EVT_INACTIVE << 8) | inactivity_mode);
        CST_APIcbSendBackendStatus(&inactivity_evt);

        triggered_timer = false;
    }

    if(c == 'm')
    {
        // Simulate barcode detection event...
        CST_APIcbSendDataToGUI(NULL);
        return;
    }

    if(c == 'p')
    {
      /*Simulate a charging mode switch */
      if(charge_mode == CHARGE_MODE_OFF)
      {
        charge_mode = CHARGE_MODE_ON;
      }
      else
      {
        charge_mode = CHARGE_MODE_OFF;
      }
      uint16_t charge_evt = ((STATUS_EVT_CHARGE_MODE<<8) | charge_mode);
      CST_APIcbSendBackendStatus(&charge_evt);
      return;
    }

    if( c == 'b')
    {
      /* Simulate a change on the battery status */
      if(battery_val == 0)
      {
        battery_val = 5;
      }
      else
      {
        battery_val--;
      }
      uint16_t gui_bat = ((STATUS_EVT_BATTERY << 8) | battery_val);
      CST_APIcbSendBackendStatus(&gui_bat);
    }
    if( c == 't')
    {
      /* Simulate a change on the blue*T*ooth status */
      if(bluetooth_val == BLUETOOTH_DISCONNECT)
      {
        bluetooth_val = BLUETOOTH_CONNECT;
      }
      else
      {
        bluetooth_val = BLUETOOTH_DISCONNECT;
      }
      /* Simulate a change in the blue*T*ooth connection */
      uint16_t gui_bt = ((STATUS_EVT_BLUETOOTH<<8) | bluetooth_val);
      CST_APIcbSendBackendStatus(&gui_bt);
    }

    if( c == 'n')
    {
      /* Simulate a change on the blue*T*ooth status */
      if(batch_mode == BATCH_MODE_OFF)
      {
        batch_mode = BATCH_MODE_ON;
      }
      else
      {
        batch_mode = BATCH_MODE_OFF;
      }
      /* Simulate a change in the blue*T*ooth connection */
      uint16_t gui_batch = ((STATUS_EVT_BATCH_MODE<<8) | batch_mode);
      CST_APIcbSendBackendStatus(&gui_batch);
    }
    // Process the key input into the keypad simulator...
    std::pair<key_output_t, unsigned char> keypad_output = keypad.process_input(c);

    if(OUTPUT_ERROR == keypad_output.first)
    {
        // State machine returned an error
        return;
    }
    if(OUTPUT_SPECIAL == keypad_output.first)
    {
        // Pressed special character. Update UI only
        if((keypad_output.second == KEYCODE_GREEN) || (keypad_output.second == KEYCODE_BLUE))
        {
            keycodeMapping(keypad_output.second);
        }
        // Pressed remaining special buttons... do not update UI
        touchgfx::MVPApplication::handleKeyEvent(keypad_output.second);
		return;
    }
    if(OUTPUT_ALPHANUMERIC == keypad_output.first)
    {
        touchgfx::MVPApplication::handleKeyEvent(keypad_output.second);
    }
    if(OUTPUT_ALPHANUMERIC_REPLACE == keypad_output.first)
    {
        touchgfx::MVPApplication::handleKeyEvent(KEYCODE_BKSP);
        touchgfx::MVPApplication::handleKeyEvent(keypad_output.second);

    }
    if(OUTPUT_ACTION == keypad_output.first)
    {
        touchgfx::MVPApplication::handleKeyEvent(keypad_output.second);
    }
}
#endif