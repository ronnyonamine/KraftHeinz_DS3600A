#include <gui/snscanandentqty_d_screen/SnScanAndEntQty_DView.hpp>
#include <gui/snscanandentqty_d_screen/SnScanAndEntQty_DPresenter.hpp>

SnScanAndEntQty_DPresenter::SnScanAndEntQty_DPresenter(SnScanAndEntQty_DView& v)
    : KeypadHandler(model), view(v)
{

}

void SnScanAndEntQty_DPresenter::activate()
{

}

void SnScanAndEntQty_DPresenter::deactivate()
{

}


void SnScanAndEntQty_DPresenter::UpdateAllIcons()
{
  /* Signals the model to start a full icon state update */
  model->UpdateAllIcons();
}

void SnScanAndEntQty_DPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
  /* Signal the View to update a specific icon */
  /* Note that the actual implementation is specific to the view - for most
     screens the icons are located in the Top Status Bar */
  view.UpdateIcon(IconId, IconState);
}

void SnScanAndEntQty_DPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

uint8_t SnScanAndEntQty_DPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

uint8_t SnScanAndEntQty_DPresenter::getScanQtyBCEditable(void)
{
    return (model->getScanQtyBCEditable());
}

uint8_t SnScanAndEntQty_DPresenter::getScanQtyQtyEditable(void)
{
    return (model->getScanQtyQtyEditable());
}

uint16_t SnScanAndEntQty_DPresenter::getQTYToutValue(void)
{
    return (model->getQTYToutValue());
}

void SnScanAndEntQty_DPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnScanAndEntQty_DPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnScanAndEntQty_DPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

void SnScanAndEntQty_DPresenter::sendBcQty(BarcodeRecord_t * barcode, uint16_t quantity)
{
    model->sendLocBcQty(NULL, barcode, quantity);
}

char * SnScanAndEntQty_DPresenter::getFnKeyRemapString(uint8_t key)
{
    return (model->getFnKeyRemapString(key));
}

bool SnScanAndEntQty_DPresenter::checkBTPopup(void)
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
