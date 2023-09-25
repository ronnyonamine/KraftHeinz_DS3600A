#ifndef SNCFGRADIOPARAMVIEW_HPP
#define SNCFGRADIOPARAMVIEW_HPP

#include <gui_generated/sncfgradioparam_screen/SnCfgRadioParamViewBase.hpp>
#include <gui/sncfgradioparam_screen/SnCfgRadioParamPresenter.hpp>

class SnCfgRadioParamView : public SnCfgRadioParamViewBase
{
public:
    SnCfgRadioParamView();
    virtual ~SnCfgRadioParamView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SNCFGRADIOPARAMVIEW_HPP
