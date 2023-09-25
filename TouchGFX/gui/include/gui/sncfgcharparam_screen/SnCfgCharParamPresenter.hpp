#ifndef SNCFGCHARPARAMPRESENTER_HPP
#define SNCFGCHARPARAMPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/KeypadHandler.hpp>

using namespace touchgfx;

class SnCfgCharParamView;

class SnCfgCharParamPresenter : public touchgfx::Presenter, public ModelListener, public KeypadHandler
{
public:
    SnCfgCharParamPresenter(SnCfgCharParamView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();
    
    virtual void UpdateAllIcons();
    virtual void UpdateIcon(IconID_t IconId, IconStateID_t IconState);
    virtual void BarcodeComeIn(char * BarcodeData);
    virtual char * getBarcode(void);
    virtual void clearBarcode(void);
    virtual void setLocDelimiter(uint8_t RadioOnItem, char user_define);
    virtual uint8_t getLocDelimiter(void);
    virtual uint8_t getLocDelimiterDefine(void);
    virtual void setCurrentScreen(uint32_t CurrentScreen);
    virtual uint8_t getHomeKeyLaunch(void);
    virtual void setBackArrowActive(bool setting);
    
    void handleDownKey();
    void handleUpKey();
    void handleEnterKey();
    void handleBackKey();
    void handleEscKey();
    void handleLeftKey();
    void handleRightKey();
    void handleBkspKey();

    virtual ~SnCfgCharParamPresenter() {};

private:
    SnCfgCharParamPresenter();

    SnCfgCharParamView& view;
};

#endif // SNCFGCHARPARAMPRESENTER_HPP
