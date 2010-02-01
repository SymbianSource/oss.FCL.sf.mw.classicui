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
* Description:  AknPhysics
*
*/

#ifndef C_AKNPHYSICS_H
#define C_AKNPHYSICS_H

#include <e32base.h>

class MAknPhysicsObserver;
class CAknPhysicsParameterProvider;
class CAknPhysicsRestrictor;
class CAknPhysicsConeObserver;
class CAknPhysicsEngine;
class CCoeControl;
class CAknHighResPeriodic;
class MTouchFeedback;


/**
 *  CAknPhysics
 *
 *  @lib aknphysics
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknPhysics ) : public CBase
    {
    
public:

    /**  CAknPhysics action definition */
    enum TAknPhysicsAction
        {
        EAknPhysicsActionNone = 1,
        EAknPhysicsActionFlicking,
        EAknPhysicsActionBouncing,
        EAknPhysicsActionDragging
        };


    /**
     * Two-phased constructor.
     * @param aObserver Observer of the physics object.
     * @param aViewControl Physics view control.
     */
    IMPORT_C static CAknPhysics* NewL( MAknPhysicsObserver& aObserver,
                                       CCoeControl* aViewControl );
    
    /**
    * Destructor.
    */
    virtual ~CAknPhysics();
    
public:

    /**
     * Physics initialization.
     *
     * @since S60 v5.0
     * @param aWorldSize Physics world size.
     * @param aViewSize Physics (visible) view size.
     * @param aLandscape ETrue if physics should work in landscape.
     */
    IMPORT_C void InitPhysicsL( const TSize& aWorldSize, 
                                const TSize& aViewSize, 
                                TBool aLandscape );

    /**
     * Starts physics simulation and applies drag event. The action is
     * done only if the drag distance is greater than the drag threshold.
     * Drag distance is adjusted by physics, if the dragging direction
     * has been changed during the dragging event.
     *
     * @param aDrag Drag distance.
     * @param aStartTime Dragging start time.
     * @return ETrue if physics was started and drag was applied.
     */
    IMPORT_C TBool StartPhysics( TPoint& aDrag, const TTime& aStartTime );

    /**
     * Stops physics simulation.
     *
     * @since S60 v5.0
     */
    IMPORT_C void StopPhysics();

    /**
     * Returns CAknPhysics action code i.e. which action CAknPhysics 
     * is currently performing.
     *
     * @since S60 v5.0
     * @return TAknPhysicsAction type action code.
     */
    IMPORT_C TInt OngoingPhysicsAction() const;
    

    /**
     * Registers view panning position. Used when view is panned
     * (dragged).
     *
     * @since S60 v5.0
     * @param aDelta Dragging distance.
     */
    IMPORT_C void RegisterPanningPosition( const TPoint& aDelta );

    /**
     * Sets friction.
     *
     * @since S60 v5.0
     * @param aFriction
     */
    IMPORT_C void SetFriction( TReal aFriction );

    /**
     * Resets friction.
     *
     * @since S60 v5.0
     */
    IMPORT_C void ResetFriction();

    /**
     * Returns highlight timeout parameter.
     *
     * @since S60 v5.0
     * @return Highlight timeout.
     */
    IMPORT_C TInt HighlightTimeout() const;

    /**
     * Returns drag threshold parameter.
     *
     * @since S60 v5.0
     * @return Drag threshold.
     */
    IMPORT_C TInt DragThreshold() const;

    /**
     * Returns feature enabled parameter.
     *
     * @since S60 v5.0
     * @return ETrue if kinetic scrolling feature is enabled.
     */
    IMPORT_C static TBool FeatureEnabled();

    /**
     * Returns EFalse if events should not be handled. This is the case if
     * flick is interrupted via key or pointer event or view is bouncing.
     *
     * @since S60 v5.0
     * @return ETrue if key and pointer events can be handled normally.
     */
    IMPORT_C TBool EventHandlingAllowed() const;

    /**
     * Updates view window control (in case e.g. view control container
     * window has changed).
     *
     * @since S60 v5.0
     * @param aControl New view control if view control itself has changed.
     */
    IMPORT_C void UpdateViewWindowControl( CCoeControl* aControl = NULL );
    
    /**
     * Suspends physics simulation, but doesn't reset current force or
     * velocity. When simulation is suspended, it is possible to change
     * view position.
     *
     * @since S60 v5.2
     */
    IMPORT_C void SuspendPhysics();
    
    /**
     * Resumes physics simulation with current view position, force
     * and velocity. 
     *
     * @since S60 v5.2
     */
    IMPORT_C void ResumePhysics();

// internal AknPhysics methods

    /**
     * Checks if view position needs updating.
     *
     * @since S60 v5.0
     * @internal
     */
    void UpdateViewPosition();

    /**
     * Returns ETrue if physics works in landscape.
     *
     * @since S60 v5.0
     * @internal
     * @return ETrue if physics works in landscape.
     */
    const TBool& Landscape();

    /**
     * Returns current view size.
     *
     * @since S60 v5.0
     * @internal
     * @return Current view size.
     */
    const TSize& ViewSize();

    /**
     * Returns current world size.
     *
     * @since S60 v5.0
     * @internal
     * @return Current world size.
     */
    const TSize& WorldSize();

    /**
     * Returns current surface erp value.
     *
     * @since S60 v5.0
     * @internal
     * @return Current surface erp value.
     */
    TInt SurfaceErp() const;

    /**
     * Returns current surface cfm value.
     *
     * @since S60 v5.0
     * @internal
     * @return Current surface cfm value.
     */
    TInt SurfaceCfm() const;

    /**
     * Returns frame delay value.
     *
     * @since S60 v5.0
     * @internal
     * @return Frame delay.
     */
    TInt FrameDelay() const;

	/**
     * Returns min frame interval value.
     *
     * @since S60 v5.0
     * @internal
     * @return Min frame interval.
     */
    TInt MinFrameInterval() const;
    
    /**
     * Draws the view in the current position.
     */
    void DrawViewInCurrentPosition();

    /**
     * Sets the iBounceTactileFeedback flag value.
     * 
     * @since S60 v5.2
     * @param aBounceTactileFeedback Whether tactile feedback is to be
     *        produced for bounce or not.
     */
    void SetBounceTactileFeedback( TBool aBounceTactileFeedback );

    /**
     * Checks if view is not drawn during panning 
     * because of high CPU usage
     *
     * @since S60 v5.2
     * @internal
     */
     TBool IsPanningDrawOmitted() const;

protected:

    /**
     * C++ constructor.
     */
    CAknPhysics( MAknPhysicsObserver& aObserver );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL( CCoeControl* aViewControl );
    
private:

    /**
     * Physics start.
     */
    void StartPhysics();

    /**
     * Apply drag.
     *
     * @param aDrag Dragging distance.
     * @param aMoveTime Dragging movetime.
     */
    void ApplyDrag( TPoint aDrag, TInt aMoveTime );

    /**
     * Timer callback.
     */
    static TInt Simulate(TAny* aSelf);

    /**
     * Physics simulation function.
     */
    void DoSimulation();

    /**
     * Cancels the physics timer and resets action state.
     */
    void CancelPhysicsTimer();

    /**
     * Updates ongoing action state according to whether physics timer is 
     * active or not and collision status.
     */
    void UpdateActionState();

    /**
     * Returns ETrue if observer view position reveals empty space i.e.
     * view is about to bounce.
     *
     * @return ETrue if observer view position reveals empty space.
     */
    TBool ViewAboutToBounce();

    /**
     * Wrapper method for notifying observer of view position change.
	 *
     * @param  aPosition  New view position.
	 * @param  aDrawNow   @c ETrue to inform the observer that it's
	 *                    view should be drawn, @c EFalse otherwise,
	 *                    in which case the observer should only update
	 *                    the logical position.
     */
    void NotifyViewPositionChanged( const TPoint& aPosition,
									TBool aDrawNow = ETrue );
    
private: // data

    /**
     * Simulation timer.
     */
    CAknHighResPeriodic* iPhysics; // Own
    
    /**
     * Physics observer.
     */
    MAknPhysicsObserver& iObserver;
    
    /**
     * Current world size.
     */
    TSize iWorldSize;

    /**
     * Current view size.
     */
    TSize iViewSize;
    
    /**
     * ETrue if physics works in landscape.
     */
    TBool iLandscape;
    
    /**
     * Ongoing action.
     */
    TAknPhysicsAction iOngoingAction;
    
    /**
     * Counter to keep track of same successive view positions.
     */
    TInt iSamePositionCounter;

    /**
     * Physics parameter provider.
     * Own.
     */
    CAknPhysicsParameterProvider* iParamProvider;

    /**
     * Physics restrictor.
     * Own.
     */
    CAknPhysicsRestrictor* iRestrictor;

    /**
     * CONE observer.
     * Own.
     */
    CAknPhysicsConeObserver* iConeObserver;
    
    /**
     * Physics engine.
     * Own.
     */
    CAknPhysicsEngine* iEngine;

    /**
     * ETrue if maximum flick time exceeded.
     */
    TBool iFlickTimeExceeded;
    
    /**
     * Handle to the null thread, used for performance monitoring.
     */
    RThread iNullThread;
    
    /**
     * CPU time used by the null thread after the last view draw.
     */
    TInt64 iNullThreadTime;

    /**
     * Time of the last view draw.
     */
    TTime iTimeOfLastDraw;

    /**
     * Pointer to touch feedback instance
     * Not own.
     */
    MTouchFeedback* iFeedback;

    /**
     * Flag that indicates whether or not to give tactile feedback when
     * bouncing.
     */
    TBool iBounceTactileFeedback;

    /**
     * ETrue if a panning frame is not drawn on screen because of
     * high CPU usage.
     */
    TBool iPanningDrawOmitted;

    /**
     * ETrue if physics simulation is suspended. 
     */
    TBool iSuspended;
    };

#endif // C_AKNPHYSICS_H
