#ifndef INVTLISTFIELD_LOC_HPP
#define INVTLISTFIELD_LOC_HPP

#include <string>
#include <gui_generated/containers/InvtListField_LocBase.hpp>

class InvtListField_Loc : public InvtListField_LocBase
{
public:
    InvtListField_Loc();
    virtual ~InvtListField_Loc() {}

    virtual void initialize();
    void setFocus(bool selected);
    void setText(std::string location);

protected:
    static const touchgfx::Unicode::UnicodeChar ELLIPSIS = 0x2025;

};

#endif // INVTLISTFIELD_LOC_HPP
