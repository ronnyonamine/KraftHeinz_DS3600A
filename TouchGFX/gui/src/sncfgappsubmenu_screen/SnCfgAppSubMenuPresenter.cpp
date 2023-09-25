#include <gui/sncfgappsubmenu_screen/SnCfgAppSubMenuView.hpp>
#include <gui/sncfgappsubmenu_screen/SnCfgAppSubMenuPresenter.hpp>

SnCfgAppSubMenuPresenter::SnCfgAppSubMenuPresenter(SnCfgAppSubMenuView& v)
    : KeypadHandler(model), view(v)
{

}

void SnCfgAppSubMenuPresenter::activate()
{

}

void SnCfgAppSubMenuPresenter::deactivate()
{

}


void SnCfgAppSubMenuPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnCfgAppSubMenuPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

void SnCfgAppSubMenuPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnCfgAppSubMenuPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnCfgAppSubMenuPresenter::setBackArrowActive(bool setting)
{
    model->setBackArrowActive(setting);
}

bool SnCfgAppSubMenuPresenter::getBackArrowActive(void)
{
    return (model->getBackArrowActive());
}

void SnCfgAppSubMenuPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnCfgAppSubMenuPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnCfgAppSubMenuPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

void SnCfgAppSubMenuPresenter::handleEnterKey()
{
    uint8_t item = view.getSelectedEntry();
    if(item == 0)
    {
      view.jumpToPrevScreen();
      return;
    }
    view.jumpToParamConfig();
}
