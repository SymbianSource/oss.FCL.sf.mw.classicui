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
* Description:   AknTreeListView physics handler
*
*/



#ifndef C_AKNSTYLUSPOPUPMENUPHYSICSHANDLER_H
#define C_AKNSTYLUSPOPUPMENUPHYSICSHANDLER_H


#include <e32base.h>
#include <w32std.h>
#include <aknphysicsobserveriface.h>

class CAknPhysics;
class CAknStylusPopUpMenuContent;

/**
 *  StylusPopUpmenu physics handler.
 *
 *  @lib aknhlist
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknStylusPopUpMenuPhysicsHandler ) : public CBase,
    public MAknPhysicsObserver
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknStylusPopUpMenuPhysicsHandler* NewL( CAknStylusPopUpMenuContent* aPopUpMenuContent );

    /**
     * Two-phased constructor.
     */
    static CAknStylusPopUpMenuPhysicsHandler* NewLC( CAknStylusPopUpMenuContent* aPopUpMenuContent );
    /**
     * Destructor.
     */
    virtual ~CAknStylusPopUpMenuPhysicsHandler();
    
public:

    /**
     * Handles the pointer event received by AknStylusPopUpMenuContent
     *
     * @param aPointerEvent Pointer event to handle.
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );                      
    
    /**
     * Sets view rect.
     *
     * @param aRect New view rect.
     */
    void SetViewRect( const TRect& aRect );

    /**
     * Sets item height.
     *
     * @param aItemHeight New item height.
     */
    void SetItemHeight( TInt aItemHeight );
    
    /**
     * Sets world height.
     *
     * @param aWorldHeight New world height.
     */
    void SetWorldHeight( TInt aWorldHeight );

    /**
     * Returns offset. Used to draw partial items.
     */
    TInt Offset() const;
    
    /**
     * Initializes physics.
     */
    void InitPhysicsL();
    
    /**
     * Scrolls the view to new position.
     *
     * @param aNewScrollIndex New view position.
     */
    void HandleScrollEvent( TInt aNewScrollIndex );

    /**
     * Resets physics so that location is set to world's top position.
     * 
     * @since S60 5.2
     */
    void Reset();
    
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
    CAknStylusPopUpMenuPhysicsHandler( CAknStylusPopUpMenuContent* aPopUpMenuContent );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();
    
    /**
     * Returns drag threshold.
     *
     * @return drag threshold.
     */
    TInt DragThreshold();
    
    /**
     * Sets highlight to item.
     * 
     * @param aItem Item to be highlighted.
     */
    void SetHighlight( TInt aItem );

    /**
     * Moves view to correct position.
     * 
     * @param  aDrawNow  Whether or not the view is drawn. If @c EFalse,
     *                   then only the logical state is updated.
     */
    void ScrollView( TBool aDrawNow = ETrue );
    
    /**
     * Stops physics.
     */
    void StopPhysics();


private: // data

    /**
     * PopUpMenuContent
     * Not own.
     */
    CAknStylusPopUpMenuContent* iPopUpMenuContent;

    /**
     * Scroll index.
     */
    TInt iScrollIndex;
    
    /**
     * Height of one item.
     */
    TInt iItemHeight;
    
    /**
     * Height of world.
     */
    TInt iWorldHeight;

    /**
     * Current pointer position.
     */   
    TPoint iPosition;
    
    /**
     * Start (pointer down) position.
     */
    TPoint iStartPosition;
    
    /**
     * View rect.
     */
    TRect iViewRect;
    
    /**
     *  ETrue if pointer down event received but pointer up not.
     */
    TBool iPressedDown;
    
    /**
     * ETrue if panning functionality is activated.
     */
    TBool iPanningActivated;
    
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
     * Previous offset.
     */
    TInt iPrevOffset;
    
    /**
     * Previous topmost item
     */
    TInt iPrevTopmostItem;
    
    /**
     * count of offset item
     */
    TInt iOffsetItemCount;
    
    };


#endif // C_AKNSTYLUSPOPUPMENUPHYSICSHANDLER_H
