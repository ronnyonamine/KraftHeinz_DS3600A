#ifndef SNQTYSENDMODEVIEW_HPP
#define SNQTYSENDMODEVIEW_HPP

#include <gui_generated/snqtysendmode_screen/SnQtySendModeViewBase.hpp>
#include <gui/snqtysendmode_screen/SnQtySendModePresenter.hpp>

class SnQtySendModeView : public SnQtySendModeViewBase
{
public:
    SnQtySendModeView();
    virtual ~SnQtySendModeView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void afterTransition();
    void selectNewItem();
    virtual void handleKeyEvent(uint8_t key);
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual void handleTickEvent();
    void BarcodeComeIn(char * BarcodeData);

protected:

private:
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    static const uint16_t MENUITEM_MAX = 3;
    FocusableIetm * MenuItem[MENUITEM_MAX];
    uint8_t selectItem;
    uint8_t RadioOnItem;
    uint16_t toastCfgMenuViewTimer;
};

#endif // SNQTYSENDMODEVIEW_HPP
