/*
* Copyright (c) 2005, 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of CAknInfoPopupNoteController class.
*
*/



// INCLUDE FILES

#include <AknPictographInterface.h>

#include <AknsDrawUtils.h>
#include <AknsFrameBackgroundControlContext.h>
#include <eiklabel.h>
#include <gulicon.h>

#include <eikdef.h>
#include <coeaui.h>

#include <e32base.h>
#include <aknappui.h>
#include <aknsoundsystem.h>

#include "akntextcontrol.h"

#include "AknInfoPopupNoteController.h"
#include "AknInfoPopupNote.h"


// CONSTANTS
const TInt KInfoPopupNoteTimeDelayBeforeShow = 1000000;  // 1 seconds
const TInt KInfoPopupNoteTimeInView          = 10000000; // 10 seconds
const TInt KFromMillisecToMicrosecMultiplier = 1000;
const TInt KObserverArrayGranularity         = 1;


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknInfoPopupNoteController
//
// -----------------------------------------------------------------------------
//
CAknInfoPopupNoteController::CAknInfoPopupNoteController()
    : CTimer( 0 ),
    iState( CAknInfoPopupNoteController::EHidden ),
    iObservers( KObserverArrayGranularity ),
    iTimeDelayBeforeShow( KInfoPopupNoteTimeDelayBeforeShow ),
    iTimeInView( KInfoPopupNoteTimeInView ),
    iTone( ENoTone )
    {
    }

// -----------------------------------------------------------------------------
// ConstructL
//
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNoteController::ConstructL()
    {
    iPopup = CAknInfoPopupNote::NewL( *this );
    CTimer::ConstructL();
    CActiveScheduler::Add( this );
    }

// -----------------------------------------------------------------------------
// NewL
//
// -----------------------------------------------------------------------------
//
EXPORT_C CAknInfoPopupNoteController* CAknInfoPopupNoteController::NewL()
    {
    CAknInfoPopupNoteController* self = new( ELeave ) CAknInfoPopupNoteController();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// -----------------------------------------------------------------------------
// ~CAknInfoPopupNoteController
//
// -----------------------------------------------------------------------------
//
CAknInfoPopupNoteController::~CAknInfoPopupNoteController()
    {
    Cancel();
    if ( iPopup )
        {
        delete iPopup;
        }
    iObservers.Reset();
    }

// -----------------------------------------------------------------------------
// SetShowTime
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::SetTimeDelayBeforeShow( TInt aMilliSeconds )
    {
    if ( aMilliSeconds >= 0 )
        {
        iTimeDelayBeforeShow = KFromMillisecToMicrosecMultiplier * aMilliSeconds;
        }
    }

// -----------------------------------------------------------------------------
// SetHideTime
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::SetTimePopupInView( TInt aMilliSeconds )
    {
    iTimeInView = KFromMillisecToMicrosecMultiplier * aMilliSeconds;
    }

// -----------------------------------------------------------------------------
// SetTextL
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::SetTextL( const TDesC& aText )
    {
    iPopup->SetTextL( aText );
    }

// -----------------------------------------------------------------------------
// ShowInfoPopupNote
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::ShowInfoPopupNote()
    {
    // cancel the timer and hide the popup, this also sets initial state
    Cancel();
    
    if(iPopup->IsVisible())
    {
    	return;
    }

    if ( iPopup->GetText() == KNullDesC() )  // if text isn't set before at all
        {
        return;
        }

    // set up timer to wait default of one second before showing the popup
    iState = CAknInfoPopupNoteController::EWaitingToShow;
    After( TTimeIntervalMicroSeconds32( iTimeDelayBeforeShow ) );
    }

// -----------------------------------------------------------------------------
// HideInfoPopupNote
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::HideInfoPopupNote()
    {
    if ( iTimeInView > 0)
        {
        Cancel();
        
        // If the button from which info popup note was launched,
        // has keyrepeat timer, the previous Cancel() -call won't
        // cause DoCancel() call. TSW Error RYPA-7DYCCY.
        if( iPopup->IsVisible() ) 
	        {
	        DoCancel();
	        }
	        
        __ASSERT_ALWAYS( !iPopup->IsVisible(), 
            User::Panic(_L("Info popup note assert"), KErrUnknown));
        }        
    else
        {
        iState = CAknInfoPopupNoteController::EHidden;
        iPopup->Hide();
        Cancel();
        }
    }

// -----------------------------------------------------------------------------
// AddObserverL
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::AddObserverL(
        const MAknInfoPopupNoteObserver& aObserver )
    {
    iObservers.InsertInAddressOrderL( &aObserver );
    }

// -----------------------------------------------------------------------------
// RemoveObserver
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::RemoveObserver(
        const MAknInfoPopupNoteObserver& aObserver )
    {
    TInt index = iObservers.FindInAddressOrder( &aObserver );
    if ( index != KErrNotFound )
        {
        iObservers.Remove( index );
        }
    }

// -----------------------------------------------------------------------------
// SetPositionAndAlignment
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::SetPositionAndAlignment(
        const TPoint& aPosition, const TGulAlignmentValue& aAlignment )
    {
    iPopup->SetPositionAndAlignment( aPosition, aAlignment );
    }

// -----------------------------------------------------------------------------
// SetPositionByHighlight
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::SetPositionByHighlight(
        const TRect& aHighlightRect )
    {
    iPopup->SetPositionByHighlight( aHighlightRect );
    }

// -----------------------------------------------------------------------------
// RestoreDefaultPosition
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::RestoreDefaultPosition()
    {
    iPopup->RestoreDefaultPosition();
    }

// -----------------------------------------------------------------------------
// SetTooltipModeL
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::SetTooltipModeL(
        const TBool aTooltipMode )
    {
    iPopup->SetTooltipModeL( aTooltipMode );
    }

// -----------------------------------------------------------------------------
// HideWhenAppFaded
//
// -----------------------------------------------------------------------------
//

EXPORT_C void CAknInfoPopupNoteController::HideWhenAppFaded( const TBool aHide )
    {
    iPopup->HideWhenAppFaded( aHide );
    }

// -----------------------------------------------------------------------------
// NotifyObservers
//
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNoteController::NotifyObservers(
        MAknInfoPopupNoteObserver::TAknInfoPopupNoteEvent aEvent )
    {
    for ( TInt i = 0; i < iObservers.Count(); ++i )
        {
        iObservers[i]->HandleInfoPopupNoteEvent( this, aEvent );
        }
    }

// -----------------------------------------------------------------------------
// CAknInfoPopupNoteController::SetTone
// Set the tone to be played
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknInfoPopupNoteController::SetTone( const TTone& aTone )
    {
    iTone = aTone;
    }

// -----------------------------------------------------------------------------
// RunL
//
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNoteController::RunL()
    {
    switch ( iState )
        {
        case CAknInfoPopupNoteController::EWaitingToShow:
            iState = CAknInfoPopupNoteController::EShowing;
            PlayTone();
            iPopup->ShowL();
            if ( iTimeInView > 0 )
                {
                After( TTimeIntervalMicroSeconds32( iTimeInView ) );    
                }
            break;

        case CAknInfoPopupNoteController::EShowing:
            iState = CAknInfoPopupNoteController::EHidden;
            iPopup->Hide();
            break;

        default:
            User::Panic( _L( "Info popup note" ), KErrUnknown );
        }
    }

// -----------------------------------------------------------------------------
// CAknInfoPopupNoteController::PlayTone
// Play the tone
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNoteController::PlayTone()
    {
    if ( ( iTone != ENoTone ) && ( CEikonEnv::Static()->AppUi() ) )
        {
        iAvkonAppUiBase->KeySounds()->PlaySound( iTone );
        }
    }

// -----------------------------------------------------------------------------
// CAknInfoPopupNoteController::DoCancel
// Implements cancellation of asynchronous operation.
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNoteController::DoCancel()
    {
    CTimer::DoCancel();
    iState = CAknInfoPopupNoteController::EHidden;
    iPopup->Hide();
    }

//  End of File
