/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Support for Avkon Popped-up lists
*
*
*/


#if !defined(__AKNPOPUP_H__)
#define __AKNPOPUP_H__

#include <coecntrl.h>
#include <eikcmobs.h>
#include <eiklbx.h>
#include <aknpopuplayout.h>
#include <aknintermediate.h>
#include <AknPopupFader.h>

class CAknPopupHeadingPane;
class CEikButtonGroupContainer;
class CEikListBox;
class CAknSearchField;
class CAknPopupListExtension;

/** Used to popup a list or grid. Takes an existing listbox control and
 *  puts it into a popup frame together with an optional title.
 *
 * @c CAknPopupList is not a dialog!
 *
 * There are two standard usages of @c CAknPopupList:
 *
 * @code 
 *  CAknPopupList *plist = CAknPopupList::NewL(...);
 *  CleanupStack::PushL(plist);
 *  ...
 *  TInt popupOk = plist->ExecuteLD(...);
 *  // No leaving functions allowed between ExecuteLD and
 *  // CleanupStack::Pop().
 *  CleanupStack::Pop(); // plist
 *  if (popupOk) { ... } else { ... } 
 * @endcode
 *
 * And then another way:
 * @code
 *  iPList = CAknPopupList::NewL(...);
 *  ...
 *  TInt popupOk = iPlist->ExecuteLD(...);
 *  // No leaving functions allowed between ExecuteLD and iPlist=NULL;
 *  iPlist = NULL;
 *  if (popupOk) {... } else {... }
 *  // note, destructor deletes the iPlist instance.
 * @endcode
 * 
 * Both these work corretly and leave-safe way. Notice this usage is pretty
 * different of how dialogs work. With dialogs you _always_ want to do 
 * @c CleanupStack::Pop() before calling @c ExecuteLD().
 */
class CAknPopupList : public CEikBorderedControl,
                      public MEikCommandObserver,
                      public MEikListBoxObserver,
                      public MCoeControlObserver,
                      public MAknIntermediateState,
                      public MAknFadedComponent
    {
public:	// enums 

    DECLARE_TYPE_ID(0x20018439)

public:

    /**
     * Two-phased constructor.
     *
     * Creates the pop-up list.
     *
     * @param aListBox Pre-existing listbox-derived class.
     * @param aCbaResource Softkey pane to display while pop-up is active.
     * @param aType The layout used.
     * @return A pointer to a pop-up list object.
     */
    IMPORT_C static CAknPopupList* NewL( 
       CEikListBox* aListBox, 
       TInt aCbaResource,
       AknPopupLayouts::TAknPopupLayouts aType = AknPopupLayouts::EMenuWindow);

    /**
     * Executes the pop-up selection list. Function returns when the user have
     * accepted or cancelled the pop-up.
     *
     * @return @c ETrue if the popup was accepted. @c EFalse if 
     *            the popup was cancelled.
     */
	IMPORT_C TBool ExecuteLD();

    /**
     * Sets the title for the selection list.
     *
     * @param aTitle Title to be displayed.
     */
    IMPORT_C void SetTitleL(const TDesC& aTitle);

    /**
     * Cancels the current popup. The popup @c ExecuteLD will return with 
     * @c EFalse.
     */
	IMPORT_C void CancelPopup();
public: // Access methods

    /**
     * Gets a button group container.
     *
     * @return The button group.
     */
	IMPORT_C CEikButtonGroupContainer* ButtonGroupContainer();
    /**
     * Gets the popup header.
     *
     * @return Header properties of the pop-up menu.
     */
	IMPORT_C CAknPopupHeadingPane* Heading();

    /**
     * Gets the popup header.
     *
     * @return Header properties of the pop-up menu.
     */
	IMPORT_C CAknPopupHeadingPane* Heading() const;

    /**
     * Gets the list box.
     *
     * @return The list box.
     */
	IMPORT_C CEikListBox* ListBox();
	
    /**
     * Sets the maximum height for the popup frame.
     *
     * @param aItems The maximum height.
     */
	IMPORT_C void SetMaximumHeight(TInt aItems);

    /**
     * Enables the findbox of the popup list.
     *
     * @param aEnable Enables (default) or disables the findbox.
     * @return @c ETrue if enabling/disabling was successfull.
     */
    IMPORT_C TBool EnableFind(TBool aEnable=ETrue);

    /**
     * Enables the findbox with adaptive search of the popup list.
     *
     * @since 5.0
     * @param aEnable Enables (default) or disables the adaptive findbox.
     * @return @c ETrue if enabling/disabling was successfull.
     */
    IMPORT_C TBool EnableAdaptiveFind(TBool aEnable=ETrue);

    /**
     * Gets the search field control.
     *
     * @return Search field control.
     */
    IMPORT_C CAknSearchField* FindBox() const;
public:
    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events of popups.
     *
     * @param aPointerEvent Pointer event to be handled.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
protected:
    /**
     * From @c MEikCommandObserver.
     *
     * Processes events from the softkeys. Responds to @c EAknSoftkeyOk and 
     * @c EAknSoftkeyBack to accept or cancel the pop-up.
     *
     * @param aCommandId Event Id from the soft-key.
     */
    IMPORT_C void ProcessCommandL(TInt aCommandId);

    /**
     * From @c MEikListBoxObserver.
     *
     * Processes key events from the listbox. Responds to 
     * @c EEventEnterKeyPressed to accept the pop-up.
     *
     * @param aListBox Listbox being observed.
     * @param aEventType Event being observed.
     */
    IMPORT_C void HandleListBoxEventL(CEikListBox* aListBox, 
                                      TListBoxEvent aEventType);
    /**
     * From @c MCoeControlObserver.
     *
     * Handles an event from an observed control.
     *
     * @param aControl Control being observed.
     * @param aEventType Event observed.
     */
    IMPORT_C void HandleControlEventL(CCoeControl* aControl,
                                      TCoeEvent aEventType);
protected:

    /**
     * C++ default constructor.
     */
    IMPORT_C CAknPopupList();

    /**
     * Destructor.
     */
    IMPORT_C ~CAknPopupList();

    /**
     * Handles 2nd phase construction.
     * 
     * @param aListBox Pre-existing listbox-derived class.
     * @param aCbaResource Softkey pane to display while pop-up is active.
     * @param aType The layout used.
     */
    IMPORT_C void ConstructL(CEikListBox* aListBox, 
                             TInt aCbaResource,
                             AknPopupLayouts::TAknPopupLayouts aType );

    /**
     * Called when the user accepts or cancels the listbox.
     *
     * @param aAccept @c ETrue if the user has accepted, @c EFalse if the user 
     *                   has cancelled the listbox.
     */
    IMPORT_C virtual void AttemptExitL(TBool aAccept);

    /**
     * Setup the whole window layout; window position, grid and heading 
     * position, shadow for the window.
     *
     * @param aType A choice of layout.  
     */
    IMPORT_C virtual void SetupWindowLayout(
                                     AknPopupLayouts::TAknPopupLayouts aType);

    /** 
     * Returns the listbox being used.
     *
     * @return Listbox contained in the pop-up.
     */
    IMPORT_C CEikListBox* ListBox() const;

    /**
     * Gets the layout definitions for the popup list.
     *
     * @return Collects all LAF specification lines that are needed for popup 
     *         windows.
     */
    IMPORT_C const TAknPopupWindowLayoutDef& Layout() const;

    /**
     * Gets the layout definitions for the popup list.
     *
     * @return Collects all LAF specification lines that are needed for popup 
     *         windows.
     */
    IMPORT_C TAknPopupWindowLayoutDef& Layout();

protected:

    /**
     * From @c MopSupplyObject.
     *
     * Retrieves an object of the same type as that encapsulated in @c aId.
     *
     * @param aId Encapsulated object type ID.
     * @return Encapsulates the pointer to the object provided.
     *         Note that the encapsulated pointer may be NULL.
     */
    IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

protected:

    /**
     * From @c CCoeControl.
     *
     * Handles a change to the control's resources.
     *
     * @param aType A message UID value.
     */
    IMPORT_C void HandleResourceChange(TInt aType);

protected:
	IMPORT_C void FadeBehindPopup(TBool aFade);



private:
	// the following needs to be imported, because they need to be
	// used in virtual table of any derived class.
	IMPORT_C TSize MinimumSize();
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
	                                     TEventCode aType);
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);

	IMPORT_C void CloseState();
	// From MAknFadedComponent
	IMPORT_C virtual TInt CountFadedComponents();
	IMPORT_C virtual CCoeControl* FadedComponent(TInt aIndex);

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
	void RemoveFindFiltering();

protected: // these are protected to allow overriding virtual functions.
	CEikListBox*				iListBox;
    
    /**
     * A button group container - a wrapper around the different button 
     * arrays.
     */
    CEikButtonGroupContainer* iPopoutCba;
    
    /** 
     * Header control for queries. Defines properties of the header of the 
     * pop-up menu.
     */
    CAknPopupHeadingPane* iTitle;
    
    /** The address to hold the return value from the popup */
    TBool* iReturn;
    
    /**  */
    TBool iMarkable;
    
    /**  */
    TInt iCurrentResource;
    
    /** Popup layout type. */
	AknPopupLayouts::TAknPopupLayouts iWindowType;
    
    /**
     * collects all LAF specification lines that are needed for popup window.
     */
    TAknPopupWindowLayoutDef iLayout;


    /**  */
    TBool iAppBroughtForwards;
    
    /**  */
    TAknPopupFader iPopupFader;
    
    /**  */
    CIdle *iIdle;


    /**  */
	CActiveSchedulerWait iWait;		// owned, safe to use as direct member data.
private:
    CAknPopupListExtension* iPopupListExtension;    // owned
	};

#endif



