/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Toolbar extension view, which shows a set of buttons or other
*                components. 
*
*/


#ifndef CAKNTOOLBAREXTENSIONVIEW_H
#define CAKNTOOLBAREXTENSIONVIEW_H

#include <AknControl.h>


class CAknToolbarExtension; 
class CAknToolbarItem; 
class CAknsFrameBackgroundControlContext;
class TAknWindowComponentLayout;
class CAknResourceProvider;


/**
 *  Toolbar extension view
 *
 *  Toolbar extension view shows the extension view window. Extension view
 *  can consist of buttons, editor and other controls. Extension view is 
 *  either focused or non-focusing, depending on toolbar. 
 *
 *  @lib eikcoctl.lib
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknToolbarExtensionView ) : public CAknControl
    {
public:

    /**
     * Creates toolbar extension
     *
     * @return extension
     */
    static CAknToolbarExtensionView* NewL( TResourceReader& aReader,
        CAknToolbarExtension* aExtension );

    /**
     * Destructor
     */
    ~CAknToolbarExtensionView();


// from base class CCoeControl

    /**
     * From CCoeControl.
     * Constructs extension view from resource
     *
     * @param aReader resource reader
     */
    void ConstructFromResourceL( TResourceReader& aReader );

    /**
     * From CCoeControl
     * Makes extension visible or hides it
     *
     * @param aVisible indicates if to show or to hide
     */
    void MakeVisible( TBool aVisible );

    /**
     * From CCoeControl.
     * Handles key events. 
     *
     * @param aKeyEvent information about the key event
     * @param aType type of the key event. 
     * @return consumed or did not consume the key event. 
     */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

    /**
     * From CCoeControl.
     * Gets the number of controls contained in a compound control.
     *
     * @return The number of component controls contained by this control.
     */
    TInt CountComponentControls() const;

    /**
     * From CCoeControl.
     * Gets the specified component of a compound control.
     *
     * @param aIndex The index of the control to get
     * @return The component control with an index of aIndex.
     */
    CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
     * From CCoeControl.
     * Handles resource changes, for example layout and skin changes 
     *
     * @param aType the type of resource change
     */
    void HandleResourceChange( TInt aType );

    /**
     * Handles pointer events
     * @param aPointerEvent information about the pointer event
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent ); 

// new functions

    /**
     * Gets a pointer to the specified control.
     *
     * @param aControlId The ID of the control for which a pointer is
     *      required.
     * @return Pointer to the control with the specified ID.
     */
    CCoeControl* ControlOrNull( TInt aCommandId ) const; 

    /**
     * Returns command id of the control given
     * @param aControl the control which command id is needed 
     * @return command id of the control
     */
    TInt CommandIdByControl( CCoeControl* aControl ) const; 

    /**
     * Checks where controltype is an editor
     * @param aType controltype of the control
     * @return ETrue if control is editor. 
     */
    TBool Editor( TInt aType );

    /**
     * Adds one item to the specified place. Takes ownership.
     * Leaves with value KErrArgument if aItem does not exist or 
     * aIndex is out of bound. 
     *
     * @param aItem The control.
     * @param aType The type of the new toolbar item.
     * @param aCommandId The command ID for this item.
     * @param aFlags The flags.
     * @param aIndex The index in array at which item should be added.
     */
    void AddItemL( CCoeControl* aItem,
                   TInt aType,
                   TInt aCommandId,
                   TInt aFlags,
                   TInt aIndex );

    /**
     * Removes an item
     * @param aCommandId the command id of the item to be removed
     */
    void RemoveItemL( TInt aCommandId ); 

    /**
     * Sets an item dimmed or undimmed
     * @param aCommandId the command id of the item to be dimmed
     * @param aDimmed to dim or undim
     */
    void SetItemDimmed( TInt aCommandId, TBool aDimmed ); 

    /**
     * Hides an item or unhides it
     * @param aCommandId command id of the item to be hidden/unhidden
     * @param aHidden to hide or unhide
     */
    void HideItemL( TInt aCommandId, TBool aHide ); 

private: // Functions from base class

    /**
     * From CCoeControl. Draws the control. Called by window server.
     */
    void Draw( const TRect& aRect ) const;  


private: // New functions

    /**
     * Default constructor
     *
     * @param aExtension pointer to extension
     */
    CAknToolbarExtensionView( CAknToolbarExtension* aExtension );

    /**
     * 2nd phase constructor
     */
    void ConstructL(); 

    /**
     * Constructs an control from resources 
     *
     * @param aReader resource reader
     * @return a toolbar item
     */
    CAknToolbarItem* ConstructControlLC( TResourceReader& aReader ); 

    /**
     * Calculates size and position for the extension
     *
     * @return the extension rect
     */
    TRect CalculateSizeL(); 

    /**
     * Selects or unselects an item
     *
     * @param aIndex the item to select/unselect
     * @param aSelect if to select an item or unselect it
     */
    void SelectItemL( TInt aIndex, TBool aSelect ); 

    /**
     * Gets rect from layout data.
     */
    TRect RectFromLayout( const TRect& aParent,
        const TAknWindowComponentLayout& aComponentLayout) const; 

    /**
     * Resizing editor and button after it
     */
    void ResizeFindPaneL( TRect& aWindowRect, TBool aLandscape, TInt aPosition, 
        TInt& aIndex ); 

    /**
     * Getting the correct y-coordinate for extension
     */
    TInt GetVariety( TInt aRow, TBool aLandscape ); 

    /**
     * Checking button frames when an item was added, removed, hidden or unhidden
     * after an editor. 
     */
    void CheckButtonFrames( TInt aAdd, TInt aIndex ); 

    /**
     * Returns index of the item which commandid is given as parameter. 
     */
    TInt ToolbarItemIndexById( TBool aVisibleItems, const TInt aId ) const;  

    /**
     * Moves highlight to another item
     * @param aDirection to which direction to move, enum defined in 
     *        akntoolbarextenion.view.cpp
     * @param aIndex if aDirection is  ENoDirection, this index informs to which item 
     *        to move the highlight
     */
    void MoveHighlightL( TInt aDirection, TInt aIndex );

    /**
     * Calculates next focusable item. Used with floating toolbar extension. 
     * @param aStep how many steps to move. 
     * @return index of the next focusable item
     */
    TInt NextFocusable( TInt aStep ); 

    /**
     * Adjusts button's properties depending on the toolbar extension's features.
     */                                   
    void AdjustButtonL( CAknButton& aButton );
    
    /**
     * Calculates and sets the control positions according to layout rects
     * @param aWindowRect Window rect
     * @param aGridRect Grid rect
     * @param aCellRect Cell rect
     * @return Extension width
     */                                   
    TInt CalculateControlPositions( 
        TRect& aWindowRect, TRect& aGridRect, TRect& aCellRect );

    /**
     * Returns hidden items count
     * Needed when iVisibleItems is not up-to-date.
     * @return Count of hidden items
     */                                   
    TInt CountHiddenItems();

private: // data

    /** Toolbar extension frame context
     * Own
     */ 
    CAknsFrameBackgroundControlContext* iFrameContext;

    /**
     * Pointer to extension
     * Not own. 
     */
    CAknToolbarExtension* iExtension; 

    /**
     * Pointer array of extension items
     * Own. 
     */
    RPointerArray<CAknToolbarItem> iItems; 

    /**
     * Pointer array of extension items
     * Own. 
     */
    RPointerArray<CAknToolbarItem> iVisibleItems; 

    /**
     * Extension position
     */
    TPoint iExtensionPosition; 

    /**
     * Currently selected item
     */
    TInt iSelectedItem; 

    /**
     * Previously selected item, used in handlepointerevent to control
     * the pointer events
     */
    TInt iPreviousItem; 

    /**
     * Item that catches point down event
     */
    TInt iDownItem;

    /**
     * Number of colums in extension. Used when moving the focus down or up. 
     */
    TInt iNumberOfColumns; 

    /**
     * Number of rows in extension. 
     */
    TInt iNumberOfRows; 

    /**
     * Resource provider.
     * Own.
     */
    CAknResourceProvider* iResourceProvider;

    /*
     * record whether the touch down operation takes place outside the view area
     */
    TBool    iIsDownOutside;
    };

#endif // CAKNTOOLBAREXTENSIONVIEW_H
