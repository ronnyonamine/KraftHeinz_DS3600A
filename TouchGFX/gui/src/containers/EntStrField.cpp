#include <gui/containers/EntStrField.hpp>
#include <gui/common/ColorPalette.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <string>

EntStrField::EntStrField() :
    textBuffer(KEY_STR_MAX, DISP_KEY_STR_MAX),
    editing(false),
    maxStrSize(false)
{
    cursorPos_X[0] = 19;
    cursorPos_X[1] = 38;
    cursorPos_X[2] = 57;
    cursorPos_X[3] = 76;
    cursorPos_X[4] = 95;
    cursorPos_X[5] = 114;
    cursorPos_X[6] = 133;
    cursorPos_X[7] = 152;
    cursorPos_X[8] = 171;
    cursorPos_X[9] = 190;
    cursorPos_X[10] = 209;
    cursorPos_X[11] = 228;
    cursorPos_X[12] = 247;
    cursorPos_X[13] = 266;
    cursorPos_X[14] = 285;
    cursorPos_X[15] = 304;
}

void EntStrField::initialize()
{
    EntStrFieldBase::initialize();
    textBuffer.setContent("");
    cursorPos_Y = boxCursor.getY();
}

bool EntStrField::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        textLabel.setColor(TEXT_LIGHT);
        textFnKeyStr.setColor(TEXT_LIGHT);
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textLabel.setColor(TEXT_MEDIUM);
        textFnKeyStr.setColor(TEXT_MEDIUM);
    }
    invalidate();
    return (true);
}

void EntStrField::setEdit(bool enableEdit)
{ 
    if (enableEdit)
    {
        boxCursor.setVisible(true);
        textFnKeyStr.setAlpha(255);
    }
    else
    {
        boxCursor.setVisible(false);
        textFnKeyStr.setAlpha(153);
    }
    //textBuffer.setContent("");            //fix for DC-28187.this change is for function keys
    Unicode::strncpy(textFnKeyStrBuffer, textBuffer.getEWContent().c_str(), TEXTFNKEYSTR_SIZE);
    boxCursor.moveTo(cursorPos_X[DISP_KEY_STR_MAX], cursorPos_Y);
    invalidate();
    editing = enableEdit;
}

void EntStrField::setDefaultText(std::string text)
{
  textBuffer.setContent(text);
  showText();
  invalidate();
}

void EntStrField::insCh(char ch)
{ 
    maxStrSize = textBuffer.isMaxContent();
    if (!maxStrSize)
    { 
        textBuffer.appendChar(ch);
        showText();
    }
}

void EntStrField::delCh()
{
    maxStrSize = false;
    textBuffer.removeChar();
    showText();
}

void EntStrField::modifyCh(char ch)
{
    if (!maxStrSize)
    {
        textBuffer.modifyChar(ch);
        showText();
    }
}

void EntStrField::moveCursorLeft()
{
    textBuffer.shiftCursorLeft();
    showText();
}

void EntStrField::moveCursorRight()
{
    textBuffer.shiftCursorRight();
    showText();
}

char * EntStrField::getText()
{
    return textBuffer.getContent();
}

void EntStrField::showText()
{
    Unicode::strncpy(textFnKeyStrBuffer, textBuffer.getEWContent().c_str(), TEXTFNKEYSTR_SIZE);
    if (textBuffer.isRightMore())
    { 
        textFnKeyStrBuffer[DISP_KEY_STR_MAX - 1] = ELLIPSIS;
    }
    if (textBuffer.isLeftMore())
    { 
        textFnKeyStrBuffer[0] = ELLIPSIS;
    }
    textFnKeyStr.invalidate();
    boxCursor.moveTo(cursorPos_X[textBuffer.getEWCursorPos()], cursorPos_Y);
    boxCursor.invalidate();
}

void EntStrField::setNextScan()
{
    setEdit(false);
}
