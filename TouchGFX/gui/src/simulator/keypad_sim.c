#ifdef SIMULATOR

#include <gui/simulator/keypad.h>

multiLayer_t _layer = LayerPrimary;

multiLayer_t get_multiLayer_state()
{
    return _layer;
}

void keycodeMapping(uint16_t key)
{
    switch(key)
    {
        case KEYCODE_BLUE:
            _layer = (_layer == LayerBlue) ? LayerPrimary : LayerBlue;
            break;
        case KEYCODE_GREEN:
            _layer = (_layer == LayerGreen) ? LayerPrimary : LayerGreen;
            break;
        default:
            _layer = LayerGreen;
            break;
    }
}
#endif
