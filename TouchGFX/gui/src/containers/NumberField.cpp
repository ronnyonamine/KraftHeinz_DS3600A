#include <gui/containers/NumberField.hpp>
#include <gui/common/ColorPalette.hpp>
#include <string>
#include <stdlib.h>

NumberField::NumberField() :
    Focusable(true),
    editing(false),
    cursorPos(0)
{
    textBuffer[0] = '1';
    textBuffer[1] = '\0';
}

void NumberField::initialize()
{
    NumberFieldBase::initialize();
}

bool NumberField::setFocus(bool selected)
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

void NumberField::setEdit(bool enableEdit)
{
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

void NumberField::insCh(char ch)
{
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

void NumberField::delCh()
{
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

void NumberField::moveCursorLeft()
{
    std::string str;
    str.assign(textBuffer);
    if (cursorPos > 0)
    {
        cursorPos--;
        boxCursor.moveTo(304 - (str.size() - cursorPos) * CHAR_W, boxCursor.getY());
        boxCursor.invalidate();
    }
}

void NumberField::moveCursorRight()
{
    std::string str;
    str.assign(textBuffer);
    if (cursorPos < str.size())
    {
        cursorPos++;
        boxCursor.moveTo(304 - (str.size() - cursorPos) * CHAR_W, boxCursor.getY());
        boxCursor.invalidate();
    }
}

uint16_t NumberField::getNumber()
{
    return atoi(textBuffer);
}

void NumberField::showText()
{
    Unicode::strncpy(textEditQtyBuffer, textBuffer, MAX_FIELD_SIZE);
    textEditQty.invalidate();
}

void NumberField::setCue()
{
    boxBackGnd.setColor(TEXT_LIGHT);
    textEditQty.setColor(TEXT_DARK);
    textLabel.setColor(TEXT_DARK);
    invalidate();
}

void NumberField::setNextScan()
{
    cursorPos = 0;
    setEdit(false);
}
