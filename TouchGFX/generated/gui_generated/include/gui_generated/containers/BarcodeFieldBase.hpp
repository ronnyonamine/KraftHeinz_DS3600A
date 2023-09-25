/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef BARCODEFIELDBASE_HPP
#define BARCODEFIELDBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/Image.hpp>

class BarcodeFieldBase : public touchgfx::Container
{
public:
    BarcodeFieldBase();
    virtual ~BarcodeFieldBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box boxBackGnd;
    touchgfx::TextAreaWithOneWildcard textBarcode_S;
    touchgfx::TextAreaWithOneWildcard textBarcode_L;
    touchgfx::Image imgBarcode;
    touchgfx::TextAreaWithOneWildcard textBarcode_Name;
    touchgfx::Box boxCursor;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTBARCODE_S_SIZE = 30;
    touchgfx::Unicode::UnicodeChar textBarcode_SBuffer[TEXTBARCODE_S_SIZE];
    static const uint16_t TEXTBARCODE_L_SIZE = 5;
    touchgfx::Unicode::UnicodeChar textBarcode_LBuffer[TEXTBARCODE_L_SIZE];
    static const uint16_t TEXTBARCODE_NAME_SIZE = 30;
    touchgfx::Unicode::UnicodeChar textBarcode_NameBuffer[TEXTBARCODE_NAME_SIZE];

private:

};

#endif // BARCODEFIELDBASE_HPP
