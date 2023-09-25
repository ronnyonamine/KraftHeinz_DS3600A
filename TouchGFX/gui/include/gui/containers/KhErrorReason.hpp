#ifndef KHERRORREASON_HPP
#define KHERRORREASON_HPP

#include <gui_generated/containers/KhErrorReasonBase.hpp>
#include <gui/containers/KHListItemContainer.hpp>  // Manual Edit - Module Specific

class KhErrorReason : public KhErrorReasonBase
{
public:
    KhErrorReason();
    virtual ~KhErrorReason() {}

    virtual void initialize();
    void loadOptions();
    void handleKeyEvent(uint8_t key);
    int getSelection();
protected:
    static const int numberOfListElements = 4;
    int menuIndex = 0;
    KhListItemContainer listElements[numberOfListElements];
};

#endif // KHERRORREASON_HPP
