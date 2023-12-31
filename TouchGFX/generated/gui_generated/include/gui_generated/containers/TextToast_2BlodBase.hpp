/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef TEXTTOAST_2BLODBASE_HPP
#define TEXTTOAST_2BLODBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class TextToast_2BlodBase : public touchgfx::Container
{
public:
    TextToast_2BlodBase();
    virtual ~TextToast_2BlodBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box boxBackGnd;
    touchgfx::TextArea textRegular;
    touchgfx::TextArea textBlod_1;
    touchgfx::TextArea textBlod_2;

private:

};

#endif // TEXTTOAST_2BLODBASE_HPP
