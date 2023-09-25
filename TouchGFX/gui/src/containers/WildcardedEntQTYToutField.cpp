#include <gui/containers/WildcardedEntQTYToutField.hpp>
#include <gui/common/ColorPalette.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <string>

WildcardedEntQTYToutField::WildcardedEntQTYToutField():
   textBuffer(""),
   editing(false),
   maxStrSize(false),
   cursorPos(0)
{
	boxCursor.setVisible(false);
}

void WildcardedEntQTYToutField::initialize()
{
    WildcardedEntQTYToutFieldBase::initialize();
}


bool WildcardedEntQTYToutField::setFocus(bool selected)
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


void WildcardedEntQTYToutField::setEdit(bool enableEdit)
{
    if (enableEdit)
    {
        boxCursor.setVisible(true);
        textTime.setAlpha(255);
        int length = strlen(textBuffer);
        if(cursorPos > length)
        {
          while(cursorPos != length)
          {
            cursorPos--;
            boxCursor.moveTo(boxCursor.getX() - CHAR_W, boxCursor.getY());
            boxCursor.invalidate();
          }
        }

        if((cursorPos == 0) && (cursorPos != length))
        {
          while(cursorPos != length)
          {
            cursorPos++;
            boxCursor.moveTo(boxCursor.getX() + CHAR_W, boxCursor.getY());
            boxCursor.invalidate();
          }
        }
    }
    else
    {
        boxCursor.setVisible(false);
        textTime.setAlpha(153);
    }
    Unicode::strncpy(textTimeBuffer, textBuffer, MAX_FIELD_SIZE);
    invalidate();
    editing = enableEdit;
}

bool WildcardedEntQTYToutField::isEditing()
{
    return (editing);
}


void WildcardedEntQTYToutField::insNumber(uint32_t number)
{
  std::string str = std::to_string(number);
  
  std::size_t length = str.copy(textBuffer, str.length());
  textBuffer[length] = '\0';
  
  Unicode::strncpy(textTimeBuffer, textBuffer, MAX_FIELD_SIZE);
  invalidate();
}

void WildcardedEntQTYToutField::insDigit(char ch)
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

void WildcardedEntQTYToutField::delDigit()
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

void WildcardedEntQTYToutField::modifyDigit(char ch)
{
    if (!maxStrSize)
    {
        textBuffer[cursorPos - 1] = ch;
        showText();
    }
}

void WildcardedEntQTYToutField::moveCursorLeft()
{
    if (cursorPos > 0)
    {
        cursorPos--;
        boxCursor.moveTo(boxCursor.getX() - CHAR_W, boxCursor.getY());
        boxCursor.invalidate();
    }
}


void WildcardedEntQTYToutField::moveCursorRight()
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

uint32_t WildcardedEntQTYToutField::getText()
{
    return atoi(textBuffer);
}

void WildcardedEntQTYToutField::showText()
{
    Unicode::strncpy(textTimeBuffer, textBuffer, MAX_FIELD_SIZE);
    textTime.invalidate();
}

void WildcardedEntQTYToutField::setNextScan()
{
    textBuffer[0] = '\0';
    cursorPos = 0;
    boxCursor.setPosition(16, 38, 1, 42);
    showText();
    setEdit(false);
    Unicode::snprintf(textTimeBuffer, TEXTTIME_SIZE, "%s", touchgfx::TypedText(T_RESOURCEID17).getText());
}

bool WildcardedEntQTYToutField::setLabel(const std::string label)
{
  if(label.length() > TEXTLABEL_SIZE)
  {
    return false;
  }
  /* Add Null termination */
  Unicode::strncpy(textLabelBuffer, label.c_str(), (uint16_t)label.length());
  textLabel.resizeToCurrentText();
  invalidate();
  return true;
}

bool WildcardedEntQTYToutField::setDefaultText(std::string text)
{
  if(text.length() > TEXTTIME_SIZE)
  {
    return false;
  }
  Unicode::strncpy(textTimeBuffer, text.c_str(), (uint16_t)text.length());
  invalidate();
  return true;
}

void WildcardedEntQTYToutField::setTextORVisible(bool visible)
{
    textOR.setVisible(visible);
}
