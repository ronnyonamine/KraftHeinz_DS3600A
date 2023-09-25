#include <gui/sncfgmenu_screen/SnCfgMenuView.hpp>
#include <gui/sncfgmenu_screen/SnCfgMenuPresenter.hpp>

SnCfgMenuPresenter::SnCfgMenuPresenter(SnCfgMenuView& v)
    : KeypadHandler(model), view(v)
{

}

void SnCfgMenuPresenter::activate()
{

}

void SnCfgMenuPresenter::deactivate()
{

}

void SnCfgMenuPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnCfgMenuPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

void SnCfgMenuPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnCfgMenuPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnCfgMenuPresenter::setBackArrowActive(bool setting)
{
    model->setBackArrowActive(setting);
}

bool SnCfgMenuPresenter::getBackArrowActive(void)
{
    return (model->getBackArrowActive());
}

void SnCfgMenuPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnCfgMenuPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnCfgMenuPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

void SnCfgMenuPresenter::handleEnterKey()
{
    uint8_t item = view.getSelectedEntry();
    if(item == 0)
    {
      this->setBackArrowActive(false);
      view.jumpToHomeMenu();
      return;
    }
    
    view.jumpToConfigSubmenu();
}
