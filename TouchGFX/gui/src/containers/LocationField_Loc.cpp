#include <gui/containers/LocationField_Loc.hpp>
#include <string>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

LocationField_Loc::LocationField_Loc() :
    editablebarcode(LOC_FIELD_MAX, DISP_LOC_FIELD_MAX),
    editable(false),
    editing(false),
    maxBarcodeSize(false)
{
    cursorPos_X[0] = 40;
    cursorPos_X[1] = 64;
    cursorPos_X[2] = 88;
    cursorPos_X[3] = 112;
    cursorPos_X[4] = 136;
    cursorPos_X[5] = 160;
    cursorPos_X[6] = 184;
    cursorPos_X[7] = 208;
    cursorPos_X[8] = 232;
    cursorPos_X[9] = 256;
    //cursorPos_X[10] = 280;
    //cursorPos_X[11] = 304;
}

void LocationField_Loc::initialize()
{
    LocationField_LocBase::initialize();
    editablebarcode.setContent("");
    cursorPos_Y = boxCursor.getY();
}

bool LocationField_Loc::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        textBarcode_Name.setColor(TEXT_LIGHT);
        textBarcode.setColor(TEXT_LIGHT);
        imageLocation.setBitmap(touchgfx::Bitmap(BITMAP_LOCATION_HOVER_ID));
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textBarcode_Name.setColor(TEXT_MEDIUM);
        textBarcode.setColor(TEXT_MEDIUM);
        imageLocation.setBitmap(touchgfx::Bitmap(BITMAP_LOCATION_ACTIVE_ID));
    }
    invalidate();
    return (true);
}

void LocationField_Loc::setEditable (bool setting)
{
    if (setting)
    {
        textBarcode_Name.setTypedText(touchgfx::TypedText(T_RESOURCEID14));
    }
    else
    {
        textBarcode_Name.setTypedText(touchgfx::TypedText(T_RESOURCEID15));
    }
    editable = setting;
}

void LocationField_Loc::setEdit(bool enableEdit)
{
    if (!editable)
        return;

    if (enableEdit)
    {
        //boxCursor.setVisible(true);
    }
    else
    {
        //boxCursor.setVisible(false);
    }
    editablebarcode.setContent("");
    showText();
    editing = enableEdit;
}

void LocationField_Loc::setText(char* string)
{
    editablebarcode.setContent(string);
    showText();
}

void LocationField_Loc::insCh(char ch)
{
    if (!editing)
        return;

    maxBarcodeSize = editablebarcode.isMaxContent();
    if (!maxBarcodeSize)
    {
        editablebarcode.appendChar(ch);
        showText();
    }
}

void LocationField_Loc::insStr(char *str)
{
    if (!editing)
        return;

    maxBarcodeSize = editablebarcode.isMaxContent();
    if (!maxBarcodeSize)
    {
        editablebarcode.appendStr(str);
        showText();
    }
}

void LocationField_Loc::delCh()
{
    if (!editing)
        return;

    maxBarcodeSize = false;
    editablebarcode.removeChar();
    showText();
}

void LocationField_Loc::modifyCh(char ch)
{
    if (!editing)
        return;

    if (!maxBarcodeSize)
    {
        editablebarcode.modifyChar(ch);
        showText();
    }
}

void LocationField_Loc::moveCursorLeft()
{
    if (!editing)
        return;

    editablebarcode.shiftCursorLeft();
    showText();
}

void LocationField_Loc::moveCursorRight()
{
    if (!editing)
        return;

    editablebarcode.shiftCursorRight();
    showText();
}

char * LocationField_Loc::getText()
{
    return editablebarcode.getContent();
}

void LocationField_Loc::showText()
{
    Unicode::strncpy(textBarcodeBuffer, editablebarcode.getEWContent().c_str(), TEXTBARCODE_SIZE);
    if (editablebarcode.isRightMore())
        textBarcodeBuffer[DISP_LOC_FIELD_MAX - 1] = ELLIPSIS;
    if (editablebarcode.isLeftMore())
        textBarcodeBuffer[0] = ELLIPSIS;

    boxCursor.moveTo(cursorPos_X[editablebarcode.getEWCursorPos()], cursorPos_Y);
    boxCursor.invalidate();

    textBarcode_Name.setVisible(false);
    textBarcode.setVisible(true);
    invalidate();
}

void LocationField_Loc::setCue(colortype colorSetting)
{
    boxBackGnd.setColor(colorSetting);
    textBarcode.setColor(TEXT_LIGHT);
    invalidate();
}

void LocationField_Loc::setNextScan()
{
    setEdit(false);
    textBarcode_Name.setVisible(true);
    textBarcode.setVisible(false);
    invalidate();
}
