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
* Description:  AknTreeListView physics handler
*
*/


#ifndef C_AKNTREELISTPHYSICSHANDLER_H
#define C_AKNTREELISTPHYSICSHANDLER_H


#include <e32base.h>
#include <aknphysicsobserveriface.h>

class CAknPhysics;
class CAknTreeItem;
class CAknTree;
class CAknTreeListView;
class CWindowGc;
class MTouchFeedback;
/**
 *  Tree list physics handler.
 *
 *  @lib aknhlist
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknTreeListPhysicsHandler ) : public CBase,
                                                  public MAknPhysicsObserver
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknTreeListPhysicsHandler* NewL( CAknTreeListView* aTreeListView,
                                             CAknTree* aTree,
                                             RArray<TAknTreeListViewItem>* aItems );

    /**
     * Two-phased constructor.
     */
    static CAknTreeListPhysicsHandler* NewLC( CAknTreeListView* aTreeListView,
                                              CAknTree* aTree,
                                              RArray<TAknTreeListViewItem>* aItems );
    /**
     * Destructor.
     */
    virtual ~CAknTreeListPhysicsHandler();
    
public:

    /**
     * Handles the pointer event received by tree list view.
     *
     * @param aPointerEvent Pointer event to handle.
     * @param aViewLevel Tree list view level.
     * @param aMarking Item marking mode.
     * @param aShiftPressed Hw shift key.
     * @param aCtrlPressed Hw control key.
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent,
                              const TInt& aViewLevel,
                              TBool aMarking,
                              TBool aShiftPressed,
                              TBool aCtrlPressed );

    /**
     * Handles the scroll event received by tree list view.
     *
     * @param aEventType Scroll event to handle.
     * @param aThumbPosition Scroll bar thumb position.
     */
    void HandleScrollEventL( TEikScrollEvent aEventType,
                             const TInt& aThumbPosition );
                             
    /**
     * Handles key events for scroll physics
     *
     * @param aKeyCode Hw key code.
     */                         
    void HandleKeyEvent( TInt aKeyCode );                        
    
    /**
     * Sets view rect.
     *
     * @param aRect New view rect.
     */
    void SetViewRect( const TRect& aRect );

    /**
     * Returns view rect.
     */
    TRect ViewRect( ) const;
    
    /**
     * Sets item height.
     *
     * @param aHeight New item height.
     */
    void SetItemHeight( const TInt& aHeight );

    /**
     * Returns offset. Used to draw partial items.
     */
    TInt Offset() const;
    
    /**
     * Initializes physics.
     */
    void InitPhysicsL();

    /**
     * Resets the pointer event disabling/enabling status.
     */
    void ResetEventBlockingStatus();
    
    /**
     * Provides vertical scroll bar parameters.
     *
     * @param aThumbSpan
     * @param aThumbPos
     * @param aScrollSpan
     */
    void GetVScrollbarParams( TInt& aThumbSpan, 
                              TInt& aThumbPos, 
                              TInt& aScrollSpan );

    /**
     * Returns ETrue if focused item is visible.
     *
     * @param aFocusedIndex Focused item index.
     * @return ETrue if focused item is visible.
     */
    TBool FocusedItemVisible( const TInt& aFocusedIndex ) const;
    
    /**
     * Returns the first visible item index.
     *
     * @return First visible item index.
     */
    TInt FirstVisibleItemIndex() const;

    /**
     * Returns the last visible item index.
     *
     * @return Last visible item index.
     */
    TInt LastVisibleItemIndex() const;

    /**
     * Updates the scroll index.
     *
     * @param aScrollTop ETrue if scroll index should be adjusted according to
     * first visible item, EFalse if last item.
     */
    void UpdateScrollIndex( const TBool& aScrollTop );

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
    
public: // New methods.
    
    /**
     * Sets graphics context used by listbox effects.
     */
    void SetGc( CWindowGc* aGc );

private:

    /**
     * C++ constructor.
     */
    CAknTreeListPhysicsHandler( CAknTreeListView* aTreeListView,
                                CAknTree* aTree,
                                RArray<TAknTreeListViewItem>* aItems );

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
     * Launches the highlight timer.
     * 
     * @param aWasScrolling ETrue if content was scrolling. In that case
     *                      highlight is drawn with timeout.
     */
    void LaunchHighlightTimer( TBool aWasScrolling );

    /**
     * Callback method for highlight timer.
     *
     * @param aThis Pointer to an instance of @c CAknTreeListView class.
     *
     * @return @c NULL, as function is intended to be called only once.
     */
    static TInt HighlightTimerCallback( TAny* aPtr );
    
    /**
     * Sets highlight to focused item.
     */
    void SetHighlight();

    /**
     * Moves view to correct position.
     *
     * @param ETrue to redraw the view after movement 
     */
    void ScrollView( TBool aDrawNow );
    
    /**
     * Stops physics.
     */
    void StopPhysics();

    /**
     * Returns world height.
     *
     * @return World height.
     */
    TInt WorldHeight();

    /**
     * Returns wheter pointer click is in empty list area.
     *
     * @return ETrue if aPosition is in empty list area.
     */    
    TBool EmptyAreaClicked( TPoint aPosition );
    
private: // data

    /**
     * Scroll index.
     */
    TInt iScrollIndex;
    
    /**
     * Previous scroll index.
     */
    TInt iPreviousIndex;
    
    /**
     * Height of one item.
     */
    TInt iItemHeight;

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
     * ETrue if pointer events are blocked.
     */
    TBool iEventsBlocked;

    /**
     * ETrue if pointer events are enabled.
     */
    TBool iEnableEvents;
    
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
     * Highlight timer.
     * Own.
     */
    CPeriodic* iHighlightTimer;
    
    /**
     * Pointer to the list item to be focused by highlight timer.
     * Not own.
     */
    CAknTreeItem* iItemToBeFocused;
    
    /**
     * Pointer to the list item to be selected.
     * Not own.
     */
    CAknTreeItem* iItemToBeSelected;
    
    /**
     * Index of the list item to be focused by highlight timer.
     */
    TInt iIndexToBeFocused;

    /**
     * Physics handler flags.
     */
    TBitFlags iFlags;
    
    /**
     * Pointer to tree.
     * Not own.
     */
    CAknTree* iTree;
    
    /**
     * Pointer to tree list view.
     * Not own.
     */
    CAknTreeListView* iTreeListView;

    /**
     * Pointer to array for visible view items.
     * Not own.
     */
    RArray<TAknTreeListViewItem>* iItems;
    
    /**
     * Offset between list first item position and view rect position.
     */
    TInt iListTopOffset;
    
    /**
     * Graphics context used by the parent listbox. Needed for transition
     * effects.
     */
    CWindowGc* iTfxGc;

    /**
     * Determines whether or not next up event should cause basic list 
     * feedback. The value is determined always on down event. If the value
     * on up event is EFalse, feedback is not played. If the value is ETrue,
     * basic list feedback is produced.
     */
    TBool iPlayFeedbackOnUp;

    /**
     * Pointer to the feedback object. Not owned.
     */    
    MTouchFeedback* iFeedback;
    // when touch down, it is true for recording physics Y of current view
    TBool iPenDown;
    // top item in current view, -1 if item's Y is negative
    TInt iOldTopItem;
    // bottom item in current view, fields count when Y is larger than
    // the last item's Y
    TInt iOldBottomItem; 
    /**
     * ETrue if empty list area is clicked.
     */    
    TBool iEmptyAreaClicked;
    };


#endif // C_AKNPHYSICSPARAMETERPROVIDER_H
