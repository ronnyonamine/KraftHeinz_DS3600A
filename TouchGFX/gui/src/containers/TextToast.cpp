#include <gui/containers/TextToast.hpp>
#include <texts/TextKeysAndLanguages.hpp>

TextToast::TextToast()
{

}

void TextToast::initialize()
{
    TextToastBase::initialize();
}

void TextToast::setText(uint8_t form)
{
    switch (form)
    {
    case 0:     // Press ENT to confirm QTY
        textRegular.setPosition(0, 10, 288, 29);
        textRegular.setTypedText(touchgfx::TypedText(T_TOAST_00));
        textBlod.setPosition(81, 10, 39, 29);
        textBlod.setTypedText(touchgfx::TypedText(T_TOAST_01));
        textBlod.setVisible(true);
        break;

    case 1:     // Press ENT to confirm barcode
        textRegular.setPosition(0, 10, 288, 29);
        textRegular.setTypedText(touchgfx::TypedText(T_TOAST_02));
        textBlod.setPosition(63, 10, 39, 29);
        textBlod.setTypedText(touchgfx::TypedText(T_TOAST_01));
        textBlod.setVisible(true);
        break;

    case 2:     // Batch mode ON
        textRegular.setPosition(0, 10, 288, 29);
        textRegular.setTypedText(touchgfx::TypedText(T_TOAST_03));
        textBlod.setPosition(184, 10, 39, 29);
        textBlod.setTypedText(touchgfx::TypedText(T_TOAST_03_B1));
        textBlod.setVisible(true);
        break;

    case 3:     // Press ESC to Exit List
        textRegular.setPosition(0, 10, 288, 29);
        textRegular.setTypedText(touchgfx::TypedText(T_TOAST_04));
        textBlod.setVisible(false);
        break;

    case 4:     // Press ENT to confirm location
        textRegular.setPosition(0, 10, 288, 29);
        textRegular.setTypedText(touchgfx::TypedText(T_TOAST_05));
        textBlod.setPosition(63, 10, 39, 29);
        textBlod.setTypedText(touchgfx::TypedText(T_TOAST_01));
        textBlod.setVisible(true);
        break;

    case 5:     // Press ENT to finish Outside
        textRegular.setPosition(0, 10, 288, 29);
        textRegular.setTypedText(touchgfx::TypedText(T_TOAST_07));
        textBlod.setPosition(73, 10, 39, 29);
        textBlod.setTypedText(touchgfx::TypedText(T_TOAST_01));
        textBlod.setVisible(true);
        break;

    case 6:     // Deleting...
        textRegular.setPosition(0, 10, 288, 29);
        textRegular.setTypedText(touchgfx::TypedText(T_TOAST_08));
        textBlod.setVisible(false);
        break;

    case 7:     // Pull Trigger to capture Image
        textRegular.setPosition(0, 10, 288, 29);
        textRegular.setTypedText(touchgfx::TypedText(T_TOAST_10));
        textBlod.setPosition(46, 10, 70, 29);
        textBlod.setTypedText(touchgfx::TypedText(T_TOAST_10_B1));
        textBlod.setVisible(true);
        break;

    case 8:     // Item Match Limit Reached
        textRegular.setPosition(0, 10, 288, 29);
        textRegular.setTypedText(touchgfx::TypedText(T_TOAST_13));
        textBlod.setVisible(false);
        break;
    }
    invalidate();
}
