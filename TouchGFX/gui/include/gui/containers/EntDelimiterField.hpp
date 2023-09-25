#ifndef ENTDELIMITERFIELD_HPP
#define ENTDELIMITERFIELD_HPP

#include <gui_generated/containers/EntDelimiterFieldBase.hpp>
#include <gui/common/FocusableIetm.hpp>

class EntDelimiterField : public EntDelimiterFieldBase, public FocusableIetm
{
public:
    EntDelimiterField();
    virtual ~EntDelimiterField() {}

    virtual void initialize();
    virtual bool setFocus(bool selected);
    void setEdit(bool enableEdit);
    bool isEditing();
    void insCh(char ch);
    void delCh();
    void modifyCh(char ch);
    void moveCursorLeft();
    void moveCursorRight();
    char getText();
    void setNextScan();

protected:
    static const uint16_t CHAR_W = 19;
    static const uint8_t MAX_FIELD_SIZE = 2;
    char textBuffer[MAX_FIELD_SIZE];
    bool editing;
    bool maxStrSize;
    uint8_t cursorPos;

    void showText();
};

#endif // ENTDELIMITERFIELD_HPP
