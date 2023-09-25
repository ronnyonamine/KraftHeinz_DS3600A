/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/snoutinmatch_screen/SnOutInMatchViewBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"

SnOutInMatchViewBase::SnOutInMatchViewBase()
{

    ccBackGnd.setXY(0, 0);

    ccStatusBar.setXY(0, 0);

    labelList.setPosition(16, 197, 39, 32);
    labelList.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelList.setLinespacing(0);
    labelList.setTypedText(touchgfx::TypedText(T_LABEL_LIST));

    imgRight.setXY(55, 197);
    imgRight.setBitmap(touchgfx::Bitmap(BITMAP_RIGHT_ID));
    imgRight.setAlpha(102);

    labelDownInside.setPosition(144, 197, 123, 32);
    labelDownInside.setVisible(false);
    labelDownInside.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelDownInside.setLinespacing(0);
    labelDownInside.setTypedText(touchgfx::TypedText(T_LABEL_DONEINSIDE));

    labelDownOutside.setPosition(128, 197, 139, 32);
    labelDownOutside.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelDownOutside.setLinespacing(0);
    labelDownOutside.setTypedText(touchgfx::TypedText(T_LABEL_DONEOUTSIDE));

    labelENT.setPosition(271, 201, 33, 25);
    labelENT.setColor(touchgfx::Color::getColorFrom24BitRGB(142, 142, 142));
    labelENT.setLinespacing(0);
    labelENT.setTypedText(touchgfx::TypedText(T_SUBLABEL_ENT));

    ccNumberBC.setXY(0, 80);

    ccUnexpect.setXY(0, 122);
    ccUnexpect.setVisible(false);

    ccMatch.setXY(0, 54);
    ccMatch.setVisible(false);

    ccBarcode.setXY(0, 80);
    ccBarcode.setVisible(false);

    ccBack.setXY(0, 0);

    cOutsideView.setPosition(0, 0, 320, 240);

    boxBackGnd_OutView.setPosition(0, 48, 320, 192);
    boxBackGnd_OutView.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    cOutsideView.add(boxBackGnd_OutView);

    boxMark_OutView.setPosition(0, 0, 48, 48);
    boxMark_OutView.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    cOutsideView.add(boxMark_OutView);

    textN_OutView.setPosition(38, 56, 245, 128);
    textN_OutView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textN_OutView.setLinespacing(0);
    textN_OutView.setTypedText(touchgfx::TypedText(T_MATCHVIEW_01));
    cOutsideView.add(textN_OutView);

    textH1_OutView.setPosition(148, 56, 93, 32);
    textH1_OutView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH1_OutView.setLinespacing(0);
    textH1_OutView.setTypedText(touchgfx::TypedText(T_MATCHVIEW_01_H1));
    cOutsideView.add(textH1_OutView);

    textH2_OutView.setPosition(38, 88, 79, 32);
    textH2_OutView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH2_OutView.setLinespacing(0);
    textH2_OutView.setTypedText(touchgfx::TypedText(T_MATCHVIEW_01_H2));
    cOutsideView.add(textH2_OutView);

    textH3_OutView.setPosition(129, 120, 42, 32);
    textH3_OutView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH3_OutView.setLinespacing(0);
    textH3_OutView.setTypedText(touchgfx::TypedText(T_MATCHVIEW_01_H3));
    cOutsideView.add(textH3_OutView);

    textH4_OutView.setPosition(90, 152, 41, 32);
    textH4_OutView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH4_OutView.setLinespacing(0);
    textH4_OutView.setTypedText(touchgfx::TypedText(T_MATCHVIEW_01_H4));
    cOutsideView.add(textH4_OutView);

    labelInst_OutView.setPosition(16, 197, 113, 32);
    labelInst_OutView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelInst_OutView.setLinespacing(0);
    labelInst_OutView.setTypedText(touchgfx::TypedText(T_LABEL_INSTRUCTION));
    cOutsideView.add(labelInst_OutView);

    imgUp_OutView.setXY(128, 197);
    imgUp_OutView.setBitmap(touchgfx::Bitmap(BITMAP_UP_ID));
    imgUp_OutView.setAlpha(102);
    cOutsideView.add(imgUp_OutView);

    cInsideView.setPosition(0, 0, 320, 240);
    cInsideView.setVisible(false);

    boxBackGnd_InView.setPosition(0, 48, 320, 192);
    boxBackGnd_InView.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    cInsideView.add(boxBackGnd_InView);

    boxMark_InView.setPosition(0, 0, 48, 48);
    boxMark_InView.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    cInsideView.add(boxMark_InView);

    textN_InView.setPosition(38, 56, 245, 128);
    textN_InView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textN_InView.setLinespacing(0);
    textN_InView.setTypedText(touchgfx::TypedText(T_MATCHVIEW_01));
    cInsideView.add(textN_InView);

    textH1_InView.setPosition(148, 56, 93, 32);
    textH1_InView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH1_InView.setLinespacing(0);
    textH1_InView.setTypedText(touchgfx::TypedText(T_MATCHVIEW_01_H1));
    cInsideView.add(textH1_InView);

    textH2_InView.setPosition(38, 88, 79, 32);
    textH2_InView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH2_InView.setLinespacing(0);
    textH2_InView.setTypedText(touchgfx::TypedText(T_MATCHVIEW_01_H5));
    cInsideView.add(textH2_InView);

    textH3_InView.setPosition(129, 120, 42, 32);
    textH3_InView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH3_InView.setLinespacing(0);
    textH3_InView.setTypedText(touchgfx::TypedText(T_MATCHVIEW_01_H3));
    cInsideView.add(textH3_InView);

    textH4_InView.setPosition(90, 152, 41, 32);
    textH4_InView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH4_InView.setLinespacing(0);
    textH4_InView.setTypedText(touchgfx::TypedText(T_MATCHVIEW_01_H4));
    cInsideView.add(textH4_InView);

    labelInst_InView.setPosition(16, 197, 113, 32);
    labelInst_InView.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelInst_InView.setLinespacing(0);
    labelInst_InView.setTypedText(touchgfx::TypedText(T_LABEL_INSTRUCTION));
    cInsideView.add(labelInst_InView);

    imgUp_InView.setXY(128, 197);
    imgUp_InView.setBitmap(touchgfx::Bitmap(BITMAP_UP_ID));
    imgUp_InView.setAlpha(102);
    cInsideView.add(imgUp_InView);

    cInstruction.setPosition(0, 0, 320, 240);
    cInstruction.setVisible(false);

    boxBackGnd_Inst.setPosition(0, 48, 320, 192);
    boxBackGnd_Inst.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    cInstruction.add(boxBackGnd_Inst);

    boxMark_Inst.setPosition(0, 0, 48, 48);
    boxMark_Inst.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    cInstruction.add(boxMark_Inst);

    textN_Inst.setPosition(16, 72, 288, 96);
    textN_Inst.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textN_Inst.setLinespacing(0);
    textN_Inst.setTypedText(touchgfx::TypedText(T_MATCHVIEW_02_1));
    cInstruction.add(textN_Inst);

    textH1_Inst.setPosition(166, 72, 79, 32);
    textH1_Inst.setVisible(false);
    textH1_Inst.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH1_Inst.setLinespacing(0);
    textH1_Inst.setTypedText(touchgfx::TypedText(T_MATCHVIEW_02_H1));
    cInstruction.add(textH1_Inst);

    textH2_Inst.setPosition(16, 104, 61, 32);
    textH2_Inst.setVisible(false);
    textH2_Inst.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH2_Inst.setLinespacing(0);
    textH2_Inst.setTypedText(touchgfx::TypedText(T_MATCHVIEW_02_H2));
    cInstruction.add(textH2_Inst);

    textH3_Inst.setPosition(153, 141, 45, 25);
    textH3_Inst.setVisible(false);
    textH3_Inst.setColor(touchgfx::Color::getColorFrom24BitRGB(142, 142, 142));
    textH3_Inst.setLinespacing(0);
    textH3_Inst.setTypedText(touchgfx::TypedText(T_SUBLABEL_BKSP));
    cInstruction.add(textH3_Inst);

    imgRightShow.setXY(187, 136);
    imgRightShow.setVisible(false);
    imgRightShow.setBitmap(touchgfx::Bitmap(BITMAP_RIGHT_ID));
    imgRightShow.setAlpha(102);
    cInstruction.add(imgRightShow);

    labelPrev.setPosition(40, 197, 47, 32);
    labelPrev.setVisible(false);
    labelPrev.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelPrev.setLinespacing(0);
    labelPrev.setTypedText(touchgfx::TypedText(T_LABEL_PREV));
    cInstruction.add(labelPrev);

    labelNext.setPosition(232, 197, 48, 32);
    labelNext.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelNext.setLinespacing(0);
    labelNext.setTypedText(touchgfx::TypedText(T_LABEL_NEXT));
    cInstruction.add(labelNext);

    labelStart.setPosition(229, 197, 51, 32);
    labelStart.setVisible(false);
    labelStart.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelStart.setLinespacing(0);
    labelStart.setTypedText(touchgfx::TypedText(T_LABEL_START));
    cInstruction.add(labelStart);

    imgLeft.setXY(8, 197);
    imgLeft.setVisible(false);
    imgLeft.setBitmap(touchgfx::Bitmap(BITMAP_LEFT_ID));
    imgLeft.setAlpha(102);
    cInstruction.add(imgLeft);

    imgRight_Inst.setXY(280, 197);
    imgRight_Inst.setBitmap(touchgfx::Bitmap(BITMAP_RIGHT_ID));
    imgRight_Inst.setAlpha(102);
    cInstruction.add(imgRight_Inst);

    labelofPage.setXY(150, 197);
    labelofPage.setColor(touchgfx::Color::getColorFrom24BitRGB(142, 142, 142));
    labelofPage.setLinespacing(0);
    labelofPage.setTypedText(touchgfx::TypedText(T_MATCHVIEW_OFPAGE));
    cInstruction.add(labelofPage);

    labelPage.setXY(135, 197);
    labelPage.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    labelPage.setLinespacing(0);
    Unicode::snprintf(labelPageBuffer, LABELPAGE_SIZE, "%s", touchgfx::TypedText(T_MATCHVIEW_PAGEDEF).getText());
    labelPage.setWildcard(labelPageBuffer);
    labelPage.resizeToCurrentText();
    labelPage.setTypedText(touchgfx::TypedText(T_MATCHVIEW_PAGEVALUE));
    cInstruction.add(labelPage);

    cOutsideList.setPosition(0, 48, 320, 192);
    cOutsideList.setVisible(false);

    boxBackGnd_OutList.setPosition(0, 0, 320, 192);
    boxBackGnd_OutList.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    cOutsideList.add(boxBackGnd_OutList);

    scOutside.setPosition(0, 24, 320, 168);
    scOutside.enableHorizontalScroll(false);
    scOutside.setScrollbarsColor(touchgfx::Color::getColorFrom24BitRGB(142, 142, 142));
    scOutside.setScrollbarsPermanentlyVisible();
    scOutside.setScrollbarsVisible(false);
    cOutsideList.add(scOutside);

    TextTitel.setPosition(87, -3, 147, 29);
    TextTitel.setColor(touchgfx::Color::getColorFrom24BitRGB(46, 46, 46));
    TextTitel.setLinespacing(0);
    TextTitel.setTypedText(touchgfx::TypedText(T_MATCHLIST_TITLE));
    cOutsideList.add(TextTitel);

    ccSuccessCue.setXY(0, 0);
    ccSuccessCue.setVisible(false);

    ccToastItem.setXY(16, 0);
    ccToastItem.setVisible(false);

    ccToastEnt.setXY(16, 184);
    ccToastEnt.setVisible(false);

    ccToastDel.setXY(16, 184);
    ccToastDel.setVisible(false);

    cMatchReport.setPosition(0, 48, 320, 192);
    cMatchReport.setVisible(false);

    boxBackGnd_Match.setPosition(0, 0, 320, 192);
    boxBackGnd_Match.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    cMatchReport.add(boxBackGnd_Match);

    textN1_Match.setPosition(91, 24, 139, 39);
    textN1_Match.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textN1_Match.setLinespacing(0);
    textN1_Match.setTypedText(touchgfx::TypedText(T_MATCHVIEW_03_1));
    cMatchReport.add(textN1_Match);

    textN2_Match.setPosition(100, 63, 139, 32);
    textN2_Match.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textN2_Match.setLinespacing(0);
    textN2_Match.setTypedText(touchgfx::TypedText(T_MATCHVIEW_03_2));
    cMatchReport.add(textN2_Match);

    textN3_Match.setPosition(120, 95, 99, 32);
    textN3_Match.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textN3_Match.setLinespacing(0);
    textN3_Match.setTypedText(touchgfx::TypedText(T_MATCHVIEW_03_3));
    cMatchReport.add(textN3_Match);

    textH1_Match.setPosition(66, 24, 80, 39);
    textH1_Match.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH1_Match.setLinespacing(0);
    Unicode::snprintf(textH1_MatchBuffer, TEXTH1_MATCH_SIZE, "%s", touchgfx::TypedText(T_MATCHVIEW_03_H1).getText());
    textH1_Match.setWildcard(textH1_MatchBuffer);
    textH1_Match.setTypedText(touchgfx::TypedText(T_MATCHVIEW_03_VALUEL));
    cMatchReport.add(textH1_Match);

    textH2_Match.setPosition(76, 63, 39, 32);
    textH2_Match.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH2_Match.setLinespacing(0);
    Unicode::snprintf(textH2_MatchBuffer, TEXTH2_MATCH_SIZE, "%s", touchgfx::TypedText(T_MATCHVIEW_03_H2).getText());
    textH2_Match.setWildcard(textH2_MatchBuffer);
    textH2_Match.setTypedText(touchgfx::TypedText(T_MATCHVIEW_03_VALUES));
    cMatchReport.add(textH2_Match);

    textH3_Match.setPosition(96, 95, 39, 32);
    textH3_Match.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 122, 186));
    textH3_Match.setLinespacing(0);
    Unicode::snprintf(textH3_MatchBuffer, TEXTH3_MATCH_SIZE, "%s", touchgfx::TypedText(T_MATCHVIEW_03_H2).getText());
    textH3_Match.setWildcard(textH3_MatchBuffer);
    textH3_Match.setTypedText(touchgfx::TypedText(T_MATCHVIEW_03_VALUES));
    cMatchReport.add(textH3_Match);

    imgRight_Match.setXY(148, 149);
    imgRight_Match.setBitmap(touchgfx::Bitmap(BITMAP_RIGHT_ID));
    imgRight_Match.setAlpha(102);
    cMatchReport.add(imgRight_Match);

    labelShowReport.setPosition(16, 149, 132, 32);
    labelShowReport.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelShowReport.setLinespacing(0);
    labelShowReport.setTypedText(touchgfx::TypedText(T_LABEL_SHOWREPORT));
    cMatchReport.add(labelShowReport);

    labelDone_Match.setPosition(214, 149, 53, 32);
    labelDone_Match.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelDone_Match.setLinespacing(0);
    labelDone_Match.setTypedText(touchgfx::TypedText(T_LABEL_DONE));
    cMatchReport.add(labelDone_Match);

    labelENT_Match.setPosition(271, 153, 33, 25);
    labelENT_Match.setColor(touchgfx::Color::getColorFrom24BitRGB(142, 142, 142));
    labelENT_Match.setLinespacing(0);
    labelENT_Match.setTypedText(touchgfx::TypedText(T_SUBLABEL_ENT));
    cMatchReport.add(labelENT_Match);

    cMatchList.setPosition(0, 48, 320, 192);
    cMatchList.setVisible(false);

    boxBackGnd_MatchList.setPosition(0, 0, 320, 192);
    boxBackGnd_MatchList.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    cMatchList.add(boxBackGnd_MatchList);

    scMatch.setPosition(0, 0, 320, 192);
    scMatch.enableHorizontalScroll(false);
    scMatch.setScrollbarsColor(touchgfx::Color::getColorFrom24BitRGB(142, 142, 142));
    scMatch.setScrollbarsPermanentlyVisible();
    scMatch.setScrollbarsVisible(false);
    cMatchList.add(scMatch);

    add(ccBackGnd);
    add(ccStatusBar);
    add(labelList);
    add(imgRight);
    add(labelDownInside);
    add(labelDownOutside);
    add(labelENT);
    add(ccNumberBC);
    add(ccUnexpect);
    add(ccMatch);
    add(ccBarcode);
    add(ccBack);
    add(cOutsideView);
    add(cInsideView);
    add(cInstruction);
    add(cOutsideList);
    add(ccSuccessCue);
    add(ccToastItem);
    add(ccToastEnt);
    add(ccToastDel);
    add(cMatchReport);
    add(cMatchList);
}

void SnOutInMatchViewBase::setupScreen()
{
    ccBackGnd.initialize();
    ccStatusBar.initialize();
    ccNumberBC.initialize();
    ccUnexpect.initialize();
    ccMatch.initialize();
    ccBarcode.initialize();
    ccBack.initialize();
    ccSuccessCue.initialize();
    ccToastItem.initialize();
    ccToastEnt.initialize();
    ccToastDel.initialize();
}
