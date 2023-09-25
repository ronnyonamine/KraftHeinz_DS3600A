#ifndef KHMENU_HPP
#define KHMENU_HPP

#include <gui_generated/containers/KhMenuBase.hpp>
#include <gui/containers/KHListItemContainer.hpp>  // Manual Edit - Module Specific

class KhMenu : public KhMenuBase
{
public:
    KhMenu();
    virtual ~KhMenu() {}

    virtual void initialize();
    void loadOptions();
    void handleKeyEvent(uint8_t key);
    int getSelection();
protected:
    static const int numberOfListElements = 4;
    int menuIndex = 0;
    KhListItemContainer listElements[numberOfListElements];
};

#endif // KHMENU_HPP
