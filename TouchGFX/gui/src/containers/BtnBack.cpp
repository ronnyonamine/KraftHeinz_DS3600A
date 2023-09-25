#include <gui/containers/BtnBack.hpp>
#include <gui/common/ColorPalette.hpp>
#include "BitmapDatabase.hpp"

BtnBack::BtnBack() :
    focusing(false)
{

}

void BtnBack::initialize()
{
    BtnBackBase::initialize();
}

bool BtnBack::setFocus(bool selected)
{
    if (selected)
    {
        boxBackGnd.setColor(PRIMARY_BLUE);
        imgBack.setBitmap(touchgfx::Bitmap(BITMAP_MDI_ARROW_BACK_SELECTED_ID));
    }
    else
    {
        boxBackGnd.setColor(TEXT_LIGHT);
        imgBack.setBitmap(touchgfx::Bitmap(BITMAP_MDI_ARROW_BACK_ID));
    }
    invalidate();
    focusing = selected;
    return (true);
}
