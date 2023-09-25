#include <gui/snimageview_screen/SnImageViewView.hpp>
#include <gui/common/platform_itf.h>
#include <texts/TextKeysAndLanguages.hpp>

#define LAUNCH_SCREEN 6
#define PREVIEW_ENABLED 1

enum ImageViewCmd
{
    DISABLE_PREVIEW = 0x01,
    ENABLE_PREVIEW = 0x02,
    SEND_SSI_IMG_MODE = 0x03,
    IMG_SEND = 0x04,
    DISABLE_IMG_MODE = 0x05,
};

enum ImageViewCmdBack
{
    ACTION_ATTR_ACK = 0x01,
    ACTION_ATTR_NACK = 0x02,
    SSI_IMG_MODE_ACK = 0x03,
    SSI_IMG_MODE_NACK = 0x04,
    PREVIEW_IMG_COMPLETED = 0x05,
    TRIGGER_PRESSED = 0x06,
    IMG_COMPLETED = 0x07,
    SEND_IMG_ACK = 0x09,
    SEND_IMG_NACK = 0x0A,
};REGISTER_APPLICATION(
    SnImageViewView,
    "View Image",
    TRANSITION_CALLBACK(gotoSnImageViewScreenNoTransition),
    LAUNCH_SCREEN - 1
)




SnImageViewView::SnImageViewView() :
    msgHostFailTimer(MSG_VIEW_TIMEOUT),
    msgResultTimer(MSG_VIEW_TIMEOUT)
{

}

void SnImageViewView::setupScreen()
{
    SnImageViewViewBase::setupScreen();
    presenter->UpdateAllIcons();
    presenter->setCurrentScreen(VIEW_IMAGE);
    ccToast_PreView.setText(7);

    Bitmap::setCache(BMP_CACHE_BUFFER, IMG_SIZE * IMG_CACHED, IMG_CACHED);
    Bitmap::cacheAll();

    //Create (16bit) dynamic bitmap of size 320x240
    bmpId = Bitmap::dynamicBitmapCreate(IMG_WIDTH, IMG_HEIGHT, Bitmap::ARGB8888);
    bmpPreViewId = Bitmap::dynamicBitmapCreate(PREIMG_WIDTH, PREIMG_HEIGHT, Bitmap::ARGB8888);

    //Make Image widget show the dynamic bitmap
    imgView.setBitmap(touchgfx::Bitmap(bmpId));
    imgView.invalidate();
    imgPreView.setBitmap(touchgfx::Bitmap(bmpPreViewId));
    imgPreView.invalidate();
}

void SnImageViewView::tearDownScreen()
{
    SnImageViewViewBase::tearDownScreen();
    Bitmap::dynamicBitmapDelete(bmpId);
    Bitmap::dynamicBitmapDelete(bmpPreViewId);
    Bitmap::removeCache();
    presenter->setImgViewCmd(DISABLE_IMG_MODE);
    // for (int i = 0 ; i <= 200 ; i++)
        // presenter->clearBarcode();
}

void SnImageViewView::handleKeyEvent(uint8_t key)
{
    if (ccBack.isFocusing())
    {
        switch (key)
        {
        case KEYCODE_DOWN:
            ccBack.setFocus(false);
            ccBack.invalidate();
            break;

        case KEYCODE_ENTER:
        case KEYCODE_ESC:
        case KEYCODE_BACK:
            application().gotoSnHomeMenuScreenNoTransition();
            break;

        case KEYCODE_HOME:
            doForHomeKey();
            break;
        }
        return;
    }

    if (cCheckHost.isVisible())
    {
        switch (key)
        {
        case KEYCODE_ENTER:
            cCheckHost.setVisible(false);
            cCheckHost.invalidate();
            if (presenter->getLiveCapture() == PREVIEW_ENABLED)
            {
                presenter->setImgViewCmd(ENABLE_PREVIEW);
            }
            else
            {
                presenter->setImgViewCmd(DISABLE_PREVIEW);
            }
            break;

        case KEYCODE_ESC:
        case KEYCODE_BKSP:
        case KEYCODE_BACK:
            application().gotoSnHomeMenuScreenNoTransition();
            break;

        case KEYCODE_HOME:
            doForHomeKey();
            break;
        }
        return;
    }

    if (cWaitCapture.isVisible())
    {
        switch (key)
        {
        case KEYCODE_UP:
            ccBack.setFocus(true);
            ccBack.invalidate();
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            application().gotoSnHomeMenuScreenNoTransition();
            break;

        case KEYCODE_HOME:
            doForHomeKey();
            break;
        }
        return;
    }

    if (cPreViewImg.isVisible())
    {
        switch (key)
        {
        case KEYCODE_UP:
            ccBack.setFocus(true);
            ccBack.invalidate();
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            application().gotoSnHomeMenuScreenNoTransition();
            break;

        case KEYCODE_HOME:
            doForHomeKey();
            break;
        }
        return;
    }

    if (cViewImg.isVisible())
    {
        switch (key)
        {
        case KEYCODE_BKSP:
            cViewImg.setVisible(false);
            cViewImg.invalidate();
            presenter->setImgViewCmd(SEND_SSI_IMG_MODE);
            break;

        case KEYCODE_ENTER:
            presenter->setImgViewCmd(IMG_SEND);
            cViewImg.setVisible(false);
            cViewImg.invalidate();
            break;

        case KEYCODE_ESC:
        case KEYCODE_BACK:
            application().gotoSnHomeMenuScreenNoTransition();
            break;

        case KEYCODE_HOME:
            doForHomeKey();
            break;
        }
        return;
    }
}

void SnImageViewView::handleTickEvent()
{
    if (msgHostFailTimer < MSG_VIEW_TIMEOUT)
    {
        msgHostFailTimer++;
        if (msgHostFailTimer == MSG_VIEW_TIMEOUT)
        {
            application().gotoSnHomeMenuScreenNoTransition();
        }
    }

    if (msgResultTimer < MSG_VIEW_TIMEOUT)
    {
        msgResultTimer++;
        if (msgResultTimer == MSG_VIEW_TIMEOUT)
        {
            cResult.setVisible(false);
            cResult.invalidate();
            presenter->setImgViewCmd(SEND_SSI_IMG_MODE);
        }
    }
}

//Called when the screen is done with transition/load
void SnImageViewView::afterTransition()
{
    // clear barcode buffer when into this screen
    while (presenter->getBarcode() != NULL)
    {
        presenter->clearBarcode();
    }
}

void SnImageViewView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnImageViewView::BarcodeComeIn(char * BarcodeData)
{
    switch (BarcodeData[0])
    {
    case ACTION_ATTR_ACK:
        presenter->setImgViewCmd(SEND_SSI_IMG_MODE);
        break;

    case ACTION_ATTR_NACK:
    case SSI_IMG_MODE_NACK:
        cHostFail.setVisible(true);
        cHostFail.invalidate();
        msgHostFailTimer = 0;
        break;

    case SSI_IMG_MODE_ACK:
        if (presenter->getLiveCapture() == PREVIEW_ENABLED)
        {
            labelWaitMsg.setTypedText(touchgfx::TypedText(T_IMGVIEW_06));
            labelWaitMsg.setVisible(true);
            labelWaitMsg.invalidate();
        }
        else
        {
            cWaitCapture.setVisible(true);
            cWaitCapture.invalidate();
        }
        break;

    case PREVIEW_IMG_COMPLETED:
        memcpy(Bitmap::dynamicBitmapGetAddress(bmpPreViewId), BMP_RX_BUFFER, PREIMG_SIZE);
        cPreViewImg.setVisible(true);
        cPreViewImg.invalidate();
        break;

    case TRIGGER_PRESSED:
        labelWaitMsg.setTypedText(touchgfx::TypedText(T_IMGVIEW_07));
        labelWaitMsg.setVisible(true);
        labelWaitMsg.invalidate();
        cWaitCapture.setVisible(false);
        cWaitCapture.invalidate();
        cPreViewImg.setVisible(false);
        cPreViewImg.invalidate();
        ccBack.setFocus(false);
        ccBack.invalidate();
        break;

    case IMG_COMPLETED:
        memcpy(Bitmap::dynamicBitmapGetAddress(bmpId), BMP_RX_BUFFER, IMG_SIZE);
        cViewImg.setVisible(true);
        cViewImg.invalidate();
        break;

    case SEND_IMG_ACK:
        textN_Result.setTypedText(touchgfx::TypedText(T_IMGVIEW_04));
        cResult.setVisible(true);
        cResult.invalidate();
        msgResultTimer = 0;
        break;

    case SEND_IMG_NACK:
        textN_Result.setTypedText(touchgfx::TypedText(T_IMGVIEW_05));
        cResult.setVisible(true);
        cResult.invalidate();
        msgResultTimer = 0;
        break;
    }
    presenter->clearBarcode();
}

void SnImageViewView::doForHomeKey()
{
presenter->keyPressed(KEYCODE_HOME);    
}

