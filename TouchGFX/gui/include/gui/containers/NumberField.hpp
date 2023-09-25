#ifndef NUMBERFIELD_HPP
#define NUMBERFIELD_HPP

#include <gui_generated/containers/NumberFieldBase.hpp>
#include <gui/common/FocusableIetm.hpp>

class NumberField : public NumberFieldBase, public FocusableIetm
{
public:
    NumberField();
    virtual ~NumberField() {}

    virtual void initialize();
    virtual bool setFocus(bool selected);
    void setFocusable (bool setting) { Focusable = setting;}
    bool isFocusable () { return Focusable;}
    void setEdit(bool enableEdit);
    bool isEditing() { return editing;}
    void insCh(char ch);
    void delCh();
    void moveCursorLeft();
    void moveCursorRight();
    uint16_t getNumber();
    void setCue();
    void setNextScan();

protected:

private:
    static const uint16_t CHAR_W = 20;
    static const uint8_t MAX_FIELD_SIZE = 5;
    char textBuffer[MAX_FIELD_SIZE];
    bool Focusable;
    bool editing;
    uint8_t cursorPos;

    void showText();
};

#endif // NUMBERFIELD_HPP
