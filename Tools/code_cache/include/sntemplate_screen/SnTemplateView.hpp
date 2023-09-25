#ifndef SNTEMPLATEVIEW_HPP
#define SNTEMPLATEVIEW_HPP

#include <gui_generated/sntemplate_screen/SnTemplateViewBase.hpp>
#include <gui/sntemplate_screen/SnTemplatePresenter.hpp>
#include <gui/common/ZebraApplication.hpp>
#include <gui/common/AppClasses.hpp>
#include <gui/common/TemplateApp.hpp>


#include <gui/containers/BarcodeField_Loc.hpp>
#include <gui/containers/WildcardedMenuItem.hpp>
#include <gui/containers/TextToast.hpp>
class SnTemplateView : 
  public SnTemplateViewBase,
  public TemplateApp
{
public:

    ZEBRA_APPLICATION

    SnTemplateView();
    virtual ~SnTemplateView() {}
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
    static const uint16_t TOAST_TIMEOUT = 120;
    static const uint8_t  MENU_ELEMENTS = 5;
    /**
     * For the screen/application, here we instantiate UI elements
     * that are not directly placed in the TouchGFX Designer project
     * but will be used at any point.
     * Everything here is up to the developer to implement/fill/use/add
     * as required.
     */
    WildcardedMenuItem ccMenuItem[3]; /* Two Generic Menu Elements */
    BarcodeField_Loc ccBarcodeField;  /* A narrow Barcode entry field */
    /* A Toast we can show on screen if certain coditions are meet */
    TextToast ccUserToast;

    /* An array of 5 focusable Item references. These are used by
     * Menu navigation methods */
    FocusableIetm * MenuItem[MENU_ELEMENTS];
	
	
    /* Flags or internal state variables for screen operation. */
    uint8_t selectItem;
    uint8_t oldSelectItem;
    uint16_t userToastTimer;

    /* Internal class methods to handle some screen operations */
    void dragScroll(int drag);
};

#endif // SNTEMPLATEVIEW_HPP
