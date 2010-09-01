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


#if !defined(__EIKMENUB_H__)
#define __EIKMENUB_H__

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKMENUP_H__)
#include <eikmenup.h>
#endif

#include <eikbtgpc.h>
#include <eikcmobs.h>
#include <aknintermediate.h>

class CEikHotKeyTable;
class CEikMenuBarExtension;
class CAknItemActionMenu;


/**
 * The CEikMenuBarTitle class encapsulates the data needed to define a menu bar title and
 * provides some of the functionality required to display the title.
 *
 * @since ER5U
 */
class CEikMenuBarTitle : public CBase
	{
public:
    /**
     * Defines a menu bar. See also @c MEikMenuObserver::DynInitMenuPaneL(). 
     * See also @c MENU_TITLE for details of the resource interface to menu 
     * items.
     */
	struct SData
		{
        enum { 
            /** Nominal legth of the text. */
            ENominalTextLength=40 
            };
        /** 
         * The resource ID from which the menu pane is constructed.
         */
		TInt iMenuPaneResourceId;
        /** 
         * The text to display on the menu pane.
         */
		TBuf<ENominalTextLength> iText; // less than this actually stored
		};
public:
    /**
     * C++ default constructor.
     */
	IMPORT_C CEikMenuBarTitle();
    /**
     * Destructor.
     */
	IMPORT_C ~CEikMenuBarTitle();
    /** 
     * Sets the title icon.
     *
     * @param aIcon The icon to set.
     */
	IMPORT_C void SetIcon(CGulIcon* aIcon);

    /** 
     * Sets whether the bitmap and mask are owned externally or not.
     *
     * @param aOwnedExternally @c ETrue if bitmaps are set as externally owned. 
     *        @c EFalse if bitmaps are set as not being externally owned. 
     */
	IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);

    /** 
     * Draws the title icon to the graphics context @c aGc, inside the rect @c 
     * aRect with an offset from the left side of the rectangle of size @c  
     * aLeftMargin.
     *
     * @param aGc Window graphic context.
     * @param aRect Rectangle area.
     * @param aLeftMargin Left margin.
     */
	IMPORT_C void DrawIcon(CWindowGc& aGc, TRect aRect, TInt aLeftMargin) const;

    /** 
     * Constructs a new icon for the title, taking ownership of the picture 
     * bitmap and the mask bitmap unless they are externally owned.
     *
     * @param aBitmap Bitmap.
     * @param aMask Mask of the bitmap.
     */
	IMPORT_C void CreateIconL(CFbsBitmap* aBitmap, CFbsBitmap* aMask);

    /** 
     * Sets the bitmap for the icon. Transfers 
     * ownership unless the bitmaps are owned externally.
     *
     * @param aBitmap Bitmap
     */	
	IMPORT_C void SetIconBitmapL(CFbsBitmap* aBitmap);

    /** 
     * Sets the bitmap mask for the icon. Transfers ownership 
     * unless the bitmaps are owned externally.
     *
     * @param aMask Mask of a bitmap.
     */	
	IMPORT_C void SetIconMaskL(CFbsBitmap* aMask);

    /** 
     * Gets a pointer to the title icon’s bitmap. Does not imply transfer of
     * ownership.
     *
     * @return Pointer to the title icon’s bitmap.
     */
	IMPORT_C CFbsBitmap* IconBitmap() const;

    /** 
     * Gets a pointer to the title icon’s bitmap mask. Does not imply transfer
     * of ownership.
     *
     * @return Pointer to the title icon’s bitmap mask. 
     */
	IMPORT_C CFbsBitmap* IconMask() const;

public: // other functions

    /** 
     * Gets the value of the extra left margin for the title text which will
     * take into account the width of the title icon.
     *
     * @return Value of extra left margin.
     */
	TInt ExtraLeftMargin() const;

    /** 
     * Adjusts the value of the title text baseline offset @c aBaseLine to take
     * into account any size of the title icon.
     *
     * @param[in,out] aBaseLine Gets result of baseline.
     * @param[in,out] aTitleHeight Gets result of height.
     */	
	void CalculateBaseLine(TInt& aBaseLine, TInt& aTitleHeight);
	
public:

    /** The title’s position on the menu bar. */
	TInt iPos;

    /** The title’s width. */
	TInt iWidth;

    /** The menu bar title text. */
	SData iData;

    /** Flags used internally by the menu bar title. */
	TInt iTitleFlags;
	
private:
	CGulIcon* iIcon;
	};

/**
 * Menu bars are constructed from @c MENU_BAR resources and issue application
 * commands which should be handled by overriding @c 
 * CEikAppUi::HandleCommandL().
 */
class CEikMenuBar : public CEikBorderedControl, 
                    public MEikCommandObserver, 
                    public MAknIntermediateState
	{
	
public:

    /** 
     * Declares an object type for a class, in order to allow the object
     * provider mechanism to locate and provide objects from the class.
     */
	DECLARE_TYPE_ID(0x101F4106)

	/** Specifies the menu item within the menu pane. */
	struct SCursor
		{
		/** Index of a title in the menu bar. */
		TInt iMenuPaneIndex;
		
		/** Index of an item in a menu pane. */
		TInt iMenuItemIndex;
		};

    /**  */
	struct SPosition
		{
		/**  */
		TInt iMenuId;
		
		/**  */
		SCursor iMenuCursorPos;
		};

    enum TMenuType {
        /** 
         *  Options menu launched from the Options softkey. 
         *  This is the default value.
         */
        EMenuOptions = 0,
        
        /** 
         *  Context sensitive menu that is launched from selection key 
         *  when the application supports it.
         */
        EMenuContext = 1,
        
        /** 
         *  Edit menu containing editing specific items.
         */
        EMenuEdit = 2,
        
        /** 
         *  Options menu launched from the Options softkey. Task swapper item
         *  is not shown.
         */
        EMenuOptionsNoTaskSwapper = 3
        };

	friend class CEikMenuPaneTitle;
	
private:
	
	enum {ENothingSelected=-1};
	
public:

    /**
     * Destructor.
     */
	IMPORT_C ~CEikMenuBar();
	
    /**
     * C++ default constructor.
     */
	IMPORT_C CEikMenuBar();
	
public: // framework

    /**
     * From @c CCoeControl
     * 
     * Handles key events offered to the menu by the control environment and
     * provides an appropriate implementation of 
     * @c CCoeControl::OfferKeyEventL(). 
     *
     * @param aKeyEvent The key event. 
     * @param aType The type of key event: @c EEventKey, @c EEventKeyUp or @c
     * EEventKeyDown. 
     *
     * @return Indicates whether or not the key event was used by this control.
     */
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
	                                     TEventCode aType);

    /**
     * From @c CCoeControl
     * 
     * Handles pointer events. This function gets called whenever a pointer 
     * event occurs in the control, i.e. when the pointer is within the 
     * control's extent, or when the control has grabbed the pointer. The 
     * control should implement this function to handle pointer events.
     * 
     * Note: events of type @c EButton1Down are processed before @c
     * HandlePointerEventL() is called, in order to transfer keyboard focus to 
     * the control in which the @c EButton1Down event occurred.
     *
     * If overriding @c HandlePointerEventL(), the implementation must include 
     * a base call to @c CCoeControl's @c HandlePointerEventL().
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    /** 
     * From @c CCoeControl
     * 
     * Not implemented.
     *
     * @param Not used.
     */
    IMPORT_C void Draw(const TRect& aRect) const;
	
private:

    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private: // from MCoeInputObserver

	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
	
public:

     /**
      *  This class enables construction, and destruction of an array of
      *  information about menu bar titles.
      */
	class CTitleArray : public CArrayPtrFlat<CEikMenuBarTitle>
		{
		
	public:
	
		/**
		 * Destructor.
		 */
		IMPORT_C ~CTitleArray();
		
        /**
         * C++ default constructor.
         */	
		IMPORT_C CTitleArray();
		
        /** 
         * Adds the menu bar title @c aMenuTitle to the end of the array owned
         * by the menu bar and transfers ownership.
         *
         * @param aMenuTitle Append object to flat array.
         */				
		IMPORT_C void AddTitleL(CEikMenuBarTitle* aMenuTitle);

        /** 
         * Deletes selected index into array.
         *
         * @param aResource Array index that will be delete.
         */		
		void DeleteResource(TInt aResource);
		};

public: // new functions

    /** 
     * Second phase constructor for a menu bar. 
     *
     * @param aMenuObserver The menu's observer. 
     * @param aHotKeyResourceId The ID of the resource, of type HOTKEY from 
     *        which the hotkey table is created. This is optional. By default
     *        it's nil.
     * @param aMenuTitleResourceId The ID of the resource, of type @c MENU_BAR 
     *        from which the menu title array is created. This is optional. By 
     *        default it's nil.
     */
		
	IMPORT_C void ConstructL(MEikMenuObserver* aMenuObserver,
	                         TInt aHotKeyResourceId=0,
	                         TInt aMenuTitleResourceId=0);

    /** 
     * Second phase constructor for a menu bar which builds the menu bar from
     * the given resource file. 
     *
     * @param aReader The resource reader. 
     */		
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    /** 
     * Not implemented
     *
     * @param aHotKeyResourceId Not used.
     * @param aMenuTitleResourceId Not used.
     * @param aDisplayNow Not used.
     */		
    IMPORT_C void ChangeMenuBarL(TInt aHotKeyResourceId=0,
                                 TInt aMenuTitleResourceId=0,
                                 TInt aDisplayNow=ETrue);

    /** 
     * Not implemented!
     *
     * @param aHotKeyTable Not used.
     * @return  NULL.
     */
    IMPORT_C CEikHotKeyTable* SetHotKeyTable(CEikHotKeyTable* aHotKeyTable);

    /** 
     * Sets the menu’s resource ID.
     * 
     * @param aMenuTitleResourceId The ID of the resource to use.
     */
    IMPORT_C void SetMenuTitleResourceId(TInt aMenuTitleResourceId);
    
    /**
    *
    *
    * @param aMenuTitleResourceId
    */
	IMPORT_C void SetContextMenuTitleResourceId(TInt aMenuTitleResourceId);
		
    /** 
     * Not implemented.
     *
     * @param aTitleArray Not used. 
     */
    IMPORT_C void SetMenuTitleArray(CTitleArray* aTitleArray);

    /** 
     * Not implemented.
     *
     * @param aOwnedExternally Not used.
     */
    IMPORT_C void SetTitleArrayOwnedExternally(TBool aOwnedExternally);

    /** 
     * Sets the cursor to the specifed menu pane and menu item.
     *
     * @param aCursor The menu pane and menu item to which the cursor is set.
     * @return A @c SCursor structure holding the menu item within the menu
     *         pane.
     */
    IMPORT_C SCursor SetMenuCursor(const SCursor& aCursor);

    /** 
     * Stops displaying the menu bar.
     * 
     * This function causes the menu bar to disappear from the screen until it
     * is invoked again by the user. In most circumstances this is done by the 
     * @c Uikon framework, so an application program will not normally need to 
     * use this function.
     */
    IMPORT_C void StopDisplayingMenuBar();

    /** 
     * Displays the menu bar.
     *
     * If the menu is not already displayed, this function displays the menu
     * bar and allows the user to make a selection. In most circumstances this
     * is done by the @c Uikon framework, so an application program will not 
     * normally need to use this function.
     */
    IMPORT_C void TryDisplayMenuBarL();
	IMPORT_C void TryDisplayContextMenuBarL();
    /**
     * If the menu is not already displayed, this function displays the menu
     * bar without fep menu and allows the user to make a selection. In most
     * circumstances this is done by the @c Uikon framework, so an application 
     * program will not normally need to use this function.
     */
    IMPORT_C void TryDisplayMenuBarWithoutFepMenusL();

    /** 
     * Not implemented.
     *
     * @param aNewSelectedTitle Not used
     * @param aNewSelectedItem Not used.
     */	
    IMPORT_C void MoveHighlightToL(TInt aNewSelectedTitle,
                                   TInt aNewSelectedItem=0);

    /** 
     * Not implemented. 
     *
     * @param aItem Not used. 
     */	
    IMPORT_C void DrawItem(TInt aItem) const;

    /** 
     * Gets a pointer to the menu’s hot key table. 
     */	
    CEikHotKeyTable* HotKeyTable() const { return(iHotKeyTable); }

    /** 
     * Gets the index of the menu pane selected by the cursor.
     *
     * @return The index of the selected menu pane.
     */	
    IMPORT_C TInt SelectedTitle();

    /** 
     * Gets the index of the menu item selected by the cursor.
     *
     * @return The index of the selected menu item.
     */	
    IMPORT_C TInt SelectedItem();

    /** 
     * Searches for the menu item that corresponds to the specified command.
     *
     * @param aCommandId The ID to search for. 
     * @param aPaneindex Menu pane index.
     * @param aItemindex Menu item index.
     */	
    IMPORT_C virtual void FindCommandIdInResourceL(TInt aCommandId,
                                                   TInt& aPaneindex,
                                                   TInt& aItemindex);

    /** 
     * Gets a menu pane resource.
     *
     * @return The pointer to @c CEikMenuPane object containing a menu pane 
     * resource.
     */	
    IMPORT_C CEikMenuPane* MenuPane();

    /** 
     * If the menu bar is visible, removes the menu bar height from the top of
     * @c aRect and returns the new rectangle in a new value of @c aRect. 
     *
     * @param[in,out] aRect A rectangle that on return is reduced in height by
     *                the height of the menu bar.
     */	
    IMPORT_C void ReduceRect(TRect& aRect) const;

    /** 
     * Gets array of information about the menu bar titles.
     *
     * @return Pointer to @c CTitleArray object containing array of information 
     *         about menu bar titles.
     */	
    IMPORT_C CTitleArray* TitleArray();

    /** 
     * Sets menu observer interface.
     *
     * @param aEditMenuObserver Menu observer interface.
     */	
    IMPORT_C void SetEditMenuObserver(MEikMenuObserver* aEditMenuObserver);

    /** 
     * Sets the menu observer interface to @c NULL.
     *
     * @param aEditMenuObserver Menu observer interface that will be set to @c
     *        NULL.
     */	
    IMPORT_C void RemoveEditMenuObserver(MEikMenuObserver* aEditMenuObserver);
 
    /** 
     * Allows the client to determine if the menubar instance is displayed.
     *
     * @return @c Etrue if displayed and @c EFalse if not.
     */
    IMPORT_C TBool IsDisplayed();

    /**
    * Sets type of the menu. Menu can be for example Options menu launched from 
    * Options softkey or context sensitive menu launched from the selection key.
    * By default the launched menu is options menu.
    * @since S60 3.1
    * @param aMenuType One of values of CEikMenuBar::TMenuType enumeration. 
    */
    IMPORT_C void SetMenuType(TMenuType aMenuType);
    
    /**
    * Gets type of the menu. 
    * 
    * @since S60 5.2
    * @return the type defined in CEikMenuBar::TMenuType of menu.
    */    
    IMPORT_C CEikMenuBar::TMenuType GetMenuType() const;    

    /**
     * Returns ETrue when item specific commands are enabled in menu
     * bar (main pane collection has a highlight) and EFalse when they are
     * disabled (main pane collection does not have a highlight). 
     * 
     * @since S60 5.2
     * @return ETrue when item specific commands are enabled.
     */
    IMPORT_C TBool ItemSpecificCommandsEnabled() const;
    
    /**
     * Sets item action menu instance to menu bar.
     * 
     * @internal
     * @since S60 v5.2
     * @param aItemActionMenu Pointer to item action menu.
     */
    void SetItemActionMenu( CAknItemActionMenu* aItemActionMenu );

    /**
     * Provides pointer to item action menu.
     * 
     * @internal
     * @since S60 v5.2
     * @return Pointer to item action menu.
     */
    CAknItemActionMenu* ItemActionMenu() const;

    /**
     * Populates item action menu.
     * 
     * @internal
     * @since S60 v5.2
     * @param aItemActionMenu Reference to item action menu.
     * @return Created menu pane. Ownership transfers to caller.
     */
    CEikMenuPane* PopulateItemActionMenuL( CAknItemActionMenu& aItemActionMenu );

private: // from MAknIntermediateState

	void CloseState();
	
public:	// from CCoeControl

    /** 
     * From @c CCoeControl.
     *
     * Gets the list of logical colours used to draw the control. 
     *
     * The list includes an explanation of how each colour is used. By default,
     * this function has an empty implementation. 
     *
     * @since 5.1 SDK.
     * @param aColorUseList The colour list.
     */
    IMPORT_C virtual void GetColorUseListL(
	    CArrayFix<TCoeColorUse>& aColorUseList) const; 
	
	/** 
     * From @c CCoeControl.
     *
     * Handles a change to the control's resources. 
     *
     * The types of resources handled are those which are shared across the
     * environment, e.g. colours or fonts. 
     *
     * @since 5.1 SDK.
     * @param aType A message UID value. The most common is @c 
     *        KEikMessageColorSchemeChange which controls get when the colour 
     *        scheme is changed. Other examples include: @c 
     *        KEikMessageFadeAllWindows, @c KEikMessageUnfadeWindows, @c 
     *        KEikMessageZoomChange, @c KEikMessageVirtualCursorStateChange, @c
     *        KEikMessageCapsLock, @c KEikMessagePrepareForSave.
     */
	IMPORT_C virtual void HandleResourceChange(TInt aType);			

private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
	// from MEikCommandObserver
	void ProcessCommandL(TInt aCommandId);
private: // from MObjectProvider
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private:
	void StartDisplayingMenuBarL();
	void HideMenuPane();
	void SaveCurrentMenuPositionL();
	void SetCursorPositionFromArray();
	TBool MenuHasItems() const;
	void SetMenuHasItems();
	TBool MenuHasPane() const;
	void SetMenuHasPane();
	TBool TitleArrayOwnedExternally() const;
	void ResetTitleArray();
	void CreateTitleArrayL();
	void SetMenuPaneFlag(TInt aFlag);
	void AddFEPMenuL();
	void AddMenuIfNotPresentL(TInt aResourceId);
	void UpdateTitleTextBaseline();
private:
	enum TEikMenuFlags {ETitleArrayOwnedExternally=0x01,EMenuHasItems=0x02,EMenuHasPane=0x04,EBackgroundFaded=0x08, ESoundsInstalled=0x10};
	CEikButtonGroupContainer* iMenuCba;
	MEikMenuObserver* iMenuObserver;
	MEikMenuObserver* iEditMenuObserver;
	MEikMenuObserver* iActiveEditMenuObserver;
	CEikMenuPane* iMenuPane;
 	CEikHotKeyTable* iHotKeyTable;
	SCursor iCursor;
	TInt iMenuTitleResourceId;
	TInt iMenuPaneResourceId;
	TInt iMenuHotKeyResourceId;
	TInt iSelectedTitle;
	TInt iBaseLine;
	TInt iMenuTitleLeftSpace;
	TInt iMenuFlags;
	CTitleArray* iTitleArray;
	CArrayFixFlat<SPosition>* iPastMenuPosArray;
	TBool iPreventFepMenu;
	friend class CEikMenuBarExtension;
	CEikMenuBarExtension* iExt;
	};

 /**
  *  This class is not intended to be used by application programmers.
  */
class CEikMenuPaneTitle : public CEikBorderedControl
	{
	
public:

    /**
     * Default C++ constructor
     */
	IMPORT_C CEikMenuPaneTitle(CEikMenuBar* aMenuBar);
	
	/** 
     * Second phase constructor for a menu bar. By default Symbian 2nd phase
     * constructor is private.
     */	
	IMPORT_C void ConstructL();
	
	/** 
     * Not implemented
     *
     * @param aSelectedTitle Not used.
     */	
	IMPORT_C void SetSelectedTitle(TInt aSelectedTitle);
	
	/** 
     * Not implemented
     *
     * @param aRect Not used.
     */	
	IMPORT_C void Draw(const TRect& aRect) const;
    
	/** 
     * Gets the menu pane title’s margins.
     *
     * @return The menu pane title’s margins.
     */    
    IMPORT_C TMargins Margins() const;
	
	/** 
     * Not implemented
     */	
	IMPORT_C void Close();
	
public:// framework

    /**
     * Not implemented.
     *
     * @param aPointerEvent Not used.
     */
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

	/** 
     * From @c CCoeControl.
     *
     * Gets the list of logical colours used to draw the control. 
     *
     * The list includes an explanation of how each colour is used. By default,
     * this function has an empty implementation. 
     *
     * Since 5.1 SDK.
     *
     * @param aColorUseList The colour list.
     */
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

	/** 
     * Not implemented
     *
     * @param aType Not used.
     */
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	CEikMenuBar* const iMenuBar;
	TInt iSelectedTitle;
	};

#endif
