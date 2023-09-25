#include <gui/containers/MatchListField.hpp>
#include <gui/common/ColorPalette.hpp>
#include "BitmapDatabase.hpp"

MatchListField::MatchListField() :
    fieldType(BARCODE)
{

}

void MatchListField::initialize()
{
    MatchListFieldBase::initialize();
}

void MatchListField::setType(MatchListType_t type)
{
    switch (type)
    {
    case BARCODE:
        textNo.setVisible(true);
        imgIcon.setVisible(false);
        textBarcode_L.setColor(TEXT_MEDIUM);
        textBarcode_S.setColor(TEXT_MEDIUM);
        boxDelete.setVisible(false);
        break;

    case MATCHES:
        textNo.setVisible(false);
        imgIcon.setBitmap(touchgfx::Bitmap(BITMAP_CHECK_ID));
        imgIcon.setVisible(true);
        textBarcode_S.setColor(PINKISH_GREY);
        textBarcode_L.setColor(PINKISH_GREY);
        boxDelete.setVisible(true);
        break;

    case MISSING:
        textNo.setVisible(false);
        imgIcon.setBitmap(touchgfx::Bitmap(BITMAP_EXCLAMATION_ID));
        imgIcon.setVisible(true);
        textBarcode_S.setColor(STATES_ERROR);
        textBarcode_L.setColor(STATES_ERROR);
        boxDelete.setVisible(false);
        break;

    case UNEXPECTED:
        textNo.setVisible(false);
        imgIcon.setBitmap(touchgfx::Bitmap(BITMAP_EXCLAMATION_ID));
        imgIcon.setVisible(true);
        textBarcode_S.setColor(STATES_ERROR);
        textBarcode_L.setColor(STATES_ERROR);
        boxDelete.setVisible(false);
        break;
    }
    invalidate();
    fieldType = type;
}

void MatchListField::setAction(uint8_t action)
{
    switch (action | fieldType)
    {
    case 0x00:      // barcode inactive
        boxBackGnd.setColor(TEXT_LIGHT);
        textNo.setColor(TEXT_MEDIUM);
        textBarcode_L.setColor(TEXT_MEDIUM);
        textBarcode_S.setColor(TEXT_MEDIUM);
        break;

    case 0x40:      // barcode delete
        boxBackGnd.setColor(STATES_ERROR);
        textNo.setColor(TEXT_LIGHT);
        textBarcode_L.setColor(TEXT_LIGHT);
        textBarcode_S.setColor(TEXT_LIGHT);
        break;

    case 0x80:      // barcode active
        boxBackGnd.setColor(PRIMARY_BLUE);
        textNo.setColor(TEXT_LIGHT);
        textBarcode_L.setColor(TEXT_LIGHT);
        textBarcode_S.setColor(TEXT_LIGHT);
        break;

    case 0x01:      // matched inactive
        boxBackGnd.setColor(TEXT_LIGHT);
        imgIcon.setBitmap(touchgfx::Bitmap(BITMAP_CHECK_ID));
        textBarcode_S.setColor(PINKISH_GREY);
        textBarcode_L.setColor(PINKISH_GREY);
        boxDelete.setColor(PINKISH_GREY);
        break;

    case 0x81:      // matched active
        boxBackGnd.setColor(PRIMARY_BLUE);
        imgIcon.setBitmap(touchgfx::Bitmap(BITMAP_CHECK_ACTIVE_ID));
        textBarcode_S.setColor(TEXT_LIGHT);
        textBarcode_L.setColor(TEXT_LIGHT);
        boxDelete.setColor(TEXT_LIGHT);
        break;

    case 0x02:      // missing inactive
        boxBackGnd.setColor(TEXT_LIGHT);
        imgIcon.setBitmap(touchgfx::Bitmap(BITMAP_MINUS_ID));
        textBarcode_S.setColor(STATES_ERROR);
        textBarcode_L.setColor(STATES_ERROR);
        break;

    case 0x82:      // missing active
        boxBackGnd.setColor(STATES_ERROR);
        imgIcon.setBitmap(touchgfx::Bitmap(BITMAP_MINUS_ACTIVE_ID));
        textBarcode_S.setColor(TEXT_LIGHT);
        textBarcode_L.setColor(TEXT_LIGHT);
        break;

    case 0x03:      // unexpected inactive
        boxBackGnd.setColor(TEXT_LIGHT);
        imgIcon.setBitmap(touchgfx::Bitmap(BITMAP_EXCLAMATION_ID));
        textBarcode_S.setColor(STATES_ERROR);
        textBarcode_L.setColor(STATES_ERROR);
        break;

    case 0x83:      // unexpected active
        boxBackGnd.setColor(STATES_ERROR);
        imgIcon.setBitmap(touchgfx::Bitmap(BITMAP_EXCLAMATION_ACTIVE_ID));
        textBarcode_S.setColor(TEXT_LIGHT);
        textBarcode_L.setColor(TEXT_LIGHT);

        break;
    }
    invalidate();
}

void MatchListField::setText(uint16_t no, bool isEllipsis, char* bc_s, char* bc_l)
{
    Unicode::snprintf(textNoBuffer, TEXTNO_SIZE, "%d", no);
    Unicode::strncpy(textBarcode_LBuffer, bc_l, TEXTBARCODE_L_SIZE);
    Unicode::strncpy(textBarcode_SBuffer, bc_s, TEXTBARCODE_S_SIZE);
    if (isEllipsis)
        textBarcode_SBuffer[0] = ELLIPSIS;
    invalidate();
}
