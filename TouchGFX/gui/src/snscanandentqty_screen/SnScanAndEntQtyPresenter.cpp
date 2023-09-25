#include <gui/snscanandentqty_screen/SnScanAndEntQtyView.hpp>
#include <gui/snscanandentqty_screen/SnScanAndEntQtyPresenter.hpp>

SnScanAndEntQtyPresenter::SnScanAndEntQtyPresenter(SnScanAndEntQtyView& v)
    : KeypadHandler(model), view(v)
{

}

void SnScanAndEntQtyPresenter::activate()
{

}

void SnScanAndEntQtyPresenter::deactivate()
{

}

void SnScanAndEntQtyPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnScanAndEntQtyPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

uint8_t SnScanAndEntQtyPresenter::getScanQtyBCEditable(void)
{
    return (model->getScanQtyBCEditable());
}

uint8_t SnScanAndEntQtyPresenter::getScanQtyQtyEditable(void)
{
    return (model->getScanQtyQtyEditable());
}

uint16_t SnScanAndEntQtyPresenter::getQTYToutValue(void)
{
    return (model->getQTYToutValue());
}

void SnScanAndEntQtyPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnScanAndEntQtyPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnScanAndEntQtyPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

int8_t SnScanAndEntQtyPresenter::sendQty(uint16_t quantity)
{
    return (model->sendQty(quantity));
}

int8_t SnScanAndEntQtyPresenter::sendBcQty(char * barcode, uint16_t quantity)
{
    return (model->sendBcQty(barcode, quantity));
}

char * SnScanAndEntQtyPresenter::getFnKeyRemapString(uint8_t key)
{
    return (model->getFnKeyRemapString(key));
}

char * SnScanAndEntQtyPresenter::getRecallBarcode(void)
{
    return (model->getRecallBarcode());
}

void SnScanAndEntQtyPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnScanAndEntQtyPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}
bool SnScanAndEntQtyPresenter::checkBTPopup(void)
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

bool  SnScanAndEntQtyPresenter::setqtyAppFlags(bool qtyappFlag)
{
  return (model->setqtyAppFlags(qtyappFlag));
}
bool  SnScanAndEntQtyPresenter::getqtyAppFlags()
{
  return (model->getqtyAppFlags());
}
uint8_t SnScanAndEntQtyPresenter::getQtyTransferMode(void)
{
    return (model->getQtyTransferMode());
}

