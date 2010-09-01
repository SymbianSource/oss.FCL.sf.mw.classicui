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
* Description:  Drag touch gesture recognizer.
*
*/

#include "akntouchgesturefwdefs.h"
#include "akntouchgesturefwevent.h"
#include "akntouchgesturefwdragrecognizer.h"
#include "akntouchgesturefwsettings.h"

using namespace AknTouchGestureFw;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwDragRecognizer* CAknTouchGestureFwDragRecognizer::NewL(
        CAknTouchGestureFwRecognitionEngine& aEngine )
    {
    CAknTouchGestureFwDragRecognizer* self =
        CAknTouchGestureFwDragRecognizer::NewLC( aEngine );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwDragRecognizer* CAknTouchGestureFwDragRecognizer::NewLC(
        CAknTouchGestureFwRecognitionEngine& aEngine )
    {
    CAknTouchGestureFwDragRecognizer* self
        = new ( ELeave ) CAknTouchGestureFwDragRecognizer( aEngine );
    CleanupStack::PushL( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwDragRecognizer::~CAknTouchGestureFwDragRecognizer()
    {
    }


// ---------------------------------------------------------------------------
// Returns the drag gesture group.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwGroup CAknTouchGestureFwDragRecognizer::GestureGroup() const
    {
    return EAknTouchGestureFwGroupDrag;
    }


// ---------------------------------------------------------------------------
// Cancels the drag gesture recognition.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwDragRecognizer::CancelRecognizing()
    {
    if ( iContinuousFeedback )
        {
        StopContinuousFeedback();
        iContinuousFeedback = EFalse;
        }
    if ( iDragDetected )
        {
        // We ignore the possible leave in order to ensure that the
        // state gets reset.
        TRAP_IGNORE( SendDragEventL( EAknTouchGestureFwStop ) );
        }
    Reset();
    }


// ---------------------------------------------------------------------------
// Handles single-touch pointer events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwDragRecognizer::HandleSinglePointerEventL(
        const TPointerEventData& aPointerData )
    {
    switch ( aPointerData.iPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            StartSingleRecognizing( aPointerData.iPointerEvent.iPosition );
            break;
            }
        case TPointerEvent::EDrag:
            {
            if ( iStartOnSingleTouchDrag )
                {
                // Start clears iStartOnSingleTouchDrag 
                StartSingleRecognizing( aPointerData.iPointerEvent.iPosition );
                }
            else
                {
                SingleRecognizeL( aPointerData.iPointerEvent.iPosition );
                }
            break;
            }
        case TPointerEvent::EButton1Up:
            {
            CompleteSingleRecognizingL();
            break;
            }
        default:
            {
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// Handles multi-touch pointer events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwDragRecognizer::HandleMultiPointerEventL(
    const TPointerEventData& aPointerData,
    const TPoint& /*aFirstPointerPosition*/,
    const TPoint& /*aSecondPointerPosition*/ )
    {
    switch ( aPointerData.iPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            // Multi touch begin completes single recognizing
            CompleteSingleRecognizingL();
            break;
            }
        case TPointerEvent::EDrag:
            {
            break;
            }
        case TPointerEvent::EButton1Up:
            {
            // Upon next single touch drag, start recognition.
            // Current position is not necessarily accurate.
            iStartOnSingleTouchDrag = ETrue;
            break;
            }
        default:
            {
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwDragRecognizer::CAknTouchGestureFwDragRecognizer(
        CAknTouchGestureFwRecognitionEngine& aEngine )
    : CAknTouchGestureFwBaseRecognizer( aEngine ),
      iStartPosition( 0, 0 ),
      iCurrentPosition( 0, 0 ),
      iPreviousPosition( 0, 0 ),
      iDragDetected( EFalse ),
      iDragArea()
    {
    Reset();
    }


// ---------------------------------------------------------------------------
// Starts recognizing the drag gesture.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwDragRecognizer::StartSingleRecognizing(
    const TPoint& aPointerPos )
    {
    iDragDetected = EFalse;
    iDragArea.Start( aPointerPos );
    iStartPosition = aPointerPos;
    iCurrentPosition = aPointerPos;
    iPreviousPosition.SetXY( 0, 0 );
    iStartOnSingleTouchDrag = EFalse;
    }


// ---------------------------------------------------------------------------
// Continues recognizing the drag gesture, called on drag pointer events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwDragRecognizer::SingleRecognizeL(
    const TPoint& aPointerPos )
    {
    iPreviousPosition = iCurrentPosition;
    iCurrentPosition = aPointerPos;

    if ( !iDragDetected )
        {
        // Check if points form a drag.
        iDragDetected = iDragArea.Check( aPointerPos, DragThreshold() );
        if ( iDragDetected )
            {
            SendDragEventL( EAknTouchGestureFwStart );
            }
        }
    else // iDragDetected holds
        {
        // Send update event if position changed.
        if ( iPreviousPosition != iCurrentPosition )
            {
            SendDragEventL( EAknTouchGestureFwOn );
            }
        }
    }


// ---------------------------------------------------------------------------
// Ends the drag gesture recognition.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwDragRecognizer::CompleteSingleRecognizingL()
    {
    if ( iContinuousFeedback )
        {
        StopContinuousFeedback();
        iContinuousFeedback = EFalse;
        }
    
    // Send drag stopped event only if drag was detected.
    if ( iDragDetected )
        {
        iDragDetected = EFalse;
        SendDragEventL( EAknTouchGestureFwStop );
        }
    }


// ---------------------------------------------------------------------------
// Send a drag gesture event to the observer.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwDragRecognizer::SendDragEventL(
        TAknTouchGestureFwState aGestureState )
    {
    if ( aGestureState != EAknTouchGestureFwStop )
        {
        TTouchFeedbackType feedbackType(
            FeedbackType( EAknTouchGestureFwDrag ) );       
    
        if ( feedbackType & ETouchFeedbackVibra )
            {
            StartContinuousFeedback( ETouchContinuousSmooth,
                    KAknTouchGestureFwFeedbackIntensity,
                    KAknTouchGestureFwDragFeedbackTimeout );
            iContinuousFeedback = ETrue;
            }
        }
    
    TAknTouchGestureFwDragEvent drag;
    drag.SetState( aGestureState );
    drag.SetStartPosition( iStartPosition );
    drag.SetCurrentPosition( iCurrentPosition );
    drag.SetPreviousPosition( iPreviousPosition );
    SendGestureEventL( drag );
    }


// ---------------------------------------------------------------------------
// Resets recognizer's state.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwDragRecognizer::Reset()
    {
    iStartPosition.SetXY( 0, 0 );
    iCurrentPosition.SetXY( 0, 0 );
    iPreviousPosition.SetXY( 0, 0 );
    iDragDetected = EFalse;
    iDragArea.Reset();
    iStartOnSingleTouchDrag = EFalse;
    }

// End of File
