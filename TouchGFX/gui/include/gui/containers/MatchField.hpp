#ifndef MATCHFIELD_HPP
#define MATCHFIELD_HPP

#include <gui_generated/containers/MatchFieldBase.hpp>

class MatchField : public MatchFieldBase
{
public:
    MatchField();
    virtual ~MatchField() {}

    virtual void initialize();
    void setValue(uint16_t inside, uint16_t outside);
    void setCue(bool cueing);

protected:
};

#endif // MATCHFIELD_HPP
