#ifndef ENTQTYTOUTFIELD_HPP
#define ENTQTYTOUTFIELD_HPP

#include <gui_generated/containers/EntQTYToutFieldBase.hpp>
#include <gui/common/FocusableIetm.hpp>

class EntQTYToutField : public EntQTYToutFieldBase, public FocusableIetm
{
public:
    EntQTYToutField();
    virtual ~EntQTYToutField() {}

    virtual void initialize();
    virtual bool setFocus(bool selected);
    void setEdit(bool enableEdit);
    bool isEditing();
    void insCh(char ch);
    void delCh();
    void moveCursorLeft();
    void moveCursorRight();
    uint8_t getText();

protected:
    static const uint16_t CHAR_W = 19;
    static const uint8_t MAX_FIELD_SIZE = 3;
    char textBuffer[MAX_FIELD_SIZE];
    bool editing;
    uint8_t cursorPos;

    void showText();
};

#endif // ENTQTYTOUTFIELD_HPP
