/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Hierarchical list view.
*
*/


#ifndef C_AKNTREELISTVIEW_H
#define C_AKNTREELISTVIEW_H


#include <AknControl.h> // CAknControl
#include <eiksbobs.h>   // MEikScrollBarObserver
#include <AknsEffectAnim.h>
#include <AknsItemID.h>
#include <babitflags.h>
#include <eikcmobs.h>
#include <akntreelistobserver.h>
#include <akncollection.h>
#include <aknlongtapdetector.h>

#include "akntreeobserver.h"
#include "akntreelistviewitem.h"

class CAknTreeNode;
class CAknTreeList;
class TAknWindowComponentLayout;
class CAknsBasicBackgroundControlContext;
class CEikScrollBarFrame;
class CAknTreeListPhysicsHandler;
class CAknItemActionMenu;

/**
 *  Hierarchical list view.
 *
 *  The hierarchical list view is responsible of maintaining the set of tree
 *  view items representing which of the tree items are currently visible,
 *  handling pointer and keyboard events, and drawing the requested part of
 *  the view.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknTreeListView ) : public CAknControl,
                                        public MEikScrollBarObserver,
                                        public MAknTreeObserver,
                                        public MAknsEffectAnimObserver,
                                        public MEikCommandObserver,
                                        public MAknCollection,
                                        public MAknLongTapDetectorCallBack
                                        
    {

public:

    /**
     * Two-phased constructor.
     *
     * @param aContainer Container for the view.
     *
     * @param aTree Reference to the tree structure.
     *
     * @param aList Reference to the list.
     *
     * @return Pointer to newly constructed object.
     */
    static CAknTreeListView* NewL( const CCoeControl& aContainer,
        CAknTree& aTree, CAknTreeList& aList );

    /**
     * Destructor.
     */
    virtual ~CAknTreeListView();

    /**
     * Utility method for calculating the rectangle of a layout component.
     *
     * @param aParent Parent rectangle for the required rectangle.
     *
     * @param aComponentLayout Component layout for the required component.
     *
     * @return Required rectangle.
     */
    static TRect RectFromLayout( const TRect& aParent,
        const TAknWindowComponentLayout& aComponentLayout );

    /**
     * Sets the focused item and its position in the view. 
     *
     * @param aItem The item to be focused. @c NULL, if no item is focused.
     *
     * @param aIndex Position of the focused item in the view as an index. If
     *      the index is less than zero or greater than or equal to the number
     *      of items in the view, the focused item is changed, but the items
     *      in the view are not changed.
     *
     * @param aDrawNow @c ETrue to redraw the view after the focused item has
     *      been changed.
     */
    void SetFocusedItem( CAknTreeItem* aItem, TInt aIndex, TBool aDrawNow );

    /**
     * Sets the focused item and its position in the view. Moves view so that 
     * focused item is allways visible.
     *
     * @param aItem The item to be focused.
     *
     */
    void SetFocusedItemAndView( CAknTreeItem* aItem );
    
    /**
     * Gets the index of the focused item on the screen. Possible values are
     * from 0 to max. number of visible lines - 1. Value -1 is
     * returned if no item is focused or focused item is not visible. 
     *
     * @return index of the focused item on the screen.
     */
    TInt FocusedItemIndex() const;
    
    
    TInt VisibleItemIndex( CAknTreeItem* aItem ) const;

    
    /**
     * Sets focus behaviour after sorting. 
     *
     * @c ESaveFocus saves focus in the item where it was before sorting, 
     * @c EMoveFocusToFirstItem changes view to the beginning of the list
     * and moves focus to the first item.  
     *
     * @return index of the focused item on the screen.
     */
    void SetFocusBehaviour( TBool saveFocus );

    /**
     * Returns pointer to the focused item.
     *
     * @return Pointer to the focused item. @c NULL, if no item is focused.
     */
    CAknTreeItem* FocusedItem() const;

    /**
     * Returns the highlight rectangle for the currently focused item. The
     * returned rectangle is empty, if no visible item is highlighted.
     *
     * @return Highlight rectangle.
     */
    TRect HighlightRect() const;

    /**
     * Returns whether the list is looping or non-looping.
     *
     * @return @c ETrue, if the list is looping.
     */
    TBool IsLooping() const;

    /**
     * Sets the list looping or non-looping.
     *
     * @param aLooping @c ETrue to set list looping, @c EFalse to set list
     *      non-looping.
     */
    void SetLooping( TBool aLooping );

    /**
     * Returns whether the list structure lines are visible.
     *
     * @return @c ETrue, if the tree structure lines are set visible.
     */
    TBool StructureLines() const;

    /**
     * Sets the visibility of structure lines.
     *
     * @param aVisible @c ETrue to set the tree structure lines visible,
     *       @c EFalse to set them invisible.
     */
    void SetStructureLineVisibility( TBool aVisible );

    /**
     * Returns whether the indention of list items is enabled.
     *
     * @return @c ETrue, if indention is enabled.
     */
    TBool Indention() const;

    /**
     * Sets the indention of list items enabled or disabled.
     *
     * @param aEnabled @c ETrue ot enable indention, @c EFalse to disable it.
     */
    void EnableIndention( TBool aEnable );

    /**
     * Returns the width of single indention step.
     *
     * @return Width of indention step. Negative value is returned when
     *      the default indention step width is to be used.
     */
    TInt IndentionWidth() const;

    /**
     * Sets the width of one indention step.
     *
     * @param aIndentionWidth The size of the indention step. Negative value
     *      can be used to use the default indention step width in current
     *      layout, which is based on the structure line segment width.
     */
    void SetIndentionWidth( TInt aIndentionWidth );

    /**
     * Checks whether marking is enabled. When marking is enabled, the list
     * items can be marked and unmarked with pointer and key events specified
     * for markable lists.
     *
     * @return @c ETrue, if marking of list items is enabled.
     */
    TBool IsMarkable() const;

    /**
     * Enables or disables the marking of list items.
     *
     * @param aEnable @c ETrue to enable marking, @c EFalse to disable it.
     */
    void EnableMarking( TBool aEnable );

    /**
     * Sets text for the empty list. This text is visible if the list box 
     * has no items.
     *
     * @param aText The text for the empty list.
     */
    void SetEmptyTextL(const TDesC& aText);

    /**
     * Initializes physics.
     */
    void InitPhysicsL();
    
    /**
     * Sets highlight to item to be focused.
     *
     * @param aItemToBeFocused Focused item.
     * @param aIndexToBeFocused Focused item index.
     */
    void SetHighlight( CAknTreeItem* aItemToBeFocused,
                       const TInt& aIndexToBeFocused );
                      
    /**
     * Selects the item.
     *
     * @param aSelectedItem Item to be selected.
     */
    void SelectItem( CAknTreeItem* aSelectedItem );

    /**
     * Returns the count how many visible items fits to screen.
     *
     * @return Visible items count.
     */
    TInt VisibleItemCount() const;

    /**
     * Sets the pressed down state.
     * 
     * @param aPressedDown ETrue if highlight should be 
     * drawn in pressed-down state.
     */
    void SetPressedDownState( const TBool& aPressedDown );

    /**
     * Updates the tree list view.
     */
    void UpdateTreeListView( const TInt& aFirstItem, const TBool& aDrawNow );

    /**
     * Returns the offset value.
     *
     * @return Offset value.
     */
    TInt Offset() const;
    
    /**
     * Changes the marking of specified item when marking is enabled.
     *
     * @param aItem Pointer to the marked item.
     *
     * @param aMarked @c ETrue to mark item, @c EFalse to unmark it.
     *
     * @param aDrawNow @c ETrue to request redraw.
     */
    void MarkItem( CAknTreeItem* aItem, TBool aMarked, TBool aDrawNow );

    /**
     * Changes the marking of specified set of items when marking is enabled.
     *
     * @param aItem Pointer to the first of the marked items.
     *
     * @param aLast Pointer to the last of the marked items.
     *
     * @param aMarked @c ETrue to mark thee specified items, @c EFalse to
     *      unmark them.
     *
     * @param aDrawNow @c ETrue to request redraw.
     */
    void MarkItems( CAknTreeItem* aFirst, CAknTreeItem* aLast, TBool aMarked,
        TBool aDrawNow );

// from base class CCoeControl

    /**
     * From CCoeControl.
     * Handles key events.
     *
     * @param aKeyEvent Key event.
     *
     * @param aType The type of key event: @c EEventKey, @c EEventKeyUp or 
     *      @c EEventKeyDown.
     */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
        TEventCode aType );

    /**
     * From CCoeControl.
     * Changes the visibility of the hierarchical list.
     *
     * @param aVisible @c ETrue to make the list visible, @c EFalse to make
     *      it invisible.
     */
    void MakeVisible( TBool aVisible );

    /**
     * From CCoeControl.
     * Sets the control's containing window by copying it from aContainer.
     *
     * @param aContainer Container.
     */
    void SetContainerWindowL( const CCoeControl& aContainer );

    /**
     * From CCoeControl.
     * Handles a change to the control's resources.
     *
     * @param aType A message UID value. 
     */
    void HandleResourceChange( TInt aType );

    /**
     * From CCoeControl.
     * Handles pointer events.
     *
     * @param aPointerEvent Pointer event.
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

    /** 
     * From CCoeControl.
     * Gets the number of controls contained in a compound control.
     *
     * @return The number of component controls contained by this control.
     */
    TInt CountComponentControls() const;

    /**
     * From CCoeControl.
     * Gets an indexed component of a compound control.
     *
     * @param aIndex The index of the control.
     *
     * @return The component control with an index of aIndex.
     */
    CCoeControl* ComponentControl( TInt aIndex ) const;

// from base class MEikScrollBarObserver

    /**
     * From MEikScrollBarObserver.
     * Handles events from scroll bar.
     *
     * @param aScrollBar Pointer to the scrollbar.
     *
     * @param aEventType Event type.
     */
    void HandleScrollEventL( CEikScrollBar* aScrollBar,
        TEikScrollEvent aEventType );

// from base class MAknTreeObserver

    /**
     * From MAknTreeObserver.
     * Handles event from the tree structure.
     *
     * @param aEvent Tree event.
     *
     * @param aItem Tree item targeted by the specified event.
     *
     * @param aDrawNow @c ETrue, when the view should be redrawn.
     */
    void HandleTreeEvent( TEvent aEvent, CAknTreeItem* aItem,
        TBool aDrawNow );

// from base class MAknsEffectAnimObserver

    /**
     * From MAknsEffectAnimObserver.
     * Animation frame is ready to be drawn.
     *
     * @param aError @c KErrNone, if frame has been succesfully created and
     *      is available for drawing. Otherwise animation has internally
     *      failed and will not be used by the tree list view anymore.
     *
     * @param aAnimId Not currently used.
     */
    void AnimFrameReady( TInt aError, TInt aAnimId );

// from base class MEikCommandObserver

    /**
     * From MEikCommandObserver.
     * Handles user commands.
     *
     * @param ID of the commmand to respond to.
     */
    void ProcessCommandL( TInt aCommandId );



#ifdef RD_UI_TRANSITION_EFFECTS_LIST
// ---------------------------------------------------------------------------
// Sets the tfxgc for effects
// ---------------------------------------------------------------------------
//
void SetGc( CWindowGc* aGc);

TInt& ItemCountLimit();
TInt& HighlightIndex();
TInt& TopIndex();
TInt& BottomIndex();

void UpdateIndexes();

TInt iItemCountLimit;
TInt iHighlightIndex;
TInt iTopIndex;
TInt iBottomIndex;

#endif //RD_UI_TRANSITION_EFFECTS_LIST

public:  // new method
    /**
     * Report event to tree list observers. Use it to aviod dependency of 
     * @c CAknTreeList
     * 
     * @param aEvent The event to be notified.
     * 
     * @param aItem ID of the tree item related to the event.
     */
    void ReportTreeListEvent( MAknTreeListObserver::TEvent aEvent, 
                              TAknTreeItemID aItem);

protected:

// from base class CCoeControl

    /**
     * From CCoeControl.
     * Handles focus change.
     *
     * @param aDrawNow @c EDrawNow to redraw the list.
     */
    void FocusChanged( TDrawNow aDrawNow );

    /**
     * From CCoeControl.
     * Responds to changes to the size and position of this control.
     */
    void SizeChanged();

    /**
     * From CCoeControl.
     * Responds to changes in the position of this control.
     */
    void PositionChanged();

    /**
     * From CCoeControl.
     * Retrieves an object of the same type as that encapsulated in aId.
     *
     * @param aId An encapsulated object type ID.
     *
     * @return Encapsulates the pointer to the object provided. Note that the
     *      encapsulated pointer may be NULL
     */
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
    
private:

    /**
     * C++ constructor.
     *
     * @param aTree Reference to the tree structure.
     */
    CAknTreeListView( CAknTree& aTree, CAknTreeList& aList );

    /**
     * Second phase constructor.
     *
     * @param aContainer Container for the view.
     */
    void ConstructL( const CCoeControl& aContainer );

    /**
     * Handes an addition of item to the tree structure.
     *
     * @param aItem Pointer to the added tree item.
     */
    void HandleItemAddedEvent( CAknTreeItem* aItem, TBool aDrawNow );

    /**
     * Handles a movement of tree item.
     *
     * @param aItem Pointer to the moved item.
     */
    void HandleItemMovedEvent( CAknTreeItem* aItem );

    /**
     * Handles a removal of item from the tree structure.
     *
     * @param aItem Pointer to the removed tree item.
     */
    void PrepareForItemRemoval( CAknTreeItem* aItem, TBool aDrawNow );

    /**
     * Handles a removal of item from the tree structure.
     *
     * @param aItem Pointer to the removed tree item.
     */
    void HandleItemRemovedEvent( CAknTreeItem* aItem, TBool aDrawNow );

    /**
     * Handles an expansion of a tree node.
     *
     * @param aNode Pointer to the expanded tree node.
     */
    void HandleNodeExpandedEvent( CAknTreeNode* aNode );

    /**
     * Handles a collapse of a tree node.
     *
     * @param aNode Pointer to the collapsed tree node.
     */
    void HandleNodeCollapsedEvent( CAknTreeNode* aNode );

    /**
     * Handles change in tree item.
     *
     * @param aItem Pointer to the modified tree item.
     */
    void HandleItemModifiedEvent( CAknTreeItem* aItem );

    /**
     * Handles tree sorting.
     */
    void HandleTreeSortedEvent( TBool aDrawNow );

    /**
     * Updates the set of tree items in the view.
     */
    void UpdateVisibleItems();

    /**
     * Updates the set of tree items in the view so, that the given item is
     * set at the given position of the view.
     *
     * @param aIndex Position of the given index in the view.
     *
     * @param aItem Tree items to be set to the given view position.
     */
    void UpdateVisibleItems( TInt aIndex, CAknTreeItem* aItem );

    /**
     * Selects the focused item. When the focused item is a leaf, the selection
     * event is passed to the list client, and when the focused item is a node,
     * the node is either expanded or collapsed.
     */
    void HandleSelectionKeyEvent();

    /**
     * Handles right arrow key event.
     */
    void HandleRightArrowKeyEvent();

    /**
     * Handles left arrow key event.
     */
    void HandleLeftArrowKeyEvent();

    /**
     * Moves the focus upwards and changes the set of visible items so that
     * the focused item becomes visible.
     */
    void HandleUpArrowKeyEvent();

    /**
     * Moves the focus downwards and changes the set of visible items so that
     * the focused item becomes visible. 
     */
    void HandleDownArrowKeyEvent();

    /**
     * Moves the focus deeper in the tree structure. If the focused item is
     * a collapsed node, this method expands the node. If the focused item is
     * a non-empty, expanded node, the focus is moved to the first item in
     * the node.
     */
    void DescendFocus();

    /**
     * Moves the focus higher in the tree structure. If the focused item is
     * an expanded node, this method collapses the node. Otherwise, the focus
     * is moved to the parent node.
     */
    void AscendFocus();

    /**
     * Returns whether the list view is empty.
     */
    TBool IsEmpty() const;

    /**
     * Sets the layout for the view from the layout data.
     */
    void LayoutView();

    /**
     * Updates scrollbars.
     */
    void UpdateScrollbars();

    /**
     * Updates the horizontal position of the view so that the beginning of
     * the currently focused item can be seen. If the focused item is not in
     * the set of visible items, this method has no effect.
     */
    void UpdateViewLevel();

    /**
     * Updates the highlight animation by setting the correct size and
     * background for the animation.
     *
     * @return @c ETrue, if animation is successfully updated, or there is
     *      no need to update it. Otherwise, @c EFalse is returned.
     */
    TBool UpdateAnimation() const;

    /**
     * Updates the highlight animation by setting the correct size and
     * background for the animation based on the given rectangle.
     *
     * @param aRect Rectangle specifying the size and position of the
     *      highlight animation.
     *
     * @return @c ETrue, if animation is successfully updated, or there is
     *      no need to update it. Otherwise, @c EFalse is returned.
     */
    TBool UpdateAnimation( const TRect& aRect ) const;

    /**
     * Sets the specified item focused.
     *
     * @param aFocusedItem Item to be focused. @c NULL, if no item is focused.
     */
    void SetFocusedItem( CAknTreeItem* aFocusedItem );

    /**
     * Checks whether the focused item is in the set of visible items.
     *
     * @return @c ETrue, if focused item is visible.
     */
    TBool FocusedItemVisible() const;

    /**
     * Sets the position of focused item in the view. Any negative number can
     * be used to indicate that focused item is not one of the visible items.
     *
     * @param aIndex Index specifying the position of the focused item in the
     *      set of visible items.
     */
    void SetFocusIndex( TInt aIndex );

    /**
     * Returns the position of focused item in the view.
     *
     * @return Index specifiying the focused item's position.
     */
    TInt FocusIndex() const;

    /**
     * Creates highlight animation for the view from currently active skin.
     * Existing animation is deleted before the new is created.
     */
    void CreateAnimationL();

    /**
     * Draws highligt animation background to given graphic context.
     *
     * @param aGc Graphic context to which highlight background is drawn.
     *
     * @return @c ETrue, if background is drawn successfully.
     */
    TBool DrawHighlightBackground( CFbsBitGc& aGc ) const;

    /**
     * Changes the highlight animation size to the specified.
     *
     * @param aHighlightSize New size for the highlight animation.
     *
     * @param aAboutToStart If animation is about to be started or continued
     *      after layer configuration this should be set to @c ETrue (to keep
     *      input layers). Otherwise, @c EFalse should be used.
     */
    void ResizeAnimationL( const TSize& aHighlightSize,
        TBool aAboutToStart ) const;

    /**
     * Draws the highlight animation of given size and position to the given
     * graphic context. The size and background of current animation is
     * updated when necessary, but to avoid flickering, they should be
     * done already before drawing sequence with UpdateAnimation() method.
     *
     * @param aGc Graphic context.
     *
     * @param aRect Size and poistion of the highlight animation.
     *
     * @return @c ETrue, if highlight animation was updated and drawn
     *      successfully. Otherwise, @c EFalse is returned.
     */
    TBool DrawAnimation( CBitmapContext& aGc, const TRect& aRect ) const;

    /**
     * Draws the highlight of given size and position to the given graphic
     * context.
     *
     * @param aGc Graphic context.
     *
     * @param aRect Rectangle specifying the size and position of the
     *      highlight to be drawn.
     *
     * @param aPressedDown @c EFalse, to draw normal highlight. @c ETrue, to 
     * draw a pressed down state.
     */
    void DrawHighlight( CWindowGc& aGc, const TRect& aRect, TBool aPressedDown = EFalse ) const;
    

    /**
     * Handles selection of specified item, by expanding the item, if it is
     * a collapsed node; collapsing the item, if it is an expanded node; or
     * selecting the item, if it is a leaf.
     *
     * @param aItem Item to be selected.
     * @param aKeyPressed Indicates that selection key has been pressed
     */
    void SelectItem( CAknTreeItem* aItem, bool aKeyPressed );

    /**
     * Begins marking. The marking begins immediately after the user
     * presses any of the the marking modifier keys (shift, ctrl, edit,
     * or hash key). This method registers view to observe MSK commands,
     * and start the timer for entering marking mode.
     */
    void BeginMarkingL();

    /**
     * Ends marking.
     */
    void EndMarking();

    /**
     * Checks whether marking is currently ongoing.
     *
     * @return @c ETrue, if list items are beign marked.
     */ 
    TBool MarkingOngoing() const;

    /**
     * Starts the long press timer.
     */
    void StartLongPressTimerL();

    /**
     * Callback method for long press timer.
     *
     * @param aThis Pointer to an instance of @c CAknTreeListView class.
     *
     * @return @c NULL, as function is intended to be called only once.
     */
    static TInt ReportLongPressL( TAny* aThis );

    /**
     * Handles long press. Called from ReportLongPressL() method for the
     * view object given as parameter.
     */
    void DoHandleLongPressL();

    /**
     * Enters marking mode. When in marking mode, the list controls the MSK
     * commands depending on whether the currently focused item is marked or
     * unmarked. Marking mode is entered after specified timeout, when user
     * keeps one of the marking modifier keys pressed.
     *
     * Notifications of the beginning and ending of marking mode is sent to
     * list observers, so that they would not update the MSK commands, when
     * they are handled by the list.
     */
    void EnterMarkingMode();

    /**
     * Exits marking mode. Marking mode is exited when user releases
     * all the marking modifier keys. After that, the list no longer
     * handles the MSK commands.
     */
    void ExitMarkingMode();

    /**
     * Updates correct mark/unmark command to MSK depending on the marking
     * of current focused item.
     */
    void UpdateMSKCommand();

    /**
     * Draws the items when physics is enabled.
     *
     * @param aRect Drawing rect.
     */
    void DrawItemsWithPhysics( const TRect& aRect ) const;

    /**
     * Returns first visible item index.
     *
     * @return First visible item index.
     */
    TInt FirstVisibleItemIndex() const;

    /**
     * Returns last visible item index.
     *
     * @return Last visible item index.
     */
    TInt LastVisibleItemIndex() const;

    /**
     * Updates view items so that aItem is visible.
     *
     * @param aItem Tree item that should be visible.
     */
    void UpdateViewItemAsVisible( CAknTreeItem* aItem );

// from base class CCoeControl

    /**
     * From CCoeControl.
     * Draws the tree list view.
     *
     * @param aRect Area that needs to be redrawn.
     */
    void Draw( const TRect& aRect ) const;

// Single click functions
public:    
    /**
     * Is single click enabled
     * 
     * @return ETrue if single click is enabled
     */
    TBool SingleClickEnabled() const;
    
    /**
     * Enables or disables highlight
     * 
     * @param ETrue to enable highlight, EFalse to disable
     */
    void EnableHighlight( TBool aEnabled );

    /**
     * Is highlight enabled
     * 
     * @return ETrue if highlight is enabled
     */
    TBool HighlightEnabled() const;    
    
    /**
     * Pointer event to long tap detector
     * 
     * @param aPointerEvent Pointer event
     */
    void LongTapPointerEventL( const TPointerEvent& aPointerEvent );

    /**
     * Cancel long tap detection
     * 
     */
    void CancelLongTapDetectorL();

    /**
     * Has list marked items
     * 
     * @return ETrue if list has marked items
     */    
    TBool HasMarkedItemsL();    
    
// From MAknCollection
    /**
     * Returns the collection state. The state is combination of
     * flags defined in MAknCollection::TStateFlag. 
     *
     * @return  Collection state.
     */
    TUint CollectionState() const;

    /**
     * Notifies that item action menu (CAknItemActionMenu)
     * was closed. 
     */
    void ItemActionMenuClosed();
    
    /** 
     * Extension function.
     *
     * @param  aExtensionId  Extension id. 
     * @param  a0            First extension method parameter.
     * @param  a1            Second extension method parameter.
     */    
    TInt CollectionExtension( TUint aExtensionId, TAny*& a0, TAny* a1 );    

// From MAknLongTapDetectorCallBack
    /**
     * Long tap detector callback 
     *
     * @param aPenEventLocation Long tap event location relative to parent control.
     * @param aPenEventScreenLocation Long tap event location relative to screen.
     */
    void HandleLongTapEventL( const TPoint& aPenEventLocation,
                                  const TPoint& aPenEventScreenLocation );
    
    
private: // data

    /**
     * Tree structure.
     */
    CAknTree& iTree;

    /**
     * List interface.
     */
    CAknTreeList& iList;

    /**
     * Array for visible view items.
     */
    RArray<TAknTreeListViewItem> iItems;

    /**
     * Pointer to currently focused list item.
     * Not own.
     */
    CAknTreeItem* iFocusedItem;

    /**
     * Position of focused item in the view. The focused item can be outside
     * of the view as well. In which case, the index can be outside the scope
     * of valid indices to the @c iItems array.
     */
    TInt iFocusedItemIndex;

    /**
     * View level. This defines the views horizontal position from which the
     * tree items are drawn.
     */
    TInt iViewLevel;

    /**
     * Maximum view level. Depends on the depth of the tree structure.
     */
    TInt iMaxViewLevel;

    /**
     * Horizontal view span defines how many tree levels of tree items with
     * minimum width can be displayed simultaneously. This value is updated
     * from the layout data on layout changes.
     */
    TInt iHorizontalViewSpan;

    /**
     * Text for empty list.
     * Own.
     */
    HBufC* iEmptyListText;

    /**
     * Scrollbar frame.
     * Own.
     */
    CEikScrollBarFrame* iScrollbarFrame;

    /**
     * Index of the item, which received the stylus down event.
     */
    TInt iStylusDownItemIndex;

    /**
     * Animation skin item ID used for highlight animation.
     */
    TAknsItemID iAnimationIID;

    /**
     * Long press timer.
     * Own.
     */
    CPeriodic* iLongPressTimer;

    /**
     * Highlight animation.
     * Own.
     */
    mutable CAknsEffectAnim* iAnimation;

    /**
     * Flags for the view.
     */
    mutable TBitFlags32 iFlags;

    /**
     * Width of single indention step.
     */
    TInt iIndentionWidth;
    
     /**
     * Pointer to the list item that was focused before EButton1Down event.
     * Not own.
     */
    CAknTreeItem* iPreviouslyFocusedItem;

    TBool iIsPressedDownState;
    
    TBool iIsDragged;
    
    /**
     * Physics handler. Used only when physics feature is enabled.
     * Own.
     */
    CAknTreeListPhysicsHandler* iPhysicsHandler;

    /**
     * ETrue if physics view should be adjusted according to top item.
     */
    TBool iScrollPhysicsTop;

    /**
    * Pointer to tfx redirect gc for effects
    *
    */
    CWindowGc* iGc;
    
    /**
     * Pointer to item action menu.
     * Not own.
     */
    CAknItemActionMenu* iItemActionMenu;    
    
   /**
    * Long tap detector
    */
    CAknLongTapDetector* iLongTapDetector;
    };


#endif // C_AKNTREELISTVIEW_H
