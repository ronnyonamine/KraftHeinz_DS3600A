#include <gui/containers/NumberField_Match.hpp>
#include <gui/common/ColorPalette.hpp>

NumberField_Match::NumberField_Match()
{

}

void NumberField_Match::initialize()
{
    NumberField_MatchBase::initialize();
}

void NumberField_Match::setNumber(uint16_t value)
{
    Unicode::snprintf(textListBuffer, TEXTLIST_SIZE, "%d", value);
    textList.invalidate();
}

void NumberField_Match::setFocus(bool setting)
{
    if (setting)
    {
        textLabel.setColor(TEXT_LIGHT);
        textList.setColor(TEXT_LIGHT);
        boxBackGnd.setColor(PRIMARY_BLUE);
    }
    else
    {
        textLabel.setColor(TEXT_DARK);
        textList.setColor(TEXT_DARK);
        boxBackGnd.setColor(TEXT_LIGHT);
    }
    invalidate();
}
