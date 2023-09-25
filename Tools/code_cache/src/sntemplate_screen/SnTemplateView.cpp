#include <gui/sntemplate_screen/SnTemplateView.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/platform_itf.h>
#include <gui/common/ConfigParam.hpp>


/* This defines the position priority of the application in the main menu */
#define LAUNCH_SCREEN 2

REGISTER_APPLICATION(
    SnTemplateView,
    "TempName",
    TRANSITION_CALLBACK(gotoSnTemplateScreenNoTransition),
    LAUNCH_SCREEN - 1
)

SnTemplateView::SnTemplateView():
    selectItem(1),    /* Initialization of the state flgs that point to the currently selected list element */
    oldSelectItem(1),
    userToastTimer(TOAST_TIMEOUT)
{
  /* We locate the user toast at some point in on the screen
   and set it as invisible */
  ccUserToast.setXY(16, 8);
  ccUserToast.setVisible(false);

  /* We assign all focusable element to the reference array that will be used for navigation */
  MenuItem[0] = &btnBack;  /* Back button */
  MenuItem[1] = &ccMenuItem[0]; /* Generic Menu elements */
  MenuItem[2] = &ccMenuItem[1]; /* Generic Menu elements */
  MenuItem[3] = &ccMenuItem[2]; /* Generic Menu elements */
  MenuItem[4] = &ccBarcodeField;/* Barcode Etry Field */
	
  /* The generic Menu elements do not have any text or perform almost anything else by default - fill in */
  ccMenuItem[0].setText("Flash Toast");
  ccMenuItem[1].setText("Set Barcode as 123");
  ccMenuItem[2].setText("Back to Main Menu");
	
  /* Add all Elements to the container that will implement scrolling */
  listLayout.add(ccMenuItem[0]);
  listLayout.add(ccMenuItem[1]);
  listLayout.add(ccMenuItem[2]);
  listLayout.add(ccBarcodeField);
  /* Add the toast to the screen - it does not reside inside the scrolling list */
  add(ccUserToast);
}

void SnTemplateView::setupScreen()
{
  SnTemplateViewBase::setupScreen();
  /* Make sure all status icons on the top bar are updated */
  presenter->UpdateAllIcons();
  /* On screen entry, select first element */
  selectItem = 1;
  /* Make the Barcode Field Editable */
  ccBarcodeField.setEditable(true);
  /* Update UI with selected element from selectItem */
  selectNewItem();
  /* Scroll the scrolling container to the initial location */
  scrollCnt.setScrollbarWidth(4);
  dragScroll(-1);
  dragScroll(1);
  scrollCnt.invalidate();

  /* Set the User toast text to be the first of the possible toast messages */
  ccUserToast.setText(0); /* TouchGFX Designer can be used to create new types of toast elements */
  
  /* Set the barcode text field as editable */
  ccBarcodeField.setEdit(true);
}

void SnTemplateView::tearDownScreen()
{
    SnTemplateViewBase::tearDownScreen();
}


void SnTemplateView::handleKeyEvent(uint8_t key)
{
  presenter->keyPressed(key);

  /* Here it is possible to handle any key directly if the presenter does not do so -
     however, this is not recomended in an MVP implementation - The presenter should
     implement the screen logic */

  /* The following snipper is how we can manage an input directly in the view - note that
     this specific example is not functional, as the presenter is already managing this key to leave the
     current screen */
  switch (key)
  {
  case KEYCODE_ESC:
    application().gotoSnHomeMenuScreenNoTransition();
    break;
  }
}

void SnTemplateView::handleTickEvent()
{
  /* Called on Every screen refresh */

  /* Here we can handle timers that do not require to be precise */
  if (userToastTimer < TOAST_TIMEOUT)
  {
    userToastTimer++;
    if (userToastTimer == TOAST_TIMEOUT)    /* If the timeout expires */
    {
      ccUserToast.setVisible(false); /* The user Toast is hidden */
      ccUserToast.invalidate();
    }
  }
}

void SnTemplateView::afterTransition()
{
  /* Called after transition */
}

void SnTemplateView::selectNewItem()
{
  for (uint8_t i = 0; i < MENU_ELEMENTS; i++)
  {
    MenuItem[i]->setFocus(selectItem == i);
  }
}

void SnTemplateView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
  /* Individual icon control for the icons on the top status bar */
  statusBar.UpdateIcon(IconId, IconState);
}





void SnTemplateView::dragScroll(int drag)
{
  if (oldSelectItem == 0)
  {
    if (selectItem < 4)
    {
      return;
    }
    else
    {
      drag += 2;
    }
  }

  int16_t xPos = scrollCnt.getScrolledX();
  int16_t yOldPos = scrollCnt.getScrolledY();
  int16_t yNewPos = yOldPos + (64 * drag);
  DragEvent relative(DragEvent::DRAGGED, xPos, yOldPos, xPos, yNewPos);
  scrollCnt.handleDragEvent(relative);
}


void SnTemplateView::exitScreen()
{
  application().gotoSnHomeMenuScreenNoTransition();
}

void  SnTemplateView::scrollListDown()
{   
  /* The presenter is calling this method to scroll the scrolling list down */
  /* This implementation can be done in whichever way the developer wants it to be */
  selectItem = (selectItem == (MENU_ELEMENTS -1)) ? (MENU_ELEMENTS -1) : selectItem + 1;
  dragScroll(oldSelectItem - selectItem);
  selectNewItem();
  oldSelectItem = selectItem;
}

void  SnTemplateView::scrollListUp()
{
  /* The presenter is calling this method to scroll the scrolling list up */
  /* This implementation can be done in whichever way the developer wants it to be */
  selectItem = (selectItem == 0) ? 0 : selectItem - 1;
  dragScroll(oldSelectItem - selectItem);
  selectNewItem();
  oldSelectItem = selectItem;
}

uint8_t  SnTemplateView::getSelectedEntry()
{
  return selectItem;
}

void  SnTemplateView::confirmSelectedEntry()
{
	char aa[] = "123";
	char ab[] = "";
	
  /* Here we perform which ever action corresponds to the menu element we have focused */
  switch(selectItem)
  {
  case 0: /* Back button */
    application().gotoSnHomeMenuScreenNoTransition();
    break;
  case 1: /* Flash Toast */
    userToastTimer = 0;
    ccUserToast.setVisible(true);
    ccUserToast.invalidate();
    break;
  case 2: /* Set Barcode Text as 123 */
    ccBarcodeField.setText(aa);
    ccBarcodeField.invalidate();
    break;
  case 3: /* Back to Main Menu */
    application().gotoSnHomeMenuScreenNoTransition();
    break;
  case 4: /* Barcode Field */
    if (ccBarcodeField.getText() == NULL)
    {
      return; /* No data to send */
    }
    presenter->sendBc(ccBarcodeField.getText());
    ccBarcodeField.setText(ab);

    break;
  }
}

bool SnTemplateView::canEditNumber()
{
  /* We will only edit the barode if it is the selected menu element -
   * this can be changed to the barcode entry field is always editable.
   * Alternatively, we can always yse the actual ccBarcodeField.isEditing() */
  if(selectItem == 4)
  {
    return true;
  }
  
  return false;
}

/* These methods expose methods from the ccBarcodeField item and make them
 * accesible for the Presenter */
void SnTemplateView::insertDigit(char key)
{
  /* Just insert the digit into the field at the cursor position */
  ccBarcodeField.insCh(key);
}

void SnTemplateView::removeDigit()
{
  /* Just remove last digit in the cursor position */
  ccBarcodeField.delCh();
}

void SnTemplateView::modifyDigit(char key)
{
  /* Replace the digit in the cursor position with a new one */
  ccBarcodeField.insCh(key);
}

void SnTemplateView::moveCursorLeft()
{
  /* Mode the Edit cursor to the left */
  ccBarcodeField.moveCursorLeft();
}

void SnTemplateView::moveCursorRight()
{
  /* Move the Edit cursor to the right */
  ccBarcodeField.moveCursorRight();
}
