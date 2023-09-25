#include <gui/sncfgboolparam_screen/SnCfgBoolParamView.hpp>
#include <gui/sncfgboolparam_screen/SnCfgBoolParamPresenter.hpp>
#include <gui/common/ConfigParam.hpp>

SnCfgBoolParamPresenter::SnCfgBoolParamPresenter(SnCfgBoolParamView& v)
    : KeypadHandler(model), view(v)
{

}

void SnCfgBoolParamPresenter::activate()
{

}

void SnCfgBoolParamPresenter::deactivate()
{

}

void SnCfgBoolParamPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnCfgBoolParamPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

void SnCfgBoolParamPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnCfgBoolParamPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnCfgBoolParamPresenter::setBackArrowActive(bool setting)
{
    model->setBackArrowActive(setting);
}

void SnCfgBoolParamPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnCfgBoolParamPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnCfgBoolParamPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

void SnCfgBoolParamPresenter::handleDownKey()
{
    view.scrollListDown();
}

void SnCfgBoolParamPresenter::handleUpKey()
{
    view.scrollListUp();
}

void SnCfgBoolParamPresenter::handleEnterKey()
{
    /* Radio Menu Navigation */
    uint8_t item = view.getSelectedEntry();
    if (view.cccContinuevisibility())
    {
       view.cccContinueChange(false);
       return;
    }
    if (view.cccOverridevisiblity())
    {
      view.cccOverrideChange(false);
      view.cccContinueChange(true);
      view.confirmSelectedEntry();
      return;
    }
    if (view.cccAboutVisibility())
    {
       view.cccAboutChange(false);
       return;
    }
    switch (item)
    {
    case 0:
      setBackArrowActive(true);
      view.exitScreen();
      break;

    default:
      if(((view.getCfgParamName() == "Manual BC Entry") || (view.getCfgParamName() == "Manual QTY Entry")) && view.getCfgParamaApp() != "Global")
      {
          if(!view.cccOverridevisiblity())
              view.cccOverrideChange(true);
          return;
      }
      view.confirmSelectedEntry();
      break;
    }
}

void SnCfgBoolParamPresenter::handleBackKey()
{
  setBackArrowActive(true);
  view.exitScreen();
}

void SnCfgBoolParamPresenter::handleEscKey()
{
  setBackArrowActive(true);
  view.exitScreen();
}

void SnCfgBoolParamPresenter::handleBkspKey()
{
  if(view.cccOverridevisiblity())
  {
    view.cccOverrideChange(false);
  }
}

void SnCfgBoolParamPresenter::handleRightKey()
{
  if(view.imgRightVisible())
      view.cccAboutChange(true);
}