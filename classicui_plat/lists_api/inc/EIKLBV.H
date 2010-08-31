/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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



#if !defined(__EIKLBV_H__)
#define __EIKLBV_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

class CListItemDrawer;
class MListBoxModel;
class CWindowGc;
class RWindowGroup;
class CWsScreenDevice;
class CWindowGc;
class RWindow;
class CListBoxViewExtension;
class CEikListBox;

//
// class MListVisibiltyObserver
//

class MListVisibilityObserver 
	{
public:
	virtual TBool IsVisible() const = 0;
	};

/**
 * List box view.
 *
 * A list box view displays the list items which are currently visible in 
 * a list box. List box views draw each of the items for display using 
 * methods defined in their associated list box drawer. 
 *
 * Together with its list item drawer, a @c CListBoxView encapsulates the 
 * on-screen appearance of data in a list box.
 *
 * List box views also encapsulate item selection, the current item, and the 
 * fundamentals of how the selection and the current item are updated according
 * to user input. Input events themselves are handled by @c CEikListBox, 
 * which calls member functions of @c CListBoxView appropriately.
 *
 * This class is sufficient for plain list box views, and may be derived from 
 * in order to provide more complex list views. @c TechView supplies and uses 
 * the classes @c CHierarchicalListBoxView and @c CSnakingListBoxView, which 
 * provide two kinds of indented list views.
 */
class CListBoxView : public CBase
	{
public:

    /**
     * Cursor movement flags. These describe the cursor movements recognised by
     * @c MoveCursorL().
     */
    enum TCursorMovement 
		{
        /** Cursors movement to next item. */
        ECursorNextItem,  	

        /** Cursors movement to previous item. */
        ECursorPreviousItem,

        /** Cursors movement to next column. */
        ECursorNextColumn,  

        /** Cursors movement to previous column. */
        ECursorPreviousColumn,  

        /** Cursors movement to previous page. */
        ECursorPreviousPage, 

        /** Cursors movement to next page. */
        ECursorNextPage,

        /** Cursors movement to the first item. */
        ECursorFirstItem,

        /** Cursors movement to the last item. */
        ECursorLastItem,

        /** Cursors movement to the next screen. */
        ECursorNextScreen,

        /** Cursors movement to the previous screen. */
        ECursorPrevScreen
        };  

    /**
     * List box view flags.
     *
     * These flags may be combined with a logical OR to get a combination of 
     * effects.
     */
	enum TFlags
		{
        /** A selection anchor exists. */
		EAnchorExists   = 0x0001,

        /** The view is emphasised. */
		EEmphasized     = 0x0002,

        /** The view is dimmed. */
		EDimmed         = 0x0004,

        /** List box view has a cursor for incremental matching. */
		EHasMatcherCursor = 0x0008,

        /** Redraw is disabled. */
		EDisableRedraw  = 0x0010,

        /** If set, selected items are painted. */
		EPaintedSelection = 0x0020,

        /** Item marking enabled. */
		EMarkSelection  = 0x0040,

        /** Item unmarking enabled. */
		EUnmarkSelection = 0x0080,

        /** Item count changes enabled. */
		EItemCountModified = 0x0100,

        /** Vertical offset has changed. */
		EOffsetChanged = 0x0200,
		};
		
    /**
     * Modes for modifying the selection.
     *
     * Changing the current item of a list box view may also affect which items
     * are selected. The selection mode of such an action describes how (or if)
     * the selection is altered by the action.
     *
     * Each function of @c CListBoxView which affects the current item is 
     * passed an appropriate selection mode by the calling input handler method
     * of @c CEikListBox. The mode is varied according to the keyboard 
     * modifiers held down by the user, or whether a pointer action was a tap 
     * or a sweep.
     *
     * Note that the behaviour of list box views may vary with the target 
     * phone due to the wide range of possible input devices. 
     * The following description assumes a phone with a pointer and a keyboard.
     */
    enum TSelectionMode 
        {
        /** 
         * The selection is not changed by actions while this is in effect, 
         * holding CTRL while pressing cursor up or down for example.
         */
        ENoSelection,
    
        /** 
         * Only a single item in the list is allowed to be selected by an 
         * action; when selecting individual items with the pointer, or 
         * moving using the cursor keys without any modifiers for example.
         */
        ESingleSelection,

        /** 
         * A single continuous run of items can be added to the selection array
         * by an action, when keyboard-selecting with the shift key held down, 
         * or when sweeping a selection with the pointer for example.
         */
        EContiguousSelection,

        /** 
         * Any single item in the list may be added to the selection by an 
         * action, when selecting or drag-selecting with the pointer when the
         * @c CTRL key is held down for example.
         */
        EDisjointSelection,

        /** 
         * Any single item in the list may be removed from the selection by an 
         * action, when unselecting for example.
         */
        EDisjointMarkSelection,

        /** 
         * Multiple items can be added to the selection array by an action, 
         * when selecting with the edit key for example.
         */
        EPenMultiselection,

        /** 
         * Mark mode is changed to @c EUnmarkSelection if item is marked or 
         * @c EMarkSelection if item is not marked by an action, when selecting
         * or unselecting item for example.
         */
        EChangeMarkMode
        };

    /** The items which are selected within a list box list. */
	typedef CArrayFix<TInt> CSelectionIndexArray;

public:

    /**
     * Destructor.
     */
	IMPORT_C ~CListBoxView();

    /**
     * C++ default constructor.
     *
     * Allocates an area of memory for a @c CListBoxView, and begins its 
     * initialisation.
     */
    IMPORT_C CListBoxView();

    /**
     * By default Symbian 2nd phase constructor is private. 
     *
     * This function completes the initialisation of a default-constructed list
     * box view. The item drawer’s graphics context is created on @c aScreen, 
     * and the list item drawer’s graphics context is set to this. See 
     * @c CListItemDrawer::SetGc().
     * 
     * @param aListBoxModel The list box model to use. 
     * @param aItemDrawer A default-constructed item drawer. 
     * @param aScreen Screen on which to display. 
     * @param aGroupWin This list box view’s window group. 
     * @param aWsWindow Window for this view. 
     * @param aDisplayArea The viewing rectangle this list box view is to use.
     * @param aItemHeight Height of a single list item. 
     */
    IMPORT_C virtual void ConstructL(MListBoxModel* aListBoxModel, 
                                     CListItemDrawer* aItemDrawer, 
                                     CWsScreenDevice* aScreen, 
                                     RWindowGroup* aGroupWin, 
                                     RWindow* aWsWindow, 
                                     const TRect& aDisplayArea, 
                                     TInt aItemHeight);

    // functions for accessing the view rect (the area of the host window in 
    // which the items are drawn)
    /**
     * Gets the list box’s view rectangle.
     *
     * @return This list box’s view rectangle.
     */
    IMPORT_C TRect ViewRect() const;

    /**
     * Sets the area within the list window in which the view can draw itself.
     * 
     * @param aRect New view rectangle.
     */
	IMPORT_C void SetViewRect(const TRect& aRect);  

	// misc. access functions for the main attributes 
    /**
     * Gets the current item’s index.
     *
     * @return Index number of the current item.
     */
	IMPORT_C virtual TInt CurrentItemIndex() const;	

    /**
     * Set the index of the current item. This function changes the current 
     * item, but does not redraw the list view or update the selection.
     *
     * @param aItemIndex Which item to make current.
     * @panic EEikPanicListBoxInvalidCurrentItemIndexSpecified Panics if the 
     *        given index is not valid. 
     */
	IMPORT_C void SetCurrentItemIndex(TInt aItemIndex); 

    /**
     * Gets the index of the item at the top of the view.
     *
     * @return The item currently displayed at the top of this list box view.
     */
	IMPORT_C TInt TopItemIndex() const;		

    /**
     * Sets the item at the top of the view by its index in the list of all 
     * items. This function also invokes @c CalcBottomItemIndex().
     *
     * @param aItemIndex Index of the item to start the view at.
     * @panic EEikPanicListBoxInvalidTopItemIndexSpecified Panics if the given
     *        index is not valid. 
     */
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);

    /**
     * Gets the index of the item at the bottom of this view.
     *
     * @return Index of the item at the bottom of this view.
     */
	IMPORT_C TInt BottomItemIndex() const;

    /**
     * Recalculates the index of the bottom item in the list by using the top 
     * item index and the size of the display.
     *
     * This function is called by the owning list box control when either the 
     * size of the list box or the number of items in its model changes.
     */
	IMPORT_C virtual void CalcBottomItemIndex();

    /**
     * Sets the item height.
     *
     * @param aItemHeight New item height.
     */
	IMPORT_C virtual void SetItemHeight(TInt aItemHeight);

	// functions that support incremental matching 
    /**
     * Sets the match cursor’s colour.
     *
     * @deprecated
     * @param aColor Colour in which to display the incremental match cursor.
     */
	IMPORT_C void SetMatcherCursorColor(TRgb aColor);

    /**
     * Sets the match cursor's position.
     *
     * @deprecated
     * @param aPosWithinCurrentItem Character position for the match cursor 
     *        within the current item’s string.
     */
	IMPORT_C void SetMatcherCursorPos(TInt aPosWithinCurrentItem);

    /**
     * Gets the match cursor’s position.
     *
     * @deprecated
     * @return Character position of the match cursor within the current
     *         item’s string.
     */
	IMPORT_C TInt MatcherCursorPos() const;

    /**
     * Draws the match cursor in its current screen position if the matcher 
     * cursor flag has been set.
     * 
     * This is deprecated and broken and should not be used.
     *
     * @deprecated
     */
	IMPORT_C virtual void DrawMatcherCursor();

    /**
     * Hides the matcher cursor.
     *
     * @deprecated
     */
	IMPORT_C void HideMatcherCursor();

    /**
     * Sets whether the matcher cursor flag to specify whether the match 
     * cursor is drawn.
     *
     * @deprecated
     * @param aMatcherCursor If @c ETrue, the view will draw match cursor. 
     */
	IMPORT_C void SetMatcherCursor(TBool aMatcherCursor);

    /**
     * Sets whether or not items are drawn as emphasised. 
     *
     * The function sets or resets the emphasised flag.
     *
     * @param aEmphasized If @c ETrue, this view will draw items emphasised. 
     *        If @c EFalse will not draw items emphasised.
     */
	IMPORT_C void SetEmphasized(TBool aEmphasized);

    /**
     * Sets whether items will be drawn dimmed. 
     *
     * The function sets or resets the dim flag.
     *
     * @param aDimmed If @c ETrue, this view will draw items dimmed. 
     *        If @c EFalse this view will not draw items dimmed.
     */
	IMPORT_C void SetDimmed(TBool aDimmed);

    /**
     * Disables or enables redraws.
     *
     * If this flag is set to @c ETrue, all member functions which draw items 
     * will return immediately without drawing anything. Functions which update
     * the internal state of the list box will still work, but nothing will be 
     * drawn or updated on the screen.
     *
     * @param aDisableRedraw Disables redraw if @c ETrue.
     */
	IMPORT_C void SetDisableRedraw(TBool aDisableRedraw);

    /**
     * Tests whether redraw is disabled.
     *
     * @return ETrue if redraw is disabled.
     */
	IMPORT_C TBool RedrawDisabled() const;

    /**
     * Sets the painted selection flag.
     *
     * @deprecated
     * @param aPaintedSelection If @c ETrue the painted selection flag is set 
     *        on. If @c EFalse the selection flag is set off. If NULL the 
     *        painted selection flag is cleared.
     */
	IMPORT_C void SetPaintedSelection( TBool aPaintedSelection );

	// functions that support selection
    /**
     * Gets a pointer to the selection list of this view.
     * 
     * @return Pointer to an array describing the items 
     *         in the list which are currently selected. The object pointed 
     *         at is owned by the @c CListBoxView.
     */
    IMPORT_C const CSelectionIndexArray* SelectionIndexes() const;

    /**
     * Gets a copy of the array of currently selected items. 
     * 
     * @param[in,out] aSelectionArray An instantiated @c CSelectionIndexArray.
     *                On return, contains a copy of selection indexes. 
     * @panic EEikPanicListBoxInvalidSelIndexArraySpecified Panics if the given
     *        selection index array is not valid.
     * @panic EEikPanicListBoxNoSelIndexArray Panics if selection indexes have 
     *        not been defined for this class. 
     */
	IMPORT_C void GetSelectionIndexesL(
                                CSelectionIndexArray* aSelectionArray) const;
	
    /**
     * Sets the currently selected items of this view from a selection index 
     * array.
     * 
     * @param aSelectionIndexes Items to select.
     * @panic EEikPanicListBoxInvalidSelIndexArraySpecified Panics if the given
     *        selection index array is not valid.
     */
    IMPORT_C void SetSelectionIndexesL(const CSelectionIndexArray* 
                                       aSelectionIndexes);
	
    /**
     * Resets the selection state so that there is nothing selected.
     *
     * @panic EEikPanicListBoxNoSelIndexArray Panics if selection indexes have 
     *        not been defined for this class. 
     */
    IMPORT_C void ClearSelection(); 		
	
    // select/highlight items without moving the cursor
    /**
     * Updates item selection.
     *
     * @param aSelectionMode The selection mode. 
     */
    IMPORT_C virtual void UpdateSelectionL(TSelectionMode aSelectionMode);  
    	
    /**
     * Toggles the selection of an item.
     *
     * @param aItemIndex Item to toggle.
     * @panic EEikPanicListBoxNoSelIndexArray Panics if selection indexes have 
     *        not been defined for this class. 
     */
    IMPORT_C void ToggleItemL(TInt aItemIndex);
	
    /**
     * Selects an item by index. 
     *
     * This function leaves if memory could not be allocated for an extra item
     * in the array of selected items.
     *
     * @param aItemIndex Item to select.
     * @panic EEikPanicListBoxNoSelIndexArray Panics if selection indexes have 
     *        not been defined for this class. 
     */
    IMPORT_C void SelectItemL(TInt aItemIndex);
	
    /**
     * Deselects an item by index.
     *
     * @param aItemIndex Item to deselect.
     * @panic EEikPanicListBoxNoSelIndexArray Panics if selection indexes have 
     *        not been defined for this class. 
     */
    IMPORT_C void DeselectItem(TInt aItemIndex);
	
    /**
     * Sets the anchor to the specified item.
     *
     * @param aItemIndex The index of the item at which the anchor is set.
     */
    IMPORT_C void SetAnchor(TInt aItemIndex);
	
    /**
     * Resets the anchor index, the active end and the  @c EAnchorExists flag.
     */
    IMPORT_C void ClearSelectionAnchorAndActiveIndex();

	// functions that support scrolling
    /**
     * Scrolls vertically to make a particular item visible. 
     * 
     * @param aItemIndex The item to make visible.
     * @return @c ETrue if any scrolling was done, @c EFalse if no 
     *         scrolling was necessary.
     */
	IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);
    
    /**
     * Sets the index of the item to be the top item.
     *
     * @param aNewTopItemIndex The item to scroll to.
     */
	IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex);

    /**
     * Sets the index of the item to be the top item.
     *
     * This two argument version returns the area which needs redrawing via 
     * @c aMinRedrawRect&. This function does not perform the redraw.
     *
     * @param aNewTopItemIndex The distance by which to scroll. 
     * @param aMinRedrawRect On return, the minimum rectangle to redraw.
     */
    IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex, 
                                    TRect& aMinRedrawRect);
	
    /**
     * Scrolls horizontally by the specified number of pixels.
     *
     * @param aHScrollAmount The distance to scroll by in pixels. A negative 
     *        value scrolls to the left, a positive value scrolls to the right.
     */
    IMPORT_C virtual void HScroll(TInt aHScrollAmount);
	
    /**
     * Gets the offset of the visible portion of the data from the left margin
     * in pixels.
     *
     * @return The horizontal scroll offset in pixels.
     */
    IMPORT_C TInt HScrollOffset() const;

    /**
     * Sets the horizontal scroll offset in pixels.
     *
     * @param aHorizontalOffset New value for the horizontal scroll offset, in 
     *        pixels.
     */
	IMPORT_C void SetHScrollOffset(TInt aHorizontalOffset);

    /**
     * Gets the width of the widest item in the list in pixels.
     *
     * @return Data width in pixels.
     */
	IMPORT_C TInt DataWidth() const;

    /**
     * Recalculates the data width of this list box view from the item width 
     * of its list item drawer. This method is called directly by 
     * @c CEikListBox when the list box’s size changes or when data is added.
     */
	IMPORT_C virtual void CalcDataWidth();

    /**
     * Gets the visible width of the specified rectangle in pixels. This 
     * function is called by @c CListBoxView itself on its own viewing 
     * rectangle.
     *
     * @param aRect The rectangle to get the visible width for.
     * @return Visible width of @c aRect.
     */
	IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;

    /**
     * Calculates which item should be selected in order to make a 
     * particular item visible. Calling 
     * @c VScrollTo(CalcNewTopItemIndexSoItemIsVisible(idx)), for example, 
     * would make the item whose index is @c idx visible.
     *
     * @param aItemIndex The index of the new top item.
     * @return The item to be selected. 
     */
    IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(
                                                        TInt aItemIndex) const;

	// functions that support drawing
    /**
     * Draws every visible item into the specified rectangle. 
     *
     * As implemented in @c CListBoxView, this function's argument is ignored 
     * and the internal viewing rectangle is used. See @c SetViewRect().
     *
     * @param aClipRect The rectangle to draw into, this is ignored. Default 
     *        value is NULL.
     * @panic EEikPanicListBoxNoModel Panics if the list box model for this 
     *        class has not been defined. 
     */
	IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;

    /**
     * Draws the specified item via @c CListBoxDrawer::DrawItem() if it is 
     * visible.
     *
     * @param aItemIndex Index number of the item to draw.
     */
	IMPORT_C virtual void DrawItem(TInt aItemIndex) const;

    /**
     * Sets list box backroung text. This text is visible if the list box 
     * has no items.
     *
     * @param aText The text for the empty list box background.
     */
	IMPORT_C void SetListEmptyTextL(const TDesC& aText);

    /**
     * Gets an empty list box text. 
     * 
     * @return Pointer the empty list box text. 
     */
	inline const TDesC* EmptyListText() const;

    /**
     * Tests whether an item is selected.
     *
     * @param aItemIndex Index of item to test.
     * @return @c ETrue if the item is selected.
     */    
    IMPORT_C TBool ItemIsSelected(TInt aItemIndex) const; 

    /**
     * Tests whether an item is visible.
     *
     * @param aItemIndex Index of item to be tested.
     * @return @c ETrue if the item is visible.
     */
	IMPORT_C TBool ItemIsVisible(TInt aItemIndex) const;

    /**
     * Gets the on-screen position of an item.
     * 
     * @param aItemIndex Index of an item.
     * @return Position of the item.
     */
	IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;

    /**
     * Gets the on-screen size of an item. 
     * 
     * As implemented in @c CListBoxView, all items report the same size. 
     * The size returned may be larger than the width of the list box view, but
     * will not be smaller.
     *
     * @param aItemIndex Index of an item. Default value is 0.
     * @return Size of the item.
     */
	IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;

    /**
     * Sets the colour in which to display text.
     *
     * @param aColor Colour in which to display text.
     */
	IMPORT_C void SetTextColor(TRgb aColor);

    /**
     * Sets the background colour.
     *
     * @param aColor The background colour.
     */
	IMPORT_C void SetBackColor(TRgb aColor);
	
    /**
     * Gets the colour in which text is to be displayed.
     *
     * @return Current text colour.
     */
    IMPORT_C TRgb TextColor() const;

    /**
     * Gets the background colour for this view.
     * 
     * @return The background colour.
     */
	IMPORT_C TRgb BackColor() const;

    /**
     * Moves the current item cursor in the specified direction. This function 
     * is called by @c CEikListBox in response to user input.
     *
     * @param aCursorMovement The cursor movement to apply. 
     * @param aSelectionMode The selection mode of the calling list box.
     */
	IMPORT_C virtual void MoveCursorL(TCursorMovement aCursorMovement, 
                                      TSelectionMode aSelectionMode);
	
    /**
     * Moves to the specified item, sets it as the current item and scrolls the
     * display to make the item visible.
     *
     * @param aTargetItemIndex The index of the item to which to move.
     * @param aSelectionMode The selection mode. 
     */
    IMPORT_C virtual void VerticalMoveToItemL(TInt aTargetItemIndex, 
                                              TSelectionMode aSelectionMode);
	
    /**
     * Converts a pixel position into an item index.
     *
     * The function returns @c ETrue and sets @c aItemIndex to the index of the
     * item whose bounding box contains @c aPosition. Returns @c EFalse if no 
     * such item exists.
     *
     * @param aPosition A position relative to the origin of the list box 
     *                  control.
     * @param aItemIndex Is set to the item at that position. 
     * @return @c ETrue if there was an item at @c aPosition.
     */
    IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, 
                                            TInt& aItemIndex) const;   
    
    /**
     * Gets the number of items that will fit into a given rectangle.
     *
     * @param aRect The rectangle.
     * @return The number of items that will fit into the given rectangle.
     */
    IMPORT_C virtual TInt NumberOfItemsThatFitInRect(const TRect& aRect) const;

    /**
     * Sets the visibility observer.
     *
     * @param aObserver New visibility observer for this control.
     */
    void SetVisibilityObserver(MListVisibilityObserver* aObserver);

    /**
     * Tests if this view is visible.
     *
     * @return @c ETrue if this view is visible. @c EFalse if this view 
     *         is not visible or does not exist.
     */
	IMPORT_C TBool IsVisible() const;

    /**
     * Gets the object used by this list box view to draw its items.
     *
     * @return Pointer to the list box item drawer. 
     */
	inline CListItemDrawer* ItemDrawer() const;

    /**
     * Not implemented.
     * 
     * @param aClientRect Not used.
     */
	IMPORT_C virtual void DrawEmptyList(const TRect &aClientRect) const;

    // disables vertical line drawing, useful only for certain 
    //custom list boxes
    /**
     * Disables vertical line drawing.
     *
     * @param aDisable @c ETrue if disabled.
     */
    void DisableVerticalLineDrawing( TBool aDisable );

    /** 
    * Deselects range between given indexes.
    *
    * @deprecated
    * @param aItemIndex1 First index of selectable range.
    * @param aItemIndex2 Second index of selectable range.
    */
    IMPORT_C void DeselectRangeL(TInt aItemIndex1, TInt aItemIndex2);

    /**
     * Sets the offset for view.
     *
     * @internal
     * @param aOffset Offset in pixels.
     */
    IMPORT_C void SetItemOffsetInPixels(TInt aOffset);
    
    /**
     * Gets view offset.
     *
     * @internal
     * @return View's offset.
     */
    IMPORT_C TInt ItemOffsetInPixels() const;
    
    /**
     * Sets scrolling state.
	 *
	 * @internal
     */
    void SetScrolling( TBool aIsScrolling );
	 
	/**
	 * Returns item's height. All items have the same height.
	 *
	 * @internal
	 * @return Item height.
	 */ 
    TInt ItemHeight() const { return iItemHeight; }
    
    /**
     * Tests whether an item is partially visible.
     * Note that this returns @c EFalse also when item is fully visible,
     * i.e. the whole item area is inside the list view rectangle.
     *
     * @param  aItemIndex  Index of item to be tested.
     *
     * @return @c ETrue if the item is partially visible,
     *         @c EFalse if it's not visible or fully visible.
     */
    IMPORT_C TBool ItemIsPartiallyVisible( TInt aItemIndex ) const;

protected:

	// functions for accessing the flags
    /**
     * Gets this view’s flags.
     *
     * These flags are defined by the nested enum @c TFlags (below).
     *
     * @return List box's flags. 
     */
	inline TInt Flags() const;

    /**
     * Sets this view’s flags according to a bitmask.
     *
     * These flags are defined by the nested enum @c TFlags (below).
     *
     * @param aMask Sets new flags for the list box.
     */
	inline void SetFlags(TInt aMask);

    /**
     * Clears this view’s flags according to a bitmask.
     *
     * These flags are defined by the nested enum @c TFlags (below).
     *
     * @param aMask Flags to be removed. 
     */
	inline void ClearFlags(TInt aMask);

    /**
     * List box base class.
     * To access @c SetFlags()/ClearFlags().
     */
    friend class CEikListBox; 

	// misc. functions
    /**
     * Selects items between given indexes.
     * 
     * @deprecated
     * @param aItemIndex1 First index of selectable range.
     * @param aItemIndex2 Second index of selectable range.
     */
	IMPORT_C void SelectRangeL(TInt aItemIndex1, TInt aItemIndex2);

private:
    /**
     * Set item index directly. 
     * For CEikListBox.
     * @param aItemIndex New item index.
     */
    void SetItemIndex( TInt aItemIndex );
 
protected:

    /**
     * The flags for this list box. These flags are defined by the nested enum
     * @c TFlags (below).
     */
	TInt iFlags;   	

    /**
     * This view’s item drawer.
     * Not owned.
     */
	CListItemDrawer* iItemDrawer;

    /**
     * This view’s model.
     * Not owned.
     */
	MListBoxModel* iModel;

    /**
     * Width (in pixels) of the longest item in the model.
     */
	TInt iDataWidth;			
    
    /**
     * Index of the item at the top of the view. This is not necessarily the 
     * item at the start of the list.
     */
    TInt iTopItemIndex;
	
    /**
     * Index of the item at the bottom of the view. This is not necessarily the
     * item at the end of the list.
     */
    TInt iBottomItemIndex;
	
    /**
     * Pixel offset of the visible portion of the data from the left margin.
     */
    TInt iHScrollOffset; 
	
    /**
     * Index of the current item.
     */
    TInt iCurrentItemIndex;
	
    /**
     * Height of each item in the list in pixels.
     */
    TInt iItemHeight;
	
    /**
     * This list box view’s window.
     */
    RWindow* iWin;
	
    /**
     * The window group of this view.
     */
    RWindowGroup* iGroupWin;
	
    /**
     * Graphics context for the control.
     */
    CWindowGc* iGc;
	
    /**
     * Graphics context for the control.
     */
    TRect iViewRect;

    /**
     * The empty list text.
     */
	HBufC *iListEmptyText;
    
    /**
     * Indicates whether vertical line drawing is disabled.
     */
    TBool iDisableVerticalLineDrawing /*TInt iSpare*/;

private:
	TInt iMatcherCursorPos;
	TRgb iMatcherCursorColor; 
	TRgb iBackColor;
	TRgb iTextColor;
	TInt iAnchorIndex;  
	TInt iActiveEndIndex;
	CSelectionIndexArray* iSelectionIndexes;
	MListVisibilityObserver* iVisibilityObserver;
protected:
    /**
     * Current vertical offset of the view in pixels.
     */
    TInt iVerticalOffset;

	CListBoxViewExtension* iExtension;
    TInt iSpare[4];
	};

NONSHARABLE_CLASS( CListBoxViewExtension ) : public CBase
    {
    public:
        static CListBoxViewExtension* NewL();
        
        ~CListBoxViewExtension();
        
    private:
        void ConstructL();
        
    public:
	CEikListBox* iListBox;
	TBool iScrolling;
	TBool iScrollingDisabled;
    };


/**
 * Return text currently in the empty list text
 */
inline const TDesC* CListBoxView::EmptyListText() const
	{ return(iListEmptyText); }


class CSnakingListBoxView : public CListBoxView
	{
public:
	IMPORT_C ~CSnakingListBoxView();
	IMPORT_C CSnakingListBoxView();
	inline TInt ColumnWidth() const;
	IMPORT_C void SetColumnWidth(TInt aColumnWidth);
	IMPORT_C virtual void MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);
	IMPORT_C virtual void SetItemHeight(TInt aItemHeight);
	IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const;
	IMPORT_C virtual TInt NumberOfItemsThatFitInRect(const TRect& aRect) const;
	IMPORT_C virtual void HScroll(TInt aHScrollAmount);
	IMPORT_C virtual void CalcDataWidth();
	IMPORT_C virtual void CalcBottomItemIndex();
	IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;
	IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;
	IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);
	IMPORT_C virtual TInt CalculateHScrollOffsetSoItemIsVisible(TInt aItemIndex);
	IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const;
	IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;
	IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;
	IMPORT_C void CalcRowAndColIndexesFromItemIndex(TInt aItemIndex, TInt& aRowIndex, TInt& aColIndex) const;
	IMPORT_C void CalcItemIndexFromRowAndColIndexes(TInt& aItemIndex, TInt aRowIndex, TInt aColIndex) const;
	IMPORT_C virtual TInt NumberOfItemsPerColumn() const;
protected:
	IMPORT_C virtual void DrawItemRange(TInt aStartItemIndex, TInt aEndItemIndex) const;
	IMPORT_C void DrawColumnRange(TInt aStartColIndex, TInt aEndColIndex) const;
	IMPORT_C void MoveToPreviousColumnL(TSelectionMode aSelectionMode);
	IMPORT_C void MoveToNextColumnL(TSelectionMode aSelectionMode);
	IMPORT_C void ClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const;
	IMPORT_C void UpdateHScrollOffsetBasedOnTopItemIndex();
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
protected:
	TInt iColumnWidth;
	};



inline TInt CListBoxView::Flags() const
	{ return iFlags; }

inline void CListBoxView::SetFlags(TInt aMask)
	{ iFlags|=aMask; }
 
inline void CListBoxView::ClearFlags(TInt aMask)
	{ iFlags&=(~aMask); }

inline CListItemDrawer* CListBoxView::ItemDrawer() const
	{ return iItemDrawer; }

inline TInt CSnakingListBoxView::ColumnWidth() const
	{ return iColumnWidth; }


#endif  // __EIKLBV_H__
