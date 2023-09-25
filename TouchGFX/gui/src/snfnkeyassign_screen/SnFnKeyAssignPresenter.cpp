#include <gui/snfnkeyassign_screen/SnFnKeyAssignView.hpp>
#include <gui/snfnkeyassign_screen/SnFnKeyAssignPresenter.hpp>

SnFnKeyAssignPresenter::SnFnKeyAssignPresenter(SnFnKeyAssignView& v)
    : KeypadHandler(model), view(v)
{

}

void SnFnKeyAssignPresenter::activate()
{

}

void SnFnKeyAssignPresenter::deactivate()
{

}

void SnFnKeyAssignPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnFnKeyAssignPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

void SnFnKeyAssignPresenter::setFnKeyRemap(uint8_t key, uint8_t setting, char * str)
{
    model->setFnKeyRemap(key, setting, str);
}

uint8_t SnFnKeyAssignPresenter::getFnKeyRemap(uint8_t key)
{
    return (model->getFnKeyRemap(key));
}

uint8_t SnFnKeyAssignPresenter::getFnKeySelected(void)
{
    return (model->getFnKeySelected());
}

void SnFnKeyAssignPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnFnKeyAssignPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnFnKeyAssignPresenter::setBackArrowActive(bool setting)
{
    model->setBackArrowActive(setting);
}

bool SnFnKeyAssignPresenter::getBackArrowActive(void)
{
    return (model->getBackArrowActive());
}

void SnFnKeyAssignPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnFnKeyAssignPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnFnKeyAssignPresenter::clearBarcode(void)
{
    model->clearBarcode();
}
