#include <gui/containers/MatchField.hpp>
#include <gui/common/ColorPalette.hpp>

MatchField::MatchField()
{

}

void MatchField::initialize()
{
    MatchFieldBase::initialize();
}

void MatchField::setValue(uint16_t inside, uint16_t outside)
{
    Unicode::snprintf(textMatchedBuffer, TEXTMATCHED_SIZE, "%d/%d", inside, outside);
    textMatched.invalidate();
}

void MatchField::setCue(bool cueing)
{
    if (cueing)
    {
        boxBackGnd.setColor(STATES_SUCCESS);
        textMatched.setColor(TEXT_LIGHT);
        textLabel.setColor(TEXT_LIGHT);
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        textMatched.setColor(TEXT_MEDIUM);
        textLabel.setColor(TEXT_MEDIUM);
    }
    invalidate();
}

