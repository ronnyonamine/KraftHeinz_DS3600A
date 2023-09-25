#include <gui/containers/KhListRecordContainer.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <string>
#include <touchgfx/Color.hpp>

KhListRecordContainer::KhListRecordContainer()
{

}

void KhListRecordContainer::initialize()
{
    KhListRecordContainerBase::initialize();
}


void KhListRecordContainer::setAsHeader()
{
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(63, 83, 163));
    textDate.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textTime.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textLearnBarcode.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textVerifyBarcode.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textSuccess.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textReason.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textInitials.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    invalidate();
}

void KhListRecordContainer::selectThis()
{
    textDate.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textTime.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textLearnBarcode.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textVerifyBarcode.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textSuccess.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textReason.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textInitials.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    invalidate();
}

void KhListRecordContainer::deselectThis()
{
    textDate.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textTime.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textLearnBarcode.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textVerifyBarcode.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textSuccess.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textReason.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textInitials.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    invalidate();
}


void KhListRecordContainer::setupListElements(string date, string time, string learnbarcode, string verifybarcode, string success, string reason, string initials)
{
    setDefaultDate(date);
    setDefaultTime(time);
    setDefaultLearnBarcode(learnbarcode);
    setDefaultVerifyBarcode(verifybarcode);
    setDefaultSuccess(success);
    setDefaultReason(reason);
    setDefaultInitials(initials);
    //textDate.resizeToCurrentText();
    //invalidate();
}

void KhListRecordContainer::showText()
{
    Unicode::strncpy(textDateBuffer, textBuffer.getEWContent().c_str(), TEXTDATE_SIZE);
    if (textBuffer.isRightMore())
        textDateBuffer[TEXTDATE_SIZE - 1] = ELLIPSIS;
    if (textBuffer.isLeftMore())
        textDateBuffer[0] = ELLIPSIS;
    Unicode::strncpy(textTimeBuffer, textBuffer1.getEWContent().c_str(), TEXTTIME_SIZE);
    if (textBuffer1.isRightMore())
        textTimeBuffer[TEXTTIME_SIZE - 1] = ELLIPSIS;
    if (textBuffer1.isLeftMore())
        textTimeBuffer[0] = ELLIPSIS;
    Unicode::strncpy(textLearnBarcodeBuffer, textBuffer2.getEWContent().c_str(), TEXTLEARNBARCODE_SIZE);
    if (textBuffer2.isRightMore())
        textLearnBarcodeBuffer[TEXTLEARNBARCODE_SIZE - 1] = ELLIPSIS;
    if (textBuffer2.isLeftMore())
        textLearnBarcodeBuffer[0] = ELLIPSIS;
    Unicode::strncpy(textVerifyBarcodeBuffer, textBuffer3.getEWContent().c_str(), TEXTVERIFYBARCODE_SIZE);
    if (textBuffer3.isRightMore())
        textVerifyBarcodeBuffer[TEXTVERIFYBARCODE_SIZE - 1] = ELLIPSIS;
    if (textBuffer3.isLeftMore())
        textVerifyBarcodeBuffer[0] = ELLIPSIS;
    Unicode::strncpy(textSuccessBuffer, textBuffer4.getEWContent().c_str(), TEXTSUCCESS_SIZE);
    if (textBuffer4.isRightMore())
        textSuccessBuffer[TEXTSUCCESS_SIZE - 1] = ELLIPSIS;
    if (textBuffer4.isLeftMore())
        textSuccessBuffer[0] = ELLIPSIS;
    Unicode::strncpy(textReasonBuffer, textBuffer5.getEWContent().c_str(), TEXTREASON_SIZE);
    if (textBuffer5.isRightMore())
        textReasonBuffer[TEXTREASON_SIZE - 1] = ELLIPSIS;
    if (textBuffer5.isLeftMore())
        textReasonBuffer[0] = ELLIPSIS;
    Unicode::strncpy(textInitialsBuffer, textBuffer6.getEWContent().c_str(), TEXTINITIALS_SIZE);
    if (textBuffer6.isRightMore())
        textInitialsBuffer[TEXTINITIALS_SIZE - 1] = ELLIPSIS;
    if (textBuffer6.isLeftMore())
        textInitialsBuffer[0] = ELLIPSIS;

    textDate.invalidate();
    textTime.invalidate();
    textLearnBarcode.invalidate();
    textVerifyBarcode.invalidate();
    textSuccess.invalidate();
    textReason.invalidate();
    textInitials.invalidate();
}

void KhListRecordContainer::setDefaultDate(std::string text)
{
    textBuffer.setContent(text);
    Unicode::strncpy(textDateBuffer, textBuffer.getEWContent().c_str(), TEXTDATE_SIZE);
    if (textBuffer.isRightMore())
        textDateBuffer[TEXTDATE_SIZE - 1] = ELLIPSIS;
    if (textBuffer.isLeftMore())
        textDateBuffer[0] = ELLIPSIS;
    textDate.invalidate();
}

void KhListRecordContainer::setDefaultTime(std::string text)
{
    textBuffer1.setContent(text);
    Unicode::strncpy(textTimeBuffer, textBuffer1.getEWContent().c_str(), TEXTTIME_SIZE);
    if (textBuffer1.isRightMore())
        textTimeBuffer[TEXTTIME_SIZE - 1] = ELLIPSIS;
    if (textBuffer1.isLeftMore())
        textTimeBuffer[0] = ELLIPSIS;
    textTime.invalidate();
}

void KhListRecordContainer::setDefaultLearnBarcode(std::string text)
{
    textBuffer2.setContent(text);
    Unicode::strncpy(textLearnBarcodeBuffer, textBuffer2.getEWContent().c_str(), TEXTLEARNBARCODE_SIZE);
    if (textBuffer2.isRightMore())
        textLearnBarcodeBuffer[TEXTLEARNBARCODE_SIZE - 1] = ELLIPSIS;
    if (textBuffer2.isLeftMore())
        textLearnBarcodeBuffer[0] = ELLIPSIS;
    textLearnBarcode.invalidate();
}

void KhListRecordContainer::setDefaultVerifyBarcode(std::string text)
{
    textBuffer3.setContent(text);
    Unicode::strncpy(textVerifyBarcodeBuffer, textBuffer3.getEWContent().c_str(), TEXTVERIFYBARCODE_SIZE);
    if (textBuffer3.isRightMore())
        textVerifyBarcodeBuffer[TEXTVERIFYBARCODE_SIZE - 1] = ELLIPSIS;
    if (textBuffer3.isLeftMore())
        textVerifyBarcodeBuffer[0] = ELLIPSIS;
    textVerifyBarcode.invalidate();
}

void KhListRecordContainer::setDefaultSuccess(std::string text)
{
    textBuffer4.setContent(text);
    Unicode::strncpy(textSuccessBuffer, textBuffer4.getEWContent().c_str(), TEXTSUCCESS_SIZE);
    if (textBuffer4.isRightMore())
        textSuccessBuffer[TEXTSUCCESS_SIZE - 1] = ELLIPSIS;
    if (textBuffer4.isLeftMore())
        textSuccessBuffer[0] = ELLIPSIS;
    textSuccess.invalidate();
}

void KhListRecordContainer::setDefaultReason(std::string text)
{
    textBuffer5.setContent(text);

    Unicode::strncpy(textReasonBuffer, textBuffer5.getContent(), TEXTREASON_SIZE);
    //if (textBuffer5.isRightMore())
    //    textReasonBuffer[TEXTREASON_SIZE - 1] = ELLIPSIS;
    //if (textBuffer5.isLeftMore())
    //    textReasonBuffer[0] = ELLIPSIS;
    textReason.invalidate();
}

void KhListRecordContainer::setDefaultInitials(std::string text)
{
    textBuffer6.setContent(text);
    Unicode::strncpy(textInitialsBuffer, textBuffer6.getEWContent().c_str(), TEXTINITIALS_SIZE);
    if (textBuffer6.isRightMore())
        textInitialsBuffer[TEXTINITIALS_SIZE - 1] = ELLIPSIS;
    if (textBuffer6.isLeftMore())
        textInitialsBuffer[0] = ELLIPSIS;
    textInitials.invalidate();
}