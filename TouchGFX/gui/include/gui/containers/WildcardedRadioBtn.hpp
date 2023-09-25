#ifndef WILDCARDEDRADIOBTN_HPP
#define WILDCARDEDRADIOBTN_HPP

#include <gui_generated/containers/WildcardedRadioBtnBase.hpp>
#include <string>
#include <gui/common/FocusableIetm.hpp>

class WildcardedRadioBtn : public WildcardedRadioBtnBase, public FocusableIetm
{
public:
    WildcardedRadioBtn();
    virtual ~WildcardedRadioBtn() {}
    
    void setText(std::string text);
    virtual bool setFocus(bool selected);
    virtual bool setRadioOn(bool on);
    
    virtual void initialize();
protected:
    bool bRadioOn;
};

#endif // WILDCARDEDRADIOBTN_HPP
