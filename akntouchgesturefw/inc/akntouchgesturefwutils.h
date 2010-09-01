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

#ifndef AKNTOUCHGESTUREFWUTILS_H
#define AKNTOUCHGESTUREFWUTILS_H

#include <e32math.h>
#include <w32std.h>

namespace AknTouchGestureFw {

class MAknTouchGestureFwEvent;

/** 
 * Data structure to hold pointer event related data.
 */
NONSHARABLE_CLASS( TPointerEventData )
    {

public:

    /**
     * Constructor.
     * 
     * @param  aPointerEvent       Pointer event from window server.
     * @param  aPointerNumber      Pointer number of the event.
     * @param  aTimeStamp          Time stamp of the event.
     * @param  aSimulated          @c ETrue if event is simulated.
     * @param  aTargetedToControl  @c ETrue if event is targeted to control.
     */
    TPointerEventData( TPointerEvent& aPointerEvent,
                       TInt aPointerNumber,
                       const TTime& aTimeStamp,
                       TBool aSimulated,
                       TBool aTargetedToControl );

    /**
     * Pointer event.
     */
    TPointerEvent& iPointerEvent;

    /**
     * Pointer number.
     */    
    TInt iPointerNumber;

    /**
     * Pointer time stamp.
     */    
    TTime iTimeStamp;

    /**
     * Indicates wheter event is simulated.
     */
    TBool iSimulated;

    /**
     * Indicates wheter event is targeted to control.
     */
    TBool iTargetedToControl;
    };


/**
 *  Represents a single point given at certain time.
 *
 */
NONSHARABLE_CLASS( TPointEntry )
    {

public:

    /**
     * C++ constructor.
     * 
     * @param  aPos   Position of the point.
     * @param  aTime  Time of the point.
     */
    TPointEntry( const TPoint& aPos, const TTime& aTime );

    /**
     * Default C++ constructor.
     */
    TPointEntry();

    /**
     * Position.
     */
    TPoint iPos;

    /**
     * Time.
     */
    TTime iTime;

    };


/**
 * Vector class (math)
 */
NONSHARABLE_CLASS( TVector )
    {

public:

    /**
     * C++ constructor.
     *
     * @param  aFrom  Starting point of the vector.
     * @param  aTo    Ending point of the vector.
     */
    TVector( const TPoint& aFrom, const TPoint& aTo );

    /**
     * C++ constructor.
     *	 
     * @param aDeltaX X part of vector.
     * @param aDeltaY Y part of vector.
     */
    TVector( TReal aDeltaX, TReal aDeltaY );

    /**
     * Default C++ constructor.
     */
    TVector();

    /**
     * Angle of the vector
     *
     * @return Angle of the vector.
     */
    TInt Angle() const;

    /**
     * Length of the vector
     *
     * @return Length of the vector.
     */
    TReal Length() const;

private:

    /**
     * Radians in degrees.
     *
     * @return Radians in degrees.
     */
    static TInt Degrees( TReal aRadians );

public:

    /**
     * X coordinate that represent the vector.
     */
    TReal iX;

    /**
     * Y coordinate that represent the vector.
     */
    TReal iY;

    };


/**
 * Threshold area.
 */
NONSHARABLE_CLASS( TThresholdArea )
    {

public:

    /**
     * Constructor.
     */
    TThresholdArea();

    /**
     * Resets the threshold area.
     * After calling this method, this area becomes inactive.
     */
    void Reset();

    /**
     * Returns @c ETrue if threshold area is active.
     *
     * @return @c ETrue if active, @c EFalse otherwise.
     */
    TBool IsActive() const;

    /**
     * Returns the initial position.
     *
     * @return Initial position.
     */
    TPoint InitialPosition() const;

    /**
     * Starts threshold checking.
     *
     * @param  aInitialPosition  Initial position against which other
     *                           points are checked.
     */
    void Start( const TPoint& aInitialPosition );

    /**
     * Checks if @c aNewPosition is inside threshold area.
     *
     * @param  aNewPosition  New position.
     * @param  aMargin       Threshold margin.
     *
     * @return True if threshold is crossed, false otherwise.
     */
    TBool Check( const TPoint& aNewPosition, TInt aMargin ) const;

    // C++ default copy constructor & assignment operator
    // are sufficient.

private:

    /**
     * Initial position.
     */
    TPoint iInitialPosition;

    /**
     * Boolean flag to indicate whether this area is active.
     */
    TBool iActive;

    };


/**
 * Touch gesture framework utility class.
 *
 */
NONSHARABLE_CLASS( AknTouchGestureFwUtils )
    {

public:

    /**
     * Dumps pointer event (principal input to this component).
     *
     * @param  aEvent      Event to output.
     * @param  aSimulated  @c ETrue if simulated, @c EFalse if from HW.
     */
    static void DumpPointerEvent( const TPointerEvent& aEvent,
                                  TBool aSimulated );

    /**
     * Dumps gesture event (principal output from this component).
     *
     * @param  aEvent  Gesture event.
     */
    static void DumpGestureEvent( MAknTouchGestureFwEvent& aEvent );

    };


/**
 * Direction tracer for gestures.
 */
class TDirectionTracer
    {
public:
    /**
     * Enumerates directions.
     */
    enum TDirection
        {
        EDirectionNeutral = 0,
        EDirectionPositive = 1,
        EDirectionNegative = -1
        };

public:    
        
    /**
     * Constructor.
     */
    TDirectionTracer();
    
    /**
     * Resets back to initial constructed state.
     */
    void Reset();
    
    /**
     * Updates tracer with new value.
     * @param aDelta change.
     * @param aSensitivity sensitivity to direction changes.
     */
    void Update( TInt aDelta, TInt aSensitivity );
        
    /**
     * Checks if direction has changed.
     * @return true if changed.
     */
    TBool IsDirectionChanged() const;
    
    /**
     * Returns current direction.
     * @return direction.
     */
    TDirection Direction() const;
    
    // Default copy constructor & assignment operator are 
    // sufficient.

private:
    
    /**
     * Checks direction change. Helper method for Update.
     * 
     * @param aDelta change in value.
     * @param aSensitivity sensitivity.
     * @param aCounter change counter.
     */
    static TBool CheckDirectionChange(
        TInt aDelta, TInt aSensitivity, TInt& aCounter );
    
private:
    
    /**
     * Current direction.
     */
    TDirection iDirection;
    
    /**
     * ETrue if direction changed.
     */
    TBool iDirectionChanged;

    /**
     * Change direction. 
     */
    TDirection iChangeDirection;

    /**
     * Change counter.
     */
    TInt iChangeCounter;
    
    };

} // namespace AknTouchGestureFw

#endif // AKNTOUCHGESTUREFWUTILS_H
