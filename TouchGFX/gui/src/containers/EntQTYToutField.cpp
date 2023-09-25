#include <gui/containers/EntQTYToutField.hpp>
#include <gui/common/ColorPalette.hpp>
#include <string>
#include <stdlib.h>

EntQTYToutField::EntQTYToutField() :
    textBuffer(""),
    editing(false),
    cursorPos(0)
{
    boxCursor.setVisible(false);
}

void EntQTYToutField::initialize()
{
    EntQTYToutFieldBase::initialize();
}

bool EntQTYToutField::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        textLabel.setColor(TEXT_LIGHT);
        textTime.setColor(TEXT_LIGHT);
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textLabel.setColor(TEXT_MEDIUM);
        textTime.setColor(TEXT_MEDIUM);
    }
    invalidate();
    return (true);
}

void EntQTYToutField::setEdit(bool enableEdit)
{
    if (enableEdit)
    {
        boxCursor.setVisible(true);
        textTime.setAlpha(255);
    }
    else
    {
        if (atoi(textBuffer) > 60)
        {
            std::string str;
            str.assign("60");
            std::size_t length = str.copy(textBuffer, MAX_FIELD_SIZE);
            textBuffer[length] = '\0';
        }
        boxCursor.setVisible(false);
        textTime.setAlpha(153);
    }
    Unicode::strncpy(textTimeBuffer, textBuffer, MAX_FIELD_SIZE);
    invalidate();
    editing = enableEdit;
}

bool EntQTYToutField::isEditing()
{
    return (editing);
}

void EntQTYToutField::insCh(char ch)
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

void EntQTYToutField::delCh()
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

void EntQTYToutField::moveCursorLeft()
{
    if (cursorPos > 0)
    {
        cursorPos--;
        boxCursor.moveTo(boxCursor.getX() - CHAR_W, boxCursor.getY());
        boxCursor.invalidate();
    }
}

void EntQTYToutField::moveCursorRight()
{
    std::string str;
    str.assign(textBuffer);
    if (cursorPos < str.size())
    {
        cursorPos++;
        boxCursor.moveTo(boxCursor.getX() + CHAR_W, boxCursor.getY());
        boxCursor.invalidate();
    }
}

uint8_t EntQTYToutField::getText()
{
    return atoi(textBuffer);
}

void EntQTYToutField::showText()
{
    Unicode::strncpy(textTimeBuffer, textBuffer, MAX_FIELD_SIZE);
    textTime.invalidate();
}
