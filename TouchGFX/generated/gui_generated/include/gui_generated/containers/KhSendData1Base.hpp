/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef KHSENDDATA1BASE_HPP
#define KHSENDDATA1BASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class KhSendData1Base : public touchgfx::Container
{
public:
    KhSendData1Base();
    virtual ~KhSendData1Base() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box boxBackGnd;
    touchgfx::TextArea textSendData;

private:

};

#endif // KHSENDDATA1BASE_HPP
