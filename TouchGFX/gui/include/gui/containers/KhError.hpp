#ifndef KHERROR_HPP
#define KHERROR_HPP

#include <gui_generated/containers/KhErrorBase.hpp>
#include <gui/containers/KHListItemContainer.hpp>  // Manual Edit - Module Specific

class KhError : public KhErrorBase
{
public:
    KhError();
    virtual ~KhError() {}

    virtual void initialize();

protected:
};

#endif // KHERROR_HPP
