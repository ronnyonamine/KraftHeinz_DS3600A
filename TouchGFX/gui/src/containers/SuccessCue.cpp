#include <gui/containers/SuccessCue.hpp>

SuccessCue::SuccessCue()
{

}

void SuccessCue::initialize()
{
    SuccessCueBase::initialize();
}

void SuccessCue::setCueColor(colortype colorSetting)
{
    box1.setColor(colorSetting);
    box2.setColor(colorSetting);
    box3.setColor(colorSetting);
    box4.setColor(colorSetting);
    invalidate();
}
