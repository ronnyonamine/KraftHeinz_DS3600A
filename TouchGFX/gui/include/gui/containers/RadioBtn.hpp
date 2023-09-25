#ifndef RADIOBTN_HPP
#define RADIOBTN_HPP

#include <gui_generated/containers/RadioBtnBase.hpp>
#include <gui/common/FocusableIetm.hpp>

class RadioBtn : public RadioBtnBase, public FocusableIetm
{
public:
    RadioBtn();
    virtual ~RadioBtn() {}

    virtual void initialize();

    void setMenuText(touchgfx::TypedText textInactive, touchgfx::TypedText textActive);
    virtual bool setFocus(bool selected);
    virtual bool setRadioOn(bool on);

protected:
    bool bRadioOn;
};

#endif // RADIOBTN_HPP
