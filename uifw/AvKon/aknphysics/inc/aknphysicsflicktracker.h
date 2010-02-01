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
* Description:  AknPhysics flick tracker
*
*/

#ifndef C_AKNPHYSICSFLICKTRACKER_H
#define C_AKNPHYSICSFLICKTRACKER_H


#include <e32base.h>

class CAknPhysicsParameterProvider;

/**
 *  Tracker data class
 *
 */
NONSHARABLE_CLASS( TAknPhysicsTrackerData )
    {

public:
    
    /**
     * Flick tracker data coordinate attribute.
     */
    TInt iCoordinate;

    /**
     * Flick tracker data time attribute.
     */
    TTime iTime;

    };

/**
 *  AknPhysics flick tracker
 *
 */
NONSHARABLE_CLASS( CAknPhysicsFlickTracker ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsFlickTracker* NewL(
            CAknPhysicsParameterProvider* aProvider );

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsFlickTracker* NewLC(
            CAknPhysicsParameterProvider* aProvider );

    /**
     * Destructor.
     */
    virtual ~CAknPhysicsFlickTracker();
    
    /**
     * Initializes tracker.
     * 
     * @param aCoordinate Start coordinate.
     */
    void InitTracker( const TInt& aCoordinate );

    /**
     * Checks if dragging parameters has changed
     * with new coordinate.
     * 
     * @param aCoordinate New coordinate.
     */
    void DragChanged( const TInt& aCoordinate );

    /**
     * Returns flick start coordinate.
     * 
     * @return Flick start coordinate.
     */
    TInt FlickStartCoordinate() const;

    /**
     * Returns flick move time.
     * 
     * @return Flick move time.
     */
    TInt FlickMoveTime() const;

private:

    /**
     * C++ constructor.
     */
    CAknPhysicsFlickTracker( CAknPhysicsParameterProvider* aProvider );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Checks if dragging speed has changed.
     * 
     * @param aCoordinate New drag coordinate.
     */
    void SpeedChanged( const TInt& aCoordinate );

    /**
     * Returns the drag threshold.
     *
     * @return Drag threshold.
     */
    TInt Threshold();

    /**
     * Calculates current dragging speed from new drag coordinate.
     *
     * @return Dragging speed.
     */
    TInt DragSpeed( const TInt& aNewCoordinate );

    /**
     * Inits tracker data item.
     *
     * @param aData Tracker data item.
     * @param aCoordinate Initial coordinate.
     */
    void InitFlickData( TAknPhysicsTrackerData& aData, 
                        const TInt& aCoordinate );

    /**
     * Returns "normal" flick move time.
     * 
     * @return Flick move time.
     */
    TInt NormalFlickMoveTime() const;

private: // data

    /**
     * Direction enum.
     */
    enum TDirection
        {
        EDirectionNone = 1,
        EDirectionForward,
        EDirectionBackward
        };

    /**
     * Current direction
     */
    TDirection iDirection;

    /**
     * Current coordinate.
     */
    TInt iCoordinate;

    /**
     * Current direction change data.
     */
    TAknPhysicsTrackerData iDirectionData;
    
    /**
     * "Normal" flick start data (not affected by speed-ups).
     */
    TAknPhysicsTrackerData iNormalStartData;
    
    /**
     * Current speed up data.
     */
    TAknPhysicsTrackerData iSpeedUpData;
    
    /**
     * Speed-up start data.
     */
    TAknPhysicsTrackerData iSpeedUpStartData;
    
    /**
     * ETrue if last direction change is registered.
     */
    TBool iChangeRegistered;
    
    /**
     * ETrue if last speed up is registered.
     */
    TBool iSpeedUpRegistered;

    /**
     * Last drag time.
     */
    TTime iLastDragTime;
    
    /**
     * Last drag speed.
     */
    TInt iLastDragSpeed;

    /**
     * Count of ignored events since last speed-up.
     */
    TInt iIgnoredEvents;

    /**
     * Physics parameter provider.
     * Not own.
     */
    CAknPhysicsParameterProvider* iProvider;

    };

#endif // C_AKNPHYSICSFLICKTRACKER_H
