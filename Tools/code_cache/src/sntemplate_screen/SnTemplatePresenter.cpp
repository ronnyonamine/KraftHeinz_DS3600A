#include <gui/sntemplate_screen/SnTemplateView.hpp>
#include <gui/sntemplate_screen/SnTemplatePresenter.hpp>

SnTemplatePresenter::SnTemplatePresenter(SnTemplateView& v)
    : KeypadHandler(model), view(v)
{

}

void SnTemplatePresenter::activate()
{

}

void SnTemplatePresenter::deactivate()
{

}


void SnTemplatePresenter::UpdateAllIcons()
{
  /* Signals the model to start a full icon state update */
  model->UpdateAllIcons();
}

void SnTemplatePresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
  /* Signal the View to update a specific icon */
  /* Note that the actual implementation is specific to the view - for most
     screens the icons are located in the Top Status Bar */
  view.UpdateIcon(IconId, IconState);
}

void SnTemplatePresenter::setCurrentScreen(uint8_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnTemplatePresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnTemplatePresenter::handleDownKey()
{
    /* Simple implementationfor a skeleton application that works as a list of actions */
    view.scrollListDown();
}

void SnTemplatePresenter::handleUpKey()
{
    /* Simple implementationfor a skeleton application that works as a list of actions */
    view.scrollListUp();
}

void SnTemplatePresenter::handleEnterKey()
{
    /* Simple implementationfor a skeleton application that works as a list of actions */
    view.confirmSelectedEntry();
}

void SnTemplatePresenter::handleBackKey()
{
    if(view.canEditNumber())
    {
      view.removeDigit();
    }
}

void SnTemplatePresenter::handleEscKey()
{
    view.exitScreen();
}

void SnTemplatePresenter::handleNumericKey(uint8_t key)
{
    if(view.canEditNumber())
    {
      view.insertDigit(key);
    } 
}

void SnTemplatePresenter::handleLeftKey()
{
    if(view.canEditNumber())
    {
      view.moveCursorLeft();
    } 
}

void SnTemplatePresenter::handleRightKey()
{
    if(view.canEditNumber())
    {
      view.moveCursorRight();
    } 
}

void SnTemplatePresenter::handleBkspKey()
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
int8_t SnTemplatePresenter::sendBc(char * barcode)
{
    return (model->sendBcQty(barcode, 1));
}
