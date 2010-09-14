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
* Description:  Touch gesture framework pointer state.
*
*/

#include "akntouchgesturefwdefs.h"
#include "akntouchgesturefwpointerstate.h"

using namespace AknTouchGestureFw;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwPointerState* CAknTouchGestureFwPointerState::NewL()
    {
    CAknTouchGestureFwPointerState* self =
        CAknTouchGestureFwPointerState::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwPointerState* CAknTouchGestureFwPointerState::NewLC()
    {
    CAknTouchGestureFwPointerState* self
        = new ( ELeave ) CAknTouchGestureFwPointerState();
    CleanupStack::PushL( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwPointerState::~CAknTouchGestureFwPointerState()
    {
    }


// ---------------------------------------------------------------------------
// Resets the pointer state.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwPointerState::Reset()
    {
    iPointerCount = 0;
    iPointerData[0].iIsPressedDown = EFalse;
    iPointerData[1].iIsPressedDown = EFalse;
    iFirstPointerNumber = KInvalidPointerNumber;
    iSecondPointerNumber = KInvalidPointerNumber;
    }


// ---------------------------------------------------------------------------
// Updates the pointer state.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwPointerState::Update(
        const TPointerEventData& aPointerData )
    {
    // Invalid events (e.g. several down events without corresponding
    // up-event) are ignored.
    iSuccessiveDownEvents = EFalse;

    TBool isValid( IsValidEvent( aPointerData.iPointerEvent.iType,
                                 aPointerData.iPointerNumber ) );
    TBool targetedToControl( aPointerData.iTargetedToControl );

    if ( isValid )
        {
        // Updates pointer-related data
        UpdatePointerOrder( aPointerData.iPointerEvent.iType,
                            aPointerData.iPointerNumber );

        TPointerData& data( iPointerData[ aPointerData.iPointerNumber ] );

        switch ( aPointerData.iPointerEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                // One pointer is already down outside gesture control.
                // No gesture recognition in such cases
                if ( targetedToControl
                        && PointersDownOutsideControlArea() )
                    {
                    targetedToControl = EFalse;
                    }
                data.iPosition = aPointerData.iPointerEvent.iPosition;
                data.iStartPosition = aPointerData.iPointerEvent.iPosition;
                data.iIsPressedDown = ETrue;
                data.iTargetedToControl = targetedToControl;
                
                iPointerCount++;                
                break;

            case TPointerEvent::EDrag:
                data.iPosition = aPointerData.iPointerEvent.iPosition;
                break;

            case TPointerEvent::EButton1Up:
                data.iIsPressedDown = EFalse;
                iPointerCount--;                
                break;
            default:
                break;
            }

        targetedToControl = data.iTargetedToControl;
        }
    else
        {
        iSuccessiveDownEvents =
            aPointerData.iPointerEvent.iType == TPointerEvent::EButton1Down;
        }

    return isValid && targetedToControl;
    }


// ---------------------------------------------------------------------------
// Returns the position of the first pointer.
// ---------------------------------------------------------------------------
//
TPoint* CAknTouchGestureFwPointerState::FirstPointerPosition()
    {
    __ASSERT_DEBUG( iFirstPointerNumber != KInvalidPointerNumber,
        User::Invariant() );
	
	// If iFirstPointerNumber is invalid, use default index instead.
    return &iPointerData[ iFirstPointerNumber == KInvalidPointerNumber ? 0 : iFirstPointerNumber ].iPosition;
    }


// ---------------------------------------------------------------------------
// Returns the position of the second pointer.
// ---------------------------------------------------------------------------
//
TPoint* CAknTouchGestureFwPointerState::SecondPointerPosition()
    {
    __ASSERT_DEBUG( iSecondPointerNumber != KInvalidPointerNumber,
        User::Invariant() );
		
	// If iSecondPointerNumber is invalid, use default index instead.
    return &iPointerData[ iSecondPointerNumber == KInvalidPointerNumber ? 1 : iSecondPointerNumber ].iPosition;
    }


// ---------------------------------------------------------------------------
// Checks whether or not two pointers are currently detected.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwPointerState::IsDoubleTouch() const
    {
    return iPointerCount == 2;
    }


// ---------------------------------------------------------------------------
// Checks whether or not only one pointer is currently detected.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwPointerState::IsSingleTouch() const
    {
    return iPointerCount == 1;
    }


// ---------------------------------------------------------------------------
// Checks whether or not there are currently any pointers detected.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwPointerState::IsNoTouch() const
    {
    return !iPointerCount;
    }


// ---------------------------------------------------------------------------
// Checks if successive down events have been received.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwPointerState::SuccessiveDownEventsReceived()
    {
    return iSuccessiveDownEvents;
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwPointerState::CAknTouchGestureFwPointerState()
    {
    Reset();
    }


// ---------------------------------------------------------------------------
// Updates the order in which the pointers were detected.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwPointerState::UpdatePointerOrder(
        TPointerEvent::TType aPointerType,
        TInt aPointerNumber )
    {
    // Updates iFirstPointerNumber and iSecondPointerNumber to hold numbers
    // (=ids) of pointers that were pressed down first and secondly.
    // Possible values are 0 or 1 (or KInvalidPointerNumber if no pointers
    // are down)

    // for double touch
    __ASSERT_ALWAYS( aPointerNumber >= 0, User::Invariant() );
    __ASSERT_ALWAYS( aPointerNumber <= 1, User::Invariant() );

    switch ( aPointerType )
        {
        case TPointerEvent::EButton1Down:
            {
            if ( iPointerCount == 0 )
                {
                iFirstPointerNumber = aPointerNumber;
                }
            else if ( iPointerCount == 1 )
                {
                iSecondPointerNumber = aPointerNumber;
                }
            break;
            }

        case TPointerEvent::EButton1Up:
            {
            if ( iPointerCount == 1 )
                {
                iFirstPointerNumber = KInvalidPointerNumber;
                }
            else if ( iPointerCount == 2 )
                {
                if ( aPointerNumber == 0 )
                    {
                    iFirstPointerNumber = 1;
                    iSecondPointerNumber = KInvalidPointerNumber;
                    }
                else if ( aPointerNumber == 1 )
                    {
                    iFirstPointerNumber = 0;
                    iSecondPointerNumber = KInvalidPointerNumber;
                    }
                }
            break;
            }

        default:
            {
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// Checks if the received event is valid or not.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwPointerState::IsValidEvent(
        TPointerEvent::TType aPointerType,
        TInt aPointerNumber )
    {
    // In practice, event is NOT valid in the following situations:
    //
    // 1. Pointer down event is received for pointer which is already down.
    // 2. Pointer up event is received for pointer which is already up.
    // 3. Pointer drag event is received for pointer which is not down.
    //
    // In these situations this function returns EFalse,
    // corresponding event is ignored and recognition continues as earlier.
    //
    TBool isValid( ETrue );
    if ( aPointerType == TPointerEvent::EButton1Down )
        {
        if ( iPointerData[ aPointerNumber ].iIsPressedDown )
            {
            isValid = EFalse;
            }
        }
    else if ( aPointerType == TPointerEvent::EButton1Up
            || aPointerType == TPointerEvent::EDrag )
        {
        if ( !iPointerData[ aPointerNumber ].iIsPressedDown )
            {
            isValid = EFalse;
            }
        }

    return isValid;
    }


// ---------------------------------------------------------------------------
// Checks if pointers are down outside the control area.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwPointerState::PointersDownOutsideControlArea() const
    {
    TBool outsideFound( EFalse );
    for ( TInt i = 0; i < KMaxPointerCount; i++ )
        {
        if ( !iPointerData[ i ].iTargetedToControl &&
             iPointerData[ i ].iIsPressedDown )
            {
            outsideFound = ETrue;
            break;
            }
        }
    return outsideFound;
    }

// End of File
