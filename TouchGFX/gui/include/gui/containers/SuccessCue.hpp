#ifndef SUCCESSCUE_HPP
#define SUCCESSCUE_HPP

#include <gui_generated/containers/SuccessCueBase.hpp>
#include <gui/common/ColorPalette.hpp>

class SuccessCue : public SuccessCueBase
{
public:
    SuccessCue();
    virtual ~SuccessCue() {}

    virtual void initialize();
    void setCueColor(colortype colorSetting = STATES_SUCCESS);

protected:

};

#endif // SUCCESSCUE_HPP
