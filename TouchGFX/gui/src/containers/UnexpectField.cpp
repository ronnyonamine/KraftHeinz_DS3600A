#include <gui/containers/UnexpectField.hpp>
#include <gui/common/ColorPalette.hpp>

UnexpectField::UnexpectField()
{

}

void UnexpectField::initialize()
{
    UnexpectFieldBase::initialize();
}

void UnexpectField::setValue(uint16_t value)
{
    Unicode::snprintf(textUnexpectBuffer, TEXTUNEXPECT_SIZE, "%d", value);
    textUnexpect.invalidate();
}

void UnexpectField::setCue(bool cueing)
{
    if (cueing)
    {
        boxBackGnd.setColor(STATES_ERROR);
        textUnexpect.setColor(TEXT_LIGHT);
        textLabel.setColor(TEXT_LIGHT);
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textUnexpect.setColor(TEXT_MEDIUM);
        textLabel.setColor(TEXT_MEDIUM);
    }
    invalidate();
}

