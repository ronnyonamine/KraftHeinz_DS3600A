/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SNSCANANDENTLOCVIEWBASE_HPP
#define SNSCANANDENTLOCVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/snscanandentloc_screen/SnScanAndEntLocPresenter.hpp>
#include <gui/containers/SnBackGnd.hpp>
#include <gui/containers/StatusBar.hpp>
#include <gui/containers/BarcodeField_Loc.hpp>
#include <gui/containers/NumberField_Loc.hpp>
#include <gui/containers/LocationField_Loc.hpp>
#include <gui/containers/BtnBack.hpp>
#include <gui/containers/TextToast.hpp>
#include <gui/containers/SuccessCue.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/containers/BluetoothPopup.hpp>
#include <touchgfx/widgets/BoxWithBorder.hpp>

class SnScanAndEntLocViewBase : public touchgfx::View<SnScanAndEntLocPresenter>
{
public:
    SnScanAndEntLocViewBase();
    virtual ~SnScanAndEntLocViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    SnBackGnd ccBackGnd;
    StatusBar ccStatusBar;
    BarcodeField_Loc ccBarcodeField;
    NumberField_Loc ccQtyField;
    LocationField_Loc ccLocationField;
    BtnBack ccBack;
    TextToast ccToastQTY;
    TextToast ccToastLocation;
    TextToast ccToastBarcode;
    SuccessCue ccSuccessCue;
    touchgfx::Container cQTYView;
    touchgfx::Box boxBackGnd;
    touchgfx::TextArea textLocation;
    touchgfx::TextArea textNormal;
    touchgfx::TextAreaWithOneWildcard textQTY;
    touchgfx::TextAreaWithOneWildcard textLOC;
    BluetoothPopup ccBTPopup;
    touchgfx::Container qTYAdjust;
    touchgfx::BoxWithBorder boxWithBorder1;
    touchgfx::BoxWithBorder boxWithBorder2;
    touchgfx::BoxWithBorder boxWithBorder3;
    touchgfx::TextAreaWithTwoWildcards textArea1;
    touchgfx::TextArea textArea2;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTQTY_SIZE = 5;
    touchgfx::Unicode::UnicodeChar textQTYBuffer[TEXTQTY_SIZE];
    static const uint16_t TEXTLOC_SIZE = 5;
    touchgfx::Unicode::UnicodeChar textLOCBuffer[TEXTLOC_SIZE];
    static const uint16_t TEXTAREA1BUFFER1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea1Buffer1[TEXTAREA1BUFFER1_SIZE];
    static const uint16_t TEXTAREA1BUFFER2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea1Buffer2[TEXTAREA1BUFFER2_SIZE];

private:

};

#endif // SNSCANANDENTLOCVIEWBASE_HPP
