#include <gui/containers/NumberField_Loc.hpp>
#include <gui/common/ColorPalette.hpp>
#include <string>
#include <stdlib.h>

NumberField_Loc::NumberField_Loc() :
    editable(false),
    editing(false),
    cursorPos(0)
{
    textBuffer[0] = '1';
    textBuffer[1] = '\0';
}

void NumberField_Loc::initialize()
{
    NumberField_LocBase::initialize();
}

bool NumberField_Loc::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        textEditQty.setColor(TEXT_LIGHT);
        textLabel.setColor(TEXT_LIGHT);
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textEditQty.setColor(TEXT_DARK);
        textLabel.setColor(TEXT_DARK);
    }
    invalidate();
    return (true);
}

void NumberField_Loc::setEdit(bool enableEdit)
{
    if (!editable)
        return;

    if (enableEdit)
    {
        textBuffer[0] = '\0';
        boxCursor.setVisible(true);
        textEditQty.setAlpha(255);
    }
    else
    {
        textBuffer[0] = '1';
        textBuffer[1] = '\0';
        boxCursor.setVisible(false);
        textEditQty.setAlpha(153);
    }
    Unicode::strncpy(textEditQtyBuffer, textBuffer, MAX_FIELD_SIZE);
    invalidate();
    editing = enableEdit;
}

void NumberField_Loc::insCh(char ch)
{
    if (!editing)
        return;

    std::string str;
    str.assign(textBuffer);
    if (str.size() < (MAX_FIELD_SIZE - 1))
    {
        str.insert(str.begin() + cursorPos, ch);
        std::size_t length = str.copy(textBuffer, MAX_FIELD_SIZE);
        textBuffer[length] = '\0';
        moveCursorRight();
        showText();
    }
}

void NumberField_Loc::delCh()
{
    if (!editing)
        return;

    if (cursorPos > 0)
    {
        std::string str;
        str.assign(textBuffer);
        if (str.size() > 0)
        {
            str.erase(str.begin() + cursorPos - 1);
            std::size_t length = str.copy(textBuffer, MAX_FIELD_SIZE);
            textBuffer[length] = '\0';
            moveCursorLeft();
            showText();
        }
    }
}

void NumberField_Loc::moveCursorLeft()
{
    if (!editing)
        return;

    std::string str;
    str.assign(textBuffer);
    if (cursorPos > 0)
    {
        cursorPos--;
        boxCursor.moveTo(304 - (str.size() - cursorPos) * CHAR_W, boxCursor.getY());
        boxCursor.invalidate();
    }
}

void NumberField_Loc::moveCursorRight()
{
    if (!editing)
        return;

    std::string str;
    str.assign(textBuffer);
    if (cursorPos < str.size())
    {
        cursorPos++;
        boxCursor.moveTo(304 - (str.size() - cursorPos) * CHAR_W, boxCursor.getY());
        boxCursor.invalidate();
    }
}

uint16_t NumberField_Loc::getNumber()
{
    return atoi(textBuffer);
}

void NumberField_Loc::showText()
{
    Unicode::strncpy(textEditQtyBuffer, textBuffer, MAX_FIELD_SIZE);
    textEditQty.invalidate();
}

void NumberField_Loc::setCue()
{
    boxBackGnd.setColor(TEXT_LIGHT);
    textEditQty.setColor(TEXT_DARK);
    textLabel.setColor(TEXT_DARK);
    invalidate();
}

void NumberField_Loc::setNextScan()
{
    cursorPos = 0;
    setEdit(false);
}
