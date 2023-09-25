#include <gui/snsplash_screen/SnSplashView.hpp>
#include <gui/snsplash_screen/SnSplashPresenter.hpp>
#include <gui/common/ConfigParam.hpp>
#include <gui/common/ZebraApplication.hpp>

SnSplashPresenter::SnSplashPresenter(SnSplashView& v)
    : view(v)
{

}

void SnSplashPresenter::activate()
{
  ConfigParam::Sort();
  ZebraApplication::Sort();
}

void SnSplashPresenter::deactivate()
{

}

void SnSplashPresenter::signal()
{
   model->setSplashScreenActive(true);
}

bool SnSplashPresenter::getScannerMsgRxStatus()
{
   return(model->getScannerMsgRxStatus());
}