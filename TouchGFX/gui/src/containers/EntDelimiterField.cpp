#include <gui/containers/EntDelimiterField.hpp>
#include <gui/common/ColorPalette.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <string>

EntDelimiterField::EntDelimiterField() :
    textBuffer(""),
    editing(false),
    maxStrSize(false),
    cursorPos(0)
{
    boxCursor.setVisible(false);
}

void EntDelimiterField::initialize()
{
    EntDelimiterFieldBase::initialize();
}

bool EntDelimiterField::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        textLabel.setColor(TEXT_LIGHT);
        textDelimiter.setColor(TEXT_LIGHT);
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textLabel.setColor(TEXT_MEDIUM);
        textDelimiter.setColor(TEXT_MEDIUM);
    }
    invalidate();
    return (true);
}

void EntDelimiterField::setEdit(bool enableEdit)
{
    if (enableEdit)
    {
        boxCursor.setVisible(true);
        textDelimiter.setAlpha(255);
    }
    else
    {
        boxCursor.setVisible(false);
        textDelimiter.setAlpha(153);
    }
    Unicode::strncpy(textDelimiterBuffer, textBuffer, MAX_FIELD_SIZE);
    invalidate();
    editing = enableEdit;
}

bool EntDelimiterField::isEditing()
{
    return (editing);
}

void EntDelimiterField::insCh(char ch)
{
    if (maxStrSize)
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
    else
    {
        maxStrSize = true;
    }
}

void EntDelimiterField::delCh()
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
            maxStrSize = false;
        } 
    }
}

void EntDelimiterField::modifyCh(char ch)
{
    if (!maxStrSize)
    {
        textBuffer[cursorPos - 1] = ch;
        showText();
    }
}

void EntDelimiterField::moveCursorLeft()
{
    if (cursorPos > 0)
    {
        cursorPos--;
        boxCursor.moveTo(boxCursor.getX() - CHAR_W, boxCursor.getY());
        boxCursor.invalidate();
    }
}

void EntDelimiterField::moveCursorRight()
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

char EntDelimiterField::getText()
{
    return textBuffer[0];
}

void EntDelimiterField::showText()
{
    Unicode::strncpy(textDelimiterBuffer, textBuffer, MAX_FIELD_SIZE);
    textDelimiter.invalidate();
}

void EntDelimiterField::setNextScan()
{
    textBuffer[0] = '\0';
    cursorPos = 0;
    boxCursor.setPosition(16, 38, 1, 42);
    showText();
    setEdit(false);
    Unicode::snprintf(textDelimiterBuffer, TEXTDELIMITER_SIZE, "%s", touchgfx::TypedText(T_RESOURCEID17).getText());
}
