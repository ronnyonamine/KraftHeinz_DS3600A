#ifndef KHSPLASHSCREEN_HPP
#define KHSPLASHSCREEN_HPP

#include <gui_generated/containers/KhSplashScreenBase.hpp>

class KhSplashScreen : public KhSplashScreenBase
{
public:
    KhSplashScreen();
    virtual ~KhSplashScreen() {}

    virtual void initialize();
protected:
};

#endif // KHSPLASHSCREEN_HPP
