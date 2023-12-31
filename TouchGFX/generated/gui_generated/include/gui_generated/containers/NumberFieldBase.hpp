/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef NUMBERFIELDBASE_HPP
#define NUMBERFIELDBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class NumberFieldBase : public touchgfx::Container
{
public:
    NumberFieldBase();
    virtual ~NumberFieldBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box boxBackGnd;
    touchgfx::TextArea textLabel;
    touchgfx::TextAreaWithOneWildcard textEditQty;
    touchgfx::Box boxCursor;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTEDITQTY_SIZE = 5;
    touchgfx::Unicode::UnicodeChar textEditQtyBuffer[TEXTEDITQTY_SIZE];

private:

};

#endif // NUMBERFIELDBASE_HPP
