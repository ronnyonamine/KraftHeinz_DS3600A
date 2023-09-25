#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>
#include <gui/simulator/KeypadHandlerSim.hpp>
#include <string>

#define TIMEOUT 60*60

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    /**
    * @brief FrontendApplication constructor
    *
    * @param m MVC Model
    * @param heap FrontendHeap object
    */
    FrontendApplication(Model& m, FrontendHeap& heap);
    /**
    * @brief Redeclaration of a pointer to FrontendApplication
    * method.
    */
    typedef void (FrontendApplicationBase::*transition_t)();
    /**
    * @brief FrontendApplication destructor.
    */
    virtual ~FrontendApplication()
    { 

    }
    /**
    * @brief Stores the transition callback
    *
    * @param pfunc pointer to FrontendApplication method.
    */
    void saveScreen(void (FrontendApplication::*pfunc)());
    /**
    * @brief Executes the pointer to FrontendApplication method
    * stored by saveScreen()
    */
    void restoreScreen();
    /**
    * @brief Stores the parameter index from the screen which it was called
    *
    * @param index Array index of the parameter
    */
    void storeParamIndex(uint16_t index);
    /**
    * @brief Returns the parameter index stored from storeParamIndex()
    *
    * @retval Array index of the parameter
    */
    uint16_t retrieveParamIndex(void);
    /**
    * @brief Stores the application name from the screen which it was called
    *
    * @param app Application name (string)
    */
    void storeAppName(std::string app);
    /**
    * @brief Returns the application name stored from storeAppName() 
    * method
    *
    * @retval Application name (string)
    */
    std::string retrieveAppName(void);
    /**
    * @brief Method executed each 1/60th of a second. Used to generate
    * time measurement units.
    */
    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();

        /** 
        * When the simulator is running, this method also implements
        * the logic to display screensaver on timeout and other stuff...
        */
#ifdef SIMULATOR
        timer++;
        keypad.increase_tick();
        
        if(timer == TIMEOUT)
        {
            /* Simulate inactivity timer triggered */
            uint8_t inactivity_mode = INACTIVITY_ON;

            uint16_t inactivity_evt = ((STATUS_EVT_INACTIVE << 8) | inactivity_mode);
            CST_APIcbSendBackendStatus(&inactivity_evt);
            triggered_timer = true;

            return;
        }
#endif
    }
    /**
    * @brief Transitions to the screensaver screen
    */
    void gotoSnScreensaverScreenNoTransition();
    /**
    * @brief Transitions back to the last screen from where the
    * last transition was called
    */
	// SnScanAndEntQty
//#ifdef SNSCANANDENTQTYPRESENTER_HPP
   void gotoSnScanAndEntQtyScreenNoTransitionEx();
//#endif
    // SnScanAndEntQty_D
//#ifdef SNSCANANDENTQTY_DPRESENTER_HPP
//    void gotoSnScanAndEntQty_DScreenNoTransition();
//#endif

    void restoreLastScreen();

    std::string getSavedBarcode();

    void setSavedBarcode(std::string barcode);

protected:
    /**
    * @brief Implicit callback for Screensaver transition
    */
    void gotoSnScreensaverScreenNoTransitionImpl();
    /**
    * @brief Callback member that contains the routine to transition
    * the next screen.
    */
    touchgfx::Callback<FrontendApplication> transitionCallback;
    /**
    * @brief Callback member that contains the routine to transition
    * to the last screen from where the last transition was called.
    */
    touchgfx::Callback<FrontendApplication> lastScreenCallback;
    /**
    * @brief Memory manager for all the screens.
    */
    FrontendHeap& frontendHeap;
    /**
    * @brief MVC Model member
    */
    Model& model;
	// SnScanAndEntQty
//#ifdef SNSCANANDENTQTYPRESENTER_HPP
//    void gotoSnScanAndEntQtyScreenNoTransitionImpl();
//#endif
    // SnScanAndEntQty_D
//#ifdef SNSCANANDENTQTY_DPRESENTER_HPP
//    void gotoSnScanAndEntQty_DScreenNoTransitionImpl();
//#endif
    /**
    * @brief Member used to store the TBD
    */
    uint16_t paramIndex;
    /**
    * @brief Member used to store the application name from where
    * the transition was called.
    */
    std::string app_name;
    std::string savedBarcode;
    transition_t lastTransition = &FrontendApplicationBase::gotoSnHomeMenuScreenNoTransition;
#ifdef SIMULATOR
    /**
    * Static callback called when a key is pressed. This approach
    * works only when the simulator is running, and it sends events
    * to the screen views for each keypress.
    *
    * @param c ASCII code for the key pressed
    */
    void handleKeyEvent(uint8_t c);

private:

    /**
    * @brief KeypadHandler used to capture keypresses from PC
    * keyboard.
    */
    KeypadHandlerSim keypad;
    /**
    * @brief Base time measurement unit. Used mainly to trigger
    * a timeout, therefore, a screensaver.
    */
    uint32_t timer = 0;
    /**
    * @brief Indicates whether the simulator should trigger the 
    * screensaver.
    */
    bool triggered_timer = false;
    /**
    * @brief Resets the screensaver timeout counter.
    */
    inline void restoreTimer()
    {
        timer = 0;
    }
#endif
};

#endif // FRONTENDAPPLICATION_HPP
