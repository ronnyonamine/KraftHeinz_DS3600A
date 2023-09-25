#include <gui/khmainscreen_screen/KHMainScreenView.hpp>
#include <gui/khmainscreen_screen/KHMainScreenPresenter.hpp>

KHMainScreenPresenter::KHMainScreenPresenter(KHMainScreenView& v)
    : KeypadHandler(model), view(v) // Manual Edit
{

}

void KHMainScreenPresenter::activate()
{

}

void KHMainScreenPresenter::deactivate()
{

}

/* Manual Edit */
void KHMainScreenPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void KHMainScreenPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

void KHMainScreenPresenter::setCurrentScreen(uint8_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t KHMainScreenPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

void KHMainScreenPresenter::BarcodeComeIn(char* BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

/* Manual Entry */
void KHMainScreenPresenter::handleDownKey()
{
}

void KHMainScreenPresenter::handleUpKey()
{
}

void KHMainScreenPresenter::handleEnterKey()
{
}

void KHMainScreenPresenter::handleNumericKey(uint8_t key)
{
}

char* KHMainScreenPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void KHMainScreenPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

void KHMainScreenPresenter::addDataRecord(string date, string time, string learnbarcode, string verifybarcode, string success)
{
    model->addDataRecord(date, time, learnbarcode, verifybarcode, success);
}

int KHMainScreenPresenter::getDataRecordCount()
{
    return model->getDataRecordCount();
}

DataRecord KHMainScreenPresenter::getDataRecord(int index)
{
    return model->getDataRecord(index);
}


void KHMainScreenPresenter::updateDataRecordError(string errorreason, string initials)
{
    model->updateDataRecordError(errorreason, initials);
}

void KHMainScreenPresenter::clearDataRecords()
{
    model->clearDataRecords();
}

int8_t KHMainScreenPresenter::sendDataQty(char* barcode, uint16_t quantity)
{
    return model->sendBcQty(barcode, quantity);
}