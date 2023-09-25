/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SNIMAGEVIEWVIEWBASE_HPP
#define SNIMAGEVIEWVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/snimageview_screen/SnImageViewPresenter.hpp>
#include <gui/containers/SnBackGnd.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/containers/TextToast.hpp>
#include <gui/containers/StatusBar.hpp>
#include <gui/containers/BtnBack.hpp>
#include <gui/containers/TextToast_2Blod.hpp>

class SnImageViewViewBase : public touchgfx::View<SnImageViewPresenter>
{
public:
    SnImageViewViewBase();
    virtual ~SnImageViewViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    SnBackGnd ccBackGnd;
    touchgfx::TextArea labelWaitMsg;
    touchgfx::Container cPreViewImg;
    touchgfx::Box boxBackGnd_PreView;
    touchgfx::Image imgPreView;
    TextToast ccToast_PreView;
    StatusBar ccStatusBar;
    BtnBack ccBack;
    touchgfx::Container cCheckHost;
    touchgfx::Box boxBackGnd_Check;
    touchgfx::Box boxMark_Check;
    touchgfx::TextArea textN_Check;
    touchgfx::TextArea textH1_Check;
    touchgfx::TextArea textH2_Check;
    touchgfx::TextArea labelExit;
    touchgfx::TextArea labelDone;
    touchgfx::TextArea subLabelBKSP;
    touchgfx::TextArea subLabelENT;
    touchgfx::Container cHostFail;
    touchgfx::Box boxBackGnd_Fail;
    touchgfx::Box boxMark_Fail;
    touchgfx::TextArea textN_Fail;
    touchgfx::TextArea textH1_Fail;
    touchgfx::TextArea textH2_Fail;
    touchgfx::Container cWaitCapture;
    touchgfx::Box boxBackGnd_Wait;
    touchgfx::TextArea textN_Wait;
    touchgfx::TextArea textH_Wait;
    touchgfx::Container cViewImg;
    touchgfx::Box boxBackGnd_View;
    touchgfx::Image imgView;
    TextToast_2Blod ccToast_View;
    touchgfx::Container cResult;
    touchgfx::Box boxBackGnd_Result;
    touchgfx::TextArea textN_Result;

private:

};

#endif // SNIMAGEVIEWVIEWBASE_HPP
