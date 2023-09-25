#include <gui/snscaninventory_screen/SnScanInventoryView.hpp>
#include <gui/snscaninventory_screen/SnScanInventoryPresenter.hpp>

SnScanInventoryPresenter::SnScanInventoryPresenter(SnScanInventoryView& v)
    : KeypadHandler(model), view(v)
{

}

void SnScanInventoryPresenter::addRecord(string date, string time, string learnbarcode, string verifybarcode, string success)
{
    model->addDataRecord(date, time, learnbarcode, verifybarcode, success);
}

void SnScanInventoryPresenter::updateRecord(string errorreason, string initials)
{
    model->updateDataRecordError(errorreason, initials);
}

void SnScanInventoryPresenter::clearRecords()
{
    model->clearDataRecords();
}

DataRecord SnScanInventoryPresenter::getRecord(int i)
{
    return model->getDataRecord(i);
}

int SnScanInventoryPresenter::getRecordCount()
{
    return model->getDataRecordCount();
}

void SnScanInventoryPresenter::activate()
{

}

void SnScanInventoryPresenter::deactivate()
{

}

void SnScanInventoryPresenter::UpdateAllIcons()
{
    model->UpdateAllIcons();
}

void SnScanInventoryPresenter::setCurrentScreen(uint32_t CurrentScreen)
{
    model->setCurrentScreen(CurrentScreen);
}

void SnScanInventoryPresenter::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    view.UpdateIcon(IconId, IconState);
}

uint8_t SnScanInventoryPresenter::getHomeKeyLaunch(void)
{
    return (model->getHomeKeyLaunch());
}

uint8_t SnScanInventoryPresenter::getScanInvtBCEditable(void)
{
    return (model->getScanInvtBCEditable());
}

uint8_t SnScanInventoryPresenter::getScanInvtQtyEditable(void)
{
    return (model->getScanInvtQtyEditable());
}

uint8_t SnScanInventoryPresenter::getInvtStore(void)
{
    return (model->getInvtStore());
}

void SnScanInventoryPresenter::BarcodeComeIn(char * BarcodeData)
{
    view.BarcodeComeIn(BarcodeData);
}

char * SnScanInventoryPresenter::getBarcode(void)
{
    return (model->getBarcode());
}

void SnScanInventoryPresenter::clearBarcode(void)
{
    model->clearBarcode();
}

char * SnScanInventoryPresenter::getFnKeyRemapString(uint8_t key)
{
    return (model->getFnKeyRemapString(key));
}

void SnScanInventoryPresenter::setInvtRecord(LocRecord_t *location, BarcodeRecord_t *barcode, uint16_t quantity)
{
    model->setInvtRecord(location, barcode, quantity);
}

Invt_Record_t* SnScanInventoryPresenter::getInvtRecord(uint16_t index)
{
    return (model->getInvtRecord(index));
}

void SnScanInventoryPresenter::submitInvtList(void)
{
    model->submitInvtList();
}

void SnScanInventoryPresenter::setInvtInProgress(bool setting)
{
    model->setInvtInProgress(setting);
}

bool SnScanInventoryPresenter::getInvtInProgress(void)
{
    return (model->getInvtInProgress());
}

void SnScanInventoryPresenter::changeLoc(LocRecord_t *oldLoc, LocRecord_t *newLoc)
{
    model->changeLoc(oldLoc, newLoc);
}

uint16_t SnScanInventoryPresenter::sendtotalqtyinvt(void)
{
    return (model->sendtotalqtyinvt());
}

uint16_t SnScanInventoryPresenter::sendcountinvt(void)
{
  return (model->sendcountinvt());
}

bool SnScanInventoryPresenter::checkBTPopup(void)
{
    uint8_t bt_state = model->getBackendStatus(STATUS_EVT_BLUETOOTH);
    uint8_t batch_state = model->getBackendStatus(STATUS_EVT_BATCH_MODE);
    
    if ((bt_state != BLUETOOTH_CONNECT) &&
        (batch_state != BATCH_MODE_ON))
    {
        return true;
    }
    return false;
}

void SnScanInventoryPresenter::setinvtAppVar(invt1 invtrecord)
{
  return (model->setinvtAppVar(invtrecord ));
}
invt1 SnScanInventoryPresenter::getinvtAppVar()
{
  return (model->getinvtAppVar());
}
uint8_t SnScanInventoryPresenter::getQtyTransferMode(void)
{
    return (model->getQtyTransferMode());
}
