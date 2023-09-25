#ifndef KHMAINSCREENVIEW_HPP
#define KHMAINSCREENVIEW_HPP

#include <gui_generated/khmainscreen_screen/KHMainScreenViewBase.hpp>
#include <gui/khmainscreen_screen/KHMainScreenPresenter.hpp>
#include <gui/common/ZebraApplication.hpp>  // Manual Edit
#include <gui/common/AppClasses.hpp>  // Manual Edit
#include <gui/common/ApplicationClasses/KHMainScreenApp.hpp> // Manual Edit

class KHMainScreenView : public KHMainScreenViewBase
{
public:
    ZEBRA_APPLICATION // Manual Edit
    KHMainScreenView();
    virtual ~KHMainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void afterTransition();
    virtual void handleKeyEvent(uint8_t key);  // Manual Edit
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);  // Manual Edit
    void BarcodeComeIn(char* BarcodeData);
    void doForLocationInput(uint8_t key);
    virtual void handleTickEvent();
    int SendingData();
    string savedBarcode;
protected:

private:
    string barcode;
    int errorindex;
    string errorreason;
    string learnbarcode;
    string verifybarcode;
    string userinitials;
    string verifydate;
    string verifytime;
    string verifysuccess;
    int recordcount;
    BarcodeRecord_t bc_r;
    BarcodeRecord_t* bc_r_ptr;
    int step;
    static const uint16_t CUE_TIMEOUT = 60;
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    static const uint16_t TOASTVIEW_LIST_LIMIT_TIMEOUT = 300;
    uint16_t cueLocTimer;
    uint16_t cueBcTimer;
    uint16_t toastViewTimer;
    uint16_t submitMsgTimer;
    uint16_t toastInventViewTimer;
    uint16_t toastInventENTViewTimer;
    uint16_t toastInventFullViewTimer;
    uint16_t BTIconState;
    uint16_t stringIdx;
    uint16_t radioIdx;
    bool sendingData;
    int sendingDataIndex;
    int testCounter;
    void hideAll();
    void sendData();
    void clearData();
};

#endif // KHMAINSCREENVIEW_HPP
