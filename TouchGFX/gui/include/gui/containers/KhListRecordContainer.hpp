#ifndef KHLISTRECORDCONTAINER_HPP
#define KHLISTRECORDCONTAINER_HPP

#include <gui_generated/containers/KhListRecordContainerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/FocusableIetm.hpp>
#include <gui/common/EditableBarcode.hpp>
#include <string>

class KhListRecordContainer : public KhListRecordContainerBase
{
public:
    KhListRecordContainer();
    virtual ~KhListRecordContainer() {}

    virtual void initialize();

    void setupListElements(string date, string time, string learnbarcode, string verifybarcode, string success, string reason, string initials);
    void setDefaultDate(std::string text);
    void setDefaultTime(std::string text);
    void setDefaultLearnBarcode(std::string text);
    void setDefaultVerifyBarcode(std::string text);
    void setDefaultSuccess(std::string text);
    void setDefaultReason(std::string text);
    void setDefaultInitials(std::string text);
    void selectThis();
    void deselectThis();
    void setAsHeader();
protected:
    static const touchgfx::Unicode::UnicodeChar ELLIPSIS = 0x2026;
    static const uint8_t KEY_STR_MAX = 20;
    static const uint8_t DISP_KEY_STR_MAX = KEY_STR_MAX - 1;
    EditableBarcode textBuffer;
    EditableBarcode textBuffer1;
    EditableBarcode textBuffer2;
    EditableBarcode textBuffer3;
    EditableBarcode textBuffer4;
    EditableBarcode textBuffer5;
    EditableBarcode textBuffer6;
    bool editing;
    bool maxStrSize;
    int16_t cursorPos_Y;
    int16_t cursorPos_X[DISP_KEY_STR_MAX + 1];

    void showText();
};

#endif // KHLISTRECORDCONTAINER_HPP
