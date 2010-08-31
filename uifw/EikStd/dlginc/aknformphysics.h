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
* Description:    Class to store physics related data in forms.
*
*/




#ifndef C_CAKNFORMPHYSICS_H
#define C_CAKNFORMPHYSICS_H


#include <e32base.h>
#include <aknphysicsobserveriface.h>


class CAknPhysics;
class CEikDialogPage;
class CAknRecordingGc;

/**
 *  ?one_line_short_description
 *  ?more_complete_description
 *
 *  @code
 *   ?good_class_usage_example(s)
 *  @endcode
 *
 *  @lib ?library
 *  @since S60 ?S60_version *** for example, S60 v3.0
 */
NONSHARABLE_CLASS( CAknFormPhysics ) : public CBase, public MAknPhysicsObserver
    {
public:

    /**
    * Two-phased constructor.
    */
    static CAknFormPhysics* NewL( CEikDialogPage& aParent, CAknRecordingGc& aRecordingGc );

    /**
    * Destructor.
    */
    virtual ~CAknFormPhysics();
    
    /**
    * Initializes physics engine.
    *
    * @since S60 v5.0
    * @param aWorldSize Collected size of all form items.
    * @param aViewSize View's size i.e. size of form's rect.
    * @param aViewCenter View center's initial position.
    */
    void InitPhysicsL( const TSize& aWorldSize, const TSize& aViewSize, const TPoint& aViewCenter );
    
    /**
    * Stops the physics engine.
    *
    * @since S60 v5.0
    */
    void Stop();

    /**
    * Starts the physics engine.
    *
    * @since S60 v5.0
    * @param aLength Length of the flick on display (in pixels).
    * @param aStartTime Flick's start time.
    * @return ETrue if flicking was started.
    */
    TBool StartFlick( const TPoint& aLength, const TTime& aStartTime );
    
    /**
    * Returns highlight timeout. Tapped item should be activated only after a small delay.
    *
    * @since S60 v5.0
    * @return Highlight delay.
    */
    TInt HighlightDelay() const;
    
    
    /**
    * Return drag event's treshold.
    *
    * @since S60 v5.0
    * @return Drag treshold in pixels.
    */
    TInt DragThreshold() const;
    

    /**
    * Returns current view size.
    *
    * @since S60 v5.0
    * @return View size.
    */
    TSize ViewSize() const;

    /**
    * Registers panning position to physics.
    *
    * @since S60 v5.0
    * @aPosition Position delta.
    */
    void SetPanningPosition( const TPoint& aDelta );
    
public: // From base class MAknPhysicsObserver.

    /**
     * Called when view position changes.
     *
     * @param  aNewPosition  The new position of the view.
     * @param  aDrawNow      @c ETrue if the screen is to be redrawn,
     *                       otherwise @c EFalse.
     * @param  aFlags        Additional flags, not used currently.
     */
    virtual void ViewPositionChanged( const TPoint& aNewPosition,
                                      TBool aDrawNow = ETrue,
                                      TUint aFlags = 0 );
    
    /**
     * Physics emulation has stopped moving the view.
     *
     * @since S60 v5.0
     */
    virtual void PhysicEmulationEnded();        

    /**
     * Returns the observer's view position.
     *
     * @since S60 v5.0
     *
     * @return Physics observer's view position.
     */
    virtual TPoint ViewPosition() const;

public: // New methods
    
    /**
     * Checks whether the physics engine can be stopped.
     *
     * @since S60 v5.0
     * @return ETrue if the physics engine can be stopped.
     */
    TBool CanBeStopped() const;
        
    /**
     * Returns CAknPhysics action code i.e. which action CAknPhysics 
     * is currently performing.
     *
     * @since S60 v5.2
     * @return TAknPhysicsAction type action code.
     */
    TInt OngoingPhysicsAction() const;
        
    /**
     * Returns view's top y coordinate.
     * 
     * @since S60 v5.0
     * @return View's top y coordinate in pixels, relative to 0. 
     */
    TInt ViewTopY() const;
    
    /**
     * Returns distance from view's top to its center. In other words,
     * ViewPosition() == ViewTopY() + ViewDistance().
     * 
     * @since S60 v5.0
     * @return Distance from view's top y to its center.
     */
    TInt ViewCenterDistance() const;
    
    /**
     * Sets view center position.
     * 
     * @since S60 v5.0
     */
    void SetViewCenter( const TPoint& aPosition );
    
    /**
     * Return view center position.
     * 
     * @since S60 v5.0
     * @return View center.
     */
    TPoint ViewCenter() const;
    
private:

    /**
    * Constructor.
    */
    CAknFormPhysics( CEikDialogPage& aParent, CAknRecordingGc& aRecordingGc );
    
    /**
    * Second stage constructor.
    */
    void ConstructL();

    /**
    * Checks whether panning and flicking are allowed with current world and
    * view sizes.
    *
    * @since S60 v5.0
    * @return ETrue if allowed.
    */
    TBool PhysicsAllowed() const;

private: // data
    /**
    * Center of the "view" (the visible window to the whole form i.e. form's
    * virtual rect).
    */
    TPoint iViewCenter;

    /**
     * Interface to the physics engine.
     * Own.
     */
    CAknPhysics* iPhysics;
    
    /**
    * Dialog page whose scrolling is controlled by this class.
    */
    CEikDialogPage& iParent;

    /**
    * Graphics context used to cache drawing commands.
    */
    CAknRecordingGc& iRecordingGc;
    
    /**
    * Size of the "world".
    */
    TSize iWorldSize;
    
    /**
    * View size.
    */
    TSize iViewSize;
    
    /**
    * Benchmark timestamp.
    */
    TTime iStartTime;
    
    /**
    * Benchmark frame counter.
    */
    TInt iFrameCount;
    };

#endif // C_CAKNFORMPHYSICS_H
