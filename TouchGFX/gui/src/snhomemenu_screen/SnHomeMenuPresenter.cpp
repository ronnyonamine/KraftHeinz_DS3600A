#include <gui/snhomemenu_screen/SnHomeMenuView.hpp>
#include <gui/snhomemenu_screen/SnHomeMenuPresenter.hpp>

SnHomeMenuPresenter::SnHomeMenuPresenter(SnHomeMenuView& v)
    : KeypadHandler(model), view(v)
{

}

void SnHomeMenuPresenter::activate()
{

}

void SnHomeMenuPresenter::deactivate()
{

}

void SnHomeMenuPresenter::handleDownKey()
{
    view.scrollListDown();
}

void SnHomeMenuPresenter::handleUpKey()
{
    view.scrollListUp();
}

void SnHomeMenuPresenter::handleEnterKey()
{
    uint8_t item = view.getSelectedEntry();
    ZebraApplication::GetApplications()[item].transitionToApp();
}

void SnHomeMenuPresenter::handleNumericKey(uint8_t key)
{
    view.scrollToItem(key);
}

void SnHomeMenuPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnHomeMenuPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

void SnHomeMenuPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

uint8_t SnHomeMenuPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnHomeMenuPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.ChangeScreen();
}
