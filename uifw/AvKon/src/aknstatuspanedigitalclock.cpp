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
* Description:  Implementation for digital clock status pane control.
*
*/


// SYSTEM INCLUDE FILES
#include <eikspane.h>
#include <AknsDrawUtils.h>
#include <AknsUtils.h>
#include <AknDef.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknStatuspaneUtils.h>

#include <AknTasHook.h> // for testability hooks
// USER INCLUDE FILES
#include "aknstatuspanedigitalclock.h"
#include "akndigitalclock.h"


// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::CAknStatuspaneDigitalClock
// C++ default constructor can NOT contain any code, that
// might leave.
// ---------------------------------------------------------------------------
//
CAknStatuspaneDigitalClock::CAknStatuspaneDigitalClock()
    : iInForeground( EFalse )
    {
    AKNTASHOOK_ADD( this, "CAknStatuspaneDigitalClock" );
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknStatuspaneDigitalClock::~CAknStatuspaneDigitalClock()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition( this );

    iCoeEnv->RemoveMessageMonitorObserver( *this );

    delete iClock;
    delete iLight;
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::ConstructFromResourceL
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknStatuspaneDigitalClock::ConstructFromResourceL(
    TResourceReader& /*aReader*/ )
    {
    // We observe foreground events in order
    // to stop the clock timer if clock is not visible.
    iCoeEnv->AddMessageMonitorObserverL( *this );

    SetComponentsToInheritVisibility( ETrue );

    iClock = CAknDigitalClock::NewL( this, ETrue );
    iClock->ActivateL();

    /* Register MHWRMLightObserver */
    iLight = CHWRMLight::NewL( this );
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::SizeChanged
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknStatuspaneDigitalClock::SizeChanged()
    {
    SetContainerWindowNonFading(
        AknStatuspaneUtils::ExtendedStaconPaneActive());


    TPoint tl( Rect().iTl );
    iClock->SetExtent( tl, Size() );

    // Set layout for extended statuspane layout (portrait)

    TAknTextLineLayout clockLayout =
        AknLayoutScalable_Avkon::clock_nsta_pane_t1().LayoutLine();

    if ( AknStatuspaneUtils::ExtendedStaconPaneActive() )
        {
        clockLayout =
            AknLayoutScalable_Avkon::clock_nsta_pane_cp2_t1().LayoutLine();
        }
    else if ( AknStatuspaneUtils::ExtendedFlatLayoutActive() )
        {
        clockLayout =
            AknLayoutScalable_Avkon::clock_nsta_pane_cp_t1().LayoutLine();
        }

    iClock->SetTimeLayout( clockLayout );

    TRgb color = KRgbBlack;

    if ( AknStatuspaneUtils::ExtendedStaconPaneActive() ||
         AknStatuspaneUtils::HDLayoutActive() )
        {
        // Set color for stacon pane layout (landscape)
        AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                   color,
                                   KAknsIIDQsnIconColors,
                                   EAknsCIQsnIconColorsCG20 );
        }
    else if (AknStatuspaneUtils::ExtendedFlatLayoutActive())
        {
        // Set color for flat status pane layout (landscape).
        // Actually clock is in control pane area in this case.
        // Uses right sk color
        if ( AknStatuspaneUtils::IdleLayoutActive() )
            {
            AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                       color,
                                       KAknsIIDQsnTextColors,
                                       EAknsCIQsnTextColorsCG16 );
            }
        else
            {
            AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                       color,
                                       KAknsIIDQsnTextColors,
                                       EAknsCIQsnTextColorsCG14 );
            }
        }
    else
        {
        // Set color for extended statuspane layout (portrait)
        AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                   color,
                                   KAknsIIDQsnIconColors,
                                   EAknsCIQsnIconColorsCG2 );
        }

    AknsUtils::RegisterControlPosition( this );

    iClock->SetColor( color );
    iClock->DrawDeferred();
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::MakeVisible
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknStatuspaneDigitalClock::MakeVisible( TBool aVisible )
    {
    CAknControl::MakeVisible( aVisible );

	if ( iClock )
	    {
	    if ( !aVisible )
    	    {
    	    // Stop the timer if this control is made non-visible.
    	    // This control may exist in status pane layouts which
    	    // don't show clock, and in those it's hidden via
    	    // this method, so no need to keep the timer running.
        	iClock->StopTimer();
    	    }
	    else if ( aVisible && iInForeground )
	        {
	        iClock->StartTimer();
	        }
	    }
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::CountComponentControls
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
TInt CAknStatuspaneDigitalClock::CountComponentControls() const
    {
    return iClock ? 1 : 0;
    }

// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::ComponentControl
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
CCoeControl* CAknStatuspaneDigitalClock::ComponentControl(
    TInt /*aIndex*/ ) const
    {
    return iClock;
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::Draw
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknStatuspaneDigitalClock::Draw( const TRect& /*aRect*/ ) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    CWindowGc& gc = SystemGc();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    AknsDrawUtils::Background( skin, cc, this, gc, Rect() );
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::SetDimmed
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknStatuspaneDigitalClock::SetDimmed( TBool aDimmed )
    {
    CCoeControl::SetDimmed( aDimmed );
    if ( iClock )
        {
        iClock->SetDimmed( aDimmed );
        }
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::HandleResourceChange
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknStatuspaneDigitalClock::HandleResourceChange( TInt aType )
    {
    if( iClock )
        {
        iClock->HandleResourceChange( aType );
        }

    if ( aType == KEikDynamicLayoutVariantSwitch ||
         aType == KEikColorResourceChange ||
         aType == KAknsMessageSkinChange )
        {
        SizeChanged();
        DrawDeferred();
        }
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::SetContainerWindowNonFading
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknStatuspaneDigitalClock::SetContainerWindowNonFading(
    TBool aNonFading )
    {
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if ( statusPane )
        {
        CCoeControl* control = NULL;
        TRAP_IGNORE( control = statusPane->ContainerControlL(
                                 TUid::Uid( EEikStatusPaneUidDigitalClock ) ) );
        if ( control )
            {
            control->DrawableWindow()->SetNonFading( aNonFading );
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::MonitorWsMessage
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknStatuspaneDigitalClock::MonitorWsMessage( const TWsEvent& aEvent )
    {
    switch ( aEvent.Type() )
        {
        case KAknFullOrPartialForegroundGained:
            {
            iInForeground = ETrue;

            TRAP_IGNORE( ForegroundGainedL() );

            break;
            }

        case KAknFullOrPartialForegroundLost:
            {
            iInForeground = EFalse;

            iClock->StopTimer();

            break;
            }

        default:
            break;
        }
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneDigitalClock::ForegroundGainedL
// Contains the leaving function calls in the foreground gain situation.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneDigitalClock::ForegroundGainedL()
    {
    if ( IsVisible() )
        {
        iClock->StartTimer();
        }
    }

void CAknStatuspaneDigitalClock::LightStatusChanged(TInt aTarget, 
                                                    CHWRMLight::TLightStatus aStatus)
    {
    if( aTarget == CHWRMLight::EPrimaryDisplay
        || aTarget == CHWRMLight::EPrimaryDisplayAndKeyboard )
        {
        if( aStatus == CHWRMLight::ELightOn && iInForeground )
            {
            iClock->StartTimer();
            }
        else if( aStatus == CHWRMLight::ELightOff )
            {
            iClock->StopTimer();
            }
        }
    }

//  End of File
