#include <gui/snminimal_screen/SnMinimalView.hpp>
#include <gui/snminimal_screen/SnMinimalPresenter.hpp>

SnMinimalPresenter::SnMinimalPresenter(SnMinimalView& v)
    : KeypadHandler(model), view(v)
{

}

void SnMinimalPresenter::activate()
{

}

void SnMinimalPresenter::deactivate()
{

}


void SnMinimalPresenter::UpdateAllIcons()
{
  /* Signals the model to start a full icon state update */
  model->UpdateAllIcons();
}

void SnMinimalPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
  /* Signal the View to update a specific icon */
  /* Note that the actual implementation is specific to the view - for most
     screens the icons are located in the Top Status Bar */
  view.UpdateIcon(IconId, IconState);
}

void SnMinimalPresenter::setCurrentScreen(uint8_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnMinimalPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnMinimalPresenter::handleDownKey()
{
    /* Simple implementationfor a skeleton application that works as a list of actions */
    view.scrollListDown();
}

void SnMinimalPresenter::handleUpKey()
{
    /* Simple implementationfor a skeleton application that works as a list of actions */
    view.scrollListUp();
}

void SnMinimalPresenter::handleEnterKey()
{
    /* Simple implementationfor a skeleton application that works as a list of actions */
    view.confirmSelectedEntry();
}

void SnMinimalPresenter::handleBackKey()
{
    if(view.canEditNumber())
    {
      view.removeDigit();
    }
}

void SnMinimalPresenter::handleEscKey()
{
    view.exitScreen();
}

void SnMinimalPresenter::handleNumericKey(uint8_t key)
{
    if(view.canEditNumber())
    {
      view.insertDigit(key);
    } 
}

void SnMinimalPresenter::handleLeftKey()
{
    if(view.canEditNumber())
    {
      view.moveCursorLeft();
    } 
}

void SnMinimalPresenter::handleRightKey()
{
    if(view.canEditNumber())
    {
      view.moveCursorRight();
    } 
}

void SnMinimalPresenter::handleBkspKey()
{
    if(view.canEditNumber())
    {
      view.removeDigit();
    }
}

/* Barcode Interface API */

/**
  * @brief Sends a null terminated string repreenting a barcode to the backend
  * @param barcode null terminated string representing a barcode
  * @retval Return code, defined in deodeDataHandler.h as APP_SEND_<>
  */
int8_t SnMinimalPresenter::sendBc(char * barcode)
{
    return (model->sendBcQty(barcode, 1));
}
