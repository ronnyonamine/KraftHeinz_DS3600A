#include <gui/sncfgnumericparam_screen/SnCfgNumericParamView.hpp>
#include <gui/sncfgnumericparam_screen/SnCfgNumericParamPresenter.hpp>

SnCfgNumericParamPresenter::SnCfgNumericParamPresenter(SnCfgNumericParamView& v)
    : KeypadHandler(model), view(v)
{

}

void SnCfgNumericParamPresenter::activate()
{

}

void SnCfgNumericParamPresenter::deactivate()
{

}


void SnCfgNumericParamPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnCfgNumericParamPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

void SnCfgNumericParamPresenter::setLocDelimiter(uint8_t RadioOnItem, char user_define)
{
    model->setLocDelimiter(RadioOnItem, user_define);
}

uint8_t SnCfgNumericParamPresenter::getLocDelimiter(void)
{
    return (model->getLocDelimiter());
}

uint8_t SnCfgNumericParamPresenter::getLocDelimiterDefine(void)
{
    return (model->getLocDelimiterDefine());
}

void SnCfgNumericParamPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnCfgNumericParamPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnCfgNumericParamPresenter::setBackArrowActive(bool setting)
{
    model->setBackArrowActive(setting);
}

void SnCfgNumericParamPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnCfgNumericParamPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnCfgNumericParamPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

void SnCfgNumericParamPresenter::handleDownKey()
{
  if(!view.isEditBarSelected())
  {
    view.scrollListDown();
  }
}

void SnCfgNumericParamPresenter::handleUpKey()
{
  if(!view.isEditBarSelected())
  {
    view.scrollListUp();
  }
}

void SnCfgNumericParamPresenter::handleLeftKey()
{
  if(view.isEditBarSelected())
  {
    view.moveEditCursorLeft();
  }
}

void SnCfgNumericParamPresenter::handleRightKey()
{
  if(view.isEditBarSelected())
  {
    view.moveEditCursorRight();
  }
}

void SnCfgNumericParamPresenter::handleBkspKey()
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

void SnCfgNumericParamPresenter::handleEscKey()
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

void SnCfgNumericParamPresenter::handleBackKey()
{
    view.exitScreen();
}

void SnCfgNumericParamPresenter::handleEnterKey()
{
//  if(view.isEditBarSelected())
//  {
//    /* Handle the Edit Field */
//    view.commitEditBar();
//  }
//  else
//  {
//    /* Radio Menu Navigation */
//    uint8_t item = view.getSelectedEntry();
//    switch (item)
//    {
//    case 0:
//      setBackArrowActive(true);
//      view.exitScreen();
//      break;
//   
//    default:
//      view.confirmSelectedEntry();
//      break;
//    }
//  }
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
    if(((view.getCfgParamName() == "QTY Delimiter") || (view.getCfgParamName() == "Loc Delimiter") || (view.getCfgParamName() == "LOC Delimiter")) && view.getCfgParamaApp() != "Global")
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
      if(((view.getCfgParamName() == "QTY Delimiter") || (view.getCfgParamName() == "Loc Delimiter") || (view.getCfgParamName() == "LOC Delimiter")) && view.getCfgParamaApp() != "Global")
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