#include <gui/containers/BarcodeField_Match.hpp>
#include <gui/common/Barcode.hpp>

BarcodeField_Match::BarcodeField_Match()
{

}

void BarcodeField_Match::initialize()
{
    BarcodeField_MatchBase::initialize();
}

void BarcodeField_Match::setText(char* string)
{
    Barcode barcode;
    barcode.setText(string);
    Unicode::strncpy(textBarcode_LBuffer, barcode.getLfont(), LARGE_FONT_SIZE + 1);
    Unicode::strncpy(textBarcode_SBuffer, barcode.getSfont(), SMALL_FONT_SIZE + 1);
    if (barcode.getEllipsis())
        textBarcode_SBuffer[0] = ELLIPSIS;
    invalidate();
}
