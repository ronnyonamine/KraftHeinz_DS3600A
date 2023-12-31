/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/UnexpectFieldBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

UnexpectFieldBase::UnexpectFieldBase()
{
    setWidth(320);
    setHeight(64);
    boxBackGnd.setPosition(0, 0, 320, 64);
    boxBackGnd.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));

    textLabel.setPosition(16, 13, 117, 39);
    textLabel.setColor(touchgfx::Color::getColorFrom24BitRGB(46, 46, 46));
    textLabel.setLinespacing(0);
    textLabel.setTypedText(touchgfx::TypedText(T_RESOURCEID20));

    textUnexpect.setPosition(133, 8, 171, 48);
    textUnexpect.setColor(touchgfx::Color::getColorFrom24BitRGB(46, 46, 46));
    textUnexpect.setLinespacing(0);
    Unicode::snprintf(textUnexpectBuffer, TEXTUNEXPECT_SIZE, "%s", touchgfx::TypedText(T_RESOURCEID21).getText());
    textUnexpect.setWildcard(textUnexpectBuffer);
    textUnexpect.setTypedText(touchgfx::TypedText(T_RESOURCEID6));

    add(boxBackGnd);
    add(textLabel);
    add(textUnexpect);
}

void UnexpectFieldBase::initialize()
{

}
