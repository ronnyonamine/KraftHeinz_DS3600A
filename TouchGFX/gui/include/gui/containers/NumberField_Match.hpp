#ifndef NUMBERFIELD_MATCH_HPP
#define NUMBERFIELD_MATCH_HPP

#include <gui_generated/containers/NumberField_MatchBase.hpp>

class NumberField_Match : public NumberField_MatchBase
{
public:
    NumberField_Match();
    virtual ~NumberField_Match() {}

    virtual void initialize();
    void setNumber(uint16_t value);
    void setFocus(bool setting);

protected:
};

#endif // NUMBERFIELD_MATCH_HPP
