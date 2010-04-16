/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Long Tap Detector with animation informing of long tap functionality
*
*/


#include <e32base.h>
#include <e32cmn.h>
#include <w32std.h>
#include <AknUtils.h>
#include <AknCapServerClient.h> // RAknUiServer
#include <AknSgcc.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknlongtapanimation.h>
#include <eiksrvs.h>
#include "AknPanic.h"
#include "aknlongtapdetector.h"

// CONSTANTS
const TInt KTimeDelayBeforeAnimation = 150000;  // 0,15 seconds
const TInt KLongTapDelay = 800000;              // 0,8 seconds

// ======== MEMBER FUNCTIONS ========


// ---------------------------------------------------------------------------
// CAknLongTapDetector::CAknLongTapDetector
// ---------------------------------------------------------------------------
//
CAknLongTapDetector::CAknLongTapDetector( MAknLongTapDetectorCallBack* aOwner )
    : CTimer( 0 ),
    iState( EWaiting ),
    iOwner( aOwner ),
    iTimeDelayBeforeAnimation( KTimeDelayBeforeAnimation ),
    iLongTapDelay( KLongTapDelay ),
    iPointerEvent(),
    iShowAnimation( ETrue )
    {
    }


// ---------------------------------------------------------------------------
// CAknLongTapDetector::ConstructL
// ---------------------------------------------------------------------------
//
void CAknLongTapDetector::ConstructL()
    {
    CTimer::ConstructL();
    CActiveScheduler::Add( this );
    }


// ---------------------------------------------------------------------------
// CAknLongTapDetector::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknLongTapDetector* CAknLongTapDetector::NewL( MAknLongTapDetectorCallBack* aOwner )
    {
    CAknLongTapDetector* self = CAknLongTapDetector::NewLC( aOwner );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknLongTapDetector::NewLC
// ---------------------------------------------------------------------------
//
EXPORT_C CAknLongTapDetector* CAknLongTapDetector::NewLC( MAknLongTapDetectorCallBack* aOwner )
    {
    CAknLongTapDetector* self = new ( ELeave ) CAknLongTapDetector( aOwner );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknLongTapDetector::~CAknLongTapDetector
// ---------------------------------------------------------------------------
//
EXPORT_C CAknLongTapDetector::~CAknLongTapDetector()
    {
    Cancel(); // CTimer
    delete iAnimation;
    }


// ---------------------------------------------------------------------------
// CAknLongTapDetector::PointerEventL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknLongTapDetector::PointerEventL( const TPointerEvent& aEvent )
    {
    // offset is now 2 layout units, if the pointer is dragged just a few 
    // pixels from the original point, long tap is not cancelled. 
    TInt offset = AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine().iW * 2 / 5;
    if ( ( iState == EShowingAnimation || iState == EWaitingForAnimation ) 
            && aEvent.iType == TPointerEvent::EDrag 
    )
        {
        TPoint aCenter = iPointerEvent.iPosition; 
        TRect rect( aCenter.iX - offset, aCenter.iY - offset, 
            aCenter.iX + offset, aCenter.iY + offset ); 
        if ( rect.Contains( aEvent.iPosition ) )
            {
            return; 
            }
        }

    Cancel();

    iPointerEvent = aEvent;
    
    const TWsEvent& lastEvent = CCoeEnv::Static()->LastEvent();
        
    CCoeControl* windowControl = 
        reinterpret_cast<CCoeControl*>( lastEvent.Handle() );
        
    if ( windowControl && windowControl->DrawableWindow() && 
        lastEvent.Type() == EEventPointer )
        {
        iPointerEvent.iParentPosition = iPointerEvent.iPosition +
            windowControl->DrawableWindow()->AbsPosition();
        }

    if ( iShowAnimation && iState == EWaiting 
            && aEvent.iType == TPointerEvent::EButton1Down )
        {
        iState = EWaitingForAnimation;
        After( TTimeIntervalMicroSeconds32( iTimeDelayBeforeAnimation ) );
        }
    else
        {
        iState = EWaiting;
        }
    }


// ---------------------------------------------------------------------------
// CAknLongTapDetector::SetTimeDelayBeforeAnimation
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknLongTapDetector::SetTimeDelayBeforeAnimation( 
        const TInt aMicroSeconds )
    {
    if ( aMicroSeconds >= 0 )
        {
        iTimeDelayBeforeAnimation = aMicroSeconds;
        }
    }


// ---------------------------------------------------------------------------
// CAknLongTapDetector::SetLongTapDelay
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknLongTapDetector::SetLongTapDelay( const TInt aMicroSeconds )
    {
    // update longtap delay time only if it is reasonable
    if ( ( aMicroSeconds >= 0 ) && 
            ( aMicroSeconds > iTimeDelayBeforeAnimation ) )
        {
        iLongTapDelay = aMicroSeconds;
        }
    }


// ---------------------------------------------------------------------------
// CAknLongTapDetector::IsAnimationRunning
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknLongTapDetector::IsAnimationRunning() const
    {
    return iState == EShowingAnimation;
    }

// ---------------------------------------------------------------------------
// CAknLongTapDetector::CancelAnimationL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknLongTapDetector::CancelAnimationL()
    {
    Cancel();
    }
    
// ---------------------------------------------------------------------------
// CAknLongTapDetector::EnableLongTapAnimation
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknLongTapDetector::EnableLongTapAnimation( 
        const TBool aAnimation )
    {
    iShowAnimation = aAnimation;
    }


// ---------------------------------------------------------------------------
// CAknLongTapDetector::RunL
// ---------------------------------------------------------------------------
//
void CAknLongTapDetector::RunL()
    {
    switch ( iState )
        {
        case EWaitingForAnimation:
            {
            iState = EShowingAnimation;
            StartAnimationL();

            After( TTimeIntervalMicroSeconds32( iLongTapDelay - iTimeDelayBeforeAnimation ) );
            break;
            }
        case EShowingAnimation:
            {
            iState = EWaiting;
            StopAnimation();

            // Report long tap to owner with locations related to both owner rect and screen rect.
            iOwner->HandleLongTapEventL( iPointerEvent.iPosition, iPointerEvent.iParentPosition );
            break;
            }
        default:
            {
            // we should never end up here.
            User::Panic( _L( "LongTapDetector" ), EAknPanicSelfCheckFailure );
            break;
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknLongTapDetector::DoCancel
// -----------------------------------------------------------------------------
//
void CAknLongTapDetector::DoCancel()
    {
    CTimer::DoCancel();
    
    if ( iState == EShowingAnimation )
        {
        StopAnimation();
        }
    }


// -----------------------------------------------------------------------------
// CAknLongTapDetector::StartAnimationL
// -----------------------------------------------------------------------------
//
void CAknLongTapDetector::StartAnimationL()
    {
    if ( iAnimation )
        {
        CCoeEnv::Static()->AddMessageMonitorObserverL( *this );
        iAnimation->ShowAnimationL( iPointerEvent.iParentPosition.iX, 
                iPointerEvent.iParentPosition.iY );
        }
    else
        {
        CCoeEnv::Static()->AddMessageMonitorObserverL( *this );
        RAknUiServer* uiServer = CAknSgcClient::AknSrv();
        
        TInt error = uiServer->ShowLongTapAnimation( iPointerEvent );
        
        if ( error == KErrCouldNotConnect )
            {
            iAnimation = CAknLongTapAnimation::NewL();
            iAnimation->ShowAnimationL( iPointerEvent.iParentPosition.iX, 
                    iPointerEvent.iParentPosition.iY );
            }
        else if ( error != KErrNone )
            {
            User::Leave( error );
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknLongTapDetector::StopAnimation
// -----------------------------------------------------------------------------
//
void CAknLongTapDetector::StopAnimation()
    {
    if ( iAnimation )
        {
        CCoeEnv::Static()->RemoveMessageMonitorObserver( *this );
        iAnimation->HideAnimation();
        }
    else
        {
        CCoeEnv::Static()->RemoveMessageMonitorObserver( *this );
        RAknUiServer* uiServer = CAknSgcClient::AknSrv();
        uiServer->HideLongTapAnimation();
        }
    }


// -----------------------------------------------------------------------------
// CAknLongTapDetector::MonitorWsMessage
// -----------------------------------------------------------------------------
//
void CAknLongTapDetector::MonitorWsMessage(const TWsEvent& aEvent)
    {
    if ( aEvent.Type() == EEventKey || aEvent.Type() == EEventKeyUp 
            || aEvent.Type() == EEventKeyDown || (aEvent.Type() == EEventPointer
            && aEvent.Pointer()->iType == TPointerEvent::EButton1Up ) )
		{
        Cancel();
        iState = EWaiting;		
	    }
    }

//  End of File
