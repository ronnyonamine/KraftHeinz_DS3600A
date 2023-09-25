#include <gui/containers/KhErrorReason.hpp>

KhErrorReason::KhErrorReason()
{

}

void KhErrorReason::initialize()
{
    KhErrorReasonBase::initialize();
    loadOptions();
    listLayout1.invalidate();
}



void KhErrorReason::handleKeyEvent(uint8_t key)
{
    int i = menuIndex;
    if (key == KEYCODE_UP) //      224
    {
        listElements[i].deselectThis();
        if (--i < 0)
            i = 0;
        listElements[i].selectThis();
    }
    if (key == KEYCODE_DOWN) //    225
    {
        listElements[i].deselectThis();
        if (++i > 3)
            i = 3;
        listElements[i].selectThis();
    }
    menuIndex = i;
}


int KhErrorReason::getSelection()
{
    return menuIndex;
}


void KhErrorReason::loadOptions()
{
    listElements[0].setupListElement(T_RESOURCEID27);
    listElements[1].setupListElement(T_RESOURCEID28);
    listElements[2].setupListElement(T_RESOURCEID29);
    listElements[3].setupListElement(T_RESOURCEID30);
    menuIndex = 0;
    listElements[menuIndex].selectThis();

    for (uint8_t i = 0; i < 4; ++i)
    {
        listLayout1.add(listElements[i]);
    }
}