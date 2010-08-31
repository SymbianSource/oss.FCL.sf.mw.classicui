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
* Description:  Control for status pane's battery pane.
*
*/


// INCLUDE FILES
#include <coemain.h>
#include <barsread.h>
#include <avkon.mbg>
#include <AknsDrawUtils.h>
#include <eikspane.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>

#include <AknTasHook.h>
#include "AknUtils.h"
#include "aknconsts.h"
#include "AknBattery.h"
#include "AknStatuspaneUtils.h"
#include "AknBatteryIcon.h"
#include "AknBatteryStrength.h"
#include "aknappui.h"
#include "AknDef.h"
#include "aknbatterydataobserver.h"


// Flags for battery pane
enum TBatteryPaneControlFlags
    {
    EAknBatteryPaneButton1DownInBatteryRect = 0x00000001
    };

// Battery recharge animation frame interval.
const TInt KBatteryRechargeTick = 500000; // 0.5 seconds


// ---------------------------------------------------------------------------
// CAknBatteryPane::CAknBatteryPane
// Default constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknBatteryPane::CAknBatteryPane()
    {
    AKNTASHOOK_ADD( this, "CAknBatteryPane" );
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::~CAknBatteryPane
// Destructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknBatteryPane::~CAknBatteryPane()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition( this );

    delete iBatteryIconControl;
    delete iBatteryStrengthControl;

    if ( iTicker )
        {
        iTicker->Cancel();
        }

    delete iTicker;
    delete iDataObserver;
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::ConstructL
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryPane::ConstructL()
    {
    iBatteryIconControl = CAknBatteryIcon::NewL();
    iBatteryIconControl->SetContainerWindowL( *this );
    iBatteryStrengthControl = CAknBatteryStrength::NewL();
    iBatteryStrengthControl->SetContainerWindowL( *this );
    iPrivateFlags = 0; // reset flags
    iDataObserver = new (ELeave) CAknBatteryDataObserver( this );
    iIsActiveIdle = AknStatuspaneUtils::IsActiveIdle();
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::ConstructFromResourceL
// Resource constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryPane::ConstructFromResourceL(
    TResourceReader& aReader )
    {
    ConstructL();
    SetBatteryLevel( aReader.ReadInt16() ); // Initial battery level.
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::SetBatteryLevel
// Sets the battery level.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryPane::SetBatteryLevel( TInt aLevel )
    {
    iBatteryLevel = aLevel;

    if ( !iBatteryStrengthControl->Recharging() )
        {
        iBatteryStrengthControl->SetBatteryLevel( aLevel );
        DrawDeferred();
        }
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::BatteryLevel
// Returns the current battery level.
// ---------------------------------------------------------------------------
//
TInt CAknBatteryPane::BatteryLevel()
    {
    return iBatteryLevel;
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::SetRecharge
// Sets the recharging state on/off.
// ---------------------------------------------------------------------------
//
void CAknBatteryPane::SetRecharge( TBool aRecharging )
    {
    if ( aRecharging )
        {
        if ( !iBatteryStrengthControl->Recharging() )
            {
            if ( !iTicker )
                {
                TRAP_IGNORE( iTicker = CPeriodic::NewL(
                                CActive::EPriorityLow ) );
                }
            else
                {
                iTicker->Cancel();
                }

            if ( iTicker )
                {
                iTicker->Start( KBatteryRechargeTick,
                                KBatteryRechargeTick,
                                TCallBack( TickerCallback, this ) );
                }
            }
        }

    iBatteryStrengthControl->SetRecharging( aRecharging );

    if ( !iBatteryStrengthControl->Recharging() )
        {
        SetBatteryLevel( iBatteryLevel ); // Set battery level to right value.
        }
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::Recharging
// Returns the current recharging state.
// ---------------------------------------------------------------------------
//
TBool CAknBatteryPane::Recharging()
    {
    if ( iBatteryStrengthControl )
        {
        return iBatteryStrengthControl->Recharging();
        }
    else
        {
        return EFalse;
        }
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::BatteryState
// Returns the current battery state.
// ---------------------------------------------------------------------------
//
TInt CAknBatteryPane::BatteryState()
    {
    if ( iBatteryIconControl )
        {
        return iBatteryIconControl->IconState();
        }
    else
        {
        return KErrNotFound;
        }
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::SetBatteryStateL
// Sets the battery state.
// ---------------------------------------------------------------------------
//
void CAknBatteryPane::SetBatteryStateL( TInt aState )
    {
    // Change battery icon only if the new state is
    // different than the current one.
    if ( iBatteryIconControl &&
         iBatteryIconControl->IconState() != aState )
        {
        iBatteryIconControl->SetBatteryIconL( aState );
        }
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::TickerCallback
// Static callback function for recharge animation timer.
// ---------------------------------------------------------------------------
//
TInt CAknBatteryPane::TickerCallback( TAny* aThis )
    {
    return static_cast<CAknBatteryPane*>( aThis )->DoTick();
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::DoTick
// Callback function for recharge animation timer.
// ---------------------------------------------------------------------------
//
TInt CAknBatteryPane::DoTick()
    {
    if ( !iBatteryStrengthControl->Recharging() )
        {
        iTicker->Cancel();
        return EFalse;
        }

    TInt newLevel = iBatteryStrengthControl->BatteryLevel() + 1;

    if ( newLevel > KBatteryLevelMax )
        {
        newLevel = KBatteryLevelMin;
        }

    iBatteryStrengthControl->SetBatteryLevel( newLevel );
    DrawDeferred(); // Must be DrawDeferred (not DrawNow) so that we don't
                    // block application thread in high load situations
    return ETrue;
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::SizeChanged
// Handles size change events.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryPane::SizeChanged()
    {
    // No fading if staconpane is active.
    SetContainerWindowNonFading( AknStatuspaneUtils::StaconPaneActive() );

    TAknWindowComponentLayout batteryIconLayout;
    TAknWindowComponentLayout batteryStrenghtLayout;

    TRect parent( Rect() );

    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        // Battery pane in STACONPANE layout
        // battery pane in status/controlpane layout used e.g. in landscape modes
        // layout 0.75 has new varieties
        TInt varietyIndex = AknStatuspaneUtils::StaconSoftKeysLeft() ? 1 : 0;
        batteryIconLayout =
            AknLayoutScalable_Avkon::battery_pane_stacon_g2( varietyIndex );
        batteryStrenghtLayout =
            AknLayoutScalable_Avkon::battery_pane_stacon_g1( varietyIndex );
        }
    else if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        batteryIconLayout = AknLayoutScalable_Avkon::battery_pane_g2( 1 );
        batteryStrenghtLayout = AknLayoutScalable_Avkon::battery_pane_g1( 1 );
        }
	 else if ((AknStatuspaneUtils::CurrentStatusPaneLayoutResId() 
                 == R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE ||
             AknStatuspaneUtils::CurrentStatusPaneLayoutResId() 
                 == R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE_MIRRORED) &&
			    Layout_Meta_Data::IsLandscapeOrientation())
		  {
        batteryIconLayout = AknLayoutScalable_Avkon::battery_pane_g2(1);
        batteryStrenghtLayout = AknLayoutScalable_Avkon::battery_pane_g1(1);
	     }
    else
        {
        // Battery pane in NORMAL of WIDESCREEN STATUS PANE layout.
        TBool hdLayout( AknStatuspaneUtils::HDLayoutActive() );
        batteryIconLayout =
            AknLayoutScalable_Avkon::battery_pane_g2( hdLayout ? 2 : 0 );
        batteryStrenghtLayout =
            AknLayoutScalable_Avkon::battery_pane_g1( hdLayout ? 2 : 0 );
        }

    AknLayoutUtils::LayoutControl(
        iBatteryIconControl, parent, batteryIconLayout );

    AknLayoutUtils::LayoutControl(
        iBatteryStrengthControl, parent, batteryStrenghtLayout );

    AknsUtils::RegisterControlPosition( this );
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::SizeChanged
// Handles position change events.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryPane::PositionChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::Draw
// Draws the battery pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryPane::Draw( const TRect& /*aRect*/ ) const
    {
    if ( iIsActiveIdle )
        {
        return;
        }

    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        DrawInStaconPane( Rect() );
        }
    else if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        DrawInFlatStatusPane( Rect() );
        }
    else
        {
        DrawInNormalStatusPane( Rect() );
        }
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::HandleResourceChange
// Handles resource change events.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryPane::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );

    if ( aType == KEikDynamicLayoutVariantSwitch ||
         aType == KAknsMessageSkinChange )
        {
        DrawDeferred();
        }
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::CountComponentControls
// Returns the amount of component controls.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknBatteryPane::CountComponentControls() const
    {
    return 2;
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::ComponentControl
// Returns a component control by a control index.
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CAknBatteryPane::ComponentControl( TInt aIndex ) const
    {
    CCoeControl* control = NULL;

    switch ( aIndex )
        {
        case 0:
            {
            control = iBatteryStrengthControl;
            break;
            }
        case 1:
            {
            control = iBatteryIconControl;
            break;
            }
        }

    return control;
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::DrawInNormalStatusPane
// Draws the battery pane in normal status pane layout.
// ---------------------------------------------------------------------------
//
void CAknBatteryPane::DrawInNormalStatusPane( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();
    TRect rect( Rect() );
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    // Solid or wipe comes from background
    if ( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
        {
        // Default drawing if skinning is not available
        gc.Clear( rect );
        gc.SetPenStyle( CGraphicsContext::ENullPen );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.SetBrushColor(
            AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
        gc.DrawRect( rect );
        }
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::DrawInStaconPane
// Draws the battery pane in stacon pane layout.
// ---------------------------------------------------------------------------
//
void CAknBatteryPane::DrawInStaconPane( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();
    TRect rect( Rect() );
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    if ( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
        {
        gc.SetPenStyle( CGraphicsContext::ENullPen );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.SetBrushColor(
            AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
        gc.DrawRect( rect );
        }
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::DrawInFlatStatusPane
// Draws the battery pane in flat status pane layout.
// ---------------------------------------------------------------------------
//
void CAknBatteryPane::DrawInFlatStatusPane( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();
    TRect rect( Rect() );
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    if ( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
        {
        gc.SetPenStyle( CGraphicsContext::ENullPen );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.SetBrushColor(
            AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
        gc.DrawRect( rect );
        }
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::ExtensionInterface
// Not implemented.
// ---------------------------------------------------------------------------
//
EXPORT_C void* CAknBatteryPane::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::HandlePointerEventL
// Processes battery pane's pointer events. Actually this does nothing yet.
// ---------------------------------------------------------------------------
//
void CAknBatteryPane::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( IsDimmed() )
            {
            iPrivateFlags &= (~EAknBatteryPaneButton1DownInBatteryRect);
            return;
            }

        // Get the rect of battery pane.
        TRect rect( Rect() );

        // Switch by type
        switch ( aPointerEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                {
                // if battery pane's rect contains pointer down position
                if ( rect.Contains( aPointerEvent.iPosition ) )
                    {
                    // set flag that pointerdown was inside battery pane
                    iPrivateFlags |= EAknBatteryPaneButton1DownInBatteryRect;
                    }
                }
                break;

            case TPointerEvent::EButton1Up:
                {
                // if battery pane's rect contains pointer down position and
                // Button1Down was clicked inside battery rect
                if ( iPrivateFlags&EAknBatteryPaneButton1DownInBatteryRect &&
                    rect.Contains( aPointerEvent.iPosition ) )
                    {
                    // Up happened inside battery pane's rect
                    // activate something
                    }

                // Up happened, reset button down flag
                iPrivateFlags &= (~EAknBatteryPaneButton1DownInBatteryRect);
                }
                break;

            default:
                break;
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknBatteryPane::SetContainerWindowNonFading
// Allows/disallows fading of battery pane.
// ---------------------------------------------------------------------------
//
void CAknBatteryPane::SetContainerWindowNonFading( TBool aNonFading )
    {
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if ( statusPane )
        {
        CCoeControl* control = NULL;
        TRAP_IGNORE( control = statusPane->ContainerControlL(
                                TUid::Uid( EEikStatusPaneUidBattery ) ) );
        if ( control )
            {
            control->DrawableWindow()->SetNonFading( aNonFading );
            }
        }
    }

//  End of File
