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
* Description:  Implementation for default status indicator control.
*
*/


// INCLUDE FILES
#include <AknsDrawUtils.h>
#include <AknPictographInterface.h>
#include <AknPictographDrawerInterface.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>
#include <AknSmallIndicator.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif

#include <AknTasHook.h>
#include <touchfeedback.h>


#include "AknIndicatorObserver.h"
#include "aknindicatordataobserver.h"
#include "AknSgcc.h"
#include "AknIncallStatusBubble.h"
#include "AknUtils.h"
#include "aknconsts.h"
#include "AknIndicator.h"
#include "AknIndicatorContainer.h"
#include "aknenv.h"
#include "AknStatuspaneUtils.h"
#include "AknIndicatorFader.h"
#include "aknappui.h"
#include "AknDef.h"
#include "layoutmetadata.cdl.h"

// CONSTANTS
const TInt KAknIndicatorQueueGranularity       = 4;
const TInt KAknIndicatorAnimationInterval      = 500000; // micro seconds
const TInt KAknIndicatorAnimationShortDelay    = 400000; // micro seconds

// Indicator pane control flags.
enum TIndicatorPaneControlFlags
    {
    EAknIndicatorsButton1DownInIndicatorPaneRect = 0x00000001
    };

// ================= PRIVATE CLASS =======================

NONSHARABLE_CLASS( CAknIndicatorContainerExtension ) :
    public CBase,
    public MAknPictographAnimatorCallBack,
    public MCoeMessageMonitorObserver
    {
public:
    /**
    * Constructor.
    */
    static CAknIndicatorContainerExtension* NewL(
        CAknIndicatorContainer* aIndicatorContainer );

    /**
    * Destructor.
    */
    ~CAknIndicatorContainerExtension();

    TBool SmallStatusPaneLayout();
    void SetSmallStatusPaneLayout( TBool aIsActive );

    // From base class @c MCoeMessageMonitorObserver.

    /**
    * Used to receive event from window server
    * when the visibility of the window changes.
    *
    * @param  aEvent  The window server event.
    */
    void MonitorWsMessage( const TWsEvent &aEvent );

private:

    CAknIndicatorContainerExtension(
        CAknIndicatorContainer* aIndicatorContainer );

    void ConstructL();

    // From MAknPictographAnimatorCallBack
    void DrawPictographArea();

public:

    CAknIndicatorContainer*     iIndicatorContainer;
    CAknPictographInterface*    iPictoInterface;
    TBool                       iSmallStatusPaneLayout;
    TBool                       iSwitchLayoutInProgress;
    TBool                       iIncallBubbleAllowedInIdle;
    TBool                       iIncallBubbleAllowedInUsual;
    TPoint                      iPositionRelativeToScreen;
    CAknIndicatorDataObserver*  iDataObserver;
    TInt                        iFlags;
    TBool                       iIncallBubbleDisabled;
    TBool                       iIsForeground;
    TBool                       iIsActiveIdle;
    };


CAknIndicatorContainerExtension* CAknIndicatorContainerExtension::NewL(
    CAknIndicatorContainer* aIndicatorContainer )
    {
    CAknIndicatorContainerExtension* self = new( ELeave )
        CAknIndicatorContainerExtension( aIndicatorContainer );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


void CAknIndicatorContainerExtension::ConstructL()
    {
    iPictoInterface = CAknPictographInterface::NewL( *iIndicatorContainer, *this );
    if ( iIndicatorContainer->IndicatorContext() ==
            CAknIndicatorContainer::EUniversalIndicators )
        {
        iDataObserver =
            new (ELeave) CAknIndicatorDataObserver( iIndicatorContainer );
        }

    TRAP_IGNORE( CCoeEnv::Static()->AddMessageMonitorObserverL( *this ) );
    }


CAknIndicatorContainerExtension::CAknIndicatorContainerExtension(
    CAknIndicatorContainer* aIndicatorContainer )
    : iIndicatorContainer( aIndicatorContainer )
    {
    iSmallStatusPaneLayout      = AknStatuspaneUtils::SmallLayoutActive();
    iIncallBubbleAllowedInUsual = ETrue;
    iIsForeground = static_cast<CAknAppUi*>( CEikonEnv::Static()->EikAppUi() )->IsForeground();
    iIsActiveIdle = AknStatuspaneUtils::IsActiveIdle();
    }


CAknIndicatorContainerExtension::~CAknIndicatorContainerExtension()
    {
    delete iPictoInterface;
    delete iDataObserver;

    CCoeEnv::Static()->RemoveMessageMonitorObserver( *this );
    }


void CAknIndicatorContainerExtension::DrawPictographArea()
    {
    iIndicatorContainer->DrawPictographArea();
    }


TBool CAknIndicatorContainerExtension::SmallStatusPaneLayout()
    {
    return iSmallStatusPaneLayout;
    }


void CAknIndicatorContainerExtension::SetSmallStatusPaneLayout(
    TBool aIsActive )
    {
    iSmallStatusPaneLayout = aIsActive;
    }

void CAknIndicatorContainerExtension::MonitorWsMessage( const TWsEvent& aEvent )
    {
    switch ( aEvent.Type() )
        {
        case KAknFullOrPartialForegroundGained:
            iIndicatorContainer->ResetAnimTicker( ETrue );
            break;

        case KAknFullOrPartialForegroundLost:
            iIndicatorContainer->ResetAnimTicker( EFalse );
            break;

        default:
            break;
        }
    }

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------------------------
// CAknIndicatorContainer::CAknIndicatorContainer
// Default constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknIndicatorContainer::CAknIndicatorContainer() :
    iLayoutOrientation( EVertical ),
    iPreviousLayoutOrientation( EVertical ),
    iAlignment( ERight ),
    iIndicatorContext( EUniversalIndicators ),
    iSynchronizingValue( 0 )
    {
    AKNTASHOOK_ADD( this, "CAknIndicatorContainer" );
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::CAknIndicatorContainer
// Constructor with context type parameter.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknIndicatorContainer::CAknIndicatorContainer(
    TBool aIndicatorContext )
    : iLayoutOrientation( EVertical ),
      iPreviousLayoutOrientation( EVertical ),
      iAlignment( ERight ),
      iIndicatorContext( aIndicatorContext ),
      iSynchronizingValue( 0 )
    {
    AKNTASHOOK_ADD( this, "CAknIndicatorContainer" );
    }

// ---------------------------------------------------------------------------
// CAknIndicatorContainer::~CAknIndicatorContainer
// Destructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknIndicatorContainer::~CAknIndicatorContainer()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition( this );

    if ( iIndicators )
        {
        TInt count = iIndicators->Count();
        for ( TInt ii = 0; ii < count; ii++)
            {
            delete iIndicators->At( ii );
            }
        delete iIndicators;
        }

    if ( iTicker )
        {
        iTicker->Cancel();
        delete iTicker;
        }

    delete iIncallBubble;
    delete iExtension;
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::ConstructL
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknIndicatorContainer::ConstructL()
    {
    iExtension = CAknIndicatorContainerExtension::NewL( this );

    if ( !iIndicators )
        {
        iIndicators =
            new (ELeave) CAknIndicatorQueue( KAknIndicatorQueueGranularity );
        }


    iTicker = CPeriodic::NewL( CActive::EPriorityLow );
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::ConstructFromResourceL
// Resource constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknIndicatorContainer::ConstructFromResourceL(
    TResourceReader& aReader )
    {
    ConstructL();

    if ( iIndicatorContext != EUniversalIndicators &&
         iIndicatorContext != ENaviPaneEditorIndicators &&
         iIndicatorContext != EQueryEditorIndicators )
        {
        TInt count = aReader.ReadInt16();
        for ( TInt ii = 0; ii < count; ii++ )
            {
            CAknIndicator* indicator =
                new (ELeave) CAknIndicator ( iIndicatorContext );
            CleanupStack::PushL( indicator );
            indicator->SetContainerWindowL( *this );
            indicator->ConstructFromResourceL( aReader, this );
            iIndicators->AppendL( indicator );
            CleanupStack::Pop( indicator );
            indicator = NULL;
            }

        PrioritizeIndicatorsL();
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::IndicatorContext
// Returns the indicator context of this container.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknIndicatorContainer::IndicatorContext() const
    {
    return iIndicatorContext;
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::SetIndicatorState
// Sets the state of an indicator in this container.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknIndicatorContainer::SetIndicatorState( TUid aIndicatorId,
                                                         TInt aState,
                                                         TBool aDrawNow )
    {
    if ( !IndicatorExists( aIndicatorId ) )
        {
        if ( iIndicatorContext == EUniversalIndicators )
            {
            TRAP_IGNORE( CreateIndicatorFromPaneResourceL(
                aIndicatorId, R_AVKON_STATUS_PANE_INDICATOR_DEFAULT, 0 ) );
            }
        else if ( iIndicatorContext == ENaviPaneEditorIndicators ||
                  iIndicatorContext == EQueryEditorIndicators )
            {
            TRAP_IGNORE( CreateIndicatorFromPaneResourceL(
                aIndicatorId, R_AVKON_NAVI_PANE_EDITOR_INDICATORS, 0 ) );
            }
        }

    TBool changed = EFalse;
    TInt  count   = iIndicators->Count();

    CAknIndicator* indicator = NULL;
    for ( TInt ii = 0; ii < count; ii++ )
        {
        indicator = iIndicators->At( ii );

        if ( indicator->Uid() == aIndicatorId )
            {
            if ( indicator->IndicatorState() != aState )
                {
                changed = ETrue;
                }

            indicator->SetIndicatorState( aState );
            if ( aState == MAknIndicator::EIndicatorAnimate )
                {
                // Synchronizes new animated indicator with previous ones
                indicator->SetAnimateState( iSynchronizingValue );
                }

            // In case of GPRS indicator in small status pane it is necessary
            // to check whether a correct status pane layout is used.
            if ( aIndicatorId == TUid::Uid( EAknNaviPaneEditorIndicatorGprs ) )
                {
                TBool layoutUpdated( EFalse );
                TRAPD( err, layoutUpdated = UpdateSmallLayoutL() );
                if ( layoutUpdated && err == KErrNone )
                    {
                    // Needed because this method is not called again.
                    iExtension->iSwitchLayoutInProgress = EFalse;
                    }
                }

            break;
            }
        }

    if ( changed )
        {
        TRAP_IGNORE( PrioritizeIndicatorsL() );
        SizeChanged(); // starts/stops also animation timers if needed
        }

    // Do not draw in case the indicator state has not changed and
    // the indicator is not visible, even if aDrawNow is defined,
    // otherwise flicker will occur.
    if ( aDrawNow && ( changed || aState ) )
        {
        DrawNow();
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::IndicatorState
// Returns current state of a status indicator in this container.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknIndicatorContainer::IndicatorState( TUid aIndicatorId )
    {
    TInt indicatorState( MAknIndicator::EIndicatorOff );

    TInt count = iIndicators->Count();
    CAknIndicator* indicator = NULL;
    for ( TInt ii = 0; ii < count; ii++ )
        {
        indicator = iIndicators->At( ii );

        if ( indicator->Uid() == aIndicatorId )
            {
            indicatorState = indicator->IndicatorState();
            break;
            }
        }

    return indicatorState;
    }


EXPORT_C void CAknIndicatorContainer::SetIndicatorValueL( TUid aIndicatorId,
                                                          const TDesC& aString )
    {
    if ( ( iIndicatorContext == ENaviPaneEditorIndicators ||
           iIndicatorContext == EQueryEditorIndicators )  &&
         !IndicatorExists( aIndicatorId ) )
        {
        CreateIndicatorFromPaneResourceL( aIndicatorId, R_AVKON_NAVI_PANE_EDITOR_INDICATORS, 0);
        }

    TInt count = iIndicators->Count();
    for(TInt ii = 0; ii < count; ii++)
        {
        CAknIndicator* indicator = iIndicators->At(ii);
        if ( indicator->Uid() == aIndicatorId )
            {
            TInt indicatorWidthBefore = indicator->IconSize().iWidth;
            indicator->SetIndicatorValueL(aString);
            TInt indicatorWidthAfter = indicator->IconSize().iWidth;

            // Draw the message length indicator if it is visible.
            if (  indicator->IndicatorState() != EAknIndicatorStateOff )
                {
                if ( indicatorWidthBefore != indicatorWidthAfter )
                    {
                    // If indicator width was changed, reposition all indicators.
                    PrioritizeIndicatorsL();
                    SizeChanged();
                    }
                DrawNow();
                }
            break;
            }
        }
    }

void CAknIndicatorContainer::DrawPictographArea()
    {
    TInt count = iIndicators->Count();

    for ( TInt i = 0; i < count; i++ )
        {
        CAknIndicator* indicator = iIndicators->At( i );
        // Draw the indicator if it is visible and contains pictographs.
        if ( indicator->TextIndicator() &&
             indicator->IndicatorState() != EAknIndicatorStateOff &&
             indicator->IsVisible() &&
             iExtension->iPictoInterface->Interface()->ContainsPictographs(
                *( indicator->iIndicatorText ) ) )
            {
            indicator->DrawDeferred();
            }
        }
    }


CAknPictographInterface* CAknIndicatorContainer::PictographInterface() const
    {
    return iExtension->iPictoInterface;
    }


EXPORT_C void  CAknIndicatorContainer::SetIncallBubbleFlags( const TInt& aFlags )
    {
    if ( aFlags & CIncallStatusBubble::ESBVisible )
        {
        if ( !iIncallBubble )
            {
            TRAP_IGNORE( CreateIncallBubbleL() );
            }

        if ( iIncallBubble )
            {
            iIncallBubble->SetFlags( aFlags );
            }
        }
    else
        {
        // RAM optimization, delete if not shown.
        delete iIncallBubble;
        iIncallBubble = NULL;
        }
    HandleStatusPaneSizeChange();
    }


EXPORT_C void CAknIndicatorContainer::HandleStatusPaneSizeChange()
    {
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if ( statusPane && iIncallBubble )
        {
        // In CDMA, the Phone app is on foreground during incall lock state
        // In GSM/WCDMA the Autolock application is on foreground

        // Nowdays Autolock itself takes care of the visibility
        const TBool showIncallIndicatorInLockState = EFalse;

        TBool showIncallIndicatorInIdle =
            iExtension->iIncallBubbleAllowedInIdle &&
            !iExtension->iIncallBubbleDisabled;

        TBool showIncallIndicatorInUsual =
            iExtension->iIncallBubbleAllowedInUsual &&
            !iExtension->iIncallBubbleDisabled;

        TBool visible = EFalse;

        TBool usualStatuspane = AknStatuspaneUtils::UsualLayoutActive();
        TBool idleStatuspane  = AknStatuspaneUtils::IdleLayoutActive();

        // Call bubble is never displayed if video telephony is
        // on the foreground.
        TInt currentLayoutResId = statusPane->CurrentLayoutResId();
        TBool vtStatuspane =
            ( currentLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_VT ||
              currentLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED );

       if ( statusPane->IsVisible() && iExtension->iIsForeground &&
            ( ( usualStatuspane && showIncallIndicatorInUsual ) ||
              ( idleStatuspane && showIncallIndicatorInIdle && !vtStatuspane ) ) )
            {
            // Incall bubble window is shown only in the usual layout when status
            // pane is shown. Exception for this rule: The bubble is shown also
            // when autolock application is in the front even if the idle
            // layout is visible.
            visible = ( iIncallBubble->Flags() & CIncallStatusBubble::ESBVisible );
            }

        IncallBubbleSizeChanged( showIncallIndicatorInLockState );
        iIncallBubble->MakeVisible( visible );
        }
    }


//-----------------------------------------------------------------------------
// CAknIndicatorContainer::HandleResourceChange
//-----------------------------------------------------------------------------
//
EXPORT_C void CAknIndicatorContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );

    if ( aType == KEikMessageFadeAllWindows && iIncallBubble )
        {
        CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
        iIncallBubble->SetFaded( statusPane->IsFaded() );
        }

    if ( aType == KEikColorResourceChange || aType == KAknsMessageSkinChange )
        {
        DrawDeferred();
        }
    else if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SizeChanged();
        DrawDeferred();
        }

    if ( iIncallBubble )
        {
        iIncallBubble->HandleResourceChange( aType );
        }
    }


//-----------------------------------------------------------------------------
// CAknIndicatorContainer::SizeChanged
//-----------------------------------------------------------------------------
//
EXPORT_C void CAknIndicatorContainer::SizeChanged()
    {
    // No fading if staconpane is active and in few other cases too...
    if ( iIndicatorContext == EUniversalIndicators )
        {
        SetContainerWindowNonFading(
            AknStatuspaneUtils::ExtendedStaconPaneActive() ||
            ( AknStatuspaneUtils::StaconPaneActive() &&
              !AknStatuspaneUtils::IdleLayoutActive() ) );
        }

    AknsUtils::RegisterControlPosition( this );
    if ( iExtension && DrawableWindow() )
        {
        iExtension->iPositionRelativeToScreen = PositionRelativeToScreen();
        }

    // Select right layout modes for indicators.
    // This is now done always to ensure right layout mode.
    SetupIndicatorLayoutModes();

    // HandleStatusPaneSizeChange() is called here always to check
    // incall bubble visibility because status pane size change is
    // not only case when it changes.
    HandleStatusPaneSizeChange();

    // Check if layout is mirrored and the context
    // of the indicators is mirrorable.
    if ( AknLayoutUtils::LayoutMirrored() &&
         ( iIndicatorContext == EUniversalIndicators ||
           iIndicatorContext == ENaviPaneEditorIndicators ||
           iIndicatorContext == EQueryEditorIndicators ) )
        {
        iAlignment = TIndicatorAlignment( ELeft );
        }
    else
        {
        iAlignment = TIndicatorAlignment( ERight );
        }

    TRect containerRect( Rect() );

    if ( containerRect.IsEmpty() )
        {
        return;
        }

    // Set faders off by default (only used in stacon)
    if ( iIndicatorContext == EUniversalIndicators )
        {
        TInt count = iIndicators->Count();
        for ( TInt ii = 0; ii < count; ii++ )
            {
            CAknIndicator* indicator = iIndicators->At( ii );
            if ( indicator )
                {
                indicator->SetIndicatorFader( NULL );
                }
            }
        }

    TBool idleLayout           = AknStatuspaneUtils::IdleLayoutActive();
    TBool smallLayout          = EFalse;
    TBool flatLayout           = EFalse;
    TBool extendedFlatLayout   = EFalse;
    TBool staconLayout         = EFalse;
    TBool extendedStaconLayout = EFalse;
    TBool hdLayout             = EFalse;
    TBool extendedLayout       = EFalse;

    if ( AknStatuspaneUtils::SmallLayoutActive() )
        {
        smallLayout = ETrue;
        }
    else if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        flatLayout         = ETrue;
        extendedFlatLayout = !AknLayoutUtils::PenEnabled() &&
                             AknStatuspaneUtils::ExtendedFlatLayoutActive();
        hdLayout           = AknStatuspaneUtils::HDLayoutActive();
        }
    else if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        staconLayout         = ETrue;
        extendedStaconLayout = AknStatuspaneUtils::ExtendedStaconPaneActive();
        }
    else
        {
        hdLayout       = AknStatuspaneUtils::HDLayoutActive();
        extendedLayout = AknStatuspaneUtils::ExtendedLayoutActive();
        }

    switch ( iIndicatorContext )
        {
        case ENaviPaneEditorIndicators:
            {
            if ( smallLayout )
                {
                SizeChangedInSmallStatusPane();
                }
            else if ( staconLayout &&
                      !idleLayout )
                {
                SizeChangedInStaconPane();
                }
            else if ( hdLayout )
                {
                SizeChangedInExtendedStatusPane();
                }
            else
                {
                SizeChangedInNormalStatusPane();
                }
            break;
            }

        case EUniversalIndicators:
            {
            if ( extendedLayout )
                {
                if ( idleLayout && !hdLayout )
                    {
                    SizeChangedInIdleExtendedStatusPane();
                    }
                else
                    {
                    SizeChangedInExtendedStatusPane();
                    }
                }
            else if ( flatLayout )
                {
                if ( extendedFlatLayout )
                    {
                    // Extended flat status pane layout.
                    SizeChangedInExtendedStatusPane();
                    }
                else
                    {
                    // Old flat status pane layout.
                    SizeChangedInFlatStatusPane();
                    }
                }
            else if ( staconLayout )
                {
                if ( extendedStaconLayout )
                    {
                    // Extended stacon layout.
                    SizeChangedInExtendedStatusPane();
                    }
                else if ( !idleLayout )
                    {
                    // Old stacon layout.
                    SizeChangedInStaconPane();
                    }
                else
                    {
                    SizeChangedInNormalStatusPane();
                    }
                }
            else if ( idleLayout &&
                      Layout_Meta_Data::IsLandscapeOrientation() &&
                      Size().iWidth < Size().iHeight )
                {
                // Universal indicator container in idle landscape
                // using vertical indicators.
                SizeChangedInIdleVertical();
                }
            else
                {
                // Normal status pane by default.
                SizeChangedInNormalStatusPane();
                }
            break;
            }

        default:
            {
            if ( hdLayout )
                {
                SizeChangedInExtendedStatusPane();
                }
            else
                {
                // Normal status pane by default.
                SizeChangedInNormalStatusPane();
                }
            break;
            }
        }
    }

EXPORT_C void CAknIndicatorContainer::PositionChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    }

EXPORT_C TInt CAknIndicatorContainer::CountComponentControls() const
    {
    return (iIndicatorsShown);
    }


EXPORT_C CCoeControl* CAknIndicatorContainer::ComponentControl(TInt aIndex) const
    {
    TInt count = iIndicators->Count();

    TInt ii = 0;
    for (ii = 0; (ii < count) && (aIndex >= 0); ii++)
        {
        if ( iIndicators->At(ii)->IndicatorState() && (iIndicators->At(ii)->Priority() != KIndicatorNotShown))
            {
            aIndex--;
            }
        }

    if ( ii > 0 )
        {
        return iIndicators->At(--ii);
        }
    else
        {
        return NULL;
        }
    }


EXPORT_C void CAknIndicatorContainer::Draw( const TRect& /*aRect*/ ) const
    {
    if ( iExtension->iIsActiveIdle )
        {
        return;
        }

    // Don't allow normal background drawing if
    // background is already drawn with a background drawer.
    const MCoeControlBackground* backgroundDrawer = FindBackground();
    if ( backgroundDrawer )
        {
        return;
        }
        
    CWindowGc& gc = SystemGc();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    TRect rect( Rect() );
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );

    //
    // S60 flat statuspane
    //
    if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        if ( iIndicatorContext == EUniversalIndicators )
            {
            if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
                {
                gc.SetPenStyle( CGraphicsContext::ENullPen );
                gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                gc.SetBrushColor(
                    AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
                gc.DrawRect( rect );
                }

            if( iIndicatorsShown &&
                iExtension &&
                AknStatuspaneUtils::IdleLayoutActive() &&
                !AknStatuspaneUtils::ExtendedFlatLayoutActive() &&
                !AknStatuspaneUtils::HDLayoutActive() )
                {
                TRect fadeRect( rect );
                // Draw fade if there are indicators
                if ( iLayoutOrientation == EVertical &&
                     Layout_Meta_Data::IsLandscapeOrientation() )
                    {
                    AknsDrawUtils::DrawCachedImage(
                        skin,
                        gc,
                        fadeRect,
                        KAknsIIDQgnGrafIdleFadeLsc );
                    }
                else if ( iLayoutOrientation == EHorizontal )
                    {
                    AknsDrawUtils::DrawCachedImage(
                        skin,
                        gc,
                        fadeRect,
                        KAknsIIDQgnGrafIdleFade );
                    }
                }
            }
        else if ( iIndicatorContext == ENaviPaneEditorIndicators )
            {
            if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
                {
                gc.SetPenStyle( CGraphicsContext::ENullPen );
                gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                gc.SetBrushColor(
                    AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
                gc.DrawRect( rect );
                }
            }
        else
            {
            gc.SetBrushColor( AKN_LAF_COLOR( 0 ) );
            AknsDrawUtils::Background( skin, cc, this, gc, rect );
            }

        return;
        }


    //
    // S60 staconpane
    //
    if (AknStatuspaneUtils::StaconPaneActive() &&
       (iIndicatorContext == EUniversalIndicators || iIndicatorContext == ENaviPaneEditorIndicators))
        {
        if (iIndicatorContext == ENaviPaneEditorIndicators)
            {
            if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
                {
                gc.SetPenStyle(CGraphicsContext::ENullPen);
                gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
                gc.SetBrushColor(AKN_LAF_COLOR(KStatusPaneBackgroundGraphicsColorUsual) );
                gc.DrawRect(rect);
                }
            }

        else if ( iIndicatorContext == EUniversalIndicators )
            {
            if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
                {
                gc.SetPenStyle(CGraphicsContext::ENullPen);
                gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
                gc.SetBrushColor(AKN_LAF_COLOR(KStatusPaneBackgroundGraphicsColorUsual) );
                gc.DrawRect(rect);
                }


            if( iIndicatorsShown &&
                iExtension &&
                AknStatuspaneUtils::IdleLayoutActive() &&
                !AknStatuspaneUtils::ExtendedStaconPaneActive())
                {
                TRect fadeRect( rect );
                if (iLayoutOrientation == EHorizontal)
                    {
                    // Always this fade
                    AknsDrawUtils::DrawCachedImage( skin, gc, fadeRect,
                        KAknsIIDQgnGrafIdleFade );
                    }
               else
                    {
                    AknsDrawUtils::DrawCachedImage( skin, gc, fadeRect,
                        KAknsIIDQgnGrafIdleFadeLsc );

                    }
                }
            }
        else
            {
            // Draw background for query editor indicators
            gc.SetBrushColor(AKN_LAF_COLOR(0));
            AknsDrawUtils::Background( skin, cc, this, gc, rect );
            }
        return;
        }

    //
    // Extended S60 statuspane
    //
    if (AknStatuspaneUtils::ExtendedLayoutActive())
        {
        if( CAknEnv::Static()->TransparencyEnabled() )
            {
            AknsDrawUtils::Background( skin, cc, this, gc, rect, KAknsDrawParamNoClearUnderImage );
            }
        else
            {
            AknsDrawUtils::Background( skin, cc, this, gc, rect );
            }
        return;
        }

    //
    // Default S60 statuspane
    //
    if ( iIndicatorContext == EUniversalIndicators )
        {
        // Draw background for universal indicator pane
        gc.SetBrushColor(AKN_LAF_COLOR(0)); // Universal indicator background color
        AknsDrawUtils::Background( skin, cc, this, gc, rect );

        if( (iLayoutOrientation == EHorizontal) && iIndicatorsShown && iExtension && !AknStatuspaneUtils::StaconPaneActive())
            {
            if (AknStatuspaneUtils::IdleLayoutActive())
                {
                TRect fadeRect( rect );
                // Draw fade if there are indicators
                AknsDrawUtils::DrawCachedImage( skin, gc, fadeRect,
                    KAknsIIDQgnGrafIdleFade );
                }
            }
        }
    if ( iIndicatorContext != EUniversalIndicators )
        {
        if ( iIndicatorContext == ENaviPaneEditorIndicators )
            {
            AknsDrawUtils::Background( skin, cc, this, gc, rect );
            }
        else
            {
            // Draw background for query editor indicators
            gc.SetBrushColor(AKN_LAF_COLOR(0));
            if( CAknEnv::Static()->TransparencyEnabled() )
                {
                AknsDrawUtils::Background( skin, cc, this, gc, rect, KAknsDrawParamNoClearUnderImage );
                }
            else
                {
                AknsDrawUtils::Background( skin, cc, this, gc, rect );
                }
            }
        }
    }

EXPORT_C void CAknIndicatorContainer::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    CAknControl::HandlePointerEventL( aPointerEvent );

    if ( AknLayoutUtils::PenEnabled() && iExtension )
        {
        TRect rect( Rect() );

        // The indicator popup is launched if both the down and up
        // pointer events happen in the indicator pane area.
        switch ( aPointerEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                {
                // if indicator's rect contains pointer down position
                if ( rect.Contains( aPointerEvent.iPosition ) )
                    {
                    // set flag that down was inside indicator
                    iExtension->iFlags |=
                        EAknIndicatorsButton1DownInIndicatorPaneRect;

                    if ( iIndicatorContext == EUniversalIndicators &&
                         iExtension->iFlags & EAknIndicatorsButton1DownInIndicatorPaneRect
                          )
                        {
                        MTouchFeedback* feedback = MTouchFeedback::Instance();

                        if ( feedback )
                            {
                            feedback->InstantFeedback( this, ETouchFeedbackSensitiveButton );
                            }
                        }
                    }
                break;
                }

            case TPointerEvent::EButton1Up:
                {
                // Currently the small digital clock pane and universal
                // indicator pane are regarded as one touch responsive area from
                // which the universal indicator popup should open on tap,
                // so upon pointer up event it must be checked here if
                // the down event happened inside this control, but the up event
                // inside digital clock pane area.
                CEikStatusPaneBase* sp = CEikStatusPaneBase::Current();
                TRect clockRect( 0, 0, 0, 0 );

                if ( sp )
                    {
                    CCoeControl* clockPane = sp->ContainerControlL(
                        TUid::Uid( EEikStatusPaneUidDigitalClock ) );
                    if ( clockPane )
                        {
                        clockRect = TRect( clockPane->PositionRelativeToScreen(),
                                           clockPane->Size() );
                        }
                    }

                // if indicator's rect contains pointer up position
                if ( iIndicatorContext == EUniversalIndicators &&
                     ( ( iExtension->iFlags & EAknIndicatorsButton1DownInIndicatorPaneRect &&
                         rect.Contains( aPointerEvent.iPosition ) ) ||
                       clockRect.Contains( aPointerEvent.iParentPosition ) ) )
                    {
                    MTouchFeedback* feedback = MTouchFeedback::Instance();
                    if ( feedback )
                        {
                        feedback->InstantFeedback( this,
                                                   ETouchFeedbackSensitiveButton,
                                                   ETouchFeedbackVibra,
                                                   aPointerEvent );
                        }
                    CAknSmallIndicator* indicatorNotifier = CAknSmallIndicator::NewLC( TUid::Uid( 0 ) );
                    indicatorNotifier->HandleIndicatorTapL();
                    CleanupStack::PopAndDestroy( indicatorNotifier );
                    }
                // Up happened, reset button down flag
                iExtension->iFlags &=
                    ( ~EAknIndicatorsButton1DownInIndicatorPaneRect );
                break;
                }

            default:
                {
                break;
                }
            }
        }
    }

EXPORT_C void* CAknIndicatorContainer::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

void CAknIndicatorContainer::Reserved_1()
    {}


void CAknIndicatorContainer::PrioritizeIndicatorsL()
    {
    iPreviousLayoutOrientation = iLayoutOrientation;

    TInt count = iIndicators->Count();
    if (count < 2)
        {
        return;
        }

    CAknIndicator* temp;
    for(TInt ii = 1; ii < count; ii++)
        {
        temp = iIndicators->At(ii);
        TInt tempPriority = temp->Priority();
        if (tempPriority >= 0)
            {
            for(TInt jj = 0; jj <= ii; jj++)
                {
                if (tempPriority < iIndicators->At(jj)->Priority())
                    {
                    iIndicators->Delete( ii );
                    CleanupStack::PushL( temp );
                    iIndicators->InsertL( jj, temp );
                    CleanupStack::Pop( temp );
                    break;
                    }
                else if ( jj == (ii-1) )
                    {
                    break;
                    }
                }
            }
        }
    }


TInt CAknIndicatorContainer::TickerCallback(TAny* aThis)
    {
    return static_cast<CAknIndicatorContainer*>(aThis)->DoTick();
    }

TInt CAknIndicatorContainer::DoTick()
    {
    if (iAnimatedIndicatorsShown > 0)
        {
        TInt count = iIndicators->Count();

        TInt ii = 0;
        for (ii = 0; ii < count; ii++)
            {
            if ( iIndicators->At(ii)->IndicatorState() == MAknIndicator::EIndicatorAnimate && (iIndicators->At(ii)->Priority() != KIndicatorNotShown))
                {
                iIndicators->At(ii)->Animate();
                }
            }
        iSynchronizingValue += 1;
        if (iSynchronizingValue >= 185794560) // This number can be divided with 2,4,6,8,10,12,14,16 and 18
            {
            iSynchronizingValue = 0;
            }

        DrawDeferred(); // Must be DrawDeferred (not DrawNow) so that we don't block application thread in high load situations
        }
    return ETrue;
    }


void CAknIndicatorContainer::IncallBubbleSizeChanged(
    TBool /*aAllowIdleStateBubble*/ )
    {
    if ( iIncallBubble &&
         iIncallBubble->Flags() & CIncallStatusBubble::ESBVisible )
        {
        TAknWindowLineLayout layout;
        if ( iIndicatorsShown > 0 )
            {
            // Position of incall bubble if universal small indicator(s) present.
            // This position is also used when the bubble is shown with idle layout
            // when autolock application is activated and it is front application.
            layout = AknLayoutScalable_Apps::popup_call_status_window( 0 ).LayoutLine();
            }
        else
            {
            // Position of incall bubble if universal small indicator pane is empty.
            layout = AknLayoutScalable_Apps::popup_call_status_window( 1 ).LayoutLine();
            }

        // screen
        TRect screenRect( iAvkonAppUi->ApplicationRect() );
        TAknLayoutRect layoutRect;

        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            TInt topVariety = 8; // default to flat landscape statuspane variety
            if ( AknStatuspaneUtils::StaconPaneActive() )
                {
                topVariety = 2;
                }

            TInt skvariety = 6;
            if ( AknStatuspaneUtils::StaconPaneActive() )
                {
                if ( AknStatuspaneUtils::StaconSoftKeysRight() )
                    {
                    skvariety = 6;
                    }
                else
                    {
                    skvariety = 8;
                    }
                }
            else if ( AknStatuspaneUtils::FlatLayoutActive() ||
                      AknStatuspaneUtils::HDLayoutActive() )
                {
                skvariety = 10;
                }

            if ( iIndicatorsShown > 0 )
                {
                // If indicators are shown we use one bigger variety index. But for "10" there is not such.
                if ( skvariety != 10 )
                    {
                    skvariety++;
                    }
                }

            layout = AknLayoutScalable_Apps::popup_call_status_window( skvariety ).LayoutLine();

            // To keep the call bubble in indicator pane area,
            // otherwise it'll get on top of the title pane in A&H layouts.
            if ( AknLayoutUtils::LayoutMirrored() )
                {
                TInt tmp = layout.il;
                layout.il = layout.ir;
                layout.ir = tmp;
                }

            TAknWindowComponentLayout topLayout = AknLayoutScalable_Avkon::area_top_pane( topVariety );
            layoutRect.LayoutRect( screenRect, topLayout );
            TRect topLayoutRect( layoutRect.Rect() );
            layoutRect.LayoutRect( topLayoutRect, layout );
            }
        else
            {
            // Incall bubble
            layoutRect.LayoutRect( screenRect, layout );
            }

        TRect rect( layoutRect.Rect() );

        // SizeChanged of incall indicator is heavyweight, so set size only if 
		// necessary.
        if ( rect != TRect( iIncallBubble->Position(), iIncallBubble->Size() ) )
            {
            iIncallBubble->SetRect( rect );
            }
        }
    }

EXPORT_C void CAknIndicatorContainer::SetIndicatorValue(TUid aIndicatorId, TInt aValue, TInt aMaxValue)
    {
    TInt count = iIndicators->Count();
    for(TInt ii = 0; ii < count; ii++)
        {
        CAknIndicator* indicator = iIndicators->At(ii);
        if ( indicator->Uid() == aIndicatorId )
            {
            indicator->SetIndicatorValue(aValue, aMaxValue);
            // Draw the indicator if it is visible.
            if (  indicator->IndicatorState() != EAknIndicatorStateOff )
                {
                DrawNow();
                }
            break;
            }
        }
    }

void CAknIndicatorContainer::SizeChangedInSmallStatusPane()
    {
    iLayoutOrientation = EHorizontal; // always horizontal

    // only editor indicators are supported in small statuspane
    if (iIndicatorContext != ENaviPaneEditorIndicators)
        {
        return;
        }

    // Gprs indicator is a special case. It is drawn
    // to other spane by the system. Check here that correct
    // statuspane layout is enabled and switch if needed
    //
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    TInt statusPaneCurrentLayoutResourceId = 0;
    if ( statusPane )
        {
        statusPaneCurrentLayoutResourceId = statusPane->CurrentLayoutResId();
        }
    TInt last = iIndicators->Count() - 1;

    // Update the status pane layout if needed to correspond the
    // visibility of the GPRS indicator. If status pane layout is changed
    // this function will be called again.
    TBool layoutChanged = EFalse;
    TRAP_IGNORE( layoutChanged = UpdateSmallLayoutL() );
    if ( layoutChanged )
        {
        return; // this method will be called again
        }

    TBool layoutMirrored( AknLayoutUtils::LayoutMirrored() );

    TRect containerRect( Rect() );

    // screen
    TRect screenRect = iAvkonAppUi->ApplicationRect();

    // small statuspane
    TRect smallStatusPaneRect;
    AknLayoutUtils::LayoutMetricsRect(
        AknLayoutUtils::EStatusPane, smallStatusPaneRect );

    // small statuspane, wait pane
    TAknLayoutRect smallStatusWaitPaneLayoutRect;
    smallStatusWaitPaneLayoutRect.LayoutRect(
        smallStatusPaneRect, AknLayoutScalable_Avkon::status_small_wait_pane( 0 ) );
    TRect smallStatusWaitPaneRect( smallStatusWaitPaneLayoutRect.Rect() );

    // small statuspane, globe
    TAknLayoutRect smallStatusWmlGlobeLayoutRect;
    smallStatusWmlGlobeLayoutRect.LayoutRect(
        smallStatusPaneRect, AknLayoutScalable_Avkon::status_small_pane_g4( 0 ) );
    TRect smallStatusWmlGlobeRect( smallStatusWmlGlobeLayoutRect.Rect() );

    // small statuspane, gprs indicator
    TAknLayoutRect smallStatusGprsLayoutRect;
    smallStatusGprsLayoutRect.LayoutRect(
        smallStatusPaneRect, AknLayoutScalable_Avkon::status_small_pane_g2( 0 ) );
    TRect smallStatusGprsRect( smallStatusGprsLayoutRect.Rect() );

    // small statuspane, secure state indicator
    TAknLayoutRect smallStatusSecureStateLayoutRect;
    smallStatusSecureStateLayoutRect.LayoutRect(
        smallStatusPaneRect, AknLayoutScalable_Avkon::status_small_pane_g3( 0 ) );
    TRect smallStatusSecureStateRect( smallStatusSecureStateLayoutRect.Rect() );


    // small statuspane, texts
    TAknTextComponentLayout smallStatusTextLayout;
    if ( statusPaneCurrentLayoutResourceId ==
            AVKONENV->StatusPaneResIdForCurrentLayout( R_AVKON_STATUS_PANE_LAYOUT_SMALL ) )
        {
        smallStatusTextLayout = AknLayoutScalable_Avkon::status_small_pane_t1( 0 );
        }
    else // gprs indicator visible
        {
        smallStatusTextLayout = AknLayoutScalable_Avkon::status_small_pane_t1( 1 );
        }

    TAknLayoutText textLayout;
    textLayout.LayoutText( smallStatusPaneRect, smallStatusTextLayout );
    TRect smallStatusTextRect( textLayout.TextRect() );

    TInt textIndicatorLeftOffset = smallStatusTextRect.iTl.iX;

    // Take possible touch pane into account.
    TInt textIndicatorVerticalOffset =
        ( containerRect.Height() - smallStatusTextRect.Height() ) / 2;

    TInt waitBarIndicatorLeftOffset     = smallStatusWaitPaneRect.iTl.iX;
    TInt progressBarIndicatorLeftOffset = smallStatusWaitPaneRect.iTl.iX;
    TInt wmlWaitGlobeLeftOffset         = smallStatusWmlGlobeRect.iTl.iX;

    if ( layoutMirrored )
        {
        waitBarIndicatorLeftOffset =
            smallStatusPaneRect.iBr.iX - smallStatusWaitPaneRect.iBr.iX;

        progressBarIndicatorLeftOffset =
            smallStatusPaneRect.iBr.iX - smallStatusWaitPaneRect.iBr.iX;

        wmlWaitGlobeLeftOffset =
            smallStatusPaneRect.iBr.iX - smallStatusWmlGlobeRect.iBr.iX;
        }


    if ( statusPaneCurrentLayoutResourceId ==
            AVKONENV->StatusPaneResIdForCurrentLayout(
                R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE ) )
        {
        // If GPRS indicator is visible then a larger offset is needed
        // for text indicator because there are no pixels empty in
        // the right side of the GPRS status icon as the layout spec
        // requires in this case.
        if ( textIndicatorLeftOffset < KMinSpaceBetweenIconsInPixels )
            {
            textIndicatorLeftOffset = KMinSpaceBetweenIconsInPixels;
            }

        // This makes the globe indicator position adjusted to
        // middle if GPRS indicator is in either side
        if( !layoutMirrored )
            {
            wmlWaitGlobeLeftOffset -= smallStatusGprsRect.Width();
            }
        }

    // Modify containerRect if alignment is Right.
    // For Left aligned no need to modify containerRect.
    if ( iAlignment == TIndicatorAlignment( ERight ) )
        {
        containerRect.iBr.iX -= 3; // Right margin of editor indicators
        containerRect.iTl.iX += 0; // Left margin of editor indicators
        }

    iIndicatorsShown                = 0;
    iAnimatedIndicatorsShown        = 0;
    TBool textIndicatorOffsetNeeded = ETrue;

    TRect rectForRightSideIndicators( containerRect.iBr.iX,
                                      containerRect.iTl.iY,
                                      containerRect.iBr.iX,
                                      containerRect.iBr.iY );

    TRect rectForLeftSideIndicators( containerRect.iTl.iX,
                                     containerRect.iTl.iY,
                                     containerRect.iTl.iX,
                                     containerRect.iBr.iY );

    TRect rectForMiddleIndicators( wmlWaitGlobeLeftOffset,
                                   containerRect.iTl.iY,
                                   wmlWaitGlobeLeftOffset,
                                   containerRect.iBr.iY );

    for ( TInt ii = 0; ii <= last; ii++ )
        {
        CAknIndicator* indicator = iIndicators->At( ii );
        TInt uid                 = indicator->Uid().iUid;
        TInt indicatorPosition   = 0;

        // Decide here how indicators are positioned.
        // Default is right side.
        indicatorPosition = indicator->IndicatorPosition();

        // Check if indicator is not shown on current layout even it is set ON.
        if ( !indicator->IndicatorState() ||
             indicator->Priority() == KIndicatorNotShown )
            {
            continue;
            }

        // Check if this is GPRS indicator, it is never shown here
        // but is drawn to the signal pane by the system
        if ( uid == EAknNaviPaneEditorIndicatorGprs )
            {
            indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
            iIndicatorsShown++;
            continue;
            }

        // Handle offsets.
        TAknLayoutRect statusPaneIconSmallRect;
        statusPaneIconSmallRect.LayoutRect(
            smallStatusPaneRect, AknLayoutScalable_Avkon::status_small_icon_pane() );

        // Take possible touch pane into account
        TInt verticalOffset =
            ( containerRect.Height() - statusPaneIconSmallRect.Rect().Height() ) / 2;

        TInt leftOffset  = 0;  // default offset
        TInt rightOffset = 0;  // default offset

        TInt indicatorWidth  = indicator->IconSize().iWidth;  // default width
        TInt indicatorHeight = indicator->IconSize().iHeight; // default height

        if ( uid == EAknNaviPaneEditorIndicatorMessageInfo    ||
             uid == EAknNaviPaneEditorIndicatorWmlWindowsText ||
             uid == EAknNaviPaneEditorIndicatorMessageLength )
            {
            indicatorHeight = smallStatusTextRect.Height();
            verticalOffset  = textIndicatorVerticalOffset;
            // First text indicator needs horizontal offset.
            if ( textIndicatorOffsetNeeded )
                {
                leftOffset += textIndicatorLeftOffset;
                }

            textIndicatorOffsetNeeded = EFalse;
            }
        else if ( uid == EAknNaviPaneEditorIndicatorFileSize )
            {
            verticalOffset = textIndicatorVerticalOffset;

            // Need left offset in western, right offset in A&H layout.
            if ( layoutMirrored )
                {
                rightOffset = textIndicatorLeftOffset;
                }
            else
                {
                leftOffset  = KMinSpaceBetweenIconsInPixels;
                }
            }
        else if ( uid == EAknNaviPaneEditorIndicatorSecuredConnection )
            {
            verticalOffset =
                ( containerRect.Height() - smallStatusSecureStateRect.Height() ) / 2;

            // Because icon bitmap does not contain enough space,
            // increase offset as the layout spec states.
            if ( layoutMirrored )
                {
                leftOffset = KMinSpaceBetweenIconsInPixels;
                }
            else
                {
                rightOffset = KMinSpaceBetweenIconsInPixels;
                }

            textIndicatorOffsetNeeded      = EFalse;
            waitBarIndicatorLeftOffset     = 0;
            progressBarIndicatorLeftOffset = 0;
            }
        else if ( uid == EAknNaviPaneEditorIndicatorWmlWaitGlobe )
            {
            verticalOffset =
                ( containerRect.Height() - indicator->IconSize().iHeight ) / 2;
            indicatorWidth = smallStatusWmlGlobeRect.Width();
            }
        else if ( uid == EAknNaviPaneEditorIndicatorProgressBar )
            {
            indicatorWidth  = smallStatusWaitPaneRect.Width();
            indicatorHeight = smallStatusWaitPaneRect.Height();
            verticalOffset  = ( containerRect.Height() - indicatorHeight ) / 2;
            leftOffset      = progressBarIndicatorLeftOffset;
            textIndicatorOffsetNeeded = ETrue;
            }
        else if ( uid == EAknNaviPaneEditorIndicatorWaitBar )
            {
            indicatorWidth  = smallStatusWaitPaneRect.Width();
            indicatorHeight = smallStatusWaitPaneRect.Height();
            verticalOffset  = ( containerRect.Height() - indicatorHeight ) / 2;
            leftOffset      = waitBarIndicatorLeftOffset;
            textIndicatorOffsetNeeded = ETrue;
            }

        if ( layoutMirrored )
            {
            TInt temp   = leftOffset;
            leftOffset  = rightOffset;
            rightOffset = temp;
            }

        // Place indicators to the left side.
        if ( ( indicatorPosition == ELeftSide &&
               iAlignment == TIndicatorAlignment( ERight ) ) ||
             ( indicatorPosition == ERightSide &&
               iAlignment == TIndicatorAlignment( ELeft ) ) )
            {
            TRect requiredRect(
                rectForLeftSideIndicators.iBr.iX,
                rectForLeftSideIndicators.iTl.iY,
                rectForLeftSideIndicators.iBr.iX + leftOffset + indicatorWidth + rightOffset,
                rectForLeftSideIndicators.iBr.iY );

            // check if indicator fits
            TBool indicatorDoesNotFit =
                ( requiredRect.Intersects( rectForRightSideIndicators ) ||
                  requiredRect.Intersects( rectForMiddleIndicators )    ||
                  containerRect.iTl.iX > requiredRect.iTl.iX            ||
                  containerRect.iBr.iX < requiredRect.iBr.iX );

            if ( indicatorDoesNotFit &&
                 !indicator->DynamicTextIndicator() )
                {
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                iIndicatorsShown++;
                continue;
                }
            else
                {
                if ( indicator->DynamicTextIndicator() && indicatorDoesNotFit )
                    {
                    // Dynamic text indicators (not normal text indicators)
                    // can adjust to any size.
                    TInt maxWidthForDynamicTextIndicator =
                        containerRect.iBr.iX - requiredRect.iTl.iX;

                    if ( requiredRect.Intersects( rectForRightSideIndicators ) )
                        {
                        maxWidthForDynamicTextIndicator =
                            rectForRightSideIndicators.iTl.iX - requiredRect.iTl.iX;
                        }

                    if ( requiredRect.Intersects( rectForMiddleIndicators ) )
                        {
                        maxWidthForDynamicTextIndicator =
                            rectForMiddleIndicators.iTl.iX - requiredRect.iTl.iX;
                        }

                    indicator->SetExtent( TPoint( requiredRect.iTl.iX + leftOffset,
                                                  verticalOffset ),
                                          TSize( maxWidthForDynamicTextIndicator,
                                                 indicatorHeight ) );

                    rectForLeftSideIndicators.iBr.iX =
                        indicator->Position().iX + indicator->Size().iWidth;
                    }
                else
                    {
                    indicator->SetExtent( TPoint( requiredRect.iTl.iX + leftOffset,
                                                  verticalOffset ),
                                          TSize( indicatorWidth, indicatorHeight ) );

                    rectForLeftSideIndicators.iBr.iX = requiredRect.iBr.iX;
                    }
                }
            }


        // Place indicators to the right side.
        if ( ( indicatorPosition == ERightSide &&
               iAlignment == TIndicatorAlignment( ERight ) ) ||
             ( indicatorPosition == ELeftSide &&
               iAlignment == TIndicatorAlignment( ELeft ) ) )
            {
            TRect requiredRect(
                rectForRightSideIndicators.iTl.iX - leftOffset - indicatorWidth - rightOffset,
                rectForRightSideIndicators.iTl.iY,
                rectForRightSideIndicators.iTl.iX,
                rectForRightSideIndicators.iBr.iY );

             // Check if indicator fits.
             TBool indicatorDoesNotFit =
                 ( requiredRect.Intersects( rectForLeftSideIndicators ) ||
                   requiredRect.Intersects( rectForMiddleIndicators )   ||
                   containerRect.iTl.iX > requiredRect.iTl.iX           ||
                   containerRect.iBr.iX < requiredRect.iBr.iX );

            if ( indicatorDoesNotFit &&
                 !indicator->DynamicTextIndicator() )
                {
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                iIndicatorsShown++;
                continue;
                }
            else
                {
                if ( indicator->DynamicTextIndicator() && indicatorDoesNotFit )
                    {
                    // Dynamic text indicators (not normal text indicators)
                    // can adjust to any size.
                    TInt maxWidthForDynamicTextIndicator =
                        requiredRect.iBr.iX - containerRect.iTl.iX - leftOffset;

                    if ( requiredRect.Intersects( rectForLeftSideIndicators ) )
                        {
                        maxWidthForDynamicTextIndicator =
                            requiredRect.iBr.iX - rectForLeftSideIndicators.iBr.iX;
                        }

                    if ( requiredRect.Intersects( rectForMiddleIndicators ) )
                        {
                        maxWidthForDynamicTextIndicator =
                            requiredRect.iBr.iX - rectForMiddleIndicators.iBr.iX;
                        }

                    indicator->SetExtent(
                        TPoint( requiredRect.iBr.iX - maxWidthForDynamicTextIndicator - leftOffset,
                                verticalOffset ),
                        TSize( maxWidthForDynamicTextIndicator,
                               indicatorHeight ) );

                    rectForRightSideIndicators.iTl.iX = indicator->Position().iX;
                    }
                else
                    {
                    indicator->SetExtent( TPoint( requiredRect.iTl.iX + leftOffset,
                                                  verticalOffset),
                                          TSize( indicatorWidth, indicatorHeight ) );

                    rectForRightSideIndicators.iTl.iX = requiredRect.iTl.iX;
                    }
                }
            }


        // Place indicators to the middle, only indicator is wml wait globe.
        if ( indicatorPosition == EMiddle )
            {
            TRect requiredRect(
                rectForMiddleIndicators.iTl.iX,
                rectForMiddleIndicators.iTl.iY,
                rectForMiddleIndicators.iTl.iX + leftOffset + indicatorWidth + rightOffset,
                rectForMiddleIndicators.iBr.iY);

            // Check if indicator fits.
            if ( ( requiredRect.Intersects( rectForRightSideIndicators ) ||
                   requiredRect.Intersects( rectForLeftSideIndicators ) ) ||
                 ( rectForMiddleIndicators.Width() != 0 ) )
                {
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                iIndicatorsShown++;
                continue;
                }
            else
                {
                indicator->SetExtent( TPoint( rectForMiddleIndicators.iTl.iX + leftOffset,
                                              verticalOffset),
                                      TSize( indicatorWidth, indicatorHeight) );
                rectForMiddleIndicators.iTl.iX += rightOffset;
                rectForMiddleIndicators.iTl.iX += indicatorWidth;
                }
            }

        iIndicatorsShown++;

        if ( indicator->IndicatorState() == MAknIndicator::EIndicatorAnimate )
            {
            iAnimatedIndicatorsShown++;
            }
        } // for

    ResetAnimTicker( iExtension->iIsForeground );
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::SizeChangedInNormalStatusPane
// Handles size change events in normal status pane layouts.
// ---------------------------------------------------------------------------
//
void CAknIndicatorContainer::SizeChangedInNormalStatusPane()
    {
    TRect containerRect( Rect() );

    TInt height = containerRect.Height();
    TInt width  = containerRect.Width();

    // Find out if pane layout is horizontal or vertical
    // Following pane uses vertical layout:
    //   - System owned universal small indicator pane
    //     when status pane is in usual layout
    // Following panes use horizontal layout:
    //   - System owned universal small indicator pane
    //     when status pane is in idle layout
    //   - Navigation pane editor indicator pane
    //   - Query editor indicators
    iLayoutOrientation = ( height > width ) ? EVertical : EHorizontal;

    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );

    TAknWindowComponentLayout indicatorIconLayout(
        AknLayoutScalable_Avkon::indicator_pane_g1( isLandscape ) );

    if ( iIndicatorContext != EUniversalIndicators )
        {
        // Editor indicators
        if ( iAlignment == TIndicatorAlignment( ERight ) )
            {
            containerRect.iBr.iX -= 4; // Right margin of editor indicators
            containerRect.iTl.iX += 6; // Left margin of editor indicators
            }
        else
            {
            containerRect.iBr.iX -= 6; // Right margin of editor indicators
            containerRect.iTl.iX += 1; // Left margin of editor indicators
            }
        }
    else if ( iLayoutOrientation == EHorizontal )
        {
        TAknWindowLineLayout indicatorLayout = AknLayout::Indicator_pane_elements_Line_1();
        TAknLayoutRect indicatorLayoutRect;
        indicatorLayoutRect.LayoutRect(containerRect, indicatorLayout);
        TRect indicatorRect( indicatorLayoutRect.Rect() );

        // Layout adaptation layer does not work correctly. Access the layout data directly in
        // scalable UI...and calculate...
        TAknWindowLineLayout layout1( AknLayoutScalable_Avkon::indicator_pane_g1(0).LayoutLine() );

        indicatorLayoutRect.LayoutRect(containerRect, layout1);
        indicatorRect = indicatorLayoutRect.Rect();

        // variety 1 is only valid in landscape layouts
        if(Layout_Meta_Data::IsLandscapeOrientation())
            {
            TAknWindowLineLayout layout2 = AknLayoutScalable_Avkon::indicator_pane_g1(1).LayoutLine();
            indicatorLayoutRect.LayoutRect(containerRect, layout2);
            TRect rect2( indicatorLayoutRect.Rect() );
            indicatorRect.BoundingRect(rect2);
            }

        containerRect.iBr.iX = indicatorRect.iBr.iX;
        containerRect.iTl.iX = indicatorRect.iTl.iX;
        }

    // Available space for indicators
    TRect rect( containerRect );

    height = rect.Height();
    width  = rect.Width();

    TInt verticalIndicatorOffset        = rect.iTl.iY;
    TInt verticalOffsetForTextIndicator = verticalIndicatorOffset;

    TAknLayoutText layoutText;
    layoutText.LayoutText(
        Rect(),
        TAknWindowComponentLayout::ComposeText(
            AknLayoutScalable_Avkon::navi_text_pane( 0 ),
            AknLayoutScalable_Avkon::navi_text_pane_t1() ) );

    TAknLayoutRect editingIconLayoutRect;
    editingIconLayoutRect.LayoutRect(
        Rect(),
        TAknWindowComponentLayout::Compose(
            AknLayoutScalable_Avkon::navi_icon_pane( 0 ),
            AknLayoutScalable_Avkon::navi_icon_pane_g1() ) );

    if ( iIndicatorContext != EUniversalIndicators )
        {
        if ( iIndicatorContext == ENaviPaneEditorIndicators )
            {
            verticalIndicatorOffset += editingIconLayoutRect.Rect().iTl.iY;
            verticalOffsetForTextIndicator = layoutText.TextRect().iTl.iY;
            }
        // In query editor indicators have offset 0
        }
    else if ( iLayoutOrientation == EHorizontal )
        {
        TAknLayoutRect indicatorLayoutRect;
        indicatorLayoutRect.LayoutRect( containerRect, indicatorIconLayout );
        TRect indicatorRect( indicatorLayoutRect.Rect() );

        verticalIndicatorOffset += indicatorRect.iTl.iY;
        }

    TInt verticalOffset = verticalIndicatorOffset;

    // If layout orientation has been changed since last call,
    // prioritize indicators again.
    if ( iLayoutOrientation != iPreviousLayoutOrientation )
        {
        // Following leave is ignored.
        // In case of leave indicators are not maybe shown correctly.
        TRAP_IGNORE ( PrioritizeIndicatorsL() );
        }

    iIndicatorsShown         = 0;
    iAnimatedIndicatorsShown = 0;
    TInt last                = iIndicators->Count() - 1;

    TRect rectForRightSideIndicators( containerRect.iBr.iX,
                                      containerRect.iTl.iY,
                                      containerRect.iBr.iX,
                                      containerRect.iBr.iY );

    TRect rectForLeftSideIndicators( containerRect.iTl.iX,
                                     containerRect.iTl.iY,
                                     containerRect.iTl.iX,
                                     containerRect.iBr.iY );

    // Not really supported in this layout.
    TRect rectForMiddleIndicators( TRect( 0, 0, 0, 0 ) );


    for ( TInt ii = 0; ii <= last; ii++ )
        {
        CAknIndicator* indicator = iIndicators->At( ii );
        if ( !indicator->IndicatorState() ||
             indicator->Priority() == KIndicatorNotShown )
            {
            // Indicator is not shown on current layout even it is set ON.
            continue;
            }

        TInt uid = indicator->Uid().iUid;

        if ( uid == EAknNaviPaneEditorIndicatorSecuredConnection ||
             uid == EAknNaviPaneEditorIndicatorProgressBar       ||
             uid == EAknNaviPaneEditorIndicatorWmlWaitGlobe      ||
             uid == EAknNaviPaneEditorIndicatorGprs              ||
             uid == EAknNaviPaneEditorIndicatorFileSize          ||
             uid == EAknNaviPaneEditorIndicatorWaitBar           ||
             uid == EAknNaviPaneEditorIndicatorWlanAvailable     ||
             uid == EAknNaviPaneEditorIndicatorWlanActive        ||
             uid == EAknNaviPaneEditorIndicatorWlanActiveSecure )
            {
            // These indicators are not shown in this statuspane layout.
            indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
            iIndicatorsShown++;
            continue;
            }


        if ( iLayoutOrientation == EVertical )
            {
            // Highest priority indicator is put topmost.
            if ( height < indicator->IconSize().iHeight )
                {
                // Space for indicators is full.
                // Rest of low priority indicators are not shown.
                break;
                }
            // Position indicators side by side.
            if ( iAlignment == TIndicatorAlignment( ERight ) )
                {
                indicator->SetExtent( rect.iTl, indicator->IconSize() );
                }
            // If layout is left aligned, must leave one pixel to the left empty.
            else
                {
                indicator->SetExtent( TPoint( rect.iTl.iX + 1, rect.iTl.iY ),
                                      indicator->IconSize() );
                }
            rect.iTl.iY += indicator->IconSize().iHeight;
            height       = rect.Height();
            }
        else
            {
            // Code to set indicator positions starts,
            // supports dynamic text indicators.
            verticalOffset = verticalIndicatorOffset;

            // Decide here how indicators are positioned.
            // Default is right side.
            TInt indicatorPosition = indicator->IndicatorPosition();

            TInt leftOffset  = 0;  // default offset
            TInt rightOffset = 0;  // default offset

            TInt indicatorWidth  = indicator->IconSize().iWidth;  // default width
            TInt indicatorHeight = indicator->IconSize().iHeight; // default height

            TBool textIndicatorOffsetNeeded = ETrue;

            TInt textIndicatorLeftOffset = KMinSpaceBetweenIconsInPixels;

            if ( uid == EAknNaviPaneEditorIndicatorMessageInfo    ||
                 uid == EAknNaviPaneEditorIndicatorWmlWindowsText ||
                 uid == EAknNaviPaneEditorIndicatorMessageLength )
                {
                verticalOffset = verticalOffsetForTextIndicator;
                // First text indicator need horizontal offset.
                if ( textIndicatorOffsetNeeded )
                    {
                    leftOffset += textIndicatorLeftOffset;
                    }

                textIndicatorOffsetNeeded = EFalse;
                }

            if ( uid == EAknNaviPaneEditorIndicatorFileSize )
                {
                verticalOffset = verticalOffsetForTextIndicator;

                // Need left offset in western, right offset in A&H layout.
                if( AknLayoutUtils::LayoutMirrored() )
                    {
                    rightOffset = textIndicatorLeftOffset;
                    }
                else
                    {
                    leftOffset  = KMinSpaceBetweenIconsInPixels;
                    }
                }

            if( AknLayoutUtils::LayoutMirrored() )
                {
                TInt temp   = leftOffset;
                leftOffset  = rightOffset;
                rightOffset = temp;
                }

            // Place indicators to the leftside.
            if ( ( indicatorPosition == ELeftSide &&
                   iAlignment == TIndicatorAlignment( ERight ) ) ||
                 ( indicatorPosition == ERightSide &&
                   iAlignment == TIndicatorAlignment( ELeft ) ) )
                {
                TRect requiredRect(
                    rectForLeftSideIndicators.iBr.iX,
                    rectForLeftSideIndicators.iTl.iY,
                    rectForLeftSideIndicators.iBr.iX + leftOffset + indicatorWidth + rightOffset,
                    rectForLeftSideIndicators.iBr.iY );

                // Check if indicator fits.
                TBool indicatorDoesNotFit =
                    ( requiredRect.Intersects( rectForRightSideIndicators ) ||
                      requiredRect.Intersects( rectForMiddleIndicators )    ||
                      containerRect.iTl.iX > requiredRect.iTl.iX            ||
                      containerRect.iBr.iX < requiredRect.iBr.iX );

                if ( indicatorDoesNotFit &&
                     !indicator->DynamicTextIndicator() )
                    {
                    indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                    iIndicatorsShown++;
                    continue;
                    }
                else
                    {
                    if ( indicator->DynamicTextIndicator() && indicatorDoesNotFit )
                        {
                        // Dynamic text indicators (not normal text indicators)
                        // can adjust to any size.
                        TInt maxWidthForDynamicTextIndicator =
                            containerRect.iBr.iX - requiredRect.iTl.iX;

                        if ( requiredRect.Intersects( rectForRightSideIndicators ) )
                            {
                            maxWidthForDynamicTextIndicator =
                                rectForRightSideIndicators.iTl.iX - requiredRect.iTl.iX;
                            }

                        if ( requiredRect.Intersects( rectForMiddleIndicators ) )
                            {
                            maxWidthForDynamicTextIndicator =
                                rectForMiddleIndicators.iTl.iX - requiredRect.iTl.iX;
                            }

                        indicator->SetExtent(
                            TPoint( requiredRect.iTl.iX + leftOffset, verticalOffset ),
                            TSize( maxWidthForDynamicTextIndicator, indicatorHeight ) );

                        rectForLeftSideIndicators.iBr.iX =
                            indicator->Position().iX + indicator->Size().iWidth;
                        }
                    else
                        {
                        indicator->SetExtent(
                            TPoint( requiredRect.iTl.iX + leftOffset, verticalOffset ),
                            TSize( indicatorWidth, indicatorHeight ) );
                        rectForLeftSideIndicators.iBr.iX = requiredRect.iBr.iX;
                        }
                    }
                }


            // Place indicators on the right side.
            if ( ( indicatorPosition == ERightSide &&
                   iAlignment == TIndicatorAlignment( ERight ) ) ||
                 ( indicatorPosition == ELeftSide &&
                   iAlignment == TIndicatorAlignment( ELeft ) ) )
                {
                TRect requiredRect(
                    rectForRightSideIndicators.iTl.iX - leftOffset - indicatorWidth - rightOffset,
                    rectForRightSideIndicators.iTl.iY,
                    rectForRightSideIndicators.iTl.iX,
                    rectForRightSideIndicators.iBr.iY );

                // Check if indicator fits.
                 TBool indicatorDoesNotFit =
                     ( requiredRect.Intersects( rectForLeftSideIndicators ) ||
                       requiredRect.Intersects( rectForMiddleIndicators )   ||
                       containerRect.iTl.iX > requiredRect.iTl.iX           ||
                       containerRect.iBr.iX < requiredRect.iBr.iX );

                if ( indicatorDoesNotFit &&
                     !indicator->DynamicTextIndicator() )
                    {
                    indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                    iIndicatorsShown++;
                    continue;
                    }
                else
                    {
                    if ( indicator->DynamicTextIndicator() && indicatorDoesNotFit )
                        {
                        // Dynamic text indicators (not normal text indicators)
                        // can adjust to any size.
                        TInt maxWidthForDynamicTextIndicator =
                            requiredRect.iBr.iX - containerRect.iTl.iX - leftOffset;

                        if ( requiredRect.Intersects( rectForLeftSideIndicators ) )
                            {
                            maxWidthForDynamicTextIndicator =
                                requiredRect.iBr.iX - rectForLeftSideIndicators.iBr.iX;
                            }

                        if ( requiredRect.Intersects( rectForMiddleIndicators ) )
                            {
                            maxWidthForDynamicTextIndicator =
                                requiredRect.iBr.iX - rectForMiddleIndicators.iBr.iX;
                            }

                        indicator->SetExtent(
                            TPoint( requiredRect.iBr.iX - maxWidthForDynamicTextIndicator + leftOffset,
                                    verticalOffset ),
                            TSize( maxWidthForDynamicTextIndicator, indicatorHeight ) );
                        rectForRightSideIndicators.iTl.iX = indicator->Position().iX;
                        }
                    else
                        {
                        indicator->SetExtent(
                            TPoint( requiredRect.iTl.iX + leftOffset, verticalOffset ),
                            TSize( indicatorWidth, indicatorHeight ) );
                        rectForRightSideIndicators.iTl.iX = requiredRect.iTl.iX;
                        }
                    }
                }


            // Place indicators to the middle if any.
            if ( indicatorPosition == EMiddle )
                {
                // Not supported for now, always set size to zero.
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                iIndicatorsShown++;
                }
            }


        iIndicatorsShown++;
        if ( indicator->IndicatorState() == MAknIndicator::EIndicatorAnimate )
            {
            iAnimatedIndicatorsShown++;
            }
        }

    // Code for setting indicator positions ends.

    ResetAnimTicker( iExtension->iIsForeground );
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::SizeChangedInExtendedStatusPane
// Handles size change events in extended status pane layouts.
// ---------------------------------------------------------------------------
//
void CAknIndicatorContainer::SizeChangedInExtendedStatusPane()
    {
    TRect containerRect( Rect() );

    TBool hdLayout( AknStatuspaneUtils::HDLayoutActive() );

    // In landscape layoutdata there is not yet data
    // so we approximate a bit here...
    if ( AknStatuspaneUtils::ExtendedStaconPaneActive() )
        {
        containerRect.iTl.iY += Rect().Size().iHeight / 9;
        containerRect.iBr.iY -= Rect().Size().iHeight / 9;
        }

    if ( iIndicatorContext == EUniversalIndicators )
        {
        iLayoutOrientation = EHorizontal;

        if ( hdLayout )
            {
            if ( !AknLayoutUtils::LayoutMirrored() )
                {
                iAlignment = TIndicatorAlignment( ELeft );
                }
            else
                {
                iAlignment = TIndicatorAlignment( ERight );
                }
            }
        }

    // Available space for indicators
    TRect rect( containerRect );

    // If layout orientation has been changed since last call, prioritize indicators again.
    if ( iLayoutOrientation != iPreviousLayoutOrientation )
        {
        TRAP_IGNORE ( PrioritizeIndicatorsL() );
        }

    iIndicatorsShown         = 0;
    iAnimatedIndicatorsShown = 0;
    TInt last = iIndicators->Count() - 1;

    if ( iIndicatorContext == EUniversalIndicators )
        {
        TRect parent( rect );

        // Read the maximum amount of indicators in one row
        // from the layout data.
        TAknLayoutScalableParameterLimits limit(
            AknLayoutScalable_Avkon::cell_indicator_nsta_pane_ParamLimits() );
        TInt maxIndicatorsShown = limit.LastColumn() + 1;

        TInt indicatorNumberVariety = 0;
        if ( maxIndicatorsShown == 4 )
            {
            indicatorNumberVariety = 1;
            }

        TAknLayoutRect layoutRect;
        TAknWindowLineLayout cellLayout;
        TAknWindowComponentLayout indicatorLayout(
            AknLayoutScalable_Avkon::cell_indicator_nsta_pane_g2( hdLayout ) );


        TInt totalIndicatorsOn( 0 );

        // Need to go through the indicator array two times
        // to be able to place the indicators in correct order.
        for ( TInt i = 0; i <= last; i++ )
            {
            CAknIndicator* indicator = iIndicators->At( i );
            if ( indicator->IndicatorState() &&
                 indicator->Priority() != KIndicatorNotShown )
                {
                totalIndicatorsOn++;
                }
            }

        for ( TInt ii = 0; ii <= last; ii++ )
            {
            CAknIndicator* indicator = iIndicators->At( ii );
            if ( !indicator->IndicatorState() ||
                 indicator->Priority() == KIndicatorNotShown )
                {
                // Indicator is not shown on current layout even it is set ON.
                continue;
                }

            iIndicatorsShown++;

            if ( iIndicatorsShown > maxIndicatorsShown )
                {
                // Maximum number of indicators is already shown.
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                break;
                }
            else
                {
                TInt columnVariety( iIndicatorsShown - 1 );

                if ( !hdLayout && totalIndicatorsOn < maxIndicatorsShown )
                    {
                    if ( totalIndicatorsOn == 1 )
                        {
                        columnVariety = maxIndicatorsShown - 1;
                        }
                    else
                        {
                        columnVariety = iIndicatorsShown;
                        }
                    }

                // set indicator sizes here, leftmost cell first if we are in
                // HD status pane layout, otherwise rightmost cell first.
                cellLayout = AknLayoutScalable_Avkon::cell_indicator_nsta_pane(
                    columnVariety,
                    indicatorNumberVariety ).LayoutLine();
                layoutRect.LayoutRect( parent, cellLayout );
                TRect cell( layoutRect.Rect() );

                layoutRect.LayoutRect( cell, indicatorLayout );
                TRect indicatorRect( layoutRect.Rect() );

                // FIXME: Layout is broken, we fix it here.
                // Remove this when layout is fixed.
                if ( indicatorRect.iBr.iX > cell.iBr.iX )
                    {
                    indicatorRect.iBr.iX = cell.iBr.iX;
                    }
                if ( indicatorRect.iTl.iX < cell.iTl.iX )
                    {
                    indicatorRect.iTl.iX = cell.iTl.iX;
                    }
                // End of FIXME

                // TBD: When touch is supported, the size may have
                // to be reconsidered.
                indicator->SetRect( indicatorRect );
                }

            if ( indicator->IndicatorState() == MAknIndicator::EIndicatorAnimate )
                {
                iAnimatedIndicatorsShown++;
                }
            } // for

        ResetAnimTicker( iExtension->iIsForeground );
        } // if universal indicators.
    else  // Editor indicators.
        {
        // Navi and query editor indicators are always horizontally
        // arranged in extended status pane layouts.
        iLayoutOrientation = EHorizontal;

        TInt verticalIndicatorOffset        = rect.iTl.iY;
        TInt verticalOffsetForTextIndicator = verticalIndicatorOffset;

        // Text layout.
        TAknLayoutText layoutText;
        layoutText.LayoutText(
            rect, AknLayoutScalable_Avkon::navi_text_pane_t1() );

        // Offsets calculated from layout data.
        TAknLayoutRect editingIconLayoutRect;
        editingIconLayoutRect.LayoutRect(
            rect, AknLayoutScalable_Avkon::navi_icon_pane_g1( 1 ) );

        if ( iIndicatorContext == ENaviPaneEditorIndicators )
            {
            verticalIndicatorOffset        += editingIconLayoutRect.Rect().iTl.iY;
            verticalOffsetForTextIndicator = layoutText.TextRect().iTl.iY;
            }
        // In query editor indicators have offset 0

        TInt verticalOffset = verticalIndicatorOffset;

        // If layout orientation has been changed since last call, prioritize indicators again.
        if ( iLayoutOrientation != iPreviousLayoutOrientation )
            {
            // Following leave is ignored.
            // In case of leave indicators are not maybe shown correctly.
            TRAP_IGNORE ( PrioritizeIndicatorsL() );
            }

        iIndicatorsShown         = 0;
        iAnimatedIndicatorsShown = 0;
        TInt last                = iIndicators->Count() - 1;

        // Check if the secured connection indicator is on before
        // reading the layouts because of different positioning
        // of wait and progress bars with that indicator on.
        TBool secureConnectionIndicOn( EFalse );
        for ( TInt i = 0; i <= last; i++ )
            {
            CAknIndicator* indicator = iIndicators->At( i );

            if ( indicator->Uid().iUid == EAknNaviPaneEditorIndicatorSecuredConnection &&
                 indicator->IndicatorState() &&
                 indicator->Priority() != KIndicatorNotShown )
                {
                secureConnectionIndicOn = ETrue;
                }
            }

        // Wait bar layout.
        TAknWindowComponentLayout smallStatusWaitPaneLayout(
            AknLayoutScalable_Avkon::status_small_wait_pane(
                secureConnectionIndicOn ? 2 : 1 ) );
        TAknLayoutRect smallStatusWaitPaneLayoutRect;
        smallStatusWaitPaneLayoutRect.LayoutRect(
            rect, smallStatusWaitPaneLayout );
        TRect smallStatusWaitPaneRect( smallStatusWaitPaneLayoutRect.Rect() );

        // Globe layout.
        TAknLayoutRect smallStatusWmlGlobeLayoutRect;
        smallStatusWmlGlobeLayoutRect.LayoutRect(
            rect, AknLayoutScalable_Avkon::status_small_pane_g4( 0 ) );
        TRect smallStatusWmlGlobeRect( smallStatusWmlGlobeLayoutRect.Rect() );

        TInt wmlWaitGlobeLeftOffset =
            rect.Width() / 2 - smallStatusWmlGlobeRect.Width() / 2;

        TRect rectForRightSideIndicators( rect.iBr.iX,
                                          rect.iTl.iY,
                                          rect.iBr.iX,
                                          rect.iBr.iY );

        TRect rectForLeftSideIndicators( rect.iTl.iX,
                                         rect.iTl.iY,
                                         rect.iTl.iX,
                                         rect.iBr.iY );

        TRect rectForMiddleIndicators( 0, 0, 0, 0 ); // Not used in portrait.
        if ( hdLayout )
            {
            rectForMiddleIndicators = TRect( wmlWaitGlobeLeftOffset,
                                             rect.iTl.iY,
                                             wmlWaitGlobeLeftOffset,
                                             rect.iBr.iY );
            }

        for ( TInt ii = 0; ii <= last; ii++ )
            {
            CAknIndicator* indicator = iIndicators->At( ii );

            // Check if indicator is not shown on current layout even it is set ON.
            if ( !indicator->IndicatorState() ||
                 indicator->Priority() == KIndicatorNotShown )
                {
                continue;
                }

            TInt uid                 = indicator->Uid().iUid;
            TInt indicatorPosition   = indicator->IndicatorPosition();

            // Handle indicators that are not shown in this layout here.

            // Check if this is gprs indicator, it is never shown here but is drawn
            // to the signal pane by the system
            if ( uid == EAknNaviPaneEditorIndicatorGprs )
                {
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                iIndicatorsShown++;
                continue;
                }
            else if ( ( !hdLayout &&
                        ( uid == EAknNaviPaneEditorIndicatorSecuredConnection ||
                          uid == EAknNaviPaneEditorIndicatorProgressBar       ||
                          uid == EAknNaviPaneEditorIndicatorWmlWaitGlobe      ||
                          uid == EAknNaviPaneEditorIndicatorGprs              ||
                          uid == EAknNaviPaneEditorIndicatorFileSize          ||
                          uid == EAknNaviPaneEditorIndicatorWaitBar ) ) ||
                      ( hdLayout &&
                        ( uid == EAknNaviPaneEditorIndicatorWlanAvailable     ||
                          uid == EAknNaviPaneEditorIndicatorWlanActive        ||
                          uid == EAknNaviPaneEditorIndicatorWlanActiveSecure ) ) )
                {
                // These indicators are not shown in this statuspane layout
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                iIndicatorsShown++;
                continue;
                }

            // End of layout exceptions

            // Calculate offsets.
            TInt leftOffset     = 0;  // default offset
            TInt rightOffset    = 0;  // default offset

            TSize indicatorSize  = indicator->IconSize();
            TInt indicatorWidth  = indicatorSize.iWidth;  // default width
            TInt indicatorHeight = indicatorSize.iHeight; // default height


            switch ( uid )
                {
                case EAknNaviPaneEditorIndicatorMessageInfo:
                case EAknNaviPaneEditorIndicatorWmlWindowsText:
                case EAknNaviPaneEditorIndicatorMessageLength:
                    {
                    verticalOffset = verticalOffsetForTextIndicator;
                    break;
                    }

                case EAknNaviPaneEditorIndicatorFileSize:
                    {
                    verticalOffset = verticalOffsetForTextIndicator;
                    leftOffset     = KMinSpaceBetweenIconsInPixels;
                    break;
                    }

                case EAknNaviPaneEditorIndicatorSecuredConnection:
                case EAknNaviPaneEditorIndicatorWlanAvailable:
                case EAknNaviPaneEditorIndicatorWlanActive:
                case EAknNaviPaneEditorIndicatorWlanActiveSecure:
                    {
                    // Because icon bitmap does not contain enough space,
                    // increase offset as the layout spec states.
                    if ( AknLayoutUtils::LayoutMirrored() )
                        {
                        leftOffset = KMinSpaceBetweenIconsInPixels;
                        }
                    else
                        {
                        rightOffset = KMinSpaceBetweenIconsInPixels;
                        }
                    break;
                    }

                case EAknNaviPaneEditorIndicatorWmlWaitGlobe:
                    {
                    verticalOffset = ( rect.Height() - indicator->IconSize().iHeight ) / 2;
                    indicatorWidth = smallStatusWmlGlobeRect.Width();
                    break;
                    }

                case EAknNaviPaneEditorIndicatorProgressBar:
                    {
                    indicatorWidth  = smallStatusWaitPaneRect.Width();
                    indicatorHeight = smallStatusWaitPaneRect.Height();
                    leftOffset      = KMinSpaceBetweenIconsInPixels;
                    break;
                    }

                case EAknNaviPaneEditorIndicatorWaitBar:
                    {
                    indicatorWidth  = smallStatusWaitPaneRect.Width();
                    indicatorHeight = smallStatusWaitPaneRect.Height();
                    leftOffset      = KMinSpaceBetweenIconsInPixels;
                    break;
                    }

                default:
                    {
                    // Default offsets.
                    break;
                    }
                }

            // End of offset calculations.

            // Place indicators to the left side.
            if ( ( indicatorPosition == ELeftSide  &&
                   iAlignment == TIndicatorAlignment( ERight ) ) ||
                 ( indicatorPosition == ERightSide &&
                   iAlignment == TIndicatorAlignment( ELeft ) ) )
                {
                TRect requiredRect(
                    rectForLeftSideIndicators.iBr.iX,
                    rectForLeftSideIndicators.iTl.iY,
                    rectForLeftSideIndicators.iBr.iX + leftOffset + indicatorWidth + rightOffset,
                    rectForLeftSideIndicators.iBr.iY );

                // Check if indicator fits
                TBool indicatorDoesNotFit =
                    requiredRect.Intersects( rectForRightSideIndicators ) ||
                    requiredRect.Intersects( rectForMiddleIndicators )    ||
                    rect.iTl.iX > requiredRect.iTl.iX                     ||
                    rect.iBr.iX < requiredRect.iBr.iX;

                if ( indicatorDoesNotFit &&
                     !indicator->DynamicTextIndicator() )
                    {
                    indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                    iIndicatorsShown++;
                    continue;
                    }
                else
                    {
                    if ( indicator->DynamicTextIndicator() && indicatorDoesNotFit )
                        {
                        // Dynamic text indicators (not normal text indicators) can adjust to any size.
                        TInt maxWidthForDynamicTextIndicator =
                            rect.iBr.iX - requiredRect.iTl.iX;
                        if ( requiredRect.Intersects( rectForRightSideIndicators ) )
                            {
                            maxWidthForDynamicTextIndicator =
                                rectForRightSideIndicators.iTl.iX - requiredRect.iTl.iX;
                            }
                        if ( requiredRect.Intersects( rectForMiddleIndicators ) )
                            {
                            maxWidthForDynamicTextIndicator =
                                rectForMiddleIndicators.iTl.iX - requiredRect.iTl.iX;
                            }

                        indicator->SetExtent(
                            TPoint( requiredRect.iTl.iX + leftOffset,
                                    verticalOffset ),
                            TSize( maxWidthForDynamicTextIndicator,
                                   indicatorHeight ) );

                        // Adjust remaining space.
                        rectForLeftSideIndicators.iBr.iX =
                            indicator->Position().iX + indicator->Size().iWidth;
                        }
                    else
                        {
                        indicator->SetExtent(
                            TPoint( requiredRect.iTl.iX + leftOffset,
                                    verticalOffset ),
                            TSize( indicatorWidth,
                                   indicatorHeight ) );

                        // Adjust remaining space.
                        rectForLeftSideIndicators.iBr.iX = requiredRect.iBr.iX;
                        }
                    }
                }


            // Place indicators on the right side.
            if ( ( indicatorPosition == ERightSide &&
                   iAlignment == TIndicatorAlignment( ERight ) ) ||
                 ( indicatorPosition == ELeftSide  &&
                   iAlignment == TIndicatorAlignment( ELeft ) ) )
                {
                TRect requiredRect(
                    rectForRightSideIndicators.iTl.iX - leftOffset - indicatorWidth - rightOffset,
                    rectForRightSideIndicators.iTl.iY,
                    rectForRightSideIndicators.iTl.iX,
                    rectForRightSideIndicators.iBr.iY );

                // Check if indicator fits.
                 TBool indicatorDoesNotFit =
                     ( requiredRect.Intersects( rectForLeftSideIndicators ) ||
                       requiredRect.Intersects( rectForMiddleIndicators )   ||
                       rect.iTl.iX > requiredRect.iTl.iX                    ||
                       rect.iBr.iX < requiredRect.iBr.iX );

                if ( indicatorDoesNotFit &&
                     !indicator->DynamicTextIndicator() )
                    {
                    indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                    iIndicatorsShown++;
                    continue;
                    }
                else
                    {
                    if ( indicator->DynamicTextIndicator() && indicatorDoesNotFit )
                        {
                        // Dynamic text indicators (not normal text indicators)
                        // can adjust to any size.
                        TInt maxWidthForDynamicTextIndicator =
                            requiredRect.iBr.iX - rect.iTl.iX  - leftOffset;
                        if ( requiredRect.Intersects( rectForLeftSideIndicators ) )
                            {
                            maxWidthForDynamicTextIndicator =
                                requiredRect.iBr.iX - rectForLeftSideIndicators.iBr.iX;
                            }
                        if ( requiredRect.Intersects( rectForMiddleIndicators ) )
                            {
                            maxWidthForDynamicTextIndicator =
                                requiredRect.iBr.iX - rectForMiddleIndicators.iBr.iX;
                            }

                        indicator->SetExtent(
                            TPoint( requiredRect.iBr.iX - maxWidthForDynamicTextIndicator - leftOffset,
                                    verticalOffset),
                            TSize( maxWidthForDynamicTextIndicator, indicatorHeight ) );

                        // Adjust remaining space.
                        rectForRightSideIndicators.iTl.iX = indicator->Position().iX;
                        }
                    else
                        {
                        indicator->SetExtent(
                            TPoint( requiredRect.iTl.iX + leftOffset,
                                    verticalOffset),
                            indicatorSize );

                        // Adjust remaining space.
                        rectForRightSideIndicators.iTl.iX = requiredRect.iTl.iX;
                        }
                    }
                }

            // Place indicators to the middle, only indicator
            // at the moment is the wml wait globe.
            if ( indicatorPosition == EMiddle )
                {
                TRect requiredRect(
                    rectForMiddleIndicators.iTl.iX,
                    rectForMiddleIndicators.iTl.iY,
                    rectForMiddleIndicators.iTl.iX + leftOffset + indicatorWidth + rightOffset,
                    rectForMiddleIndicators.iBr.iY );

                // Check if indicator fits.
                if ( ( requiredRect.Intersects( rectForRightSideIndicators ) ||
                       requiredRect.Intersects( rectForLeftSideIndicators ) )  ||
                     rectForMiddleIndicators.Width() != 0 )
                    {
                    // No space available in the middle.
                    indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                    iIndicatorsShown++;
                    continue;
                    }
                else
                    {
                    indicator->SetExtent(
                        TPoint( rectForMiddleIndicators.iTl.iX + leftOffset,
                                verticalOffset ),
                        indicatorSize );

                    // Adjust remaining space.
                    rectForMiddleIndicators.iTl.iX += rightOffset + indicatorWidth;
                    }
                }

            iIndicatorsShown++;

            if ( indicator->IndicatorState() == MAknIndicator::EIndicatorAnimate )
                {
                iAnimatedIndicatorsShown++;
                }
            } // for

        // Code for setting indicator positions ends.

        ResetAnimTicker( iExtension->iIsForeground );
        }
    }


void CAknIndicatorContainer::SizeChangedInIdleExtendedStatusPane()
    {
    TRect containerRect( Rect() );

    if (iIndicatorContext == EUniversalIndicators)
        {
        iLayoutOrientation = EHorizontal;
        }

    // Available space for indicators
    TRect rect(containerRect);

    // If layout orientation has been changed since last call, prioritize indicators again.
    if ( iLayoutOrientation != iPreviousLayoutOrientation )
        {
        TRAP_IGNORE ( PrioritizeIndicatorsL() );
        }

    iIndicatorsShown = 0;
    iAnimatedIndicatorsShown = 0;
    TInt last = iIndicators->Count() - 1;

    if (iIndicatorContext == EUniversalIndicators)
        {
        TRect parent( rect );

        TAknLayoutScalableParameterLimits limit =
            AknLayoutScalable_Avkon::cell_indicator_nsta_pane_ParamLimits();
        TInt maxIndicatorsShownInOneLine = 3; // magic

        TAknLayoutRect layoutRect;
        TAknWindowLineLayout cellLayout;
        TAknWindowLineLayout indicatorLayout;

        TInt totalIndicatorsOn = 0;

        // Need to go through the indicator array two times
        // to be able to place the indicators in correct order.
        for ( TInt i = 0; i <= last; i++ )
            {
            CAknIndicator* indicator = iIndicators->At( i );

            if ( indicator->IndicatorState() &&
                 indicator->Priority() != KIndicatorNotShown )
                {
                totalIndicatorsOn++;
                }
            }

        for ( TInt ii = 0; ii <= last; ii++ )
            {
            CAknIndicator* indicator = iIndicators->At(ii);
            if ( !indicator->IndicatorState() || (indicator->Priority() == KIndicatorNotShown))
                {
                // Indicator is not shown on current layout even it is set ON.
                continue;
                }

            iIndicatorsShown++;

            if (iIndicatorsShown > maxIndicatorsShownInOneLine * 2)
                {
                indicator->SetExtent(TPoint(0,0), TSize(0,0));
                break;
                }
            else
                {
                TInt indicatorRow = ( iIndicatorsShown - 1 ) / maxIndicatorsShownInOneLine;

                TInt columnVariety =
                    iIndicatorsShown - maxIndicatorsShownInOneLine * indicatorRow - 1;

                if ( ( totalIndicatorsOn < maxIndicatorsShownInOneLine &&
                       indicatorRow == 0 ) ||
                     ( totalIndicatorsOn > maxIndicatorsShownInOneLine &&
                       totalIndicatorsOn < maxIndicatorsShownInOneLine * 2 &&
                       indicatorRow == 1 ) )
                    {
                    if ( totalIndicatorsOn == 1 ||
                         totalIndicatorsOn == maxIndicatorsShownInOneLine + 1 )
                        {
                        columnVariety = maxIndicatorsShownInOneLine - 1;
                        }
                    else
                        {
                        columnVariety =
                            iIndicatorsShown - maxIndicatorsShownInOneLine * indicatorRow;
                        }
                    }

                // set indicator sizes here...rightmost cell first
                cellLayout = AknLayoutScalable_Avkon::cell_indicator_nsta_pane(
                    columnVariety,
                    2,
                    indicatorRow ).LayoutLine();
                layoutRect.LayoutRect( parent, cellLayout );
                TRect cell( layoutRect.Rect() );

                indicatorLayout =
                    AknLayoutScalable_Avkon::cell_indicator_nsta_pane_g2().LayoutLine();
                layoutRect.LayoutRect(cell,indicatorLayout);
                TRect indicatorRect( layoutRect.Rect() );

                // FIXME: Layout is broken, we fix it here. Remove this when layout is fixed.
                if (indicatorRect.iBr.iX > cell.iBr.iX)
                    indicatorRect.iBr.iX = cell.iBr.iX;
                if (indicatorRect.iTl.iX < cell.iTl.iX)
                    indicatorRect.iTl.iX = cell.iTl.iX;
                // End of FIXME

                // TBD: When touch is supported, the size may have to be reconsidered.
                indicator->SetRect(indicatorRect);
                }

            if (indicator->IndicatorState() == MAknIndicator::EIndicatorAnimate)
                {
                iAnimatedIndicatorsShown++;
                }
            } // for

        ResetAnimTicker( iExtension->iIsForeground );
        } // if universal indicators
    }


void CAknIndicatorContainer::SizeChangedInFlatStatusPane()
    {
    TRect containerRect(Rect());

    if (iIndicatorContext == EUniversalIndicators)
        {
        iLayoutOrientation = EVertical;
        }

    // Available space for indicators
    TRect rect(containerRect);

    // If layout orientation has been changed since last call, prioritize indicators again.
    if ( iLayoutOrientation != iPreviousLayoutOrientation )
        {
        TRAP_IGNORE ( PrioritizeIndicatorsL() );
        }

    iIndicatorsShown = 0;
    iAnimatedIndicatorsShown = 0;
    TInt last = iIndicators->Count() - 1;

    if (iIndicatorContext == EUniversalIndicators)
        {
        TAknLayoutRect layoutRect;
        TAknWindowComponentLayout indicatorLayout;
        TBool extendedFlatLayout(
            AknStatuspaneUtils::ExtendedFlatLayoutActive() );
        
        for (TInt ii = 0; ii <= last; ii++)
            {
            CAknIndicator* indicator = iIndicators->At(ii);
            if ( !indicator->IndicatorState() || (indicator->Priority() == KIndicatorNotShown))
                {
                // Indicator is not shown on current layout even it is set ON.
                continue;
                }

            iIndicatorsShown++;

            TBool showIndicator( ETrue );
            switch ( iIndicatorsShown )
                {
                case 1:
                    {
                    indicatorLayout =
                        AknLayoutScalable_Avkon::uni_indicator_pane_g1( 1 );
                    break;
                    }
                case 2:
                    {
                    indicatorLayout =
                        AknLayoutScalable_Avkon::uni_indicator_pane_g2( 1 );
                    break;
                    }
                case 3:
                    {
                    indicatorLayout =
                        AknLayoutScalable_Avkon::uni_indicator_pane_g3( 1 );
                    break;
                    }
                    
                // TODO: Add support (remove the extendedFlatLayout checks
                // below) for six indicators also in the extended flat layout
                // once the layout data is fixed.
                    
                case 4:
                    {
                    if ( !extendedFlatLayout )
                        {
                        indicatorLayout =
                            AknLayoutScalable_Avkon::uni_indicator_pane_g4( 1 );
                        }
                    else
                        {
                        showIndicator = EFalse;
                        }
                    break;
                    }
                case 5:
                    {
                    if ( !extendedFlatLayout )
                        {
                        indicatorLayout =
                            AknLayoutScalable_Avkon::uni_indicator_pane_g5( 1 );
                        }
                    else
                        {
                        showIndicator = EFalse;
                        }
                    break;
                    }
                case 6:
                    {
                    if ( !extendedFlatLayout )
                        {
                        indicatorLayout =
                            AknLayoutScalable_Avkon::uni_indicator_pane_g6( 1 );
                        }
                    else
                        {
                        showIndicator = EFalse;
                        }
                    break;
                    }
                default:
                    {
                    showIndicator = EFalse;
                    break;
                    }
                }

            if ( showIndicator )
                {
                layoutRect.LayoutRect( containerRect, indicatorLayout );
                indicator->SetRect( layoutRect.Rect() );
                }
            else // Maximum indicator are shown, others are invisible.
                {
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                }
            
            if (indicator->IndicatorState() == MAknIndicator::EIndicatorAnimate)
                {
                iAnimatedIndicatorsShown++;
                }
            } // for

        ResetAnimTicker( iExtension->iIsForeground );
        } // if universal indicators
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::SizeChangedInStaconPane
// Handles size change events in stacon pane layouts.
// ---------------------------------------------------------------------------
//
void CAknIndicatorContainer::SizeChangedInStaconPane()
    {
    TRect containerRect( Rect() );

    if ( iIndicatorContext == EUniversalIndicators )
        {
        if ( AknStatuspaneUtils::IdleLayoutActive() )
            {
            iLayoutOrientation = EHorizontal;
            }
        else
            {
            iLayoutOrientation = EVertical;
            }
        }

    // Available space for indicators.
    TRect rect( containerRect );

    // If layout orientation has been changed since last call,
    // prioritize indicators again.
    if ( iLayoutOrientation != iPreviousLayoutOrientation )
        {
        // Following leave is ignored.
        // In case of leave indicators are not maybe shown correctly.
        TRAP_IGNORE ( PrioritizeIndicatorsL() );
        }

    iIndicatorsShown         = 0;
    iAnimatedIndicatorsShown = 0;
    TInt last                = iIndicators->Count() - 1;

    if ( iIndicatorContext == EUniversalIndicators )
        {
        TRect parent( rect );

        // Layout data for four indicators in stacon pane layout exists,
        // but for only two indicators are shown.
        for ( TInt ii = 0; ii <= last; ii++ )
            {
            CAknIndicator* indicator = iIndicators->At( ii );
            if ( !indicator->IndicatorState() ||
                 indicator->Priority() == KIndicatorNotShown )
                {
                // Indicator is not shown on current layout even it is set ON.
                continue;
                }

            iIndicatorsShown++;

            // No fading is done to indicators until transparent
            // windows are available, faders always set to NULL for now.
            CAknIndicatorFader* topFader    = NULL;
            CAknIndicatorFader* bottomFader = NULL;

            if ( AknStatuspaneUtils::StaconSoftKeysRight() )
                {
                if ( iIndicatorsShown == 1 )
                    {
                    indicator->SetIndicatorFader( topFader );
                    AknLayoutUtils::LayoutControl(
                        indicator,
                        parent,
                        AknLayoutScalable_Avkon::uni_indicator_pane_stacon_g1() );
                    }
                else if ( iIndicatorsShown == 2 )
                    {
                    indicator->SetIndicatorFader( bottomFader );
                    AknLayoutUtils::LayoutControl(
                        indicator,
                        parent,
                        AknLayoutScalable_Avkon::uni_indicator_pane_stacon_g2() );
                    }
                }
            else if ( AknStatuspaneUtils::StaconSoftKeysLeft() )
                {
                // LAF does not contain mirrored lines. We mirror positions here.
                if ( iIndicatorsShown == 1 )
                    {
                    indicator->SetIndicatorFader( topFader );
                    AknLayoutUtils::LayoutControl(
                        indicator,
                        parent,
                        AknLayoutScalable_Avkon::uni_indicator_pane_stacon_g3() );
                    }
                else if ( iIndicatorsShown == 2 )
                    {
                    indicator->SetIndicatorFader( bottomFader );
                    AknLayoutUtils::LayoutControl(
                        indicator,
                        parent,
                        AknLayoutScalable_Avkon::uni_indicator_pane_stacon_g4() );
                    }
                }

            if ( iIndicatorsShown > 2 )
                {
                indicator->SetIndicatorFader( NULL );
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                break;
                }

            if ( indicator->IndicatorState() == MAknIndicator::EIndicatorAnimate )
                {
                iAnimatedIndicatorsShown++;
                }
            } // for

        ResetAnimTicker( iExtension->iIsForeground );
        } // if universal indicators
    // Currently uses small statuspane layouts in navipane indicators because not all exist for stacon yet.
    else if ( iIndicatorContext == ENaviPaneEditorIndicators )
        {
        TBool isMirrored( AknLayoutUtils::LayoutMirrored() );

        iLayoutOrientation = EHorizontal; // always horizontal

        TRect containerRect( Rect() );

        // Check if the secured connection indicator is on before
        // reading the layouts because of different positioning
        // of wait and progress bars with that indicator on.
        TBool secureConnectionIndicOn( EFalse );
        for ( TInt i = 0; i <= last; i++ )
            {
            CAknIndicator* indicator = iIndicators->At( i );

            if ( indicator->Uid().iUid == EAknNaviPaneEditorIndicatorSecuredConnection &&
                 indicator->IndicatorState() &&
                 indicator->Priority() != KIndicatorNotShown )
                {
                secureConnectionIndicOn = ETrue;
                }
            }

        // screen
        TRect screenRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );

        // app window
        TRect applicationWindowRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow,
                                           applicationWindowRect );

        // small statuspane
        TAknLayoutRect smallStatusPaneLayoutRect;
        smallStatusPaneLayoutRect.LayoutRect(
            applicationWindowRect,
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Avkon::area_top_pane( 1 ),
                AknLayoutScalable_Avkon::status_small_pane() ) );
        TRect smallStatusPaneRect( smallStatusPaneLayoutRect.Rect() );

        // small statuspane, wait pane
        TAknLayoutRect smallStatusWaitPaneLayoutRect;
        smallStatusWaitPaneLayoutRect.LayoutRect(
            smallStatusPaneRect,
            AknLayoutScalable_Avkon::status_small_wait_pane(
                secureConnectionIndicOn ? 2 : 1 ) );
        TRect smallStatusWaitPaneRect( smallStatusWaitPaneLayoutRect.Rect() );

        // small statuspane, globe
        TAknLayoutRect smallStatusWmlGlobeLayoutRect;
        smallStatusWmlGlobeLayoutRect.LayoutRect(
            smallStatusPaneRect,
            AknLayoutScalable_Avkon::status_small_pane_g4( 0 ) );
        TRect smallStatusWmlGlobeRect( smallStatusWmlGlobeLayoutRect.Rect() );

        // small statuspane, GPRS indicator
        TAknLayoutRect smallStatusGprsLayoutRect;
        smallStatusGprsLayoutRect.LayoutRect(
            smallStatusPaneRect,
            AknLayoutScalable_Avkon::status_small_pane_g2( 0 ) );
        TRect smallStatusGprsRect( smallStatusGprsLayoutRect.Rect() );

        // small statuspane, secure state indicator
        TAknLayoutRect smallStatusSecureStateLayoutRect;
        smallStatusSecureStateLayoutRect.LayoutRect(
            smallStatusPaneRect,
            AknLayoutScalable_Avkon::status_small_pane_g3( 0 ) );
        TRect smallStatusSecureStateRect( smallStatusSecureStateLayoutRect.Rect() );


        // small statuspane, texts
        TAknLayoutText textLayout;
        textLayout.LayoutText(
            containerRect,
            AknLayoutScalable_Avkon::status_small_pane_t1( 0 ) );
        TRect smallStatusTextRect( textLayout.TextRect() );

        TInt textIndicatorLeftOffset     = smallStatusTextRect.iTl.iX;
        TInt textIndicatorVerticalOffset = smallStatusTextRect.iTl.iY;

        TInt wmlWaitGlobeLeftOffset =
            containerRect.Width() / 2 - smallStatusWmlGlobeRect.Width() / 2;

        // Modify containerRect if alignment is Right.
        // For Left aligned no need to modify containerRect.
        if ( iAlignment == TIndicatorAlignment( ERight ) )
            {
            containerRect.iBr.iX -= 3; // Right margin of editor indicators
            containerRect.iTl.iX += 0; // Left margin of editor indicators
            }

        iIndicatorsShown                = 0;
        iAnimatedIndicatorsShown        = 0;
        TBool textIndicatorOffsetNeeded = ETrue;

        TRect rectForRightSideIndicators( containerRect.iBr.iX,
                                          containerRect.iTl.iY,
                                          containerRect.iBr.iX,
                                          containerRect.iBr.iY );

        TRect rectForLeftSideIndicators( containerRect.iTl.iX,
                                         containerRect.iTl.iY,
                                         containerRect.iTl.iX,
                                         containerRect.iBr.iY );

        TRect rectForMiddleIndicators( wmlWaitGlobeLeftOffset,
                                       containerRect.iTl.iY,
                                       wmlWaitGlobeLeftOffset,
                                       containerRect.iBr.iY );

        for ( TInt ii = 0; ii <= last; ii++ )
            {
            CAknIndicator* indicator = iIndicators->At( ii );
            TInt uid = indicator->Uid().iUid;
            TInt indicatorPosition = 0;

            // decide here how indicators are positioned. Default is rigth side.
            indicatorPosition = indicator->IndicatorPosition();

            // Check if indicator is not shown on current layout even it is set ON.
            if ( !indicator->IndicatorState() ||
                 indicator->Priority() == KIndicatorNotShown )
                {
                continue;
                }

            // Check if this is gprs indicator, it is never shown here but is drawn
            // to the signal pane by the system
            if ( uid == EAknNaviPaneEditorIndicatorGprs )
                {
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                iIndicatorsShown++;
                continue;
                }
            else if ( uid == EAknNaviPaneEditorIndicatorWlanAvailable ||
                      uid == EAknNaviPaneEditorIndicatorWlanActive ||
                      uid == EAknNaviPaneEditorIndicatorWlanActiveSecure )
                {
                // These are not shown in stacon layout navi pane, as
                // the same indicators are shown on the universal
                // indicator pane.
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                iIndicatorsShown++;
                continue;
                }

            // handle offsets
            TAknWindowLineLayout areaTopPaneLayout = AknLayoutScalable_Avkon::area_top_pane( 0 );
            TAknLayoutRect areaTopPaneLayoutRect;
            areaTopPaneLayoutRect.LayoutRect( screenRect, areaTopPaneLayout );

            TAknWindowLineLayout statusPaneIconSmallLayout(
                TAknWindowComponentLayout::Compose(
                    AknLayoutScalable_Avkon::area_top_pane( 1 ),
                    TAknWindowComponentLayout::Compose(
                        AknLayoutScalable_Avkon::status_small_pane(),
                        AknLayoutScalable_Avkon::status_small_icon_pane() ) ).LayoutLine() );

            // If top pane area's vertical position doesn't start at 0,
            // the statusPaneIconSmallRect's values will be incorrect and
            // must be adjusted.
            TInt offsetFromTop = areaTopPaneLayoutRect.Rect().iTl.iY;
            TRect normSmallStatusPaneRect( smallStatusPaneRect );
            normSmallStatusPaneRect.iTl.iY -= offsetFromTop;
            statusPaneIconSmallLayout.it -= offsetFromTop;

            TAknLayoutRect statusPaneIconSmallLayoutRect;
            statusPaneIconSmallLayoutRect.LayoutRect(
                normSmallStatusPaneRect, statusPaneIconSmallLayout );

            TInt verticalOffset = statusPaneIconSmallLayoutRect.Rect().iTl.iY;

            TInt leftOffset  = 0;  // default offset
            TInt rightOffset = 0;  // default offset

            TInt indicatorWidth = indicator->IconSize().iWidth;   // default width
            TInt indicatorHeight = indicator->IconSize().iHeight; // default height

            if ( uid == EAknNaviPaneEditorIndicatorMessageInfo    ||
                 uid == EAknNaviPaneEditorIndicatorWmlWindowsText ||
                 uid == EAknNaviPaneEditorIndicatorMessageLength )
                {
                verticalOffset = textIndicatorVerticalOffset;
                // first text idicator need horizontal offset
                if ( textIndicatorOffsetNeeded )
                    {
                    leftOffset += textIndicatorLeftOffset;
                    }
                textIndicatorOffsetNeeded = EFalse;
                }
            else if ( uid == EAknNaviPaneEditorIndicatorFileSize )
                {
                verticalOffset = textIndicatorVerticalOffset;

                // Need left offset in western, right offset in A&H layout.
                if ( isMirrored )
                    {
                    rightOffset = textIndicatorLeftOffset;
                    }
                else
                    {
                    leftOffset  = KMinSpaceBetweenIconsInPixels;
                    }
                }
            else if ( uid == EAknNaviPaneEditorIndicatorSecuredConnection )
                {
                verticalOffset = smallStatusSecureStateRect.iTl.iY;
                // Because icon bitmap does not contain enough space,
                // increase offset as the layout spec states.
                if ( isMirrored )
                    {
                    leftOffset = KMinSpaceBetweenIconsInPixels;
                    }
                else
                    {
                    rightOffset = KMinSpaceBetweenIconsInPixels;
                    }
                textIndicatorOffsetNeeded = EFalse;
                }
            else if ( uid == EAknNaviPaneEditorIndicatorWmlWaitGlobe )
                {
                verticalOffset = (containerRect.Height() - indicator->IconSize().iHeight)/2;
                indicatorWidth = smallStatusWmlGlobeRect.Width();
                }
            else if ( uid == EAknNaviPaneEditorIndicatorProgressBar )
                {
                verticalOffset  = smallStatusWaitPaneRect.iTl.iY;
                indicatorWidth  = smallStatusWaitPaneRect.Width();
                indicatorHeight = smallStatusWaitPaneRect.Height();
                leftOffset      = 0;
                textIndicatorOffsetNeeded = ETrue;
                }
            else if ( uid == EAknNaviPaneEditorIndicatorWaitBar )
                {
                verticalOffset  = smallStatusWaitPaneRect.iTl.iY;
                indicatorWidth  = smallStatusWaitPaneRect.Width();
                indicatorHeight = smallStatusWaitPaneRect.Height();
                leftOffset      = 0;
                textIndicatorOffsetNeeded = ETrue;
                }

            if ( isMirrored )
                {
                TInt temp   = leftOffset;
                leftOffset  = rightOffset;
                rightOffset = temp;
                }

            // Place indicators to the left side.
            if ( ( indicatorPosition == ELeftSide &&
                   iAlignment == TIndicatorAlignment( ERight ) ) ||
                 ( indicatorPosition == ERightSide &&
                   iAlignment == TIndicatorAlignment( ELeft ) ) )
                {
                TRect requiredRect(
                    rectForLeftSideIndicators.iBr.iX,
                    rectForLeftSideIndicators.iTl.iY,
                    rectForLeftSideIndicators.iBr.iX + leftOffset + indicatorWidth + rightOffset,
                    rectForLeftSideIndicators.iBr.iY );

                // Check if indicator fits.
                TBool indicatorDoesNotFit =
                    ( requiredRect.Intersects( rectForRightSideIndicators ) ||
                      requiredRect.Intersects( rectForMiddleIndicators )    ||
                      containerRect.iTl.iX > requiredRect.iTl.iX            ||
                      containerRect.iBr.iX < requiredRect.iBr.iX );

                    if ( indicatorDoesNotFit &&
                         !indicator->DynamicTextIndicator() )
                        {
                        indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                        iIndicatorsShown++;
                        continue;
                        }
                    else
                        {
                        if ( indicator->DynamicTextIndicator() && indicatorDoesNotFit )
                            {
                            // Dynamic text indicators (not normal text indicators)
                            // can adjust to any size.
                            TInt maxWidthForDynamicTextIndicator =
                                containerRect.iBr.iX - requiredRect.iTl.iX;

                            if ( requiredRect.Intersects( rectForRightSideIndicators ) )
                                {
                                maxWidthForDynamicTextIndicator =
                                    rectForRightSideIndicators.iTl.iX - requiredRect.iTl.iX;
                                }

                            if ( requiredRect.Intersects( rectForMiddleIndicators ) )
                                {
                                maxWidthForDynamicTextIndicator =
                                    rectForMiddleIndicators.iTl.iX - requiredRect.iTl.iX;
                                }

                            indicator->SetExtent(
                                TPoint( requiredRect.iTl.iX + leftOffset, verticalOffset ),
                                TSize( maxWidthForDynamicTextIndicator, indicatorHeight ) );

                            rectForLeftSideIndicators.iBr.iX =
                                indicator->Position().iX + indicator->Size().iWidth;
                            }
                        else
                            {
                            indicator->SetExtent(
                                TPoint( requiredRect.iTl.iX + leftOffset, verticalOffset ),
                                TSize( indicatorWidth, indicatorHeight ) );

                            rectForLeftSideIndicators.iBr.iX = requiredRect.iBr.iX;
                            }
                        }
                    }


                // Place indicators to the right side.
                if ( ( indicatorPosition == ERightSide &&
                       iAlignment == TIndicatorAlignment( ERight ) ) ||
                     ( indicatorPosition == ELeftSide &&
                       iAlignment == TIndicatorAlignment( ELeft ) ) )
                    {
                    TRect requiredRect(
                        rectForRightSideIndicators.iTl.iX - leftOffset - indicatorWidth - rightOffset,
                        rectForRightSideIndicators.iTl.iY,
                        rectForRightSideIndicators.iTl.iX,
                        rectForRightSideIndicators.iBr.iY );

                    // Check if indicator fits.
                    TBool indicatorDoesNotFit =
                         ( requiredRect.Intersects( rectForLeftSideIndicators ) ||
                           requiredRect.Intersects( rectForMiddleIndicators )   ||
                           containerRect.iTl.iX > requiredRect.iTl.iX           ||
                           containerRect.iBr.iX < requiredRect.iBr.iX );

                    if ( indicatorDoesNotFit &&
                         !indicator->DynamicTextIndicator() )
                        {
                        indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                        iIndicatorsShown++;
                        continue;
                        }
                    else
                        {
                        if ( indicator->DynamicTextIndicator() &&
                             indicatorDoesNotFit )
                            {
                            // Dynamic text indicators (not normal text indicators)
                            // can adjust to any size.
                            TInt maxWidthForDynamicTextIndicator =
                                requiredRect.iBr.iX - containerRect.iTl.iX  - leftOffset;

                            if ( requiredRect.Intersects( rectForLeftSideIndicators ) )
                                {
                                maxWidthForDynamicTextIndicator =
                                    requiredRect.iBr.iX - rectForLeftSideIndicators.iBr.iX;
                                }
                            if ( requiredRect.Intersects( rectForMiddleIndicators ) )
                                {
                                maxWidthForDynamicTextIndicator =
                                    requiredRect.iBr.iX - rectForMiddleIndicators.iBr.iX;
                                }

                            indicator->SetExtent(
                                TPoint( requiredRect.iBr.iX - maxWidthForDynamicTextIndicator + leftOffset,
                                        verticalOffset),
                                TSize( maxWidthForDynamicTextIndicator, indicatorHeight ) );
                            rectForRightSideIndicators.iTl.iX = indicator->Position().iX;
                            }
                        else
                            {
                            indicator->SetExtent(
                                TPoint( requiredRect.iTl.iX + leftOffset, verticalOffset ),
                                TSize( indicatorWidth, indicatorHeight ) );

                            rectForRightSideIndicators.iTl.iX = requiredRect.iTl.iX;
                            }
                        }
                    }


            // place indicators to the middle, only indicator is wml wait globe
            if ( indicatorPosition == EMiddle )
                {
                TRect requiredRect(
                    rectForMiddleIndicators.iTl.iX,
                    rectForMiddleIndicators.iTl.iY,
                    rectForMiddleIndicators.iTl.iX + leftOffset + indicatorWidth + rightOffset,
                    rectForMiddleIndicators.iBr.iY );

                // check if indicator fits
                if ( requiredRect.Intersects( rectForRightSideIndicators ) ||
                     requiredRect.Intersects( rectForLeftSideIndicators )  ||
                     rectForMiddleIndicators.Width() != 0 )
                    {
                    indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                    iIndicatorsShown++;
                    continue;
                    }
                else
                    {
                    indicator->SetExtent( TPoint( rectForMiddleIndicators.iTl.iX + leftOffset,
                                                  verticalOffset ),
                                          TSize( indicatorWidth, indicatorHeight ) );

                    rectForMiddleIndicators.iTl.iX += ( rightOffset + indicatorWidth );
                    }
                }

            iIndicatorsShown++;

            if ( indicator->IndicatorState() == MAknIndicator::EIndicatorAnimate )
                {
                iAnimatedIndicatorsShown++;
                }
            } // for
        }

    ResetAnimTicker( iExtension->iIsForeground );
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::SetIncallBubbleAllowedInIdle
// Allows/disallows showing the small incall status bubble of this container
// in idle status pane layouts.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknIndicatorContainer::SetIncallBubbleAllowedInIdle(
    TBool aAllowed )
    {
    if ( iExtension )
        {
        iExtension->iIncallBubbleAllowedInIdle = aAllowed;
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::SetIncallBubbleAllowedInUsual
// Allows/disallows showing the small incall status bubble of this container
// in usual status pane layouts.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknIndicatorContainer::SetIncallBubbleAllowedInUsual(
    TBool aAllowed )
    {
    if ( iExtension )
        {
        iExtension->iIncallBubbleAllowedInUsual = aAllowed;
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::SetIndicatorObserver
// Sets aIndicatorObserver to observe indicator with aIndicatorUid
// by looping through indicators to find indicator with aIndicaotrUid
// and calling SetIndicatorObserver to it with given pointer to observer
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknIndicatorContainer::SetIndicatorObserver(
    MAknIndicatorObserver* aIndicatorObserver,
    TUid aIndicatorUid )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        TInt count = iIndicators->Count();

        // Loop through indicators and find indicator with given UID.
        for ( TInt ii = 0; ii < count; ii++ )
            {
            CAknIndicator* indicator = iIndicators->At( ii );

            // If indicator found, set aIndicatorObserver to observe it.
            if ( indicator->Uid() == aIndicatorUid )
                {
                indicator->SetIndicatorObserver( aIndicatorObserver );
                break;
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::SetContainerWindowNonFading
// Allows/disallows fading of this pane.
// ---------------------------------------------------------------------------
//
void CAknIndicatorContainer::SetContainerWindowNonFading( TBool aNonFading )
    {
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if ( statusPane )
        {
        CCoeControl* control = NULL;
        TRAP_IGNORE(
            control = statusPane->ContainerControlL(
                TUid::Uid( EEikStatusPaneUidIndic ) ) );

        if ( control )
            {
            control->DrawableWindow()->SetNonFading( aNonFading );
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::SetupIndicatorLayoutModes
// Sets the appropriate layout mode to all the indicators inside
// this container.
// ---------------------------------------------------------------------------
//
void CAknIndicatorContainer::SetupIndicatorLayoutModes()
    {
    TInt mode  = SelectIndicatorLayoutMode();
    TInt count = iIndicators->Count();
    for ( TInt ii = 0; ii < count; ii++ )
        {
        iIndicators->At( ii )->SetLayoutMode(
            (CAknIndicator::TLayoutMode) mode );
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::SelectIndicatorLayoutMode
// Decides the layout mode to be used for indicators inside this container.
// ---------------------------------------------------------------------------
//
TInt CAknIndicatorContainer::SelectIndicatorLayoutMode()
    {
    // Usually this can be used to decide mode...
    TInt mode = ( Rect().Height() > Rect().Width() ) ?
        CAknIndicator::ELayoutModeUsual :
        CAknIndicator::ELayoutModeWide;

    // But one exception is idle where we can have vertical indicators using "wide" mode.
    if ( iIndicatorContext == EUniversalIndicators &&
         AknStatuspaneUtils::IdleLayoutActive() )
        {
        mode = CAknIndicator::ELayoutModeWide;

        // But exception to exception is portraitmode video telephony layout
        CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
        if ( statusPane )
            {
            TInt currentStatusPaneLayoutResId = statusPane->CurrentLayoutResId();
            if ( currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_VT ||
                 currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED )
                {
                mode = CAknIndicator::ELayoutModeUsual;
                }
            }
        }
    // Another thing is if universal indicators but not idle
    else if ( iIndicatorContext == EUniversalIndicators &&
              !AknStatuspaneUtils::IdleLayoutActive() )
        {
        mode = CAknIndicator::ELayoutModeUsual;
        }
    else if ( iIndicatorContext == EQueryEditorIndicators )
        {
        mode = CAknIndicator::ELayoutModeUsual;
        }

    return mode;
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::SizeChangedInIdleVertical
// Handles size change events of vertically arranged universal indicator
// pane in idle status pane layout.
// ---------------------------------------------------------------------------
//
void CAknIndicatorContainer::SizeChangedInIdleVertical()
    {
    TRect containerRect( Rect() );

    if ( iIndicatorContext == EUniversalIndicators )
        {
        iLayoutOrientation = EVertical;
        }

    // Available space for indicators
    TRect rect( containerRect );

    // If layout orientation has been changed since last call,
    // prioritize indicators again.
    if ( iLayoutOrientation != iPreviousLayoutOrientation )
        {
        TRAP_IGNORE ( PrioritizeIndicatorsL() );
        }

    iIndicatorsShown         = 0;
    iAnimatedIndicatorsShown = 0;
    TInt last                = iIndicators->Count() - 1;

    if ( iIndicatorContext == EUniversalIndicators )
        {
        TRect parent( rect );
        TAknLayoutRect layoutRect;

        layoutRect.LayoutRect(
            parent, AknLayoutScalable_Avkon::grid_indicator_pane() );
        parent = layoutRect.Rect();

        TRect indicatorRect( 0,0,0,0 );

        TInt maxNumberOfIndicatorsShown =
            AknLayoutScalable_Avkon::cell_indicator_pane_ParamLimits().LastRow();

        for ( TInt ii = 0; ii <= last; ii++ )
            {
            CAknIndicator* indicator = iIndicators->At( ii );
            if ( !indicator->IndicatorState() ||
                 indicator->Priority() == KIndicatorNotShown )
                {
                // Indicator is not shown on current layout even it is set ON.
                continue;
                }

            layoutRect.LayoutRect(
                parent,
                AknLayoutScalable_Avkon::cell_indicator_pane( iIndicatorsShown ) );
            indicatorRect = layoutRect.Rect();
            indicator->SetRect( indicatorRect );

            iIndicatorsShown++;

            if ( iIndicatorsShown > maxNumberOfIndicatorsShown )
                {
                indicator->SetExtent( TPoint( 0, 0 ), TSize( 0, 0 ) );
                break;
                }

            if ( indicator->IndicatorState() == MAknIndicator::EIndicatorAnimate )
                {
                iAnimatedIndicatorsShown++;
                }
            } // for

        ResetAnimTicker( iExtension->iIsForeground );

        } // if universal indicators
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::CreateIndicatorFromResourceL
// Constructs a status indicator from an indicator resource.
// ---------------------------------------------------------------------------
//
EXPORT_C TUid CAknIndicatorContainer::CreateIndicatorFromResourceL(
    TInt aIndicatorResourceId,
    TInt aCustomIndicatorFlags )
    {
    CAknIndicator* newIndicator =
        new (ELeave) CAknIndicator ( iIndicatorContext );
    CleanupStack::PushL( newIndicator );
    newIndicator->SetContainerWindowL( *this );

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, aIndicatorResourceId );
    newIndicator->ConstructFromResourceL( reader, this );
    CleanupStack::PopAndDestroy();  // resource reader

    // Always assign a dynamic UID to avoid clash with pre-defined indicators
    TInt dynamicUid = EAknNaviPaneEditorIndicatorDynamicUidRangeFirst;
    TInt count      = iIndicators->Count();

    // Loop through indicators and try to find a free dynamic UID.
    while ( dynamicUid <= EAknNaviPaneEditorIndicatorDynamicUidRangeLast )
        {
        for ( TInt ii = 0; ii < count; ii++ )
            {
            CAknIndicator* indicator = iIndicators->At( ii );
            if ( indicator->iUid == dynamicUid )
                {
                dynamicUid++;
                break;
                }
            }
        break;
        }

    if ( dynamicUid <= EAknNaviPaneEditorIndicatorDynamicUidRangeLast )
        {
        newIndicator->iUid = dynamicUid;
        }
    else
        {
        User::Leave( KErrGeneral ); // All dynamic UIDs already in use.
        }


    // Handle flags here
    if ( aCustomIndicatorFlags & EMultiColorIndicator )
        {
        newIndicator->SetMultiColorMode( ETrue );
        }

    if ( aCustomIndicatorFlags & EIndicatorPositionInverted )
        {
        newIndicator->SetIndicatorPosition( ELeftSide );
        }
    else
        {
        newIndicator->SetIndicatorPosition( ERightSide );
        }

    // Finally add the new indicator and prioritize all.
    TUid uid = TUid::Uid( newIndicator->iUid );
    iIndicators->AppendL( newIndicator );
    CleanupStack::Pop( newIndicator );
    newIndicator = NULL;

    PrioritizeIndicatorsL();

    return uid;
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::ReplaceIndicatorIconL
// Replaces the icon of an existing indicator.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknIndicatorContainer::ReplaceIndicatorIconL(
    TUid aIndicator,
    TInt /*aState*/,
    TInt aLayoutMode,
    CFbsBitmap* aIconBitmap,
    CFbsBitmap* aIconMask,
    TInt aIconIndex )
    {
    TInt count = iIndicators->Count();
    CAknIndicator* indicator = NULL;
    for ( TInt ii = 0; ii < count; ii++ )
        {
        indicator = iIndicators->At( ii );
        if ( indicator && indicator->iUid == aIndicator.iUid )
            {
            // This ensures all default bitmaps are created.
            indicator->CreateLoadedIndicatorBitmapsL();

            if ( aIconBitmap &&
                 indicator->iIndicatorBitmaps[aLayoutMode]->At( aIconIndex ) )
                {
                delete indicator->iIndicatorBitmaps[aLayoutMode]->At( aIconIndex );
                indicator->iIndicatorBitmaps[aLayoutMode]->At( aIconIndex ) = aIconBitmap;
                }

            if ( aIconMask &&
                 indicator->iIndicatorBitmaps[aLayoutMode]->At( aIconIndex + 1 ) )
                {
                delete indicator->iIndicatorBitmaps[aLayoutMode]->At( aIconIndex + 1 );
                indicator->iIndicatorBitmaps[aLayoutMode]->At( aIconIndex + 1 ) = aIconMask;
                }

            break;
            }
        }

    if ( indicator &&
        ( indicator->IndicatorState() || indicator->Priority() != KIndicatorNotShown ) )
        {
        SizeChanged();
        DrawDeferred();
        }
    }

// ---------------------------------------------------------------------------
// CAknIndicatorContainer::CreateIndicatorFromPaneResourceL
// Creates a status indicator from an indicator pane resource.
// ---------------------------------------------------------------------------
//
void CAknIndicatorContainer::CreateIndicatorFromPaneResourceL(
    TUid aUid,
    TInt aIndicatorPaneResourceId,
    TInt aCustomIndicatorFlags )
    {
    TResourceReader res;
    iEikonEnv->CreateResourceReaderLC( res, aIndicatorPaneResourceId );

    TInt indicatorCount = res.ReadInt16();
    for ( TInt ii = 0; ii < indicatorCount; ii++ )
        {
        TInt foundUid = res.ReadInt16();
        if ( foundUid == aUid.iUid )
            {
            res.Rewind( sizeof( TInt16 ) );
            CAknIndicator* indicator =
                new (ELeave) CAknIndicator ( iIndicatorContext );
            CleanupStack::PushL( indicator );
            indicator->SetContainerWindowL( *this );
            indicator->ConstructFromResourceL( res, this );
            iIndicators->AppendL( indicator );

            if ( aCustomIndicatorFlags & EMultiColorIndicator )
                {
                indicator->SetMultiColorMode( ETrue );
                }

            // Editor indicator positions are set separately.
            if ( iIndicatorContext == EUniversalIndicators )
                {
                if ( aCustomIndicatorFlags & EIndicatorPositionInverted )
                    {
                    indicator->SetIndicatorPosition( ELeftSide );
                    }
                else
                    {
                    indicator->SetIndicatorPosition( ERightSide );
                    }
                }

            indicator->SetLayoutMode(
                (CAknIndicator::TLayoutMode) SelectIndicatorLayoutMode() );

            CleanupStack::Pop( indicator );
            indicator = NULL;
            break;
            }
        else
            {
            res.ReadInt16();
            res.ReadInt16();
            HBufC* bitmapFile = res.ReadHBufCL(); // bmp filename
            delete bitmapFile;
            bitmapFile = NULL;
            TInt numberOfStates = res.ReadInt16();  // Number of states
            for ( TInt i = 0; i < numberOfStates; i++ )
                {
                res.ReadInt16(); // State id
                TInt numberOfIcons = res.ReadInt16();
                for ( TInt j = 0; j < numberOfIcons; j++ )
                    {
                    for ( TInt jj = ELayoutModeUsual; jj <= ELayoutModeWide; jj++ )
                        {
                        res.ReadInt16(); // bitmaps
                        res.ReadInt16(); // mask
                        }
                    }
                }
            }
        }

    CleanupStack::PopAndDestroy();  // res
    }


// ---------------------------------------------------------------------------
// CAknIndicatorContainer::IndicatorExists
// Checks if an indicator already exists in the indicator array.
// ---------------------------------------------------------------------------
//
TBool CAknIndicatorContainer::IndicatorExists( TUid aUid ) const
    {
    TBool exists( EFalse );

    TInt count = iIndicators->Count();
    for ( TInt ii = 0; ii < count; ii++ )
        {
        if ( iIndicators->At( ii )->Uid() == aUid )
            {
            exists = ETrue;
            break;
            }
        }

    return exists;
    }

// ---------------------------------------------------------------------------
// CAknIndicatorContainer::CreateIncallBubbleL
// Creates the small incall status bubble.
// ---------------------------------------------------------------------------
//
void CAknIndicatorContainer::CreateIncallBubbleL()
    {
	// Create incall indicator, use empty rect.
	// Correct size is set in IncallBubbleSizeChanged.
    iIncallBubble = CIncallStatusBubble::NewL( TRect() );
    iIncallBubble->SetFlags( 0 );
    iIncallBubble->MakeVisible( EFalse );
    iIncallBubble->SetFaded( CAknSgcClient::IsSystemFaded() );
    }


TBool CAknIndicatorContainer::UpdateSmallLayoutL()
    {
    // Needed only if small status pane is in use.
    if ( AknStatuspaneUtils::SmallLayoutActive() )
        {
        CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();

        if ( statusPane )
            {
            TInt statusPaneCurrentLayoutResourceId = statusPane->CurrentLayoutResId();
            TInt statusPaneRequiredLayoutResourceId =
                AVKONENV->StatusPaneResIdForCurrentLayout(R_AVKON_STATUS_PANE_LAYOUT_SMALL);

            TInt last = iIndicators->Count() - 1;
            for (TInt j = 0; j <= last; j++)
                {
                CAknIndicator* indicator = iIndicators->At(j);
                TUid uid = indicator->Uid();

                if ( uid == TUid::Uid(EAknNaviPaneEditorIndicatorGprs) )
                    {
                    if ( indicator->IndicatorState() )
                        {
                        if ( AknLayoutUtils::LayoutMirrored() )
                            {
                            statusPaneRequiredLayoutResourceId =
                            AVKONENV->StatusPaneResIdForCurrentLayout(
                                R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED);
                            }
                        else
                            {
                            statusPaneRequiredLayoutResourceId =
                                AVKONENV->StatusPaneResIdForCurrentLayout(
                                    R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE);
                            }
                        break;
                        }
                    }
                }

            // switch layout if needed
            if ( statusPaneCurrentLayoutResourceId != statusPaneRequiredLayoutResourceId )
                {
                if (iExtension && !iExtension->iSwitchLayoutInProgress)
                    {
                    iExtension->iSwitchLayoutInProgress = ETrue;
                    statusPane->SwitchLayoutL( statusPaneRequiredLayoutResourceId );
                    return ETrue;
                    }
                }
            else
                {
                if (iExtension)
                    {
                    iExtension->iSwitchLayoutInProgress = EFalse;
                    }
                }
            }
        }

    // layout not changed
    return EFalse;
    }


void CAknIndicatorContainer::SetIncallBubbleDisabled( TBool aDisabled )
    {
    if ( iExtension )
        {
        iExtension->iIncallBubbleDisabled = aDisabled;
        }
    }

void CAknIndicatorContainer::ResetAnimTicker( TBool bForeground )
    {
    iExtension->iIsForeground = bForeground;

    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    TInt curId = R_AVKON_STATUS_PANE_LAYOUT_USUAL;
    if ( statusPane )
        {
        curId = statusPane->CurrentLayoutResId();
        }
    // if not foreground, cancel the timer
    if ( !iExtension->iIsForeground ||
            R_AVKON_STATUS_PANE_LAYOUT_EMPTY == curId )
        {
        if ( iTicker->IsActive() )
            {
            iTicker->Cancel();
            }
        return;
        }

    if ( !iTicker->IsActive() && iAnimatedIndicatorsShown > 0 )
        {
        iTicker->Start( KAknIndicatorAnimationShortDelay,
                        KAknIndicatorAnimationInterval,
                        TCallBack( TickerCallback, this ) );
        }
    else if ( iTicker->IsActive() && iAnimatedIndicatorsShown == 0 )
        {
        // Cancel animation timer if animated indicators
        // are not visible anymore.
        iTicker->Cancel();
        iSynchronizingValue = 0;
        }
    }

//  End of File
