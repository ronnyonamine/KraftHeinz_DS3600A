/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef BARCODEFIELD_MATCHBASE_HPP
#define BARCODEFIELD_MATCHBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/Image.hpp>

class BarcodeField_MatchBase : public touchgfx::Container
{
public:
    BarcodeField_MatchBase();
    virtual ~BarcodeField_MatchBase() {}
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
    touchgfx::Box boxBackGnd_1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTBARCODE_S_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textBarcode_SBuffer[TEXTBARCODE_S_SIZE];
    static const uint16_t TEXTBARCODE_L_SIZE = 5;
    touchgfx::Unicode::UnicodeChar textBarcode_LBuffer[TEXTBARCODE_L_SIZE];

private:

};

#endif // BARCODEFIELD_MATCHBASE_HPP
