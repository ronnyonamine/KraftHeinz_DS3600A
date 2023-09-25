#ifndef SNMINIMALVIEW_HPP
#define SNMINIMALVIEW_HPP

#include <gui_generated/snminimal_screen/SnMinimalViewBase.hpp>
#include <gui/snminimal_screen/SnMinimalPresenter.hpp>
#include <gui/common/ZebraApplication.hpp>
#include <gui/common/AppClasses.hpp>
#include <gui/common/MinimalApp.hpp>


#include <gui/containers/BarcodeField_Loc.hpp>
#include <gui/containers/WildcardedMenuItem.hpp>
#include <gui/containers/TextToast.hpp>
class SnMinimalView : 
  public SnMinimalViewBase,
  public MinimalApp
{
public:

    ZEBRA_APPLICATION

    SnMinimalView();
    virtual ~SnMinimalView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void selectNewItem();
    virtual void afterTransition();
    virtual void handleKeyEvent(uint8_t key);
    virtual void handleTickEvent();
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);

	
    /* Here we can declare screen APIs for the presenter to control the view -
       actions/operations to execute over the screen */
    void exitScreen();
    void scrollListDown();
    void scrollListUp();
    uint8_t getSelectedEntry();
    void confirmSelectedEntry();
    
    /* These APIs are specific to the Number edit field */
    bool canEditNumber();
    void insertDigit(char key);
    void removeDigit();
    void modifyDigit(char key);
    void moveCursorLeft();
    void moveCursorRight();
	
protected:

private:
    /* static constant declaration */
    static const uint8_t  MENU_ELEMENTS = 1;

    /* An array of focusable Item references. These are used by
     * Menu navigation methods */
    FocusableIetm * MenuItem[MENU_ELEMENTS];
    
    /* Flags or internal state variables for screen operation. */
    uint8_t selectItem;
    uint8_t oldSelectItem;

    /* Internal class methods to handle some screen operations */
    void dragScroll(int drag);
};

#endif // SNMINIMALVIEW_HPP
