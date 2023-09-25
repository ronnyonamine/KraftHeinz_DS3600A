#include <gui/containers/MatchListTitle.hpp>
#include <texts/TextKeysAndLanguages.hpp>

MatchListTitle::MatchListTitle()
{

}

void MatchListTitle::initialize()
{
    MatchListTitleBase::initialize();
}

void MatchListTitle::setText(uint8_t type)
{
    switch (type)
    {
    case 0:     // Unexpected
        textTitle.setTypedText(touchgfx::TypedText(T_MATCHLISTTITLE_01));
        break;

    case 1:     // Missing
        textTitle.setTypedText(touchgfx::TypedText(T_MATCHLISTTITLE_02));
        break;

    case 2:     // Matched
        textTitle.setTypedText(touchgfx::TypedText(T_MATCHLISTTITLE_03));
        break;
    }

    invalidate();
}
