#include <gui/snbarcodeprogress_screen/SnBarcodeProgressView.hpp>
#include <gui/snbarcodeprogress_screen/SnBarcodeProgressPresenter.hpp>

SnBarcodeProgressPresenter::SnBarcodeProgressPresenter(SnBarcodeProgressView& v)
    : KeypadHandler(model), view(v)
{

}

void SnBarcodeProgressPresenter::activate()
{

}

void SnBarcodeProgressPresenter::deactivate()
{

}

void SnBarcodeProgressPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnBarcodeProgressPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

uint16_t SnBarcodeProgressPresenter::sendtotalqtyinvt(void)
{
    return (model->sendtotalqtyinvt());
}

uint16_t SnBarcodeProgressPresenter::sendcountinvt(void)
{
  return (model->sendcountinvt());
}

bool SnBarcodeProgressPresenter::getInvtInProgress(void)
{
    return (model->getInvtInProgress());
}

bool SnBarcodeProgressPresenter::checkBTPopup(void)
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

// For ScanAndEntQty
bool  SnBarcodeProgressPresenter::setqtyAppFlags(bool qtyappFlag)
{
  return (model->setqtyAppFlags(qtyappFlag));
}
bool  SnBarcodeProgressPresenter::getqtyAppFlags()
{
  return (model->getqtyAppFlags());
}

// For ScanAndEntLoc
bool SnBarcodeProgressPresenter::setlocAppVar(string tmploc)
{
    return (model-> setlocAppVar(tmploc));
}

string SnBarcodeProgressPresenter::getlocAppVar()
{
    return (model-> getlocAppVar());
}

// For ScanAndEntInvt
void SnBarcodeProgressPresenter::setinvtAppVar(invt1 invtrecord)
{
  return (model->setinvtAppVar(invtrecord ));
}
invt1 SnBarcodeProgressPresenter::getinvtAppVar()
{
  return (model->getinvtAppVar());
}

uint8_t SnBarcodeProgressPresenter::getCurrentScreen()
{
  return (model->getCurrentScreen());
}


