#ifndef LOCATIONFIELD_LOC_HPP
#define LOCATIONFIELD_LOC_HPP

#include <gui_generated/containers/LocationField_LocBase.hpp>
#include <gui/common/ColorPalette.hpp>
#include <gui/common/FocusableIetm.hpp>
#include <gui/common/EditableBarcode.hpp>

class LocationField_Loc : public LocationField_LocBase, public FocusableIetm
{
public:
    LocationField_Loc();
    virtual ~LocationField_Loc() {}

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
    void setCue(colortype colorSetting = PRIMARY_BLUE);
    void setNextScan();

protected:

private:
    static const touchgfx::Unicode::UnicodeChar ELLIPSIS = 0x2025;
    static const uint8_t LOC_FIELD_MAX = 20;
    static const uint8_t DISP_LOC_FIELD_MAX = TEXTBARCODE_SIZE - 1;
    EditableBarcode editablebarcode;
    bool editable;
    bool editing;
    bool maxBarcodeSize;
    int16_t cursorPos_Y;
    int16_t cursorPos_X[DISP_LOC_FIELD_MAX + 1];

    void showText();
};

#endif // LOCATIONFIELD_LOC_HPP
