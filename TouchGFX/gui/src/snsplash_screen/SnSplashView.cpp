#include <gui/snsplash_screen/SnSplashView.hpp>
#include <gui/common/platform_itf.h>

SnSplashView::SnSplashView() :
    interactionCounter(0),
    splashCounter(0)
{

}

void SnSplashView::setupScreen()
{
    SnSplashViewBase::setupScreen();
}

void SnSplashView::tearDownScreen()
{
    SnSplashViewBase::tearDownScreen();
}

//Handles delays
void SnSplashView::handleTickEvent()
{
    if(interactionCounter > 0)
    {
        interactionCounter--;
        if(interactionCounter == 216)
        {
            dot5.setAlpha(255);
            dot5.invalidate();
        }

        if(interactionCounter == 192)
        {
            dot5.setAlpha(100);
            dot5.invalidate();
        }

        if(interactionCounter == 168)
        {
            dot4.setAlpha(255);
            dot4.invalidate();
        }

        if(interactionCounter == 144)
        {
            dot4.setAlpha(100);
            dot4.invalidate();
        }

        if(interactionCounter == 120)
        {
            dot3.setAlpha(255);
            dot3.invalidate();
        }

        if(interactionCounter == 96)
        {
            dot3.setAlpha(100);
            dot3.invalidate();
        }

        if(interactionCounter == 72)
        {
            dot2.setAlpha(255);
            dot2.invalidate();
        }

        if(interactionCounter == 48)
        {
            dot2.setAlpha(100);
            dot2.invalidate();
        }

        if(interactionCounter == 24)
        {
            dot1.setAlpha(255);
            dot1.invalidate();             
        }

        if (interactionCounter == 0)
        {
           if (presenter->getScannerMsgRxStatus() == true)
           {
              //application().gotoSnFedExscanScreenNoTransition();
              application().gotoSnHomeMenuScreenNoTransition();
           }
           else if (splashCounter >= 10) // This is a fail safe case, should never happen
           {
              //application().gotoSnFedExscanScreenNoTransition();
              application().gotoSnHomeMenuScreenNoTransition();
           }
           else
           {
             dot1.setAlpha(100);
             dot1.invalidate();    
             SendBootupCommand();
             interactionCounter = INTERACTION_DURATION;    
             splashCounter++;
           }
        }
    }
}

//Called when the screen is done with transition/load
void SnSplashView::afterTransition()
{
    //When screen is entered delay
    interactionCounter = INTERACTION_DURATION;
    splashCounter = 0;
    ili9342c_DisplayOn();
    presenter->signal();
}
