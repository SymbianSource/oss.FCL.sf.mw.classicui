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
* Description:
*
*/

#include "akntouchgesturefwdragtracer.h"

using namespace AknTouchGestureFw;


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwDragTracer* CAknTouchGestureFwDragTracer::NewL()
    {
    CAknTouchGestureFwDragTracer* self =
        CAknTouchGestureFwDragTracer::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwDragTracer* CAknTouchGestureFwDragTracer::NewLC()
    {
    CAknTouchGestureFwDragTracer* self
        = new ( ELeave ) CAknTouchGestureFwDragTracer();
    CleanupStack::PushL( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwDragTracer::~CAknTouchGestureFwDragTracer()
    {
    }


// ---------------------------------------------------------------------------
// Initializes the drag tracer state.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwDragTracer::Initialize( const TPoint& aStartPosition )
    {
    iHorizDirection = EDirectionNone;
    iVertDirection = EDirectionNone;

    iHorizCounter = 0;
    iVertCounter = 0;
    iPosition = aStartPosition;
    }



// ---------------------------------------------------------------------------
// Checks if the drag direction has been changed.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwDragTracer::IsDirectionChanged(
    const TPoint& aPosition,
    TInt aSensitivity )
    {
    if ( aPosition == iPosition )
        {
        // Can't calculate direction.
        return EFalse;
        }

    TBool directionChanged( EFalse );

    // Horizontal direction

    if ( iHorizDirection == EDirectionNone )
        {
        // Calculate first horizontal direction based on current and
        // previous point.
        if ( aPosition.iX > iPosition.iX )
            {
            iHorizDirection = EDirectionForward;
            }
        else if ( aPosition.iX < iPosition.iX )
            {
            iHorizDirection = EDirectionBackward;
            }
        }
    else
        {
        // Horizontal direction changes only if certain amount of new points
        // is to reversed direction.

        // Note: direction counter is updated with the following calls.
        if ( IsDirectionChanged(
                aPosition.iX,
                iPosition.iX,
                iHorizDirection,
                iHorizCounter,
                aSensitivity ) )
            {
            directionChanged = ETrue;
            }
        }

    // Vertical direction

    if ( iVertDirection == EDirectionNone )
        {
        // Calculate first vertical direction based on current and
        // previous point.
        if ( aPosition.iY > iPosition.iY )
            {
            iVertDirection = EDirectionForward;
            }
        else if ( aPosition.iY < iPosition.iY )
            {
            iVertDirection = EDirectionBackward;
            }
        }
    else
        {
        // Vertical direction changes only if certain amount of new points
        // is to reversed direction.

        // Note: direction counter is updated with the following call.
        if ( IsDirectionChanged(
                aPosition.iY,
                iPosition.iY,
                iVertDirection,
                iVertCounter,
                aSensitivity ) )
            {
            directionChanged = ETrue;
            }
        }

    iPosition = aPosition;
    return directionChanged;
    }


// ---------------------------------------------------------------------------
// Checks if the drag direction has been changed.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwDragTracer::IsDirectionChanged(
    TInt aCurrentCoordinate,
    TInt aPrevCoordinate,
    TDirection& aDirection,
    TInt& aCounter,
    TInt aSensitivity )
    {
    TBool directionChanged( EFalse );

    if ( aDirection == EDirectionForward )
        {
        if ( aCurrentCoordinate < aPrevCoordinate )
            {
            aCounter++;
            }
        else
            {
            aCounter = 0;
            }

        if ( aCounter == aSensitivity )
            {
            directionChanged = ETrue;
            aDirection = EDirectionBackward;
            aCounter = 0;
            }
        }
    else if ( aDirection == EDirectionBackward )
        {
        if ( aCurrentCoordinate > aPrevCoordinate )
            {
            aCounter++;
            }
        else
            {
            aCounter = 0;
            }

        if ( aCounter == aSensitivity )
            {
            directionChanged = ETrue;
            aDirection = EDirectionForward;
            aCounter = 0;
            }
        }
    return directionChanged;
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwDragTracer::CAknTouchGestureFwDragTracer():
    iHorizDirection( EDirectionNone ),
    iVertDirection( EDirectionNone ),
    iHorizCounter( 0 ),
    iVertCounter( 0 ),
    iPosition( 0, 0 )
    {
    }

// End of File
