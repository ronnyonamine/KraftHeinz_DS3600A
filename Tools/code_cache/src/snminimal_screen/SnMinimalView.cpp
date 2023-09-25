#include <gui/snminimal_screen/SnMinimalView.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/platform_itf.h>
#include <gui/common/ConfigParam.hpp>


/* This defines the position priority of the application in the main menu */
#define LAUNCH_SCREEN 2

REGISTER_APPLICATION(
    SnMinimalView,
    "TempName",
    TRANSITION_CALLBACK(gotoSnMinimalScreenNoTransition),
    LAUNCH_SCREEN - 1
)

SnMinimalView::SnMinimalView():
    selectItem(0),    /* Initialization of the state flgs that point to the currently selected list element */
    oldSelectItem(0)
{
  /* We assign all focusable element to the reference array that will be used for navigation */
  MenuItem[0] = &btnBack;  /* Back button */
}

void SnMinimalView::setupScreen()
{
  SnMinimalViewBase::setupScreen();
  /* Make sure all status icons on the top bar are updated */
  presenter->UpdateAllIcons();
  /* On screen entry, select first element */
  selectItem = 0;
  /* Update UI with selected element from selectItem */
  selectNewItem();
}

void SnMinimalView::tearDownScreen()
{
    SnMinimalViewBase::tearDownScreen();
}


void SnMinimalView::handleKeyEvent(uint8_t key)
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

void SnMinimalView::handleTickEvent()
{
  /* Called on Every screen refresh */
  
}

void SnMinimalView::afterTransition()
{
  /* Called after transition */
}

void SnMinimalView::selectNewItem()
{
  for (uint8_t i = 0; i < MENU_ELEMENTS; i++)
  {
    MenuItem[i]->setFocus(selectItem == i);
  }
}

void SnMinimalView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
  /* Individual icon control for the icons on the top status bar */
  statusBar.UpdateIcon(IconId, IconState);
}

void SnMinimalView::dragScroll(int drag)
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


void SnMinimalView::exitScreen()
{
  application().gotoSnHomeMenuScreenNoTransition();
}

void  SnMinimalView::scrollListDown()
{   
  /* The presenter is calling this method to scroll the scrolling list down */
  /* This implementation can be done in whichever way the developer wants it to be */
  selectItem = (selectItem == (MENU_ELEMENTS -1)) ? (MENU_ELEMENTS -1) : selectItem + 1;
  dragScroll(oldSelectItem - selectItem);
  selectNewItem();
  oldSelectItem = selectItem;
}

void  SnMinimalView::scrollListUp()
{
  /* The presenter is calling this method to scroll the scrolling list up */
  /* This implementation can be done in whichever way the developer wants it to be */
  selectItem = (selectItem == 0) ? 0 : selectItem - 1;
  dragScroll(oldSelectItem - selectItem);
  selectNewItem();
  oldSelectItem = selectItem;
}

uint8_t  SnMinimalView::getSelectedEntry()
{
  return selectItem;
}

void  SnMinimalView::confirmSelectedEntry()
{
  /* Here we perform which ever action corresponds to the menu element we have focused */
  switch(selectItem)
  {
  case 0: /* Back button */
    application().gotoSnHomeMenuScreenNoTransition();
    break;
  }
}

bool SnMinimalView::canEditNumber()
{
  return false;
}

void SnMinimalView::insertDigit(char key)
{

}

void SnMinimalView::removeDigit()
{

}

void SnMinimalView::modifyDigit(char key)
{

}

void SnMinimalView::moveCursorLeft()
{

}

void SnMinimalView::moveCursorRight()
{

}
