#ifndef WILDCARDEDCHARENTRYFIELD_HPP
#define WILDCARDEDCHARENTRYFIELD_HPP

#include <gui_generated/containers/WildcardedCharEntryFieldBase.hpp>
#include <gui/common/FocusableIetm.hpp>
#include <gui/common/EditableBarcode.hpp>
#include <string>

class WildcardedCharEntryField : public WildcardedCharEntryFieldBase, public FocusableIetm
{
public:
    WildcardedCharEntryField();
    virtual ~WildcardedCharEntryField() {}

    virtual void initialize();
	virtual bool setFocus(bool selected);
    void setEdit(bool enableEdit);
    bool isEditing();
    void insCh(char ch);
    void delCh();
    void modifyCh(char ch);
    void moveCursorLeft();
    void moveCursorRight();
    char* getText();
    void setNextScan();
    void clearText();
    void setLabel(const std::string label);
    void setDefaultText(std::string text);
    void setTextORVisible(bool visible);
    void setText(std::string text);

protected:
    static const touchgfx::Unicode::UnicodeChar ELLIPSIS = 0x2026;
    EditableBarcode textBuffer;
    static const uint16_t CHAR_W = 19;
    static const uint8_t MAX_FIELD_SIZE = 100;
    static const uint8_t DISP_STR_MAX = 15;
    //char textBuffer[MAX_FIELD_SIZE];
    bool editing;
    bool maxStrSize;
    uint8_t cursorPos;
    int16_t cursorPos_Y;
    int16_t cursorPos_X[DISP_STR_MAX + 1];

    void showText();
protected:
};

#endif // WILDCARDEDCHARENTRYFIELD_HPP
