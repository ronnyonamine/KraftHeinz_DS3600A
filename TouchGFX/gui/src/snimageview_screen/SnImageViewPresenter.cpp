#include <gui/snimageview_screen/SnImageViewView.hpp>
#include <gui/snimageview_screen/SnImageViewPresenter.hpp>

SnImageViewPresenter::SnImageViewPresenter(SnImageViewView& v)
    : KeypadHandler(model), view(v)
{

}

void SnImageViewPresenter::activate()
{

}

void SnImageViewPresenter::deactivate()
{

}

void SnImageViewPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnImageViewPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

void SnImageViewPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnImageViewPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnImageViewPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnImageViewPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnImageViewPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

uint8_t SnImageViewPresenter::getLiveCapture(void)
{
    return (model->getLiveCapture());
}

void SnImageViewPresenter::setImgViewCmd(uint16_t cmd)
{
    model->setImgViewCmd(cmd);
}
