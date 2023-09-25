#include <gui/containers/WildcardedCharEntryField.hpp>
#include <gui/common/ColorPalette.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <string>

WildcardedCharEntryField::WildcardedCharEntryField():
    //textBuffer(""),
    textBuffer(MAX_FIELD_SIZE, DISP_STR_MAX),
    editing(false),
    maxStrSize(false),
    cursorPos(0)
{
    boxCursor.setVisible(false);
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

void WildcardedCharEntryField::initialize()
{
    WildcardedCharEntryFieldBase::initialize();
    textBuffer.setContent("");
    cursorPos_Y = boxCursor.getY();
}

bool WildcardedCharEntryField::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        textLabel.setColor(TEXT_LIGHT);
        textCharacter.setColor(TEXT_LIGHT);
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textLabel.setColor(TEXT_MEDIUM);
        textCharacter.setColor(TEXT_MEDIUM);
    }
    invalidate();
    return (true);
}

void WildcardedCharEntryField::setDefaultText(std::string text)
{
    memset(textCharacterBuffer, 0x00, TEXTCHARACTER_SIZE);
    Unicode::strncpy(textCharacterBuffer, text.c_str(), (uint16_t)text.length()+1);
    invalidate();
}

void WildcardedCharEntryField::setText(std::string text)
{
    textBuffer.setContent(text);
    showText();
    invalidate();
}

void WildcardedCharEntryField::setEdit(bool enableEdit)
{
    if (enableEdit)
    {   
        boxCursor.setVisible(true);
        textCharacter.setAlpha(255);
        /*
        int length = strlen(textBuffer);
        if(cursorPos > length)
        {
          while(cursorPos != length)
          {
            cursorPos--;
            //boxCursor.moveTo(boxCursor.getX() - CHAR_W, boxCursor.getY());
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
        */
    }
    else
    {
        boxCursor.setVisible(false);
        textCharacter.setAlpha(153);
    }
    //Unicode::strncpy(textCharacterBuffer, textBuffer, MAX_FIELD_SIZE);
    Unicode::strncpy(textCharacterBuffer,textBuffer.getEWContent().c_str(), TEXTCHARACTER_SIZE);
    boxCursor.moveTo(cursorPos_X[DISP_STR_MAX], cursorPos_Y);               //added new
    invalidate();
    editing = enableEdit;
}

bool WildcardedCharEntryField::isEditing()
{
    return (editing);
}

void WildcardedCharEntryField::insCh(char ch)
{
    /*
    if (maxStrSize)
        return;
    std::string str;
    //str.assign(textBuffer);
    textBuffer.appendChar(ch);
    showText();
    */

    maxStrSize = textBuffer.isMaxContent();
    if (!maxStrSize)
    { 
        textBuffer.appendChar(ch);
        showText();
    }

    /*
    
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
    */
}


void WildcardedCharEntryField::delCh()
{
    textBuffer.removeChar();
    showText();
    maxStrSize = false;
    /*
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
    */
}

void WildcardedCharEntryField::modifyCh(char ch)
{
    /*
    if (!maxStrSize)
    {
      if(cursorPos == 0)
      {
        textBuffer[cursorPos] = ch;
      }
      else
      {
        textBuffer[cursorPos - 1] = ch;
      }
      showText();
    }
    */

    if (!maxStrSize)
    {
        textBuffer.modifyChar(ch);
        showText();
    }
}

void WildcardedCharEntryField::moveCursorLeft()
{
    textBuffer.shiftCursorLeft();
    showText();
    /*
    if (cursorPos > 0)
    {
        cursorPos--;
        boxCursor.moveTo(boxCursor.getX() - CHAR_W, boxCursor.getY());
        boxCursor.invalidate();
        
    }
    */
}

void WildcardedCharEntryField::moveCursorRight()
{
    textBuffer.shiftCursorRight();
    showText();
    /*
    std::string str;
    str.assign(textBuffer);
    if (cursorPos < str.size())
    {
      cursorPos++;
      boxCursor.moveTo(boxCursor.getX() + CHAR_W, boxCursor.getY());
      boxCursor.invalidate();
    }
    */
}

char* WildcardedCharEntryField::getText()
{
    return textBuffer.getContent();
}

void WildcardedCharEntryField::showText()
{
    Unicode::strncpy(textCharacterBuffer, textBuffer.getEWContent().c_str(), TEXTCHARACTER_SIZE);

    if (textBuffer.isRightMore())
    { 
        textCharacterBuffer[DISP_STR_MAX - 1] = ELLIPSIS;
    }
    if (textBuffer.isLeftMore())
    { 
        textCharacterBuffer[0] = ELLIPSIS;
    }
    textCharacter.invalidate();

    boxCursor.moveTo(cursorPos_X[textBuffer.getEWCursorPos()], cursorPos_Y);   //from function keys

    boxCursor.invalidate();
}

void WildcardedCharEntryField::clearText()
{
    //memset(textBuffer, 0x00, MAX_FIELD_SIZE);
    textBuffer.setContent("");
    memcpy(textCharacterBuffer, textBuffer.getEWContent().c_str(), TEXTCHARACTER_SIZE);
    textCharacter.invalidate();
}

void WildcardedCharEntryField::setNextScan()
{
    //textBuffer[0] = '\0';
    textBuffer.setContent("");
    cursorPos = 0;
    boxCursor.setPosition(16, 38, 1, 42);
    showText();
    setEdit(false);
    //Unicode::snprintf(textCharacterBuffer, TEXTCHARACTER_SIZE, "%s", touchgfx::TypedText(T_RESOURCEID17).getText());
}

void WildcardedCharEntryField::setLabel(const std::string label)
{
    /* We need to transform ASCII array to unicode. In C++,
     * transform an uint8_t array to uint16_t
     */
    Unicode::UnicodeChar unicode_text[20];
	
    for(uint8_t i = 0; i < label.size() + 1; i++)
    {
        unicode_text[i] = label[i];
    }
    Unicode::snprintf(textCharacterBuffer, label.size() + 1, "%s", unicode_text);
	
    textCharacter.resizeToCurrentText();
    textCharacter.invalidate();
}void WildcardedCharEntryField::setTextORVisible(bool visible)
{
    textOR.setVisible(visible);
}
