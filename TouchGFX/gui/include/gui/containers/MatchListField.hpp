#ifndef MATCHLISTFIELD_HPP
#define MATCHLISTFIELD_HPP

#include <gui_generated/containers/MatchListFieldBase.hpp>

class MatchListField : public MatchListFieldBase
{
public:
    typedef enum
    {
        BARCODE,
        MATCHES,
        MISSING,
        UNEXPECTED
    } MatchListType_t;

    enum
    {
        NORMAL = 0,
        SET_DELETE = 0x40,
        SET_FOCUS = 0x80,
    } MatchListAction_t;

    MatchListField();
    virtual ~MatchListField() {}

    virtual void initialize();
    void setType(MatchListType_t type);
    void setAction(uint8_t action);
    void setText(uint16_t no, bool isEllipsis, char* bc_s, char* bc_l);

protected:

private:
    static const touchgfx::Unicode::UnicodeChar ELLIPSIS = 0x2026;
    uint8_t fieldType;
};

#endif // MATCHLISTFIELD_HPP
