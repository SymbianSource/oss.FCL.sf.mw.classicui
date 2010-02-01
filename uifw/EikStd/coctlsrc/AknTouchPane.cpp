/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Implementation of the concrete touch pane class.
*
*/


// INCLUDE FILES
#include <eikaufty.h>   // MEikAppUiFactory
#include <eikenv.h>     // CEikonEnv
#include <eikapp.h>     // CEikApplication
#include <eikpanic.h>
#include <AknCapServerClient.h> // RAknUiServer
#include <barsread.h>           // TResourceReader
#include <AknDef.h>             // View ids
#include <AknsUtils.h>
#include <AknsDrawUtils.h>
#include <AknsFrameBackgroundControlContext.h>
#include <aknview.h>            // CAknView
#include <aknViewAppUi.h>       // CAknViewAppUi
#include <StringLoader.h>       // StringLoader
#include <hlplch.h>             // HlpLauncher
#include <AknSgcc.h>
#include <AknUtils.h>
#include <AknStatuspaneUtils.h>
#include <aknbutton.h>
#include <akntoolbar.h>
#include <aknfeppensupportinterface.h> // MAknFepPenSupportInterface
#include <AknCapServerDefs.h>

#include <AknTasHook.h> // for testability hooks
#include <avkon.mbg>
#include <avkon.rsg>
#include <aknpriv.rsg>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <gfxtranseffect/gfxtranseffect.h> 
#include <akntranseffect.h>
#include <akntransitionutils.h>

#include "touchtoolbardata.h"

#include "akntouchpane.hrh"
#include "akntouchpane.h"

#ifdef RD_SCALABLE_UI_V2

const TInt KDisableToolbar = 0xfff1;
const TInt KEnableToolbar = 0xfff2;

// UIDs for contacts application.
#ifdef RD_PHONEBOOK2
#define KAknTouchPaneContactsAppUid TUid::Uid(0x101f4cce)
#else
#define KAknTouchPaneContactsAppUid TUid::Uid(0x101f87b1)
#endif
#define KAknTouchPaneContactsViewUid TUid::Uid(1)

// UIDs for dialler application.
#define KAknTouchPaneDiallerAppUid TUid::Uid(0x100058B3)
#define KAknTouchPaneDiallerViewUid TUid::Uid(0x10282D81)
#define KTouchPaneDiallerVievCommand TUid::Uid(0x1)

#define KAknTouchPaneHelpAppUid TUid::Uid(0x10005234)

#define KAknTouchPaneAutoLockAppUid TUid::Uid(0x100059B5)


// Class for storing touch pane item description.
class TAknTouchPaneItem
    {
public:

    TAknTouchPaneItem()
        : iPriority( -1 ),
          iId( ETouchPaneElementNone ),
          iPlugin( NULL ) {}

    TInt iPriority;
    TUint iId;
    TUint iPlugin;
    };

// Enumeration for touch pane flags.
enum TAknTouchPaneFlags
    {
    ENoAutomaticVisibilityChanges   = 0,
    ETouchPaneActive                = 1,
    EHasForeground                  = 2,
    EShellIconActive                = 3,
    ESwapperIconActive              = 4,
    EIdleViewIconActive             = 5,
    EDiallerIconActive              = 6,
    ERotateIconActive               = 7,
    EHelpIconActive                 = 8,
    EInputMethodIconActive          = 9,
    EToolbarIconActive              = 10,
    EContactsIconActive            = 11
    };

#endif // RD_SCALABLE_UI_V2

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// RectFromLayout
// Gets a rect by mapping the given component layout with the given parent
// rect.
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
TRect RectFromLayout( const TRect& aParent,
    const TAknWindowComponentLayout& aComponentLayout )
    {
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParent, aComponentLayout.LayoutLine() );
    return layoutRect.Rect();
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// Reads default touch pane content from the resources.
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
TUint ReadDefaultTouchPaneContentL( RArray<TAknTouchPaneItem>& aItems )
    {
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_AKNPRIV_TOUCHPANE );
    TUint flags = reader.ReadUint32();
    
    TAknTouchPaneItem item;
    for ( TUint itemCount = reader.ReadInt16(); itemCount > 0; itemCount-- )
        {
        TUint version = reader.ReadUint8();
        if ( version != 1 )
            {
            User::Leave( KErrNotSupported );
            }

        item.iPriority = reader.ReadUint8();
        item.iId = reader.ReadUint8();
        item.iPlugin = reader.ReadUint32();
        aItems.AppendL( item );
        }

    CleanupStack::PopAndDestroy(); // reader
    return flags;
    };
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// Reads the given resource and modifies the given item set based on the
// customizations specified in the resource.
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void ReadCustomTouchPaneContentL( TInt aResourceId,
    RArray<TAknTouchPaneItem>& aItems, TBool aAllowCustomization )
    {
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, aResourceId );

    // Check resource version.
    const TUint version = reader.ReadUint8();
    if ( version != 1 )
        {
        User::Leave( KErrNotSupported );
        }

    // Read application specific touch pane flags.
    const TUint flags = reader.ReadUint32();

    if ( flags & EAknNoTouchPane )
        {
        aItems.Reset();
        }
    else if ( aAllowCustomization && ( flags & EAknCustomTouchPane ) )
        {
        const TInt itemCount = reader.ReadInt16();
        for ( TInt ii = itemCount; ii > 0; --ii )
            {
            // Read custom item.
            const TInt version = reader.ReadInt8();
            if ( version != 1 )
                {
                User::Leave( KErrNotSupported );
                }
            const TUint id = reader.ReadUint8();
            const TUint plugin = reader.ReadUint32();

            // Find optional item with lowest priority.
            TInt optionalItemPriority = 0;
            TInt optionalItemIndex = -1;
            for ( TInt jj = aItems.Count() - 1; jj >= 0; --jj )
                {
                if ( aItems[jj].iPriority > optionalItemPriority )
                    {
                    optionalItemPriority = aItems[jj].iPriority;
                    optionalItemIndex = jj;
                    }
                }

            // Replace optional item.
            if ( optionalItemIndex >= 0 )
                {
                aItems[optionalItemIndex].iPriority = -1;
                aItems[optionalItemIndex].iId = id;
                aItems[optionalItemIndex].iPlugin = plugin;
                }
            }
        }

    CleanupStack::PopAndDestroy(); // reader
    return;
    }
#endif // RD_SCALABLE_UI_V2

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknTouchPane::CAknTouchPane
// C++ default constructor.
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
CAknTouchPane::CAknTouchPane()
    : iAppUi( iAvkonAppUi ),
      iUid( TUid::Null() )
    {
    __ASSERT_DEBUG( iAppUi, User::Invariant() );
    SetMopParent( iAppUi );

    CApaApplication* application = iAppUi->Application();
    if ( application )
        {
        iUid = application->AppDllUid();
        }

    iFlags.Assign( ETouchPaneActive, iUid != KAknTouchPaneAutoLockAppUid );
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::ConstructL( RArray<TAknTouchPaneItem>& aItems )
    {
    CreateWindowL();
    Window().SetPointerGrab( ETrue );
    Window().SetNonFading( ETrue );
    Window().SetOrdinalPosition( 0, ECoeWinPriorityHigh );
    SetFocusing( EFalse );

    InitComponentArrayL();

    CCoeControl* component = NULL;
    for ( TInt ii = 0; ii < aItems.Count(); ++ii )
        {
        if ( aItems[ii].iId != ETouchPaneElementPlugin )
            {
            component = ConstructDefaultComponentL( aItems[ii].iId );
            }
        if ( component )
            {
            Components().AppendLC( component, KCoeNoControlId );
            CleanupStack::Pop( component );
            component = NULL;
            }
        }

    iBgContext = CAknsBasicBackgroundControlContext::NewL(
        KAknsIIDQsnBgScreen, TRect(), ETrue );

    iFrameContext = CAknsFrameBackgroundControlContext::NewL(
        KAknsIIDNone, TRect(), TRect(), ETrue );

    // Touch pane is set visible only in touch layouts.
    if ( AknLayoutUtils::PenEnabled() && Layout_Meta_Data::IsTouchPaneEnabled() )
        {
        SetWindowLayout();
        CCoeControl::MakeVisible( ETrue );
        }
    else
        {
        CCoeControl::MakeVisible( EFalse );
        }
        
    ActivateL();
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C CAknTouchPane* CAknTouchPane::NewL()
    {
    return CAknTouchPane::NewL( NULL );
    }
#else
EXPORT_C CAknTouchPane* CAknTouchPane::NewL()
    {
    return NULL;
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C CAknTouchPane* CAknTouchPane::NewL( TInt aResourceId )
    {
    RArray<TAknTouchPaneItem> items;
    CleanupClosePushL( items );

    const TUint flags = ReadDefaultTouchPaneContentL( items );

    if ( aResourceId )
        {
        ReadCustomTouchPaneContentL( aResourceId, items,
            !( flags & EAknDisabeTouchPaneCustomizations ) );
        }
    else if ( !( flags & EAknConstructTouchPaneByDefault ) )
        {
        items.Reset();
        }

    CAknTouchPane* self = NULL;
    if ( items.Count() )
        {
        self = new ( ELeave ) CAknTouchPane;
        CleanupStack::PushL( self );
        self->ConstructL( items );
        CleanupStack::Pop( self );
        }

    CleanupStack::Pop( &items );
    items.Close();
    AKNTASHOOK_ADDL( self, "CAknTouchPane" );
    return self;
    }
#else
EXPORT_C CAknTouchPane* CAknTouchPane::NewL( TInt )
    {
    return NULL;
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::~CAknTouchPane
// Destructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknTouchPane::~CAknTouchPane()
    {
    AKNTASHOOK_REMOVE();
#ifdef RD_SCALABLE_UI_V2
    DeregisterControlPositions();

    if ( iAppUi )
        {
        iAppUi->RemoveFromStack( this );
        iAppUi = NULL; // Not owned
        }

    // Although, these elements are owned by touch pane, they are deleted
    // through component array.
    iShellIcon = NULL;
    iSwapperIcon = NULL;
    iIdleViewIcon = NULL;
    iDiallerIcon = NULL;
    iRotateIcon = NULL;
    iHelpIcon = NULL;
    iInputMethodIcon = NULL;
    iToolbarIcon = NULL;
    iContactsIcon = NULL;

    iObserver = NULL; // Not owned
    delete iBgContext;
    delete iFrameContext;
#endif // RD_SCALABLE_UI_V2
    }

// -----------------------------------------------------------------------------
// CAknTouchPane::ReduceRect
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknTouchPane::ReduceRect( TRect& aBoundingRect ) const
    {
    if ( !IsVisible() )
        {
        return;
        }

    TRect rect( Position(), Size() );

    if ( rect.Intersects( aBoundingRect ) )
        {
        rect.Intersection( aBoundingRect );

        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            aBoundingRect.iTl.iX = rect.iBr.iX;
            }
        else 
            {
            aBoundingRect.iTl.iY = rect.iBr.iY;
            }
        }
    }
#else
EXPORT_C void CAknTouchPane::ReduceRect( TRect& ) const
    {
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::SetObserver
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknTouchPane::SetObserver( MAknTouchPaneObserver* aObserver )
    {
    iObserver = aObserver;
    }
#else
EXPORT_C void CAknTouchPane::SetObserver( MAknTouchPaneObserver* )
    {
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::SetVisibilityMode
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknTouchPane::SetVisibilityMode( TVisibilityMode aMode )
    {
#ifdef RD_SCALABLE_UI_V2
    if ( aMode == EAutomaticVisibilityChanges )
        {
        iFlags.Clear( ENoAutomaticVisibilityChanges );
        }
    else if ( aMode == EManualVisibilityChanges )
        {
        iFlags.Set( ENoAutomaticVisibilityChanges );
        }
#else
    (void)aMode;
#endif // RD_SCALABLE_UI_V2
    }

// -----------------------------------------------------------------------------
// CAknTouchPane::AllowInputMethodActivation
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknTouchPane::AllowInputMethodActivation( TBool aValue )
    {
    if ( iInputMethodIcon )
        {
        iFlags.Assign( EInputMethodIconActive, aValue );

        // Icon dimming is updated only when touch pane is active.
        if ( iFlags.IsSet( ETouchPaneActive ) )
            {
            iInputMethodIcon->SetDimmed( !aValue );
            Window().Invalidate( iInputMethodIcon->Rect() );
            }
        }
    }
#else
EXPORT_C void CAknTouchPane::AllowInputMethodActivation( TBool )
    {
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::SetInputMethodIconActivated
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknTouchPane::SetInputMethodIconActivated( TBool aActivated )
    {
    if ( iInputMethodIcon )
        {
        iInputMethodIcon->SetCurrentState( aActivated ? 1 : 0, 
            !iInputMethodIcon->IsDimmed() );
        }
    }
#else
EXPORT_C void CAknTouchPane::SetInputMethodIconActivated( TBool )
    {
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::RefreshL
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknTouchPane::RefreshL()
    {
#ifdef RD_SCALABLE_UI_V2
    if ( iHelpIcon && iUid != KAknTouchPaneHelpAppUid )
        {
        CArrayFix<TCoeHelpContext>* help = iAppUi->AppHelpContextL();
        TBool helpActive = help && help->Count();
        iFlags.Assign( EHelpIconActive, helpActive );
        delete help; help = NULL;
        }

    if ( iRotateIcon )
        {
        if ( iAppUi->Orientation() == CAknAppUiBase::EAppUiOrientationUnspecified )
            {
            iFlags.Set( ERotateIconActive );
            }
        else 
            {
            iFlags.Clear( ERotateIconActive );
            }
        }

    if ( iToolbarIcon )
        {
        CAknToolbar* toolbar = iAppUi->CurrentPopupToolbar();
        if ( toolbar && !toolbar->IsToolbarDisabled() )
            {
            iFlags.Set( EToolbarIconActive );
            TInt nextState = toolbar->IsShown() ? 1 : 0;
            if ( nextState != iToolbarIcon->StateIndex() )
                {
                iToolbarIcon->SetCurrentState( nextState, EFalse );
                Window().Invalidate( iToolbarIcon->Rect() );
                }
            }
        else
            {
            iFlags.Clear( EToolbarIconActive );
            }
        }

    // Updates the dimming of buttons.
    DoRefresh();
#endif // RD_SCALABLE_UI_V2
    }

// -----------------------------------------------------------------------------
// CAknTouchPane::SetFepPenSupportInterface
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknTouchPane::SetFepPenSupportInterface(
    MAknFepPenSupportInterface* aFepPenSupportInterface )
    {
    iFepPenSupportInterface = aFepPenSupportInterface;
    }
#else
EXPORT_C void CAknTouchPane::SetFepPenSupportInterface(
    MAknFepPenSupportInterface* )
    {
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::HandleStatusPaneSizeChange
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::HandleStatusPaneSizeChange( TInt aInitialResourceId,
    TInt aLastRequestedResourceId )
    {
    if ( !iFlags.IsSet( ENoAutomaticVisibilityChanges ) )
        {
        TInt resourceId = aLastRequestedResourceId ?
            aLastRequestedResourceId : aInitialResourceId;

        __ASSERT_DEBUG( iAvkonAppUi->StatusPane(), User::Invariant() );
        TBool visible = iAvkonAppUi->StatusPane()->IsVisible();
        if ( visible )
            {
            visible = AknStatuspaneUtils::TouchPaneCompatibleLayoutActive() &&
                !( AknStatuspaneUtils::StaconPaneActive() &&
                    resourceId == R_AVKON_STATUS_PANE_LAYOUT_EMPTY );
            }
        MakeVisible( visible );
        }
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::CountComponentControls
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknTouchPane::CountComponentControls() const
    {
#ifdef RD_SCALABLE_UI_V2
    return CCoeControl::CountComponentControls();
#else
    return NULL;
#endif // RD_SCALABLE_UI_V2
    }

// -----------------------------------------------------------------------------
// CAknTouchPane::ComponentControl
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C CCoeControl* CAknTouchPane::ComponentControl( TInt aIndex ) const
    {
    __ASSERT_DEBUG(aIndex >= 0, Panic(EEikPanicInvalidIndex));
    __ASSERT_DEBUG(aIndex < Components().Count(), Panic(EEikPanicInvalidIndex));

    return CCoeControl::ComponentControl( aIndex );
    }
#else
EXPORT_C CCoeControl* CAknTouchPane::ComponentControl( TInt ) const
    {
    return NULL;
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::Draw
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknTouchPane::Draw( CWindowGc& aGc, 
    const CCoeControl& /*aControl*/, const TRect& aRect ) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    
    if ( !cc )
        {
        iFrameContext->SetParentContext( iBgContext );
        }
    else
        {
        iFrameContext->SetParentContext( cc );
        }
    
    if ( !AknsDrawUtils::DrawBackground( skin, iFrameContext, this, aGc,
            aRect.iTl, aRect, KAknsDrawParamNoClearUnderImage ) )
        {
        aGc.SetBrushColor( KRgbRed );
        aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        aGc.SetClippingRect( aRect );
        aGc.DrawRect( Rect() );
        }
    }
#else
EXPORT_C void CAknTouchPane::Draw( CWindowGc&, const CCoeControl&,
    const TRect& ) const
    {
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::HandleControlEventL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknTouchPane::HandleControlEventL( CCoeControl* aControl,
    TCoeEvent aEventType )
    {
    if ( aControl && ( aEventType == EEventStateChanged ) )
        {
        if ( aControl == iShellIcon )
            {
            if ( iUid != KAknApplicationShellViewId.iAppUid )
                {                
                ActivateApplicationShellL();
                }
            else
                {
                ActivateIdleViewL();
                }
            }
        else if ( aControl == iSwapperIcon )
            {
            ActivateFastSwapL();
            }
        else if ( aControl == iIdleViewIcon )
            {
            ActivateIdleViewL();
            }
        else if ( aControl == iDiallerIcon )
            {
            ActivateDiallerL( iUid != KAknTouchPaneDiallerAppUid );
            }
        else if ( aControl == iRotateIcon )
            {
            RotateScreenL();
            }
        else if ( aControl == iHelpIcon )
            {
            ActivateHelpL( iUid != KAknTouchPaneHelpAppUid );
            }
        else if ( aControl == iInputMethodIcon )
            {
            ActivateStylusInputL( iInputMethodIcon->StateIndex() == 1 );
            }
        else if ( aControl == iToolbarIcon )
            {
            ActivateToolbarL( iToolbarIcon->StateIndex() == 1 );
            }
        else if ( aControl == iContactsIcon )
            {
            ActivateContactsL( iUid != KAknTouchPaneContactsAppUid );
            }

        // Update the toolbar button state, if current toolbar notifies of a
        // change in its state
        else if ( aControl == iAppUi->CurrentPopupToolbar() && 
                  iToolbarIcon )
            {
            CAknToolbar* toolbar = iAppUi->CurrentPopupToolbar();
            iToolbarIcon->SetDimmed( EFalse );
            iFlags.Set( EToolbarIconActive );
            iToolbarIcon->SetCurrentState( toolbar->IsShown() ? 1 : 0, ETrue );
            }
        }

    else if ( aControl && ( aEventType == CAknButton::ELongPressEvent ) )
        {
        if ( aControl == iShellIcon || aControl == iSwapperIcon )
            {
            ActivateFastSwapL();
            }
        }

    else if ( aControl && ( aEventType == KDisableToolbar ) )
        {
        CAknToolbar* toolbar = iAppUi->CurrentPopupToolbar(); 
        if ( aControl == toolbar && iToolbarIcon )
            {
            iToolbarIcon->SetDimmed( ETrue );
            iFlags.Clear( EToolbarIconActive );
            }
        Window().Invalidate( iToolbarIcon->Rect() );
        }
    else if ( aControl && ( aEventType == KEnableToolbar ) )
        {
        CAknToolbar* toolbar = iAppUi->CurrentPopupToolbar(); 
        if ( aControl == toolbar && iToolbarIcon )
            {
            iToolbarIcon->SetDimmed( EFalse );
            iFlags.Set( EToolbarIconActive );
            }
        Window().Invalidate( iToolbarIcon->Rect() );
        }
    }
#else
EXPORT_C void CAknTouchPane::HandleControlEventL( CCoeControl*, TCoeEvent )
    {
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::HandleResourceChange
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknTouchPane::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );

    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        if ( AknLayoutUtils::PenEnabled() && Layout_Meta_Data::IsTouchPaneEnabled() )
            {
            SetWindowLayout();
            }
        else
            {
            CCoeControl::MakeVisible( EFalse );
            }
        }
    }
#else
EXPORT_C void CAknTouchPane::HandleResourceChange( TInt )
    {
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::MakeVisible
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknTouchPane::MakeVisible( TBool aVisible )
    {
    if ( ( !aVisible || AknLayoutUtils::PenEnabled() ) && 
        ( aVisible != IsVisible() ) && Layout_Meta_Data::IsTouchPaneEnabled() )
        {
        CCoeControl::MakeVisible( aVisible );
        ReportSizeChange();
        }
    }
#else
EXPORT_C void CAknTouchPane::MakeVisible( TBool )
    {
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::OfferKeyEventL
// -----------------------------------------------------------------------------
//
EXPORT_C TKeyResponse CAknTouchPane::OfferKeyEventL(
    const TKeyEvent& /*aKeyEvent*/, TEventCode /*aType*/ )
    {
    return EKeyWasNotConsumed;
    }

// -----------------------------------------------------------------------------
// Handles window server events.
// -----------------------------------------------------------------------------
//
void CAknTouchPane::HandleWsEventL( const TWsEvent& aEvent,
    CCoeControl* /*aDestination*/ )
    {
#ifdef RD_SCALABLE_UI_V2
    TInt eventType = aEvent.Type();
    if ( eventType == EEventFocusLost )
        {
        iFlags.Clear( EHasForeground );
        DoRefresh();
        }
    else if ( eventType == EEventFocusGained )
        {
        iFlags.Set( EHasForeground );
        DoRefresh();
        }
#else
    (void) aEvent;
#endif // RD_SCALABLE_UI_V2
    }

// -----------------------------------------------------------------------------
// CAknTouchPane::HandlePointerEventL
// When application is displaying menu or dialog, this method ignores pointer
// events on other than application shell, application swapper, and idle view
// icons.
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknTouchPane::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    TPoint position = aPointerEvent.iPosition;
    TBool isDisplayingMenu = EFalse;
    CEikMenuBar* menuBar = NULL;

    TVwsViewId viewId;
    TInt err = iAppUi->GetActiveViewId( viewId );
    if ( err == KErrNone && viewId.iAppUid != viewId.iViewUid )
        {
        // Application has active view
        CAknView* view = iAvkonViewAppUi->View( viewId.iViewUid );
        if ( view )
            {
            //menuBar = view->MenuBar();
            menuBar = view->CAknView::MenuBar();
            }
        }
    else
        {
        menuBar = iEikonEnv->AppUiFactory()->MenuBar();
        }

    if ( menuBar )
        {
        isDisplayingMenu = menuBar->IsDisplayed();
        }

    // Close menu on button up event
    if ( isDisplayingMenu && Rect().Contains( position ) && 
         aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        menuBar->StopDisplayingMenuBar(); //lint !e613
        }

    if ( !isDisplayingMenu ||
         ( iShellIcon && iShellIcon->Rect().Contains( position ) ) ||
         ( iSwapperIcon && iSwapperIcon->Rect().Contains( position ) ) ||
         ( iIdleViewIcon && iIdleViewIcon->Rect().Contains( position ) ) )
        {
        CCoeControl::HandlePointerEventL( aPointerEvent );
        }
    }
#else
EXPORT_C void CAknTouchPane::HandlePointerEventL( const TPointerEvent& )
    {
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::PositionChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknTouchPane::PositionChanged()
    {
#ifdef RD_SCALABLE_UI_V2
    RegisterControlPositions();
#endif // RD_SCALABLE_UI_V2
    }

// -----------------------------------------------------------------------------
// CAknTouchPane::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknTouchPane::SizeChanged()
    {
#ifdef RD_SCALABLE_UI_V2
    // Update frame and background control contexts
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        iFrameContext->SetFrame( KAknsIIDQgnGrafBgTouchVertical );
        }
    else
        {
        iFrameContext->SetFrame( KAknsIIDQgnGrafBgTouchHorizontal );
        }
    iFrameContext->SetFrameRects( Rect(), TRect() );
    iFrameContext->SetParentPos( Position() );

    iBgContext->SetParentPos( iAvkonAppUi->ApplicationRect().iTl );
    iBgContext->SetRect( iAvkonAppUi->ApplicationRect() );

    TInt gridVariety = Layout_Meta_Data::IsLandscapeOrientation() ? 1 : 0;

    TInt cellVariety = Layout_Meta_Data::IsLandscapeOrientation() ? 1 : 0;
    if ( Components().Count() < 4 )
        {
        if ( Components().Count() == 3 )
            {
            cellVariety += 2;
            }
        else
            {
            cellVariety += 4;
            }
        }

    TRect gridRect = RectFromLayout( Rect(),
        AknLayoutScalable_Avkon::grid_touch_3_pane( gridVariety ) );

    TAknLayoutScalableParameterLimits limits =
        AknLayoutScalable_Avkon::cell_touch_3_pane_ParamLimits( cellVariety );

    const TInt gridSize = ( ( limits.LastRow() - limits.FirstRow() ) + 1 ) *
        ( ( limits.LastColumn() - limits.FirstColumn() ) + 1 );

    const TInt maxItemCount = Min( gridSize, Components().Count() );

    TInt row = 0;
    TInt col = 0;
    TInt index = 0;
    TRect cellRect;
    for ( row = limits.FirstRow(); row <= limits.LastRow(); ++row )
        {
        for ( col = limits.FirstColumn(); col <= limits.LastColumn(); ++col )
            {
            if ( index < maxItemCount )
                {
                cellRect = RectFromLayout( gridRect, AknLayoutScalable_Avkon::
                    cell_touch_3_pane( cellVariety, col, row ) );
                Components().At( index ).iControl->SetRect( cellRect );
                ++index;
                }
            }
        }

    // Set empty rect for controls that should not be visible (no layout data)
    TInt count = CountComponentControls();
    for ( TInt ii = maxItemCount; ii < count; ++ii )
        {
        Components().At( ii ).iControl->SetRect( TRect() );
        }

    // Set the tooltip positions. Code assumes that touch pane is always
    // horizontal in portrait mode and vertical in landscape mode.
    CAknButton::TTooltipPosition tooltipPosition;
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        if ( Position().iX > iAppUi->ClientRect().Center().iX )
            {
            tooltipPosition = CAknButton::EPositionLeft;
            }
        else
            {
            tooltipPosition = CAknButton::EPositionRight;
            }
        }
    else
        {
        if ( Position().iY > iAppUi->ClientRect().Center().iY )
            {
            tooltipPosition = CAknButton::EPositionTop;
            }
        else
            {
            tooltipPosition = CAknButton::EPositionBottom;
            }
        }

    for ( TInt ii = 0; ii < maxItemCount; ++ii )
        {
        // This assumes that every control in touch pane is button
        CAknButton* button =  
            static_cast<CAknButton*>( Components().At( ii ).iControl );
        button->SetTooltipPosition( tooltipPosition );
        
        // recalculate icon size
        TRect sizeRect = RectFromLayout( cellRect, 
            AknLayoutScalable_Avkon::cell_touch_3_pane_g2() );
        button->SetIconSize( sizeRect.Size() );
        
        // recalculate margins
        TRect graphicsRect = RectFromLayout( cellRect, 
            AknLayoutScalable_Avkon::cell_touch_3_pane_g1() );
        graphicsRect.BoundingRect( sizeRect );
        
        TMargins8 margins;
        margins.iTop = sizeRect.iTl.iY - graphicsRect.iTl.iY;
        margins.iBottom = graphicsRect.iBr.iY - sizeRect.iBr.iY;
        margins.iLeft = sizeRect.iTl.iX - graphicsRect.iTl.iX;
        margins.iRight = graphicsRect.iBr.iX - sizeRect.iBr.iX;
        
        button->SetMargins( margins );
        }

    RegisterControlPositions();
    ReportSizeChange();
#endif // RD_SCALABLE_UI_V2
    }

// -----------------------------------------------------------------------------
// CAknTouchPane::ActivateApplicationShellL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::ActivateApplicationShellL()
    {
    TVwsViewId shellView = KAknApplicationShellViewId;
    iAppUi->CreateActivateViewEventL( shellView, TUid::Uid(1), KNullDesC8() );
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::ActivateFastSwapL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::ActivateFastSwapL() const
    {
    RAknUiServer* uiServer = CAknSgcClient::AknSrv();
    uiServer->MakeTaskListVisible( ETrue );
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::ActivateIdleViewL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::ActivateIdleViewL() const
    {
    TVwsViewId idleView;
    RAknUiServer* uiServer = CAknSgcClient::AknSrv();
    TInt error = uiServer->GetPhoneIdleViewId( idleView );
    if ( !error && iUid != idleView.iAppUid )
        {
        iAppUi->CreateActivateViewEventL( idleView, KNullUid, KNullDesC8() );
        }
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::RotateScreenL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::RotateScreenL() const
    {
    RAknUiServer* uiServer = CAknSgcClient::AknSrv();
    User::LeaveIfError( uiServer->RotateScreen() );
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::ActivateStylusInputL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::ActivateStylusInputL( TBool aActivate ) const
    {
    if( iFepPenSupportInterface != NULL)
        {
        if ( aActivate )
            {
            iFepPenSupportInterface->ActivatePenInputL();
            }
        else
            {
            iFepPenSupportInterface->DeactivatePenInputL();
            }
        }
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::ActivateToolbarL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::ActivateToolbarL( TBool aActivate ) const
    {
    CAknToolbar* toolbar = iAppUi->CurrentPopupToolbar();
    if ( toolbar )
        {
        // Toolbar transition effects integration.
        // This code just does the registration part, and sets the demarcation
        // rect, as that comes from the icon in the touchpane, which is only
        // available here.  For toolbar animations where the touchpane aren't
        // involved, registering etc. is done in AknToolbar.cpp.
        TRect iconRect( iToolbarIcon->Position(),
                        iToolbarIcon->Position() + iToolbarIcon->Size() );

        if ( CTouchToolbarData::SetData( toolbar, iconRect, ETrue ) ==
             KErrNone )
            {
            GfxTransEffect::Register( toolbar, KGfxTouchToolbarControlUid,
                                      EFalse );
            GfxTransEffect::Enable();
            CTouchToolbarData* ttb = CTouchToolbarData::GetData( toolbar );
            if( ttb )
                {
                ttb->SetBetweenRegisterAndBegin( ETrue );    
                }
            
            }
        toolbar->SetToolbarVisibility( aActivate, EFalse );
        }
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::ActivateHelpL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::ActivateHelpL( TBool aActivate )
    {
    if ( aActivate )
        {
        CArrayFix<TCoeHelpContext>* help = iAppUi->AppHelpContextL();
        if ( help )
            {
            CleanupStack::PushL( help );
            HlpLauncher::LaunchHelpApplicationL( iEikonEnv->WsSession(), help );
            CleanupStack::Pop( help );
            }
        }
    else
        {
        iAppUi->HandleCommandL( EEikCmdExit );
        }
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::ActivateDiallerL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::ActivateDiallerL( TBool aActivate )
    {
    if ( aActivate )
        {
        TVwsViewId diallerView( KAknTouchPaneDiallerAppUid,
            KAknTouchPaneDiallerViewUid );
        iAppUi->CreateActivateViewEventL( diallerView,
            KTouchPaneDiallerVievCommand, KNullDesC8() );
        }
    else
        {
        iAppUi->HandleCommandL( EAknCmdExit );
        }
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::ActivateContactsL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::ActivateContactsL( TBool aActivate )
    {
    if ( aActivate )
        {
        TVwsViewId contactsView( KAknTouchPaneContactsAppUid,
            KAknTouchPaneContactsViewUid );
        iAppUi->CreateActivateViewEventL( contactsView, TUid::Null(),
            KNullDesC8() );
        }
    else
        {
        iAppUi->HandleCommandL( EAknCmdExit );
        }
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::ConstructDefaultComponentL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
CAknButton* CAknTouchPane::ConstructDefaultComponentL( TInt aId )
    {
    CAknButton* element = NULL;
    HBufC* tooltip = NULL;
    HBufC* helpText = NULL;

    switch ( aId )
        {
        case ETouchPaneElementNone:
            {
            // Creates an empty button
            element = CAknButton::NewLC();
            element->AddStateL( NULL, NULL, NULL, NULL, KNullDesC(),
                                KNullDesC(), NULL );
            element->SetDimmed( ETrue );
            break;
            }
        case ETouchPaneElementAppsGrid:
            {
            if ( !iShellIcon )
                {
                tooltip = StringLoader::LoadLC( R_QTN_GEN_APP_SHELL_TOOLTIP );
                element = CAknButton::NewLC(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_appsgrid,
	                EMbmAvkonQgn_indi_tp_appsgrid_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, KAknButtonReportOnLongPress, NULL,
                    KAknsIIDQgnIndiTpAppsgrid );
                iShellIcon = element;
                CleanupStack::Pop( element );
                CleanupStack::Pop( tooltip );
                CleanupStack::PushL( element ); // will not leave
                iFlags.Set( EShellIconActive );
                }
            break;
            }
        case ETouchPaneElementAppSwapper:
            {
            if ( !iSwapperIcon )
                {
                tooltip = StringLoader::LoadLC( R_QTN_GEN_FAST_SWAPPER_TOOLTIP );
                element = CAknButton::NewLC(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_appswapper,
                    EMbmAvkonQgn_indi_tp_appswapper_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, KAknButtonReportOnLongPress, NULL,
                    KAknsIIDQgnIndiTpAppswapper );
                iSwapperIcon = element;
                CleanupStack::Pop( element );
                CleanupStack::Pop( tooltip );
                CleanupStack::PushL( element ); // will not leave
                iFlags.Set( ESwapperIconActive );
                }
            break;
            }
        case ETouchPaneElementIdle:
            {
            if ( !iIdleViewIcon )
                {
                tooltip = StringLoader::LoadLC( R_QTN_GEN_IDLE_VIEW_TOOLTIP );
                element = CAknButton::NewLC(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_idle,
                    EMbmAvkonQgn_indi_tp_idle_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, NULL, NULL,
                    KAknsIIDQgnIndiTpIdle );
                iIdleViewIcon = element;
                CleanupStack::Pop( element );
                CleanupStack::Pop( tooltip );
                CleanupStack::PushL( element ); // will not leave
                iFlags.Set( EIdleViewIconActive );
                }
            break;
            }
        case ETouchPaneElementInput:
            {
            if ( !iInputMethodIcon )
                {
                tooltip = StringLoader::LoadLC( 
                    R_QTN_GEN_INPUT_ACTIVATION_TOOLTIP );
                helpText = StringLoader::LoadLC( 
                    R_QTN_GEN_INFO_POP_UP_DIMMED_ITEM, *tooltip );
                element = CAknButton::NewLC(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_input,
                    EMbmAvkonQgn_indi_tp_input_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, NULL, NULL,
                    KAknsIIDQgnIndiTpInput );
                element->AddStateL(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_input,
                    EMbmAvkonQgn_indi_tp_input_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, KAknButtonStateHasLatchedFrame,
                    KAknsIIDQgnIndiTpInput, KAknsIIDNone,
                    KAknsIIDNone, KAknsIIDNone );
                element->SetDimmed( ETrue );
                element->SetDimmedHelpTextL( *helpText );
                iInputMethodIcon = element;
                CleanupStack::Pop( element );
                CleanupStack::Pop( helpText );
                CleanupStack::Pop( tooltip );
                CleanupStack::PushL( element ); // will not leave
                iFlags.Clear( EInputMethodIconActive );
                }
            break;
            }
        case ETouchPaneElementRotateScreen:
            {
            if ( !iRotateIcon )
                {
                tooltip = StringLoader::LoadLC( 
                    R_QTN_GEN_ROTATE_ICON_TOOLTIP );
                element = CAknButton::NewLC(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_rotate_screen,
                    EMbmAvkonQgn_indi_tp_rotate_screen_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, NULL, NULL,
                    KAknsIIDQgnIndiTpRotateScreen );
                iRotateIcon = element;
                CleanupStack::Pop( element );
                CleanupStack::Pop( tooltip );
                CleanupStack::PushL( element ); // will not leave
                iFlags.Set( ERotateIconActive );
                }
            break;
            }
        case ETouchPaneElementToolbar:
            {
            if ( !iToolbarIcon )
                {
                tooltip = StringLoader::LoadLC( 
                    R_QTN_GEN_TOOLBAR_ICON_TOOLTIP );
                helpText = StringLoader::LoadLC( 
                    R_QTN_GEN_INFO_POP_UP_DIMMED_ITEM, *tooltip );
                element = CAknButton::NewLC(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_toolbar,
                    EMbmAvkonQgn_indi_tp_toolbar_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, NULL, NULL,
                    KAknsIIDQgnIndiTpToolbar );
                element->AddStateL(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_toolbar,
                    EMbmAvkonQgn_indi_tp_toolbar_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, KAknButtonStateHasLatchedFrame,
                    KAknsIIDQgnIndiTpToolbar, KAknsIIDNone,
                    KAknsIIDNone, KAknsIIDNone );
                element->SetDimmed( ETrue );
                element->SetDimmedHelpTextL( *helpText );
                iToolbarIcon = element;
                CleanupStack::Pop( element );
                CleanupStack::Pop( helpText );
                CleanupStack::Pop( tooltip );
                CleanupStack::PushL( element ); // will not leave
                iFlags.Clear( EToolbarIconActive );
                }
            break;
            }
        case ETouchPaneElementHelp:
            {
            if ( !iHelpIcon )
                {
                TInt stateFlags = ( iUid == KAknTouchPaneHelpAppUid ) ?
                    KAknButtonStateHasLatchedFrame : NULL;
                tooltip = StringLoader::LoadLC( R_QTN_GEN_HELP_TOOLTIP );
                helpText = StringLoader::LoadLC( 
                    R_QTN_GEN_INFO_POP_UP_DIMMED_ITEM, *tooltip );
                element = CAknButton::NewLC(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_help,
                    EMbmAvkonQgn_indi_tp_help_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, NULL, stateFlags,
                    KAknsIIDQgnIndiTpHelp );
                element->SetDimmedHelpTextL( *helpText );
                iHelpIcon = element;
                CleanupStack::Pop( element );
                CleanupStack::Pop( helpText );
                CleanupStack::Pop( tooltip );
                CleanupStack::PushL( element ); // will not leave
                iFlags.Set( EHelpIconActive );
                }
            break;
            }
        case ETouchPaneElementDialler:
            {
            if ( !iDiallerIcon )
                {
                tooltip = StringLoader::LoadLC( 
                    R_QTN_GEN_DIALLER_ICON_TOOLTIP );
                element = CAknButton::NewLC( 
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_dialler,
                    EMbmAvkonQgn_indi_tp_dialler_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, NULL, NULL,
                    KAknsIIDQgnIndiTpDialler );
                element->AddStateL(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_dialler,
                    EMbmAvkonQgn_indi_tp_dialler_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, KAknButtonStateHasLatchedFrame,
                    KAknsIIDQgnIndiTpDialler, KAknsIIDNone,
                    KAknsIIDNone, KAknsIIDNone );
                iDiallerIcon = element;
                CleanupStack::Pop( element );
                CleanupStack::Pop( tooltip );
                CleanupStack::PushL( element ); // will not leave
                iFlags.Set( EDiallerIconActive );
                }
            break;
            }
        case ETouchPaneElementContacts:
            {
            if ( !iContactsIcon )
                {
                _LIT( KContactsTooltip, "Contacts" );
                tooltip = KContactsTooltip().AllocLC();
                element = CAknButton::NewLC(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_contacts,
                    EMbmAvkonQgn_indi_tp_contacts_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, NULL, NULL,
                    KAknsIIDQgnIndiTpContacts );
                iContactsIcon = element;
                element->AddStateL(
                    AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_indi_tp_contacts,
                    EMbmAvkonQgn_indi_tp_contacts_mask,
                    -1, -1, -1, -1, -1, -1,
                    KNullDesC, *tooltip, KAknButtonStateHasLatchedFrame,
                    KAknsIIDQgnIndiTpContacts, KAknsIIDNone,
                    KAknsIIDNone, KAknsIIDNone );
                CleanupStack::Pop( element );
                CleanupStack::Pop( tooltip );
                CleanupStack::PushL( element ); // will not leave
                iFlags.Set( EContactsIconActive );
                }
            break;
            }
        default:
            {
            User::Leave( KErrNotSupported );
            }
        }
 
    delete tooltip; tooltip = NULL;
    delete helpText; helpText = NULL;
 
    if ( element )
        {
        // Set background for the element.
        if ( aId != ETouchPaneElementNone )
            {
            element->SetBackgroundIds( KAknsIIDQsnFrButtonTpNormal,
                KAknsIIDQsnFrButtonTpPressed, KAknsIIDQsnFrButtonTpInactive,
                KAknsIIDQsnFrButtonTpPressed, KAknsIIDQsnFrButtonTpInactive );
            }
        else
            {
            element->SetBackgroundIds( KAknsIIDNone, KAknsIIDNone,
                KAknsIIDNone, KAknsIIDNone, KAknsIIDNone );
            }

        SetDefaultPropertiesL( element );
        CleanupStack::Pop( element );
        }
    return element;
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::ReportSizeChange
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::ReportSizeChange() const
    {
    if ( iObserver )
        {
        iObserver->HandleTouchPaneSizeChange();
        }
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::SetDefaultProperties
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::SetDefaultPropertiesL( CCoeControl* aControl )
    {
    aControl->SetContainerWindowL( *this );
    aControl->SetObserver( this );
    aControl->SetFocusing( EFalse );
    aControl->SetBackground( this );
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::SetWindowLayout
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::SetWindowLayout()
    {
    const TInt variety = Layout_Meta_Data::IsLandscapeOrientation() ? 1 : 0;
    TRect touchPaneRect = RectFromLayout( iAppUi->ApplicationRect(),
        AknLayoutScalable_Avkon::touch_pane( variety ) );
    SetRect( touchPaneRect );
    Window().Invalidate();
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::RegisterControlPositions
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::RegisterControlPositions() const
    {
    TInt count = CountComponentControls();
    CCoeControl* control = NULL;
    AknsUtils::RegisterControlPosition( this, Position() );
    for ( TInt ii = 0; ii < count; ++ii )
        {
        control = ComponentControl( ii );
        AknsUtils::RegisterControlPosition( control,
            Position() + control->Position() );
        }
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::DeregisterControlPositions
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::DeregisterControlPositions() const
    {
    TInt count = CountComponentControls();
    CCoeControl* control = NULL;
    AknsUtils::DeregisterControlPosition( this );
    for ( TInt ii = 0; ii < count; ++ii )
        {
        control = ComponentControl( ii );
        AknsUtils::DeregisterControlPosition( control );
        }
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::DoRefresh
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::DoRefresh()
    {
    if ( iDiallerIcon )
        {
        // Set dialler icon pressed only in dialler application.
        TInt state = ( iUid == KAknTouchPaneDiallerAppUid ? 1 : 0 );
        if ( state != iDiallerIcon->StateIndex() )
            {
            iDiallerIcon->SetCurrentState( state, EFalse );
            Window().Invalidate( iDiallerIcon->Rect() );
            }
        }

    if ( iContactsIcon )
        {
        // Set Contacts icon pressed only in contacts application.
        TInt state = ( iUid == KAknTouchPaneContactsAppUid ? 1 : 0 );
        if ( state != iContactsIcon->StateIndex() )
            {
            iContactsIcon->SetCurrentState( state, EFalse );
            Window().Invalidate( iContactsIcon->Rect() );
            }
        }

    // Update icon dimming depending on whether the touch pane is active.
    const TBool active = iFlags.IsSet( ETouchPaneActive ) &&
        iFlags.IsSet( EHasForeground );

    if ( iShellIcon && iShellIcon->IsDimmed() == ( active &&
         iFlags.IsSet( EShellIconActive ) ) )
        {
        iShellIcon->SetDimmed( !iShellIcon->IsDimmed() );
        Window().Invalidate( iShellIcon->Rect() );
        }

    if ( iSwapperIcon && iSwapperIcon->IsDimmed() == ( active &&
         iFlags.IsSet( ESwapperIconActive ) ) )
        {
        iSwapperIcon->SetDimmed( !iSwapperIcon->IsDimmed() );
        Window().Invalidate( iSwapperIcon->Rect() );
        }

    if ( iIdleViewIcon && iIdleViewIcon->IsDimmed() == ( active &&
         iFlags.IsSet( EIdleViewIconActive ) ) )
        {
        iIdleViewIcon->SetDimmed( !iIdleViewIcon->IsDimmed() );
        Window().Invalidate( iIdleViewIcon->Rect() );
        }

    if ( iDiallerIcon && iDiallerIcon->IsDimmed() == ( active &&
         iFlags.IsSet( EDiallerIconActive ) ) )
        {
        iDiallerIcon->SetDimmed( !iDiallerIcon->IsDimmed() );
        Window().Invalidate( iDiallerIcon->Rect() );
        }

    if ( iRotateIcon && iRotateIcon->IsDimmed() == ( active &&
         iFlags.IsSet( ERotateIconActive ) ) )
        {
        iRotateIcon->SetDimmed( !iRotateIcon->IsDimmed() );
        Window().Invalidate( iRotateIcon->Rect() );
        }

    if ( iHelpIcon && iHelpIcon->IsDimmed() == ( active &&
         iFlags.IsSet( EHelpIconActive ) ) )
        {
        iHelpIcon->SetDimmed( !iHelpIcon->IsDimmed() );
        Window().Invalidate( iHelpIcon->Rect() );
        }

    if ( iInputMethodIcon && iInputMethodIcon->IsDimmed() == ( active &&
         iFlags.IsSet( EInputMethodIconActive ) ) )
        {
        iInputMethodIcon->SetDimmed( !iInputMethodIcon->IsDimmed() );
        Window().Invalidate( iInputMethodIcon->Rect() );
        }

    if ( iToolbarIcon && iToolbarIcon->IsDimmed() == ( active &&
         iFlags.IsSet( EToolbarIconActive ) ) )
        {
        iToolbarIcon->SetDimmed( !iToolbarIcon->IsDimmed() );
        Window().Invalidate( iToolbarIcon->Rect() );
        }

    if ( iContactsIcon && iContactsIcon->IsDimmed() == ( active &&
         iFlags.IsSet( EContactsIconActive ) ) )
        {
        iContactsIcon->SetDimmed( !iContactsIcon->IsDimmed() );
        Window().Invalidate( iContactsIcon->Rect() );
        }
    }
#endif // RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknTouchPane::Draw
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
void CAknTouchPane::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    Draw( gc, *this, aRect );
    }
#else
void CAknTouchPane::Draw( const TRect& ) const
    {
    }
#endif // RD_SCALABLE_UI_V2

//  End of File  
