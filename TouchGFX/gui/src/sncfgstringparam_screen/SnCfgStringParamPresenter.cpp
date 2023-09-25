#include <gui/sncfgstringparam_screen/SnCfgStringParamView.hpp>
#include <gui/sncfgstringparam_screen/SnCfgStringParamPresenter.hpp>

SnCfgStringParamPresenter::SnCfgStringParamPresenter(SnCfgStringParamView& v)
    :KeypadHandler(model), view(v)
{

}

void SnCfgStringParamPresenter::activate()
{

}

void SnCfgStringParamPresenter::deactivate()
{

}

void SnCfgStringParamPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnCfgStringParamPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}


void SnCfgStringParamPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnCfgStringParamPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnCfgStringParamPresenter::setBackArrowActive(bool setting)
{
    model->setBackArrowActive(setting);
}

void SnCfgStringParamPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnCfgStringParamPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnCfgStringParamPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

void SnCfgStringParamPresenter::handleDownKey()
{
  if(!view.isEditBarSelected())
  {
    view.scrollListDown();
  }
}

void SnCfgStringParamPresenter::handleUpKey()
{
  if(!view.isEditBarSelected())
  {
    view.scrollListUp();
  }
}

void SnCfgStringParamPresenter::handleLeftKey()
{
  if(view.isEditBarSelected())
  {
    view.moveEditCursorLeft();
  }
}

void SnCfgStringParamPresenter::handleRightKey()
{
  if(view.isEditBarSelected())
  {
    view.moveEditCursorRight();
  }
}

void SnCfgStringParamPresenter::handleBkspKey()
{
  if(view.isEditBarSelected())
  {
    view.eraseEditBarChar();
  }
}

void SnCfgStringParamPresenter::handleEscKey()
{
  if(view.isEditBarSelected())
  {
    view.cancelEditBar();
  }
  else
  {
    view.exitScreen();
  }
}

void SnCfgStringParamPresenter::handleBackKey()
{
    view.exitScreen();
}

void SnCfgStringParamPresenter::handleEnterKey()
{
  if(view.isEditBarSelected())
  {
    /* Handle the Edit Field */
    view.commitEditBar();
  }
  else
  {
    /* Radio Menu Navigation */
    uint8_t item = view.getSelectedEntry();
    switch (item)
    {
    case 0:
      setBackArrowActive(true);
      view.exitScreen();
      break;
      
    default:
      view.confirmSelectedEntry();
      break;
    }
  }
}