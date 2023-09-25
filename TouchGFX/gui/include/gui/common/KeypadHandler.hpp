#ifndef __KEYPAD_HANDLER__
#define __KEYPAD_HANDLER__
#include <gui/model/Model.hpp>
#include <gui/common/ZebraApplication.hpp>
#include <touchgfx/Utils.hpp>

class KeypadHandler
{
public:
    KeypadHandler(Model * model)
    {
        this->g_model = model;
    }

    virtual void handleUpKey() { }
    virtual void handleDownKey() { }
    virtual void handleEnterKey() { }
    virtual void handleNumericKey(uint8_t key) { }
    virtual void handleEscKey() { }
    virtual void handleBackKey() { }
    virtual void handleLeftKey() { }
    virtual void handleRightKey() { }
    virtual void handleBkspKey() { }
    
    inline virtual void handleHomeKey(uint8_t key) 
    {
        /* Home values are indexed starting from 1. Home Menu is the base
         * index (1). Since it's not an application, we will not use the ZebraApp
         * static function 
         */
        if(g_model->getHomeKeyLaunch() == 0)
        {
            return;
        }
        
        if(g_model->getHomeKeyLaunch() == 1)
        {
            ZebraApplication::application().gotoSnHomeMenuScreenNoTransition();
            return;
        }

        /* A higher value means that the No home key was selected and thus, should
         * ignore it
         */
        if(g_model->getHomeKeyLaunch() > ZebraApplication::GetApplications().size() + 1)
        {
            return;
        }

        /* Do noting if user is already on home screen */
//        if(g_model->getHomeKeyLaunch() == g_model->getCurrentScreen())
//        {
//            return;
//        }

        ZebraApplication::GetApplications()[g_model->getHomeKeyLaunch() - 2].transitionToApp();
    }

    virtual void keyPressed(uint8_t key)
    {
        switch(key)
        {
            case KEYCODE_UP:
                handleUpKey();
                break;
            case KEYCODE_DOWN:
                handleDownKey();
                break;
            case KEYCODE_LEFT:
                handleLeftKey();
                break;
            case KEYCODE_RIGHT:
                handleRightKey();
                break;
            case KEYCODE_HOME:
                handleHomeKey(key);
                break;
            case KEYCODE_ENTER:
                handleEnterKey();
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                handleNumericKey(key);
                break;
            case KEYCODE_ESC:
                handleEscKey();
                break;
            case KEYCODE_BACK:
                handleBackKey();
                break;
            case KEYCODE_BKSP:
                handleBkspKey();
                break;
            default:
                break;
        }        
    }

    virtual ~KeypadHandler() { }
private:
    Model * g_model;
};

#endif