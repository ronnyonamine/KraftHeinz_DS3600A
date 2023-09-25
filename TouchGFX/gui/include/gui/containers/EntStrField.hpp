#ifndef ENTSTRFIELD_HPP
#define ENTSTRFIELD_HPP

#include <gui_generated/containers/EntStrFieldBase.hpp>
#include <gui/common/FocusableIetm.hpp>
#include <gui/common/EditableBarcode.hpp>
#include <string>

class EntStrField : public EntStrFieldBase, public FocusableIetm
{
public:
    EntStrField();
    virtual ~EntStrField() {}

    virtual void initialize();
    virtual bool setFocus(bool selected);
    void setEdit(bool enableEdit);
    bool isEditing() { return editing;}
    void insCh(char ch);
    void delCh();
    void modifyCh(char ch);
    void moveCursorLeft();
    void moveCursorRight();
    char * getText();
    void setNextScan();
    void setDefaultText(std::string text);

protected:
    static const touchgfx::Unicode::UnicodeChar ELLIPSIS = 0x2026;
    static const uint8_t KEY_STR_MAX = 20;
    static const uint8_t DISP_KEY_STR_MAX = TEXTFNKEYSTR_SIZE - 1;
    EditableBarcode textBuffer;
    bool editing;
    bool maxStrSize;
    int16_t cursorPos_Y;
    int16_t cursorPos_X[DISP_KEY_STR_MAX + 1];

    void showText();
};

#endif // ENTSTRFIELD_HPP
