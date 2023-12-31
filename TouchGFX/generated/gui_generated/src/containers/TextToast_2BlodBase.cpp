/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/TextToast_2BlodBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

TextToast_2BlodBase::TextToast_2BlodBase()
{
    setWidth(288);
    setHeight(48);
    boxBackGnd.setPosition(0, 0, 288, 48);
    boxBackGnd.setColor(touchgfx::Color::getColorFrom24BitRGB(46, 46, 46));

    textRegular.setPosition(0, 10, 288, 29);
    textRegular.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textRegular.setLinespacing(0);
    textRegular.setTypedText(touchgfx::TypedText(T_TOAST2B_01));

    textBlod_1.setPosition(7, 10, 39, 29);
    textBlod_1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textBlod_1.setLinespacing(0);
    textBlod_1.setTypedText(touchgfx::TypedText(T_TOAST2B_01_B1));

    textBlod_2.setPosition(130, 10, 53, 29);
    textBlod_2.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textBlod_2.setLinespacing(0);
    textBlod_2.setTypedText(touchgfx::TypedText(T_TOAST2B_01_B2));

    add(boxBackGnd);
    add(textRegular);
    add(textBlod_1);
    add(textBlod_2);
}

void TextToast_2BlodBase::initialize()
{

}
