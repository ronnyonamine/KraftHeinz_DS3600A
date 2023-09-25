#ifndef BTNBACK_HPP
#define BTNBACK_HPP

#include <gui_generated/containers/BtnBackBase.hpp>
#include <gui/common/FocusableIetm.hpp>

class BtnBack : public BtnBackBase, public FocusableIetm
{
public:
    BtnBack();
    virtual ~BtnBack() {}

    virtual void initialize();
    virtual bool setFocus(bool selected);
    bool isFocusing() { return focusing;}

protected:

private:
    bool focusing;
};

#endif // BTNBACK_HPP
