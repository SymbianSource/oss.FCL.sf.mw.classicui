/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Control for status pane's signal pane.
*
*/


// INCLUDE FILES
#include <AknSignal.h>
#include <barsread.h>
#include <eikspane.h>
#include <avkon.mbg>
#include <AknsDrawUtils.h>
#include <AknsUtils.h>
#include <AknIconUtils.h>
#include <AknUtils.h>
#include <aknconsts.h>
#include <aknenv.h>
#include <AknStatuspaneUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknDef.h>

#include <AknTasHook.h>
#include "AknSignalIcon.h"
#include "AknSignalStrength.h"
#include "aknsignaldataobserver.h"

/** Frame delay for signal state animations. */
const TInt KAknIndicatorAnimationDelay    = 500000; // microseconds

/** Frame interval for signal state animations. */
const TInt KAknIndicatorAnimationInterval = 500000; // microseconds


/** Number of bitmap frames for CDMA animations. */
const TInt KAknCdmaAnimationFrames = 14;

// Flags for Signal Pane
enum TSignalPaneControlFlags
    {
    EAknSignalPaneButton1DownInSignalRect = 0x00000001
    };


class CAknSignalPaneExtension: public CBase
    {
public:

    CAknSignalPaneExtension();
    ~CAknSignalPaneExtension();

public: // new methods

    TBool CdmaSignalIconInUse();
    CFbsBitmap* CdmaSignalIcon();
    void CdmaSignalAnimate();

public:

    // General signal indicators
    TAny* iSpare1; // was iSignalIcon
    TAny* iSpare2; // was iSignalIconMask

    // CDMA Signal indicators
    TInt        iCdmaAnimationIndex;
    TInt        iCdmaSignalState;
    CFbsBitmap* iCdmaReceiveIcons[KAknCdmaAnimationFrames];  // animation frames
    CFbsBitmap* iCdmaReceiveMasks[KAknCdmaAnimationFrames];  // animation frame masks (needed because of AknIconUtils)
    CFbsBitmap* iCdmaSendIcons[KAknCdmaAnimationFrames];     // animation frames
    CFbsBitmap* iCdmaSendMasks[KAknCdmaAnimationFrames];     // animation frame masks (needed because of AknIconUtils)
    CFbsBitmap* iCdmaStaticIcons[5];    // non-animated icons
    CFbsBitmap* iCdmaStaticMasks[5];    // non-animated masks (needed because of AknIconUtils)

    TBool       iIsActiveIdle;
    };


// ---------------------------------------------------------------------------
// CAknSignalPaneExtension::CAknSignalPaneExtension
// Default constructor.
// ---------------------------------------------------------------------------
//
CAknSignalPaneExtension::CAknSignalPaneExtension()
    {
    }


// ---------------------------------------------------------------------------
// CAknSignalPaneExtension::~CAknSignalPaneExtension
// Destructor
// ---------------------------------------------------------------------------
//
CAknSignalPaneExtension::~CAknSignalPaneExtension()
    {
    }


// ---------------------------------------------------------------------------
// CAknSignalPaneExtension::CdmaSignalIconInUse
// Determine if any CDMA indicator is being used.
// ---------------------------------------------------------------------------
//
TBool CAknSignalPaneExtension::CdmaSignalIconInUse()
    {
    if ( iCdmaSignalState != EAknSignalCdmaIndicatorOff )
        {
        return ETrue;
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknSignalPaneExtension::CdmaSignalIcon
// Get the current CDMA icon to be displayed.
// ---------------------------------------------------------------------------
//
CFbsBitmap* CAknSignalPaneExtension::CdmaSignalIcon()
    {
    if ( iCdmaSignalState == EAknSignalCdmaIndicatorReceiving )
        {
        return iCdmaReceiveMasks[iCdmaAnimationIndex];
        }
    else if ( iCdmaSignalState == EAknSignalCdmaIndicatorSending )
        {
        return iCdmaSendMasks[iCdmaAnimationIndex];
        }
    else
        {
        return iCdmaStaticMasks[iCdmaSignalState - EAknSignalCdmaIndicatorNoService];
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPaneExtension::CdmaSignalAnimate
// Adjusts the animation of the CDMA signal icon.
// ---------------------------------------------------------------------------
//
void CAknSignalPaneExtension::CdmaSignalAnimate()
    {
    iCdmaAnimationIndex++;
    if ( iCdmaAnimationIndex >= KAknCdmaAnimationFrames )
        {
        iCdmaAnimationIndex = 0;
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::CAknSignalPane
// Default contructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSignalPane::CAknSignalPane()
    {
    AKNTASHOOK_ADD( this, "CAknSignalPane" );
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::~CAknSignalPane
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSignalPane::~CAknSignalPane()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition( this );

    delete iDataObserver;
    delete iTicker;
    for ( TInt ll = 0; ll < KAknCdmaAnimationFrames; ll++ )
        {
        delete iExtension->iCdmaReceiveIcons[ll];
        delete iExtension->iCdmaReceiveMasks[ll];
        }

    for ( TInt mm = 0; mm < KAknCdmaAnimationFrames; mm++ )
        {
        delete iExtension->iCdmaSendIcons[mm];
        delete iExtension->iCdmaSendMasks[mm];
        }

    for ( TInt nn = 0; nn < 5; nn++ )
        {
        delete iExtension->iCdmaStaticIcons[nn];
        delete iExtension->iCdmaStaticMasks[nn];
        }
    delete iSignalIconControl;
    delete iSignalStrengthControl;

    delete iExtension;
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::ConstructL
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::ConstructL()
    {
    iExtension = new (ELeave) CAknSignalPaneExtension();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

#ifdef __PROTOCOL_CDMA
    // Create CDMA indicator icons
    for ( TInt mm = 0; mm < KAknCdmaAnimationFrames; mm++ )
        {
        AknIconUtils::CreateIconL(
            iExtension->iCdmaReceiveIcons[mm],
            iExtension->iCdmaReceiveMasks[mm],
            AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_indi_signal_receiving_cdma_01 + mm,
            EMbmAvkonQgn_indi_signal_receiving_cdma_01 + mm );

        AknIconUtils::CreateIconL(
            iExtension->iCdmaSendIcons[mm],
            iExtension->iCdmaSendMasks[mm],
            AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_indi_signal_sending_cdma_01 + mm,
            EMbmAvkonQgn_indi_signal_sending_cdma_01 + mm );
        }

    // No service
    AknsUtils::CreateColorIconL(
        skin,
        KAknsIIDQgnIndiSignalNoService,
        iExtension->iCdmaStaticIcons[0],
        iExtension->iCdmaStaticMasks[0],
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_signal_no_service,
        EMbmAvkonQgn_indi_signal_no_service );

     // Packet data available, uses standard signal icon
    AknsUtils::CreateColorIconL(
        skin,
        KAknsIIDQgnPropSignalIcon,
        iExtension->iCdmaStaticIcons[1],
        iExtension->iCdmaStaticMasks[1],
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_prop_signal_icon,
        EMbmAvkonQgn_prop_signal_icon );

    // Packet data unavailable
    AknsUtils::CreateColorIconL(
        skin,
        KAknsIIDQgnIndiSignalNotAvailCdma,
        iExtension->iCdmaStaticIcons[2],
        iExtension->iCdmaStaticMasks[2],
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_signal_not_avail_cdma,
        EMbmAvkonQgn_indi_signal_not_avail_cdma );

    // Packet data active
    AknsUtils::CreateColorIconL(
        skin,
        KAknsIIDQgnIndiSignalActiveCdma,
        iExtension->iCdmaStaticIcons[3],
        iExtension->iCdmaStaticMasks[3],
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_signal_active_cdma,
        EMbmAvkonQgn_indi_signal_active_cdma );

    // Packet data dormant
    AknsUtils::CreateColorIconL(
        skin,
        KAknsIIDQgnIndiSignalDormantCdma,
        iExtension->iCdmaStaticIcons[4],
        iExtension->iCdmaStaticMasks[4],
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_signal_dormant_cdma,
        EMbmAvkonQgn_indi_signal_dormant_cdma );
#endif // __PROTOCOL_CDMA

    // off by default
    iExtension->iCdmaSignalState    = EAknSignalCdmaIndicatorOff;
    iExtension->iCdmaAnimationIndex = 0;
    iExtension->iIsActiveIdle = AknStatuspaneUtils::IsActiveIdle();

    iSignalIconControl = CAknSignalIcon::NewL();
    iSignalIconControl->SetDrawBlank( EFalse );

    // Load default icon
    LoadSignalIconL( 0, 0 );

    iSignalStrengthControl = CAknSignalStrength::NewL();

    iSignalIconControl->SetContainerWindowL( *this );
    iSignalStrengthControl->SetContainerWindowL( *this );

    iTicker = CPeriodic::NewL( CActive::EPriorityLow );

    // Set flags to default values
    iPrivateFlags = 0;

    iDataObserver = new (ELeave) CAknSignalDataObserver( this );
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::ConstructFromResourceL
// Resource constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::ConstructFromResourceL(
    TResourceReader& aReader )
    {
    ConstructL();
    SetSignalLevel( aReader.ReadInt16() ); // Initial signal level.
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::SetSignalLevel
// Sets the signal level.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::SetSignalLevel( TInt aLevel )
    {
    if ( aLevel == KAknSignalOffLineMode )
        {
        iSignalIconControl->SetOffLine( ETrue );
        }
    else
        {
        iSignalIconControl->SetOffLine( EFalse );
        }

    iSignalStrengthControl->SetSignalLevel( aLevel );
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::SignalLevel
// Returns the current signal level.
// ---------------------------------------------------------------------------
//
TInt CAknSignalPane::SignalLevel()
    {
    if ( iSignalStrengthControl )
        {
        return iSignalStrengthControl->SignalLevel();
        }
    else
        {
        return 0;
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::SignalState
// Returns the current signal state.
// ---------------------------------------------------------------------------
//
TInt CAknSignalPane::SignalState()
    {
    return iSignalState;
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::DisableAnimation
// Stops ongoing signal state animation.
// ---------------------------------------------------------------------------
//
void CAknSignalPane::DisableAnimation()
    {
    if ( iTicker && iTicker->IsActive() )
        {
        iTicker->Cancel();
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::ShowGprsIcon
// Displays a GRPS state icon.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::ShowGprsIcon( TInt aGprsIconState )
    {
    // Gprs state is not changed if illegal value was given.
    if (  aGprsIconState >= EAknSignalGprsIndicatorOff &&
          aGprsIconState <= EAknSignalGprsIndicatorMultipdp )
        {
        TRAP_IGNORE( LoadSignalIconL( aGprsIconState,
                                      iSignalIconControl->ColorIndex() ) );

        iSignalIconControl->SetDrawBlank( EFalse );

        if ( aGprsIconState != EAknSignalGprsIndicatorEstablishingContext &&
             iTicker )
            {
            iTicker->Cancel();
            }
        else if ( aGprsIconState == EAknSignalGprsIndicatorEstablishingContext )
            {
            if ( iTicker && !iTicker->IsActive() )
                {
                iTicker->Start( KAknIndicatorAnimationDelay,
                                KAknIndicatorAnimationInterval,
                                TCallBack( TickerCallback, this ) );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// CAknSignalPane::SizeChanged
// Handles size change events.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::SizeChanged()
    {
    // No fading if staconpane is active.
    SetContainerWindowNonFading( AknStatuspaneUtils::StaconPaneActive() );

    TAknWindowComponentLayout signalIconLayout;
    TAknWindowComponentLayout signalStrenghtLayout;

    TRect parent( Rect() );

    TAknLayoutRect rect;

    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        //  Signal pane in STACON PANE.
        TInt varietyIndex = AknStatuspaneUtils::StaconSoftKeysLeft() ? 1 : 0;
        signalIconLayout =
            AknLayoutScalable_Avkon::signal_pane_stacon_g2( varietyIndex );
        signalStrenghtLayout =
            AknLayoutScalable_Avkon::signal_pane_stacon_g1( varietyIndex );

        AknLayoutUtils::LayoutControl( iSignalIconControl,
                                       parent,
                                       signalIconLayout );
        AknLayoutUtils::LayoutControl( iSignalStrengthControl,
                                       parent,
                                       signalStrenghtLayout );
        }
    else if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        //  Signal pane in FLAT STATUSPANE.
        signalIconLayout     = AknLayoutScalable_Avkon::signal_pane_g2( 1 );
        signalStrenghtLayout = AknLayoutScalable_Avkon::signal_pane_g1( 1 );

        AknLayoutUtils::LayoutControl( iSignalIconControl,
                                       parent,
                                       signalIconLayout);
        AknLayoutUtils::LayoutControl( iSignalStrengthControl,
                                       parent,
                                       signalStrenghtLayout );
        }
    else if ( AknStatuspaneUtils::SmallLayoutActive() )
        {
        //  Signal pane in SMALL STATUSPANE, only icon shown.
        signalIconLayout = AknLayoutScalable_Avkon::status_small_pane_g2( 0 );
        AknLayoutUtils::LayoutControl( iSignalIconControl,
                                       parent,
                                       signalIconLayout );
        iSignalStrengthControl->SetRect( TRect( 0, 0, 0, 0 ) );
        }
    else
        {
        // Signal pane in NORMAL or WIDESCREEN STATUS PANE.
        TBool hdLayout( AknStatuspaneUtils::HDLayoutActive() );
        signalIconLayout =
            AknLayoutScalable_Avkon::signal_pane_g2( hdLayout ? 2 : 0 );
        signalStrenghtLayout =
            AknLayoutScalable_Avkon::signal_pane_g1( hdLayout ? 2 : 0 );

        AknLayoutUtils::LayoutControl( iSignalIconControl,
                                       parent,
                                       signalIconLayout );

        AknLayoutUtils::LayoutControl( iSignalStrengthControl,
                                       parent,
                                       signalStrenghtLayout );
        }

    TInt iconColorIndex = 0;
    if ( AknStatuspaneUtils::StaconPaneActive() ||
         AknStatuspaneUtils::FlatLayoutActive() )
        {
        iconColorIndex = EAknsCIQsnIconColorsCG23;
        }
    else
        {
        iconColorIndex = EAknsCIQsnIconColorsCG5;
        }

    TRAP_IGNORE( LoadSignalIconL( iSignalState, iconColorIndex ) );

    AknsUtils::RegisterControlPosition( this );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// CAknSignalPane::PositionChanged
// Handles position change events.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::PositionChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// CAknSignalPane::Draw
// Draws the signal pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::Draw( const TRect& /*aRect*/ ) const
    {
    if ( iExtension->iIsActiveIdle )
        {
        return;
        }

    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        //  Signal pane in STACON PANE layout
        DrawInStaconPane( Rect() );
        }
    else if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        //  Signal pane in FLAT STATUSPANE layout
        DrawInFlatStatusPane( Rect() );
        }
    else if ( AknStatuspaneUtils::SmallLayoutActive() )
        {
        //  Signal pane in SMALL STATUSPANE layout
        DrawInSmallStatusPane( Rect() );
        }
    else
        {
        // Signal pane in NORMAL STATUSPANE layout
        DrawInNormalStatusPane( Rect() );
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::TickerCallback
// Static callback function for signal state animation timer.
// ---------------------------------------------------------------------------
//
TInt CAknSignalPane::TickerCallback( TAny* aThis )
    {
    return static_cast<CAknSignalPane*>( aThis )->DoTick();
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::DoTick
// Callback function for signal state animation timer.
// ---------------------------------------------------------------------------
//
TInt CAknSignalPane::DoTick()
    {
    if ( iExtension->CdmaSignalIconInUse() )
        {
        // tick used for cdma animation
        iExtension->CdmaSignalAnimate();
        iSignalIconControl->SetSignalIcon( iExtension->CdmaSignalIcon() );
        iSignalIconControl->SetSignalIconMask( iExtension->CdmaSignalIcon() );
        }
    else
        {
        // default tick blinks icon
        iSignalIconControl->SetDrawBlank( !iSignalIconControl->DrawBlank() );
        }

    // Must be DrawDeferred (not DrawNow) so that we don't block
    // application thread in high load situations.
    DrawDeferred();

    return ETrue;
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// CAknSignalPane::HandleResourceChange
// Handles resource change events.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );

    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        DrawDeferred();
        }

    if ( aType == KEikColorResourceChange || aType == KAknsMessageSkinChange )
        {
        if ( iSignalIconControl )
            {
            iSignalIconControl->SetColorIndex( 0 ); // reset skin color
            }
        SizeChanged(); // Sizechanged updates the color
        DrawDeferred();
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::SetNaviPaneBackgroundType
// Not used anymore.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::SetNaviPaneBackgroundType( TInt /*aType*/ )
    {
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::DrawInNormalStatusPane
// Draws the signal pane in normal status pane layout.
// ---------------------------------------------------------------------------
//
void CAknSignalPane::DrawInNormalStatusPane( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    TRect rect( Rect() );

    // Solid or wipe comes from background
    if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
        {
        // Default drawing if skinning is not available
        gc.Clear( rect );
        // Default solid
        gc.SetPenStyle( CGraphicsContext::ENullPen );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.SetBrushColor(
            AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
        gc.DrawRect( rect );
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::DrawInSmallStatusPane
// Draws the signal pane in small status pane layout.
// ---------------------------------------------------------------------------
//
void CAknSignalPane::DrawInSmallStatusPane( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    TRect rect( Rect() );

    if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
        {
        gc.Clear( rect );
        // If there is no background, draw navi pane part
        gc.SetPenStyle( CGraphicsContext::ENullPen );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.SetBrushColor(
            AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
        gc.DrawRect( rect );
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::DrawInStaconPane
// Draws the signal pane in stacon pane layout.
// ---------------------------------------------------------------------------
//
void CAknSignalPane::DrawInStaconPane( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();
    TRect rect( Rect() );
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
        {
        gc.SetPenStyle( CGraphicsContext::ENullPen );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.SetBrushColor(
            AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
        gc.DrawRect( rect );
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::DrawInFlatStatusPane
// Draws the signal pane in flat status pane layout.
// ---------------------------------------------------------------------------
//
void CAknSignalPane::DrawInFlatStatusPane( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();
    TRect rect( Rect() );
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
        {
        gc.SetPenStyle( CGraphicsContext::ENullPen );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.SetBrushColor(
            AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
        gc.DrawRect( rect );
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::ShowCommonPacketDataIcon
// Displays a common packet data state icon.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::ShowCommonPacketDataIcon(
    TInt aCommonPacketDataIconState )
    {
    // State is not changed if illegal value was given.
    if ( aCommonPacketDataIconState >= EAknSignalCommonPacketDataIndicatorOff &&
         aCommonPacketDataIconState <= EAknSignalCommonPacketDataIndicatorMultipdp )
        {
        TRAP_IGNORE( LoadSignalIconL( aCommonPacketDataIconState,
                                      iSignalIconControl->ColorIndex() ) );

        iSignalIconControl->SetDrawBlank( EFalse );

        if ( aCommonPacketDataIconState != EAknSignalCommonPacketDataIndicatorEstablishingContext &&
             iTicker )
            {
            iTicker->Cancel();
            }
        else if ( aCommonPacketDataIconState == EAknSignalCommonPacketDataIndicatorEstablishingContext )
            {
            if ( iTicker && !iTicker->IsActive() )
                {
                iTicker->Start( KAknIndicatorAnimationDelay,
                                KAknIndicatorAnimationInterval,
                                TCallBack( TickerCallback, this ) );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::ShowEdgeIcon
// Displays an EDGE state icon.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::ShowEdgeIcon( TInt aEdgeIconState )
    {
    // State is not changed if illegal value was given.
    if ( aEdgeIconState >= EAknSignalEdgeIndicatorOff &&
         aEdgeIconState <= EAknSignalEdgeIndicatorMultipdp )
        {
        TRAP_IGNORE( LoadSignalIconL( aEdgeIconState,
                                      iSignalIconControl->ColorIndex() ) );

        iSignalIconControl->SetDrawBlank( EFalse );

        if ( aEdgeIconState != EAknSignalEdgeIndicatorEstablishingContext &&
             iTicker )
            {
            iTicker->Cancel();
            }
        else if ( aEdgeIconState == EAknSignalEdgeIndicatorEstablishingContext )
            {
            if ( iTicker && !iTicker->IsActive() )
                {
                iTicker->Start( KAknIndicatorAnimationDelay,
                                KAknIndicatorAnimationInterval,
                                TCallBack( TickerCallback, this ) );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::ShowWcdmaIcon
// Displays a WCDMA state icon.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::ShowWcdmaIcon( TInt aWcdmaIconState )
    {
    // State is not changed if illegal value was given.
    if ( aWcdmaIconState >= EAknSignalWcdmaIndicatorOff &&
         aWcdmaIconState <= EAknSignalWcdmaIndicatorSuspended )
        {
        TRAP_IGNORE( LoadSignalIconL( aWcdmaIconState,
                                      iSignalIconControl->ColorIndex() ) );

        iSignalIconControl->SetDrawBlank( EFalse );

        if ( aWcdmaIconState != EAknSignalWcdmaIndicatorEstablishingContext &&
             iTicker )
            {
            iTicker->Cancel();
            }
        else if ( aWcdmaIconState == EAknSignalWcdmaIndicatorEstablishingContext )
            {
            if ( iTicker && !iTicker->IsActive() )
                {
                iTicker->Start( KAknIndicatorAnimationDelay,
                                KAknIndicatorAnimationInterval,
                                TCallBack( TickerCallback, this ) );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::ShowHsdpaIcon
// Displays an HSDPA state icon.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalPane::ShowHsdpaIcon( TInt aHsdpaIconState )
    {
    // State is not changed if illegal value was given.
    if ( aHsdpaIconState >= EAknSignalHsdpaIndicatorOff &&
         aHsdpaIconState <= EAknSignalHsdpaIndicatorMultipdp )
        {
        TRAP_IGNORE( LoadSignalIconL( aHsdpaIconState,
                                      iSignalIconControl->ColorIndex() ) );

        iSignalIconControl->SetDrawBlank( EFalse );

        if ( aHsdpaIconState != EAknSignalHsdpaIndicatorEstablishingContext &&
             iTicker )
            {
            iTicker->Cancel();
            }
        else if ( aHsdpaIconState == EAknSignalHsdpaIndicatorEstablishingContext )
            {
            if ( iTicker && !iTicker->IsActive() )
                {
                iTicker->Start( KAknIndicatorAnimationDelay,
                                KAknIndicatorAnimationInterval,
                                TCallBack( TickerCallback, this ) );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::ShowCdmaIcon
// Displays a CDMA state icon.
// ---------------------------------------------------------------------------
//
#ifdef __PROTOCOL_CDMA
EXPORT_C void CAknSignalPane::ShowCdmaIcon( TInt aCdmaIconState )
    {
    // Cdma state is not changed if illegal value was given, or if there was no change
    if ( aCdmaIconState >= EAknSignalCdmaIndicatorOff &&
         aCdmaIconState <= EAknSignalCdmaIndicatorReceiving &&
         aCdmaIconState != iExtension->iCdmaSignalState )
        {
        TRAP_IGNORE( LoadSignalIconL( aCdmaIconState,
                                      iSignalIconControl->ColorIndex() ) );

        iExtension->iCdmaSignalState = aCdmaIconState;

        // Tick timer is only used when animating.
        if ( aCdmaIconState != EAknSignalCdmaIndicatorSending &&
             aCdmaIconState != EAknSignalCdmaIndicatorReceiving &&
             iTicker )
            {
            iTicker->Cancel();
            }

        switch ( aCdmaIconState )
            {
            case EAknSignalCdmaIndicatorSending:
            case EAknSignalCdmaIndicatorReceiving:
                if ( iTicker && !iTicker->IsActive() )
                    {
                    // restart animation
                    iExtension->iCdmaAnimationIndex = 0;
                    iTicker->Start( KAknIndicatorShortAnimationInterval,
                                    KAknIndicatorShortAnimationInterval,
                                    TCallBack( TickerCallback, this ) );
                    }
                break;
            default:
                break;
            }
        }
    }
#else
EXPORT_C void CAknSignalPane::ShowCdmaIcon(TInt /*aCdmaIconState*/ )
    {
    }
#endif // __PROTOCOL_CDMA


// ---------------------------------------------------------------------------
// From class CCoeControl.
// CAknSignalPane::CountComponentControls
// Returns the amount of component controls.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknSignalPane::CountComponentControls() const
    {
    return 2;
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// CAknSignalPane::ComponentControl
// Gets a component control by a control index.
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CAknSignalPane::ComponentControl( TInt aIndex ) const
    {
    CCoeControl* control = NULL;

    switch ( aIndex )
        {
        case 0:
            {
            control = iSignalStrengthControl;
            break;
            }
        case 1:
            {
            control = iSignalIconControl;
            break;
            }
        }

    return control;
    }


// ---------------------------------------------------------------------------
// From class CAknControl.
// CAknSignalPane::ExtensionInterface
// Not implemented.
// ---------------------------------------------------------------------------
//
EXPORT_C void* CAknSignalPane::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }


// ---------------------------------------------------------------------------
// From class CCoeControl.
// CAknSignalPane::HandlePointerEventL()
// Processes signal pane's pointer events. Actually this does nothing yet
// ---------------------------------------------------------------------------
//
void CAknSignalPane::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( IsDimmed() )
            {
            iPrivateFlags &= (~EAknSignalPaneButton1DownInSignalRect);
            return;
            }

        // Get rect of signal pane.
        TRect rect( Rect() );

        // Switch by type
        switch ( aPointerEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                {
                // if signal pane's rect contains pointer down position
                if ( rect.Contains( aPointerEvent.iPosition ) )
                    {
                    // set flag that down was inside signal pane
                    iPrivateFlags |= EAknSignalPaneButton1DownInSignalRect;
                    }
                }
                break;

            case TPointerEvent::EButton1Up:
                {
                // if signalPane's rect contains pointer down position
                if ( iPrivateFlags&EAknSignalPaneButton1DownInSignalRect &&
                     rect.Contains( aPointerEvent.iPosition ) )
                    {
                    // Up happened inside signal pane's rect
                    // activate something
                    }

                // Up happened, reset button down flag
                iPrivateFlags &= (~EAknSignalPaneButton1DownInSignalRect);
                }
                break;

            default:
                break;
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::SetContainerWindowNonFading
// Allows/disallows fading of signal pane.
// ---------------------------------------------------------------------------
//
void CAknSignalPane::SetContainerWindowNonFading( TBool aNonFading )
    {
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if ( statusPane )
        {
        CCoeControl* control = NULL;
        TRAP_IGNORE(
            control = statusPane->ContainerControlL(
                TUid::Uid( EEikStatusPaneUidSignal ) ) );
        if ( control )
            {
            control->DrawableWindow()->SetNonFading( aNonFading );
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalPane::LoadSignalIconL
// Changes the signal state icon of the signal icon control.
// ---------------------------------------------------------------------------
//
void CAknSignalPane::LoadSignalIconL( TInt aIconState, TInt aIconColorIndex )
    {
    if ( iSignalIconControl )
        {
        iSignalIconControl->LoadIconL( aIconState, aIconColorIndex );
        }

    iSignalState = aIconState;
    }

//  End of File
