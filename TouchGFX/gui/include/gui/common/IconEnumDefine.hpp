#ifndef ICONENUMDEFINE_HPP
#define ICONENUMDEFINE_HPP

typedef enum
{
    HomeIcon = 0,
    ShiftIcon = 1,
    BatchOnIcon = 2,
    BTIcon = 3,
    BatteryIcon = 4
} IconID_t;

typedef enum
{
    Shift_None = 0,
    Shift_Blue = 1,
    Shift_Green = 2,
    Batch_On = 1,
    Batch_Off = 2,
    Batt_Full = 1,
    Batt_Med_High = 2,
    Batt_Med = 3,
    Batt_Med_Low = 4,
    Batt_Low = 5,
    Batt_Full_EOL = 0x81,
    Batt_Med_High_EOL = 0x82,
    Batt_Med_EOL = 0x83,
    Batt_Med_Low_EOL = 0x84,
    Batt_Low_EOL = 0x85,
} IconStateID_t;

#endif // ICONENUMDEFINE_HPP
