#ifndef SNSPLASHPRESENTER_HPP
#define SNSPLASHPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SnSplashView;

class SnSplashPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SnSplashPresenter(SnSplashView& v);

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
    virtual void signal();
    virtual bool getScannerMsgRxStatus();

    virtual ~SnSplashPresenter() {};

private:
    SnSplashPresenter();

    SnSplashView& view;
};

#endif // SNSPLASHPRESENTER_HPP
