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
* Description:  The event handler to handle events of list box in dialog.
*
*/



#ifndef C_AKNMEMORYSELECTIONEVENTHANDLER_H
#define C_AKNMEMORYSELECTIONEVENTHANDLER_H


#include <e32base.h>

#include "MAknCommonDialogsEventObserver.h"

class MAknMemorySelectionModel;
class MAknMemorySelectionObserver;
class MAknMemorySelectionDriveObserver;
class CCoeEnv;
class CActiveDriveMonitor;
class CActiveRemotePropertySubscriber;

/**
 *  A class that handles events reported from an UI class in memory selection.
 *
 *  @lib CommonDialogs.lib
 *  @since S60 1.2
 */
NONSHARABLE_CLASS(CAknMemorySelectionEventHandler)
    : public CBase,
      public MAknCommonDialogsEventObserver
    {
public:

// Constructors and destructors

    /**
     * Static constructor.
     * Do not use aObserver parameter, useless now.
     *
     * @param aCoeEnv A pointer to control environment.
     * @param aModel A pointer to memory selection model.
     * @param aObserver A pointer to an observer which is asked if the
     *                  selected item can be selected.
     * @return Returns a pointer to an instance of itself.
     */
    static CAknMemorySelectionEventHandler* NewL(
        CCoeEnv* aCoeEnv,
        MAknMemorySelectionModel* aModel,
        MAknMemorySelectionObserver* aObserver );


    ~CAknMemorySelectionEventHandler();

// Functions from base classes

    /**
     * From MAknCommonEventObserver.
     */
    TAction HandleEventL(
        TEvent aEvent,
        TInt& aFocusedItemIndex,
        TInt& aTopItemIndex,
        CEikButtonGroupContainer* aContainer );

// New functions

    /**
     * Start to listen NotifyDisk & activate the AO
     */
    void StartNotifyDisk(
        MAknMemorySelectionDriveObserver* aMemoryCardObserver,
        TBool aHasRemoteDrive = EFalse );

    /**
     * Stop listening NotifyDisk & deactivate the AO
     */
    void StopNotifyDisk();

private:

// Constructors and destructors

    void ConstructL();

    /**
     * Constructor.
     * @param aCoeEnv A pointer to control environment.
     * @param aModel A pointer to memory selection model.
     * @param aObserver A pointer to an observer which is
     *        asked if the selected item can be selected.
     */
    CAknMemorySelectionEventHandler(
        CCoeEnv* aCoeEnv,
        MAknMemorySelectionModel* aModel,
        MAknMemorySelectionObserver* aObserver );

// New methods

    /**
     * Displays password query dialog.
     * @param aPwd Descriptor where the entered password is stored.
     * @param aResourceId A resource id for query dialog.
     * @return Returns query dialog return value.
     */
    TInt ShowSimplePwdQueryL( TDes& aPwd, TInt aResourceId ) const;

    /**
     * Converts 16-bit descriptor to 8-bit password descriptor.
     * @param aWord Password that user entered.
     * @param aConverted Converted 8-bit password descriptor.
     */
    void ConvertCharsToPwd( TDesC& aWord, TDes8& aConverted ) const;

    /**
     * Tries to unlock the MMC with given password.
     * @param aPswd MMC password.
     */
    TBool UnlockMMC( TMediaPassword& aPswd ) const;

    /**
     * Launches password requester and tries to unlock drive.
     * @return Returns ETrue if drive was unlocked.
     * @param aDrive The drive to be unlocked.
     */
    TBool TryToUnlockDriveL( TDriveNumber aDrive );

private:    // Data

    // Ref: Control environment
    CCoeEnv* iCoeEnv;

    // Ref: Model
    MAknMemorySelectionModel* iModel;

    /**
    * Ref: Observer, useless when multiple drive supported.
    */
    MAknMemorySelectionObserver* iObserver;

    /**
     * Own: drive's monitor
     */
    CActiveDriveMonitor* iDriveMonitor;
    
    /**
     * Own: subscriber for remote drive's connection
     */
    CActiveRemotePropertySubscriber* iRemotePropertySubscriber;
    
    TBool iCanceledAllActions;
    };

#endif // C_AKNMEMORYSELECTIONEVENTHANDLER_H
