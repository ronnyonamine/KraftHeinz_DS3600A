#include <gui/containers/BarcodeField_Loc.hpp>
#include <gui/common/ColorPalette.hpp>
#include <string>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

BarcodeField_Loc::BarcodeField_Loc() :
    editable(false),
    editing(false),
    maxBarcodeSize(false)
{
    cursorPos_X[0] = 64;
    cursorPos_X[1] = 80;
    cursorPos_X[2] = 96;
    cursorPos_X[3] = 112;
    cursorPos_X[4] = 128;
    cursorPos_X[5] = 144;
    cursorPos_X[6] = 160;
    cursorPos_X[7] = 176;
    cursorPos_X[8] = 192;
    cursorPos_X[9] = 208;
    cursorPos_X[10] = 232;
    cursorPos_X[11] = 256;
    cursorPos_X[12] = 280;
    cursorPos_X[13] = 304;
}

void BarcodeField_Loc::initialize()
{
    BarcodeField_LocBase::initialize();
    editablebarcode.setContent("");
    barcode.setText(editablebarcode.getEWContent());
    cursorPos_Y = boxCursor.getY();
}

bool BarcodeField_Loc::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        textBarcode_Name.setColor(TEXT_LIGHT);
        textBarcode_L.setColor(TEXT_LIGHT);
        textBarcode_S.setColor(TEXT_LIGHT);
        imgBarcode.setBitmap(touchgfx::Bitmap(BITMAP_BARCODE_ACTIVE_ID));
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textBarcode_Name.setColor(TEXT_MEDIUM);
        textBarcode_L.setColor(TEXT_MEDIUM);
        textBarcode_S.setColor(TEXT_MEDIUM);
        imgBarcode.setBitmap(touchgfx::Bitmap(BITMAP_BARCODE_ID));
    }
    invalidate();
    return (true);
}

void BarcodeField_Loc::setEditable(bool setting)
{
    if (setting)
    {
        Unicode::snprintf(textBarcode_NameBuffer, TEXTBARCODE_NAME_SIZE, "%s", touchgfx::TypedText(T_RESOURCEID12).getText());
    }
    else
    {
        Unicode::snprintf(textBarcode_NameBuffer, TEXTBARCODE_NAME_SIZE, "%s", touchgfx::TypedText(T_RESOURCEID13).getText());
    }
    editable = setting;
}

void BarcodeField_Loc::setEdit(bool enableEdit)
{
    if (!editable)
        return;

    if (enableEdit)
    {
        boxCursor.setVisible(true);
    }
    else
    {
        boxCursor.setVisible(false);
    }
    editablebarcode.setContent("");
    barcode.setText(editablebarcode.getEWContent());
    showText();
    editing = enableEdit;
}

void BarcodeField_Loc::setText(char* string)
{
    editablebarcode.setContent(string);
    barcode.setText(editablebarcode.getEWContent());
    showText();
}

void BarcodeField_Loc::insCh(char ch)
{
    if (!editing)
        return;

    maxBarcodeSize = editablebarcode.isMaxContent();
    if (!maxBarcodeSize)
    {
        editablebarcode.appendChar(ch);
        barcode.setText(editablebarcode.getEWContent());
        showText();
    }
}

void BarcodeField_Loc::insStr(char *str)
{
    if (!editing)
        return;

    maxBarcodeSize = editablebarcode.isMaxContent();
    if (!maxBarcodeSize)
    {
        editablebarcode.appendStr(str);
        barcode.setText(editablebarcode.getEWContent());
        showText();
    }
}

void BarcodeField_Loc::delCh()
{
    if (!editing)
        return;

    maxBarcodeSize = false;
    editablebarcode.removeChar();
    barcode.setText(editablebarcode.getEWContent());
    showText();
}

void BarcodeField_Loc::modifyCh(char ch)
{
    if (!editing)
        return;

    if (!maxBarcodeSize)
    {
        editablebarcode.modifyChar(ch);
        barcode.setText(editablebarcode.getEWContent());
        showText();
    }
}

void BarcodeField_Loc::moveCursorLeft()
{
    if (!editing)
        return;

    editablebarcode.shiftCursorLeft();
    barcode.setText(editablebarcode.getEWContent());
    showText();
}

void BarcodeField_Loc::moveCursorRight()
{
    if (!editing)
        return;

    editablebarcode.shiftCursorRight();
    barcode.setText(editablebarcode.getEWContent());
    showText();
}

char * BarcodeField_Loc::getText()
{
    return editablebarcode.getContent();
}

void BarcodeField_Loc::showText()
{
    Unicode::strncpy(textBarcode_LBuffer, barcode.getLfont(), LARGE_FONT_SIZE + 1);
    if (editablebarcode.isRightMore())
        textBarcode_LBuffer[3] = ELLIPSIS;
    Unicode::strncpy(textBarcode_SBuffer, barcode.getSfont(), SMALL_FONT_SIZE + 1);
    if (editablebarcode.isLeftMore())
        textBarcode_SBuffer[0] = ELLIPSIS;

    boxCursor.moveTo(cursorPos_X[editablebarcode.getEWCursorPos()], cursorPos_Y);
    boxCursor.invalidate();

    textBarcode_Name.setVisible(false);
    textBarcode_L.setVisible(true);
    textBarcode_S.setVisible(true);
    invalidate();
}

void BarcodeField_Loc::setCue()
{
    boxBackGnd.setColor(STATES_SUCCESS);
    textBarcode_S.setColor(TEXT_LIGHT);
    textBarcode_L.setColor(TEXT_LIGHT);
    imgBarcode.setBitmap(touchgfx::Bitmap(BITMAP_BARCODE_ACTIVE_ID));
    invalidate();
}

void BarcodeField_Loc::setNextScan()
{
    setEdit(false);
    textBarcode_Name.setVisible(true);
    textBarcode_L.setVisible(false);
    textBarcode_S.setVisible(false);
    invalidate();
}
