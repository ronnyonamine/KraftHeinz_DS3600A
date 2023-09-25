#include <gui/snscanandentloc_screen/SnScanAndEntLocView.hpp>
#include <gui/snscanandentloc_screen/SnScanAndEntLocPresenter.hpp>

SnScanAndEntLocPresenter::SnScanAndEntLocPresenter(SnScanAndEntLocView& v)
    : KeypadHandler(model), view(v)
{

}

void SnScanAndEntLocPresenter::activate()
{

}

void SnScanAndEntLocPresenter::deactivate()
{

}

void SnScanAndEntLocPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnScanAndEntLocPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

void SnScanAndEntLocPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

uint8_t SnScanAndEntLocPresenter::getScanLocBCEditable(void)
{
    return (model->getScanLocBCEditable());
}

uint8_t SnScanAndEntLocPresenter::getScanLocQtyEditable(void)
{
    return (model->getScanLocQtyEditable());
}

void SnScanAndEntLocPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnScanAndEntLocPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnScanAndEntLocPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

int8_t SnScanAndEntLocPresenter::sendQty(uint16_t quantity)
{
    return (model->sendQty(quantity));
}

int8_t SnScanAndEntLocPresenter::sendBcQty(char * barcode, uint16_t quantity)
{
    return (model->sendBcQty(barcode, quantity));
}

int8_t SnScanAndEntLocPresenter::sendLocBcQty(LocRecord_t * location, BarcodeRecord_t * barcode, uint16_t quantity)
{
    return model->sendLocBcQty(location, barcode, quantity);
}

char * SnScanAndEntLocPresenter::getFnKeyRemapString(uint8_t key)
{
    return (model->getFnKeyRemapString(key));
}

uint8_t SnScanAndEntLocPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

bool SnScanAndEntLocPresenter::checkBTPopup(void)
{
  uint8_t bt_state = model->getBackendStatus(STATUS_EVT_BLUETOOTH);
  uint8_t batch_state = model->getBackendStatus(STATUS_EVT_BATCH_MODE);
  uint8_t autoreconnect_bc_data = model->getBackendStatus(STATUS_EVT_AUTORECONNECT);
    
    if ((bt_state != BLUETOOTH_CONNECT) &&
        (batch_state != BATCH_MODE_ON) &&
        (!autoreconnect_bc_data))
    {
       return true;
    }
    return false;
}

bool SnScanAndEntLocPresenter::setlocAppVar(string tmploc)
{
    return (model-> setlocAppVar(tmploc));
}

string SnScanAndEntLocPresenter::getlocAppVar()
{
    return (model-> getlocAppVar());
}

uint8_t SnScanAndEntLocPresenter::getQtyTransferMode(void)
{
    return (model->getQtyTransferMode());
}
