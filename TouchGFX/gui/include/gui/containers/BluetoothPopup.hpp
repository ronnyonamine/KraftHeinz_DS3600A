#ifndef BLUETOOTHPOPUP_HPP
#define BLUETOOTHPOPUP_HPP

#include <gui_generated/containers/BluetoothPopupBase.hpp>

class BluetoothPopup : public BluetoothPopupBase
{
public:
    BluetoothPopup();
    virtual ~BluetoothPopup() {}

    virtual void initialize();
protected:
};

#endif // BLUETOOTHPOPUP_HPP
