#ifndef KHLEARNBARCODE_HPP
#define KHLEARNBARCODE_HPP

#include <gui_generated/containers/khLearnBarcodeBase.hpp>

class khLearnBarcode : public khLearnBarcodeBase
{
public:
    khLearnBarcode();
    virtual ~khLearnBarcode() {}

    virtual void initialize();
protected:
};

#endif // KHLEARNBARCODE_HPP
