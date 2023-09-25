#include <gui/containers/InvtListField_Loc.hpp>
#include <gui/common/ColorPalette.hpp>
#include "BitmapDatabase.hpp"

InvtListField_Loc::InvtListField_Loc()
{

}

void InvtListField_Loc::initialize()
{
    InvtListField_LocBase::initialize();
}

void InvtListField_Loc::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        titelLoc.setColor(TEXT_LIGHT);
        imgLoc.setBitmap(touchgfx::Bitmap(BITMAP_LOCATION_HOVER_ID));
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        titelLoc.setColor(TEXT_MEDIUM);
        imgLoc.setBitmap(touchgfx::Bitmap(BITMAP_LOCATION_ACTIVE_ID));
    }
    invalidate();
}

void InvtListField_Loc::setText(std::string location)
{
    Unicode::UnicodeChar tempStr[TITELLOC_SIZE];
    int length = location.length();
    if (length < TITELLOC_SIZE)
        Unicode::strncpy(tempStr, location.c_str(), TITELLOC_SIZE - 1);
    else
    {
        Unicode::strncpy(tempStr, location.c_str() + (length - TITELLOC_SIZE + 1), TITELLOC_SIZE - 1);
        tempStr[0] = ELLIPSIS;    // show ..
    }
    Unicode::snprintf(titelLocBuffer, TITELLOC_SIZE, "%s", tempStr);
    invalidate();
}
