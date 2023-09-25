/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/khLearnBarcodeBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

khLearnBarcodeBase::khLearnBarcodeBase()
{
    setWidth(320);
    setHeight(155);
    boxBackGnd.setPosition(0, 0, 320, 155);
    boxBackGnd.setColor(touchgfx::Color::getColorFrom24BitRGB(162, 202, 250));

    textArea1.setXY(40, 22);
    textArea1.setColor(touchgfx::Color::getColorFrom24BitRGB(10, 50, 165));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID87));

    textArea2.setXY(40, 46);
    textArea2.setColor(touchgfx::Color::getColorFrom24BitRGB(10, 50, 165));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T_SINGLEUSEID88));

    add(boxBackGnd);
    add(textArea1);
    add(textArea2);
}

void khLearnBarcodeBase::initialize()
{

}
