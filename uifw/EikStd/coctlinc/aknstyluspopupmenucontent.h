/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Content that is shown inside a stylus popup menu.
*
*/


#ifndef CAKNSTYLUSPOPUPMENUCONTENT_H
#define CAKNSTYLUSPOPUPMENUCONTENT_H

#include <AknControl.h>
#include <aknstyluspopupmenu.h>

class CAknStylusPopUpMenuItem;
class CAknStylusPopUpMenuExtension;
class CAknStylusPopUpMenuPhysicsHandler;

/**
 *  Class providing content for the stylus popup menu.
 *
 *  @lib eikcoctl.lib
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknStylusPopUpMenuContent ) : public CAknControl,
                                                  public MCoeForegroundObserver,
                                                  public MEikScrollBarObserver
                                                  
    {
private: 
    enum THighlightType { ENoHighlight, EDrawHighlight, ERemoveHighlight };
    enum TScrollType { ENoScroll, EScrollUp, EScrollDown };

public:

    static CAknStylusPopUpMenuContent* NewL( CAknStylusPopUpMenu& aPopUpMenu );

    static CAknStylusPopUpMenuContent* NewLC( CAknStylusPopUpMenu& aPopUpMenu );

    ~CAknStylusPopUpMenuContent();

    /**
     * Adds a new menu item.
     *
     * @param aItem Menu item to be added.
     * @param aCommandId Command ID of the menu item.
     */
    void AddMenuItemL( const TDesC& aItem, const TInt aCommandId );

    /**
     * Removes a menu item.
     *
     * @param aIndex Index of the menu item.
     */
    void RemoveMenuItem( const TInt aIndex );
    
    /**
     * Hides / shows a menu item.
     *
     * @param aIndex Index of the menu item.
     * @param aDimmed ETrue to hide and EFalse to show
     */
    void SetItemDimmed( const TInt aIndex, const TBool aDimmed );
        
    /**
     * Method to get the command id of currently selected item.
     *
     * @return Command id.
     */
    TInt CurrentCommandId() const;

    /**
     * Draws highlight again when animation frame is ready. Called by 
     * extension. 
     */
    void RepaintHighlight() const;

    /**
     * Returns current item's rect
     * @return current item's highlightrect
     */
    TRect HighlightRect() const;

    /**
     * Removes all items.
     */
    void Clear();

// from base class CCoeControl

    /**
     * Returns the minimum size of the control.
     *
     * @return Minimum size.
     */
     TSize MinimumSize();
    
    /**
     * Handles changes to the control's resources.
     *
     * @aParam aType Type of resource change.
     */     
     void HandleResourceChange( TInt aType );

    /**
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event. 
     */
     void HandlePointerEventL( const TPointerEvent& aPointerEvent );

    /**
     * Makes item visible or hides it
     *
     * @param aVisible if to be shown
     */
     void MakeVisible( TBool aVisible );

   /**
     * Gets the number of controls contained in a compound control.
     *
     * @return The number of component controls contained by this control.
     */
     TInt CountComponentControls() const;

     /**
     * Gets the specified component of a compound control.
     *
     * @param aIndex The index of the control to get
     * @return The component control with an index of aIndex.
     */
     CCoeControl* ComponentControl( TInt aIndex ) const;
     
     
// from base class MCoeControlObserver

     /**
      * Not used, but implementation is required by
      * MCoeForegroundObserver
      */
	 void HandleGainingForeground();
	
	 /**
	  * When foreground is lost, stylus popupmenu is closed,
	  * TSW Error AJUA-79ELVM.
	  */
	 void HandleLosingForeground();


     // Functions related to Physics handling

public:

    /**
     * Updates view so that aTopmostItem is topmost item.
     * Uses also offset from physics handler to locate view smoothly. 
     *
     * @aParam aTopmostItem Topmost item
     */ 
    void UpdateView( TInt aTopmostItem );
    
    /**
     * Returns index of item that contains given position. 
     *
     * @return index of item that contains given position
     */ 
    TInt ContainingItem( const TPoint& aPosition );

    /**
    * Sets highlight to given item
    *
    * @aParam aItem Item to be highlight
    */ 
   void SetHighlight( TInt aItem );
   
   /**
    * Return currently highlighted item's index.
    * 
    * @return Highlighted item's index or -1 if no item has highlight.
    */
   TInt CurrentItem() const;
      
    /**
     * Selects given item
     *
     * @aParam aItem Item to be selected
     */ 
    void SelectItem( TInt aItem );
    
private:
	
	/**
     * Initializes physics.
     */
	void InitPhysicsL();
    
    /**
     * Returns offset. Used to draw partial items.
     *
     * @return offset
     */
    TInt Offset() const; 
    
    /**
     * Returns height of whole list content (excluding hidden items).
     *
     * @return world height
     */
    TInt WorldHeight() const;
    
private:

    /**
     * Default constructor
     */
    CAknStylusPopUpMenuContent( CAknStylusPopUpMenu& aPopUpMenu );

    /**
     * 2nd phase constructor
     */
    void ConstructL();

    /**
     * Moves the highlight to a newly selected menu item identified
     * by @c aNewSelectedItem. Redraws only the newly selected item and the currently
     * selected item if possible.
     * 
     * @param aNewSelectedItem The newly selected menu item index.
     */
    void MoveHighlightTo( TInt aNewSelectedItem );
    
    /**
     * Draws items. Draws higlight for the items 
     *
     * @param aGc The graphics context
     * @param aItem the item for which the highlight is drawn
     * @param aHighlight if the item has highlight or not
     */
    void DrawItem( CWindowGc& aGc, TInt aItem, THighlightType aHighlight ) const; 

    /**
     * Starts highlight animation
     *
     * @return KErrNone if successful, error code if not
     */
    TInt StartAnimation(); 

    /**
     * Updates scroll bar
     */
    void UpdateScrollBar();
    
    /**
     * Calculates which items are shown and sets rects for them
     *
     * @param aScroll TScrollType type of scroll
     * @return Index of the last shown item 
     */
    TInt CalculateShownItems( TScrollType aScroll );
     
        
// from base class CCoeControl
    
    /**
     * Sets new rect for the items
     */
    void SizeChanged();

    /**
     * Draw a control called by window server.
     *
     * @param aRect The region of the control to be redrawn. 
     *      Co-ordinates are relative to the control's origin (top left corner).
     */
    void Draw( const TRect& aRect ) const;


    /**
     * Get's list rect from layout data
     *
     * @param aParent The region of the parent control
     * @param aLineLayout The component which to get from layout data
     * 
     * @return list rect
     */
    TRect ListRectFromLayout( const TRect& aParent,
        const TAknWindowLineLayout& aLineLayout ) const; 

    /**
     * Get's rect from layout data according to layout data 
     *
     * @param aParent The region of the parent control
     * @param aParent The component which to get from layout data
     * 
     * @return layout rect
     */
    TRect RectFromLayout( const TRect& aParent,
        const TAknWindowLineLayout& aLineLayout ) const; 


// from MEikScrollBarObserver

    /**
     * Handles events from scrollbar
     *
     * @param aScrollBar Pointer to scrollbar
     * @param aEventType Scrollbar event
     */
    void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType); 

private: // data

    /**
     * Array which holds pointers to menu items. 
     */
    RPointerArray<CAknStylusPopUpMenuItem> iItems;
    
    /**
     * Current item
     */
    TInt iCurrentItem; 

    /**
     * Stylus PopUp menu extension which handles highlight animation 
     * own
     */
    CAknStylusPopUpMenuExtension* iExtension; 
    
    /** 
     * The scroll bar used by this control
     * own
     */ 
    CEikScrollBarFrame* iSBFrame;
    
    /**
     * First visible item on the list
     */
    TInt iFirstItem;
    
    CAknStylusPopUpMenu& iPopUpMenu;
    
    /**
     * Physics handler.
     * own.
     */
    CAknStylusPopUpMenuPhysicsHandler* iPhysicsHandler; 
    };

#endif // CAKNSTYLUSPOPUPMENUCONTENT_H

