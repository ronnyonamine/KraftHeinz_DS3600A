#include <gui/snoutinmatch_screen/SnOutInMatchView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/platform_itf.h>
#include <gui/common/Barcode.hpp>
#include <gui/common/ColorPalette.hpp>
#include <vector>
#include <string>
using std::vector;
using std::string;

#define LAUNCH_SCREEN 5

REGISTER_APPLICATION(
    SnOutInMatchView,
    "Out/Inside Match",
    TRANSITION_CALLBACK(gotoSnOutInMatchScreenNoTransition),
    LAUNCH_SCREEN - 1
)

enum ProcessState
{
    OUTSIDE_INST = 0,
    OUTSIDE_SCAN = 1,
    OUTSIDE_LIST = 2,
    OUTSIDE_DONE = 3,   // outside done same as inside instruction state
    INSIDE_INST = 4,
    INSIDE_SCAN = 5,
    INSIDE_DONE = 6,
    INSIDE_LIST = 7,
};

typedef struct
{
    string barcode; ///< keep barcode
    bool matched;   ///< the barcode matched or not
} OutsideRecord;

static OutsideRecord tempRecord;
vector<OutsideRecord> OutsideList;
vector<string> UnexpectList;

SnOutInMatchView::SnOutInMatchView() :
    stateInProcess(OUTSIDE_INST),
    instPage(1),
    cueScanBCTimer(CUE_TIMEOUT),
    cueDelBCTimer(CUE_TIMEOUT),
    cueMatchTimer(CUE_TIMEOUT),
    cueUnexpectTimer(CUE_TIMEOUT),
    toastViewTimer(TOASTVIEW_TIMEOUT),
    toastViewTimer_ListLimit(TOASTVIEW_LIST_LIMIT_TIMEOUT),
    amountOutside(0),
    amountMatch(0),
    amountUnexpect(0),
    outsideListItem(0),
    outsideListItemMax(0),
    matchListItem(0),
    matchListItemMax(0)
{

}

void SnOutInMatchView::setupScreen()
{
    SnOutInMatchViewBase::setupScreen();
    presenter->UpdateAllIcons();
    presenter->setCurrentScreen(OUT_INSIDE_MATCH);
    ccToastEnt.setText(5);
    ccToastDel.setText(6);
    ccToastItem.setText(8);
    scOutside.setScrollbarWidth(4);
    dragOutsideList(-1);
    dragOutsideList(1);
    scOutside.invalidate();
    scMatch.setScrollbarWidth(4);
    dragMatchList(-1);
    dragMatchList(1);
    scMatch.invalidate();
}

void SnOutInMatchView::tearDownScreen()
{
    SnOutInMatchViewBase::tearDownScreen();
    OutsideList.clear();
    UnexpectList.clear();
    clear_item_list_flag();
}

void SnOutInMatchView::handleKeyEvent(uint8_t key)
{
    if (cueDelBCTimer < CUE_TIMEOUT)
        return;

    if (ccBack.isFocusing())
    {
        doForBack(key);
        return;
    }

    presenter->keyPressed(key);
    
    if (cMatchList.isVisible())     // for show match list state
    {
        switch (key)
        {
        case KEYCODE_UP:
            if (matchListItem != 0)
            {
                int drag = (ccMatchList[matchListItem].getY() - ccMatchList[matchListItem - 1].getY()) / 56;
                dragMatchList(drag);
                ccMatchList[matchListItem].setAction(MatchListField::NORMAL);
                matchListItem--;
                ccMatchList[matchListItem].setAction(MatchListField::SET_FOCUS);
                cMatchList.invalidate();
            }
            else
            {
                dragMatchList(1);
                ccMatchList[matchListItem].setAction(MatchListField::NORMAL);
                cMatchList.invalidate();
                ccBack.setFocus(true);
                ccBack.invalidate();
            }
            break;

        case KEYCODE_DOWN:
            if (matchListItem < matchListItemMax)
            {
                int drag = (ccMatchList[matchListItem].getY() - ccMatchList[matchListItem + 1].getY()) / 56;
                dragMatchList(drag);
                ccMatchList[matchListItem].setAction(MatchListField::NORMAL);
                matchListItem++;
                ccMatchList[matchListItem].setAction(MatchListField::SET_FOCUS);
                cMatchList.invalidate();
            }
            break;

        case KEYCODE_ENTER:
            // cMatchList.setVisible(false);
            // cMatchList.invalidate();
            // scMatch.removeAll();
            // cMatchReport.setVisible(false);
            // cMatchReport.invalidate();
            // OutsideList.clear();
            // transInToOutside();
            application().gotoSnOutInMatchScreenNoTransition();
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            ccBack.setFocus(false);
            ccBack.invalidate();
            cMatchList.setVisible(false);
            cMatchList.invalidate();
            scMatch.removeAll();
            stateInProcess = INSIDE_DONE;
            break;


        }
        return;
    }

    if (cMatchReport.isVisible())   // for show match report state
    {
        switch (key)
        {
        case KEYCODE_UP:
            ccBack.setFocus(true);
            ccBack.invalidate();
            break;

        case KEYCODE_RIGHT:
            showMatchList();
            break;

        case KEYCODE_ENTER:
            // cMatchReport.setVisible(false);
            // cMatchReport.invalidate();
            // OutsideList.clear();
            // transInToOutside();
            application().gotoSnOutInMatchScreenNoTransition();
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            ccBack.setFocus(false);
            ccBack.invalidate();
            cMatchReport.setVisible(false);
            cMatchReport.invalidate();
            stateInProcess = INSIDE_SCAN;
            break;


        }
        return;
    }

    if (cOutsideList.isVisible())   // for show outside list state
    {
        switch (key)
        {
        case KEYCODE_UP:
            dragOutsideList(1);
            ccMatchList[outsideListItem].setAction(MatchListField::NORMAL);
            if (outsideListItem != 0)
            {
                outsideListItem--;
                ccMatchList[outsideListItem].setAction(MatchListField::SET_FOCUS);
            }
            else
            {
                ccBack.setFocus(true);
                ccBack.invalidate();
            }
            cOutsideList.invalidate();
            break;

        case KEYCODE_DOWN:
            if (outsideListItem < outsideListItemMax)
            {
                dragOutsideList(-1);
                ccMatchList[outsideListItem].setAction(MatchListField::NORMAL);
                outsideListItem++;
                ccMatchList[outsideListItem].setAction(MatchListField::SET_FOCUS);
                cOutsideList.invalidate();
            }
            break;

        case KEYCODE_BKSP:
            if (OutsideList.empty())
                return;
            ccMatchList[outsideListItem].setAction(MatchListField::SET_DELETE);
            cOutsideList.invalidate();
            cueDelBCTimer = 0;
            ccSuccessCue.setCueColor(STATES_ERROR);
            ccSuccessCue.setVisible(true);
            ccSuccessCue.invalidate();
            toastViewTimer = 0;
            ccToastDel.setVisible(true);
            ccToastDel.invalidate();
            break;

        case KEYCODE_ENTER:
            cOutsideList.setVisible(false);
            cOutsideList.invalidate();
            scOutside.removeAll();
            transOutToInside();
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            ccBack.setFocus(false);
            ccBack.invalidate();
            cOutsideList.setVisible(false);
            cOutsideList.invalidate();
            scOutside.removeAll();
            stateInProcess = OUTSIDE_SCAN;
            break;


        }
        return;
    }

    if (cInstruction.isVisible())   // for outside/inside instruction state
    {
        switch (key)
        {
        case KEYCODE_LEFT:
            instPage -= (instPage <= 1) ? 0 : 1;
            showInstPage();
            break;

        case KEYCODE_RIGHT:
            instPage += (instPage >= 9) ? 0 : 1;
            showInstPage();
            break;

        case KEYCODE_ENTER:
            cInstruction.setVisible(false);
            cInstruction.invalidate();
            cOutsideView.setVisible(false);
            cOutsideView.invalidate();
            cInsideView.setVisible(false);
            cInsideView.invalidate();
            instPage = 1;
            stateInProcess++;       // instruction -> scan
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            if (stateInProcess == INSIDE_INST)
            {
                ccBack.setFocus(false);
                ccBack.invalidate();
                cInstruction.setVisible(false);
                cInstruction.invalidate();
                cOutsideView.setVisible(false);
                cOutsideView.invalidate();
                cInsideView.setVisible(false);
                cInsideView.invalidate();
                transInToOutside();
            }
            else
            {
                application().gotoSnHomeMenuScreenNoTransition();
            }
            break;


        }
        return;
    }

    if (cInsideView.isVisible())    // for inside instruction state
    {
        switch (key)
        {
        case KEYCODE_UP:
            instPage = 1;
            showInstPage();
            cInstruction.setVisible(true);
            cInstruction.invalidate();
            break;

        case KEYCODE_ENTER:
            cInsideView.setVisible(false);
            cInsideView.invalidate();
            stateInProcess = INSIDE_SCAN;
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            ccBack.setFocus(false);
            ccBack.invalidate();
            cInsideView.setVisible(false);
            cInsideView.invalidate();
            transInToOutside();
            break;


        }
        return;
    }

    if (cOutsideView.isVisible())   // for outside instruction state
    {
        switch (key)
        {
        case KEYCODE_UP:
            instPage = 1;
            showInstPage();
            cInstruction.setVisible(true);
            cInstruction.invalidate();
            break;

        case KEYCODE_ENTER:
            cOutsideView.setVisible(false);
            cOutsideView.invalidate();
            stateInProcess = OUTSIDE_SCAN;
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            application().gotoSnHomeMenuScreenNoTransition();
            break;


        }
        return;
    }

    switch (stateInProcess)
    {
    case OUTSIDE_SCAN:
        switch (key)
        {
        case KEYCODE_UP:
            ccBack.setFocus(true);
            ccBack.invalidate();
            ccNumberBC.setFocus(false);
            ccNumberBC.invalidate();
            break;

        case KEYCODE_RIGHT:
            showOutsideList();
            break;

        case KEYCODE_ENTER:
            transOutToInside();
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            application().gotoSnHomeMenuScreenNoTransition();
            break;
        }
        break;

    case INSIDE_SCAN:
        switch (key)
        {
        case KEYCODE_UP:
            ccBack.setFocus(true);
            ccBack.invalidate();
            break;

        case KEYCODE_ENTER:
            showMatchReport();
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            ccBack.setFocus(false);
            ccBack.invalidate();
            transInToOutside();
            break;


        }
        break;
    }
}

void SnOutInMatchView::handleTickEvent()
{
    if (cueScanBCTimer < CUE_TIMEOUT)
    {
        cueScanBCTimer++;
        if (cueScanBCTimer == CUE_TIMEOUT)
        {
            ccBarcode.setVisible(false);
            ccBarcode.invalidate();
            ccSuccessCue.setVisible(false);
            ccSuccessCue.invalidate();
        }
    }

    if (cueDelBCTimer < CUE_TIMEOUT)
    {
        cueDelBCTimer++;
        if (cueDelBCTimer == CUE_TIMEOUT)
        {
            ccSuccessCue.setVisible(false);
            ccSuccessCue.invalidate();
            OutsideList.erase(OutsideList.begin() + outsideListItem);
            scOutside.removeAll();
            ccNumberBC.setNumber(OutsideList.size());
            ccNumberBC.invalidate();
            showOutsideList();
        }
    }

    if (cueMatchTimer < CUE_TIMEOUT)
    {
        cueMatchTimer++;
        if (cueMatchTimer == CUE_TIMEOUT)
        {
            ccMatch.setCue(false);
            ccMatch.invalidate();
            ccSuccessCue.setVisible(false);
            ccSuccessCue.invalidate();
        }
    }

    if (cueUnexpectTimer < CUE_TIMEOUT)
    {
        cueUnexpectTimer++;
        if (cueUnexpectTimer == CUE_TIMEOUT)
        {
            ccUnexpect.setCue(false);
            ccUnexpect.invalidate();
            ccSuccessCue.setVisible(false);
            ccSuccessCue.invalidate();
        }
    }

    if (toastViewTimer < TOASTVIEW_TIMEOUT)
    {
        toastViewTimer++;
        if (toastViewTimer == TOASTVIEW_TIMEOUT)
        {
            ccToastEnt.setVisible(false);
            ccToastEnt.invalidate();
            ccToastDel.setVisible(false);
            ccToastDel.invalidate();
        }
    }

    if (toastViewTimer_ListLimit < TOASTVIEW_LIST_LIMIT_TIMEOUT)
    {
        toastViewTimer_ListLimit++;
        if (toastViewTimer_ListLimit == TOASTVIEW_LIST_LIMIT_TIMEOUT)
        {
            ccToastItem.setVisible(false);
            ccToastItem.invalidate();
        }
    }
}

//Called when the screen is done with transition/load
void SnOutInMatchView::afterTransition()
{
    // clear barcode buffer when into this screen
    while (presenter->getBarcode() != NULL)
    {
        presenter->clearBarcode();
    }
}

void SnOutInMatchView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnOutInMatchView::BarcodeComeIn(char * BarcodeData)
{
    if (cueDelBCTimer < CUE_TIMEOUT)
    {
        presenter->clearBarcode();
        return;
    }

    switch (stateInProcess)
    {
    case OUTSIDE_INST:
        cInstruction.setVisible(false); // set Instruction view off
        cInstruction.invalidate();
        cOutsideView.setVisible(false);
        cOutsideView.invalidate();
        [[fallthrough]];
         
    case OUTSIDE_LIST:
        cOutsideList.setVisible(false);
        cOutsideList.invalidate();
        scOutside.removeAll();
        stateInProcess = OUTSIDE_SCAN;
        [[fallthrough]]	;	
        
    case OUTSIDE_SCAN:
        if (OutsideList.size() >= MATCH_LIST_ITEM_MAX)
        {
            presenter->clearBarcode();
            toastViewTimer_ListLimit = 0;
            ccToastItem.setVisible(true);
            ccToastItem.invalidate();
            SendInventoryListFullCommand();
            return;
        }

        if (presenter->getOutInMatchListFullFlag() ==1)
        {
            presenter->clearBarcode();
            toastViewTimer_ListLimit = 0;
            ccToastItem.setVisible(true);
            ccToastItem.invalidate();
            SendInventoryListFullCommand();
            return;
        }

        tempRecord.barcode.assign(BarcodeData);
        tempRecord.matched = false;
        OutsideList.push_back(tempRecord);
        ccBarcode.setText(NonPrintCharFilter(BarcodeData)); // set barcode text
        presenter->clearBarcode();
        ccBack.setFocus(false);
        ccBack.invalidate();
        ccNumberBC.setFocus(true);
        ccNumberBC.setNumber(OutsideList.size());
        ccNumberBC.invalidate();
        cueScanBCTimer = 0;             // show barcode and SuccessCue
        ccBarcode.setVisible(true);
        ccBarcode.invalidate();
        ccSuccessCue.setCueColor(STATES_SUCCESS);
        ccSuccessCue.setVisible(true);
        ccSuccessCue.invalidate();
        break;

    case INSIDE_INST:
        cInstruction.setVisible(false); // set Instruction view off
        cInstruction.invalidate();
        cInsideView.setVisible(false);
        cInsideView.invalidate();
        stateInProcess = INSIDE_SCAN;
        [[fallthrough]]	;	

    case INSIDE_SCAN:
        if ((amountMatch + amountUnexpect) >= MATCH_LIST_ITEM_MAX)
        {
            presenter->clearBarcode();
            toastViewTimer_ListLimit = 0;
            ccToastItem.setVisible(true);
            ccToastItem.invalidate();
            SendInventoryListFullCommand();
            return;
        }

        if (presenter->getOutInMatchListFullFlag() ==1)
        {
            presenter->clearBarcode();
            toastViewTimer_ListLimit = 0;
            ccToastItem.setVisible(true);
            ccToastItem.invalidate();
            SendInventoryListFullCommand();
            return;
        }

        if (checkBarcodeMatch(BarcodeData)) // Matched
        {
            amountMatch++;
            cueMatchTimer = 0;
            ccMatch.setValue(amountMatch, amountOutside);
            ccMatch.setCue(true);
            ccMatch.invalidate();
            ccSuccessCue.setCueColor(STATES_SUCCESS);
            ccSuccessCue.setVisible(true);
            ccSuccessCue.invalidate();
        }
        else                                // Unexpect
        {
            amountUnexpect++;
            cueUnexpectTimer = 0;
            ccUnexpect.setValue(amountUnexpect);
            ccUnexpect.setCue(true);
            ccUnexpect.invalidate();
            ccSuccessCue.setCueColor(STATES_ERROR);
            ccSuccessCue.setVisible(true);
            ccSuccessCue.invalidate();
        }
        break;

    default:
        presenter->clearBarcode();
        break;
    }
}

void SnOutInMatchView::dragOutsideList(int drag)
{
    int16_t xPos = scOutside.getScrolledX();
    int16_t yOldPos = scOutside.getScrolledY();
    int16_t yNewPos = yOldPos + (56 * drag);
    DragEvent relative(DragEvent::DRAGGED, xPos, yOldPos, xPos, yNewPos);
    scOutside.handleDragEvent(relative);
}

void SnOutInMatchView::dragMatchList(int drag)
{
    int16_t xPos = scMatch.getScrolledX();
    int16_t yOldPos = scMatch.getScrolledY();
    int16_t yNewPos = yOldPos + (56 * drag);
    DragEvent relative(DragEvent::DRAGGED, xPos, yOldPos, xPos, yNewPos);
    scMatch.handleDragEvent(relative);
}

void SnOutInMatchView::doForBack(uint8_t key)
{
    switch (stateInProcess)
    {
    case OUTSIDE_INST:
        ccBack.setFocus(false);
        ccBack.invalidate();
        break;

    case OUTSIDE_SCAN:
        switch (key)
        {
        case KEYCODE_DOWN:
            ccBack.setFocus(false);
            ccBack.invalidate();
            ccNumberBC.setFocus(true);
            ccNumberBC.invalidate();
            stateInProcess = OUTSIDE_SCAN;
            break;

        case KEYCODE_ENTER:
        case KEYCODE_ESC:
        case KEYCODE_BACK:
            application().gotoSnHomeMenuScreenNoTransition();
            break;
        }
        break;

    case OUTSIDE_LIST:
        switch (key)
        {
        case KEYCODE_DOWN:
            ccBack.setFocus(false);
            ccBack.invalidate();
            stateInProcess = OUTSIDE_LIST;
            outsideListItem = 0;
            ccMatchList[outsideListItem].setAction(MatchListField::SET_FOCUS);
            cOutsideList.invalidate();
            break;

        case KEYCODE_ENTER:
        case KEYCODE_ESC:
        case KEYCODE_BACK:
            ccBack.setFocus(false);
            ccBack.invalidate();
            cOutsideList.setVisible(false);
            cOutsideList.invalidate();
            scOutside.removeAll();
            stateInProcess = OUTSIDE_SCAN;
            break;


        }
        break;

    case INSIDE_INST:
        ccBack.setFocus(false);
        ccBack.invalidate();
        stateInProcess = INSIDE_INST;
        break;

    case INSIDE_SCAN:
        switch (key)
        {
        case KEYCODE_DOWN:
            ccBack.setFocus(false);
            ccBack.invalidate();
            stateInProcess = INSIDE_SCAN;
            break;

        case KEYCODE_ENTER:
            ccBack.setFocus(false);
            ccBack.invalidate();
            transInToOutside();
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            application().gotoSnHomeMenuScreenNoTransition();
            break;
        }
        break;

    case INSIDE_DONE:
        switch (key)
        {
        case KEYCODE_DOWN:
            ccBack.setFocus(false);
            ccBack.invalidate();
            stateInProcess = INSIDE_DONE;
            break;

        case KEYCODE_RIGHT:
            ccBack.setFocus(false);
            ccBack.invalidate();
            showMatchList();
            break;

        case KEYCODE_ENTER:
        case KEYCODE_ESC:
        case KEYCODE_BACK:
            ccBack.setFocus(false);
            ccBack.invalidate();
            cMatchReport.setVisible(false);
            cMatchReport.invalidate();
            stateInProcess = INSIDE_SCAN;
            break;


        }
        break;

    case INSIDE_LIST:
        switch (key)
        {
        case KEYCODE_DOWN:
            ccBack.setFocus(false);
            ccBack.invalidate();
            stateInProcess = INSIDE_LIST;
            matchListItem = 0;
            ccMatchList[matchListItem].setAction(MatchListField::SET_FOCUS);
            cMatchList.invalidate();
            break;

        case KEYCODE_ENTER:
        case KEYCODE_ESC:
        case KEYCODE_BACK:
            ccBack.setFocus(false);
            ccBack.invalidate();
            cMatchList.setVisible(false);
            cMatchList.invalidate();
            scMatch.removeAll();
            stateInProcess = INSIDE_DONE;
            break;


        }
        break;
    }
}

void SnOutInMatchView::transOutToInside()
{
    amountOutside = OutsideList.size();
    amountMatch = 0;
    amountUnexpect = 0;
    ccNumberBC.setVisible(false);       // switch Field
    ccNumberBC.invalidate();
    ccMatch.setValue(amountMatch, amountOutside);
    ccMatch.setVisible(true);
    ccMatch.invalidate();
    ccUnexpect.setValue(amountUnexpect);
    ccUnexpect.setVisible(true);
    ccUnexpect.invalidate();
    labelDownOutside.setVisible(false); // switch label/icon
    labelDownOutside.invalidate();
    labelDownInside.setVisible(true);
    labelDownInside.invalidate();
    imgRight.setVisible(false);
    imgRight.invalidate();
    labelList.setVisible(false);
    labelList.invalidate();
    cInsideView.setVisible(true);       // pop Inside Instruction View
    cInsideView.invalidate();
    stateInProcess = INSIDE_INST;
}

void SnOutInMatchView::transInToOutside()
{
    for (uint16_t i = 0;i < OutsideList.size();i++)
    {
        OutsideList.at(i).matched = false;
    }
    UnexpectList.clear();
    ccNumberBC.setVisible(true);        // switch Field
    ccNumberBC.invalidate();
    ccMatch.setVisible(false);
    ccMatch.invalidate();
    ccUnexpect.setVisible(false);
    ccUnexpect.invalidate();
    labelDownOutside.setVisible(true);  // switch label/icon
    labelDownOutside.invalidate();
    labelDownInside.setVisible(false);
    labelDownInside.invalidate();
    imgRight.setVisible(true);
    imgRight.invalidate();
    labelList.setVisible(true);
    labelList.invalidate();
    stateInProcess = OUTSIDE_SCAN;
}

bool SnOutInMatchView::checkBarcodeMatch(char * BarcodeData)
{
    UnexpectList.push_back(BarcodeData);
    presenter->clearBarcode();

    for (uint16_t i = 0;i < OutsideList.size();i++)
    {
        if (OutsideList.at(i).matched == false)
        {
            if (UnexpectList.back().compare(OutsideList.at(i).barcode) == 0)
            {
                OutsideList.at(i).matched = true;
                UnexpectList.pop_back();
                return (true);
            }
        }
    }
    return (false);
}

void SnOutInMatchView::showInstPage()
{
    Unicode::snprintf(labelPageBuffer, LABELPAGE_SIZE, "%d", instPage);
    switch (instPage)
    {
    case 1:
        textN_Inst.setTypedText(touchgfx::TypedText(T_MATCHVIEW_02_1));
        textH1_Inst.setVisible(false);
        textH2_Inst.setVisible(false);
        textH3_Inst.setVisible(false);
        labelNext.setVisible(true);
        labelStart.setVisible(false);
        labelPrev.setVisible(false);
        imgLeft.setVisible(false);
        break;

    case 2:
        textN_Inst.setTypedText(touchgfx::TypedText(T_MATCHVIEW_02_2));
        textH1_Inst.setVisible(false);
        textH2_Inst.setVisible(false);
        labelPrev.setVisible(true);
        imgLeft.setVisible(true);
        break;

    case 3:
        textN_Inst.setTypedText(touchgfx::TypedText(T_MATCHVIEW_02_3));
        textH1_Inst.setVisible(true);
        textH2_Inst.setVisible(true);
        imgRightShow.setVisible(false);
        break;

    case 4:
        textN_Inst.setTypedText(touchgfx::TypedText(T_MATCHVIEW_02_4));
        textH1_Inst.setVisible(false);
        textH2_Inst.setVisible(false);
        imgRightShow.setVisible(true);
        textH3_Inst.setVisible(false);
        break;

    case 5:
        textN_Inst.setTypedText(touchgfx::TypedText(T_MATCHVIEW_02_5));
        imgRightShow.setVisible(false);
        textH3_Inst.setPosition(153, 141, 45, 25);
        textH3_Inst.setTypedText(touchgfx::TypedText(T_SUBLABEL_BKSP));
        textH3_Inst.setVisible(true);
        break;

    case 6:
        textN_Inst.setTypedText(touchgfx::TypedText(T_MATCHVIEW_02_6));
        textH3_Inst.setPosition(78, 141, 45, 25);
        textH3_Inst.setTypedText(touchgfx::TypedText(T_SUBLABEL_ENT));
        textH3_Inst.setVisible(true);
        break;

    case 7:
        textN_Inst.setTypedText(touchgfx::TypedText(T_MATCHVIEW_02_7));
        textH3_Inst.setVisible(false);
        labelNext.setVisible(true);
        labelStart.setVisible(false);
        break;

    case 8:
        textN_Inst.setTypedText(touchgfx::TypedText(T_MATCHVIEW_02_8));
        labelNext.setVisible(false);
        labelStart.setVisible(true);
        break;

    case 9:
        cInstruction.setVisible(false);
        cOutsideView.setVisible(false);
        cOutsideView.invalidate();
        cInsideView.setVisible(false);
        cInsideView.invalidate();
        stateInProcess++;       // instruction -> scan
        break;
    }
    cInstruction.invalidate();
}

void SnOutInMatchView::showOutsideList()
{
    outsideListItemMax = 0;
    for (uint16_t i = 0;(i < OutsideList.size()) && (i < MATCH_LIST_ITEM_MAX);i++)
    {
        Barcode tempBC;

        tempBC.setText(NonPrintCharFilter(const_cast<char *>(OutsideList.at(i).barcode.c_str())));
        ccMatchList[i].setXY(0, 56 * i);
        ccMatchList[i].setType(MatchListField::BARCODE);
        ccMatchList[i].setText((i + 1), tempBC.getEllipsis(), tempBC.getSfont(),
                               tempBC.getLfont());
        ccMatchList[i].setAction(MatchListField::NORMAL);
        scOutside.add(ccMatchList[i]);
        outsideListItemMax++;
    }

    outsideListItemMax--;
    outsideListItem = 0;
    toastViewTimer = 0;
    ccToastEnt.setVisible(true);
    ccToastEnt.invalidate();
    ccMatchList[outsideListItem].setAction(MatchListField::SET_FOCUS);
    cOutsideList.setVisible(true);
    cOutsideList.invalidate();
    stateInProcess = OUTSIDE_LIST;
}

void SnOutInMatchView::showMatchReport()
{
    if ((amountUnexpect > 0) || (amountOutside > amountMatch))
    {
        textH1_Match.setColor(STATES_ERROR);
        Unicode::snprintf(textH1_MatchBuffer, TEXTH1_MATCH_SIZE, "%d%c", ((amountMatch * 100) / amountOutside), '%');
        Unicode::snprintf(textH2_MatchBuffer, TEXTH2_MATCH_SIZE, "%d", amountUnexpect);
        textH2_Match.setVisible(true);
        textN2_Match.setVisible(true);
        Unicode::snprintf(textH3_MatchBuffer, TEXTH3_MATCH_SIZE, "%d", (amountOutside - amountMatch));
        textH3_Match.setVisible(true);
        textN3_Match.setVisible(true);
    }
    else
    {
        textH1_Match.setColor(STATES_SUCCESS);
        Unicode::snprintf(textH1_MatchBuffer, TEXTH1_MATCH_SIZE, "%d%c", 100, '%');
        textH2_Match.setVisible(false);
        textN2_Match.setVisible(false);
        textH3_Match.setVisible(false);
        textN3_Match.setVisible(false);
    }
    cMatchReport.setVisible(true);
    cMatchReport.invalidate();
    stateInProcess = INSIDE_DONE;
}

void SnOutInMatchView::showMatchList()
{
    uint16_t index = 0;
    uint16_t offset = 0;
    Barcode tempBC;

    if (amountUnexpect > 0) // show Unexpected
    {
        ccMatchTitle[0].setXY(0, 56 * index);
        ccMatchTitle[0].setText(0);
        scMatch.add(ccMatchTitle[0]);
        index++;
        for (uint16_t i = 0;(i < amountUnexpect) && (index < MATCH_LIST_ITEM_MAX);i++)
        {
            tempBC.setText(NonPrintCharFilter(const_cast<char *>(UnexpectList.at(i).c_str())));
            ccMatchList[offset].setXY(0, 56 * index);
            ccMatchList[offset].setType(MatchListField::UNEXPECTED);
            ccMatchList[offset].setText(0, tempBC.getEllipsis(), tempBC.getSfont(), tempBC.getLfont());
            ccMatchList[offset].setAction(MatchListField::NORMAL);
            scMatch.add(ccMatchList[offset]);
            index++;
            offset++;
        }
    }

    if (amountOutside > amountMatch) // show Missing
    {
        ccMatchTitle[1].setXY(0, 56 * index);
        ccMatchTitle[1].setText(1);
        scMatch.add(ccMatchTitle[1]);
        index++;
        for (uint16_t i = 0;(i < OutsideList.size()) && (offset < MATCH_LIST_ITEM_MAX);i++)
        {
            if (OutsideList.at(i).matched == false)
            {
                tempBC.setText(NonPrintCharFilter(const_cast<char *>(OutsideList.at(i).barcode.c_str())));
                ccMatchList[offset].setXY(0, 56 * index);
                ccMatchList[offset].setType(MatchListField::MISSING);
                ccMatchList[offset].setText(0, tempBC.getEllipsis(), tempBC.getSfont(), tempBC.getLfont());
                ccMatchList[offset].setAction(MatchListField::NORMAL);
                scMatch.add(ccMatchList[offset]);
                index++;
                offset++;
            }
        }
    }

    // show Matched
    ccMatchTitle[2].setXY(0, 56 * index);
    ccMatchTitle[2].setText(2);
    scMatch.add(ccMatchTitle[2]);
    index++;
    for (uint16_t i = 0;(i < OutsideList.size()) && (offset < MATCH_LIST_ITEM_MAX);i++)
    {
        if (OutsideList.at(i).matched == true)
        {
            tempBC.setText(NonPrintCharFilter(const_cast<char *>(OutsideList.at(i).barcode.c_str())));
            ccMatchList[offset].setXY(0, 56 * index);
            ccMatchList[offset].setType(MatchListField::MATCHES);
            ccMatchList[offset].setText(0, tempBC.getEllipsis(), tempBC.getSfont(), tempBC.getLfont());
            ccMatchList[offset].setAction(MatchListField::NORMAL);
            scMatch.add(ccMatchList[offset]);
            index++;
            offset++;
        }
    }

    matchListItemMax = offset - 1;
    matchListItem = 0;
    ccMatchList[matchListItem].setAction(MatchListField::SET_FOCUS);
    dragMatchList(-(matchListItemMax));
    dragMatchList(matchListItemMax);
    cMatchList.setVisible(true);
    cMatchList.invalidate();
    stateInProcess = INSIDE_LIST;
}
