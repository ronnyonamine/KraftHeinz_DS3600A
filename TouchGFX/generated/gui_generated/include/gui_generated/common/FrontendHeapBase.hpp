/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FRONTENDHEAPBASE_HPP
#define FRONTENDHEAPBASE_HPP

#include <common/Meta.hpp>
#include <common/Partition.hpp>
#include <mvp/MVPHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>



















#include <gui/common/FrontendApplication.hpp>
#include <gui/model/Model.hpp>

#include <gui/snsplash_screen/SnSplashView.hpp>
#include <gui/snsplash_screen/SnSplashPresenter.hpp>
#include <gui/snscanandentqty_screen/SnScanAndEntQtyView.hpp>
#include <gui/snscanandentqty_screen/SnScanAndEntQtyPresenter.hpp>
#include <gui/snscanandentqty_d_screen/SnScanAndEntQty_DView.hpp>
#include <gui/snscanandentqty_d_screen/SnScanAndEntQty_DPresenter.hpp>
#include <gui/snscanandentloc_screen/SnScanAndEntLocView.hpp>
#include <gui/snscanandentloc_screen/SnScanAndEntLocPresenter.hpp>
#include <gui/snscaninventory_screen/SnScanInventoryView.hpp>
#include <gui/snscaninventory_screen/SnScanInventoryPresenter.hpp>
#include <gui/snoutinmatch_screen/SnOutInMatchView.hpp>
#include <gui/snoutinmatch_screen/SnOutInMatchPresenter.hpp>
#include <gui/snimageview_screen/SnImageViewView.hpp>
#include <gui/snimageview_screen/SnImageViewPresenter.hpp>
#include <gui/sncfgmenu_screen/SnCfgMenuView.hpp>
#include <gui/sncfgmenu_screen/SnCfgMenuPresenter.hpp>
#include <gui/sncfgappsubmenu_screen/SnCfgAppSubMenuView.hpp>
#include <gui/sncfgappsubmenu_screen/SnCfgAppSubMenuPresenter.hpp>
#include <gui/sncfgboolparam_screen/SnCfgBoolParamView.hpp>
#include <gui/sncfgboolparam_screen/SnCfgBoolParamPresenter.hpp>
#include <gui/sncfgradioparam_screen/SnCfgRadioParamView.hpp>
#include <gui/sncfgradioparam_screen/SnCfgRadioParamPresenter.hpp>
#include <gui/sncfgcharparam_screen/SnCfgCharParamView.hpp>
#include <gui/sncfgcharparam_screen/SnCfgCharParamPresenter.hpp>
#include <gui/sncfgnumericparam_screen/SnCfgNumericParamView.hpp>
#include <gui/sncfgnumericparam_screen/SnCfgNumericParamPresenter.hpp>
#include <gui/sncfgstringparam_screen/SnCfgStringParamView.hpp>
#include <gui/sncfgstringparam_screen/SnCfgStringParamPresenter.hpp>
#include <gui/snfnkeyassign_screen/SnFnKeyAssignView.hpp>
#include <gui/snfnkeyassign_screen/SnFnKeyAssignPresenter.hpp>
#include <gui/snbarcodeprogress_screen/SnBarcodeProgressView.hpp>
#include <gui/snbarcodeprogress_screen/SnBarcodeProgressPresenter.hpp>
#include <gui/snscreensaver_screen/SnScreensaverView.hpp>
#include <gui/snscreensaver_screen/SnScreensaverPresenter.hpp>
#include <gui/snhomemenu_screen/SnHomeMenuView.hpp>
#include <gui/snhomemenu_screen/SnHomeMenuPresenter.hpp>
#include <gui/khmainscreen_screen/KHMainScreenView.hpp>
#include <gui/khmainscreen_screen/KHMainScreenPresenter.hpp>


/**
 * This class provides the memory that shall be used for memory allocations
 * in the frontend. A single instance of the FrontendHeap is allocated once (in heap
 * memory), and all other frontend objects such as views, presenters and data model are
 * allocated within the scope of this FrontendHeap. As such, the RAM usage of the entire
 * user interface is sizeof(FrontendHeap).
 *
 * @note The FrontendHeap reserves memory for the most memory-consuming presenter and
 * view only. The largest of these classes are determined at compile-time using template
 * magic. As such, it is important to add all presenters, views and transitions to the
 * type lists in this class.
 *
 */
class FrontendHeapBase : public touchgfx::MVPHeap
{
public:
    /**
     * A list of all view types. Must end with meta::Nil.
     * @note All view types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< SnSplashView,
            touchgfx::meta::TypeList< SnScanAndEntQtyView,
            touchgfx::meta::TypeList< SnScanAndEntQty_DView,
            touchgfx::meta::TypeList< SnScanAndEntLocView,
            touchgfx::meta::TypeList< SnScanInventoryView,
            touchgfx::meta::TypeList< SnOutInMatchView,
            touchgfx::meta::TypeList< SnImageViewView,
            touchgfx::meta::TypeList< SnCfgMenuView,
            touchgfx::meta::TypeList< SnCfgAppSubMenuView,
            touchgfx::meta::TypeList< SnCfgBoolParamView,
            touchgfx::meta::TypeList< SnCfgRadioParamView,
            touchgfx::meta::TypeList< SnCfgCharParamView,
            touchgfx::meta::TypeList< SnCfgNumericParamView,
            touchgfx::meta::TypeList< SnCfgStringParamView,
            touchgfx::meta::TypeList< SnFnKeyAssignView,
            touchgfx::meta::TypeList< SnBarcodeProgressView,
            touchgfx::meta::TypeList< SnScreensaverView,
            touchgfx::meta::TypeList< SnHomeMenuView,
            touchgfx::meta::TypeList< KHMainScreenView,
            touchgfx::meta::Nil > > > > > > > > > > > > > > > > > >
            > GeneratedViewTypes;

    /**
     * Determine (compile time) the View type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< GeneratedViewTypes >::type MaxGeneratedViewType;

    /**
     * A list of all presenter types. Must end with meta::Nil.
     * @note All presenter types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< SnSplashPresenter,
            touchgfx::meta::TypeList< SnScanAndEntQtyPresenter,
            touchgfx::meta::TypeList< SnScanAndEntQty_DPresenter,
            touchgfx::meta::TypeList< SnScanAndEntLocPresenter,
            touchgfx::meta::TypeList< SnScanInventoryPresenter,
            touchgfx::meta::TypeList< SnOutInMatchPresenter,
            touchgfx::meta::TypeList< SnImageViewPresenter,
            touchgfx::meta::TypeList< SnCfgMenuPresenter,
            touchgfx::meta::TypeList< SnCfgAppSubMenuPresenter,
            touchgfx::meta::TypeList< SnCfgBoolParamPresenter,
            touchgfx::meta::TypeList< SnCfgRadioParamPresenter,
            touchgfx::meta::TypeList< SnCfgCharParamPresenter,
            touchgfx::meta::TypeList< SnCfgNumericParamPresenter,
            touchgfx::meta::TypeList< SnCfgStringParamPresenter,
            touchgfx::meta::TypeList< SnFnKeyAssignPresenter,
            touchgfx::meta::TypeList< SnBarcodeProgressPresenter,
            touchgfx::meta::TypeList< SnScreensaverPresenter,
            touchgfx::meta::TypeList< SnHomeMenuPresenter,
            touchgfx::meta::TypeList< KHMainScreenPresenter,
            touchgfx::meta::Nil > > > > > > > > > > > > > > > > > >
            > GeneratedPresenterTypes;

    /**
     * Determine (compile time) the Presenter type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< GeneratedPresenterTypes >::type MaxGeneratedPresenterType;

    /**
     * A list of all transition types. Must end with meta::Nil.
     * @note All transition types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< touchgfx::NoTransition,
            touchgfx::meta::Nil
            > GeneratedTransitionTypes;

    /**
     * Determine (compile time) the Transition type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< GeneratedTransitionTypes >::type MaxGeneratedTransitionType;

    virtual void gotoStartScreen(FrontendApplication& app)
    {
        app.gotoSnSplashScreenNoTransition();
    }
protected:
    FrontendHeapBase(touchgfx::AbstractPartition& presenters, touchgfx::AbstractPartition& views, touchgfx::AbstractPartition& transitions, FrontendApplication& app)
        : MVPHeap(presenters, views, transitions, app)
    {

    }

};

#endif // FRONTENDHEAPBASE_HPP
