#ifndef BARCODEFIELD_LOC_HPP
#define BARCODEFIELD_LOC_HPP

#include <gui_generated/containers/BarcodeField_LocBase.hpp>
#include <gui/common/FocusableIetm.hpp>
#include <gui/common/Barcode.hpp>
#include <gui/common/EditableBarcode.hpp>

class BarcodeField_Loc : public BarcodeField_LocBase, public FocusableIetm
{
public:
    BarcodeField_Loc();
    virtual ~BarcodeField_Loc() {}

    virtual void initialize();
    void setText(char * string);
    virtual bool setFocus(bool selected);
    void setEditable (bool setting);
    bool isEditable () { return editable;}
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
    bool editable;
    bool editing;
    bool maxBarcodeSize;
    int16_t cursorPos_Y;
    int16_t cursorPos_X[TEXT_SIZE + 1];

    void showText();
};

#endif // BARCODEFIELD_LOC_HPP
