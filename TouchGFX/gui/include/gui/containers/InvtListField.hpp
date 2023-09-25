#ifndef INVTLISTFIELD_HPP
#define INVTLISTFIELD_HPP

#include <gui_generated/containers/InvtListFieldBase.hpp>

class InvtListField : public InvtListFieldBase
{
public:
    InvtListField();
    virtual ~InvtListField() {}

    virtual void initialize();
    void setFocus(bool selected);
    void setText(bool isEllipsis, char* bc_s, char* bc_l, uint16_t qty);

protected:
    static const touchgfx::Unicode::UnicodeChar ELLIPSIS = 0x2026;

};

#endif // INVTLISTFIELD_HPP
