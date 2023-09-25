#ifndef INVENTTOAST_HPP
#define INVENTTOAST_HPP

#include <gui_generated/containers/InventToastBase.hpp>

class InventToast : public InventToastBase
{
public:
    InventToast();
    virtual ~InventToast() {}

    virtual void initialize();
protected:
};

#endif // INVENTTOAST_HPP
