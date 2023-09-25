#include <gui/containers/InvtListField.hpp>
#include <gui/common/ColorPalette.hpp>

InvtListField::InvtListField()
{

}

void InvtListField::initialize()
{
    InvtListFieldBase::initialize();
}

void InvtListField::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        textQty.setColor(TEXT_LIGHT);
        textBarcode_L.setColor(TEXT_LIGHT);
        textBarcode_S.setColor(TEXT_LIGHT);
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textQty.setColor(TEXT_MEDIUM);
        textBarcode_L.setColor(TEXT_MEDIUM);
        textBarcode_S.setColor(TEXT_MEDIUM);
    }
    invalidate();
}

void InvtListField::setText(bool isEllipsis, char* bc_s, char* bc_l, uint16_t qty)
{
    Unicode::snprintf(textQtyBuffer, TEXTQTY_SIZE, "%d", qty);
    Unicode::strncpy(textBarcode_LBuffer, bc_l, TEXTBARCODE_L_SIZE);
    Unicode::strncpy(textBarcode_SBuffer, bc_s, TEXTBARCODE_S_SIZE);
    if (isEllipsis)
        textBarcode_SBuffer[0] = ELLIPSIS;
    invalidate();
}
