/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/KhMenuBase.hpp>
#include <touchgfx/Color.hpp>

KhMenuBase::KhMenuBase()
{
    setWidth(320);
    setHeight(155);
    boxBackGnd.setPosition(0, 0, 320, 155);
    boxBackGnd.setColor(touchgfx::Color::getColorFrom24BitRGB(162, 202, 250));

    listLayout1.setDirection(touchgfx::SOUTH);
    listLayout1.setPosition(35, 27, 250, 250);

    add(boxBackGnd);
    add(listLayout1);
}

void KhMenuBase::initialize()
{

}
