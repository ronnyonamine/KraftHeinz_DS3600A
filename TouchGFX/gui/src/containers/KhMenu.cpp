#include <gui/containers/KhMenu.hpp>
#include <gui/containers/KhListItemContainer.hpp>

KhMenu::KhMenu()
{
}

void KhMenu::initialize()
{
    KhMenuBase::initialize();
    loadOptions();
    listLayout1.invalidate();
}


void KhMenu::handleKeyEvent(uint8_t key)
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

int KhMenu::getSelection()
{
    return menuIndex;
}


void KhMenu::loadOptions()
{
    listElements[0].setupListElement(T_RESOURCEID23);
    listElements[1].setupListElement(T_RESOURCEID24);
    listElements[2].setupListElement(T_RESOURCEID25);
    listElements[3].setupListElement(T_RESOURCEID26);
    menuIndex = 0;
    listElements[menuIndex].selectThis();

    for (uint8_t i = 0; i < 4; ++i)
    {
        listLayout1.add(listElements[i]);
    }
}
