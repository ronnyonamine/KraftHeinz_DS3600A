#include <gui/containers/KhBottomBar.hpp>

KhBottomBar::KhBottomBar()
{

}

void KhBottomBar::initialize()
{
    KhBottomBarBase::initialize();
}

void KhBottomBar::showDot()
{
    orangeDot1.setVisible(true);
    orangeDot1.invalidate();
    digitalClock1.setVisible(false);
    digitalClock1.invalidate();
}

void KhBottomBar::hideDot()
{
    orangeDot1.setVisible(false);
    orangeDot1.invalidate();
    digitalClock1.setVisible(true);
    digitalClock1.invalidate();
}
