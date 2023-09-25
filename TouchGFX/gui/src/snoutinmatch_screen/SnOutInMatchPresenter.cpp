#include <gui/snoutinmatch_screen/SnOutInMatchView.hpp>
#include <gui/snoutinmatch_screen/SnOutInMatchPresenter.hpp>

SnOutInMatchPresenter::SnOutInMatchPresenter(SnOutInMatchView& v)
    : KeypadHandler(model), view(v)
{

}

void SnOutInMatchPresenter::activate()
{

}

void SnOutInMatchPresenter::deactivate()
{

}

void SnOutInMatchPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnOutInMatchPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

void SnOutInMatchPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnOutInMatchPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void SnOutInMatchPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnOutInMatchPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnOutInMatchPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

uint8_t SnOutInMatchPresenter::getOutInMatchListFullFlag(void)
{
  return(model->getOutInListFullFlag());
}
