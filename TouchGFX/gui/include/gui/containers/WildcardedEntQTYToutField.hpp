#ifndef WILDCARDEDENTQTYTOUTFIELD_HPP
#define WILDCARDEDENTQTYTOUTFIELD_HPP

#include <gui_generated/containers/WildcardedEntQTYToutFieldBase.hpp>
#include <gui/common/FocusableIetm.hpp>
#include <string>

class WildcardedEntQTYToutField : public WildcardedEntQTYToutFieldBase, public FocusableIetm
{
public:
    WildcardedEntQTYToutField();
    virtual ~WildcardedEntQTYToutField() {}

    virtual void initialize();
    bool setFocus(bool selected) override;
    void setEdit(bool enableEdit);
    bool isEditing();
    void insNumber(uint32_t number);
    void insDigit(char ch);
    void delDigit();
    void modifyDigit(char ch);
    void moveCursorLeft();
    void moveCursorRight();
    uint32_t getText();
    void setNextScan();
    bool setLabel(const std::string label);
    bool setDefaultText(std::string text);
    void setTextORVisible(bool visible);

protected:
protected:
    static const uint16_t CHAR_W = 19;
    static const uint8_t MAX_FIELD_SIZE = 11; /* max for uint32_t */
    char textBuffer[MAX_FIELD_SIZE];
    bool editing;
	bool maxStrSize;
    uint8_t cursorPos;

    void showText();
};

#endif // WILDCARDEDENTQTYTOUTFIELD_HPP
