/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Popup list used to display memory selection dialog
*                and file selection dialog.
 *
*/


#ifndef CAKNCOMMONDIALOGSPOPUPLIST_H
#define CAKNCOMMONDIALOGSPOPUPLIST_H

// INCLUDES
#include <aknPopup.h>
#include "CAknCommonDialogsBase.h"
#include "MAknCommonDialogsEventObserver.h"
#include "maknmemoryselectiondriveobserver.h"

// FORWARD DECLARATIONS
class CEikListBox;

//  CLASS DEFINITION
/**
 *  A class derived from CAknPopupList in order to catch events and report
 *  them to the event handler.
 *
 *  @lib CommonDialogs.lib
 *  @since 1.2
 */
NONSHARABLE_CLASS(CAknCommonDialogsPopupList) : public CAknPopupList,
public MAknMemorySelectionDriveObserver
    {
public: // Constructors and destructor

    /**
     * Static constructor.
     * @param aObserver An observer to which events are reported.
     * @param aListBox A parameter for CAknPopupList.
     * @param aType A parameter for CAknPopupList.
     * @param aIsEndKeyPress Get call termination key event.
     * @return Returns a pointer to an instance of itself.
     */
    static CAknCommonDialogsPopupList* NewL(
            MAknCommonDialogsEventObserver& aObserver,
            CEikListBox* aListBox,
            AknPopupLayouts::TAknPopupLayouts aType,
            TBool& aIsEndKeyPress );

    ~CAknCommonDialogsPopupList();

    /**
     * From MAknMemoryCardInsertObserver
     * Update popuplist with new memory names
     * @param aItemArray Memory names from memory selection model
     */
    virtual void NotifyDrivesChangedL(const MDesCArray* aItemArray);

    /**
     * From CCoeControl. To handle the Pointer events.
     * @param aPointerEvent The Pointer event details.
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

private: // Constructors

    /**
     * Second phase construction.
     * @param aListBox A parameter for CAknPopupList.
     * @param aType A parameter for CAknPopupList.
     */
    void ConstructL(
            CEikListBox* aListBox,
            AknPopupLayouts::TAknPopupLayouts aType );

    /**
     * Constructor.
     * @param aObserver An observer to which events are reported.
     * @param aIsEndKeyPress Get call termination key event
     */
    CAknCommonDialogsPopupList( MAknCommonDialogsEventObserver& aObserver,
            TBool& aIsEndKeyPress );

private: // Functions from base classes 

    /**
     * From CAknPopupList
     */
    void ProcessCommandL( TInt aCommandId );

    /**
     * From CAknPopupList
     */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

    /**
     * From CAknPopupList
     */
    void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);

private: // New functions

    /**
     * Implements reporting events to event handler.
     * @param aEvent The event to report.
     * @return Returns ETrue if it is allowed to exit popup.
     */
    TBool ReportPopupEventL( MAknCommonDialogsEventObserver::TEvent aEvent );

    /**
     * Updates the listbox and the pop-up list after listbox items have changed.
     * @param aFocus Focus of the current item.
     * @param aTopIndex Index of the topmost item.
     */
    void UpdateItemsAndRedrawPopupL( TInt aFocus, TInt aTopIndex );

    /**
     * Processes the highlight change event of listbox
     * @param aListBox Listbox being observed.
     */
    void HandleListBoxHighlightChangedL( CEikListBox* aListBox );

private: // Data

    // Ref: Observer to report events
    MAknCommonDialogsEventObserver& iObserver;
    
    // Ref: Get EndCall key event
    TBool& iEndKey;

    };

#endif // CAKNCOMMONDIALOGSPOPUPLIST_H
// End of File
