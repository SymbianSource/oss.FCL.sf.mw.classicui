/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Grouped notifier note for soft notifications.
*
*/

#ifndef __AKNGROUPEDNOTIFIERNOTE_H__
#define __AKNGROUPEDNOTIFIERNOTE_H__

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknstaticnotedialog.h>
#include <eikcmobs.h>               // for MEikCommandObserver
#include <AknQueryDialog.h>
#include <aknlistquerydialog.h>
#include "AknSystemPopup.h"         // for MAknKeyLockObserver

// FORWARD DECLARATIONS
class MAknKeyLockController;
class MAknKeyLockObserver;

// DATA TYPES
enum TAknGroupedNotifierItem
    {
    EMissedCalls = 0,
    ENewMessages,
    ENewChatMsgs,
    ENewMails,
    EMaxItem
    };
    
// CONSTANTS
const TInt KAknMaxGroupedNoteItemTextLength = 50;    

// CLASS DECLARATIONS

/**
 * Mixin class for the grouped soft notification dialog callback.
 *
 * @lib aknoldstylenotif.lib
 */
class MAknGroupedNotifierNoteObserver
    {
public:
    /**
     * This method is called when the note is completed (either by accepting or discarding 
     * the note).
     *
     * @param aCommandId The id of the button the user pressed.
     * @param aSelectedItem The selected item enum when the note has been accepted or EMaxItem 
     *                      if it has been discarded
     */
    virtual void GroupedNoteCompletedL(
        TInt aCommandId,
        TAknGroupedNotifierItem aSelectedItem = EMaxItem) = 0;
    
    /**
     * Support for adding new items to grouped form.
     *
     * @param aTexts Array into which add new texts.
     * @param aOrder Key array for list to manage its entries.
     */    
    virtual void AddItemsL(
        CDesCArray& aTexts, 
        CArrayFix<TInt>& aOrder) = 0;

    /**
     * Custom soft notifications may have custom softkeys. This method returns the softkeys
     * and the accept softkey id for the given custom notification.
     *
     * @since S60 3.1
     * @param aCustomItem A custom notification for which to search softkeys.
     * @param aSoftkeyResourceId On return, the softkeys resource identifier.
     * @param aAcceptKeyId On return, the key that is used to accept the grouped notifier item, 
     *        i.e. to launch the handler application.
     * @param aLeftSoftkey Custom text for left softkey.
     * @param aRightSoftkey Custom text for right softkey.
     */
    virtual void SoftkeysForCustomItem(
        TAknGroupedNotifierItem aCustomItem, 
        TInt& aSoftkeyResourceId, 
        TInt& aAcceptKeyId,
        TDes& aLeftSoftkey,
        TDes& aRightSoftkey) = 0;
    };

/**
 * Grouped soft notification dialog.
 *
 * @lib aknoldstylenotif.lib  
 */
NONSHARABLE_CLASS(CAknGroupedNotifierNote) : public CAknListQueryDialog, public MDesCArray
    {
public: // Constructors and destructor
    /**
     * C++ default constructor.
     */
    CAknGroupedNotifierNote();
            
    /**
     * Destructor.
     */
    virtual ~CAknGroupedNotifierNote();

public: // New functions
    /**
     * Construct method.
     * 
     * @param aNoteObserver The observer to call after the notifier is completed.
     */
    void ConstructL(MAknGroupedNotifierNoteObserver* aNoteObserver);

    /**
     * This method is for setting the number of a certain item - for example, to set the number
     * of missed calls to 7. If an item count is set to 0, the note should check if the list 
     * has less than two items left and if so call the NotifierItemCounteLessThanTwo()-method. 
     
     * @param aItem Missed calls, new messages, new mail or new chat messages.
     * @param aAmount The amount of items specified by aItem.
     * @param aHighlight ETrue to set the item highlighted.
     */
    void SetItemAmountL(TAknGroupedNotifierItem aItem, TInt aAmount, TBool aHighlight = EFalse);

public: // Functions from base classes.
    /**
     * From CEikDialog.
     * This function is called by the dialog framework before the dialog is sized and laid out.
     */
    void PreLayoutDynInitL();
    
    /**
     * From CEikDialog.
     * This function is called by the dialog framework after the dialog has been sized and laid 
     * out, but before it has been activated.
     */    
    void PostLayoutDynInitL();
            
    /**
     * From CCoeControl.
     * Method to be called by framework when keypress occurs
     *
     * @param aKeyEvent The key pressed.
     * @param aType Type of key pressed (EEventKeyUp or EEventKeyDown for instance).
     * @return EKeyWasNotConsumed or EKeyWasConsumed depending whether key was processed or not.
     */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    
    /**
     * From MDesCArray. 
     * Gives number of items inside an array.
     *
     * @return Number of items.
     */
    TInt MdcaCount() const;
    
    /**
     * From MDesCArray.
     * Returns a string from index.
     *
     * @param aIndex The string to be returned.
     * @return The string.
     */
    TPtrC MdcaPoint(TInt aIndex) const; 
    
    /**
     * From CAknListQueryDialog.
     * Handle pointer event.
     */
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
                
protected: // Functions from base classes.
    /**
     * From CEikDialog. 
     * Method to be called when the user presses a softkey.
     *
     * @param aButtonId The id of the softkey that the user just pressed.
     * @return ETrue if exit is to be performed, EFalse if not.
     */
    TBool OkToExitL(TInt aButtonId);

    /**
     * From CCoeControl.
     * Sets the control to be ready for drawing.
     */
    void ActivateL();
    
    /**
     * From CCoeControl
     * Event handling section e.g for Listbox events.
     * @param aControl Pointer to a control.
     * @param aEventType The event type.
     */    
    void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);    

private:
    enum TNoteAction
        {
        EDoNothing = 0,
        ELaunchItemHandler,
        EExitNote
        };

private:
    TBool AutoLockEnabled();
        
    // Methods to handle order of items.
    void RemoveType(TAknGroupedNotifierItem aItem);
    void InsertType(TAknGroupedNotifierItem aItem);
    
    // Sets the correct softkeys depending on the focused item.
    void UpdateSoftkeysL();

    /**
     * From MEikCommandObserver - this method is called by framework when a command is issued.
     */
    virtual void ProcessCommandL(TInt aCommandId);
 
    virtual void CEikDialog_Reserved_1();
    virtual void CEikDialog_Reserved_2();   
    virtual void CAknDialog_Reserved();
    virtual void CAknQueryDialog_Reserved();

private: // Data
    MAknGroupedNotifierNoteObserver* iNoteObserver;
    TInt iCount[EMaxItem]; // how many calls etc. 
    CArrayFix<TInt> *iOrder; // which order are these. (ownership)
    CDesCArray *iTexts; // (ownership)
    CDesCArray *iTextsPlural; // (ownership)
    __MUTABLE TBuf<KAknMaxGroupedNoteItemTextLength> iBuffer;
    TInt iSelectedItem;
    TInt iHighlightedItem;
    
    // Dynamic softkeys for currently focused custom grouped notifier item.
    TInt iCustomNoteSoftkeys; 
    
    // Accept softkey for currently focused custom grouped notifier item.
    TInt iCustomNoteAcceptKeyId;
    
    // Whether custom softkeys were used on previously focused notifier item
    TBool iCustomNoteSoftkeysAssigned;
    
    TInt iAutoLockStatus;
    };

#endif // __AKNGROUPEDNOTIFIERNOTE_H__
            
// End of File
