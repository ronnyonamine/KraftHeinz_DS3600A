#include <gui/sncfgcharparam_screen/SnCfgCharParamView.hpp>
#include <gui/sncfgcharparam_screen/SnCfgCharParamPresenter.hpp>

SnCfgCharParamPresenter::SnCfgCharParamPresenter(SnCfgCharParamView& v)
    : KeypadHandler(model), view(v)
{

}

void SnCfgCharParamPresenter::activate()
{

}

void SnCfgCharParamPresenter::deactivate()
{

}


void SnCfgCharParamPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnCfgCharParamPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

void SnCfgCharParamPresenter::setLocDelimiter(uint8_t RadioOnItem, char user_define)
{
    model->setLocDelimiter(RadioOnItem, user_define);
}

uint8_t SnCfgCharParamPresenter::getLocDelimiter(void)
{
    return (model->getLocDelimiter());
}

uint8_t SnCfgCharParamPresenter::getLocDelimiterDefine(void)
{
    return (model->getLocDelimiterDefine());
}

void SnCfgCharParamPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnCfgCharParamPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnCfgCharParamPresenter::setBackArrowActive(bool setting)
{
    model->setBackArrowActive(setting);
}

void SnCfgCharParamPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnCfgCharParamPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnCfgCharParamPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

void SnCfgCharParamPresenter::handleDownKey()
{
  if(!view.isEditBarSelected())
  {
    view.scrollListDown();
  }
}

void SnCfgCharParamPresenter::handleUpKey()
{
  if(!view.isEditBarSelected())
  {
    view.scrollListUp();
  }
}

void SnCfgCharParamPresenter::handleLeftKey()
{
  if(view.isEditBarSelected())
  {
    view.moveEditCursorLeft();
  }
}

void SnCfgCharParamPresenter::handleRightKey()
{
  if(view.isEditBarSelected())
  {
    view.moveEditCursorRight();
  }
}

void SnCfgCharParamPresenter::handleBkspKey()
{
  if(view.cccOverridevisiblity())
  {
    view.cccOverrideChange(false);
    return;
  }
  if(view.isEditBarSelected())
  {
    view.eraseEditBarChar();
  }
}

void SnCfgCharParamPresenter::handleEscKey()
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

void SnCfgCharParamPresenter::handleBackKey()
{
    view.exitScreen();
}

void SnCfgCharParamPresenter::handleEnterKey()
{
  if (view.cccContinuevisibility())
    {
       view.cccContinueChange(false);
       return;
    }
    if (view.cccOverridevisiblity())
    {
      view.cccOverrideChange(false);
      view.cccContinueChange(true);
      if(view.isEditBarSelected())
      {
        view.commitEditBar();
      }
      else
      {
        view.confirmSelectedEntry();
      }
      return;
    }
  if(view.isEditBarSelected())
  {
    if(((view.getCfgParamName() == "Delimiter") || (view.getCfgParamName() == "Delimiter loc") || (view.getCfgParamName() == "Loc Delimiter invt")) && view.getCfgParamaApp() != "Global")
    {
      if(!view.cccOverridevisiblity())
      view.cccOverrideChange(true);
    /* Handle the Edit Field */
    //view.commitEditBar();
      return;
    }
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
      //view.confirmSelectedEntry();
      if(((view.getCfgParamName() == "Delimiter") || (view.getCfgParamName() == "Delimiter loc") || (view.getCfgParamName() == "Loc Delimiter invt")) && view.getCfgParamaApp() != "Global")
      {
          if(!view.cccOverridevisiblity() && item != 1)
              view.cccOverrideChange(true);
          else 
            view.confirmSelectedEntry();
          return;
      }
      view.confirmSelectedEntry();
      break;
    }
  }
}