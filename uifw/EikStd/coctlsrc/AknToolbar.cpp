/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Popup toolbar component
*
*/


// INCLUDE FILES
#include <akntoolbar.h>
#include <akntoolbarobserver.h> 
#include <aknbutton.h>  // CAknButton
#include <akntouchpane.h> // CAknTouchPane
#include "akntoolbaritem.h" 
#include <akntoolbarextension.h>

#include <barsread.h>   // TResourceReader
#include <eikfctry.h>   // SEikControlInfo
#include <eikappui.h>   // CEikAppUi
#include <eikpanic.h>
#include <avkon.hrh>
#include <eikon.hrh>    // toolbar flags
#include <aknappui.h>  
#include <systemwarninglevels.hrh> // KRAMGOODTHRESHOLD
#include <eikbtgpc.h>   // CEikButtonGroupContainer
#include <avkon.rsg>

#include <aknViewAppUi.h>
#include <aknview.h>
#include <AknsDrawUtils.h>
#include <AknsControlContext.h>
#include <aknlayout.cdl.h>
#include <skinlayout.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknUtils.h>
#include <AknsFrameBackgroundControlContext.h>
#include <layoutmetadata.cdl.h>
#include <AknPriv.hrh>
#include <hal.h>
#include <AknsMaskedLayerBackgroundControlContext.h>
#include <AknSgcc.h>
#include <AknStatuspaneUtils.h>
#include <AknsConstants.h>
#include <centralrepository.h>
#include <AknSkinsInternalCRKeys.h>
#include <eikdialg.h>
#include <eikapp.h>
#include <AknDef.h>

#include <AknTasHook.h> // for testability hooks
#include <touchfeedback.h>
#include <eikcolib.h>

#include <gfxtranseffect/gfxtranseffect.h> 
#include <akntranseffect.h>
#include <akntransitionutils.h>
#include "touchtoolbardata.h"

// CONSTANTS
const TInt KLineArrayGranularity = 5;

const TInt KFocusedNone = -1;
const TInt KSelectedNone = -2;

const TInt KToolbarButtonBeforeTimeout = 300; 
const TInt KToolbarButtonInViewTimeout = 5000; 

const TInt KFixedtoolbarButtons = 3; // Number of buttons fixed toolbar has to have
//const TUint32 KToolbarColorKey = 0x00000000; // ARGB

const TUint32 KToolbarBgColor = 0x00000000;
const TInt KToolBarBgAlpha = 0x7F;

#ifdef RD_SCALABLE_UI_V2
const TInt KDisableToolbar = 0xfff1; 
const TInt KEnableToolbar = 0xfff2; 
#endif

// toolbar's internal flags
enum TInternalFlags
    {
    EInIdle,                // toolbar is shown in idle view
    ESlidingSupported,      // whether toolbar can be show up with sliding effect if it is needed
    EWithSliding,           // defines whether toolbar should be shown with sliding effect
    ENoItemsVisible,        // used to check if no items are visible, this is needed to know if CBA needs to be created again
    EShown,                 // whether toolbar is shown right now( IsVisible() is not safe enough because can be changed from outside with MakeVisible()
    EShowingAgain,          // used to check if toolbar is shown again when allready shown, this is needed for not sliding when toolbar is allready shown
    ESliding,               // set if toolbar is currently sliding
    EFixedShown,            // tells to fixed toolbar if it needs to be shown when the layout is good
    ECalledFromFW,          // indicates to SetToolbarVisibility that it was called by the framework
    EAppOverrideVisibility, // indicates whether fixed toolbar visibility has been overriden by the application
    EDisabled,              // whether toolbar is disabled or not
    EDrawBackground,        // whether only toolbar background should be drawn
    EItemsHidden,            // whether application has called HideItemsAndDrawOnlyBackground
    EItemsHiddenWithPriority,    // whether application has called HideItemsAndDrawOnlyBackground with priority
    ESwitchForItemsHidden,   // switch for clearing EItemsHidden when the toolbar is to be shown
    EDefaultToolbar          //used for hideitemsanddrawonlybackground
    };

// Control stack priority for toolbar to enable view deactivation
const TInt KCoeStackToolbarPriority = ECoeStackPriorityCba; 


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknToolbar::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknToolbar* CAknToolbar::NewL( const TInt aResourceId )
    {
    CAknToolbar* self = NewLC( aResourceId );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::NewLC
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknToolbar* CAknToolbar::NewLC( const TInt aResourceId )
    {
    CAknToolbar* self = new ( ELeave ) CAknToolbar();
    CleanupStack::PushL( self );
    self->ConstructL();
    self->ConstructFromResourceL( aResourceId );
    AKNTASHOOK_ADDL( self, "CAknToolbar" );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::CAknToolbar
// C++ default constructor.
// -----------------------------------------------------------------------------
//
CAknToolbar::CAknToolbar()
    : iItems( KLineArrayGranularity ),
      iVisibleItems( KLineArrayGranularity ),
      iFocusedItem( KFocusedNone ),
      iSelectedItem( KSelectedNone ),
      iInitialFocusedItem ( KFocusedNone ),
      iLastFocusedItem(  KFocusedNone ),
      iOrientation( EAknOrientationHorizontal ), 
      iSoftkeyResource( R_AVKON_SOFTKEYS_SELECT_CLOSE__SELECT ),
      iPreviousItem( KSelectedNone ),
      iDrawingPriority( ECoeWinPriorityLow )
    {
    CEikApplication* application = iAvkonAppUi->Application();

    if ( application )
        {
        TVwsViewId idleView;
        TInt err = AknDef::GetPhoneIdleViewId( idleView );
        
        if ( application->AppDllUid() == idleView.iAppUid )
            {
            iInternalFlags.Set( EInIdle );
            }
        }
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
EXPORT_C CAknToolbar::~CAknToolbar()
    {
    AKNTASHOOK_REMOVE();
    SetFocus( EFalse );
    CEikonEnv::Static()->EikAppUi()->RemoveFromStack( this );

    iVisibleItems.Reset();
    iItems.ResetAndDestroy();
            
    delete iToolbarCba;    
    delete iFrameContext;
    delete iBgContext; 
    if ( iIdle && iIdle->IsActive() )
        {
        iIdle->Cancel(); 
        }
    delete iIdle; 
        
    iToolbarObserver = NULL; // not owned

    GfxTransEffect::Deregister( this );

    CTouchToolbarData* d = CTouchToolbarData::GetData( this );
    if ( d )
        {
        CAknTransitionUtils::RemoveObserver( d, 
            CAknTransitionUtils::EEventControlTransitionFinished );
        CAknTransitionUtils::RemoveData( reinterpret_cast<TInt>( this ) );
        delete d;
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CAknToolbar::ConstructL()
    {            
    // create control's window
    CreateWindowL();
    SetFocusing( EFalse ); 

    DrawableWindow()->SetPointerGrab( ETrue );
    DrawableWindow()->SetShadowDisabled( ETrue );
    DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityNeverAtFront );

    CEikonEnv::Static()->EikAppUi()->AddToStackL( this, KCoeStackToolbarPriority,
        ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys );

    SetComponentsToInheritVisibility( ETrue );
    SetShown( EFalse );
    iBgIID = KAknsIIDNone;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::CountComponentControls
// Gets the number of controls contained in a compound control.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknToolbar::CountComponentControls() const
    {
    return iVisibleItems.Count();
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ConstructFromResourceL
// Constructs controls from a resource file.
// -----------------------------------------------------------------------------
//
void CAknToolbar::ConstructFromResourceL( TResourceReader& aReader )
    {
    aReader.ReadInt8(); //version, not used currently
    aReader.ReadInt8();  //lines, not used currently
    iFlags = aReader.ReadInt32();

    TBool enableTransparency = CAknEnv::Static()->TransparencyEnabled() && 
        ( ( !( iFlags & KAknToolbarFixed ) && 
                !( iFlags & KAknToolbarFloatingUnTransparent ) ) || 
        ( iFlags & KAknToolbarTransparent && iFlags & KAknToolbarFixed ) ); 


    if( enableTransparency ) 
        {
        Window().SetRequiredDisplayMode( EColor16MA ); // Without this, ACT does not work in all cases in HW
        TInt err = Window().SetTransparencyAlphaChannel();

        if ( err == KErrNone ) // it should all ways be true in NGA
            {
            // Set the window initially completely transparent. This needs to be called only once.
            Window().SetBackgroundColor(~0);
            }
        }



    iFrameContext = CAknsFrameBackgroundControlContext::NewL( KAknsIIDQsnFrPopupSub, 
            TRect(), TRect(), ( iFlags & KAknToolbarFixed )? ETrue : EFalse );  

    iBgContext = CAknsBasicBackgroundControlContext::NewL(
        KAknsIIDQsnBgScreen, TRect(), ETrue );

    SetWithSliding( ETrue ); 

    TInt softkeyResource = aReader.ReadUint32(); //softkeys

    if ( softkeyResource > 0 )
        {
        iSoftkeyResource = softkeyResource; 
        }

    const TInt controlCount = aReader.ReadInt16();

    for ( TInt ii = 0; ii < controlCount; ii++ )
        {
        CAknToolbarItem* item = ConstructControlLC( aReader ); 
        if ( item )
            {
            if ( IsSupportedItemType( item->ControlType() ) )
                {
                iItems.AppendL( item );
                CleanupStack::Pop( item ); 
                }
            else
                {
                // we don't support this type
                CleanupStack::PopAndDestroy( item ); 
                }
            }
        }
    aReader.ReadInt32(); // extension link, not used currently


    SetOrientation( iOrientation ); 
    
    // If toolbar is fixed need to set size for toolbar so that it can reduce 
    // the rects correctly. 
    if ( iFlags & KAknToolbarFixed )
        {
        if ( iFlags & KAknToolbarDefault )
            {
            SetDimmed( ETrue ); 
            }
        SetFocusing( EFalse ); 
        SetRect( CalculateSizeAndPosition() ); 
        }

    AdjustAllButtons();
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ConstructFromResourceL
// Constructs controls from a resource file.
// -----------------------------------------------------------------------------
//
void CAknToolbar::ConstructFromResourceL( const TInt aResourceId ) 
    {    
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
    ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    iToolbarResourceId = aResourceId;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ControlOrNull
// Gets a pointer to the specified control.
// -----------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CAknToolbar::ControlOrNull( const TInt aControlId ) const
    {
    for ( TInt ii = 0; ii < iItems.Count(); ii++ )
        {
        CAknToolbarItem* item = iItems[ii];
        if ( item->CommandId() == aControlId )
            {
            return item->Control();
            }
        }
    return NULL;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetToolbarVisibility
// Shows or hides toolbar.
// The position of the top left corner should be set in advance.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::SetToolbarVisibility( const TBool aVisible )
    {
    SetToolbarVisibility( aVisible, ETrue );
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetToolbarVisibility
// If flag RD_SCALABLE_UI_V2 is not defined, toolbar is always focusing. 
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::SetToolbarVisibility( const TBool aVisible,
                                                 const TBool aFocusing )
    {
    if ( iInternalFlags.IsSet( EDisabled ) )
        {
        return; 
        }

    TBool visible = aVisible;
    
    if ( iInternalFlags.IsSet( ECalledFromFW ) )
        {
        if ( iInternalFlags.IsSet( EAppOverrideVisibility ) )
            {
            visible = EFalse;
            }
        }
    else
        {
        if ( aVisible )
            {
            iInternalFlags.Clear( EAppOverrideVisibility );
            }
        else
            {
            iInternalFlags.Set( EAppOverrideVisibility );
            }
        }        
      
    if ( iFlags & KAknToolbarFixed )
        {
        if ( visible )
            {
            iInternalFlags.Set( EFixedShown );
            }
        else
            {
            iInternalFlags.Clear( EFixedShown );
            }

        if ( visible && ( !AknLayoutUtils::PenEnabled() || 
            ( !Layout_Meta_Data::IsLandscapeOrientation() && iFlags & KAknToolbarDefault ) ) )
            {
            return; 
            }

        }
    if ( iFlags & KAknToolbarAlwaysFocusing )
        {
        SetFocusing( ETrue );
        }
    else
        {
#ifdef RD_SCALABLE_UI_V2
        if ( iFlags & KAknToolbarFixed )
            {
            SetFocusing( EFalse );             
            }
        else
            {
            SetFocusing( aFocusing );
            }
#else
        SetFocusing( ETrue ); 
#endif
        }

    if ( iInternalFlags.IsSet( EShown ) && visible )
        {
        if ( iFlags & KAknToolbarFixed )
            {
            return; 
            }
        if ( iInternalFlags.IsSet( EShown ) )
            {
            //using IsVisible() to avoide setting flag when toolbar is invisible.  
            if ( IsVisible() )
                {
                iInternalFlags.Set( EShowingAgain );
                }            
            ShowViaIdle(); 
            }

        return;
        }
       
    if ( visible )
        {
        if ( !(iFlags & KAknToolbarFixed ) )
            {
            ShowViaIdle(); 
            }
        else
            {
            TRAPD( err, ShowToolbarL() );
            if ( err != KErrNone )
                {
                // if we failed then softkeys should be deleted just in case if they 
                // were created before leave
                delete iToolbarCba;
                iToolbarCba = NULL;
                
                SetFocus( EFalse );
                CEikonEnv::Static()->EikAppUi()->UpdateStackedControlFlags( this, 
                    ~0, ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys );

                }
    
            }

        }
    else
        {
        TRAP_IGNORE( HideToolbarL() );
        }
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
static CTouchToolbarData* CheckRegistration( CCoeControl* aControl )
    {
    TInt key = reinterpret_cast<TInt>( aControl );
    TBool selectPressed = EFalse;
    
    CTouchToolbarData* data = reinterpret_cast<CTouchToolbarData*>( 
                                        CAknTransitionUtils::GetData( key ) );

    if ( data && data->SelectPressed() )
        {
        selectPressed = ETrue;
        }

    // If we're not already registered from the touchpane, register here for
    // a toolbar transition without the touchpane.
    if ( !data || !data->BetweenRegisterAndBegin() )
        {
        // We need to reset the data here, to make sure that
        // DemarcationRectSet() is false below.
        TRect rect;
        if ( CTouchToolbarData::SetData( aControl, rect, EFalse ) != 
             KErrNone )
            {
            return NULL;
            }
            
        // if already registered, then the toolbar client may have chosen a different
        // effect for the toolbar
        if( !GfxTransEffect::IsRegistered( aControl ) )
            {
            GfxTransEffect::Register( aControl, KGfxToolbarControlUid, EFalse );
            }
        GfxTransEffect::Enable();

        data = reinterpret_cast<CTouchToolbarData*>( 
                                        CAknTransitionUtils::GetData( key ) );

        if ( selectPressed )
            {
            data->SetSelectPressed( selectPressed );
            }    
        }

    return data;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ShowToolbarL
// Makes toolbar visible and activates it
// The position of the top left corner should be set in advance.
// -----------------------------------------------------------------------------
//
void CAknToolbar::ShowToolbarL()
    {
    if ( iFlags & KAknToolbarFixed &&
         ( !AknLayoutUtils::PenEnabled() ||
           iFlags & KAknToolbarDefault ) )
        {
        if ( IsVisible() )
            {
            MakeVisible( EFalse );
            }
        return;
        }
    iInternalFlags.Clear( EDrawBackground ); 
    // get specific settings from observer
    if ( iToolbarObserver )
        {
        iToolbarObserver->DynInitToolbarL( iToolbarResourceId, this );
        }

    // Check buttons if fixed toolbar
    if ( iFlags & KAknToolbarFixed && ! ( iFlags & KAknToolbarDefault ) )
        {
        CheckFixedToolbarButtonsL();
        }

    TRect rect( CalculateSizeAndPosition() );

    if ( iVisibleItems.Count() > 0  || ( iFlags & KAknToolbarFixed ) ) 
        {
        TBool tmpDisplayed = CEikonEnv::Static()->EikAppUi()->IsDisplayingMenuOrDialog();
        TBool tmpCondition = IsNonFocusing() ||( !IsNonFocusing() && tmpDisplayed ) ;
        CEikonEnv::Static()->EikAppUi()->UpdateStackedControlFlags( this, 
                tmpCondition ? ECoeStackFlagRefusesFocus : ECoeStackFlagStandard, 
            ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys );
        
        // This is called so toolbar can get focus if needed
        CEikonEnv::Static()->EikAppUi()->HandleStackChanged(); 
            
        TPoint startPos = rect.iTl;
        if ( iInternalFlags.IsSet( ESlidingSupported ) && iInternalFlags.IsSet( EWithSliding ) && 
            iOrientation == EAknOrientationHorizontal )
            {
            startPos.iX = -rect.Size().iWidth;
            }
        SetExtent( startPos, rect.Size() );
        UpdateControlPositions(); 

        TBool redrawStoreEnabled(EFalse);
        if( !CAknEnv::Static()->TransparencyEnabled() )
            {
            redrawStoreEnabled = Window().IsRedrawStoreEnabled();
            }

        CTouchToolbarData* data = CheckRegistration( this );      
        if ( data && !(iFlags & KAknToolbarFixed) && iAvkonAppUi->IsForeground() )
            {
            data->SetBetweenRegisterAndBegin( EFalse );
            
            CAknTransitionUtils::SetAllParents( this );

            Window().ClearRedrawStore( );

            GfxTransEffect::NotifyExternalState( ENotifyGlobalAbort );
            GfxTransEffect::Begin( this, KGfxControlAppearAction );
            }

        SetShown( ETrue );

        if ( data )
            {
            if ( data->DemarcationRectSet() )
                {
                GfxTransEffect::SetBeginDemarcation( this, data->DemarcationRect() );
                }
            else
                {        
                GfxTransEffect::SetBeginDemarcation( this, rect );
                }

            if ( CAknTransitionUtils::AddObserver( data, 
                         CAknTransitionUtils::EEventControlTransitionFinished,
                         reinterpret_cast<TDesC8*>( this ) ) == KErrNone )
                {
                GfxTransEffect::End( this );
                }
            else
                {
                CAknTransitionUtils::RemoveData( reinterpret_cast<TInt>( this ) );
                delete data;
                GfxTransEffect::Deregister( this );
                }

            if ( !CAknEnv::Static()->TransparencyEnabled() && redrawStoreEnabled )
                {
                Window().EnableRedrawStore( ETrue );
                }
            }

        // notify observer, for example touch pane, that toolbar was shown
        if ( Observer() )
            {
            Observer()->HandleControlEventL( this, 
                MCoeControlObserver::EEventStateChanged );
            }


        // Default toolbar window priority to low to prevent toolbar
        // to be drawn on top of a full-screen application
        if ( iFlags & KAknToolbarDefault && !iInternalFlags.IsSet( EItemsHidden ) )
            {
            DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityLow );
            }
        else
            {
            DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityNormal );    
            }
        
        if ( iFlags & KAknToolbarFixed )
            {
            SetOrdinalPositions();
            }

        ActivateL();

        //Also activating the items that are currently not in iVisibleItems
        for ( TInt ii = 0; ii < iItems.Count(); ++ii )
            {
            iItems[ii]->Control()->ActivateL(); 
            }


        // softkeys for focused toolbar only
        if ( !IsNonFocusing() && IsFocused() )
            {
            TBool withoutCba( iFlags & KAknToolbarWithoutCba );                    
            
            if ( !withoutCba )
                {                    
                if ( !iToolbarCba )
                    {
                    iToolbarCba = 
                        CEikButtonGroupContainer::NewL( CEikButtonGroupContainer::ECba, 
                                                        CEikButtonGroupContainer::EHorizontal,
                                                        this, iSoftkeyResource );
                    }

                if ( iToolbarCba->ButtonGroup() )
                    {
                    static_cast<CEikCba*>( iToolbarCba->ButtonGroup() )->
                        SetSkinBackgroundId( KAknsIIDQsnBgAreaControlPopup );
                    }
                }
            }
        else if ( iToolbarCba )
            {
            delete iToolbarCba;
            iToolbarCba = NULL;
            }


        if ( iInternalFlags.IsSet( ESlidingSupported ) && iInternalFlags.IsSet( EWithSliding ) )
            {
            SlideToolbar( rect.iTl );
            }
        else 
            {
            if ( !( iFlags & KAknToolbarFixed ) ) 
                {
                InitFocusedItemL( ETrue );
                }
            DrawNow();
            }
        }
    else
        {
        SetShown( EFalse );

        // notify observer, for example touch pane, that toolbar was closed
        if ( Observer() )
            {
            Observer()->HandleControlEventL( this, 
                MCoeControlObserver::EEventStateChanged );
            }
        }

    if ( !IsNonFocusing() )
        {
        SetFocus( ETrue );
        }
    }
 
// -----------------------------------------------------------------------------
// CAknToolbar::HideToolbar
// Disactivate toolbar and hides it.
// -----------------------------------------------------------------------------
//
void CAknToolbar::HideToolbarL()
    {
    if ( !iInternalFlags.IsSet( EShown ) ) // nothing to hide
        {
        if ( iFlags & KAknToolbarDefault && !AknLayoutUtils::PenEnabled()
              && IsVisible() )
            {
            MakeVisible( EFalse );
            }
        return;
        }

   if ( iIdle && iIdle->IsActive() ) 
        {
        iIdle->Cancel();  
        }       
        
    if ( !IsNonFocusing() & IsFocused() )
        {
        SetFocus( EFalse );
        }
    
    iLastFocusedItem = iFocusedItem;
  
    SelectItemL( iSelectedItem, EFalse );
    if ( !IsNonFocusing() && iFocusedItem < iVisibleItems.Count() &&
        iFocusedItem >= 0 )
        {
        // Take focus away from control so that it shows tooltip next time
        iVisibleItems[iFocusedItem]->SetFocusL( EFalse, ETrue, ENoDrawNow, this );
        }

    if ( iToolbarCba )
        {
        // we don't want toolbar to be focused again after softkeys are deleted
        // so it shouldn't get focus as the top item
        CEikonEnv::Static()->EikAppUi()->UpdateStackedControlFlags( this, 
            ~0, ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys );
                    
        delete iToolbarCba;
        iToolbarCba = NULL;
            
        CEikonEnv::Static()->EikAppUi()->UpdateStackedControlFlags( this, 
            0, ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys);
        
        }

    
    // Drawing toolbar background, when application hides toolbar
    if ( ( !iInternalFlags.IsSet( ECalledFromFW ) && !iInternalFlags.IsSet( EItemsHidden ) || 
        iInternalFlags.IsSet( EDrawBackground ) ) && iFlags & KAknToolbarFixed && 
        !( iFlags & KAknToolbarDsaMode ) && !( iFlags & KAknToolbarNoBackground ) ||
        iInternalFlags.IsSet( EItemsHidden ) && iFlags & KAknToolbarFixed &&
        !( iFlags & KAknToolbarDsaMode) && !( iFlags & KAknToolbarNoBackground ) ) 
        {
        
        if ( iInternalFlags.IsSet( EItemsHiddenWithPriority ) )
            {
            DrawableWindow()->SetOrdinalPosition( 0, iDrawingPriority );
            iInternalFlags.Clear( EItemsHiddenWithPriority );
            }
        else
            {
            DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityLow );            
            }

        iInternalFlags.Set( EDrawBackground );

        for ( TInt i = 0; i < iVisibleItems.Count(); i++ )
            {
            iVisibleItems[i]->Control()->MakeVisible( EFalse ); 
            }
          
        TRect rect = Rect(); 
        Window().Invalidate( rect );
        ActivateGc(); 
        Window().BeginRedraw( rect );

        CWindowGc& gc = SystemGc();
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        AknsDrawUtils::Background( skin, iBgContext, this, gc, rect, 
            KAknsDrawParamNoClearUnderImage );


        Window().EndRedraw();
        DeactivateGc();
        iInternalFlags.Clear( EShown ); 
        }
    CTouchToolbarData* data = CheckRegistration( this );

    TBool foreground = iAvkonAppUi->IsForeground();
    // The window is created asynchronously (in CreateDelayedWindow(), so if 
    // you click the toolbar button quickly enough, you can get here before
    // the window has actually been created, and in that case the app would
    // crash, hence the check.
    if ( &Window() && data && !data->SelectPressed() && !(iFlags & KAknToolbarFixed)
        && foreground )
        {
        data->SetBetweenRegisterAndBegin( EFalse );

        GfxTransEffect::NotifyExternalState( ENotifyGlobalAbort );
        GfxTransEffect::Begin( this, KGfxControlDisappearAction );
        }

    if ( !iInternalFlags.IsSet( EDrawBackground ) )
        {
        SetShown( EFalse );
        }

    if ( &Window() && data && !data->SelectPressed() && !(iFlags & KAknToolbarFixed)
         && foreground )        
        {
        if ( data->DemarcationRectSet() )
            {
            GfxTransEffect::SetEndDemarcation( this, data->DemarcationRect() );
            }
        else
            {        
            GfxTransEffect::SetEndDemarcation( this, Rect() );
            }

        if ( CAknTransitionUtils::AddObserver( data, 
                CAknTransitionUtils::EEventControlTransitionFinished,
                reinterpret_cast<const TDesC8*>( this ) ) == KErrNone )
            {
            GfxTransEffect::End( this );
            }
        else
            {
            CAknTransitionUtils::RemoveData( reinterpret_cast<TInt>( this ) );
            delete data;
            GfxTransEffect::Deregister( this );
            }
        }
    else if ( data )
        {
        CAknTransitionUtils::RemoveData( reinterpret_cast<TInt>( this ) );
        delete data;
        }
    if ( !iInternalFlags.IsSet( EDrawBackground ) ) 
        {
        DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityNeverAtFront );
        }

    CEikonEnv::Static()->EikAppUi()->UpdateStackedControlFlags( this, 
        ~0, ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys );

    // notify observer, for example touch pane, that toolbar was closed
    if ( Observer() )
        {
        Observer()->HandleControlEventL( this, 
            MCoeControlObserver::EEventStateChanged );
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetItemDimmed
// Dims (greys out) or undims a toolbar item.
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknToolbar::SetItemDimmed( const TInt aCommandId, 
                                          const TBool aDimmed, 
                                          const TBool aDrawNow ) 
    {
    CAknToolbarItem* item = ToolbarItemById( aCommandId );
    if ( item && item->Control() ) 
        {
        item->Control()->SetDimmed( aDimmed );
        if ( aDimmed && IsFocused() && item->Control()->IsFocused() )
            {
            // move selection to the next non-dimmed item
            if ( iFocusedItem == iVisibleItems.Count() - 1 )
                {
                TRAP_IGNORE( MoveHighlightL( 0, aDrawNow ) );
                }
            else 
                {
                TRAP_IGNORE( MoveHighlightL( ToolbarVisibleIndexById( aCommandId ) + 1, 
                    aDrawNow ) );
                }
            if ( iFocusedItem == KFocusedNone && item->Control()->IsFocused()  )
                {
                item->Control()->SetFocus( EFalse );
                }
            }
        if ( aDrawNow )
            {
            item->Control()->DrawDeferred();
            }
        }
    }



// -----------------------------------------------------------------------------
// CAknToolbar::HideItem
// Hides or unhides a toolbar item.
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknToolbar::HideItem( const TInt aCommandId,
                                     const TBool aHide, 
                                     const TBool aDrawNow )
    {
    CAknToolbarItem* item = ToolbarItemById( aCommandId );
    
    if ( !aHide && item && item->ControlType() == EAknCtButton && item->Control() )
        {
        CAknButton* button = static_cast<CAknButton*>( item->Control() ); 
        button->ResetState();           
        }
    
    if ( item && item->Control() && item->IsHidden() != aHide ) 
        {
        item->SetHidden( aHide ); 

        TInt itemIndex; 
        TRect rect; 
        if ( aHide )
            {
            itemIndex = ToolbarVisibleIndexByControl( item->Control() ); 
            TRAP_IGNORE( SelectItemL ( itemIndex, EFalse ) ); 
            rect = CalculateSizeAndPosition();
            }
        else
            {
            rect = CalculateSizeAndPosition();
            itemIndex = ToolbarVisibleIndexByControl( item->Control() ); 
            }
        UpdateControlVisibility(); 
        UpdateControlPositions();
        
        if ( itemIndex >=0 && itemIndex <= iFocusedItem && !IsNonFocusing() )
            {
            if ( aHide )
                {
                // Check if the hidden item was the last
                if ( iFocusedItem >= iVisibleItems.Count() )
                    {
                    iFocusedItem = iVisibleItems.Count() - 1; 
                    }
                else if ( iVisibleItems.Count() > 0 && 
                          !( itemIndex == 0 && iFocusedItem == 0 ) && 
                          ( itemIndex != iFocusedItem ) )
                    {
                    TRAP_IGNORE( MoveHighlightL( iFocusedItem - 1, EFalse ) );    
                    }
                }
            else 
                {
                TRAP_IGNORE( MoveHighlightL( iFocusedItem + 1, EFalse ) );    
                }
            }
        if ( iInternalFlags.IsSet( EShown ) && aDrawNow )
            {
            if ( !( iFlags & KAknToolbarFlexiblePosition ) )
                {
                SetPosition( rect.iTl );
                }
            SetSize( rect.Size() );
            DrawDeferred();
            }
        }
    else 
        {
        if ( aDrawNow )
            {
            DrawDeferred();
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknToolbar::SetToolbarObserver
// Sets the observer for the toolbar
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::SetToolbarObserver( MAknToolbarObserver* aObserver ) 
    {
    iToolbarObserver = aObserver;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ToolbarObserver
// Returns a pointer to the toolbar observer.
// -----------------------------------------------------------------------------
//
EXPORT_C MAknToolbarObserver* CAknToolbar::ToolbarObserver() 
    {
    return iToolbarObserver;
    }
// -----------------------------------------------------------------------------
// CAknToolbar::HandlePointerEventL
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::HandlePointerEventL( 
        const TPointerEvent& aPointerEvent )
    {
    if ( !DrawableWindow()->IsNonFading() && ( DrawableWindow()->IsFaded() 
         || iInternalFlags.IsSet( EDrawBackground ) ) )
        { 
        return; 
        } 

    TPointerEvent event( aPointerEvent );
    TBool override ( EFalse );
            
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )            
        {
        iPreviousItem = KSelectedNone;
        }
        
    // Cancel previous button
    if ( iPreviousItem >=0 && ( aPointerEvent.iType == TPointerEvent::EDrag ||
        aPointerEvent.iType == TPointerEvent::EButtonRepeat ) )
        {
        CAknToolbarItem* prevItem = iVisibleItems[iPreviousItem];

        if ( prevItem->Control() 
            && ( prevItem->ControlType() == EAknCtButton
            || prevItem->ControlType() == EAknCtToolbarExtension ) )
            {
            CAknButton* button = static_cast<CAknButton*>( prevItem->Control() );
            if ( !button->TouchArea().Contains( aPointerEvent.iPosition ) )
                {
                event.iType = TPointerEvent::EButton1Up;
                button->HandlePointerEventL ( event );
                override = ETrue;
                iPreviousItem = KSelectedNone;
                }
            }
        }
    
    CAknToolbarItem* item = NULL;
    for ( TInt ii = 0; ii < iVisibleItems.Count(); ++ii )
        {
        item = iVisibleItems[ii];
        if ( item->Control() && 
             item->Control()->Rect().Contains( aPointerEvent.iPosition ) )
            {
            if ( item->ControlType() == EAknCtButton || 
                 item->ControlType() == EAknCtToolbarExtension )
                {
                CAknButton* button = static_cast<CAknButton*>( item->Control() ); 
                
                if ( button->TouchArea().Contains( aPointerEvent.iPosition ) )
                    {
                    if ( ii != iPreviousItem )
                        {
                        if ( !button->IsDimmed() )
                            {
                            MoveHighlightL( ii, ETrue ); 
                            // focus has moved from one button to another due to dragging, 
                            // give sensitive feedback
                            if ( iPreviousItem != iFocusedItem && 
                                ( aPointerEvent.iType == TPointerEvent::EDrag ||
                                aPointerEvent.iType == TPointerEvent::EButtonRepeat ) )
                                {
                                MTouchFeedback* feedback = MTouchFeedback::Instance();
                                if ( feedback )
                                    {
                                    feedback->InstantFeedback( ETouchFeedbackSensitiveButton );
                                    }
                                }
                            }

                        if ( aPointerEvent.iType == TPointerEvent::EDrag ||
                            aPointerEvent.iType == TPointerEvent::EButtonRepeat ) 
                            {
                            button->SetHelpNoteTimeouts( KToolbarButtonBeforeTimeout, 0 );
                            event.iType = TPointerEvent::EButton1Down;
                            button->HandlePointerEventL( event );
                            override = ETrue;
                            }
                        iPreviousItem = ii;
                        }

                    if ( aPointerEvent.iType == TPointerEvent::EButton1Down )                    
                        {
                        iDownItem = ii;
                        button->SetHelpNoteTimeouts( KToolbarButtonBeforeTimeout, 0 );
                        }
                
                    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
                        {
                        // Up and down events are in different items, give basic
                        // feedback to the released item.
                        if ( ii != iDownItem && !button->IsDimmed() )
                            {
                            MTouchFeedback* feedback = MTouchFeedback::Instance();
                            if ( feedback )
                                {
                                feedback->InstantFeedback( ETouchFeedbackBasicButton );
                                }
                            }
                
                        button->HandlePointerEventL( aPointerEvent );
                        override = ETrue;
                        }
                    }
                else
                    {
                    // Button touchArea did not contain pointerevent
                    break;
                    }
                    
                }
            SelectItemL( ii, ETrue );
            }
        }

    if ( !override )        
        {
        CAknControl::HandlePointerEventL( aPointerEvent );        
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::HandleResourceChange
// Handles a change to the control's resources.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::HandleResourceChange( TInt aType ) 
    {
    // Base class method is not called because only visible components are
    // returned by ComponentControl -> all icons wouldn't be updated.
    
    if ( aType == KAknToolbarSetHiddenAndDrawBackground )
        {
        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            aType = KAknToolbarSetHidden;
            }
        else
            {
            if ( IsShown() )
                {
                iInternalFlags.Set( ECalledFromFW );
                if ( !( iFlags & KAknToolbarNoBackground ) )
                    {
                    iInternalFlags.Set( EDrawBackground );                  
                    }
                
                SetToolbarVisibility(EFalse, EFalse);
                iInternalFlags.Clear( ECalledFromFW );
                }
            else if ( iFlags & KAknToolbarDefault )
                {
                iInternalFlags.Clear( EFixedShown );
                }
            return;
            }
        }
        
    if ( aType == KAknToolbarSetVisible && iFlags & KAknToolbarDefault 
            && !AknLayoutUtils::PenEnabled() )
        {
        return; 
        }
    else if ( aType == KAknToolbarSetVisible && !IsShown() )
        {
        iInternalFlags.Set( ECalledFromFW );
        iInternalFlags.Clear( EDrawBackground ); 
        SetToolbarVisibility(ETrue, EFalse);
        iInternalFlags.Clear( ECalledFromFW );
        }
    else if ( aType == KAknToolbarSetHidden && IsShown() )
        {
        iInternalFlags.Set( ECalledFromFW );
        iInternalFlags.Clear( EDrawBackground ); 
        SetToolbarVisibility(EFalse, EFalse);
        iInternalFlags.Clear( ECalledFromFW );
        }
    else if ( aType == KAknToolbarSetHidden && 
              iInternalFlags.IsSet( EFixedShown ) )
        {
        iInternalFlags.Clear( EFixedShown );
        }
            
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        iPreviousItem = KSelectedNone;
        for(TInt i = 0; i < iVisibleItems.Count(); i++)
            {
            CAknToolbarItem* item = iVisibleItems[ i ];
            CAknButton* button = static_cast<CAknButton*>( item->Control() ); 
            button->ResetState();
            }
        if ( iFlags & KAknToolbarDefault && !AknLayoutUtils::PenEnabled() && IsVisible() )
            {
            TRAP_IGNORE( HideToolbarL() ); 
            return; 
            }
        else if ( iFlags & KAknToolbarFixed )
            {
            if ( Layout_Meta_Data::IsLandscapeOrientation() && AknLayoutUtils::PenEnabled() )
                {
                iOrientation = EAknOrientationVertical; 
                if ( ( iInternalFlags.IsSet( EFixedShown ) 
                    || ( iInternalFlags.IsSet( EItemsHidden )
                    && iInternalFlags.IsSet( EAppOverrideVisibility ) ) )
                    && !iInternalFlags.IsSet( EShown ) )
                    {
                    // When the window is faded (e.g. while showing
                    // some note, ShowViaIdle is too slow
                    if ( DrawableWindow()->IsFaded() )
                        {
                        TRAP_IGNORE( ShowToolbarL() );
                        }
                    else
                        {
                        ShowViaIdle();                          
                        }
                    }
                }
            else if ( !( iFlags & KAknToolbarDefault ) && AknLayoutUtils::PenEnabled() )
                {
                iOrientation = EAknOrientationHorizontal; 
                if ( iInternalFlags.IsSet( EFixedShown ) && !iInternalFlags.IsSet( EShown ) )
                    {
                    // If showing toolbar because HideItemsAndDrawOnlyBackground( EFalse )
                    // called, show toolbar immediately (ShowViaIdle is too slow)
                    if ( iInternalFlags.IsSet( EItemsHidden ) )
                        {
                        iInternalFlags.Clear( EItemsHidden );
                        TRAP_IGNORE( ShowToolbarL() ); 
                        }
                    else
                        {
                        ShowViaIdle();
                        }
                    }
                }
            else if ( ( !AknLayoutUtils::PenEnabled() || iFlags & KAknToolbarDefault ) && iInternalFlags.IsSet( EShown ) )
                {
                TRAP_IGNORE( HideToolbarL() ); 
                return; 
                }
            else
                {
                iOrientation = EAknOrientationHorizontal; 
                }
                
            // Ordinal positions must be set in both landscape & portrait. In
            // portrait that is needed in order to bring dialogs on top of the
            // fixed toolbar whereas in landscape that is needed to disable
            // toolbar's buttons when there is a dialog on the screen.
            if ( iInternalFlags.IsSet( EShown ) )
                {
                SetOrdinalPositions();
                }
            }

        //Recalculate size no matter whether toolbar is visible.
        {
        TRect rect( CalculateSizeAndPosition() );

        if ( !( iFlags & KAknToolbarFlexiblePosition ) )
            {
            SetPosition( rect.iTl );
            }
        else 
            {
            UpdateControlPositions(); 
            }

        SetSize( rect.Size() );
        }
            
        if ( iInternalFlags.IsSet( EShown ) )
        	{
            if ( IsFocused() )
                {
                TRAP_IGNORE( MoveHighlightL( iFocusedItem, EFalse ) );
                }
            
            }
        }
        
    for ( TInt ii = 0; ii < iItems.Count(); ++ii )
        {
        iItems[ii]->Control()->HandleResourceChange( aType );
        }
        
    if ( iInternalFlags.IsSet( EShown ) && ( aType == KAknsMessageSkinChange || 
        aType == KEikDynamicLayoutVariantSwitch ) )
        {
        if ( aType == KAknsMessageSkinChange )
            {
            DrawDeferred();    
            }
        }
        
    if ( aType == KEikMessageFadeAllWindows )
        {
        // non-fixed toolbar should not be focusable when its window is faded
        if ( !( iFlags & KAknToolbarFixed ) && IsVisible() && !IsNonFocusing() )
            {
            // Cope with a situation where a focusing toolbar was visible when
            // the application lost foreground when e.g. a task swapper was shown.
            // In that case TopFocusedControl == NULL since it has not been set
            // yet in CCoeAppUi. KEikMessageFadeAllWindows is sent via AknPopupFader
            // which is a window server message observer i.e. it gets all ws
            // events before any other processing is done.
            CAknAppUi* appUi = iAvkonAppUi;

            CCoeControl* topControl = appUi->TopFocusedControl();
            
            if ( topControl )
                {
                appUi->UpdateStackedControlFlags( this, ~0, 
                    ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys );

                appUi->HandleStackChanged();                
                }
            }
        }
    else if ( aType == KEikMessageUnfadeWindows )    
        {
        if ( !( iFlags & KAknToolbarFixed ) && IsVisible() && !IsNonFocusing() )
            {
            // window is unfaded, toolbar can be focused again
            CAknAppUi* appUi = iAvkonAppUi;
            
            appUi->UpdateStackedControlFlags( this, ECoeStackFlagStandard, 
                ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys );
            
            appUi->HandleStackChanged();
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknToolbar::HandleControlEventL
// Handles an event from an observed toolbar item.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::HandleControlEventL( CCoeControl* aControl,
                                                TCoeEvent aEventType )
    {
    switch ( aEventType )
        {
        
        case MCoeControlObserver::EEventRequestCancel:
            {
            CAknToolbarItem* item = ToolbarItemByControl( aControl );
            if ( item )
                {
                if ( item->ControlType() == EAknCtButton ||
                     item->ControlType() == EAknCtToolbarExtension )
                    {
                    CAknButton* button = static_cast<CAknButton*>( aControl );
                    button->SetHelpNoteTimeouts( KToolbarButtonBeforeTimeout,
                        KToolbarButtonInViewTimeout );
                    }
                }
            break;
            }
        case MCoeControlObserver::EEventRequestExit:
            {
            HideToolbarL();
            break;
            }
        case MCoeControlObserver::EEventStateChanged:
            {
            iEventModifiers &= ~(ELongPress | ELongPressEnded); 

            if ( ( iFlags & KAknToolbarLastUsedItemFocused ) && 
                !IsNonFocusing() && IsFocused() )
                {                
                iInitialFocusedItem = iFocusedItem;
                }
            CAknToolbarItem* item = ToolbarItemByControl( aControl );
            if ( item )
                {
                if ( item->ControlType() == EAknCtButton || 
                     item->ControlType() == EAknCtToolbarExtension)
                    {
                    CAknButton* button = static_cast<CAknButton*>( aControl ); 
                    button->SetHelpNoteTimeouts( KToolbarButtonBeforeTimeout, 
                        KToolbarButtonInViewTimeout ); 
                    }
                
                if ( iToolbarObserver )
                    {
                    // We don't want to start a transition if the toolbar
                    // is closed because select/ok was pressed.
                    CTouchToolbarData* d = CTouchToolbarData::GetData( this );
                    if ( !d )
                        {
                        TRect rect;
                        if ( CTouchToolbarData::SetData( this, rect, EFalse ) != 
                                KErrNone )
                            {
                            return;
                            }
                            
                        d = CTouchToolbarData::GetData( this );    
                        }
                    
                    if (NULL != d)
                        {
                        d->SetSelectPressed( ETrue );
                        }
                    
                    if ( iAvkonAppUi && iAvkonAppUi->IsForeground() )
                        {
                        iToolbarObserver->OfferToolbarEventL( item->CommandId() );
                        }
                    d = CTouchToolbarData::GetData( this );
                    if ( d )
                        {
                        d->SetSelectPressed( EFalse );
                        }
                    }
                }
            break;
            }
        case MCoeControlObserver::EEventRequestFocus:
            {
            if ( !IsNonFocusing() && !aControl->IsDimmed() )
                {
                CAknToolbarItem* item = ToolbarItemByControl( aControl ); 
                if ( item->ControlType() == EAknCtButton || 
                     item->ControlType() == EAknCtToolbarExtension )
                    {
                    CAknButton* button = static_cast<CAknButton*>(aControl); 
                    if ( button->IsDimmed() )
                        {
                        break; 
                        }
                    }
                // focus should be moved to this control
                TInt index = ToolbarVisibleIndexByControl( aControl );
                if ( index == KErrNotFound )
                    {
                    return;
                    }
                if ( !IsFocused() )
                    {
                    iLastFocusedItem = index;
                    SetFocus( ETrue, EDrawNow );
                    }
                else
                    {
                    MoveHighlightL( index, ETrue );
                    }
                }
            break;
            }
        case CAknButton::ELongPressEvent: 
        case CAknButton::ELongPressEndedEvent: 
            {
            iEventModifiers &= ~( ELongPressEnded | ELongPress); 
            iEventModifiers |= ( aEventType == CAknButton::ELongPressEvent ) ? 
                ELongPress : ELongPressEnded;  
            CAknToolbarItem* item = ToolbarItemByControl( aControl );

            if ( item && iToolbarObserver && iAvkonAppUi && iAvkonAppUi->IsForeground() )
                {
                iToolbarObserver->OfferToolbarEventL( item->CommandId() );
                }
            break; 
            }
        default:
            {
            break;
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::PositionChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::PositionChanged()
    {
    if ( iFlags & KAknToolbarFlexiblePosition && !iInternalFlags.IsSet( ESliding ) )
        {
        SetSize( CalculateSizeAndPosition().Size() );
        
        if ( IsFocused() )
            {
            TRAP_IGNORE( MoveHighlightL( iFocusedItem, EFalse ) ); 
            }
        }

    UpdateControlPositions(); 
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ProcessCommandL
// From MEikCommandObserver.
// Processes user commands.
// -----------------------------------------------------------------------------
//     
EXPORT_C void CAknToolbar::ProcessCommandL( TInt aCommandId )
    {
    switch ( aCommandId )
        {            
        case EAknSoftkeySelect:
            {
            // shouldn't be KFocusedNone either
            __ASSERT_ALWAYS( ( iFocusedItem >= 0 && iFocusedItem < iVisibleItems.Count() ), 
                Panic( EEikPanicInvalidIndex )); 
                
            if ( iFlags & KAknToolbarLastUsedItemFocused )
                {                
                iInitialFocusedItem = iFocusedItem;            
                }

            CAknToolbarItem* item = iVisibleItems[iFocusedItem];
            if ( item && item->Control() )
                {
                if ( !( item->ControlType() == EAknCtButton || 
                        item->ControlType() == EAknCtToolbarExtension ) )
                    {
                    SelectItemL( iFocusedItem, EFalse );
                    if ( iToolbarObserver )
                        {
                        iToolbarObserver->OfferToolbarEventL( item->CommandId() );
                        }
                    }
                }
            break;
            }
            
        case EAknSoftkeyClose:
        case EAknSoftkeyDone:
            {
            HideToolbarL();
            break;
            }

        default:
            {
            break;
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetDimmed
// Sets toolbar dimmed. Doesn't redraw.
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknToolbar::SetDimmed( TBool aDimmed ) 
    {
    for ( TInt ii = 0; ii < iItems.Count(); ii++ )
        {
        CAknToolbarItem* item = iItems[ii];
        if ( item && item->Control() )
            {
            item->Control()->SetDimmed( aDimmed );
            }
        }
    if ( aDimmed && !IsNonFocusing() )
        {
        iFocusedItem = KFocusedNone;
        if ( !iToolbarCba )
            {
            return; 
            }
        iToolbarCba->MakeCommandVisibleByPosition( 
            CEikButtonGroupContainer::ELeftSoftkeyPosition, EFalse ); 
        iToolbarCba->MakeCommandVisibleByPosition( 
            CEikButtonGroupContainer::EMiddleSoftkeyPosition, EFalse ); 
        iToolbarCba->DrawDeferred(); 
        }
    CCoeControl::SetDimmed( aDimmed );
    }

// -----------------------------------------------------------------------------
// CAknToolbar::OfferKeyEventL
// Handles key events.
// -----------------------------------------------------------------------------
//    
EXPORT_C TKeyResponse CAknToolbar::OfferKeyEventL( const TKeyEvent& aKeyEvent, 
                                                   TEventCode aType )
    {
    if ( aKeyEvent.iCode == EKeyEscape )
        {
        return EKeyWasNotConsumed; 
        }
        
    if ( IsNonFocusing() || !IsFocused() )
        {
        if ( iSelectedItem != KSelectedNone )
            {
            CAknToolbarItem* item = iVisibleItems[iSelectedItem];
            if ( item->Control() && !item->RefusesKeys() )
                {
                return item->Control()->OfferKeyEventL( aKeyEvent, aType );
                }
            }
        return EKeyWasNotConsumed;
        }

    if ( ( iFlags & KAknToolbarWithoutCba ) && 
        !IsNonFocusing() && IsFocused() )
        {
        if ( aKeyEvent.iCode == EKeyCBA1 || aKeyEvent.iCode == EKeyCBA2 || 
             aKeyEvent.iScanCode == EStdKeyDevice0 )
            {
            return EKeyWasNotConsumed;                 
            }
        
        CEikMenuPane* menuPane = NULL;
        TBool useFactoryMenu = ETrue;
        
        // if this is a view app then ask menu from the currently active view
        TVwsViewId uid;
        
        if ( iAvkonAppUi->GetActiveViewId( uid ) == KErrNone )
            {
            if ( uid.iAppUid != uid.iViewUid )
                {
                CEikMenuBar* menuBar = iAvkonViewAppUi->View( uid.iViewUid )->MenuBar();
                
                if ( menuBar )
                    {
                    menuPane = menuBar->MenuPane();
                    useFactoryMenu = EFalse;
                    }
                }
            }

        // use factory menu if available
        if ( useFactoryMenu )
            {
            CEikMenuBar* menuBar = iEikonEnv->AppUiFactory( *iAvkonAppUi )->MenuBar();
            
            if ( menuBar )
                {
                menuPane = menuBar->MenuPane();
                }
            }
        // if menu is displayed then toolbar should not use key events.
        if ( menuPane )
            {
            if ( menuPane->IsVisible() )
                {
                return EKeyWasNotConsumed;
                }
            }
        }
    
    TInt count = iItems.Count();
    if ( count == 0 || iFocusedItem == KFocusedNone )
        {
        return EKeyWasNotConsumed;
        }
    
    CAknToolbarItem* item = iVisibleItems[iFocusedItem];
    
    if ( ( !item || !item->IsSelected() ) && aType == EEventKey )
        {
        switch ( aKeyEvent.iCode )
            {
            case EKeyRightArrow:
            case EKeyDownArrow:
            case EKeyTab:
                if ( ( aKeyEvent.iCode == EKeyDownArrow  &&
                    iOrientation != EAknOrientationVertical ) || 
                    ( aKeyEvent.iCode == EKeyRightArrow  && 
                    iOrientation != EAknOrientationHorizontal ) )
                    {
                    return EKeyWasNotConsumed;
                    }

                if ( count == 1 )
                    {
                    return EKeyWasConsumed;
                    }
                
                if ( iFocusedItem + 1 < iVisibleItems.Count() )
                    {
                    MoveHighlightL( iFocusedItem + 1, ETrue );
                    }
                else
                    {
                    MoveHighlightL( 0, ETrue );
                    }
                return EKeyWasConsumed;
                
            case EKeyLeftArrow:
            case EKeyUpArrow:
                if ( ( aKeyEvent.iCode == EKeyUpArrow &&
                    iOrientation != EAknOrientationVertical ) || 
                    ( aKeyEvent.iCode == EKeyLeftArrow && 
                    iOrientation != EAknOrientationHorizontal ) )
                    {
                    return EKeyWasNotConsumed;
                    }
                    
                if ( count == 1 )
                    {
                    return EKeyWasConsumed;
                    }
                
                if ( iFocusedItem - 1 >= 0 )
                    {
                    MoveHighlightL( iFocusedItem - 1, ETrue, EFalse, ETrue );
                    }
                else
                    {
                    MoveHighlightL( iVisibleItems.Count() - 1, ETrue, EFalse, 
                                     ETrue );
                    }
                return EKeyWasConsumed;
                
            default:
                break;
            }
        }
        
    // All key events can be given to buttons, other toolbar items must 
    // be seleceted to get events
    if ( item && item->Control() )
        {
        if ( ( item->ControlType() == EAknCtButton ) || 
           ( item->ControlType() == EAknCtToolbarExtension )  || item->IsSelected() )
            {
            if ( aKeyEvent.iScanCode == EStdKeyDevice0 )
                {
                TKeyEvent keyEvent = aKeyEvent; 
                // Button does not accept key events if the code is EStdKeyDevice0
                // so changing the key event to EStdKeyDevice3    
                keyEvent.iScanCode = EStdKeyDevice3; 
                item->Control()->OfferKeyEventL( keyEvent, aType );
                }
            else
                {
                item->Control()->OfferKeyEventL( aKeyEvent, aType );
                }
            }
        }

    return EKeyWasConsumed; // To avoid loss of focus
    }

// -----------------------------------------------------------------------------
// CAknToolbar::InputCapabilities
// Gets the control's input capabilities.
// -----------------------------------------------------------------------------
//    
EXPORT_C TCoeInputCapabilities CAknToolbar::InputCapabilities() const 
    {
    return TCoeInputCapabilities::EAllText;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::MopSupplyObject
// Retrieves an object of the same type as that encapsulated in aId.
// -----------------------------------------------------------------------------
//    
EXPORT_C TTypeUid::Ptr CAknToolbar::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == CEikCba::ETypeId )
        {
        if ( iToolbarCba && iToolbarCba->ButtonGroupType() == 
            CEikButtonGroupContainer::ECba )
            {
            return aId.MakePtr( static_cast<CEikCba*>( iToolbarCba->ButtonGroup() ) );
            }    
        else
            {
            return TTypeUid::Null();
            }
        }
    else if ( iToolbarCba && aId.iUid == CEikButtonGroupContainer::ETypeId )
        {
        return aId.MakePtr( iToolbarCba );
        }
    return CCoeControl::MopSupplyObject(aId);
    }

// -----------------------------------------------------------------------------
// CAknToolbar::Draw
// From MCoeControlBackground
// Draw the background for a given control.
// The text drawer that shall be used to draw text on the specific background 
// can be fetched through the GetTextDrawer() method. 
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknToolbar::Draw( CWindowGc& aGc, const CCoeControl& aControl, 
                                 const TRect& aRect ) const 
    {
    if ( !( iFlags & KAknToolbarFixed ) )
        {
        SetOrdinalPositions();
        }

    if ( iFlags & KAknToolbarNoBackground )
        {
        return;
        }

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
    aGc.SetClippingRect( aRect );
    
    CAknToolbarItem* item = ToolbarItemByControl( &aControl ); 
    
    if ( iFlags & KAknToolbarFixed )
        {
        TRAP_IGNORE( DrawFixedBackgroundL( aGc, aControl, aRect) );
        return;
        }

    if ( item && ( item->ControlType() == EAknCtButton || 
        item->ControlType() == EAknCtToolbarExtension ) ) 
        {
        CAknButton* button = static_cast<CAknButton*>( item->Control() ); 
        if ( !( button && ( button->ButtonFlags() & KAknButtonNoFrame ) ) )
            {
            AknsDrawUtils::Background( skin, iFrameContext, aGc, aRect );
            }
        }
    else
        {
        AknsDrawUtils::Background( skin, iFrameContext, aGc, aRect );
        }

    if ( iFocusedItem == KFocusedNone )
        {
        return; 
        }
    if ( !IsNonFocusing() && ( iFlags & KAknToolbarSmall ) && 
        &aControl == iVisibleItems[iFocusedItem]->Control() )
            {
            CAknToolbarItem* item = iVisibleItems[iFocusedItem];
            if ( item && item->HighlightRect().Intersects( aRect ) )
                {
                TAknLayoutRect topLeft;
                topLeft.LayoutRect( item->HighlightRect(),
                    SkinLayout::Highlight_skin_placing__grid__Line_2() );
          
                TAknLayoutRect bottomRight;
                bottomRight.LayoutRect( item->HighlightRect(),
                    SkinLayout::Highlight_skin_placing__grid__Line_5() );
          
                TRect outerRect( topLeft.Rect().iTl, bottomRight.Rect().iBr );
                TRect innerRect( topLeft.Rect().iBr, bottomRight.Rect().iTl );

                if ( iFlags & KAknToolbarTransparent )
                    {
                    outerRect.Move(TPoint(-(topLeft.Rect().iTl.iX),-(topLeft.Rect().iTl.iY))); 
                    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                              aGc, outerRect, innerRect,
                                              KAknsIIDQsnFrGrid, KAknsIIDDefault );  // to another skin id ( Alpha )
                    }
                else
                    {
                    if ( !AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(), 
                                                aGc, outerRect, innerRect,
                                                KAknsIIDQsnFrGrid, KAknsIIDDefault ) )
                        {
                        aGc.SetBrushColor( KRgbRed );
                        aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                        aGc.DrawRect( item->HighlightRect() );
                        }                
                    }
                }
            }

    }

// -----------------------------------------------------------------------------
// CAknToolbar::ComponentControl
// Gets the specified component of a compound control.
// -----------------------------------------------------------------------------
//    
EXPORT_C CCoeControl* CAknToolbar::ComponentControl( TInt aIndex ) const
    {
    if ( aIndex < iVisibleItems.Count() && aIndex >= 0 )
        {
        return iVisibleItems[aIndex]->Control();
        }
    return NULL;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SizeChanged
// Responds to size changes to sets the size and position of the contents 
// of this control.
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknToolbar::SizeChanged()
    {
    // Setup skin
    const TRect popupRect( Rect() );
    if(  popupRect.IsEmpty() || !iFrameContext )
    {
        return ;
    }
    TAknLayoutRect topLeft;
    topLeft.LayoutRect( popupRect, SkinLayout::Submenu_skin_placing_Line_2() );
    TAknLayoutRect bottomRight;
    bottomRight.LayoutRect( popupRect, SkinLayout::Submenu_skin_placing_Line_5() );
    TRect outerRect = TRect( topLeft.Rect().iTl, bottomRight.Rect().iBr );
    TRect innerRect = TRect( topLeft.Rect().iBr, bottomRight.Rect().iTl );

    if ( ( !( iFlags & KAknToolbarFixed ) && 
         !( iFlags & KAknToolbarFloatingUnTransparent ) ) )
        {
        TRegionFix<4> transparentRegion;
        // left side
        transparentRegion.AddRect( TRect( outerRect.iTl, TPoint( innerRect.iTl.iX, outerRect.iBr.iY ) ) );
        // right side
        transparentRegion.AddRect( TRect( TPoint( innerRect.iBr.iX, outerRect.iTl.iY ), outerRect.iBr ) );
        // top center
        transparentRegion.AddRect( TRect( innerRect.iTl.iX, outerRect.iTl.iY, innerRect.iBr.iX, innerRect.iTl.iY ) );
        // bottom center
        transparentRegion.AddRect( TRect( innerRect.iTl.iX, innerRect.iBr.iY, innerRect.iBr.iX, outerRect.iBr.iY ) );

        Window().SetTransparentRegion( transparentRegion );
        }

    iFrameContext->SetFrameRects( outerRect, innerRect );

    iFrameContext->SetParentPos( Position() ); 

    iBgContext->SetParentPos( iAvkonAppUi->ApplicationRect().iTl );
    iBgContext->SetRect( iAvkonAppUi->ApplicationRect() ); 
    
    //reset button tooltip position
    UpdateItemTooltipPosition();
    }

// -----------------------------------------------------------------------------
// CAknToolbar::FocusChanged
// This function is called whenever a control gains or loses focus.
// -----------------------------------------------------------------------------
// 
EXPORT_C void CAknToolbar::FocusChanged( TDrawNow aDrawNow )
    {
    if ( !iInternalFlags.IsSet( EShown ) || IsNonFocusing() )
        {
        return; // nothing should be done in this case 
        }

    TBool withoutCba( iFlags & KAknToolbarWithoutCba );    
    if ( IsFocused() )
        {
        if ( !withoutCba )
            {            
            if ( !iToolbarCba )
                {
                TRAP_IGNORE( iToolbarCba = 
                    CEikButtonGroupContainer::NewL( CEikButtonGroupContainer::ECba, 
                                                    CEikButtonGroupContainer::EHorizontal,
                                                    this, iSoftkeyResource ) ); //lint !e665
                }
            }
        if ( iToolbarCba && iToolbarCba->ButtonGroup() )
            {
            static_cast<CEikCba*>( iToolbarCba->ButtonGroup() )->SetSkinBackgroundId( 
                KAknsIIDQsnBgAreaControlPopup );
            }
        
        if ( iLastFocusedItem == KFocusedNone ) 
            {
            TRAP_IGNORE( InitFocusedItemL( aDrawNow ) );
            }
        else
            {
            TRAP_IGNORE( MoveHighlightL( iLastFocusedItem, aDrawNow ) );
            }
        }
    else
        {
        iLastFocusedItem = iFocusedItem;
        }
    }
    
// -----------------------------------------------------------------------------
// CAknToolbar::ExtensionInterface
// For future extensions
// -----------------------------------------------------------------------------
//
EXPORT_C void* CAknToolbar::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }
// -----------------------------------------------------------------------------
// CAknToolbar::Draw
// Draw a control called by window server.
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknToolbar::Draw( const TRect& aRect ) const
    {
    if ( !( iFlags & KAknToolbarFixed ) )
        {
        SetOrdinalPositions();
        }

    CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    // Draw background         
    if ( iFlags & KAknToolbarFixed && 
         iBgRect.Height() > 0 &&
         iBgRect.Width() > 0 )
        {
        if ( aRect.Intersects( iBgRect ) )
            {
            TBool idleLayout( AknStatuspaneUtils::IdleLayoutActive() );
            TBool wallpaperInUse( EFalse );    

            if ( iInternalFlags.IsSet( EInIdle ) || idleLayout )
                {
                CRepository* repository = 0;
                TRAP_IGNORE( repository = CRepository::NewL(KCRUidPersonalisation) );
				if( repository )	
					{
					repository->Get( KPslnWallpaperType, wallpaperInUse );
					delete repository;
					}
                }
            
            if ( wallpaperInUse != 0 && Layout_Meta_Data::IsLandscapeOrientation() && iInternalFlags.IsSet( EItemsHidden ) )
                {                
                iBgContext->SetBitmap( KAknsIIDWallpaper );
                }
            AknsDrawUtils::Background( skin, iBgContext, this, gc, iBgRect, 
            KAknsDrawParamNoClearUnderImage );
            }
        }

    if ( ( iFlags & KAknToolbarFixed ) ||
         ( iFlags & KAknToolbarNoBackground ) )
        {
        // fixed toolbar doesn't draw anything itself - all drawing is done
        // through background drawer implementation
        return;
        }

    gc.SetClippingRect( aRect );

    if ( iFlags & KAknToolbarFixed )
        {
        AknsDrawUtils::Background( skin, iFrameContext, this, gc, aRect, KAknsDrawParamNoClearUnderImage );
        }
    else
        {
        AknsDrawUtils::Background( skin, iFrameContext, gc, aRect );
        }         

    // draw toolbar item highlight if toolbar is not small
    if ( !IsNonFocusing() && iFocusedItem != KFocusedNone && !( iFlags & KAknToolbarSmall ) )
        {
        CAknToolbarItem* item = iVisibleItems[iFocusedItem];
        if ( item && item->HighlightRect().Intersects( aRect ) )
            {
            TAknLayoutRect topLeft;
            topLeft.LayoutRect( item->HighlightRect(),
                SkinLayout::Highlight_skin_placing__grid__Line_2() );
          
            TAknLayoutRect bottomRight;
            bottomRight.LayoutRect( item->HighlightRect(),
                SkinLayout::Highlight_skin_placing__grid__Line_5() );
          
            TRect outerRect( topLeft.Rect().iTl, bottomRight.Rect().iBr );
            TRect innerRect( topLeft.Rect().iBr, bottomRight.Rect().iTl );
    
            if ( !AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(), 
                                            gc, outerRect, innerRect,
                                            KAknsIIDQsnFrGrid, KAknsIIDDefault ) )
                {
                gc.SetBrushColor( KRgbRed );
                gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                gc.DrawRect( item->HighlightRect() );
                }                
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::AddItemL
// Adds one new item to the toolbar.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::AddItemL( CCoeControl* aItem, 
                                     const TInt aType, 
                                     const TInt aCommandId, 
                                     const TInt aFlags ) 
    {
    AddItemL( aItem, aType, aCommandId, aFlags, iItems.Count() );
    }

// -----------------------------------------------------------------------------
// CAknToolbar::AddItemL
// Adds one new item to the toolbar.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::AddItemL( CCoeControl* aItem, 
                                     const TInt aType, 
                                     const TInt aCommandId, 
                                     const TInt aFlags, 
                                     const TInt aIndex ) 
    {
    if ( aItem && IsSupportedItemType( aType ) )
        {
        aItem->SetContainerWindowL( *this );
        aItem->SetBackground( this );
        
        if ( aType != EAknCtToolbarExtension )
            {
            aItem->SetObserver( this );
            }

        CAknToolbarItem* tbItem = new ( ELeave ) CAknToolbarItem( aItem, aType, 
            aCommandId, aFlags );
        CleanupStack::PushL( tbItem );
        iItems.InsertL( tbItem, aIndex );
        CleanupStack::Pop( tbItem );

        TRect rect = CalculateSizeAndPosition();
        UpdateControlVisibility();
        TInt itemIndex = ToolbarVisibleIndexById( aCommandId ); 

        if ( itemIndex <= iFocusedItem && IsFocused() && itemIndex >= 0 )
            {
            MoveHighlightL( iFocusedItem + 1, EFalse );   
            }
        if ( aType == EAknCtButton || aType == EAknCtToolbarExtension  )
            {
            AdjustButton( *static_cast<CAknButton*>( aItem ) );
            }

        if ( iInternalFlags.IsSet( EShown ) )
            {
            aItem->ActivateL(); 

            if ( !( iFlags & KAknToolbarFlexiblePosition ) )
                {
                SetPosition( rect.iTl );
                }
            else 
                {
                UpdateControlPositions(); 
                }
            SetSize( rect.Size() );
            DrawDeferred();
            }
        }
    else
        {
        User::Leave( KErrNotSupported );
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::RemoveItem
// Removes the item according to the specified ID
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::RemoveItem( const TInt aCommandId ) 
    {
    TInt itemIndex = ToolbarItemIndexById( aCommandId );
    if ( itemIndex >= 0 && itemIndex < iItems.Count() )
        {
        TInt visibleIndex = ToolbarVisibleIndexById( aCommandId ); 

        delete iItems[itemIndex];
        iItems.Remove( itemIndex );

        TRect rect = CalculateSizeAndPosition();
        UpdateControlVisibility();

        if ( visibleIndex >= 0 && visibleIndex < iFocusedItem && IsFocused() )
            {
            TRAP_IGNORE( MoveHighlightL( iFocusedItem - 1, EFalse ) ); 
            }
        if ( iInternalFlags.IsSet( EShown ) )
            {
            if ( !( iFlags & KAknToolbarFlexiblePosition ) )
                {
                SetPosition( rect.iTl );
                }
            else 
                {
                UpdateControlPositions(); 
                }
            SetSize( rect.Size() );
            DrawDeferred();
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::IsSupportedItemType
// Returns ETrue if item is supported. 
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknToolbar::IsSupportedItemType( const TInt aType ) const 
    {
    switch ( aType )
        {
        case EAknCtButton:
        case EAknCtToolbarExtension :
            {
            return ETrue;
            }
        default:
            {
#ifdef RD_SCALABLE_UI_V2
            if ( iFlags & KAknToolbarSmall || iFlags & KAknToolbarFixed  )
                {
                return EFalse; 
                }
            else 
                {
                return ETrue;
                }
#else   
            return EFalse; 
#endif

            }
        }
    }
   
// -----------------------------------------------------------------------------
// CAknToolbar::SetInitialFocusedItem
// Changes the command ID for the initially focused item when toolbar
//  is shown or gain focus.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::SetInitialFocusedItem( const TInt aCommandId )
    {
    iInitialFocusedItem = ToolbarVisibleIndexById( aCommandId );
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetEmphasis
// Called by the framework to handle the emphasising or 
// de-emphasising of a toolbar window when it is needed. 
// -----------------------------------------------------------------------------
//   
EXPORT_C void CAknToolbar::SetEmphasis( const TBool aEmphasis )
    {
    if ( iInternalFlags.IsSet( EShown ) )
        {
        CEikonEnv::Static()->EikAppUi()->UpdateStackedControlFlags( this, 
            aEmphasis ? 0 : ECoeStackFlagRefusesFocus, ECoeStackFlagRefusesFocus );
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::IsShown
// Returns toolbar visibility at this moment 
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknToolbar::IsShown() const
    {
    return ( iInternalFlags.IsSet( EShown ) || ( iIdle && iIdle->IsActive() ) );
    }
    
// -----------------------------------------------------------------------------
// CAknToolbar::SetWithSliding
// Specifies whether toolbar should be shown with sliding effect or not.
// By default toolbar is shown with sliding.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::SetWithSliding( const TBool /* aSlide */ )
    {
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetCloseOnCommand
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknToolbar::SetCloseOnCommand( const TInt aCommandId,
                                              const TBool aClose )
    {
    CAknToolbarItem* item = ToolbarItemById( aCommandId );
    if ( item )
        {
        item->SetCloseOnCommand( aClose );
        }
    } //lint !e1762 function cannot be made const

// -----------------------------------------------------------------------------
// CAknToolbar::SetCloseOnAllCommands
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknToolbar::SetCloseOnAllCommands( const TBool aClose )
    {
    for ( TInt ii = 0; ii < iItems.Count(); ++ii )
        {
        iItems[ii]->SetCloseOnCommand( aClose );
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetOrientation
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknToolbar::SetOrientation( const TAknOrientation aOrientation )
    {
    iOrientation = aOrientation;
    if ( iFlags & KAknToolbarFixed )
        {
        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            iOrientation = EAknOrientationVertical; 
            }
        else
            {
            iOrientation = EAknOrientationHorizontal; 
            }
        }
    if ( iFlags & KAknToolbarTransparent )
        {        
        TAknsItemID bgContextId; 
        if ( iFlags & KAknToolbarSmall )
            {
            bgContextId = KAknsIIDQgnGrafPopupTrans;
            }
        else 
            {
            bgContextId = ( iOrientation == EAknOrientationHorizontal ? 
                KAknsIIDQgnGrafBgTouchHorizontal : KAknsIIDQgnGrafBgTouchVertical );
            }
        iFrameContext->SetFrame( bgContextId );
        if ( iFlags & KAknToolbarSmall )
            {
            iFrameContext->SetCenter( KAknsIIDQgnGrafPopupTransCenter ); 
            }
        } 

    TRect rect = CalculateSizeAndPosition();
    // Set focused item again to avoid panic in a case when toolbar has more 
    // items in previous orientation and some of the items that do not 
    // fit to toolbar in this orientation was focused. 
    if ( IsFocused() )
        {
        TRAP_IGNORE( MoveHighlightL( iFocusedItem, EFalse ) ); 
        }

    if ( iInternalFlags.IsSet( EShown ) )
        {
        if ( !( iFlags & KAknToolbarFlexiblePosition ) )
            {
            SetPosition( rect.iTl );
            }
        else 
            {
            UpdateControlPositions(); 
            }
        SetSize( rect.Size() );
        DrawDeferred();
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::NotifyBackgroundChange
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::UpdateBackground() 
    {
    return ;
    }


// -----------------------------------------------------------------------------
// CAknToolbar::ShowToolbarForBackgroundUpdate
// Shows toolbar after it has been hidden with HideToolbarForBackgroundUpdate
// this function is deserted for NGA's removing BitmapDevice
// -----------------------------------------------------------------------------
//
void CAknToolbar::ShowToolbarForBackgroundUpdate()
    {
	  return;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::DisableToolbarL
// This disables toolbar so that it cannot be enabled. This is needed especially
// if a dialog is shown on the screen and toolbar should not be enabled by the 
// user from touch pane. 
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::DisableToolbarL( TBool aDisable )
    {
    if ( iInternalFlags.IsSet( EShown ) )
        {
        User::Leave( KErrToolbarShown ); 
        }

    // notify observer (touch pane) that toolbar is disabled 
    if ( aDisable )
        {
        iInternalFlags.Set( EDisabled );
        
        if ( Observer() )
            {
            Observer()->HandleControlEventL( this, 
                static_cast<MCoeControlObserver::TCoeEvent>( KDisableToolbar ) );
            }
        }
    else 
        {
        iInternalFlags.Clear( EDisabled );

        if ( Observer() )
            {
            Observer()->HandleControlEventL( this, 
                static_cast<MCoeControlObserver::TCoeEvent>( KEnableToolbar ) );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::IsToolbarDisabled
// Returns ETrue if toolbar is disabled
// -----------------------------------------------------------------------------
//    
EXPORT_C TBool CAknToolbar::IsToolbarDisabled() const
    {
    return iInternalFlags.IsSet( EDisabled ); 
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetFocusedItemL
// Sets toolbar item focused if found. 
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknToolbar::SetFocusedItemL( const TInt aCommandId )
    {
    TInt visibleIndex = ToolbarVisibleIndexById( aCommandId ); 
    if ( visibleIndex == KErrNotFound || IsNonFocusing() )
        {
        User::Leave( KErrNotFound ); 
        }

    if ( visibleIndex == iFocusedItem )
        {
        return;
        }

    // There are only buttons in a focusable toolbar
    CAknToolbarItem* item = iVisibleItems[visibleIndex];
    CAknButton* button = static_cast<CAknButton*>( item->Control() ); 

    if ( button && button->IsDimmed() )
        {
        return; 
        }

    TInt oldFocused = iFocusedItem; 

    iFocusedItem = visibleIndex; 

    // set this item focused
    item->SetFocusL( ETrue, EFalse, ENoDrawNow, this );
    DrawNow( item->HighlightRect() );

    if ( oldFocused != KFocusedNone )
        {
        item = iVisibleItems[oldFocused];
        if ( item && item->Control() )
            {
            SelectItemL( oldFocused, EFalse );

            // take the focus away
            item->SetFocusL( EFalse, EFalse, ENoDrawNow, this );
            DrawNow( item->HighlightRect() );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::FocusedItem
// Returns focused toolbar item command id  
// -----------------------------------------------------------------------------
//    
EXPORT_C TInt CAknToolbar::FocusedItem() const
    {
    if ( iFocusedItem < 0 || iFocusedItem >= iVisibleItems.Count() )
        {
        return KErrNotFound; 
        }
    CAknToolbarItem* item = iVisibleItems[iFocusedItem]; 
    return item->CommandId(); 
    }

// -----------------------------------------------------------------------------
// CAknToolbar::PrepareForFocusLossL
// Takes focus away from editor/other controls if needed
// -----------------------------------------------------------------------------
//    
void CAknToolbar::PrepareForFocusLossL()
    {
    if ( iSelectedItem != KSelectedNone )
        {
        SelectItemL( iSelectedItem, EFalse ); 
        }
    }


// -----------------------------------------------------------------------------
// CAknToolbar::EventModifiers
// Returns event modifiers
// -----------------------------------------------------------------------------
//    
EXPORT_C TInt CAknToolbar::EventModifiers() const
    {
    return iEventModifiers; 
    }


// -----------------------------------------------------------------------------
// CAknToolbar::ToolbarFlags
// Returns toolbar flags
// -----------------------------------------------------------------------------
//    
EXPORT_C TInt CAknToolbar::ToolbarFlags() const
    {
    return iFlags; 
    }


// -----------------------------------------------------------------------------
// CAknToolbar::FadeBehindPopup
// Fades behind popup
// -----------------------------------------------------------------------------
//    
void CAknToolbar::FadeBehindPopup( TBool aFade )
    {
    iFader.FadeBehindPopup( this, this, aFade );
    }


// -----------------------------------------------------------------------------
// CAknToolbar::CountFadedComponents
// Counts faded components
// -----------------------------------------------------------------------------
//    
TInt CAknToolbar::CountFadedComponents()
    {
    TInt count = 1; //this
    if ( iToolbarCba )
        {
        count++; 
        }
    if ( ToolbarExtension() && ToolbarExtension()->ExtensionView() )
        {
        count++; 
        }
    return count; 
    }

// -----------------------------------------------------------------------------
// CAknToolbar::FadedComponent
// Returns faded components
// -----------------------------------------------------------------------------
//    
CCoeControl* CAknToolbar::FadedComponent(TInt aIndex)
    {
    switch ( aIndex )
        {
        case 0: 
            return this; 
        case 1: 
            if ( iToolbarCba )
                {
                return iToolbarCba; 
                }
            return ToolbarExtension()->ExtensionView();         
        case 2: 
            return ToolbarExtension()->ExtensionView(); 
        default: 
            return NULL; 
        }
    }


// -----------------------------------------------------------------------------
// CAknToolbar::ReduceRect
// Reduces main pane rect
// -----------------------------------------------------------------------------
//    
void CAknToolbar::ReduceRect( TRect& aBoundingRect ) const
    {
    TBool toolbarNotVisible( !IsShown() && !( iFlags & KAknToolbarDefault ) );
    TBool fixedToolbar( iFlags & KAknToolbarFixed );
    TBool landscapeOrientation( Layout_Meta_Data::IsLandscapeOrientation() );
    TBool touchEnabled( AknLayoutUtils::PenEnabled() );
    TBool defaultContent( iFlags & KAknToolbarDefault );

    if ( toolbarNotVisible || 
         !fixedToolbar ||
         ( defaultContent && !landscapeOrientation ) ||
         !touchEnabled ||
         ( fixedToolbar && defaultContent ) )
        {
        return;
        }
    TRect appRect, toolbarRect; 
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow, 
                                       appRect); 
    if ( !Layout_Meta_Data::IsLandscapeOrientation() )
        {
        toolbarRect = RectFromLayout( appRect,
            AknLayoutScalable_Avkon::area_side_right_pane( 6 ) );
        }
    else
        {
        toolbarRect = RectFromLayout( appRect,
            AknLayoutScalable_Avkon::area_side_right_pane( 0 ) );
        }


    if ( toolbarRect.Intersects( aBoundingRect ) )
        {
        toolbarRect.Intersection( aBoundingRect );

        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            aBoundingRect.iBr.iX = toolbarRect.iTl.iX; 
            }
        else 
            {
            aBoundingRect.iBr.iY = toolbarRect.iTl.iY; 
            }
        }
    }
 

// -----------------------------------------------------------------------------
// CAknToolbar::SetSoftkeyResourceIdL
// Sets softkey resource id for toolbar
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknToolbar::SetSoftkeyResourceIdL( TInt aSoftkeyResourceId )
    {
    iSoftkeyResource = aSoftkeyResourceId; 
    if ( iToolbarCba )
        {
        iToolbarCba->SetCommandSetL( iSoftkeyResource ); 
        iToolbarCba->DrawDeferred(); 
        }
    }


// -----------------------------------------------------------------------------
// CAknToolbar::ExtensionEventL
// Extension notifies of its events using this method
// -----------------------------------------------------------------------------
//
void CAknToolbar::ExtensionEventL( TInt aCommandId )
    {
    if ( iToolbarObserver )
        {
        iToolbarObserver->OfferToolbarEventL( aCommandId ); 
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ConstructControlLC
// Constructs one of the toolbar items
// -----------------------------------------------------------------------------
//    
CAknToolbarItem* CAknToolbar::ConstructControlLC( TResourceReader& aReader )
    {
    CAknToolbarItem* item = new(ELeave) CAknToolbarItem;
    CleanupStack::PushL( item );

    item->ConstructFromResourceL( aReader );
    if ( item->Control() )
        {
        item->Control()->SetContainerWindowL( *this );
        item->Control()->SetBackground( this );

        if ( item->ControlType() != EAknCtToolbarExtension )
            {
            item->Control()->SetObserver( this );
            }
        }
    else
        {
        CleanupStack::PopAndDestroy( item );
        item = NULL;
        }
    
    return item;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::CalculateSizeAndPosition
// Calculates size and position of the toolbar.
// -----------------------------------------------------------------------------
//
TRect CAknToolbar::CalculateSizeAndPosition()
    {
    iVisibleItems.Reset();
    iPreviousItem = KSelectedNone;
    if ( iItems.Count() <= 0 )
        {
        return TRect();
        }

    TRect mainPaneRect;
    if ( !( iFlags & KAknToolbarFixed ) )
        {
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane,
                                       mainPaneRect );
        if ( iAvkonAppUi->TouchPane() )
            {
            iAvkonAppUi->TouchPane()->ReduceRect( mainPaneRect );
            }
        }
    else
        {
        TRect appRect; 
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow, 
                                           appRect); 
        if ( !Layout_Meta_Data::IsLandscapeOrientation() )
            {
            iOrientation = EAknOrientationHorizontal; 
            mainPaneRect = RectFromLayout( appRect,
                AknLayoutScalable_Avkon::area_side_right_pane( 6 ) );
            }
        else
            {
            iOrientation = EAknOrientationVertical; 
            mainPaneRect = RectFromLayout( appRect,
                AknLayoutScalable_Avkon::area_side_right_pane( 0 ) );
            }
        }

    TRect toolbarRect;
    TRect gridPaneRect;
    TRect cellPaneRect;

    TBool smallToolbar = iFlags & KAknToolbarSmall; 

    CalculateRects( mainPaneRect, toolbarRect, gridPaneRect, cellPaneRect ); 

    // The position of the toolbar is by default fixed, but it can be changed
    TPoint position;
    TBool flexiblePosition = iFlags & KAknToolbarFlexiblePosition;
    if ( flexiblePosition )
        {
        position = Position();
        }
    else
        {
        position = toolbarRect.iTl;
        }

    TInt minToolbarWidthOrHeight;
    // Maximum possible width of the toolbar with the specified position
    TInt maxToolbarWidthOrHeight;

    if ( iOrientation == EAknOrientationHorizontal )
        {        
        // Width of empty toolbar
        minToolbarWidthOrHeight = toolbarRect.Width() - gridPaneRect.Width();
        // Maximum width for toolbar
        maxToolbarWidthOrHeight = mainPaneRect.Width() - 
                          ( position.iX - mainPaneRect.iTl.iX );
        }
    else
        {
        if ( iFlags & KAknToolbarFixed )
            {
            minToolbarWidthOrHeight = 0; 
            maxToolbarWidthOrHeight = gridPaneRect.Height(); 
            }
        else    
            {
             // Height of empty toolbar
            minToolbarWidthOrHeight = toolbarRect.Height() - gridPaneRect.Height();        
            // Maximum height for toolbar
            maxToolbarWidthOrHeight = mainPaneRect.Height() - 
                          ( position.iY - mainPaneRect.iTl.iY );        
            }
        }
  
    
    TInt gridPaneWidth= 0;
    TInt gridPaneHeight = 0;
    
    TInt maxGridPaneWidthOrHeight = maxToolbarWidthOrHeight - minToolbarWidthOrHeight;
    

    // Layout the component controls in grid pane. Note: Code does not use the
    // actual cells from the layout, because toolbar must be able to contain any
    // kind of control. It assumes that the cells are side by side in grid pane
    // and that grid pane is filled from left to right. Code takes the height of
    // the controls from button pane, but uses the control's own width.
    TRect currentCellPaneRect = cellPaneRect;
    iBgRect = TRect( TPoint( 0,0 ), toolbarRect.Size() );
    if ( iInternalFlags.IsSet( ESwitchForItemsHidden ) 
            && iInternalFlags.IsSet( EItemsHidden ))
        {
        iInternalFlags.Clear( EItemsHidden );
        }
    for ( TInt ii = 0;
          ii < iItems.Count() && 
          ( iOrientation == EAknOrientationHorizontal ? 
                currentCellPaneRect.iBr.iX - gridPaneRect.iTl.iX: 
                currentCellPaneRect.iBr.iY - gridPaneRect.iTl.iY ) 
                <= maxGridPaneWidthOrHeight; ++ii )
        {
        CAknToolbarItem* item = iItems[ii];
        if ( item && item->Control() && !item->IsHidden() && !iInternalFlags.IsSet( EItemsHidden ) )
            {
            switch ( item->ControlType() )
                {
                case EAknCtButton:
                case EAknCtToolbarExtension :

                    {                    
                    TRect controlRect;
                    
                    if ( iFlags & KAknToolbarSmall )
                        {
                        controlRect = currentCellPaneRect; 
                        }
                    else if ( iFlags & KAknToolbarFixed )
                        {
                        controlRect = currentCellPaneRect; 
                        TAknLayoutRect centerLayout;
                        centerLayout.LayoutRect( currentCellPaneRect,
                            AknLayoutScalable_Avkon::cell_sctrl_middle_pane_g2( iOrientation == EAknOrientationHorizontal ).LayoutLine() );
                        TRect graphicsRect = centerLayout.Rect();

                        CAknButton* button = static_cast<CAknButton*>( item->Control() ); 
                        button->SetIconSize( graphicsRect.Size() ); 

                        TMargins8 margins;
                        margins.iTop = currentCellPaneRect.iTl.iY - graphicsRect.iTl.iY;
                        margins.iBottom = graphicsRect.iBr.iY - currentCellPaneRect.iBr.iY;
                        margins.iLeft = currentCellPaneRect.iTl.iX - graphicsRect.iTl.iX;
                        margins.iRight = graphicsRect.iBr.iX - currentCellPaneRect.iBr.iX;
                        button->SetMargins( margins ); 
                        }
                    else    
                        {
                        controlRect = CalculateControlRect( currentCellPaneRect ); 
                        }
                    item->Control()->SetRect( controlRect );
                    
                    if ( iOrientation == EAknOrientationHorizontal )
                        {
                        iBgRect.iTl.iX += controlRect.Width();
                        }
                    else
                        {
                        iBgRect.iTl.iY += controlRect.Height();
                        }
                    break;
                    }
                default:
                    {
                    CCoeControl* control = item->Control();

                    TRect controlRect  = RectFromLayout( currentCellPaneRect,
                       AknLayoutScalable_Avkon::toolbar_button_pane() );
    
                    if ( iOrientation == EAknOrientationHorizontal )
                        {                       
                        control->SetExtent( controlRect.iTl,
                                            TSize( control->Rect().Width(),
                                                   controlRect.Height() ) );

                        currentCellPaneRect.Resize( control->Rect().Width() -
                                                    controlRect.Width(), 0);
                        }
                    else
                        {
                        control->SetExtent( controlRect.iTl,
                                            TSize( controlRect.Width(),
                                                   control->Rect().Height() ) );

                        currentCellPaneRect.Resize( 0, control->Rect().Height() -
                                                       controlRect.Height() );
                        }
                    break;
                    }
                }
            TRect highlightRect; 
            if ( smallToolbar )
                {
                highlightRect = currentCellPaneRect; 
                }
            else if ( iOrientation == EAknOrientationHorizontal )
                {
                highlightRect = RectFromLayout( currentCellPaneRect,
                    AknLayoutScalable_Avkon::grid_highlight_pane_cp2(0) );
                }
            else 
                {
                highlightRect = RectFromLayout( currentCellPaneRect, 
                    AknLayoutScalable_Avkon::grid_highlight_pane_cp2(3) );
                }
    
            item->SetHighlightRect( highlightRect );   


#ifdef RD_SCALABLE_UI_V2
            // Only buttons are shown with focusable toolbar or small toolbar.
            if ( ( IsNonFocusing() && !smallToolbar ) || 
                item->ControlType() == EAknCtButton || item->ControlType() == EAknCtToolbarExtension  )
#else
            if ( item->ControlType() == EAknCtButton || item->ControlType() == EAknCtToolbarExtension  )
#endif
                {
                if ( iOrientation == EAknOrientationHorizontal && 
                    gridPaneWidth + currentCellPaneRect.Width() <= 
                    maxGridPaneWidthOrHeight )
                    {
                    iVisibleItems.Append( item );
                    gridPaneWidth += currentCellPaneRect.Width();
                    }
                    
                else if ( iOrientation == EAknOrientationVertical &&
                    gridPaneHeight + currentCellPaneRect.Height() <= 
                    maxGridPaneWidthOrHeight )
                    {
                    iVisibleItems.Append( item );
                    gridPaneHeight += currentCellPaneRect.Height();
                    gridPaneWidth = item->Control()->Rect().Width();
                    }

                // Set up next cell pane rect
                if ( iOrientation == EAknOrientationVertical )
                    {
                    currentCellPaneRect.SetRect( TPoint( currentCellPaneRect.iTl.iX,
                                                  currentCellPaneRect.iBr.iY ),
                                                 cellPaneRect.Size() );
                    }
                else
                    {
                    currentCellPaneRect.SetRect( TPoint( currentCellPaneRect.iBr.iX,
                                                  currentCellPaneRect.iTl.iY ),
                                                 cellPaneRect.Size() );
                    }
                }
            else
                {
                if ( item->IsSelected() )
                    {
                    TRAP_IGNORE( item->SetIsSelectedL( EFalse ) );
                    }

                currentCellPaneRect.SetRect( TPoint( currentCellPaneRect.iTl.iX,
                                             currentCellPaneRect.iTl.iY ),
                                             cellPaneRect.Size() );
                }
            }
        }

    if ( TooFewItemsVisible() ) 
        {
        return TRect( position, TSize(0,0) ); 
        }

    
    TRect rect;
    
    if ( iFlags & KAknToolbarFixed )
            {
            rect = toolbarRect; 
            return rect; 
            }
            
    if ( iOrientation == EAknOrientationHorizontal )
        {
        TInt mid = mainPaneRect.Width() / 2;
        if ( !flexiblePosition ) 
            {
            position.iX = mainPaneRect.iTl.iX + 
                ( mid - ( minToolbarWidthOrHeight + gridPaneWidth ) / 2 ); 
            if ( position.iX < toolbarRect.iTl.iX )
                {
                position.iX = toolbarRect.iTl.iX; 
                }
            }
        rect = TRect( position, TSize( minToolbarWidthOrHeight + gridPaneWidth,
                                   toolbarRect.Height() ) );
        }    
    else 
        {
        TInt mid = mainPaneRect.Height() / 2;
        if ( !flexiblePosition ) 
            {
            position.iY = mainPaneRect.iTl.iY + 
                ( mid - ( minToolbarWidthOrHeight + gridPaneHeight ) / 2 ); 
            if ( position.iY < toolbarRect.iTl.iY )
                {
                position.iY = toolbarRect.iTl.iY; 
                }
            }
        rect = TRect( position, TSize( toolbarRect.Width(), 
                        minToolbarWidthOrHeight + gridPaneHeight ) );
        }
           
    return rect;
    }



// -----------------------------------------------------------------------------
// CAknToolbar::CalculateRects
// Calculates rects for toolbar.
// -----------------------------------------------------------------------------
//
void CAknToolbar::CalculateRects( TRect& aMainPaneRect, TRect& aToolbarRect, 
    TRect& aGridPaneRect, TRect& aCellPaneRect )
    {
    TBool smallToolbar = iFlags & KAknToolbarSmall; 

    TInt variety;
    
    if ( smallToolbar )
        {
        if ( iOrientation == EAknOrientationHorizontal )
            {        
            variety = 1;    
            aToolbarRect = RectFromLayout( aMainPaneRect,
                AknLayoutScalable_Avkon::popup_toolbar_trans_pane( variety ) );

            aGridPaneRect = RectFromLayout( TRect( TPoint(), aToolbarRect.Size() ),
                AknLayoutScalable_Avkon::grid_tb_trans_pane( variety ) );
            
            aCellPaneRect = RectFromLayout( aGridPaneRect,     
                AknLayoutScalable_Avkon::cell_toolbar_trans_pane( 0, variety ) );
            }
        else
            {        
            aToolbarRect = RectFromLayout( aMainPaneRect,
                AknLayoutScalable_Avkon::popup_toolbar_trans_pane() );

            aGridPaneRect = RectFromLayout( TRect( TPoint(), aToolbarRect.Size() ),
                AknLayoutScalable_Avkon::grid_tb_trans_pane() );
            
            aCellPaneRect = RectFromLayout( aGridPaneRect,     
                AknLayoutScalable_Avkon::cell_toolbar_trans_pane( 0 ) );
        
            }
        }
    else if ( iFlags & KAknToolbarFixed )
        {
        if ( iOrientation == EAknOrientationHorizontal )
            {        
            variety = 4;    
            aToolbarRect = RectFromLayout( aMainPaneRect,
                AknLayoutScalable_Avkon::grid_sctrl_middle_pane( 1 ) );

            aGridPaneRect = TRect( TPoint(), aToolbarRect.Size() ); 
            
            aCellPaneRect = RectFromLayout( aGridPaneRect,     
                AknLayoutScalable_Avkon::cell_sctrl_middle_pane( 1, 0, 0 ) );
            }
        else
            {
            aToolbarRect = RectFromLayout( aMainPaneRect,
                AknLayoutScalable_Avkon::grid_sctrl_middle_pane( 0 ) );

            aGridPaneRect = TRect( TPoint(), aToolbarRect.Size() ); 


            aCellPaneRect = RectFromLayout( aGridPaneRect,     
                AknLayoutScalable_Avkon::cell_sctrl_middle_pane( 0, 0, 0 ) );
            }
        }
    else    
        {
        if ( iOrientation == EAknOrientationHorizontal )
            {        
            variety = 4;    
            aToolbarRect = RectFromLayout( aMainPaneRect,
                AknLayoutScalable_Avkon::popup_toolbar_window( variety ) );

            aGridPaneRect = RectFromLayout( TRect( TPoint(), aToolbarRect.Size() ),
                AknLayoutScalable_Avkon::grid_toobar_pane() );
            
            aCellPaneRect = RectFromLayout( aGridPaneRect,     
                AknLayoutScalable_Avkon::cell_toolbar_pane( 0 ) );
            }
        else
            {        
            aToolbarRect = RectFromLayout( aMainPaneRect,
                AknLayoutScalable_Avkon::popup_toolbar_window( 6 ) );

            aGridPaneRect = RectFromLayout( TRect( TPoint(), aToolbarRect.Size() ),
                AknLayoutScalable_Avkon::grid_toobar_pane( 6 ) );
            
            aCellPaneRect = RectFromLayout( aGridPaneRect,     
                AknLayoutScalable_Avkon::cell_toolbar_pane( 0, 1, 0 ) );
        
            }
        }
   }

// -----------------------------------------------------------------------------
// CAknToolbar::CalculateControlRect
// Calculates control rect for toolbar item.
// -----------------------------------------------------------------------------
//
TRect CAknToolbar::CalculateControlRect( TRect& aCurrentCellPaneRect )
    {
    TRect controlRect;     
    if ( iOrientation == EAknOrientationHorizontal )
        {
        controlRect = RectFromLayout( aCurrentCellPaneRect,
            AknLayoutScalable_Avkon::toolbar_button_pane() );                        
        }                    
    else
        {
        controlRect = RectFromLayout( aCurrentCellPaneRect,
            AknLayoutScalable_Avkon::toolbar_button_pane( 2 ) );                        
        }
    return controlRect; 
    }

// -----------------------------------------------------------------------------
// CAknToolbar::CheckNumberOfVisibleItems
// Checks number of visible items and deletes or created CBA if needed
// -----------------------------------------------------------------------------
//
TBool CAknToolbar::TooFewItemsVisible()
    {
    if( !iVisibleItems.Count() )
        {
        if ( iFlags & KAknToolbarFixed )
            {
            return EFalse;
            }
        else
            {
            //if the number of toolbar items is 0 then toolbar CBA is deleted
            if ( iToolbarCba )
                {
                delete iToolbarCba;
                iToolbarCba = NULL;
                }
        
            DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityNeverAtFront );

            iInternalFlags.Set( ENoItemsVisible );
            return ETrue;     
            }
        }
    else if ( iInternalFlags.IsSet( ENoItemsVisible ) )   
        {
        iInternalFlags.Clear( ENoItemsVisible );

        TBool withoutCba( iFlags & KAknToolbarWithoutCba );                    

        DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityNormal );

        // toolbar CBA is created here because it had been deleted due to 
        // too few items in toolbar
        if ( !withoutCba && !IsNonFocusing() )
            {
            TRAP_IGNORE( iToolbarCba = CEikButtonGroupContainer::NewL( 
                CEikButtonGroupContainer::ECba, 
                CEikButtonGroupContainer::EHorizontal,
                this, iSoftkeyResource ) );

            if ( iToolbarCba->ButtonGroup() )
                {
                static_cast<CEikCba*>( iToolbarCba->ButtonGroup() )->
                    SetSkinBackgroundId( KAknsIIDQsnBgAreaControlPopup );
                }
                TRAP_IGNORE( InitFocusedItemL( ETrue ) );
            
            }
        }
    return EFalse; 
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ToolbarItemByControl
// Returns toolbar item object for the specified control.
// -----------------------------------------------------------------------------
//
CAknToolbarItem* CAknToolbar::ToolbarItemByControl( const CCoeControl* aControl ) const 
    {
    if ( aControl )
        {
        for ( TInt ii = 0; ii < iItems.Count(); ii++ ) 
            {
            CAknToolbarItem* item = iItems[ii];
            if ( item && item->Control() && item->Control() == aControl )
                {
                return item;
                }
            }
        }
    return NULL;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ToolbarItemById
// Returns toolbar item object for the specified command ID
// -----------------------------------------------------------------------------
//
CAknToolbarItem* CAknToolbar::ToolbarItemById( const TInt aId ) const 
    {
    for ( TInt ii = 0; ii < iItems.Count(); ii++ )
        {
        CAknToolbarItem* item = iItems[ii];
        if ( item && item->CommandId() == aId )
            {
            return item;
            }
        }
    return NULL;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ToolbarItemIndexById
// Returns the index of the toolbar item inside of the iItems array.
// -----------------------------------------------------------------------------
//
TInt CAknToolbar::ToolbarItemIndexById( const TInt aId ) const 
    {
    for ( TInt ii = 0; ii < iItems.Count(); ii++ )
        {
        CAknToolbarItem* item = iItems[ii];
        if ( item && item->CommandId() == aId )
            {
            return ii;
            }
        }
    return KErrNotFound;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ToolbarItemIndexByControl
// Returns toolbar item index for the specified control or KErrNotFound.
// -----------------------------------------------------------------------------
//
TInt CAknToolbar::ToolbarItemIndexByControl( const CCoeControl* aControl ) const 
    {
    if ( aControl )
        {
        for ( TInt ii = 0; ii < iItems.Count(); ii++ ) 
            {
            CAknToolbarItem* item = iItems[ii];
            if ( item && item->Control() == aControl )
                {
                return ii;
                }
            }
        }
    return KErrNotFound;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ToolbarVisibleIndexById
// Returns the index of the toolbar item inside of the iVisibleItems array.
// -----------------------------------------------------------------------------
//
TInt CAknToolbar::ToolbarVisibleIndexById( const TInt aId ) const 
    {
    for ( TInt ii = 0; ii < iVisibleItems.Count(); ii++ )
        {
        CAknToolbarItem* item = iVisibleItems[ii];
        if ( item && item->CommandId() == aId )
            {
            return ii;
            }
        }
    return KErrNotFound;
    }



// -----------------------------------------------------------------------------
// CAknToolbar::ToolbarVisibleIndexByControl
// Returns visible toolbar item index for the specified control or KErrNotFound.
// -----------------------------------------------------------------------------
//
TInt CAknToolbar::ToolbarVisibleIndexByControl( const CCoeControl* aControl ) const 
    {
    if ( aControl )
        {
        for ( TInt ii = 0; ii < iVisibleItems.Count(); ii++ ) 
            {
            CAknToolbarItem* item = iVisibleItems[ii];
            if ( item && item->Control() == aControl )
                {
                return ii;
                }
            }
        }
    return KErrNotFound;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SlideToolbar
// Draws the toolbar with sliding effect.
// -----------------------------------------------------------------------------
//    
void CAknToolbar::SlideToolbar( const TPoint& aEndPos )
    {          
    // Currently supports sliding only from left to right. 
    // If some other cases are needed implementation should be changed then.   

    if ( iOrientation == EAknOrientationVertical )
        {
        return; 
        }
    
    TPoint start = Position();
    iStep = (  aEndPos.iX - start.iX ) / 10;

    iEndPos = aEndPos.iX; 

    SlideWithIdle(); 

    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetRightCbaText
// Changes CBA if no item is focused.
// -----------------------------------------------------------------------------
//  
void CAknToolbar::SetRightCbaTextL()
    {
    if ( !iToolbarCba )
        {
        return;
        }
    
    if ( IsFocused() && iFocusedItem == KFocusedNone )
        {
        iToolbarCba->MakeCommandVisibleByPosition( 
            CEikButtonGroupContainer::ELeftSoftkeyPosition, EFalse ); 
        iToolbarCba->MakeCommandVisibleByPosition( 
            CEikButtonGroupContainer::EMiddleSoftkeyPosition, EFalse ); 
        iToolbarCba->DrawDeferred();
        }
    }
// -----------------------------------------------------------------------------
// CAknToolbar::GetNextSelectableItemIndex
// Returns next not dimmed and not hidden control index.
// -----------------------------------------------------------------------------
//    
TInt CAknToolbar::GetNextSelectableItemIndex( TInt aStartIndex, TBool aMoveForward )
    {
    TInt index( aStartIndex );
    
    if ( IsNonFocusing() )
        {
        return KFocusedNone; 
        }
    
    __ASSERT_ALWAYS( iVisibleItems.Count(), Panic( EEikPanicInvalidLength ) ); 
    
    CAknButton* button = NULL;  
    // we will do it till we don't get valid non-dimmed item or till we don't
    // make the whole round ( all items are dimmed )
    do 
        {
        button = NULL; 
        if ( aMoveForward && index >= iVisibleItems.Count() - 1 )
            {
            index = 0;
            }
        else if ( !aMoveForward && index == 0 )
            {
            index = iVisibleItems.Count() - 1;
            }
        else
            {
            if ( aMoveForward )
                {
                ++index;
                }
            else 
                {
                --index;
                }
            }
        button = static_cast<CAknButton*>( iVisibleItems[index]->Control() );

        } while ( ( !button || button->IsDimmed() ) && aStartIndex != index );
                      
    // no non-dimmed items
    if ( aStartIndex == index )
        {
        return KFocusedNone;
        }
    
    return index;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::MoveHighlightL
// Moves highlight from one item to another
// -----------------------------------------------------------------------------
//    
void CAknToolbar::MoveHighlightL( TInt aItemIndex, 
                                   const TBool aDrawNow,
                                   const TBool aMoveForward,
                                   const TBool aPrepareControl )
    {
    if ( IsNonFocusing() || !iVisibleItems.Count() )
        {
        // Item cannot get focus, when toolbar is non-focusing
        aItemIndex = KFocusedNone;
        }
    
    if ( aItemIndex >= iVisibleItems.Count() )
        {
        aItemIndex = iVisibleItems.Count() - 1;
        }
    else if ( aItemIndex < 0 && aItemIndex != KFocusedNone )
        {
        aItemIndex = 0;
        }
        
    if ( aItemIndex == iFocusedItem )
        {
        if ( iFocusedItem >= 0 && iFocusedItem < iVisibleItems.Count() )
            {
            // Set item focused again so that tooltip is shown again. 
            iVisibleItems[iFocusedItem]->SetFocusL( ETrue, aPrepareControl,
                aDrawNow ? EDrawNow : ENoDrawNow, this );
            }
        return;
        }
    
    TInt oldFocused = iFocusedItem;
    if ( oldFocused < 0 || oldFocused >= iVisibleItems.Count() )
        {
        oldFocused = KFocusedNone;
        }
    iFocusedItem = aItemIndex;
    CAknToolbarItem* item = NULL;
    CAknButton* button = NULL; 
    
    if ( iFocusedItem != KFocusedNone )  
        {
        // There are only buttons in a focusable toolbar
        item = iVisibleItems[iFocusedItem];
        button = static_cast<CAknButton*>( item->Control() ); 

        if ( button && button->IsDimmed() )
            {
            // we should skip dimmed controls
            TInt index = GetNextSelectableItemIndex( iFocusedItem, 
                aMoveForward );
            if ( index == KFocusedNone )
                {
                // all items are dimmed
                iFocusedItem = KFocusedNone;
                SetRightCbaTextL();
                // Draw last hightlighted item again to remove highlight
                if ( oldFocused >= 0 && oldFocused < iVisibleItems.Count() )
                    {
                    CAknToolbarItem* oldItem = iVisibleItems[oldFocused]; 
                    DrawNow( oldItem->HighlightRect() );     
                    }
                return;
                }
            // there is only one non dimmed item
            else if ( index == oldFocused )
                {
                iFocusedItem = oldFocused; 
                return;
                }
            else
                {
                iFocusedItem = index;
                }
                
            __ASSERT_DEBUG( ( index >= 0 && index < iVisibleItems.Count() ), 
                Panic( EEikPanicInvalidIndex ) );
            item = iVisibleItems[index];
            }
           
        // set this item focused
        item->SetFocusL( ETrue, aPrepareControl,
                         aDrawNow ? EDrawNow : ENoDrawNow, this );
        item->Control()->DrawNow( item->HighlightRect() ); 
        }
    
    if ( oldFocused != KFocusedNone )
        {
        item = iVisibleItems[oldFocused];
        if ( item && item->Control() )
            {
            SelectItemL( oldFocused, EFalse );

            // take the focus away
            item->SetFocusL( EFalse, aPrepareControl,
                             aDrawNow ? EDrawNow : ENoDrawNow, this );
            item->Control()->DrawNow( item->HighlightRect() ); 
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::InitFocusedItemL
// Set the focus to the middle or first item. Size and position should be
// calculated already, to avoid iVisibleItems.Count() to be 0.
// -----------------------------------------------------------------------------
//
void CAknToolbar::InitFocusedItemL( const TBool aDrawNow )
    {
    __ASSERT_ALWAYS( iVisibleItems.Count(), Panic( EEikPanicInvalidLength ) );
    
    if ( iInitialFocusedItem >= 0 && 
         iInitialFocusedItem < iVisibleItems.Count() )
        {
        MoveHighlightL( iInitialFocusedItem, aDrawNow );
        return;
        }
    
    if ( iFlags & KAknToolbarMiddleItemFocused && iVisibleItems.Count() != 1 )
        {
        // focus is in the middle
        if ( iVisibleItems.Count() % 2 )
            {
            // if the number of visible items is odd number
            MoveHighlightL( iVisibleItems.Count() / 2, aDrawNow );
            }
        else
            {
            // if the number of visible items is even number
            MoveHighlightL( iVisibleItems.Count() / 2 - 1, aDrawNow );
            }
        }
    else // default behaviour
        {
        MoveHighlightL( 0, aDrawNow );
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetShown
// Sets the flag on or off.
// -----------------------------------------------------------------------------
//
void CAknToolbar::SetShown( const TBool aShown )
    {
    if ( aShown )
        {
        iInternalFlags.Set( EShown );
        }
    else
        {
        iInternalFlags.Clear( EShown );
        }

    if ( !( iFlags & KAknToolbarWithoutCba ) && !IsNonFocusing() &&
        !( iFlags & KAknToolbarSmall ) )
        {
        FadeBehindPopup( aShown ); 
        }
    CCoeControl::MakeVisible( aShown );
    // Need to call here, because ComponentControl only returns
    // visible items
    UpdateControlVisibility();
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SelectItemL
// -----------------------------------------------------------------------------
//
void CAknToolbar::SelectItemL( const TInt aIndex, const TBool aSelect )
    {
    if ( aSelect )
        {
        if ( aIndex != iSelectedItem )
            {
            if ( iSelectedItem != KSelectedNone &&
                 iSelectedItem < iVisibleItems.Count() )
                {
                iVisibleItems[iSelectedItem]->SetIsSelectedL( EFalse );
                }

            if ( aIndex != KSelectedNone && aIndex < iVisibleItems.Count() )
                {
                if ( iVisibleItems[aIndex]->SetIsSelectedL( ETrue ) )
                    {
                    iSelectedItem = aIndex;
                    }
                else
                    {
                    iSelectedItem = KSelectedNone;
                    }
                }
            else
                {
                iSelectedItem = KSelectedNone;
                }
            }
        }
    else
        {
        if ( aIndex == iSelectedItem )
            {
            if ( aIndex != KSelectedNone && aIndex < iVisibleItems.Count() )
                {
                iVisibleItems[aIndex]->SetIsSelectedL( EFalse );
                }
            iSelectedItem = KSelectedNone;
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::RectFromLayout
// -----------------------------------------------------------------------------
//
TRect CAknToolbar::RectFromLayout( const TRect& aParent,
        const TAknWindowComponentLayout& aComponentLayout ) const
    {
    TAknWindowLineLayout lineLayout = aComponentLayout.LayoutLine();
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParent, lineLayout );
    return layoutRect.Rect();
    }

// -----------------------------------------------------------------------------
// CAknToolbar::WaitForScreenSwitch. This is called by CIdle when it returns. 
// Toolbar is shown again with new screen capture. 
// this function is deserted for NGA's removing BitmapDevice
// -----------------------------------------------------------------------------
//
TInt CAknToolbar::WaitForScreenSwitch(TAny* /*aThis*/)
    {
    return KErrNone; 
    }

// -----------------------------------------------------------------------------
// CAknToolbar::HideToolbarForBackgroundUpdate
// This hides toolbar so that it is possible to get a screen capture. 
// -----------------------------------------------------------------------------
//
void CAknToolbar::HideToolbarForBackgroundUpdate()
    {
	  return;
    }

// -----------------------------------------------------------------------------
// CAknToolbar::UpdateTooltipPositions
// Updates tooltips positions
// -----------------------------------------------------------------------------
//
void CAknToolbar::UpdateControlPositions()
    {
    for ( TInt ii = 0; ii < iVisibleItems.Count(); ++ii )
        {
        iVisibleItems[ii]->RegisterPosition( Position() );
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ShowViaIdle
// Shows toolbar via CIdle.
// -----------------------------------------------------------------------------
//
void CAknToolbar::ShowViaIdle()
    {
    if ( !iIdle )
        {
        TRAPD( err, iIdle = CIdle::NewL( CActive::EPriorityStandard ) );
        
        if ( err != KErrNone)
            {
            return; 
            }
        }
    
    if ( iIdle->IsActive() )
        {
        iIdle->Cancel();
        }

    if ( iFlags & KAknToolbarFixed )   
        {
        iIdle->SetPriority ( CActive::EPriorityStandard );
        }
    else
        {
        iIdle->SetPriority( CActive::EPriorityIdle );
        }
        
    iInternalFlags.Set( EShown );
    iIdle->Start( TCallBack ( ShowDelayedToolbar, this ) );
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ShowDelayedToolbar
// Callback for delayed window creation.
// -----------------------------------------------------------------------------
//
TInt CAknToolbar::ShowDelayedToolbar( TAny* aThis )
    {
    CAknToolbar* toolbar = static_cast<CAknToolbar*>(aThis);
    if ( !toolbar->iInternalFlags.IsSet( EShowingAgain ) && 
         toolbar->iInternalFlags.IsSet( EShown ) )
        {
        TRAPD(err,toolbar->ShowToolbarL()); 
        if ( err != KErrNone )
            {
            // if we failed then softkeys should be deleted just in case if they 
            // were created before leave
            delete toolbar->iToolbarCba;
            toolbar->iToolbarCba = NULL;
                
            toolbar->SetFocus( EFalse );
            CEikonEnv::Static()->EikAppUi()->UpdateStackedControlFlags( toolbar, 
                ~0, ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys );

            }
        }
    else
        {
        toolbar->DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityNormal );
        toolbar->iInternalFlags.Clear( EShowingAgain );
        }
    return KErrNone; 
    }


// -----------------------------------------------------------------------------
// CAknToolbar::CheckHitAreas
// Registers buttons to check hit areas in the case of fixed toolbar
// -----------------------------------------------------------------------------
//
void CAknToolbar::CheckHitAreas()
    {
    CAknButton* button = NULL; 

    for ( TInt ii = 0; ii < iItems.Count(); ++ii )
        {
        if ( iItems[ii]->ControlType() == EAknCtButton || 
             iItems[ii]->ControlType() == EAknCtToolbarExtension  )
            {
            button = static_cast<CAknButton*>(iItems[ii]->Control());             
            button->CheckHitArea(); 
            }
       }

    }

// -----------------------------------------------------------------------------
// CAknToolbar::Toolbar Extension
// Return pointer to toolbar extension if available
// -----------------------------------------------------------------------------
//
EXPORT_C CAknToolbarExtension* CAknToolbar::ToolbarExtension() const 
    {
    for ( TInt i = 0; i < iItems.Count(); ++i )
        {
        if ( iItems[i]->ControlType() == EAknCtToolbarExtension )
            {
            return static_cast<CAknToolbarExtension*>( iItems[i]->Control() ); 
            }
        }
    return NULL;     
    }

// -----------------------------------------------------------------------------
// Calls dyninittoolbarL about extension opening. 
// -----------------------------------------------------------------------------
//
void CAknToolbar::DynInitExtensionL( CCoeControl* aControl )  
    {
    TInt commandId = ToolbarItemByControl( aControl )->CommandId(); 
    if ( iToolbarObserver )
        {
        iToolbarObserver->DynInitToolbarL( commandId, this );
        }
    }


// -----------------------------------------------------------------------------
// CAknToolbar::CheckFixedToolbarButtonsL
// Counts button components of fixed toolbar and adds button(s) if needed
// -----------------------------------------------------------------------------
//    
void CAknToolbar::CheckFixedToolbarButtonsL()
    {
    if ( iFlags & KAknToolbarFixed )
        {
        // Count button components
        TInt count ( 0 );
        for ( TInt ii = 0; ii < iItems.Count(); ++ii )
            {
            if ( iItems[ii]->ControlType() == EAknCtButton || 
                iItems[ii]->ControlType() == EAknCtToolbarExtension )
                {
                ++count;
                }
           }
           
        // Add missing button components
        for ( TInt kk = count; kk < KFixedtoolbarButtons; ++kk )
            {
            CAknButton* button = CAknButton::NewLC( NULL, NULL, NULL, NULL, 
                KNullDesC, KNullDesC, 0, 0 );
            button->SetDimmed( ETrue );
            AddItemL( button, EAknCtButton, -1, 0 );
            CleanupStack::Pop( button );
            AdjustButton( *button );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::DrawFixedBackgroundL
// Draws background of fixed toolbar
// -----------------------------------------------------------------------------
//    
void CAknToolbar::DrawFixedBackgroundL( CWindowGc& aGc, 
                                        const CCoeControl& aControl, 
                                        const TRect& aRect ) const
    {
    // What happens here is:
    // 1. Check if we are in the idle state and a wallpaper is in use.
    // 2. If wallpaper is not used then just blit a correct piece of the skin
    //    background to the screen and return.
    // 3. If we're in idle and wallpaper is used then draw wallpaper to a
    //    temporary bitmap.
    // 4. Skin background with additional mask (either qgn_graf_bg_lsc_bottom_mask_icon 
    //    or qgn_graf_bg_prt_bottom_mask_icon) is blitted on top of the wallpaper. 
    //    Skin background's original mask is ignored. Note that these additional
    //    masks are larger than the actual fixed toolbar so only a portion of them
    //    should be used.
    //    Blit the generated background bitmap to the screen.
    TBool wallpaperInUse = EFalse;
    TInt itemsInCleanupStack = 0;
    
    if ( iInternalFlags.IsSet( EInIdle ) )
        {
        CRepository* repository = CRepository::NewL( KCRUidPersonalisation );
        repository->Get( KPslnWallpaperType, wallpaperInUse );
        delete repository;
        }

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
    // background context shared by both wallpaper and skin background
    TAknsItemID itemID = iInternalFlags.IsSet( EInIdle ) ? KAknsIIDQsnBgScreenIdle : KAknsIIDQsnBgScreen;
    if ( iBgIID !=  KAknsIIDNone )
    	{
    	itemID = iBgIID;
    	}
    CAknsBasicBackgroundControlContext* context =
        CAknsBasicBackgroundControlContext::NewL(
        itemID,
        iAvkonAppUi->ApplicationRect(),
        EFalse );

    CleanupStack::PushL( context );
    ++itemsInCleanupStack;

    const TDisplayMode displayMode(
        CCoeEnv::Static()->ScreenDevice()->DisplayMode() );
        
    TBool useDithering = EFalse;
    TPoint skinOrigin( aRect.iTl );

    // check if dithering is to be used
    if ( ( displayMode == EColor16MA || displayMode == EColor16MU ) && 
         ( iFlags & KAknToolbarDsaMode ) /*&&
         !bgBmp->IsCompressedInRAM() */)
        {
        useDithering = ETrue;
        }

    // draw skin background to whatever context was chosen (window or bitmap)
    AknsDrawUtils::DrawBackground( skin, 
                                   context, 
                                   this, 
                                   aGc,
                                   skinOrigin, 
                                   TRect( iPosition + aRect.iTl, aControl.Size() ),
                                   KAknsDrawParamDefault );

    if ( wallpaperInUse )
        {
        // Blit wallpaper to the background bitmap.
        context->SetBitmap( KAknsIIDWallpaper );
        AknsDrawUtils::DrawBackground( skin,
                                       context, 
                                       this, 
                                       aGc,
                                       TPoint( 0, 0 ), 
                                       TRect( iPosition + aRect.iTl, aControl.Size() ),
                                       KAknsDrawParamDefault );
            }
    if ( useDithering )
        {
        aGc.SetDrawMode( CGraphicsContext::EDrawModeWriteAlpha );
        aGc.SetBrushColor( TRgb( KToolbarBgColor, KToolBarBgAlpha ) );
        aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        aGc.DrawRect( Rect() );
        }

    CleanupStack::PopAndDestroy( itemsInCleanupStack );
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SlideWithIdle. This is called by CIdle when it returns. 
// Toolbar is drawn again with different coordinates.  
// -----------------------------------------------------------------------------
//
void CAknToolbar::SlideWithIdle()
    {
    TPoint start(iPosition); 

    if ( start.iX < iEndPos )
        {
        start.iX += iStep;
        if ( start.iX >= iEndPos )
            {
            start.iX = iEndPos; // needed if start.iX is greater than iEndPos
            TRAP_IGNORE( InitFocusedItemL( ETrue ) );
            }
        SetPosition( start );
        DrawNow(); 

        if ( !iIdle )
            {
            TRAPD( err, iIdle = CIdle::NewL( CActive::EPriorityIdle ) );
            if ( err != KErrNone)
                {
                return; 
                }
            }
            
        if ( iIdle->IsActive() )
            {
            iIdle->Cancel();
            }
            
        iIdle->Start( TCallBack ( ReadyToSlide, this ) );
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::ReadyToSlide. This is called by CIdle when it returns. 
// Toolbar is drawn again with different coordinates.  
// -----------------------------------------------------------------------------
//
TInt CAknToolbar::ReadyToSlide( TAny* aThis )
    {
    CAknToolbar* toolbar = static_cast<CAknToolbar*>(aThis);
    toolbar->SlideWithIdle();
    return KErrNone; 
    }

// -----------------------------------------------------------------------------
// CAknToolbar::AdjustButton
// Adjusts button's properties depending on the toolbar's features.  
// -----------------------------------------------------------------------------
//
void CAknToolbar::AdjustButton( CAknButton& aButton )
    {
    // tooltip properties
    aButton.SetHelpNoteTimeouts( KToolbarButtonBeforeTimeout, 
        KToolbarButtonInViewTimeout );
        
    aButton.HideTooltipWhenAppFaded( EFalse ); 
    
    // toolbar buttons don't have margins
    if ( aButton.UsesDefaultMargins() )
        {
        TMargins8 margins;
        margins.SetAllValuesTo( 0 );
        aButton.SetMargins( margins );
        }
        
    // remove frame graphics if the current toolbar mode doesn't support them
    if ( ( iFlags & KAknToolbarSmall ) ||
         ( iFlags & KAknToolbarNoBackground ) )
        { 
        aButton.SetButtonFlags( aButton.ButtonFlags() | KAknButtonNoFrame ); 
        }

    // force frame graphics for fixed toolbar button
    if ( iFlags & KAknToolbarFixed )
        {
        aButton.UseMaskedDraw( ETrue );
        aButton.SetFrameAndCenterIds( KAknsIIDQgnFrSctrlButton,
                                      KAknsIIDQgnFrSctrlButtonCenter,
                                      KAknsIIDQgnFrSctrlButtonPressed,
                                      KAknsIIDQgnFrSctrlButtonCenterPressed,
                                      KAknsIIDQgnFrSctrlButton,
                                      KAknsIIDQgnFrSctrlButtonCenter,
                                      KAknsIIDQgnFrSctrlButtonPressed,
                                      KAknsIIDQgnFrSctrlButtonCenterPressed,
                                      KAknsIIDQgnFrSctrlButton,
                                      KAknsIIDQgnFrSctrlButtonCenter );
                                      
        // Touch area tuning - in fixed toolbar only such events
        // that hit to touch rect
        aButton.CheckHitArea(); 
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::AdjustAllButtons
// Adjusts all buttons' properties depending on the toolbar's features.  
// -----------------------------------------------------------------------------
//
void CAknToolbar::AdjustAllButtons()
    {
    for ( TInt i = 0; i < iItems.Count(); ++i )
        {
        if ( iItems[i]->ControlType() == EAknCtButton || 
             iItems[i]->ControlType() == EAknCtToolbarExtension  )
            {
            AdjustButton( *static_cast<CAknButton*>(iItems[i]->Control() ) );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetOrdinalPositions
// Adjusts toolbar's and overlying dialog's window positions so that dialog is
// displayed on top of the toolbar.  
// -----------------------------------------------------------------------------
//
void CAknToolbar::SetOrdinalPositions() const
    {
    TBool isDisplayed = CEikonEnv::Static()->EikAppUi()->IsDisplayingMenuOrDialog(); 
    CCoeControl* ctrl = NULL;  
    RDrawableWindow* ctrlWindow = NULL;
    RDrawableWindow* childWindow = NULL;

    if ( !isDisplayed )
        {
        CEikMenuBar* menuBar = NULL; 
        TVwsViewId viewId;
        TInt err = iAvkonViewAppUi->GetActiveViewId( viewId );
        if ( err == KErrNone && viewId.iAppUid != viewId.iViewUid )
            {
            // Application has active view
            CAknView* view = iAvkonViewAppUi->View( viewId.iViewUid );
            if ( view )
                {
                ctrl = menuBar = view->CAknView::MenuBar();
                }
            }
        else
            {
            ctrl = menuBar = iEikonEnv->AppUiFactory()->MenuBar();
            }

        if ( menuBar )
            {
            isDisplayed = menuBar->IsDisplayed();
            }
        if ( isDisplayed )
            {
            // if menuBar returns ETrue from IsDisplayed, it means it has a menu 
            // pane
            ctrlWindow = menuBar->MenuPane()->DrawableWindow();
            
            if ( menuBar->MenuPane()->CascadeMenuPane() )
                {
                // submenu has a submenu
                if ( menuBar->MenuPane()->CascadeMenuPane()->CascadeMenuPane() )
                    {
                    ctrlWindow = menuBar->MenuPane()->CascadeMenuPane()->DrawableWindow();
                    childWindow =                     
                        menuBar->MenuPane()->CascadeMenuPane()->CascadeMenuPane()->DrawableWindow();
                    }
                else
                    {
                    childWindow = 
                        menuBar->MenuPane()->CascadeMenuPane()->DrawableWindow();
                    }
                }
            }
        }
    else
        {
        ctrl = CCoeEnv::Static()->AppUi()->TopFocusedControl(); 
        
        if ( ctrl )
            {
            CEikDialog* dialog = ctrl->MopGetObject( dialog );
            
            if ( dialog )
                {
                if ( dialog->DrawableWindow() )
                    {
                    TInt flag = dialog->DialogFlags();
                    
                    if( !( flag & EEikDialogFlagFillScreen ) && 
                        !( flag & EEikDialogFlagFillAppClientRect ) )
                        {
                        ctrlWindow = dialog->DrawableWindow();
                        }
                    }
                }
            else
                {
                CEikMenuBar* ctrlMenu = ctrl->MopGetObject( ctrlMenu );
            
                if ( ctrlMenu && ctrlMenu->IsDisplayed() )
                    {
                    ctrlWindow = ctrlMenu->MenuPane()->DrawableWindow();
                    ctrl = ctrlMenu;
                    if ( ctrlMenu->MenuPane()->CascadeMenuPane() )
                        {
                        childWindow = ctrlMenu->MenuPane()->CascadeMenuPane()->DrawableWindow();
                        }
                    }
                }
            }
        }
    // Menupane or dialog most probably has softkeys so we need to push
    // the control first and then softkeys so that a possible pointer
    // capture still works.
    if ( ctrlWindow )
        {
        CEikCba* cba = ctrl->MopGetObject( cba );
        
        TBool ctrlFaded = ctrlWindow->IsFaded();
        TBool childFaded = EFalse;
        TBool cbaFaded = EFalse;

        if ( childWindow ) 
            {
            childFaded = childWindow->IsFaded();
            }
        if ( cba && cba->DrawableWindow() ) 
            {
            cbaFaded = cba->DrawableWindow()->IsFaded();
            }

        if ( !ctrlFaded )
            {
            ctrlWindow->SetOrdinalPosition( 0 );            
            }
        
        // Set possible child in front of parent
        if ( childWindow && !childFaded )
            {
            childWindow->SetOrdinalPosition( 0 );    
            }
       
        if ( cba && cba->DrawableWindow()&& !cbaFaded )
            {
            cba->DrawableWindow()->SetOrdinalPosition( 0 );
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknToolbar::HideItemsAndDrawOnlyBackground
// Hides/Unhides toolbar items temporarily. When called with ETrue toolbar draws
// just background in landscape and is hidden in portrait. Calling with EFalse
// returns the situation to normal. 
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::HideItemsAndDrawOnlyBackground( TBool aHide ) 
    {
    __ASSERT_DEBUG( ( iFlags & KAknToolbarFixed ), User::Invariant() );

    if ( aHide )
        {
        if ( iFlags & KAknToolbarDefault && !( iInternalFlags.IsSet( EItemsHidden ) ) )
            {
            iInternalFlags.Set( EDefaultToolbar );
            }
        iInternalFlags.Set( EItemsHidden ); 
        iFlags |= KAknToolbarDefault; 
        HandleResourceChange( KEikDynamicLayoutVariantSwitch ); 
        UpdateControlVisibility();
        }
    else
        {
        if ( !( iInternalFlags.IsSet( EItemsHidden ) ) && CountComponentControls() > 0  )
    		{
    		return;
    		}        
        TInt messageType( KEikDynamicLayoutVariantSwitch );
        //defualt property should not be given up
        if ( !iInternalFlags.IsSet( EDefaultToolbar ) ) 
            {
            iFlags &= ~KAknToolbarDefault;            
            }  
        
        if ( !Layout_Meta_Data::IsLandscapeOrientation() && iInternalFlags.IsSet( EDefaultToolbar ) )
            {
            messageType = KAknToolbarSetHiddenAndDrawBackground; 
            }
        else
            {
            // Clearing this temporarily, it gets setted again from HandleResourceChange
            iInternalFlags.Clear( EShown );            
            }
        iInternalFlags.Set( ESwitchForItemsHidden );
        HandleResourceChange( messageType ); 
        // Clear this after HandleResourceChange so that correct method
        // for toolbar showing is chosen
        if ( iInternalFlags.IsSet( EItemsHidden ) )
            {
            iInternalFlags.Clear( EItemsHidden );
            }
        iInternalFlags.Clear( EItemsHiddenWithPriority ); 
        UpdateControlVisibility();
        iInternalFlags.Clear( ESwitchForItemsHidden );
        iInternalFlags.Clear( EDefaultToolbar );
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbar::HideItemsAndDrawOnlyBackground
// Hides/Unhides toolbar items temporarily. When called with ETrue toolbar draws
// just background with the window priority defined in aPriority. 
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbar::HideItemsAndDrawOnlyBackground( TBool aHide, TInt aPriority ) 
    {
    if ( aHide )
        {
        if ( iInternalFlags.IsSet( EShown ) )
            {
            iInternalFlags.Set( EItemsHiddenWithPriority ); 
            iDrawingPriority = aPriority;
            }
        else if ( aPriority != DrawableWindow()->OrdinalPriority() )
            {
            DrawableWindow()->SetOrdinalPosition( 0, aPriority );
            }
        }
    HideItemsAndDrawOnlyBackground( aHide );
    }

// -----------------------------------------------------------------------------
// CAknToolbar::SetSkinBackgroundId
// Define new fixed toolbar background theme ID.
// -----------------------------------------------------------------------------
// 
EXPORT_C void CAknToolbar::SetSkinBackgroundId( const TAknsItemID& aIID )
	{
	iBgIID = aIID;	
	}

// -----------------------------------------------------------------------------
// CAknToolbar::UpdateControlVisibility
// Other details are commented in header
// -----------------------------------------------------------------------------
//
void CAknToolbar::UpdateControlVisibility()
    {
    for ( TInt ii = 0; ii < iItems.Count(); ii++ )
        {
        CAknToolbarItem* item = iItems[ii];
        TBool makeVisible = iInternalFlags.IsSet( EShown ) 
                         && ( ToolbarVisibleIndexByControl( item->Control() ) >= 0 );
        item->Control()->MakeVisible( makeVisible ); 
        }
    }
    
// -----------------------------------------------------------------------------
// CAknToolbar::UpdateItemTooltipPosition()
// Update items tooltip position
// -----------------------------------------------------------------------------
//
void CAknToolbar::UpdateItemTooltipPosition()
    {
    //reset position of button tooltip
    TPoint centerPos = static_cast<CEikAppUiFactory*> 
                            ( iEikonEnv->AppUiFactory() )->ClientRect().Center();
    CAknButton::TTooltipPosition tooltipPosition;
    if ( iOrientation == EAknOrientationHorizontal )
        {
        if ( Position().iY > centerPos.iY )
            {
            tooltipPosition = CAknButton::EPositionTop;
            }
        else
            {
            tooltipPosition = CAknButton::EPositionBottom;
            }
        }
    else
        {        
        if ( Position().iX > centerPos.iX )
            {
            tooltipPosition = CAknButton::EPositionLeft;
            }
        else
            {
            tooltipPosition = CAknButton::EPositionRight;
            }
        } 
    for ( TInt ii = 0; ii < iItems.Count(); ++ii )
        {
        // This assumes that every control in touch pane is button
        CAknToolbarItem* item = iItems[ii];
        if ( item->ControlType() == EAknCtButton || 
                item->ControlType() == EAknCtToolbarExtension )
            {
            CAknButton* button = static_cast<CAknButton*>( item->Control() ); 
            button->SetTooltipPosition( tooltipPosition );
            }
        }
   
    }
// End of file
