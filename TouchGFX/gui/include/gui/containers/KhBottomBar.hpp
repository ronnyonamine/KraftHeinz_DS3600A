#ifndef KHBOTTOMBAR_HPP
#define KHBOTTOMBAR_HPP

#include <gui_generated/containers/KhBottomBarBase.hpp>

class KhBottomBar : public KhBottomBarBase
{
public:
    KhBottomBar();
    virtual ~KhBottomBar() {}

    virtual void initialize();
    void showDot();
    void hideDot();
protected:
};

#endif // KHBOTTOMBAR_HPP
