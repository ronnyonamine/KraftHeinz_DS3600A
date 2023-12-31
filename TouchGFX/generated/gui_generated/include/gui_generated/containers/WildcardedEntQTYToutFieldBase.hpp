/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef WILDCARDEDENTQTYTOUTFIELDBASE_HPP
#define WILDCARDEDENTQTYTOUTFIELDBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class WildcardedEntQTYToutFieldBase : public touchgfx::Container
{
public:
    WildcardedEntQTYToutFieldBase();
    virtual ~WildcardedEntQTYToutFieldBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box boxBackGnd_1;
    touchgfx::Box boxBackGnd;
    touchgfx::TextAreaWithOneWildcard textLabel;
    touchgfx::TextAreaWithOneWildcard textTime;
    touchgfx::TextArea textOR;
    touchgfx::Box boxCursor;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTLABEL_SIZE = 12;
    touchgfx::Unicode::UnicodeChar textLabelBuffer[TEXTLABEL_SIZE];
    static const uint16_t TEXTTIME_SIZE = 24;
    touchgfx::Unicode::UnicodeChar textTimeBuffer[TEXTTIME_SIZE];

private:

};

#endif // WILDCARDEDENTQTYTOUTFIELDBASE_HPP
