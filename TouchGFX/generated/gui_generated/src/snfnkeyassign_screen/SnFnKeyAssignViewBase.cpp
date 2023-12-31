/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/snfnkeyassign_screen/SnFnKeyAssignViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

SnFnKeyAssignViewBase::SnFnKeyAssignViewBase()
{

    ccBackGnd.setXY(0, 0);

    ccStatusBar.setXY(0, 0);

    ccBack.setXY(0, 0);

    cccfgMenuToast.setXY(16, 0);
    cccfgMenuToast.setVisible(false);

    scrollCnt.setPosition(0, 48, 320, 192);
    scrollCnt.enableHorizontalScroll(false);
    scrollCnt.setScrollbarsColor(touchgfx::Color::getColorFrom24BitRGB(142, 142, 142));

    listLayout.setDirection(touchgfx::SOUTH);
    listLayout.setXY(0, 3);

    listLayout.add(ccEntStrField);
    scrollCnt.add(listLayout);
    scrollCnt.setScrollbarsPermanentlyVisible();
    scrollCnt.setScrollbarsVisible(false);

    cView.setPosition(0, 48, 320, 192);

    boxBackGnd.setPosition(0, 0, 320, 192);
    boxBackGnd.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    cView.add(boxBackGnd);

    textNormal.setPosition(16, 0, 288, 64);
    textNormal.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textNormal.setLinespacing(0);
    textNormal.setTypedText(touchgfx::TypedText(T_TEXTVIEW_00));
    cView.add(textNormal);

    textFnKey.setPosition(60, 0, 25, 32);
    textFnKey.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textFnKey.setLinespacing(0);
    textFnKey.setTypedText(touchgfx::TypedText(T_KEYASSIGNVIEW_F0));
    cView.add(textFnKey);

    textKeyAssigned.setPosition(16, 64, 288, 32);
    textKeyAssigned.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textKeyAssigned.setLinespacing(0);
    Unicode::snprintf(textKeyAssignedBuffer, TEXTKEYASSIGNED_SIZE, "%s", touchgfx::TypedText(T_KEYASSIGNVIEW_UNASSIGNED).getText());
    textKeyAssigned.setWildcard(textKeyAssignedBuffer);
    textKeyAssigned.setTypedText(touchgfx::TypedText(T_TEXTVIEW_01));
    cView.add(textKeyAssigned);

    labelContinue.setPosition(169, 148, 93, 32);
    labelContinue.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelContinue.setLinespacing(0);
    labelContinue.setTypedText(touchgfx::TypedText(T_LABEL_CONTINUE));
    cView.add(labelContinue);

    labelENT.setPosition(270, 155, 33, 25);
    labelENT.setColor(touchgfx::Color::getColorFrom24BitRGB(142, 142, 142));
    labelENT.setLinespacing(0);
    labelENT.setTypedText(touchgfx::TypedText(T_SUBLABEL_ENT));
    cView.add(labelENT);

    add(ccBackGnd);
    add(ccStatusBar);
    add(ccBack);
    add(cccfgMenuToast);
    add(scrollCnt);
    add(cView);
}

void SnFnKeyAssignViewBase::setupScreen()
{
    ccBackGnd.initialize();
    ccStatusBar.initialize();
    ccBack.initialize();
    cccfgMenuToast.initialize();
    ccEntStrField.initialize();
}
