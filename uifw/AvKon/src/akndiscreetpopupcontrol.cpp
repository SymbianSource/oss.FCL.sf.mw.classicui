/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Discreet popup control
*
*/

#include <aknappui.h>
#include <aknenv.h>
#include <AknPriv.hrh>
#include <aknsoundsystem.h>
#include <AknsUtils.h>
#include <AknTasHook.h>
#include <AknUtils.h>
#include <apgwgnam.h>
#include <bautils.h>
#include <barsread.h>
#include <gulicon.h>
#include <avkon.hrh>
#include "akndiscreetpopupcontrol.h"
#include "akndiscreetpopupdrawer.h"

_LIT( KDiscreetPopupWindowGroupName, "Discreet pop-up" );

const TInt KOpacityChangeSpeed( 18 );
const TInt KAlphaMax( 255 );
const TInt KAlphaMin( 0 );
const TInt KShortTimeout( 1500000 );
const TInt KLongTimeout( 3000000 );
const TInt KShowDelay( 300000 );
const TInt KShowInterval( 50000 );
const TInt KHideDelay( 50000 );
const TInt KHideInterval( 50000 );
const TInt KGlobalShowOrdinalPriority( ECoeWinPriorityAlwaysAtFront * 4 );
const TInt KLocalShowOrdinalPriority( ECoeWinPriorityNormal + 1 );
const TInt KLocalHideOrdinalPosition( -10 );
const TInt KOpacityDismissFactor( 3 );
const TInt KMaxFadeTime( 1000000 );

/**
 * Internal discreet popup control flags.
 */
enum TAknDiscreetPopupControlFlags
    {
    EPressedDown,     // Pointer down is received in popup area
    EDismissed,       // Popup is dismissed (pointer up is received in popup area)
    EGlobal,          // Popup is global
    EFading,          // Popup is closing (fading)
    EDragged          // Pointer is dragged while popup open
    };


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknDiscreetPopupControl* CAknDiscreetPopupControl::NewL( 
    const TBool aGlobal,
    const TDesC& aTitle, 
    const TDesC& aText, 
    CGulIcon* aIcon, 
    const TAknsItemID& aSkinId,
    const TDesC& aBitmapFile,
    const TInt& aBitmapId,
    const TInt& aMaskId,
    const TInt& aFlags, 
    const TInt& aCommand,
    const TInt& aPopupId,
    MEikCommandObserver* aCommandObserver )
    {
    CAknDiscreetPopupControl* self = 
        CAknDiscreetPopupControl::NewLC( aGlobal,
                                         aTitle,
                                         aText,
                                         aIcon,
                                         aSkinId,
                                         aBitmapFile,
                                         aBitmapId,
                                         aMaskId,
                                         aFlags,
                                         aCommand,
                                         aPopupId,
                                         aCommandObserver );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknDiscreetPopupControl* CAknDiscreetPopupControl::NewL(
    const TBool aGlobal,		
    const TInt& aResourceId,
    const TDesC& aResourceFile,
    const TInt& aCommand,
    const TInt& aPopupId,
    MEikCommandObserver* aCommandObserver )
    {
    CAknDiscreetPopupControl* self = 
        CAknDiscreetPopupControl::NewLC( aGlobal, 
                                         aCommand, 
                                         aPopupId, 
                                         aCommandObserver );
                                         
    self->ConstructFromResourceL( aResourceId, aResourceFile );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::NewLC
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupControl* CAknDiscreetPopupControl::NewLC(
    const TBool aGlobal,
    const TDesC& aTitle, 
    const TDesC& aText,
    CGulIcon* aIcon, 
    const TAknsItemID& aSkinId,
    const TDesC& aBitmapFile,
    const TInt& aBitmapId,
    const TInt& aMaskId,
    const TInt& aFlags, 
    const TInt& aCommand,
    const TInt& aPopupId,
    MEikCommandObserver* aCommandObserver )
    {
    CAknDiscreetPopupControl* self = 
        new ( ELeave ) CAknDiscreetPopupControl( aGlobal, 
                                                 aFlags, 
                                                 aCommand,
                                                 aPopupId, 
                                                 aCommandObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    self->ConstructDrawerL( aTitle, 
                            aText, 
                            aIcon,
                            aSkinId,
                            aBitmapFile,
                            aBitmapId,
                            aMaskId );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::NewLC
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupControl* CAknDiscreetPopupControl::NewLC(
    const TBool aGlobal,
    const TInt& aCommand,
    const TInt& aPopupId,
    MEikCommandObserver* aCommandObserver )
    {
    CAknDiscreetPopupControl* self = new ( ELeave ) CAknDiscreetPopupControl(
        aGlobal, 0, aCommand, aPopupId, aCommandObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::~CAknDiscreetPopupControl
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupControl::~CAknDiscreetPopupControl()
    {
    AKNTASHOOK_REMOVE();
    if ( IsVisible() )
        {
        HidePopup();
        }
    if ( iInternalFlags.IsSet( EGlobal ) )
        {
        iWindowGroup.Close();
        }
    delete iTimer;	
    delete iDrawer;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::HandleDiscreetPopupActionL
// ---------------------------------------------------------------------------

EXPORT_C void CAknDiscreetPopupControl::HandleDiscreetPopupActionL(
        const TInt& aType )
    {
    switch ( aType )
        {
        case EAknDiscreetPopupShow:
            {
            ShowPopupL();
            break;
            }
        case EAknDiscreetPopupHide:
            {
            break;
            }
        case EAknDiscreetPopupAnotherLaunched:
            {
            SetPressedDownState( EFalse );
            break;
            }
        default:
            {
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::PopupId
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknDiscreetPopupControl::PopupId()
    {
    return iPopupId;
    }    


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::TimeOut
// ---------------------------------------------------------------------------
//
TInt CAknDiscreetPopupControl::TimeOut( TAny* aObject )
    {
    static_cast<CAknDiscreetPopupControl*>( aObject )->DoTimeOut();
    return 1;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::MakeVisible
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::MakeVisible( TBool aVisible )
    {
    if ( iTimer )
        {
        iTimer->Cancel();
        }
    
    CCoeControl::MakeVisible( aVisible );
 
    if( iInternalFlags.IsSet( EGlobal ) )
        {
        iWindowGroup.SetOrdinalPosition( 0, KGlobalShowOrdinalPriority );
        }
    else
        {
        Window().SetOrdinalPosition( 0, KLocalShowOrdinalPriority );
        }    
        
    if ( aVisible && iTimer )
        {
        iAlpha = 0;
        iInternalFlags.Clear( EFading );
        iInternalFlags.Clear( EDismissed );
        
        iTimer->Start( KShowDelay, 
                       KShowInterval, 
                       TCallBack( TimeOut, this ) );
                             
        iFadeTime.HomeTime(); 
        TTimeIntervalMicroSeconds32 timeout( KShowDelay );
        iFadeTime += timeout;
        }
    UpdateNonFadingStatus();
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::CAknDiscreetPopupControl
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupControl::CAknDiscreetPopupControl( 
    const TBool& aGlobal, 
    const TInt& aFlags,
    const TInt& aCommand,
    const TInt& aPopupId,  
    MEikCommandObserver* aCommandObserver )
    : 
    iFlags( aFlags ),
    iCommand( 0 ),
    iPopupId ( aPopupId ),
    iCommandObserver( NULL ),
    iDrawer( NULL ),
    iFeedBack( MTouchFeedback::Instance() )
    {
    RThread thread;
    
    if ( aGlobal || thread.Name() == EIKAPPUI_SERVER_THREAD_NAME )
        {
        iInternalFlags.Set( EGlobal );
        }
    iInternalFlags.Set( EDismissed );

    // Action allowed only when touch enabled
    if ( AknLayoutUtils::PenEnabled() )
        {
        iCommand = aCommand;
        iCommandObserver = aCommandObserver;
        }
    AKNTASHOOK_ADD( this, "CAknDiscreetPopupControl" );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::ConstructL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::ConstructL()
    {
    if( iInternalFlags.IsSet( EGlobal ) )
        {
        RWsSession& wsSession = iCoeEnv->WsSession();
        iWindowGroup = RWindowGroup( wsSession );
        User::LeaveIfError( iWindowGroup.Construct( 
                                    ( TUint32 ) &iWindowGroup, EFalse ) );
        iWindowGroup.AutoForeground( EFalse );

        CApaWindowGroupName* name = 
                CApaWindowGroupName::NewLC( wsSession, (TUint32) &iWindowGroup );
        name->SetHidden( ETrue );
        name->SetCaptionL( KDiscreetPopupWindowGroupName );
        User::LeaveIfError( name->SetWindowGroupName( iWindowGroup ));
        CleanupStack::PopAndDestroy( name );

        iWindowGroup.SetOrdinalPosition( 0, ECoeWinPriorityNeverAtFront );
        
        // create control's window to own window group
        CreateWindowL( &iWindowGroup );	
        }
    else
        {
        CreateWindowL();
        Window().SetOrdinalPosition( KLocalHideOrdinalPosition );
        }
        
    iTimer = CPeriodic::NewL( 0 );
    
    // try to enable window transparency
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        Window().SetRequiredDisplayMode( EColor16MA );
        if ( Window().SetTransparencyAlphaChannel() == KErrNone )
            {
            Window().SetBackgroundColor( ~0 );
            }
        }

    Window().SetPointerGrab( ETrue );
    EnableDragEvents();
    MakeVisible( EFalse );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::ConstructDrawerL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::ConstructDrawerL( 
    const TDesC& aTitleText, const TDesC& aBodyText, CGulIcon* aIcon,
    const TAknsItemID& aSkinId, const TDesC& aBitmapFile, 
    const TInt& aBitmapId, const TInt& aMaskId )
    {
    if ( !iDrawer )
        {
        iDrawer = CAknDiscreetPopupDrawer::NewL( this, 
                                                 aTitleText, 
                                                 aBodyText, 
                                                 aIcon, 
                                                 aSkinId, 
                                                 aBitmapFile, 
                                                 aBitmapId, 
                                                 aMaskId,
                                                 iCommand != 0 );
        SetRect( iDrawer->LayoutPopup() );
        ActivateL();
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::ConstructFromResourceL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::ConstructFromResourceL( 
    const TInt& aResourceId, const TDesC& aResourceFile )
    {
    // Add resource file if needed
    if ( aResourceFile != KNullDesC )
        {
        TFileName resourceFile;
        resourceFile.Append( aResourceFile );
        BaflUtils::NearestLanguageFile( iEikonEnv->FsSession(), resourceFile );
        iEikonEnv->AddResourceFileL( resourceFile );
        }

    // Construct according to resource id
    if ( aResourceId )
        {
        TResourceReader reader;
        iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
        ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy(); // reader
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::DoTimeOut
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::DoTimeOut()
    {
    if ( iInternalFlags.IsSet( EFading ) && iAlpha <= KAlphaMin )
        {
        // popup has faded completely, exit
        TRAP_IGNORE( RequestExitL() );
        }
    else
        {
        TInt opacityChange = 
            iInternalFlags.IsSet( EFading ) ? -KOpacityChangeSpeed : KOpacityChangeSpeed;
        
        if ( iInternalFlags.IsSet( EPressedDown ) 
             && iInternalFlags.IsSet( EFading ) )
            {
            iAlpha = KAlphaMax;
            opacityChange = 0;
            }
        
        if ( iInternalFlags.IsSet( EDismissed ) )
            {
            opacityChange *= KOpacityDismissFactor;
            }
        iAlpha += opacityChange;
        
        TTime now;     
        now.HomeTime();
        TInt fadeTime( now.MicroSecondsFrom( iFadeTime ).Int64() );
            
        if ( fadeTime > KMaxFadeTime )
            {          
            if ( !iInternalFlags.IsSet( EFading ) )
                {
                // fade in animation is taking too long, 
                // make popup fully visible
                iAlpha = KAlphaMax;
                }
            else
                {
                // fade out animation is taking too long, 
                // make popup invisible
                iAlpha = KAlphaMin;    
                }   
            }         
        
        if ( iAlpha >= KAlphaMax )
            {
            // popup is completely visible. set the EFading flag and set timeout
            iAlpha = KAlphaMax;
            iInternalFlags.Set( EFading );
            iTimer->Cancel();
            //fade out after timeout
            TTimeIntervalMicroSeconds32 timeout( KShortTimeout );
            if ( iFlags & KAknDiscreetPopupDurationLong )
                {
                timeout = KLongTimeout;
                }
            iTimer->Start( timeout, 
                           KHideInterval, 
                           TCallBack( TimeOut, this ) );
                           
            iFadeTime.HomeTime();
            iFadeTime += timeout;            
            }
        else if ( iAlpha < KAlphaMin )
            {
            iAlpha = KAlphaMin;
            }

        DrawNow();
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::RequestExitL
// Popup exit when popup is completely invisible.
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::RequestExitL()
    {
    if( iCommandObserver && !iInternalFlags.IsSet( EGlobal ) )
        {
        iCommandObserver->ProcessCommandL( EAknDiscreetPopupCmdClose );
        }
    HidePopup();
    ReportEventL( MCoeControlObserver::EEventRequestExit );
    iInternalFlags.Clear( EPressedDown );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::NotifyObserverL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::NotifyObserverL()
    {
    if ( iCommand != 0 && iCommandObserver )
        {
        // Play feedback if there is command associated with the popup
        ImmediateFeedback( ETouchFeedbackSensitive );
        iCommandObserver->ProcessCommandL( iCommand );
        }
    }


// -----------------------------------------------------------------------------
// CAknDiscreetPopupControl::ImmediateFeedback
// -----------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::ImmediateFeedback( TTouchLogicalFeedback aType )
    {
    if ( iFeedBack )
        {
        iFeedBack->InstantFeedback( aType );
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::UpdateNonFadingStatus
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::UpdateNonFadingStatus()
    {
    // Local popups are nonfading when application in foreground
    // Global popups are always nonfading
    TBool newStatus( IsVisible() );
    TBool changeStatus( 
            !Window().IsNonFading() && newStatus 
            || Window().IsNonFading() && !newStatus );
    TBool changeFadeState( EFalse );
    TBool newFadeState( EFalse );

    if ( !iInternalFlags.IsSet( EGlobal ) && newStatus )
        {
        CAknAppUi* appUi = AppUi();
        if ( appUi && !appUi->IsForeground() )
            {
            newStatus = EFalse;
            changeStatus = ETrue;
            if ( changeStatus )
                {
                Window().SetNonFading( newStatus );
                }
            if ( appUi->IsFaded() )
                {
                changeFadeState = ETrue;
                newFadeState = ETrue;
                }
            }
        }

    if ( changeStatus )
        {
        Window().SetNonFading( newStatus );
        }
    if ( changeFadeState )
        {
        Window().SetFaded( newFadeState, RWindowTreeNode::EFadeWindowOnly );
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::SetPressedDownState
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::SetPressedDownState( const TBool& aPressedDown )
    {
    // Reset pressed-down state
    if ( !aPressedDown 
        && ( iInternalFlags.IsSet( EPressedDown ) 
        || iInternalFlags.IsSet( EDragged ) ) )
        {
        iInternalFlags.Clear( EDragged );
        iInternalFlags.Clear( EPressedDown );
        }
    // Set pressed-down state
    else if ( aPressedDown && !iInternalFlags.IsSet( EPressedDown ) )
        {
        iInternalFlags.Set( EPressedDown );
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::ShowPopupL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::ShowPopupL()
    {
    AppUi()->AddToStackL( 
            this, 
            ECoeStackPriorityDefault,
            ECoeStackFlagRefusesAllKeys |
            ECoeStackFlagRefusesFocus );

    User::ResetInactivityTime();

    PlayTone();
    MakeVisible( ETrue );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::HidePopup
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::HidePopup()
    {
    MakeVisible( EFalse );
    AppUi()->RemoveFromStack( this );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::AppUi
// ---------------------------------------------------------------------------
//
CAknAppUi* CAknDiscreetPopupControl::AppUi()
    {
    return static_cast<CAknAppUi*>( iCoeEnv->AppUi() );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::PlayTone
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::PlayTone()
    {
    // Play popup tone if one is defined with flags
    TInt toneId( 0 );
    if ( iFlags & KAknDiscreetPopupConfirmationTone )
        {
        toneId = EAvkonSIDConfirmationTone;
        }
    else if ( iFlags & KAknDiscreetPopupWarningTone )
        {
        toneId = EAvkonSIDWarningTone;
        }
    else if ( iFlags & KAknDiscreetPopupErrorTone )
        {
        toneId = EAvkonSIDErrorTone;
        }
    if ( toneId )
        {
        CAknKeySoundSystem* soundSystem = AppUi()->KeySounds();
        if ( soundSystem )
            {
            soundSystem->PlaySound( toneId );
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::Draw
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::Draw( const TRect& /*aRect*/ ) const
    {
    if ( !iDrawer )
        {
        return;
        }

    CFbsBitmap* popupBitmap( iDrawer->PopupBitmap( Size() ) );
    
    // create a transparent mask for the popup
    CFbsBitmap* transParentBitmap = 
        iDrawer->TransparentMask( popupBitmap->SizeInPixels(), iAlpha );
    
    // blit the bitmap to screen with the transparent mask
    CWindowGc& gc = SystemGc();
    if( transParentBitmap )
        {
        gc.BitBltMasked( Rect().iTl, 
                         popupBitmap, 
                         popupBitmap->SizeInPixels(), 
                         transParentBitmap, 
                         EFalse );	
        }
    else
        {
        gc.BitBlt( Rect().iTl, popupBitmap );
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::ConstructFromResourceL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::ConstructFromResourceL( 
    TResourceReader &aReader )
    {
    // Flags
    iFlags = aReader.ReadInt16();

    // Texts
    TPtrC titleText( aReader.ReadTPtrC() );
    TPtrC bodyText( aReader.ReadTPtrC() );
    
    // Bitmap info
    TPtrC bitmapFile( aReader.ReadTPtrC() );
    TInt bitmapId( aReader.ReadInt16() );
    TInt maskId( aReader.ReadInt16() );
    
    // Skin id info
    
    TAknsItemID skinId;     
    TInt major = aReader.ReadInt32();
    TInt minor = aReader.ReadInt32();
    if ( major > 0 && minor > 0 )
        {
        skinId.Set( major, minor ); 
        }
    else
        {
        skinId = KAknsIIDNone;
        }        
   
    // Extension, not used currently
    aReader.ReadInt32();
    
    ConstructDrawerL( titleText, 
                      bodyText, 
                      NULL, 
                      skinId, 
                      bitmapFile, 
                      bitmapId, 
                      maskId );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::HandleResourceChange
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::HandleResourceChange( TInt aType )
    {
    CAknControl::HandleResourceChange( aType );
    switch ( aType )
        {
        case KEikDynamicLayoutVariantSwitch:
            {
            SetRect( iDrawer->LayoutPopup() );
            break;
            }
        case KAknMessageFocusLost:
        case KEikMessageUnfadeWindows:
            {
            SetPressedDownState( EFalse );
            UpdateNonFadingStatus();
            break;
            }
        case KEikMessageFadeAllWindows:
            {
            SetPressedDownState( EFalse );
            break;
            }
        default:
            {
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupControl::HandlePointerEventL
// Pointer up launches the popup-specific action. 
// Popup is not dismissed when pointer is down on the popup.
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupControl::HandlePointerEventL( 
    const TPointerEvent& aPointerEvent )
    {
    TBool eventInRect( Rect().Contains( aPointerEvent.iPosition ) );

    // Pointer down - set pressed-down state (popup completely visible while
    // pressed-down)
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down
         && eventInRect
         && iInternalFlags.IsClear( EDismissed ) )
        {
        SetPressedDownState( ETrue );
        // Play feedback only when popup is completely visible (or fading away)
        if ( iInternalFlags.IsSet( EFading ) )
            {
            ImmediateFeedback( ETouchFeedbackSensitive );
            }
        }

    // Pointer drag - reset pressed-down state if pointer out of popup area
    else if ( aPointerEvent.iType == TPointerEvent::EDrag )
        {
        iInternalFlags.Set( EDragged );
        if ( !eventInRect && iInternalFlags.IsSet( EPressedDown ) )
            {
            iInternalFlags.Clear( EPressedDown );
            }
        else if ( eventInRect && !iInternalFlags.IsSet( EPressedDown ) )
            {
            iInternalFlags.Set( EPressedDown );
            }
        }

    // Pointer up - reset pressed-down state 
    else if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        if ( iInternalFlags.IsSet( EFading )
             && iInternalFlags.IsSet( EPressedDown )
             && eventInRect )
            {
            // Notify popup tap
            NotifyObserverL();
            // Start fading away
            if ( iInternalFlags.IsClear( EDismissed ) )
                {
                iTimer->Cancel();
                iInternalFlags.Set( EFading );
                iInternalFlags.Set( EDismissed );
                iTimer->Start( KHideDelay, KHideInterval, TCallBack( TimeOut, this ) );
                }
            }
        SetPressedDownState( EFalse );
        }
    }

