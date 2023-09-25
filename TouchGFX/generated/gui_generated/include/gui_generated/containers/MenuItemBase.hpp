/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MENUITEMBASE_HPP
#define MENUITEMBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class MenuItemBase : public touchgfx::Container
{
public:
    MenuItemBase();
    virtual ~MenuItemBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box boxBackGnd;
    touchgfx::TextArea textMenuItemInactive;
    touchgfx::TextArea textMenuItemActive;

private:

};

#endif // MENUITEMBASE_HPP
