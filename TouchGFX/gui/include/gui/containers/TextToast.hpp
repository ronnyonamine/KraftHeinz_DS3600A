#ifndef TEXTTOAST_HPP
#define TEXTTOAST_HPP

#include <gui_generated/containers/TextToastBase.hpp>

class TextToast : public TextToastBase
{
public:
    TextToast();
    virtual ~TextToast() {}

    virtual void initialize();
    void setText(uint8_t form);

protected:
};

#endif // TEXTTOAST_HPP
