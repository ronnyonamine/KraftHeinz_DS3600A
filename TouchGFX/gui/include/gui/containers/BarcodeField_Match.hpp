#ifndef BARCODEFIELD_MATCH_HPP
#define BARCODEFIELD_MATCH_HPP

#include <gui_generated/containers/BarcodeField_MatchBase.hpp>

class BarcodeField_Match : public BarcodeField_MatchBase
{
public:
    BarcodeField_Match();
    virtual ~BarcodeField_Match() {}

    virtual void initialize();
    void setText(char * string);

protected:

private:
    static const touchgfx::Unicode::UnicodeChar ELLIPSIS = 0x2026;
};

#endif // BARCODEFIELD_MATCH_HPP
