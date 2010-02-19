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
* Description:  Base class for an on-screen list box control from
*               which one or more items can be selected.
*
*/
   
#ifndef __EIKLBX_H__
#define __EIKLBX_H__

//  INCLUDES 
#include <gdi.h>
#include <eikbctrl.h>
#include <eiklbo.h>
#include <eiksbfrm.h>
#include <eiklbm.h>
#include <eiklbv.h>
#include <gulbordr.h>
#include <eiklbed.h>
#include <gulutil.h>
#include <lafpublc.h>

//  FORWARD DECLARATIONS
enum TKeyCode;
class RIncrMatcherBase;
class CListItemDrawer;
class CEikScrollBarFrame;
class CEikButtonBase;
class CMatchBuffer;
class CListBoxExt;
class CEikListBox;

//  CLASS DECLARATION

/**
* Item change observer will be notified when list box items have been added or
* removed or the list box has been reset. Observers can be added and removed by
* using @c CEikListBox methods @c AddItemChangeObserverL() and
* @c RemoveItemChangeObserver().
*
* @since 3.0
*/
class MListBoxItemChangeObserver
    {
    public:
        /**
         * Notification and handling of a list box item change.
         *
         * @param aListBox The source list box of this message.
         */
        virtual void ListBoxItemsChanged(CEikListBox* aListBox) = 0;
    };


/**
* Item selection (marking) observer is used to let application control item marking
* (in markable lists). Observers can be added and removed by using
* @c CEikListBox methods @c AddSelectionObserverL() and
* @c RemoveSelectionObserver().
*
* @since 3.2
*/
class MListBoxSelectionObserver
    {
    public:
        /**
         * Notification of entering and leaving marking mode. Marking mode
         * is enabled by long pressing shift, ctrl or hash keys (when hash key marking is enabled).
         *
         * @param aListBox The source list box of this message.
         * @param aSelectionModeEnabled ETrue, when entering selection (marking) mode.
         */
        virtual void SelectionModeChanged(CEikListBox* aListBox, TBool aSelectionModeEnabled) = 0;
    };


// CLASS DECLARATION
    
/**
 * Base class for an on-screen list box control from which one or more items 
 * can be selected.
 *
 * @c CEikListBox implements the basics of a list box. It has a scroll bar 
 * frame, an item drawer, and a model, and reports events to a list box 
 * observer.
 * 
 * List boxes display a number of items within a scrolling frame; the items 
 * in a list box which are visible at one time are represented by a list 
 * box view. 
 * 
 * Writing derived classes: 
 * 
 * This class may be derived from to provide specialisations of the basic 
 * list box behaviour. It is usual when subclassing CEikListBox to also 
 * provide specialisations of CListItemDrawer and CListBoxView for 
 * representing the data of such a list box effectively
 */
class CEikListBox : public CEikBorderedControl, public MEikScrollBarObserver
    {

public:

    friend class CListBoxExt;

public:

    /**
    * Construction flags.
    */
    enum TFlags
        {
        
        /**
         * Construction flag for a list box from which the user can
         * select multiple items.
         */
        EMultipleSelection          = SLafListBox::EMultipleSelection,
        
        /**
         * Construction flag for disabling extended selection. 
         * If this is set the user cannot select multiple items by
         * using @c SHIFT button.
         */
        ENoExtendedSelection        = SLafListBox::ENoExtendedSelection,
        
        /**
         * Construction flag that sets the list box to match user?s keystrokes 
         * incrementally.
         */
        EIncrementalMatching        = SLafListBox::EIncrementalMatching,
        
        /**
         * Construction flag for setting the list box as a pop-out list box. 
         * Pop-out list boxes handle certain keystrokes and events differently.
         */
        EPopout                     = SLafListBox::EPopout,

        /**
         * Construction flag that enables the indication of pointer press 
         * inside the view of the list box.
         */
        ELeftDownInViewRect         = SLafListBox::ELeftDownInViewRect,
        
        /**
         * Construction flag for enabling @c CEiklist box item double click 
         * indication.
         */
        EItemDoubleClicked          = SLafListBox::EItemDoubleClicked,
                
        /**
         * Construction flag for removing the ownership of the supplied list box
         * model from the @c CEikListBox so that the list box model will not be 
         * deleted with the @c CEikListBoxes destruction.
         */
        EKeepModel                  = SLafListBox::EKeepModel,
        
        /**
         * Construction flag for excluding the scroll bar.
         * If the flag is set the scroll bas is drawn ouside the window that 
         * describes the scroll bars extent.
         */
        EScrollBarSizeExcluded      = SLafListBox::EScrollBarSizeExcluded,

        /**
         * Construction flag for enabling @c CEikListBox change indication.
         */
        EStateChanged               = SLafListBox::EStateChanged,

        /**
         * Construction flag that indicates that the list box should be created 
         * to its own window.
         */
        ECreateOwnWindow            = SLafListBox::ECreateOwnWindow,

        /**
         * Construction flag for disabling key matching.
         */
        ENoFirstLetterMatching      = SLafListBox::ENoFirstLetterMatching,

        /**
         * Construction flag for enabling painting of selected items.
         */
        EPaintedSelection           = SLafListBox::EPaintedSelection ,

        /**
         * Construction flag for enabling loop scrolling in which the list box 
         * jumps from the last item to the first item.
         */
        ELoopScrolling = 0x1000,

        /**
         * Construction flag for enabling @c Avkon multiselection list.
         */
        EEnterMarks = 0x2000,       // Avkon multiselection list

        /**
         * Construction flag for enabling Avkon markable list which enables the 
         * marking of several items from the list. 
         */
        EShiftEnterMarks = 0x4000,  // Avkon markable list

        /**
         * Construction flag that combines @c EPageAtOnceScrolling and 
         * @c EDisableHighlight flags
         */
        EViewerFlag = 0x8000,       // combined the two flags to fit to WORD.

        /**
         * Construction flag for enabling scrolling at a page per time so that 
         * the whole list box page is scrolled to the next. 
         */
        EPageAtOnceScrolling = 0x8000, // Avkon viewers

        /**
         * Construction flag for disabling the highlighting of the selected item.
         */
        EDisableHighlight = 0x8000,  // Avkon viewers       

        /**
         * Construction flag for enabling S60 style selection of multiple items 
         * from the list box.
         */
        ES60StyleMultiselection     = SLafListBox::ES60StyleMultiselection,   
        
        /**
         * Construction flag for enabling S60 style markable items.
         */
        ES60StyleMarkable           = SLafListBox::ES60StyleMarkable,

        /**
         * Construction flag for disabling item specific stylus popup menu.
         */
        EDisableItemSpecificMenu    = 0x00040000
        };
    enum {KEikMaxMatchingBufferLength = 2};

    /** 
     * Indicates who owns the scroll bar.
     */ 
    enum TScrollBarOwnerShip
        {
        /**
         * Indicates that the scrollbar is not owned by an external class.
         */
        ENotOwnedExternally=0x0000,
        /**
         * Indicates that the scrollbar is owned by an external class.
         */
        EOwnedExternally   =0x0001
        };

protected:

    /**
     * Used for indicating the reason why the item lost focus.
     */
    enum TReasonForFocusLost
        { 
        /**
         * Focus has been lost from the list box to an external control.
         */
        EFocusLostToExternalControl, 
        /**
         * Focus has been moved from the list box to an internal editor.
         */
        EFocusLostToInternalEditor 
        };

public:
    /**
     * Destructor.
     */
    IMPORT_C ~CEikListBox();

    /**
     * C++ default constructor.
     */
    IMPORT_C CEikListBox();
    /**
     * Handles 2nd phase construction.
     * 
     * Sets list box model and list item drawer. Request another @c ConstructL 
     * to handle @c aParent and @c aFlags. 
     *
     * @param aListBoxModel List box model that is to be used with the list box.
     * @param aListItemDrawer List item drawer that is to be used with the 
     *        list box.
     * @param aParent Host @c CoeControl for the list box.
     * @param aFlags Construction flags (@c TFlags) for the list box.
     */
    IMPORT_C void ConstructL(MListBoxModel* aListBoxModel,
                             CListItemDrawer* aListItemDrawer,
                             const CCoeControl* aParent,
                             TInt aFlags = 0);
    
    /**
     * Handles 2nd phase construction.
     *
     *
     * Sets the border that is to be drawn outside the list box. Request another 
     * @c ConstructL to handle list box model, list item drawer, @c aParent 
     * and @c aFlags. 
     *
     * @param aListBoxModel List box model that is to be used with the list box.
     * @param aListItemDrawer List item drawer that is to be used with the 
     *        list box.
     * @param aParent Host @c CoeControl for the list box.
     * @param aBorder Border to be drawn outside the list box.
     * @param aFlags Construction flags (@c TFlags) for the list box.
     */
    IMPORT_C void ConstructL(MListBoxModel* aListBoxModel,
                             CListItemDrawer* aListItemDrawer,
                             const CCoeControl* aParent, 
                             TGulBorder aBorder, 
                             TInt aFlags = 0);
    /**
     * Informs the @c CEikListbox of a key press.
     *
     * @param aKeyEvent Details of the key event that is being handled.
     * @param aType Defines what kind of key event is being handled e.g. 
     *        @c EEventKeyUp.
     * @return @c EKeyWasConsumed if the key was handled by the method.
     *         @c EKeyWasNotConsumed if the key was not handled.
     */
    IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                                 TEventCode aType);
    
    /**
     * Handling of pointer event within the @c CEikListBox. 
     * Used for e.g. selecting an item from the list box.
     *
     * @param aPointerEvent Details of the pointer event that is being handled.
     */
    IMPORT_C virtual void HandlePointerEventL(
                            const TPointerEvent& aPointerEvent);
    
    /**
     * Creates an own window for the list box or draws the list box to an old 
     * window defined by the @c aContainer.
     *
     * @param aContainer Defines the container where the list box will be drawn.
     */
    IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aContainer);
    
    /**
     * Checks the minimum size needed for the list box.
     *
     * @return The two dimensional minimum size for the list box.
     */
    IMPORT_C virtual TSize MinimumSize();
    
    /**
     * This function sets a flag within the control which indicates 
     * whether or not the control is dimmed (greyed out). 
     *
     * @param aDimmed @c ETrue dimmed. @c EFalse not dimmed.
     */
    IMPORT_C virtual void SetDimmed(TBool aDimmed);

    /**
     * Used for scrolling through the items in the list box. 
     *
     * @param aScrollBar Scroll bar for the list box.
     * @param aEventType Type of the event that occured.
     */
    IMPORT_C virtual void HandleScrollEventL(CEikScrollBar* aScrollBar, 
                                             TEikScrollEvent aEventType);

    // model/view access functions 
    /**
     * Gets the list box data model.
     *
     * @return Interface to the list box data model.
     */
    IMPORT_C MListBoxModel* Model() const;

    /**
     * Gets the list box view.
     *
     * @return Interface to the list box view.
     */
    IMPORT_C CListBoxView* View() const;

    // functions for accessing top/current/bottom item index
    /**
     * Gets the index number of the top item.
     *
     * @return Index number for the top item.
     */
    IMPORT_C TInt TopItemIndex() const;
    
    /**
     * Sets the selected item to be the top item.
     *
     * @param aItemIndex Index for the item to be set as the top item.
     */
    IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex) const;
    
    /**
     * Gets for the bottom items index.
     *
     * @return Index for the bottom item.
     */
    IMPORT_C TInt BottomItemIndex() const;
    
    /**
     * Gets the index number of the selected item.
     *
     * @return Index of the selected item.
     */
    IMPORT_C TInt CurrentItemIndex() const;   
    
    /**
     * Changes the current item index to the selected item index. Does not
     * redraw the list. If the item was not previously visible it is set to the 
     * top item in the view.
     *
     * @param aItemIndex Defines the index of the selected item.
     */
    IMPORT_C void SetCurrentItemIndex(TInt aItemIndex) const;
    
    /**
     * Changes the current item index to the selected item index and 
     * redraws the view.
     *
     * @param aItemIndex Defines the index of the selected item.
     */
    IMPORT_C void SetCurrentItemIndexAndDraw(TInt aItemIndex) const;

    // functions for dealing with the selection state
    /**
     * Gets for list boxes selection indexes.
     *
     * @return Pointer to the list boxes in array of selection indexes.
     */
    IMPORT_C const CListBoxView::CSelectionIndexArray* SelectionIndexes() const;
    
    /**
     * Assigns a array of selection indexes for the list box.
     *
     * @param aArrayOfSelectionIndexes The index array that is to be assigned 
     *        to the list Box.
     */
    IMPORT_C void SetSelectionIndexesL(
                CListBoxView::CSelectionIndexArray* aArrayOfSelectionIndexes);
    
    /**
     * Clears the selection from the view.
     */
    IMPORT_C void ClearSelection(); 

    // Functions for updating a list box's internal state after its model has
    // been updated, all of them will emit item change event to item change
    // observers.
    /**
     * Handles the addition of item to the list box.
     */
    IMPORT_C void HandleItemAdditionL();
    
    /**
     * Handles the removal of an item from the list box.
     */
    IMPORT_C void HandleItemRemovalL();

    /**
     * Handles the addition of new items to the list box and updates 
     * selection indexes array.
     *
     * NOTE. This algorithm can not handle position of the list highlight
     * nor can it update the top item index correctly.
     *
     * @param aArrayOfNewIndexesAfterAddition Array of new indexes to be added.
     */
    IMPORT_C void HandleItemAdditionL(
                    CArrayFix<TInt> &aArrayOfNewIndexesAfterAddition);
    
    /**
     * Handles the removal of items to the list box and updates 
     * selection indexes array.
     *
     * NOTE. This algorithm cannot handle position of the list highlight
     * nor can it update the top item index correctly.
     *
     * @param aArrayOfOldIndexesBeforeRemoval Array of indexes to be removed.
     */
    IMPORT_C void HandleItemRemovalL(
                    CArrayFix<TInt> &aArrayOfOldIndexesBeforeRemoval);
    
    /**
     * Deletes the item editor
     */
    IMPORT_C void Reset();

    /**
    * Adds an item change observer to the listbox. Duplicates are not checked
    * (i.e. adding the same observer multiple times is not prevented).
    *
    * @since 3.0
    * @param aObserver Must be non-NULL.
    */
    IMPORT_C void AddItemChangeObserverL( MListBoxItemChangeObserver* aObserver );
    /**
    * Removes an item change observer from the listbox.
    *
    * @since 3.0
    * @param aObserver The observer to be removed.
    * @return ETrue if removal ok, EFalse if observer was not removed (not
    *         found from the list of observers).
    */
    IMPORT_C TBool RemoveItemChangeObserver( MListBoxItemChangeObserver* aObserver );

    // functions for accessing the item height
    /**
     * Sets the height of the item to the selected value.
     * 
     * @param aHeight New height for the item.
     */
    IMPORT_C virtual void SetItemHeightL(TInt aHeight);
    
    /**
     * Gets height of the item.
     *
     * @return Height of the item.
     */
    IMPORT_C TInt ItemHeight() const;

    // functions for scrollbars
    /**
     * Creates a scrollbar frame.
     *
     * @param  aPreAlloc Boolean defining if there should be initial 
     *         memory allocations.
     * @return The new scroll bar frame.
     */
    IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL(TBool aPreAlloc=EFalse);

    /**
     * Sets the given scroll bar frame for the list box with the given 
     * ownership leve.
     *
     * @param aScrollBarFrame The new frame that is going to be used.
     * @param aOwnerShip Ownership level of the scroll bar frame.
     */
    IMPORT_C void SetScrollBarFrame(CEikScrollBarFrame* aScrollBarFrame, TScrollBarOwnerShip aOwnerShip);

    /**
     * Gets pointer for the scroll bar frame.
     *
     * @return Pointer to the scroll bar frame.
     */
    IMPORT_C CEikScrollBarFrame* const ScrollBarFrame();

    /**
     * Updates all scroll bars.
     */
    IMPORT_C virtual void UpdateScrollBarsL();

    // construction support functions
    /**
     * Gets the size of the rectangle required to display a pop out.
     * 
     * @param aTargetItemIndex The item from which the popout originates.
     * @param aTargetYPos Vertical position of the item from which the popout 
     *        originates.
     * @param aListBoxRect The list box rectangle.
     * @param aMinHeightInNumOfItems The minimum number of items for the popout.
     */
    IMPORT_C void CalculatePopoutRect( TInt aTargetItemIndex,
                                       TInt aTargetYPos,
                                       TRect& aListBoxRect,
                                       TInt aMinHeightInNumOfItems = 1 );
    /**
     * Gets the size of the list box in pixels based on the height of 
     * the list box in items and the length of the items in characters.
     *
     * Returns @c TSize element consisting of two elements, the height 
     * and the width. Height is the number of items times the height 
     * of the font in pixels. Width is the number of characters in a 
     * single line times the width of the font in pixels. 
     *
     * @param aWidthAsNumOfChars Width of list box in characters.
     * @param aHeightAsNumOfItems Height of list box in characters.
     * @return The size of the list box in pixels as TSize.
     */
    IMPORT_C TSize CalcSizeInPixels(TInt aWidthAsNumOfChars, 
                                    TInt aHeightAsNumOfItems) const;

    /**
     * Gets the width of the list box in pixels based on the width of the list 
     * box in characters.
     *
     * Returns the number of characters times the width of a character 
     * in pixels. 
     *
     * @param aNumOfChars The number of characters.
     * @return The width of the list box in pixels.
     */
    IMPORT_C TInt CalcWidthBasedOnNumOfChars(TInt aNumOfChars) const;
    
    /**
     * Gets the height of the list box in pixels based on the width of the 
     * list box in characters.
     *
     * Returns the number of items times the height of the font in pixels.
     *
     * @param aNumOfItems The number of items.
     * @return The height of the list box in pixels.
     */
    IMPORT_C TInt CalcHeightBasedOnNumOfItems(TInt aNumOfItems) const;
    
    /**
     * Gets the width of the list box in pixels based on the width of the 
     * list box text in pixels.
     *
     * returns the width of the whole list box in pixels, which includes 
     * the text width and the width of elements in the list box that have
     * an effect on the overall width.
     *
     * @param aTextWidthInPixels Width of list box text in pixels.
     * @return Required width of whole list box in pixels.
     */
    IMPORT_C TInt CalcWidthBasedOnRequiredItemWidth(
                                TInt aTextWidthInPixels) const;

    // drawing/scrolling functions
    /**
     * Draws a list box item, first scrolling the list to make it visible 
     * if it is not already. 
     *
     * @c DrawItem() panics if there is no list box view currently set.
     * @param aItemIndex Index of the item to reveal.
     */
    IMPORT_C void DrawItem(TInt aItemIndex) const;

    /**
     * Makes an item visible in the list, scrolling it if necessary.
     *
     * @param aItemIndex Index of the item to reveal.
     */
    IMPORT_C void ScrollToMakeItemVisible(TInt aItemIndex) const;

    /**
    * Redraws list item.
    * @param aItemIndex index of item to be redrawn.
    * @since 3.2
    */
    IMPORT_C void RedrawItem( TInt aItemIndex );

    // observer support
    /**
     * Sets the observer for the list box.
     *
     * @param aObserver Wanted observer for the list box.
     */
    IMPORT_C void SetListBoxObserver(MEikListBoxObserver* aObserver);

    
    /**
     * Gets the size of the vertical gap between items. This space is used 
     * by the view to allow a box to be drawn around each item.
     *
     * @return Size of the vertical gap in pixels.
     */
    IMPORT_C TInt VerticalInterItemGap() const;

    // popouts only
    /**
     * Provides a call back mechanism to the button which just launched a 
     * popout menu.
     *
     * @param aButton The button which just launched a popout menu.
     */
    IMPORT_C void SetLaunchingButton(CEikButtonBase* aButton);

    // Editing support
    /**
     * Selects an item editor for the list box.
     *
     * @param aEditor The editor that has been selected for usage.
     */
    IMPORT_C void SetItemEditor(MEikListBoxEditor* aEditor);
    
    /**
     * Resets the list boxes item editor.
     */
    IMPORT_C void ResetItemEditor();
    /**
     * Gets item editor for the current class.
     *
     * @return The item editor used by the list box class.
     */
    IMPORT_C MEikListBoxEditor* ItemEditor();
    
    /**
     * Creates an item editor and starts editing the current item.
     *
     * The editor can edit the current item up to a maximum length of 
     * @c aMaxLength characters. Also reports an @c EEventEditingStarted event 
     * to any list box observer by default.
     *
     * The function only creates a new editor if one does not already exist.
     *
     * @param aMaxLength Maximum length of characters to edit.
     */
    IMPORT_C virtual void EditItemL(TInt aMaxLength);
    
    /**
     * Stops editing and deletes the item editor. 
     *
     * The function reports an @c EEventEditingStopped event to any list box 
     * observer, and updates the list box model if @c aUpdateModel is @c ETrue.
     *
     * @param aUpdateModel If @c ETrue the list box model is updated.
     */
    IMPORT_C void StopEditingL(TBool aUpdateModel);

    // functions needed for Avkon shortcuts, 
    // passing information from one list to another

    /**
     * No Implementation.
     *
     * @return Always returns 0.
     */
    IMPORT_C virtual TInt ShortcutValueForNextList();
    
    /**
     * No Implementation.
     *
     * @param aValue Not Used.
     */
    IMPORT_C virtual void SetShortcutValueFromPrevList(TInt aValue);

    // pop-up positioning support
    /**
     * Gets the position and the size of the list box.
     *
     * @return A rectangle with the correct position data as 
     *         well as size data for the list box.
     */
    IMPORT_C TRect HighlightRect() const;
    
    /**
     * Checks whether background drawing is suppressed on item level i.e. each
	 *  list item doesn't draw its background.
	 *
	 * @since S60 5.0
	 * @return ETrue if background drawing is suppressed.
     */
     IMPORT_C TBool BackgroundDrawingSuppressed() const;

public: // from CCoeControl

    /**
     * From @c CCoeControl
     *
     * Gets the list of logical colours employed in the drawing of the control, 
     * paired with an explanation of how they are used. Appends the list to 
     * @c aColorUseList.
     *
     * @param aColorUseList List of logical colours.
     */
    IMPORT_C virtual void GetColorUseListL(
                        CArrayFix<TCoeColorUse>& aColorUseList) const; 
                        // not available before Release 005u
    
    /**
     * From @c CCoeControl
     *
     * Handles a change to the list box?s resources of type @c aType which are 
     * shared across the environment, colours or fonts for example.
     *
     * @param aType The type of resources that have changed.
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);         
                // not available before Release 005u
    
    /**
     * From @c CCoeControl
     *
     * Sets the control as ready to be drawn.
     *
     * The application should call this function on all controls that are not 
     * components in a compound control.
     *
     * The purpose of this function is that controls are not always ready to 
     * be drawn as soon as they have been constructed. For example, it may 
     * not be possible to set the control's extent during construction, but 
     * its extent should always be set before it is drawn. Similarly, if a 
     * control is to be made  invisible, this should be done before it is 
     * activated.
     * 
     * The default implementation sets a flag in the control to indicate it is 
     * ready to be drawn. If the control is a compound control, the default 
     * implementation also calls @c ActivateL() for all the control's components. 
     * To get the control's components it uses @c CountComponentControls() and 
     * @c ComponentControl(), which should be implemented by the compound control.
     * 
     * @c ActivateL() is typically called from the control's @c ConstructL() 
     * function.
     *
     * Notes:
     *
     * This function can be overridden. This is useful for doing late 
     * initialisation of the control, using information that was not available 
     * at the time the control was created. For example, a text editor might 
     * override @c ActivateL() and use it to enquire whether it is focused: if 
     * it is, it makes the cursor and any highlighting visible. At the time when 
     * the editor is created, it doesn't know whether or not it has keyboard 
     * focus.
     *
     * If overriding @c ActivateL(), the implementation must include a base 
     * call to @c CCoeControl's @c ActivateL(). 
     */
    IMPORT_C virtual void ActivateL();
    
    /**
     * From @c CCoeControl.
     *
     * Gets the input capabilities of the control and all its components.
     *
     * @return The input capabilities of the control.
     */
    IMPORT_C TCoeInputCapabilities InputCapabilities() const;

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

protected:
    // Shortcuts need access to Incremental matching
    // The shortcuts will be used inside OfferkeyEventL().
    friend class AknListBoxShortCutsImplementation;
    // Avkon layout uses SetVerticalMargin, which is protected.
    friend class AknListBoxLayouts;

    /**
     * Responds to a change in focus.
     *
     * This is called whenever the control gains or loses focus, 
     * as a result of a call to @c SetFocus(). A typical use of 
     * @c FocusChanged() is to change the appearance of the control, 
     * for example by drawing a focus rectangle around it.
     *
     * The default implementation is empty, and should be 
     * overridden by the @c CCoeControl-derived class.
     *
     * @param aDrawNow Contains the value that was passed to it 
     *        by @c SetFocus().
     */
    IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
    
    /**
     * Responds to changes to the size and position of the contents 
     * of this control.
     * 
     * For a simple control this might include text or graphics. 
     * For a compound control it sets the size and position of the 
     * components. It has an empty default implementation and should 
     * be implemented by the CCoeControl-derived class.
     *
     * The function is called whenever @c SetExtent(), @c SetSize(), 
     * @c SetRect(), @c SetCornerAndSize(), or @c SetExtentToWholeScreen() 
     * are called on the control. Note that the window server does not 
     * generate size-changed events: @c SizeChanged() gets called only as 
     * a result of calling the functions listed above. Therefore, if a 
     * resize of one control affects the size of other controls, it is 
     * up to the application to ensure that it handles the re-sizing 
     * of all affected controls. 
     */
    IMPORT_C virtual void SizeChanged();

    /**
     * Handles the change in case that the size of the view rectangle
     * for the list box changes.
     */
    IMPORT_C virtual void HandleViewRectSizeChangeL();
    
    /**
     * Gets the number of controls contained in a compound control.
     *
     * There are two ways to implement a compound control. One way is to
     * override this function. The other way is to use the @c CCoeControlArray
     * functionality (see the @c InitComponentArrayL method).
     *
     * @return The number of component controls contained by this control.
     */
    IMPORT_C virtual TInt CountComponentControls() const;
    
    /**
     * Gets an indexed component of a compound control.
     *
     * There are two ways to implement a compound control. One way is to 
     * override this function. The other way is to use the @c CCoeControlArray 
     * functionality (see the @c InitComponentArrayL method).
     *
     * Note: Within a compound control each component control is identified 
     * by an index, where the index depends on the order the controls were 
     * added: the first is given an index of 0, the next an index of 1, and
     * so on.
     *
     * @param aIndex The index of the control. 
     * @return The component control with an index of aIndex. 
     */
    IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;

    // functions that implement first letter and incremental matching
    /**
     * Creates a buffer for checking how well two strings match up.
     */
    IMPORT_C void CreateMatchBufferL();  

    /**
     * Empties the match buffer .
     */
    IMPORT_C void ClearMatchBuffer() const;

    /**
     * Checks matching for the given character.
     *
     * @param aCode Character code.
     */
    IMPORT_C void MatchTypedCharL(TUint aCode);

    /**
     * Undoes changes from the match buffer that have been caused 
     * by the last match with a character.
     */
    IMPORT_C void UndoLastChar();
    /**
     * Checks if the last character matched with the string.
     *
     * @return @c ETrue if a match was found from the buffer with the character.
     */
    IMPORT_C TBool LastCharMatched() const;

    // functions needed for supporting scrollbars
    /**
     * Updates the position of this list box?s scroll bars? thumbs to reflect 
     * the horizontal and vertical position of the list view within the list.
     */
    IMPORT_C virtual void UpdateScrollBarThumbs() const;
    
    /**
     * Get horizontal scroll granularity in pixels.
     * The granularity is the minimum size of a horizontal move of the client 
     * area.
     *
     * @return Grain size for horizontal scrolling in pixels.
     */
    IMPORT_C virtual TInt HorizScrollGranularityInPixels() const;
    
    /**
     * Gets the number of grains to move horizontally when a nudge button is 
     * tapped. 
     * For simple list boxes, this value is a fraction of the width of the 
     * client area. 
     *
     * @return Number of grains to move left or right on each nudge
     */
    IMPORT_C virtual TInt HorizontalNudgeValue() const;
    
    /**
     * Called by various functions of this class to ensure that the top 
     * item index is always a sane value. The implementation in @c CEikListBox 
     * tries to ensure the minimum amount of white space at the bottom of 
     * the list box. Note that this function does not affect the 
     * current item index.
     */
    IMPORT_C virtual void AdjustTopItemIndex() const;

    // navigation support functions
    /**
     * Simulates an arrow key event. 
     * 
     * If the list box flags include @c EMultipleSelection, this has the effect 
     * of pressing @c SHIFT with the arrow key represented by @c aKeyCode. 
     * Calls @c CEikListBox::OfferKeyEventL() with aKeyCode translated into a 
     * key event.
     *
     * @param aKeyCode A key code.
     */
    IMPORT_C void SimulateArrowKeyEventL(TKeyCode aKeyCode);
    
    /**
     * Handles a left arrow key event.
     *
     * The method used to handle the event depends on the selection mode, e.g. 
     * whether the user has pressed the @c SHIFT or @c CONTROL key. 
     *
     * @param aSelectionMode Not used
     */
    IMPORT_C virtual void HandleLeftArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);
    
    /**
     * Handles a right arrow key event.
     *
     * The method used to handle the event depends on the selection mode, 
     * e.g. whether the user has pressed the @c SHIFT or @c CONTROL key. 
     *
     * @param aSelectionMode Not used.
     */
    IMPORT_C virtual void HandleRightArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);

    // construction support functions
    /**
     * Restores the list box properties shared by all subclasses from a resource
     * reader. This function is not called within @c CEikListBox itself, but is 
     * used by subclasses which support construction from resources.
     *
     * @param aReader A resource reader.
     */
    IMPORT_C void RestoreCommonListBoxPropertiesL(TResourceReader& aReader); 

    /**
     * Second-phase constructor.
     *
     * This protected form is overridden non-virtually by the second-phase 
     * constructors of each subclass, and should be invoked by them using 
     * @c CEikListBox::ConstructL().
     *
     * @param aParent The parent control. May be NULL. 
     * @param aFlags Construction flags. 
     */
    IMPORT_C virtual void ConstructL(const CCoeControl* aParent, TInt aFlags = 0);
    
    /**
     * Completes the list box view?s construction.
     *
     * This function is called by @c ConstructL() to complete construction 
     * of the resource view, calling its @c ConstructL() with appropriate 
     * arguments and assigning it to @c iView. Also prepares the view for use.
     */
    IMPORT_C virtual void CreateViewL();
    
    /**
     * Creates the list box view.
     *
     * The function is called by @c ConstructL() to create an instance of 
     * the appropriate list box view class for this list box. The returned 
     * instance is owned by this object, and does not have to have its 
     * second-phase constructor run. This function is called by @c CreateViewL().
     *
     * @return Pointer to a newly constructed list box view for this object.
     */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
    
    /**
     * Sets the view rectangle from the client rectangle making sure a whole 
     * number of items is displayed.
     * 
     * @param aClientRect  The client rectangle
     */
    IMPORT_C void SetViewRectFromClientRect(const TRect& aClientRect);
    
    /**
     * Calculates the client area.
     *
     * This method is called by various functions of this class to 
     * recalculate the extent of the client area from @c iViewRect. This
     * implementation takes into account any rounding of the viewing 
     * rectangle made to fit a whole number of items.
     *
     * @param aClientRect On return contains a size for the client area 
     *        in pixels.
     */
    IMPORT_C virtual void RestoreClientRectFromViewRect( TRect& aClientRect) const;

    /**
     * Rounds down the height of the rectangle (if necessary) so that 
     * only a whole number of items can be displayed inside the list box.
     *
     * @param aRect The rectangle to be modified. 
     * @return The number of pixels reduced. 
     */
    IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems( TRect& aRect) const;

    // accessor for Laf members
    /**
     * Gets list box margins.
     *
     * @return The list box margins in pixels.
     */
    IMPORT_C TMargins8 ListBoxMargins() const;

    // various accessors for private data members
    /**
     * This function gets the horizontal margin. Use 
     * @c CEikListBox::ListBoxMargins() instead, as this 
     * provides a more accurate value due to the bit shifting involved.
     *
     * @deprecated Use @c CEikListBox::ListBoxMargins()
     * @return The horizontal margin in pixels.
     */
    IMPORT_C TInt HorizontalMargin() const;
    
    /**
     * This function gets the vertical margin. This function 
     * is deprecated, use @c CEikListBox::ListBoxMargins() instead, 
     * this provides a more accurate value due to the bit 
     * shifting involved.
     *
     * @deprecated Use @c CEikListBox::ListBoxMargins()
     * @return The vertical margin in pixels.
     */
    IMPORT_C TInt VerticalMargin() const;
    
    /**
     * Sets the horizontal margin.
     *
     * @param aMargin The required horizontal margin.
     */
    IMPORT_C void SetHorizontalMargin(TInt aMargin);
    
    /**
     * Sets the vertical margin.
     *
     * @param aMargin The required vertical margin.
     */
    IMPORT_C void SetVerticalMargin(TInt aMargin);
    
    /**
     * Gets a pointer to the match buffer. Returns 
     * NULL if the match buffer does not exist.
     *
     * @return Pointer to the match buffer.
     */
    IMPORT_C RIncrMatcherBase* MatchBuffer() const;
    
    /**
     * Gets the view rectangle height adjustment. 
     *
     * These are the adjustments that were made to the 
     * view rectangle when the @c SetViewRectFromClientRect() 
     * function was called.
     *
     * @return Height adjustment.
     */
    IMPORT_C TInt ViewRectHeightAdjustment() const;
    
    /**
     * Gets the background colour.
     *
     * @return The background colour.
     */
    IMPORT_C TRgb BackColor() const;
    
    /**
     * Sets the view rectangle height adjustment. 
     *
     * @param aAdjustment New adjustment.
     */
    IMPORT_C void SetViewRectHeightAdjustment(TInt aAdjustment);

    // misc functions
    
    /**
     * Reports a list box event to any observer of this list box. 
     * This function returns immediately if no observer is set.
     *
     * @param aEvent The event to report.
     */
    IMPORT_C virtual void ReportListBoxEventL( MEikListBoxObserver::TListBoxEvent aEvent );
    
    /**
     * Redraws the specified area of this list box into the specified rectangle.
     *
     * @param aRect Rectangle to be redrawn. Specified relative to the 
     *        origin of this control.
     */
    IMPORT_C virtual void Draw(const TRect& aRect) const;
    
    /**
     * Clears the list box margins. The list box is redrawn only if redraws 
     * are enabled for the list box view.
     */
    IMPORT_C void ClearMargins() const;
    
    /**
     * Sets an item as the current item, even if it is not currently 
     * visible. Redraws the list box to reflect the change. This 
     * should not be called from within another Draw function.
     * 
     * @param aItemIndex The index of the list box item to update.
     */
    IMPORT_C virtual void UpdateCurrentItem(TInt aItemIndex) const;
    
    /**
     * Handles drag events.
     *
     * This function is called by @c HandlePointerEventL() to handle pointer 
     * drag events appropriately.
     *
     * @param aPointerPos The position of the @c TPointerEvent for which this 
     *        handler is invoked.
     */
    IMPORT_C virtual void HandleDragEventL(TPoint aPointerPos);
    
    /**
     * Tests whether an item exists.
     *
     * @param aItemIndex Index to test. 
     * @return @c ETrue if the specified item exists, EFalse otherwise.
     */
    IMPORT_C TBool ItemExists(TInt aItemIndex) const;
    
    /**
     * Draws the matcher cursor in the correct location for the current match. 
     * If there is no match buffer, this function returns immediately; 
     * otherwise the cursor is drawn on the current item using 
     * @c CListBoxView::DrawMatcherCursor() after scrolling to make the current 
     * item visible.
     * 
     * A list box control?s matcher cursor is an on-screen cursor which is 
     * drawn to indicate to the user the location of the current text. Whether 
     * the cursor is drawn is dependent on the 
     * @c CListBoxView::TFlags::EHasMatcherCursor flag, which may be set on the 
     * list box?s view.
     *
     * Note, that CListBoxView::DrawMatcherCursor() is not implemented in S60. 
     */
    IMPORT_C void DrawMatcherCursor() const;

    /**
     * Gets the vertical gap between elements in the list box. 
     *
     * @return The vertical gap between elements in the list box.
     */
    IMPORT_C static TInt InterItemGap();

    /**
     * Updates the view colours in line with the colours in effect for the 
     * Uikon environment. Has no effect if there is no view.
     */
    IMPORT_C void UpdateViewColors();

    /**
     * Updates the item drawer colours in line with the colours in effect 
     * for the Uikon environment. Has no effect if there is no item drawer.
     */
    IMPORT_C void UpdateItemDrawerColors();

    /**
     * Notifies item change observers about item change. Subclasses must call
     * this method if they have implemented item handling functions (e.g.
     * @c HandleItemAdditionL or @c HandleItemRemovalL).
     *
     * @since S60 3.0
     */
    IMPORT_C void FireItemChange();


protected:	// functions which deal with extension
    /**
     * Sets the reason for the list box?s loss of focus.
     *
     * This is required so the list box can determine whether 
     * loss of focus is due to an external control or an internal component.
     *
     * @param aReasonForFocusLost The reason for the loss of focus.
     */
    IMPORT_C void SetReasonForFocusLostL( TReasonForFocusLost aReasonForFocusLost );

    /**
     * Gets the reason for the list box?s loss of focus.
     *
     * @return The reason for the loss of focus.
     */
    IMPORT_C TReasonForFocusLost ReasonForFocusLostL();

    /**
     * Tests whether the list box match buffer exists.
     *
     * @return @c ETrue if the list box match buffer exists. 
               @c EFalse if the list box match buffer does not exist.
     */
    IMPORT_C TBool IsMatchBuffer() const;

    /**
     * Checks for a list box extension. Attempts to create one if not present. 
     *
     * This function leaves if an extension cannot be created.
     */
    void CheckCreateExtensionL();

    /**
     * Checks for a list box extension. Creates one if not present. 
     *
     * @return @c ETrue if a list box extension already existed or 
     *         if there was no previous extension and a new extension 
     *         class was created successfully. 
     *         @c EFalse if there was no previous extension and a new one 
     *         could not be constructed.
     */
    TBool CheckCreateExtension();

    /**
     * Checks the list box match buffer exists. If a buffer does not 
     * exist, one is created.
     */
    void CheckCreateBufferL();

    /**
     * Gets the list box match buffer.
     *
     * @return The list box match buffer.
     */
    CMatchBuffer* Buffer() const;

protected:
    /**
     * Creates a scroll bar frame layout according to @c aLayout.
     *
     * @param aLayout Defines the layout.
     */
    IMPORT_C void CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout) const;
    
    /**
     * If MiddleSoftKey is either Mark or Unmark, this method sets MSK
     * according to the current item selection state.
     */
    void UpdateMarkUnmarkMSKL() const;

public:
    /**
     * @return Event modifiers for the @c CEikListBox.
     */
    IMPORT_C TInt EventModifiers();

    /* 
    * Returns ETrue if list has ES60StyleMultiselection flag. 
    */
    IMPORT_C TBool IsMultiselection();

    /**
    * Creates a scrollbar for the listbox. The caller may choose if the scrollbar is requested 
    * remotely via the mop chain from parent control
    *
    * @param	aPreAlloc Is the scrollbar created immediately or when taking in to use
    * @param	aRemote If True, the scrollbar is obtained via mop-chain from 
    *           parent control. If used, the listbox only sets the scrollbar 
    *           values. The scrollbar position and size must set in the parent
    *           control's code.
    *
    * @return	CEikScrollBarFrame*	pointer to scrollbar frame object
    */	
    IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL(TBool aPreAlloc, TBool aRemote);
	
    /**
    * Creates a scrollbar for the listbox. The caller may choose if the scrollbar is requested 
    * remotely via the mop chain from parent control
    *
    * @param    aPreAlloc Is the scrollbar created immediately or when taking in to use
    * @param    aRemote If True, the scrollbar is obtained via mop-chain from 
    *           parent control. If used, the listbox only sets the scrollbar 
    *           values. The scrollbar position and size must set in the parent
    *           control's code.
    * @param    aWindowOwning Does the created scrollbar create own window or 
    *           is it compound control. The listbox uses a window owning 
    *           scrollbar by default.
    *
    * @return    CEikScrollBarFrame*    pointer to scrollbar frame object
    */    
    IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL(TBool aPreAlloc, TBool aRemote, TBool aWindowOwning);

    /**
    * By default markable listbox has middle softkey observer, which handles
    * Mark / Unmark functionality. By this method, the caller may disable default
    * observer.
    *
    * @since S60 3.1
    *
    * @param    aEnable If EFalse, disables default middle softkey observer
    *           for markable lists. ETrue enables observer again.
    */    
    IMPORT_C void EnableMSKObserver(TBool aEnable);
    
    /**
    * Called from MSK observer when shift+MSK have been pressed
    *
    * @Since S60 3.1
    */
    void DoShiftMSKMarkingL();

    /**
    * This method is only called by CEikButtonGroupContainer when MSK observer
    * is enabled and CEikButtonGroupContainer is deleted.
    *
    * @Since S60 3.1
    */
    void InformMSKButtonGroupDeletion();
    
    /**
    * Adds a selection (item marking) observer to the listbox. Duplicates are not checked
    * (i.e. adding the same observer multiple times is not prevented).
    *
    * @since 3.2
    * @param aObserver Must be non-NULL.
    */
    IMPORT_C void AddSelectionObserverL( MListBoxSelectionObserver* aObserver );
    
    /**
    * Removes a selection (item marking) observer from the listbox.
    *
    * @since 3.2
    * @param aObserver The observer to be removed.
    */
    IMPORT_C void RemoveSelectionObserver( MListBoxSelectionObserver* aObserver );

    /**
    * This switches listbox into selection mode. Basicly only changes MSK and
    * informs selection observers about the change.
    *
    * @since 3.2
    * @param aEnable ETrue when entering into selection mode, EFalse when leaving
    */
    void ChangeSelectionMode(TBool aEnable);

    /**
    * Sets the number of list items that form one grid line.
	*
	* @since S60 5.0
	* @param aItems Number of items in one grid line.
	*/
    IMPORT_C void SetItemsInSingleLine(TInt aItems);
    
    /**
    * Gets the number of list items in one line. This is more than one for
    * grids only.
	*
	* @since S60 5.2
	* @return The number of list items in one line.
	*/
    IMPORT_C TInt ItemsInSingleLine() const;
	
    /**
    * Removes pointer event filtering for list items.
    *
    * When there are two pointer up events on the same item at short interval, 
    * listbox will only get the first one and drop the second one. This method forces listbox to handle all pointer up events.
    *
    * @since S60 5.0
    *
    * @param aItemIndexes Array of item indexes to be added.
    **/
    IMPORT_C void SetPointerEventFilterDisabledL( const CArrayFix<TInt>& aItemIndexes );

    /**
     * Scrolls the view by the given amount of pixels while keeping the
     * physics parameters up-to-date.
     * This should be called when scrolling the list box view except for
     * when it is done by list dragging (e.g. scrolling with scroll bar).
     *
     * @param  aDeltaPixels  Amount of pixels to scroll the view.
     *
     * @since 5.0
     */
    IMPORT_C void HandlePhysicsScrollEventL( TInt aDeltaPixels );

    /**
     * Disables the kinetic scrolling functionality in the list.
     * By default the feature is enabled.
     * 
     * @param  aDisabled  @c ETrue to disable kinetic scrolling,
     *                    @c EFalse otherwise.
     *
     * @since 5.0
     */
    IMPORT_C void DisableScrolling( TBool aDisabled );
    
    /**
     * Checks if the kinetic scrolling is currently enabled in the list.
     *
     * @return @c ETrue if kinetic scrolling is enabled, @c EFalse otherwise.
     *
     * @since 5.0
     */
    IMPORT_C TBool ScrollingDisabled();
    
    /**
     * Suspends transitions effects.
     *
     * @since S60 5.0
     *
     * @param aSuspend ETrue to suspend effects, EFalse to re-enable them.
     */
    IMPORT_C void SuspendEffects( TBool aSuspend );

    /**
     * Disables the single click functionality in the list.
     * By default the feature is enabled.
     *
     * @since S60 5.2
     * 
     * @param  aDisabled @c ETrue to disable single click
     *                   @c EFalse does currently nothing
     */
    IMPORT_C void DisableSingleClick( TBool aDisabled );
    
    /**
     * Disables item specific menu from the list. This has the same effect as
     * construction time flag @c EAknListBoxItemSpecificMenuDisabled and
     * calling this method also turns that flag on.
     *
     * @since S60 5.2
     */
    IMPORT_C void DisableItemSpecificMenu();
    
private:
    IMPORT_C virtual void CEikListBox_Reserved(); // listbox use only
    void HorizontalScroll(TInt aScrollAmountInPixels);
    void DrawItemInView(TInt aItemIndex) const;
    void ClearMargins(CWindowGc& aGc) const;
    TKeyResponse DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    void UpdateScrollBarColors(CEikScrollBar* aScrollBar);
    void UpdateScrollBarsColors();

    void HandleItemRemovalWithoutSelectionsL();

    /**
     * Scrolls the view by the given amount of pixels.
     *
     * @param  aOffset   Amount of offset in pixels.
     * @param  aDrawNow  Whether or not the view is be drawn.
     *                   If @c EFalse then only the logical state is updated.
     *
     * @internal
     * @since 5.0
     */
    void ScrollView( const TInt aOffset, TBool aDrawNow );
    
    /**
     * Handles pointer events if physics are enabled.
     *
     * @return @c ETrue if the event was consumed by kinetic scrolling.
     *
     * @internal
     * @since 5.0
     */
    TBool HandlePhysicsPointerEventL( const TPointerEvent& aPointerEvent );
    
    /**
     * Selects an item and draws highlight to it.
     * 
     * @param  aItemIndex  Index of the highlighted item. 
     * 
     * @internal
     * @since 5.0
     */
    void UpdateHighlightL( TInt aItemIndex );

public:
    /**
     * Sets this control as visible or invisible.
     * 
     * @param aVisible ETrue to make the control visible, EFalse to make
     *                 it invisible.
     * @since 5.2
     */
    IMPORT_C virtual void MakeVisible( TBool aVisible );

protected:
    /** Flags for this list box  */
    TInt iListBoxFlags;
    
    /** This List box's view  */
    CListBoxView* iView;
    
    /** Item drawer for this list box */
    CListItemDrawer* iItemDrawer;
    
    /** Data model for this list box */
    MListBoxModel* iModel;
    
    /** Height of each item in the list */
    TInt iItemHeight;   
    
    /** The scroll bar used by this control */
    CEikScrollBarFrame* iSBFrame;
    
    /** Identifies if the scroll bar is owned by this list */
    TScrollBarOwnerShip iSBFrameOwned;
    
    /** The required height of this list box expressed in 
     * terms of a number of items.
     */
    TInt iRequiredHeightInNumOfItems;
    
    /**
     * Defines which button launched the popout.
     */
    CEikButtonBase* iLaunchingButton; // only used by popouts
    
    /** The button which just launched a popout menu. */
    MEikListBoxObserver* iListBoxObserver;

private:

    TRgb iBackColor;
//  TInt iHorizontalMargin;
//  TInt iVerticalMargin;
    TMargins8 iMargins ;
    CListBoxExt* iListBoxExt;
    TInt iViewRectHeightAdjustment;
    MEikListBoxEditor* iItemEditor;
    TBool* iLbxDestroyed;
    TBool iLastCharMatched;
    TInt iSpare;
    };



/**
* This is a list box that scrolls horizontally, displaying its items 
* in as many vertical columns as needed. Columns are arranged across 
* the control from left to right; within columns, items are arranged 
* from top to bottom. The flow of items or text ?snakes? across the 
* face of the control.
*
* This is a flexible control class that makes good use of short, wide 
* display areas; for instance, subclasses of @c CEikSnakingListBox could 
* be used for file lists or for a control panel. A standard user 
* subclass, @c CEikSnakingTextListBox, also exists.
*
* @since Symbian 5.0
*/     
class CEikSnakingListBox : public CEikListBox  
    {
public:
    /**
     * C++ standard constructor
     */
    IMPORT_C CEikSnakingListBox();
    
    /**
     * Destructor
     */
    IMPORT_C ~CEikSnakingListBox();
    
    /**
     * Creates an instance of the view class.
     *
     * This function is called during construction to create 
     * (but not second-phase construct) an instance of the correct view 
     * class for this list box control. In the case of the snaking list 
     * box, a @c CSnakingListBoxView is returned.
     *
     * This function overrides @c CEikListBox::MakeViewClassInstanceL().
     *
     * @return The view which will be used by the list box being created
     */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
    
    /**
     * Sets the top item?s index.
     *
     * @param aItemIndex Index of the item to set as the top item.
     */
    IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex) const;
    
    /**
     * Gets the width of this list box?s columns. 
     *
     * @return Width of each column.
     */
    IMPORT_C TInt ColumnWidth() const;
    
    /**
     * Sets the width of all columns in the list box.
     *
     * @param aColumnWidth New column width.
     */
    IMPORT_C void SetColumnWidth(TInt aColumnWidth);

public: //from CCoeControl
    
    /**
     * From @c CCoeControl.
     *
     * Handles pointer events. 
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected:
    
    /**
     * Handles a change in size of the viewing rectangle.
     *
     * This function is called by framework functions to update the content, 
     * view, and scroll bars of this list box after the viewing rectangle has 
     * changed size. This implementation ensures that the current item is 
     * visible after a resize.
     */
    IMPORT_C virtual void HandleViewRectSizeChangeL();

    /**
     * Handles a left arrow key event.
     * 
     * Moves the cursor into the correct column and clears any matcher buffer 
     * that may have been built up.
     *
     * @param aSelectionMode Not used.
     */
    IMPORT_C virtual void HandleLeftArrowKeyL(
                            CListBoxView::TSelectionMode aSelectionMode);
    
    /**
     * Handles a right arrow key event.
     * 
     * Moves the cursor into the correct column and clears any matcher buffer 
     * that may have been built up.
     *
     * @param aSelectionMode Not used.
     */
    IMPORT_C virtual void HandleRightArrowKeyL(
                            CListBoxView::TSelectionMode aSelectionMode);
    
    /**
     * Gets the number of grains to move horizontally when a nudge button 
     * is tapped. 
     *
     * For simple list boxes, this value is a fraction of the width of the
     * client area. 
     *
     * @return Number of grains to move left or right on each nudge.
     */
    IMPORT_C virtual TInt HorizontalNudgeValue() const;

    /**
     * Gets the granularity for horizontal scrolls. 
     *
     * The granularity is the minimum size of a horizontal move of the 
     * client area.
     *
     * @return Grain size for horizontal scrolling in pixels.
     */
    IMPORT_C virtual TInt HorizScrollGranularityInPixels() const;

    /**
     * Called by various functions of this class to ensure that the top 
     * item index is always a sane value. The implementation in @c CEikListBox 
     * tries to ensure the minimum amount of white space at the bottom of 
     * the list box. Note that this function does not affect the current 
     * item index.
     */
    IMPORT_C virtual void AdjustTopItemIndex() const;

    /**
     * Handles drag events.
     *
     * This function is called by @c HandlePointerEventL() to handle 
     * pointer drag events appropriately.
     *
     * @param aPointerPos The position of the @c TPointerEvent for which this 
     *        handler is invoked.
     */
    IMPORT_C virtual void HandleDragEventL(TPoint aPointerPos);

    /**
     * Calculates the client area.
     *
     * This method is called by various functions of this class to recalculate 
     * the extent of the client area from @c iViewRect. This implementation 
     * takes into account any rounding of the viewing rectangle made to fit a 
     * whole number of items.
     *
     * @param aClientRect On return contains a size for the client area in 
     *        pixels.
     */
    IMPORT_C virtual void RestoreClientRectFromViewRect(
                                                    TRect& aClientRect) const;

    /**
     * Rounds down the height of the rectangle (if necessary) so that only a 
     * whole number of items can be displayed inside the list box.
     *
     * @param aRect The rectangle to be modified. 
     * @return The number of pixels reduced.
     */
    IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(
                                                        TRect& aRect) const;

    /**
     * Move to next or previous item according to the given parameter.
     *
     * @param aPoint Position which defines the moving direction.
     */
    IMPORT_C void MoveToNextOrPreviousItemL(TPoint aPoint);

protected: //from CCoeControl

    /**
     * From @c CCoeControl
     *
     * Updates the viewing rectangle of this control appropriately. The function
     * updates the viewing rectangle, and invokes @c HandleViewRectSizeChangeL().
     */
    IMPORT_C virtual void SizeChanged();
    
    /**
     * From @c CCoeControl
     *
     * Gets the list of logical colours employed in the drawing of the control,
     * paired with an explanation of how they are used. Appends the list to 
     * @c aColorUseList.
     *
     * @param aColorUseList List of logical colours.
     */
    IMPORT_C virtual void GetColorUseListL(
                    CArrayFix<TCoeColorUse>& aColorUseList) const; 
                    // not available before Release 005u
    /**
     * From @c CCoeControl.
     *
     * Handles a change to the list box?s resources of type @c aType which are 
     * shared across the environment, colours or fonts for example.
     *
     * @param aType The type of resources that have changed.
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);         
                    // not available before Release 005u

private: // from CCoeControl
    IMPORT_C void Reserved_1();
    
    IMPORT_C void Reserved_2();

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
    IMPORT_C virtual void CEikListBox_Reserved(); // listbox use only
    };

#endif  // __EIKLBX_H__
