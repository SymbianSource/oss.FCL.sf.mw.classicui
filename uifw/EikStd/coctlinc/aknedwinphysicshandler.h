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
* Description:  EikEdwin physics handler
*
*/

#ifndef C_AKNEDWINPHYSICSHANDLER_H
#define C_AKNEDWINPHYSICSHANDLER_H


#include <e32base.h>
#include <aknphysicsobserveriface.h>

class CAknPhysics;
class CEikEdwin;

/**
 *  EikEdwin physics handler.
 *
 *  @lib eikcoctl
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknEdwinPhysicsHandler ) : public CBase,
                                               public MAknPhysicsObserver
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknEdwinPhysicsHandler* NewL( CEikEdwin& aEdwin );

    /**
     * Two-phased constructor.
     */
    static CAknEdwinPhysicsHandler* NewLC( CEikEdwin& aEdwin );
    /**
     * Destructor.
     */
    virtual ~CAknEdwinPhysicsHandler();
    
public:
    
    /**
     * Sets view rect.
     *
     * @param aRect New view rect.
     */
    void SetViewRect( const TRect& aRect );
    
    /**
     * Initializes physics.
     */
    void InitPhysicsL();
  
    /**
     * Moves the scroll index.
     *
     * @param aPixelsToMove Number of pixels to move.
     */
    void MoveScrollIndex( TInt aPixelsToMove );
    
    /**
     * Returns ETrue if flicking or bouncing is ongoing.
     *
     * @return ETrue if flicking or bouncing is ongoing.
     */
    TBool EmulationOngoing();
    
    /**
     * Returns drag threshold.
     *
     * @return drag threshold.
     */
    TInt DragThreshold() const;
    
    /**
     * Initialises scrolling.
     *
     * @param aStartPosition Start position of dragging.
     */
    void InitKineticScrolling( const TPoint& aStartPosition );
    
    /**
     * Handles kinetic scrolling.
     *
     * @param aPointerEvent Pointer event to handle.
     * @param aShouldReturn Set to ETrue if we should return from
     *                      CEikEdwin's HandlePointerEventL after
     *                      call to this function. 
     */
    void HandleKineticScrolling( const TPointerEvent& aPointerEvent,
        TBool& aShouldReturn );
    
    /**
     * Returns ETrue if selection is started.
     *
     * @return ETrue if selection is started.
     */
    TBool SelectionStarted() const;
    
    /**
     * Returns ETrue if dragging is started.
     *
     * @return ETrue if dragging is started.
     */
    TBool DraggingStarted() const;
    
    /**
     * Returns ETrue if drag threshold is exceeded.
     *
     * @param aCurrentPosition Current position of dragging.
     * @return ETrue if drag threshold is exceeded.
     */
    TBool DragThresholdExceeded( const TPoint& aCurrentPosition ) const;
    
    
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
     * Called when emulation has ended.
     */
    virtual void PhysicEmulationEnded();

    /**
     * Returns the observer's view position.
     *
     * @return Physics observer's view position.
     */
    virtual TPoint ViewPosition() const;
    
private:

    /**
     * C++ constructor.
     */
    CAknEdwinPhysicsHandler( CEikEdwin& aEdwin );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Scrolls view to correct position.
     * 
     * @param  aAllowBounce If ETrue, it is possible to scroll
     *                      content out of borders.
     */
    void ScrollView( TBool aAllowBounce );
    
	/**
     * Used to scroll view normally (without bounce).
     * Called from ScrollView.
     *
     * @param  aPixelsToScroll Number of pixels to scroll
     * @param  aAllowBounce    If this parameter is EFalse and end or
     *                         beginning of content is exceeded, this
     *                         function doesn't scroll over the border.
     *                         If this parameter is ETrue, it is possible
     *                         to scroll out of borders.  
     */
    void ScrollStep( TInt aPixelsToScroll, TBool aAllowBounce );
	
	/**
     * Used to scroll view with bounce (there can be empty
     * space above or below the content). 
     * Called from ScrollView.
     *
     * @param  aPixelsToScroll Number of pixels to scroll
     * @param  aRestOfPixels   Number of pixels not scrolled	 
     */
    void ScrollStepWithBounce( TInt aPixelsToScroll, TInt& aRestOfPixels );
    
	/**
     * Moves world index.
     * 
     * @param  aDelta Number of pixels to move.
     */
    void MoveWorldIndex( TInt aDelta );
	
	/**
     * Scrolls rest of pixels. This function is used
     * to scroll rest of pixels when end or beginning
     * of content has exceeded and bounce starts. 
     *
     * @param  aRestOfPixels Number of pixels to scroll. 
     */
    void ScrollRestOfPixels( TInt aRestOfPixels ); 
	
    /**
     * Stops physics.
     */
    void StopPhysics();
	
	/**
     * Blocks/unblocks pointer events.
     *
     * @param  aBlocked Tells if events should be blocked or not. 
     */
    void BlockEvents( TBool aBlocked );
    
    /**
     * Returns ETrue if flicking is ongoing. 
     */
    TBool IsFlicking() const;
    
    /**
     * Returns ETrue if bouncing is ongoing. 
     */
    TBool IsBouncing() const;

    /**
     * Initialises bounce.
     *
     * @param  aBounceDown ETrue if bouncing down. 
     */
    void InitBounce( TBool aBounceDown );
    
    /**
      * Handles the pointer event received by edwin.
      *
      * @param aPointerEvent Pointer event to handle.
      */
     void HandlePointerEvent( const TPointerEvent& aPointerEvent );


private: // data

    /**
     * Physics handler flags
     */
    enum TAknEdwinPhysicsHandlerFlags
        {
        EFlagUpdatingView, // View updating ongoing
        EFlagBouncingUp,   // Content bouncing up, empty space below content   
        EFlagBouncingDown,  // Content bouncing down, empty space above content
        EFlagDraggingAllowed // Dragging allowed
        };
    
    /**
     * Scroll index.
     */
    TInt iWorldIndex;
    
    /**
     * Previous scroll index.
     */
    TInt iPreviousWorldIndex;

    /**
     * Previous pointer position.
     */   
    TPoint iPrevPosition;
    
    /**
     * View rect.
     */
    TRect iViewRect;
    
    /**
     * ETrue if pointer events are blocked.
     */
    TBool iEventsBlocked;

    /**
     * If set to ETrue, first pointer down event unblocks pointer events.
     */
    TBool iEventUnblockingAllowed;
    
    /**
     * ETrue if drag threshold exceeded.
     */
    TBool iDragThresholdExceeded;
    
    /**
     * Pointer down start time.
     */
    TTime iStartTime;
    
    /**
     * Physics. 
     * Own.
     */
    CAknPhysics *iPhysics;

    /**
     * Physics handler flags.
     */
    TBitFlags iFlags;
    
    /**
     * Pointer to edwin.
     * Not own.
     */
    CEikEdwin& iEdwin;
    
    /**
     * Position where bouncing down started.
     */
    TInt iBounceDownIndex;
    
    /**
     * Position where bouncing up started.
     */
    TInt iBounceUpIndex;
    
    /**
     * Previous Y-coordinate.
     */
    TInt iPreviousYCoordinate;
    
    /**
     * ETrue, if text selection has been started.
     */
    TBool iSelectionStarted;
            
    /**
     * ETrue, if dragging of content has been started.
     */
    TBool iDraggingStarted;
    
    /**
     * Start position of drag.
     */
    TPoint iStartPosition;
    };

#endif // C_AKNEDWINPHYSICSHANDLER_H
