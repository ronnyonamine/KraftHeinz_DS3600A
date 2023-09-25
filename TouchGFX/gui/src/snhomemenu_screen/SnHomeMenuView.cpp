#include <gui/snhomemenu_screen/SnHomeMenuView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/platform_itf.h>
#include <gui/common/ZebraApplication.hpp>
#include <touchgfx/Color.hpp>
#include <gui/common/ConfigParam.hpp>

#define LAUNCH_SCREEN 1

extern "C" bool virtual_cfg_menu_lock;
/* Note -> This parameter defines the Home Key functionality. The system will
 * fill this parameter on run-time based on the registered applications, but
 * ONLY if this parameter is defined */

REGISTER_DESC_NUM(gblHomeKeyDesc,
                  0,
                  6,
                  false,
                  true,
                  "Home Key Launch",
                  NVAL(0x00, None),
                  NVAL(0x01, Navigator (Default)),
                  NVAL(0x02, ScanEnterQty),
                  NVAL(0x03, ScanQtyLoc),
                  NVAL(0x04, ScanInventory),
                  NVAL(0x05, OIMatch),
                  NVAL(0x06, ImageViewer))


REGISTER_PARAMETER(
     gblHomeKey,
     "Home Key Launch",
     "Home Key Launch",
     "Global",
     PARAM_TYPE_NUMERIC,
     0x00,
     1,
     false,
     gblHomeKeyDesc,
     0x01,
     7,
     user_cfg_set_home_key_launch,
     user_cfg_get_home_key_launch)

SnHomeMenuView::SnHomeMenuView() :
    selectItem(0),
    oldSelectItem(0)
{
    for(uint8_t i = 0; i < ZebraApplication::GetApplications().size(); i++)
    {
        ZebraApplication app = ZebraApplication::GetApplications()[i];
        ccMenuItems[i].setText(std::to_string(i+1) + " " + app.name);

        MenuItem[i] = &ccMenuItems[i];

        listLayout1.add(ccMenuItems[i]);
    }
}

void SnHomeMenuView::setupScreen()
{
    presenter->UpdateAllIcons();
    presenter->setCurrentScreen(SCAN_QTY_RESEND_DATA);
    selectNewItem();
    scrollCnt.setScrollbarWidth(4);
    dragScroll(-1);
    dragScroll(1);
    scrollCnt.invalidate();
}

void SnHomeMenuView::tearDownScreen()
{

}

void SnHomeMenuView::scrollListUp()
{
    selectItem = (selectItem == 0) ? 0 : selectItem - 1;
    dragScroll(oldSelectItem - selectItem);
    selectNewItem();
    oldSelectItem = selectItem;
}

void SnHomeMenuView::scrollListDown()
{
    selectItem = (selectItem == (ZebraApplication::GetApplications().size() - 1)) ? (ZebraApplication::GetApplications().size() - 1) : selectItem + 1;
    dragScroll(oldSelectItem - selectItem);
    selectNewItem();
    oldSelectItem = selectItem;
}

void SnHomeMenuView::scrollToItem(uint8_t item)
{
    uint8_t total_application = ZebraApplication::GetApplications().size();    //find total number of application
    
    if(item == '0')
        return;
    else if(item > ('0' + total_application))
        return;
        
    selectItem = item - '1';
    dragScroll(oldSelectItem - selectItem);
    selectNewItem();
    oldSelectItem = selectItem;
}

void SnHomeMenuView::handleKeyEvent(uint8_t key)
{
    /* Notifies presenter about key event. Do not perform any
    action from the View */
    if(!(virtual_cfg_menu_lock && (key == KEYCODE_ENTER) && (selectItem == (ZebraApplication::GetApplications().size() - 1))))
        presenter->keyPressed(key);
}

//Called when the screen is done with transition/load
void SnHomeMenuView::afterTransition()
{

}

void SnHomeMenuView::selectNewItem()
{
    for (uint8_t i = 0; i < ZebraApplication::GetApplications().size(); i++)
    {
        if((virtual_cfg_menu_lock) && (selectItem == (ZebraApplication::GetApplications().size() - 1)))
        {
            MenuItem[i]->GreyItem(selectItem == i);
        }
        else
        {
            MenuItem[i]->setFocus(selectItem == i);
        }
    }
}

void SnHomeMenuView::UpdateIcon(IconID_t IconId, IconStateID_t IconState)
{
    ccStatusBar.UpdateIcon(IconId, IconState);
}

void SnHomeMenuView::dragScroll(int drag)
{
    int16_t xPos = scrollCnt.getScrolledX();
    int16_t yOldPos = scrollCnt.getScrolledY();
    int16_t yNewPos = yOldPos + (64 * drag);
    DragEvent relative(DragEvent::DRAGGED, xPos, yOldPos, xPos, yNewPos);
    scrollCnt.handleDragEvent(relative);
}

void SnHomeMenuView::ChangeScreen()
{
    ZebraApplication::GetApplications()[0].transitionToApp();
}

uint8_t SnHomeMenuView::getSelectedEntry()
{
    return selectItem;
}
