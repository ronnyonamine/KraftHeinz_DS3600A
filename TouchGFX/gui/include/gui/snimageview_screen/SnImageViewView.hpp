#ifndef SNIMAGEVIEWVIEW_HPP
#define SNIMAGEVIEWVIEW_HPP

#include <gui_generated/snimageview_screen/SnImageViewViewBase.hpp>
#include <gui/snimageview_screen/SnImageViewPresenter.hpp>
#include <gui/common/ZebraApplication.hpp>
#include <gui/common/AppClasses.hpp>
#include <gui/common/ConfigParam.hpp>

class SnImageViewView : 
  public SnImageViewViewBase, 
  public ImageViewerApp
{
public:

    ZEBRA_APPLICATION

    SnImageViewView();
    virtual ~SnImageViewView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void afterTransition();
    void selectNewItem();
    virtual void handleKeyEvent(uint8_t key);
    virtual void handleTickEvent();
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    void BarcodeComeIn(char * BarcodeData);

protected:

private:
    #define BMP_RX_BUFFER       (void *)0x60100000          //Address of BMP Rx buffer
    #define BMP_CACHE_BUFFER    (uint16_t*)(0x60150000UL)   //Address of BMP Cache buffer
    static const uint16_t IMG_WIDTH = 320;
    static const uint16_t IMG_HEIGHT = 240;
    static const uint32_t IMG_SIZE = IMG_WIDTH * IMG_HEIGHT * 4;
    static const uint32_t IMG_CACHED = 5;
    static const uint16_t PREIMG_WIDTH = 256;
    static const uint16_t PREIMG_HEIGHT = 192;
    static const uint32_t PREIMG_SIZE = PREIMG_WIDTH * PREIMG_HEIGHT * 4;
    BitmapId bmpId;
    BitmapId bmpPreViewId;
    static const uint16_t MSG_VIEW_TIMEOUT = 120;
    static const uint16_t TOASTVIEW_TIMEOUT = 120;
    uint16_t msgHostFailTimer;
    uint16_t msgResultTimer;

    void doForHomeKey();
};

#endif // SNIMAGEVIEWVIEW_HPP
