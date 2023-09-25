#ifndef NUMBERFIELD_LOC_HPP
#define NUMBERFIELD_LOC_HPP

#include <gui_generated/containers/NumberField_LocBase.hpp>
#include <gui/common/FocusableIetm.hpp>

class NumberField_Loc : public NumberField_LocBase, public FocusableIetm
{
public:
    NumberField_Loc();
    virtual ~NumberField_Loc() {}

    virtual void initialize();
    virtual bool setFocus(bool selected);
    void setEditable (bool setting) { editable = setting;}
    bool isEditable () { return editable;}
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
    bool editable;
    bool editing;
    uint8_t cursorPos;

    void showText();
};

#endif // NUMBERFIELD_LOC_HPP
