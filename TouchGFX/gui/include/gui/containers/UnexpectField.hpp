#ifndef UNEXPECTFIELD_HPP
#define UNEXPECTFIELD_HPP

#include <gui_generated/containers/UnexpectFieldBase.hpp>

class UnexpectField : public UnexpectFieldBase
{
public:
    UnexpectField();
    virtual ~UnexpectField() {}

    virtual void initialize();
    void setValue(uint16_t value);
    void setCue(bool cueing);

protected:
};

#endif // UNEXPECTFIELD_HPP
