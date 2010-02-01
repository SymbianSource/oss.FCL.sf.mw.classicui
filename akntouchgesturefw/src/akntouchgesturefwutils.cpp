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
* Description:  Touch gesture framework utility functions.
*
*/

#include <akntouchgesturefwevents.h>

#include "akntouchgesturefwutils.h"
#include "akntouchgesturefwdefs.h"

using namespace AknTouchGestureFw;

_LIT(KAknTouchPointerEventDown, "[GFW] IN P%d DOWN (%d, %d) %S");
_LIT(KAknTouchPointerEventDrag, "[GFW] IN P%d DRAG (%d, %d) %S");
_LIT(KAknTouchPointerEventUp, "[GFW] IN P%d UP (%d, %d) %S");
_LIT(KAknTouchPointerEventHw, "HW");
_LIT(KAknTouchPointerEventSimulated, "SM");
_LIT(KAknTouchGestureGeneric, "[GFW] OUT S:%d G:%x T:%x %%:%d");
_LIT(KAknTouchGesturePointer,
        "[GFW] ... %d: SP:(%d,%d) CP:(%d,%d) PP:(%d,%d) S:(%d,%d)");

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// TPointerEventData::TPointerEventData
// ---------------------------------------------------------------------------
//
AknTouchGestureFw::TPointerEventData::TPointerEventData(
        TPointerEvent& aPointerEvent,
        TInt aPointerNumber,
        const TTime& aTimeStamp,
        TBool aSimulated,
        TBool aTargetedToControl )
    : iPointerEvent( aPointerEvent ),
      iPointerNumber( aPointerNumber ),
      iTimeStamp( aTimeStamp ),
      iSimulated( aSimulated ),
      iTargetedToControl( aTargetedToControl )
    {
    }


// ---------------------------------------------------------------------------
// TPointEntry::TPointEntry
// ---------------------------------------------------------------------------
//
TPointEntry::TPointEntry( const TPoint& aPos, const TTime& aTime )
    :  iPos( aPos ), iTime( aTime )
    {
    }


// ---------------------------------------------------------------------------
// TPointEntry::TPointEntry
// ---------------------------------------------------------------------------
//
TPointEntry::TPointEntry()
    : iPos( TPoint() ), iTime( TTime() )
    {
    }


// ---------------------------------------------------------------------------
// TVector::TVector
// ---------------------------------------------------------------------------
//
TVector::TVector( const TPoint& aFrom, const TPoint& aTo )
    : iX( aTo.iX - aFrom.iX ),
    iY( aTo.iY - aFrom.iY )
    {
    }


// ---------------------------------------------------------------------------
// TVector::TVector
// ---------------------------------------------------------------------------
//
TVector::TVector( TReal aDeltaX, TReal aDeltaY )
    : iX( aDeltaX ), iY( aDeltaY )
    {
    }


// ---------------------------------------------------------------------------
// TVector::TVector
// ---------------------------------------------------------------------------
//
TVector::TVector()
    : iX( 0 ), iY( 0 )
    {
    }


// ---------------------------------------------------------------------------
// TVector::Angle
// ---------------------------------------------------------------------------
//
TInt TVector::Angle() const
    {
    TReal angle = 0;
    TReal length = Length();
    if ( Abs( length ) > KEpsilon )
        {
        Math::ACos( angle, iX / length );
        if ( iY < 0 )
            {
            angle = 2 * KPi - angle;
            }
        }

    return Degrees( angle );
    }


// ---------------------------------------------------------------------------
// TVector::Length
// ---------------------------------------------------------------------------
//
TReal TVector::Length() const
    {
    TReal length = 0;
    Math::Sqrt( length, iX * iX + iY * iY );
    return length;
    }


// ---------------------------------------------------------------------------
// static TVector::Degrees
// ---------------------------------------------------------------------------
//
TInt TVector::Degrees( TReal aRadians )
    {
    return aRadians * 180 / KPi;
    }


// ---------------------------------------------------------------------------
// TThresholdArea::TThresholdArea
// ---------------------------------------------------------------------------
//
TThresholdArea::TThresholdArea()
    : iInitialPosition(), iActive( EFalse )
    {
    Reset();
    }


// ---------------------------------------------------------------------------
// TThresholdArea::Reset
// ---------------------------------------------------------------------------
//
void TThresholdArea::Reset()
    {
    iInitialPosition = TPoint();
    iActive = EFalse;
    }


// ---------------------------------------------------------------------------
// TThresholdArea::IsActive
// ---------------------------------------------------------------------------
//
TBool TThresholdArea::IsActive() const
    {
    return iActive;
    }


// ---------------------------------------------------------------------------
// TThresholdArea::InitialPosition
// ---------------------------------------------------------------------------
//
TPoint TThresholdArea::InitialPosition() const
    {
    TPoint position;
    if ( iActive )
        {
        position = iInitialPosition;
        }
    return position;
    }


// ---------------------------------------------------------------------------
// TThresholdArea::Start
// ---------------------------------------------------------------------------
//
void TThresholdArea::Start( const TPoint& aInitialPosition )
    {
    iInitialPosition = aInitialPosition;
    iActive = ETrue;
    }


// ---------------------------------------------------------------------------
// TThresholdArea::Check
// ---------------------------------------------------------------------------
//
TBool TThresholdArea::Check( const TPoint& aNewPosition, TInt aMargin ) const
    {
    TBool crossed = EFalse;
    if ( iActive )
        {
        TInt deltaX = aNewPosition.iX - iInitialPosition.iX;
        TInt deltaY = aNewPosition.iY - iInitialPosition.iY;
        deltaX = Abs( deltaX );
        deltaY = Abs( deltaY );
        crossed = deltaX > aMargin || deltaY > aMargin;
        }
    return crossed;
    }


// ---------------------------------------------------------------------------
// Dumps pointer event data to the debug output.
// ---------------------------------------------------------------------------
//
void AknTouchGestureFwUtils::DumpPointerEvent( const TPointerEvent& aEvent,
                                               TBool aSimulated )
    {
    TInt pointerNumber = 0;

    if ( aEvent.IsAdvancedPointerEvent() )
        {
        pointerNumber = aEvent.AdvancedPointerEvent()->PointerNumber();
        }

    const TDesC* source;
    if ( aSimulated )
        {
        source = &KAknTouchPointerEventSimulated;
        }
    else
        {
        source = &KAknTouchPointerEventHw;
        }

    switch ( aEvent.iType )
        {
    case TPointerEvent::EButton1Down:
        RDebug::Print(KAknTouchPointerEventDown, pointerNumber,
                aEvent.iPosition.iX, aEvent.iPosition.iY, source);
        break;

    case TPointerEvent::EDrag:
        RDebug::Print(KAknTouchPointerEventDrag, pointerNumber,
                aEvent.iPosition.iX, aEvent.iPosition.iY, source);
        break;

    case TPointerEvent::EButton1Up:
        RDebug::Print(KAknTouchPointerEventUp, pointerNumber,
                aEvent.iPosition.iX, aEvent.iPosition.iY, source);
        break;

    default:
        break;
        }
    }


// ---------------------------------------------------------------------------
// Dumps gesture event data to the debug output.
// ---------------------------------------------------------------------------
//
void AknTouchGestureFwUtils::DumpGestureEvent(
    MAknTouchGestureFwEvent& aEvent )
    {
    TInt movement( 0 );
    TPoint startPos;
    TPoint currentPos;
    TPoint previousPos;
    TPoint speed;
    TAknTouchGestureFwState state( EAknTouchGestureFwOn );

    switch ( aEvent.Group() )
        {
    case EAknTouchGestureFwGroupTap:
        {
        MAknTouchGestureFwTapEvent* tap =
            static_cast<MAknTouchGestureFwTapEvent*>( &aEvent );
        startPos = tap->Position();
        }
        break;
            
    case EAknTouchGestureFwGroupFlick:
        {
        MAknTouchGestureFwFlickEvent* flick =
            static_cast<MAknTouchGestureFwFlickEvent*>( &aEvent );
        startPos = flick->Position();
        speed = flick->Speed();
        }
        break;
            
    case EAknTouchGestureFwGroupDrag:
        {
        MAknTouchGestureFwDragEvent* drag =
            static_cast<MAknTouchGestureFwDragEvent*>( &aEvent );
        startPos = drag->StartPosition();
        currentPos = drag->CurrentPosition();
        previousPos = drag->PreviousPosition();
        state = drag->State();
        }
        break;
            
    case EAknTouchGestureFwGroupPinch:
        {
        MAknTouchGestureFwPinchEvent* pinch =
            static_cast<MAknTouchGestureFwPinchEvent*>( &aEvent );
        movement = pinch->Movement();
        state = pinch->State();
        }
        break;

    default:
        break;
        }

    RDebug::Print( KAknTouchGestureGeneric,
            state, aEvent.Group(),
            aEvent.Type(), movement );
    RDebug::Print(KAknTouchGesturePointer, 0,
            startPos.iX, startPos.iY, currentPos.iX, currentPos.iY,
            previousPos.iX, previousPos.iY, speed.iX, speed.iY );
    }


// ---------------------------------------------------------------------------
// TDirectionTracer::TDirectionTracer
// ---------------------------------------------------------------------------
//
TDirectionTracer::TDirectionTracer()
    : iDirection( EDirectionNeutral ), iDirectionChanged( EFalse ), 
      iChangeDirection( EDirectionNeutral ), iChangeCounter( 0 )
    {    
    }

// ---------------------------------------------------------------------------
// TDirectionTracer::Reset
// ---------------------------------------------------------------------------
//
void TDirectionTracer::Reset()
    {
    iDirection = EDirectionNeutral;
    iDirectionChanged = EFalse;
    iChangeDirection = EDirectionNeutral;
    iChangeCounter = 0;
    }

// ---------------------------------------------------------------------------
// TDirectionTracer::Update
// ---------------------------------------------------------------------------
//
void TDirectionTracer::Update( TInt aDelta, TInt aSensitivity )
    {
    iDirectionChanged = EFalse;

    if ( !aDelta )
        {
        return; // no change, cannot determine direction
        }
    
    if ( iDirection == EDirectionNeutral )
        {
        TDirection direction = EDirectionNeutral;
        if ( aDelta > 0 )
            {
            direction = EDirectionPositive;
            }
        else
            {
            direction = EDirectionNegative;
            }
        
        if ( direction == iChangeDirection )
            {
            iChangeCounter++;
            
            if ( iChangeCounter >= aSensitivity )
                {
                iDirection = iChangeDirection;
                iDirectionChanged = ETrue;
                iChangeCounter = 0;
                }
            }
        else
            {
            iChangeDirection = direction;
            iChangeCounter = 0;
            iChangeCounter++;
            }
        }
    else if ( iDirection == EDirectionPositive )
        {
        // Subsequent direction changes require a couple of movement
        // to same direction
        
        if ( CheckDirectionChange( -aDelta, aSensitivity, iChangeCounter ) )
            {
            iDirection = EDirectionNegative;
            iDirectionChanged = ETrue;                            
            }
        }
    else // iDirection == EDirectionNegative
        {
        // Subsequent direction changes require a couple of movement
        // to same direction

        if ( CheckDirectionChange( aDelta, aSensitivity, iChangeCounter ) )
            {
            iDirection = EDirectionPositive;
            iDirectionChanged = ETrue;
            }
        }
    }


// ---------------------------------------------------------------------------
// TDirectionTracer::IsDirectionChanged
// ---------------------------------------------------------------------------
//
TBool TDirectionTracer::IsDirectionChanged() const
    {
    return iDirectionChanged;
    }


// ---------------------------------------------------------------------------
// TDirectionTracer::Direction
// ---------------------------------------------------------------------------
//
TDirectionTracer::TDirection TDirectionTracer::Direction() const
    {
    return iDirection;
    }


// ---------------------------------------------------------------------------
// TDirectionTracer::CheckDirectionChange
// ---------------------------------------------------------------------------
//
TBool TDirectionTracer::CheckDirectionChange(
        TInt aDelta, TInt aSensitivity, TInt& aCounter)
    {
    TBool directionChanged = EFalse;
    
    if ( aDelta > 0 )
        {
        aCounter++;
        }
    else
        {
        aCounter = 0;
        }
    
    if ( aCounter >= aSensitivity )
        {
        aCounter = 0;
        directionChanged = ETrue;
        }
    
    return directionChanged;
    }

// End of File
