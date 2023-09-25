#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include <gui/common/IconEnumDefine.hpp>
#include <gui/common/FrontendApplication.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}

    virtual ~ModelListener() {}

    virtual void UpdateIcon(IconID_t IconId, IconStateID_t IconState) {}

    inline void ActivateScreensaver (void)
    {
        application().gotoSnScreensaverScreenNoTransition();
    }

    inline void DeactivateScreensaver (void)
    {
        application().restoreLastScreen();
    }

    virtual void MoveToHomeScreen(void) {}
    virtual void BarcodeComeIn(char * BarcodeData) {}
    inline bool storeParamValue (uint16_t index, uint8_t* buff, uint16_t len)
    {
      return model->setConfigParamValue(index, buff, len);
    }
    inline uint8_t retrieveParamValue (uint16_t index, uint8_t* buff)
    {
      return model->getConfigParamValue(index, buff);
    }
    
    void bind(Model* m)
    {
        model = m;
    }

protected:
    Model* model;

private:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }
};

#endif // MODELLISTENER_HPP
