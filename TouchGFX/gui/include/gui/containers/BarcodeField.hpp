#ifndef BARCODEFIELD_HPP
#define BARCODEFIELD_HPP

#include <gui_generated/containers/BarcodeFieldBase.hpp>
#include <gui/common/FocusableIetm.hpp>
#include <gui/common/Barcode.hpp>
#include <gui/common/EditableBarcode.hpp>

class BarcodeField : public BarcodeFieldBase, public FocusableIetm
{
public:
    BarcodeField();
    virtual ~BarcodeField() {}

    virtual void initialize();
    void setText(char * string);
    virtual bool setFocus(bool selected);
    void setFocusable (bool setting);
    bool isFocusable () { return Focusable;}
    void setEdit(bool enableEdit);
    bool isEditing() { return editing;}
    void insCh(char ch);
    void insStr(char *str);
    void delCh();
    void modifyCh(char ch);
    void moveCursorLeft();
    void moveCursorRight();
    char * getText();
    void setCue();
    void setNextScan();

protected:

private:
    static const touchgfx::Unicode::UnicodeChar ELLIPSIS = 0x2026;
    Barcode barcode;
    EditableBarcode editablebarcode;
    bool Focusable;
    bool editing;
    bool maxBarcodeSize;
    uint8_t cursorPos;
    int16_t cursorPos_Y;
    int16_t cursorPos_X[TEXT_SIZE + 1];

    void showText();
};

#endif // BARCODEFIELD_HPP
