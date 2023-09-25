#ifndef SNOUTINMATCHVIEW_HPP
#define SNOUTINMATCHVIEW_HPP

#include <gui_generated/snoutinmatch_screen/SnOutInMatchViewBase.hpp>
#include <gui/snoutinmatch_screen/SnOutInMatchPresenter.hpp>
#include <gui/containers/MatchListField.hpp>
#include <gui/containers/MatchListTitle.hpp>
#include <gui/common/ZebraApplication.hpp>
#include <gui/common/AppClasses.hpp>
#include <gui/common/ConfigParam.hpp>

class SnOutInMatchView : 
  public SnOutInMatchViewBase,
  public OutInMatchApp
{
public:

    ZEBRA_APPLICATION

    SnOutInMatchView();
    virtual ~SnOutInMatchView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void afterTransition();
    virtual void handleKeyEvent(uint8_t key);
    virtual void handleTickEvent();
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    void BarcodeComeIn(char * BarcodeData);

protected:
    static const uint8_t MATCH_LIST_ITEM_MAX = 200;
    MatchListField ccMatchList[MATCH_LIST_ITEM_MAX];
    MatchListTitle ccMatchTitle[3];

private:
    uint8_t stateInProcess;
    uint8_t instPage;
    static const uint16_t CUE_TIMEOUT = 60;
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    static const uint16_t TOASTVIEW_LIST_LIMIT_TIMEOUT = 300;
    uint16_t cueScanBCTimer;
    uint16_t cueDelBCTimer;
    uint16_t cueMatchTimer;
    uint16_t cueUnexpectTimer;
    uint16_t toastViewTimer;
    uint16_t toastViewTimer_ListLimit;
    uint16_t amountOutside;
    uint16_t amountMatch;
    uint16_t amountUnexpect;
    uint16_t outsideListItem;
    uint16_t outsideListItemMax;
    uint16_t matchListItem;
    uint16_t matchListItemMax;

    void dragOutsideList(int drag);
    void dragMatchList(int drag);
    void doForBack(uint8_t key);
    void doForHomeKey();
    void transOutToInside();
    void transInToOutside();
    bool checkBarcodeMatch(char * BarcodeData);
    void showInstPage();
    void showOutsideList();
    void showMatchReport();
    void showMatchList();
};

#endif // SNOUTINMATCHVIEW_HPP
