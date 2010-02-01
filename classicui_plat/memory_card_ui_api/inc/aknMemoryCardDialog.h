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
* Description:  Dialog used to unlock MMC drive.
*
*/



#ifndef C_AKNMEMORYCARDDIALOG_H
#define C_AKNMEMORYCARDDIALOG_H

#include <eiknotapi.h> // to be removed
#include <AknCapServerClient.h>
#include <e32std.h>

// To preserve BC, FOR NOW; to be removed
IMPORT_C CArrayPtr<MEikSrvNotifierBase2>* NotifierArray();

/**
 * An abstract interface class for user of CAknMemoryCardDialog
 *
 * Operation of unlocking MMC is asynchronous. So user of CAknMemoryCardDialog
 * should implement a method UnlockComplete in a class inherited from
 * MAknMemoryCardDialogObserver. UnlockComplete will be called after unlocking
 * operation is ended.
 *
 * @lib AknMemoryCardUi.lib
 * @since S60 1.2
 */
class MAknMemoryCardDialogObserver
    {
public:
    /**
     * Implement this method to be notified when the memory card
     * unlock operation is complete. aResult contains the result
     * of the unlock operation:-
     *
     * @return Error code
     *         KErrNone on success
     *         KErrCancel if the dialog has been canceled
     *         Any other standard system error codes, see SDK for details
     */
    virtual void UnlockComplete( TInt aResult ) = 0;
    };

/**
 * Display a memory card dialog and unlock the memory card.
 * Do not delete instances of this class, memory is
 * automatically released.
 *
 * Usage example:-
 *
 * CAknMemoryCardDialog* dlg = CAknMemoryCardDialog::NewLC();
 * dlg->UnlockCardLD();
 *
 * @lib AknMemoryCardUi.dll
 * @since S60 1.2
 */
NONSHARABLE_CLASS(CAknMemoryCardDialog) : public CActive
  {
public:
   /**
    * Create an instance of CAknMemoryCardDialog.
    *
    * The pointer is put on the cleanup stack.
    *
    * @param aObserver      An implementation of MAknMemoryCardDialogObserver.
    *                       This is needed if the application wants to be
    *                       notified when the unlock operation is complete.
    * @return               An instance of CAknMemoryCardDialog
    */
    IMPORT_C static CAknMemoryCardDialog* NewLC(
        MAknMemoryCardDialogObserver* aObserver = NULL );

    /**
     * Unlock the default Multimedia Memory Card.
     *
     * Display a text query dialog requesting the password.
     * Unlock the MMC using the password entered by the user
     * in this dialog (unless the dialog is cancelled).
     * If the password is wrong display the dialog again with
     * a different prompt. This call is asynchronous, the
     * application should not assume that the card has been
     * unlocked when this function returns. In fact,
     * when this function returns the dialog is still
     * displaying. If the application needs to be notified
     * when the unlock operation is complete, it should implement
     * UnlockComplete. Memory for this class is automatically
     * released when the unlock operation is complete.
     * The application should therefore not delete this object.
     *
     * @param aStore        store passwd
     *
     */
    IMPORT_C void UnlockCardLD( TBool aStore = ETrue );

    /**
     * Unlock the specified Multimedia Memory Card.
     *
     * Display a text query dialog requesting the password.
     * Unlock the MMC using the password entered by the user
     * in this dialog (unless the dialog is cancelled).
     * If the password is wrong display the dialog again with
     * a different prompt. This call is asynchronous, the
     * application should not assume that the card has been
     * unlocked when this function returns. In fact,
     * when this function returns the dialog is still
     * displaying. If the application needs to be notified
     * when the unlock operation is complete, it should implement
     * UnlockComplete. Memory for this class is automatically
     * released when the unlock operation is complete.
     * The application should therefore not delete this object.
     *
     * @since S60 5.0
     * @param aDrive        The drive to be unlocked.
     * @param aStore        store passwd
     *
     */
    IMPORT_C void UnlockCardLD( TDriveNumber& aDrive, TBool aStore = ETrue);

    /**
    * Adds address to owners pointer. This must not be in stack unless observer
    * will wait inside same method until UnlockComplete is called. Value of
    * given pointer is set to null when dilaog is deleted.
    *
    * The pointer is put on the cleanup stack.
    *
    * @param aSelf  Address of observers pointer pointing to this
    */
    IMPORT_C void SetSelfPointer( CAknMemoryCardDialog** aSelf );

    // Application must not call this unless self pointer correctly set.
    ~CAknMemoryCardDialog();

private:
// Constructors
    CAknMemoryCardDialog( MAknMemoryCardDialogObserver* aObserver = NULL );
    void ConstructL( TBool aUnlock );

// Functions from base class CActive
    void DoCancel(); // will delete this unless we are deleting already
    void RunL();

// New functions
    void StartL( TDriveNumber& aDrive);
    void  NotifyObserverAndExit(TInt aResult) const;

private: // Data

    MAknMemoryCardDialogObserver*  iObserver;
    RAknUiServer                   iAknCapServerClient;
    TBool                          iStore;
    TBool                          iObserverNotified;
    TBool                          iBoolDeletingAlready;
    CAknMemoryCardDialog**         iSelf;
    TBool                          iStubInUse;
    };

#endif //C_AKNMEMORYCARDDIALOG_H
