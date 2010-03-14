/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKMENUP_H__)
#define __EIKMENUP_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h> // for TEikScrollEvent
#endif

#include <bidi.h>

// FORWARD DECLARATIONS
class MEikMenuObserver;
class CEikHotKeyTable;
class CEikMenuPaneTitle;
class CEikButtonBase;
class CEikScrollBarFrame;
class CEikScrollBar;
class TEikScrollBarModel;
class CGulIcon;
class CEikMenuPaneExtension ;
class CEikCba;
class CAknItemActionMenuData;

// CONSTANTS
const TInt KScaleableTextSeparator = 0x0001;

/**
  * A helper class for extending CEikMenuPaneItem without breaking binary 
  * compability.
  */
class CExtendedItemData : public CBase
    {
    
public:
    
    /**
     * Destructor.
     */
    ~CExtendedItemData();
    
public:
    
    /** Two packaked bitmaps: bitmap icon and mask for it. */
    CGulIcon* iIcon;
    
    /** Scalable text buffer. */
    HBufC* iScaleableText;    
    };


/**
 * The @c CEikMenuPaneItem class encapsulates the data needed to define a menu
 * pane item and provides some of the functionality required to display the 
 * item.
 *
 * @since ER5U
 */
class CEikMenuPaneItem : public CBase
    {
    
public:
    
    /** Struct to menu pane item. */
    struct SData
        {
        
        /** Nominal text length.*/
        enum { ENominalTextLength=40 };
        
        /** 
         * ID of the command to issue when the menu item using this @c SData is 
         * selected.
         */
        TInt iCommandId;
        
        /** Resource ID of a menu pane to cascade from this item. */
        TInt iCascadeId;
        
        /** 
         * Flags used internally by @c CEikMenuPane and accessible through 
         * functions such as @c CEikMenuPane::SetItemDimmed().
         */
        TInt iFlags;
        
        /** The text buffer displayed in the main area of the menu item. */
        TBuf<ENominalTextLength> iText; // less than this actually stored
        
        /** 
         * Additional descriptive text about the item. This is used by @c 
         * CEikMenuPane to display hotkey names.
         */
        TBuf<1> iExtraText;
        };
        
public:

    /**
     * C++ default constructor.
     */
    IMPORT_C CEikMenuPaneItem();
    
    /**
     * Destructor.
     */
    IMPORT_C ~CEikMenuPaneItem();
    
    /**
     * Sets a menu item icon. This replaces any icon already set for the menu
     * item.
     *
     * @param aIcon Menu item icon consisting of a picture bitmap and a mask 
     *        bitmap.
     */
    IMPORT_C void SetIcon(CGulIcon* aIcon);
    
    /**
     * Draws the menu item icon.
     * 
     * @param aGc Graphics context to which the icon is drawn.
     * @param aRect Rectangle in which the icon is drawn. 
     * @param aDimmed If @c ETrue the icon is drawn dimmed. 
     * @param aBitmapSpaceRequired Length of one side of the square required to 
     *        contain the bitmap.
     */
    IMPORT_C void DrawItemIcon(CWindowGc& aGc, 
                               TRect aRect, 
                               TBool aDimmed, 
                               TInt aBitmapSpaceRequired) const;
    
    /**
     * Construct an icon from bitmaps. 
     * 
     * Constructs a new icon for the menu item, taking ownership of the picture
     * bitmap aBitmap and the mask bitmap aMask unless the bitmaps are 
     * externally owned.
     * 
     * @param aBitmap Picture bitmap.
     * @param aMask Mask bitmap.
     */
    IMPORT_C void CreateIconL(CFbsBitmap* aBitmap, 
                              CFbsBitmap* aMask);
    
    /**
     * Gets a pointer to the menu item's icon picture bitmap. This does not 
     * imply transfer of ownership.
     * 
     * @return Picture bitmap.
     */
    IMPORT_C CFbsBitmap* IconBitmap() const;
    
    /**
     * Gets a pointer to the menu item's icon mask bitmap. This does not imply
     * transfer of ownership.
     * 
     * @return Mask bitmap.
     */
    IMPORT_C CFbsBitmap* IconMask() const;
    
    /**
     * Sets icon bitmap ownership.
     * Sets the menu item's icon bitmaps as externally owned if @c 
     * aOwnedExternally is @c ETrue.
     * 
     * @param aOwnedExternally If @c ETrue bitmaps are set as externally owned. 
     *        @c If EFalse bitmaps are set as not being externally owned. 
     */
    IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);
    
    /**
     * Sets the picture bitmap. Transfers ownership unless the bitmaps are 
     * already owned externally.
     * 
     * @param aBitmap Picture bitmap.
     */
    IMPORT_C void SetIconBitmapL(CFbsBitmap* aBitmap);
    
    /**
     * Sets the mask bitmap. Transfers ownership unless the bitmaps are already
     * owned externally.
     * 
     * @param aMask Mask bitmap.
     */
    IMPORT_C void SetIconMaskL(CFbsBitmap* aMask);
    
    /**
     * Returns scaleable text. If there isn't scaleable text available then
     * this method returns @c iData.iText.
     * 
     * @return Pointer to TPtrC object that contains scaleable text.
     */
    IMPORT_C TPtrC ScaleableText() const;
    
    /**
     * Sets scaleable text. @c iData.iText is set to first text version.
     * 
     * @param aText Scalable text.
     */
    IMPORT_C void SetScaleableTextL(const TDesC& aText);

private:
    inline void CreateExtendedDataBlock();
    inline TBool IsScaleableText(const TDesC& aText) const;
    TPtrC GetNominalText(const TDesC& aText);

public:

    /** The y position of the menu pane item. */
    TInt iPos;
    
    /** The menu pane item's hotkey text. */
    TInt iHotKeyCode;
    
    /** Information from an SData struct. */
    SData  iData;

private:
    CExtendedItemData* iExtendedData;
    };


inline void CEikMenuPaneItem::CreateExtendedDataBlock()
    {
    if (!iExtendedData)
        {
        TRAPD(err, ( iExtendedData = new (ELeave) CExtendedItemData() ) );
        }
    }


inline TBool CEikMenuPaneItem::IsScaleableText(const TDesC& aText) const
    {
    return aText.Locate( TChar( KScaleableTextSeparator ) ) != KErrNotFound;
    }


/**
 * Menu panes are opened by activating the menu title 
 * @c (CEikMenuPaneTitle / MENU_TITLE) which is displayed in the menu bar @c 
 * (CEikMenuBar / MENU_BAR). They can also be cascaded from a menu item @c
 * (CEikMenuPaneItem / MENU_ITEM) or launched by a menu button @c 
 * (CEikMenuButton). 
 *
 * Menu panes may be defined using a @c MENU_PANE resource.
 */
class CEikMenuPane : public CEikBorderedControl
    {
private:
    enum {ENothingSelected=-1};
    class CMenuScroller;
    friend class CMenuScroller;
    friend class CEikMenuPaneExtension;
public:
    
    /** The text to be displayed for a hotkey. */
    typedef TBuf<20> THotKeyDisplayText;
    
public:

    /**
     * This class provides a constructor to create an array of menu pane items
     * and a destructor to destroy an array of menu pane items.
     */
    class CItemArray:public CArrayPtrFlat<CEikMenuPaneItem>
        {
        
    public:
        
        /**
         * C++ default constructor that creates a flat array of menu pane 
         * items.
         */
        IMPORT_C CItemArray();
        
        /**
         * Destructor.
         */
        IMPORT_C ~CItemArray();
        
        /**
         * Appends @c CEikMenuPaneItem class object to array.
         *
         * @param aMenuItem The menu item to add.
         */        
        IMPORT_C void AddItemL(CEikMenuPaneItem* aMenuItem);
        };

public:

    /**
     * Destructor.
     */
    IMPORT_C ~CEikMenuPane();
    
    /**
     * C++ default constructor. Constructs a menu pane object with the 
     * specified observer.
     * 
     * @param aMenuObserver Menu observer.
     */
    IMPORT_C CEikMenuPane(MEikMenuObserver* aMenuObserver);

    /**
     * Handles 2nd base construction. Completes construction of a menu pane object. 
     * 
     * @param aOwner Menu pane owner ( for cascade menu ).
     * @param aEditMenuObserver Observer for the edit menu. In default this is 
     *        @c NULL.
     */
    IMPORT_C void ConstructL(CEikMenuPane* aOwner, 
                             MEikMenuObserver* aEditMenuObserver = NULL);
    
    /**
     * Destroys the menu pane's item array.
     */
    IMPORT_C void Reset();
    
public: // framework

    /**
     * From @c CcoeControl.
     *
     * Handles key events offered to the menu by the control environment and 
     * provides an appropriate implementation of @c 
     * CCoeControl::OfferKeyEventL(). 
     * 
     * @param aKeyEvent The key event. 
     * @param aType The type of key event: @c EEventKey, @c EEventKeyUp or @c 
     *        EEventKeyDown.
     */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                         TEventCode aType);
    
    /**
     * From @c CcoeControl.
     *
     * Handles a pointer event on the menu.
     * 
     * @param aPointerEvent The pointer event to handle.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    /**
     * From @c CcoeControl.
     *
     * Gets the list of logical colours employed in the drawing of the control, 
     * paired with an explanation of how they are used. Appends the list into 
     * @c aColorUseList.
     * 
     * @since 005u
     * @param aColorUseList The list of colours paired with explanations.
     */
    IMPORT_C virtual void GetColorUseListL(
        CArrayFix<TCoeColorUse>& aColorUseList) const; 
    
    /**
     * From @c CcoeControl.
     *
     * Handles a change to the menu's resources which are shared across the
     * environment. For example, colours or fonts.
     * 
     * @since 005u
     * @param aType The type of resource that has changed.
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u

private: // from base class

    /**
     * Not implemented.
     * 
     * @param Not used.
     * @return NULL
     */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
public: // from MCoeInputObserver
    
    /**
     * From @c CCoeControl.
     *
     * Gets the list box’s input capabilities as set through the list box flags.
     *
     * @return List box input capabilities.
     */
    IMPORT_C TCoeInputCapabilities InputCapabilities() const;
    
protected: // from base class
    
    /** 
     * From @c CCoeControl
     * 
     * Draw a control called by window server. 
     *
     * All controls, except blank controls, should implement this function. The
     * default implementation draws a blank control. This function is used for
     * window server-initiated redrawing of controls, and for some 
     * application-initiated drawing. It should be implemented by each control,
     * but  is only called from within @c CCoeControl's member functions, and 
     * not from the derived class. For this reason it is a private member 
     * function of @c CCoeControl.
     *
     * The rectangle aRect indicates the region of the control that needs to be
     * redrawn. The implementation of @c Draw() must always draw to every pixel 
     * within this rectangle.
     *
     * @param aRect The region of the control to be redrawn. 
     *        Co-ordinates are relative to the control's origin (top left 
     *        corner). Optional, not used currently.
     */
    IMPORT_C void Draw(const TRect& aRect) const;
    
    /**
     * From @c CCoeControl.
     *
     * Takes any action required when the menu pane gains or loses focus, 
     * to change its appearance for example.
     * 
     * @param aDrawNow If @c EDrawNow the menu pane is redrawn. If @c 
     *        ENoDrawNow the menu pane is not redrawn.
     */
    IMPORT_C void FocusChanged(TDrawNow aDrawNow);
    
    /**
     * From @c CCoeControl.
     *
     * Constructs the menu pane using the specified resource reader.
     * Fills the menu item array with the list of menu items provided by the
     * resource file.
     * 
     * @param aReader The resource reader to use.
     * @leave KErrNoMemory Memory allocation failure earlier construction.     
     */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
public: // new functions

    /**
     * Adds a menu item dynamically by creating a new menu item, setting its 
     * data to @c aMenuItem and appending it to the pane's menu item array. 
     * Updates the menu's scroll bar to take account of the new item.
     * 
     * @param aMenuItem The menu item to add.
     *        NOTICE that @c SData is a structure so all fields in it should be
     *        set to avoid any unexpected behaviour.
     */
    IMPORT_C void AddMenuItemL(const CEikMenuPaneItem::SData& aMenuItem);
    
    /**
     * Adds a menu item dynamically by creating a new menu item, setting its 
     * data to @c aMenuItem and inserting it into the pane's menu item array. 
     * Updates the menu's scroll bar to take account of the new item.
     * 
     * @param aMenuItem The menu item to add. NOTICE that @c SData is a 
     *        structure so all fields in it should be set to avoid any 
     *        unexpected behaviour.
     * @param aPreviousId The id of the item after which the new item should be
     *        added.
     */
    IMPORT_C void AddMenuItemL(const CEikMenuPaneItem::SData& aMenuItem, 
                               TInt aPreviousId);
    
    /**
     * Adds menu items dynamically by creating new menu items from resource 
     * and inserts them into the pane's menu item array. 
     * 
     * @param aResourceId The ID of the resource for the menu item.
     * @param aPreviousId The ID of the previous menu item, after which this 
     *        newly created item should be added.
     * @param aAddSeperator Shouldn't be used as separator is not not supported
     *        anymore.
     */
    IMPORT_C void AddMenuItemsL(TInt aResourceId, 
                                TInt aPreviousId = 0,
                                TBool aAddSeperator = EFalse);
    
    /**
     * Deletes the specified item in the menu pane.
     * 
     * @param aCommandId The ID for the item to be deleted.
     */
    IMPORT_C void DeleteMenuItem(TInt aCommandId);
    
    /**
     * Deletes the items between specified items.
     * 
     * @param aStartIndex The index of the item after which items should be 
     *        deleted.
     * @param aEndIndex The index of the item up to which items should be 
     *        deleted.
     */
    IMPORT_C void DeleteBetweenMenuItems(TInt aStartIndex, 
                                         TInt aEndIndex);
    
    /**
     * Gets a reference to the data in the specified menu item.
     * 
     * @param aCommandId The command ID of the menu item for which data is 
     *        obtained.
     * @return Reference to struct that contains command id.
     */
    IMPORT_C CEikMenuPaneItem::SData& ItemData(TInt aCommandId);
    
    /**
     * Gets a pointer to the specified menu item. Also gets the position of the
     * item within the menu pane. Panics if there are no menu items in the menu
     * pane. Panics if the menu pane id does not identify any menu pane item in
     * the array.
     * 
     * @param aCommandId The ID of the menu item for which a pointer is 
     *        returned. 
     * @param aPos On return, the position of the menu item with an ID of 
     *        aCommandId.
     * @return A pointer to the menu item.
     * @panic EEikPanicNoSuchMenuItem Panics if there are no menu items in the
     *                                menu pane or if the menu pane id does not
     *                                identify any menu pane item in the array.
     */
    IMPORT_C CEikMenuPaneItem* ItemAndPos(TInt aCommandId,TInt& aPos);
    
    /**
     * Displays the menu pane with the corner identified by @c aTargetType in 
     * the position specified by @c aTargetPos. This function uses @c 
     * aMinTitleWidth to calculate the area required to display the menu pane,
     * taking into account whether the menu is a cascading menu or popup menu.
     * 
     * @param aHotKeyTable Optional hotkey table. 
     * @param aTargetPos Position of the corner of the menu pane identified by 
     *        @c aTargetType. 
     * @param aMenuPaneTitle The menu pane's title.
     * @param aMinWidth Minimum width of the menu's title.
     * @param aTargetType The corner of the menu pane to which @c aTargetPos 
     *        relates. The default is the top left corner. Possible: @c 
     *        EPopupTargetTopLeft, @c EPopupTargetTopRight, 
     *        @cEPopupTargetBottomLeft, @c EPopupTargetBottomRight.
     */
    IMPORT_C void StartDisplayingMenuPane(
            const CEikHotKeyTable* aHotKeyTable,                               
            const TPoint& aTargetPos, 
            const CEikMenuPaneTitle* aMenuPaneTitle,
            TInt aMinWidth,  
            TPopupTargetPosType aTargetType = EPopupTargetTopLeft);
            
    /**
     * Sets the text in a menu item.
     * 
     * @param aCommandId The command (as defined in an .hrh file) associated
     *        with this menu item. This identifies the menu item whose text is
     *        to be set. 
     * @param aDes New item text.
     */                                      
    IMPORT_C void SetItemTextL(TInt aCommandId,
                               const TDesC& aDes);
    
    /**
     * Sets the text in a menu item from resource.
     *
     * @param aCommandId The command (as defined in an .hrh file) associated 
     *        with this menu item. This identifies the menu item whose text is
     *        to be set. 
     * @param aRid The resource ID of the menu item text. 
     */
    IMPORT_C void SetItemTextL(TInt aCommandId,
                               TInt aRid);
                               
    /**
     * Dims (greys out) or undims a menu item. Dimming indicates that user 
     * input is not accepted.
     * 
     * @param aCommandId The command (as defined in an .hrh file) associated
     *        with this menu item. This identifies the menu item whose text is
     *        to be dimmed or un-dimmed. 
     * @param aDimmed @c ETrue to dim this menu item. @c EFalse to un-dim this
     *        menu item.
     */
    IMPORT_C void SetItemDimmed(TInt aCommandId,
                                TBool aDimmed);
                                
    /**
     * Sets the item to be indicated or not. It should be used to change the
     * state of radio buttons or check box items. It has real effect only 
     * starting from S60 v3.0.
     * 
     * @param aCommandId The command (as defined in an .hrh file) associated 
     *        with this menu item. This identifies the menu item for which the 
     *        state is set or unset. 
     * @param aButtonState should be @c EEikMenuItemSymbolOn or @c
     *        EEikMenuItemSymbolIndeterminate
     */                           
    IMPORT_C void SetItemButtonState(TInt aCommandId,
                                     TInt aButtonState);
    
    /**
     * Sets the selected menu item.
     * 
     * @param aSelectedItem The index of the item to get selected
     */                                
    IMPORT_C void SetSelectedItem(TInt aSelectedItem);
    
    /**
     * Gets the position of the selected menu item.
     * 
     * @return The position of the selected menu item.
     */
    IMPORT_C TInt SelectedItem() const;
    
    /**
     * Closes and destroys any current cascade menu and takes focus back. Does
     * nothing if no cascade menu exists.
     */
    IMPORT_C void CloseCascadeMenu();
    
    /**
     * Sets the array containing the list of menu items for the current menu 
     * pane.
     * 
     * @param aItemArray The menu item array for the menu pane.
     */
    IMPORT_C void SetItemArray(CItemArray* aItemArray);
    
    /**
     * Set menu item array ownership.
     * 
     * @param aOwnedExternally If @c ETrue the menu pane's menu item array is 
     *        set as externally owned. If @c EFalse the menu pane's menu item 
     *        array is set as not externally owned.
     */
    IMPORT_C void SetItemArrayOwnedExternally(TBool aOwnedExternally);
    
    /**
     * Sets the specified button to launch the menu pane. Doesn't have any 
     * effect in current implementation.
     * 
     * @param aButton The button to set as launching the menu.
     */
    IMPORT_C void SetLaunchingButton(CEikButtonBase* aButton);
    
    /**
     * Moves the menu pane highlight to a newly selected menu item identified
     * by @c aNewSelectedItem. Scrolls the menu to show the new selected item
     * if necessary and redraws only the newly selected item and the currently
     * selected item if possible.
     * 
     * @param aNewSelectedItem The newly selected menu item index.
     */
    IMPORT_C void MoveHighlightTo(TInt aNewSelectedItem);
    
    /**
     * Gets the number of menu items within the menu pane.
     *
     * @return Number of menu items within menu pane.
     */
    IMPORT_C TInt NumberOfItemsInPane() const;
    
    /**
     * Closes the menu pane.
     */
    IMPORT_C void Close();
    
    /**
     * From @ CCoeControl
     *
     * Handles key events offered to the menu by the control environment.
     * 
     * @since Platform 004.
     * @param aKeyEvent The key event.
     * @param aType The type of key event: @c EEventKey, @c EEventKeyUp or @c
     *        EEventKeyDown. 
     * @param aConsumeAllKeys If @c ETrue this function returns @c 
     *        EKeyWasConsumed regardless of whether it was used. If @c EFalse
     *        the key event is consumed if possible and either @c 
     *        EKeyWasConsumed or @c EKeyWasNotConsumed is returned as 
     *        appropriate.
     */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                         TEventCode aType,
                                         TBool aConsumeAllKeys); // not available before Platform 004
    
    /**
     * Sets whether the scroll bar occupies the left side of the menu pane.
     * 
     * @param aOnLeft If @c ETrue the scroll bar will occupy the left side of
     *        the menu pane.
     */                                     
    IMPORT_C void SetScrollBarOnLeft(TBool aOnLeft);
    
    /**
     * Sets whether the menu pane uses an arrow head scroll bar.
     * 
     * @param aArrowHead If @c ETrue the menu pane uses an arrow head scroll 
     *        bar.
     */
    IMPORT_C void SetArrowHeadScrollBar(TBool aArrowHead);
    
// new for AVKON
    
    /**
     * Moves highlight to the next item or to the first one if last item is 
     * selected. 
     */
    IMPORT_C void NavigateToNextItem();
    
    /**
     * Inserts the menu item to the specified position.
     * 
     * @param aMenuItem The menu item to add. NOTICE @c SData is the structure
     *        and all fileds should be initialized.
     * @param aPosition The position of newly created item in the array.
     */
    IMPORT_C void InsertMenuItemL(const CEikMenuPaneItem::SData& aMenuItem, 
                                  TInt aPosition);
    
    /**
     * Checks whether menu pane contains the menu item and returns position of
     * it if the item is found.
     * 
     * @param[in] aCommandId The command ID of the item to be searched for.
     * @param[out] aPosition On return contains position of the item.
     * @return @c ETrue if item was found. Otherwise @c EFalse.
     */
    IMPORT_C TBool MenuItemExists(TInt aCommandId, 
                                  TInt& aPosition);
    
    /**
     * Checks whether the menu pane is a cascade menu or a main menu. 
     *
     * @return @c ETrue if the menu pane is cascade menu and @c EFalse if the
     *         menu pane is the main menu.
     */
    IMPORT_C TBool IsCascadeMenuPane() const;
    
    /**
     * Enables or disables text scrolling functionality. It is disabled by 
     * default.
     * 
     * @param aEnable @c ETrue to enable text scrolling functionality.
     */
    IMPORT_C void EnableMarqueeL(const TBool aEnable); 

    /**
     * Report that selection was done for the currently highlighted item.
     */
    void ActivateCurrentItemL();
    
    /**
     * Closes cascade menu if there is one and it is active.
     */
    TBool CancelActiveMenuPane();
    
    /**
     * Deletes dimmed items from the menu item array.
     */
    void FilterDimmedItems();

    /**
     * Gets the menu pane for the cascade menu.
     *
     * @return The menu pane for the cascade menu.
     */
    IMPORT_C CEikMenuPane* CascadeMenuPane();
    
    /**
     * Gets a reference to the data in the specified menu item.
     * 
     * @since S60 3.1
     * @param aItemIndex The index of the item in the items array.
     * @return The menu item's data.
     * @leave  KErrArgument Wrong @aItemIndex.
     */
    IMPORT_C CEikMenuPaneItem::SData& ItemDataByIndexL(TInt aItemIndex);

    /**
     * Creates and enables a special characters row to be used in the edit 
     * menu.
     *
     * @since S60 3.1 
     * @param aSpecialChars Buffer that holds the selected characters after 
     *                      user has selected them.
     */
    IMPORT_C void ConstructMenuSctRowL( TDes& aSpecialChars );

    /**
     * Returns the command id of the specified menu item. The function panics
     * if aIndex doesn't exist or is out of range.
     * @param aIndex The index of the menu item for which the command ID is returned.
     * @since 3.1
     */
    IMPORT_C TInt MenuItemCommandId( TInt aIndex ) const;

    /**
     * Creates and enables a special characters row to be used in the edit menu.
     * The special character row is constructed from the given special character table.
     *
     * @param aSpecialChars Buffer that holds the selected characters after 
     * user has selected them.
     * @param aResourceId The special character table resource id to define the 
     * characters in the row.
     *
     * @since S60 3.1
     */
    IMPORT_C void ConstructMenuSctRowL( TDes& aSpecialChars, TInt aResourceId );

    /**
     * Creates and enables a special characters row to be used in the edit menu.
     * The special character row is constructed from the given special character dialog.
     *
     * @param aSpecialChars Buffer that holds the selected characters after 
     * user has selected them.
     * @param aResourceId The special character dialog  resource id that contains a special character table
     *
     * @since S60 3.2
     */
    IMPORT_C void ConstructMenuSctRowFromDialogL( TDes& aSpecialChars, TInt aResourceId );

    /**
     * Creates and enables a special characters row to be used in the edit menu.
     * The special character row is constructed from the given special character dialog.
     *
     * @param aCharCase the charcase used by menu sct
     * @param aSpecialChars Buffer that holds the selected characters after
     * user has selected them.
     * @param aResourceId The special character dialog  resource id that contains a special character table
     *
     * @since S60 3.2
     */
    IMPORT_C void ConstructMenuSctRowFromDialogL( TInt aCharCase, TDes& aSpecialChars, TInt aResourceId );

    /**
     * Sets menu item as item specific command.
     * 
     * @param aCommandId The command associated with this menu item.
     * @param aItemSpecific ETrue to define the menu item item specific,
     * EFalse otherwise.
     */
    IMPORT_C void SetItemSpecific( TInt aCommandId, TBool aItemSpecific );

    /**
     * Sets the embedded cba to options menu
     *
     * @param aCba Cba to embed to menu
     * 
     * @since S60 v5.2
     */
    void SetEmbeddedCba( CEikCba* aCba );

    /**
     * Closes and destroys any current cascade menu and takes focus back. Does
     * nothing if no cascade menu exists.
     * 
     * @param aMainMenuClosing ETrue if main menu is also to be closed.
     */
    void CloseCascadeMenu( TBool aMainMenuClosing );

    /**
     * Symbian two-phased constructor for menu panes that are created for
     * item specific menus.
     * 
     * @internal
     * @since S60 v5.2
     * @return Created menu pane. Ownership transfers to caller.
     */
    static CEikMenuPane* NewItemCommandMenuL( MEikMenuObserver* aObserver );

    /**
     * Sets item specific commands dimmed.
     * 
     * @internal
     * @since S60 v5.2
     */
    void SetItemCommandsDimmed();

    /**
     * Adds menu items to this menu and item action menu data. 
     * 
     * @internal
     * @since S60 v5.2
     * @param aMenuData Item action menu data.
     */
    void AddMenuItemsToItemActionMenuL(
            CAknItemActionMenuData& aMenuData );

    /**
     * Adds cascade menu items to item action menu data.
     * 
     * @internal
     * @since S60 v5.2
     * @param aCascadeId Cascade menu id.
     * @param aItemSpecific If ETrue, adds only item specific items.
     * @param aMenuData Item action menu data.
     */
    void AddCascadeMenuItemsToActionMenuL(
            TInt aCascadeId,
            TBool aItemSpecific,
            CAknItemActionMenuData& aMenuData );
    
    /**
     * Enables the default highlight in menu
     */
    void SetDefaultHighlight();
    
private:
    enum { EInvalidCurrentSize=0x01, EBackgroundFaded=0x02 };
    
private: // new functions
    TRect CalculateSizeAndPosition() ;
    enum THighlightType {ENoHighlight,EDrawHighlight,ERemoveHighlight};
    void DrawItem( TInt aItem, THighlightType aHighlight ) const;
    void DrawItem(CWindowGc& aGc,TInt aItem, THighlightType aHighlight) const;
    void ReportSelectionMadeL( TBool aAbortTransition = ETrue );
    void ReportCanceled();
    void LaunchCascadeMenuL(TInt aCascadeMenuId);
    void DoLaunchCascadeMenuL(TInt aCascadeMenuId);
    void TryLaunchCascadeMenuL(const CEikMenuPaneItem& aItem);
    void PrepareGcForDrawingItems(CGraphicsContext& aGc) const;
    TBool ItemArrayOwnedExternally() const;
    TBool IsHotKeyL(const TInt modifiers,const TInt aCode);
    TBool MoveToItemL(TInt aCode, TInt aModifiers);
    void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);
    void CreateScrollBarFrame();
    void UpdateScrollBar();
    void DoUpdateScrollBarL();
    void UpdateScrollBarThumbs();
    static TInt UpdateScrollBarCallBackL(TAny* aObj);
    TRect ViewRect() const;
    TInt TotalItemHeight() const;
    void ScrollToMakeItemVisible(TInt aItemIndex);
    void Scroll(TInt aAmount);
    TBool CheckCreateScroller();
    void CheckCreateScrollerL();
    void ResetItemArray();
    void CreateItemArrayL();
    void CreateIconFromResourceL(TResourceReader& aReader, CEikMenuPaneItem& aItem) const;

    // Skin support for menu
    void UpdateBackgroundContext(const TRect& aWindowRect);

    // Support method for highlight animation
    void RepaintHighlight() const;

private: // from CCoeControl
    IMPORT_C void Reserved_1();
    IMPORT_C void Reserved_2();

private : // new functions
    void LoadCascadeBitmapL() ;

    // Support for check mark, from v3.0
    void LoadCheckMarkBitmapL();
    TBool MenuHasCheckBoxOn() const;
    // Support for radio button, from v3.0
    void LoadRadioButtonBitmapL();
    TBool IsItemMemberOfRadioButtonGroup(TInt aItem) const ;
    // for drawing,from v3.0
    TBool MenuHasIcon() const;

    TRect CalculateSizeAndPositionScalable( const TRect& aWindowRect, TInt aNumItemsInPane ) ;
    TRect HighlightRect() const;
    void PrepareHighlightFrame() const;
    void SetCascadedIconSize() const;

    // fixes marquee flickering
    friend class CAknMarqueeControl;
    
    CEikMenuPaneExtension* Extension() const;
    
    /**
     * Creates menu pane's extension object if it doesn't exist yet.
     */
    void CheckCreateExtensionL();
    
    /**
     * Calculates the rectangle occupied by an item.
	 *
	 * @param aItemIndex Item's index.
	 * @return Item's rectangle.
     */
    TRect ItemRect( TInt aItemIndex ) const;
    
    /**
     * Calculates the height of menu items.
	 *
	 * @return Item height.
     */
    TInt CalculateItemHeight() const;

protected: // from CoeControl

    /**
     * From @c CCoeControl.
     *
     * Retrieves an object of the same type as that encapsulated in aId. Other
     * than in the case where @c NULL is returned, the object returned must be 
     * of the same object type - that is, the @c ETypeId member of the object
     * pointed to by the pointer returned by this function must be equal to the
     * @c iUid member of @c aId.
     *
     * @since SDK 7.0s
     * @param aId An encapsulated object type ID.
     * @return Encapsulates the pointer to the object provided. Note that the 
     *         encapsulated pointer may be @c NULL.
     */
    IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

public: // From CoeControl.
    
    /**
     * From @c CoeControl.
     *
     * Gets the number of controls contained in a compound control. This 
     * function should be implemented by all compound controls.
     * 
     * Note: 
     * In SDK 6.1 this was changed from protected to public.
     * 
     * @return The number of component controls contained by this control.
     */
    IMPORT_C TInt CountComponentControls() const;
    
    /**
     * From @c CoeControl.
     *
     * Gets the specified component of a compound control. This function should?
     * be implemented by all compound controls.
     *
     * Note:
     * Within a compound control, each component control is identified by an 
     * index, where the index depends on the order the controls were added: the
     * first is given an index of 0, the next an index of 1, and so on.
     *
     * @param[in, out] aIndex The index of the control to get.
     * @return The component control with an index of @c aIndex.
     */
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
    
protected: // new functions

    /**
     * Gets the maximum number of items which can be seen simultaneously.
     *
     * @return The maximum number of items which can be seen simultaneously.
     */
    TInt NumberOfItemsThatFitInView() const;
    
private: // data
    friend class CEikMenuButton;
    MEikMenuObserver* iMenuObserver;
    MEikMenuObserver* iEditMenuObserver;
    CEikMenuPane* iCascadeMenuPane;
    const CEikMenuPaneTitle* iMenuPaneTitle;
    const CEikHotKeyTable* iHotKeyTable;
    CEikMenuPane* iOwner;
    CItemArray* iItemArray;
    TBool iArrayOwnedExternally;
    TBool iAllowPointerUpEvents;
    TInt iNumberOfDragEvents;
    TInt iSelectedItem;
    TInt iItemHeight;
    TInt iBaseLine;
    TInt iHotkeyColWidth;
    TInt iFlags;
    CEikScrollBarFrame* iSBFrame;
    CMenuScroller* iScroller;
    CEikButtonBase* iLaunchingButton; // for popouts only
    TInt iSubPopupWidth; // 0..2
    TInt iSpare;
    CEikMenuPaneExtension* iExtension;

    };

#endif

