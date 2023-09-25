#ifndef SNCFGRADIOPARAMPRESENTER_HPP
#define SNCFGRADIOPARAMPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SnCfgRadioParamView;

class SnCfgRadioParamPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SnCfgRadioParamPresenter(SnCfgRadioParamView& v);

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

    virtual ~SnCfgRadioParamPresenter() {};

private:
    SnCfgRadioParamPresenter();

    SnCfgRadioParamView& view;
};

#endif // SNCFGRADIOPARAMPRESENTER_HPP
