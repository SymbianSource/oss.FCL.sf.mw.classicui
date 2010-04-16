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
* Description:  ?Description
*
*/


#include <AknQueryDialog.h>
#include <aknnotewrappers.h>
#include <commondialogs.rsg>
#include <aknmemorycarddialog.h>
#include <pathinfo.h> //PathInfo
#include <e32property.h>


#include "CAknMemorySelectionEventHandler.h"
#include "CAknMemorySelectionDialog.h"
#include "MAknMemorySelectionObserver.h"
#include "maknmemoryselectiondriveobserver.h"
#include "maknmemoryselectionmodel.h"
//#include "CAknMemorySelectionModel.h"
#include "AknCFDUtility.h"

// CActiveDriveMonitor for monitoring drive adding or removing.
NONSHARABLE_CLASS(CActiveDriveMonitor) : public CActive,
                                         public MAknMemoryCardDialogObserver
    {

public:

    /**
     * Implement this method to be notified when the memory card
     * unlock operation is complete. aResult contains the result
     * of the unlock operation:-
     *
     * - KErrNone on success
     * - KErrCancel if the dialog has been canceled
     * - Any other standard system error codes, see SDK for details
     */
    void UnlockComplete(TInt aResult)
        {
        iRet = aResult;
        if ( iWait.IsStarted() )
            {
            iWait.AsyncStop();
            }
        }

    void Start()
        {
        iRet = 0;
        iWait.Start();
        }

    CActiveDriveMonitor( MAknMemorySelectionModel* aModel );

    ~CActiveDriveMonitor()
        {
        Cancel();
        delete iDptr; // cancels request if still active
        CAknEnv::StopSchedulerWaitWithBusyMessage(iWait);
        }

    /**
     * Start ActiveObject to listen if a drive is added/removed.
     */
    void StartMonitoring(
        MAknMemorySelectionDriveObserver* aObserver );

    TBool IsStarted() const
        {
        return iWait.IsStarted();
        }

private:
    
    /**
     * Sets file system event
     * @since s60 5.0
     */
    void Setup();
    
protected:

// from base class CActive

    /**
     * From CActive
     */
    void RunL();

    /**
     * From CActive
     */
    void DoCancel();

public: // Data

    CAknMemoryCardDialog* iDptr;
    CActiveSchedulerWait iWait;
    TInt iRet;

    // Ref: Model
    MAknMemorySelectionModel* iModel;

    // Ref: object needed to be notified about drive insertion/deletion
    MAknMemorySelectionDriveObserver* iObserver; // not own
    };

// CActiveRemotePropertySubscriber for listening if remote drive is connected.
NONSHARABLE_CLASS(CActiveRemotePropertySubscriber) : public CActive
    {
public:

    /**
     * NewL function
     */
    static CActiveRemotePropertySubscriber* NewL(
        MAknMemorySelectionModel* aModel );

    /**
     * Destructor
     */
    ~CActiveRemotePropertySubscriber()
        {
        Cancel();
        iProperty.Close();
        }

    /**
     * Start ActiveObject to listen if remote drive is connected.
     */
    void Subscribe( MAknMemorySelectionDriveObserver* aObserver );
    
    
protected:

// from base class CActive

    /**
     * From CActive
     */
    void RunL();

    /**
     * From CActive
     */
    void DoCancel();

private:
    /**
     * C++ Constructor.
     */
    CActiveRemotePropertySubscriber( MAknMemorySelectionModel* aModel );
    
    /**
     * ConstructL function
     */
    void ConstructL();
    
    /**
     * Start ActiveObject
     */
    void Setup();
    
private: // Data

    // Ref: Model
    MAknMemorySelectionModel* iModel;

    // Ref: object needed to be notified
    //      about remote drive connection/disconnection
    MAknMemorySelectionDriveObserver* iObserver; // not own
    
    // Own: PS handle
    RProperty iProperty;
    };

// ============================ MEMBER FUNCTIONS ===============================
// CActiveDriveMonitor

// -----------------------------------------------------------------------------
// C++ constructor
// -----------------------------------------------------------------------------
//
CActiveDriveMonitor::CActiveDriveMonitor( MAknMemorySelectionModel* aModel )
    :CActive( EPriorityStandard ),
     iModel( aModel )
    {
    CActiveScheduler::Add( this );
    }

// ---------------------------------------------------------------------------
// CActiveDriveMonitor::StartMonitoring
//
// ---------------------------------------------------------------------------
//
void CActiveDriveMonitor::StartMonitoring(
        MAknMemorySelectionDriveObserver* aObserver )
    {
    iObserver = aObserver;
    
    Setup();
    }

// ---------------------------------------------------------------------------
// CActiveDriveMonitor::Setup
//
// ---------------------------------------------------------------------------
//
void CActiveDriveMonitor::Setup()
    {
    if ( !IsActive() )
        {
        CEikonEnv::Static()->FsSession().NotifyChange( ENotifyDisk, iStatus );
        SetActive();
        }
    }

// ---------------------------------------------------------------------------
// CActiveDriveMonitor::RunL
//
// -----------------------------------------------------------------------------
//
void CActiveDriveMonitor::RunL()
    {
    TInt status = iStatus.Int();
    Setup();
    
    if ( ( status == KErrNone ) && ( iObserver != NULL ) )
        {
        // Update data arrays in model
        iModel->UpdateDataArraysL();
        // Update memory names in model
        iModel->UpdateItemsL();
        // Notify observer memory card insertion
        iObserver->NotifyDrivesChangedL( iModel );
        }
    }

// -----------------------------------------------------------------------------
// CActiveDriveMonitor::DoCancel
//
// -----------------------------------------------------------------------------
//
void CActiveDriveMonitor::DoCancel()
    {
    CEikonEnv::Static()->FsSession().NotifyChangeCancel();
    iObserver = NULL;
    }


// ============================ MEMBER FUNCTIONS ===============================
// CActiveRemotePropertySubscriber

// -----------------------------------------------------------------------------
// CActiveRemotePropertySubscriber::NewL
// -----------------------------------------------------------------------------
//
CActiveRemotePropertySubscriber* CActiveRemotePropertySubscriber::NewL(
    MAknMemorySelectionModel* aModel )
    {
    CActiveRemotePropertySubscriber* self =
        new ( ELeave ) CActiveRemotePropertySubscriber( aModel );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CActiveRemotePropertySubscriber::Subscribe
// -----------------------------------------------------------------------------
//
void CActiveRemotePropertySubscriber::Subscribe(
        MAknMemorySelectionDriveObserver* aObserver )
    {
    iObserver = aObserver;
    
    Setup();
    }

// -----------------------------------------------------------------------------
// CActiveRemotePropertySubscriber::Setup
// -----------------------------------------------------------------------------
//
void CActiveRemotePropertySubscriber::Setup()
    {
    if ( !IsActive() )
        {
        iProperty.Subscribe( iStatus );
        
        SetActive();
        }
    }

// -----------------------------------------------------------------------------
// C++ constructor
// -----------------------------------------------------------------------------
//
CActiveRemotePropertySubscriber::CActiveRemotePropertySubscriber(
    MAknMemorySelectionModel* aModel )
    :CActive( EPriorityStandard ),
     iModel( aModel )
    {
    }

// -----------------------------------------------------------------------------
// CActiveRemotePropertySubscriber::ConstructL
// -----------------------------------------------------------------------------
//
void CActiveRemotePropertySubscriber::ConstructL()
    {
    CActiveScheduler::Add(this);
    //User::LeaveIfError(
    //    iProperty.Attach( KRfeServerSecureUid, ERsfwPSKeyConnect ) );
    }

// ---------------------------------------------------------------------------
// CActiveRemotePropertySubscriber::RunL
//
// -----------------------------------------------------------------------------
//
void CActiveRemotePropertySubscriber::RunL()
    {
    TInt statusValue = iStatus.Int();
    Setup();
    
    if ( ( statusValue == KErrNone ) && ( iObserver != NULL ) )
        {
        // Update memory names in model
        iModel->UpdateItemsL();
        // Notify observer memory card insertion
        iObserver->NotifyDrivesChangedL( iModel );
        }
    }

// -----------------------------------------------------------------------------
// CActiveRemotePropertySubscriber::DoCancel
//
// -----------------------------------------------------------------------------
//
void CActiveRemotePropertySubscriber::DoCancel()
    {
    iProperty.Cancel();
    iObserver = NULL;
    }


// ============================ MEMBER FUNCTIONS ===============================
// CAknMemorySelectionEventHandler
// -----------------------------------------------------------------------------
// CAknMemorySelectionEventHandler::CAknMemorySelectionEventHandler
//
//
// -----------------------------------------------------------------------------
//
CAknMemorySelectionEventHandler::CAknMemorySelectionEventHandler(
    CCoeEnv* aCoeEnv,
    MAknMemorySelectionModel* aModel,
    MAknMemorySelectionObserver* aObserver )
    :   iCoeEnv( aCoeEnv ),
        iModel( aModel ),
        iObserver( aObserver ),
        iCanceledAllActions( EFalse )
    {
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionEventHandler::ConstructL
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionEventHandler::ConstructL()
    {
    iDriveMonitor = new ( ELeave ) CActiveDriveMonitor( iModel );
    iRemotePropertySubscriber = CActiveRemotePropertySubscriber::NewL( iModel );
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionEventHandler::NewL
//
// -----------------------------------------------------------------------------
//
CAknMemorySelectionEventHandler* CAknMemorySelectionEventHandler::NewL(
    CCoeEnv* aCoeEnv,
    MAknMemorySelectionModel* aModel,
    MAknMemorySelectionObserver* aObserver )
    {
    CAknMemorySelectionEventHandler* self =
        new( ELeave ) CAknMemorySelectionEventHandler(
            aCoeEnv, aModel, aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// Destructor
CAknMemorySelectionEventHandler::~CAknMemorySelectionEventHandler()
    {
    if( iDriveMonitor )
        {
        iDriveMonitor->Cancel();
        delete iDriveMonitor;
        iDriveMonitor = NULL;
        }

    if ( iRemotePropertySubscriber )
        {
        iRemotePropertySubscriber->Cancel();
        delete iRemotePropertySubscriber;
        iRemotePropertySubscriber = NULL;
        }
    }


// -----------------------------------------------------------------------------
// CAknMemorySelectionEventHandler::ShowSimplePwdQueryL
//
//
// -----------------------------------------------------------------------------
//
TInt CAknMemorySelectionEventHandler::ShowSimplePwdQueryL( TDes& aPwd, TInt aResourceId ) const
    {
    HBufC* dlgText = iCoeEnv->AllocReadResourceLC( aResourceId );
    CAknTextQueryDialog* pwdDlg = CAknTextQueryDialog::NewL( aPwd );
    TInt ret( pwdDlg->ExecuteLD( R_CFD_PASSWORD_QUERY_DIALOG, *dlgText ) );
    CleanupStack::PopAndDestroy( ); // dlgText
    return ret;
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionEventHandler::ConvertCharsToPwd
//
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionEventHandler::ConvertCharsToPwd( TDesC& aWord, TDes8& aConverted ) const
    {
    // Make sure the target password is empty
    aConverted.FillZ( aConverted.MaxLength() );
    aConverted.Zero();
    if( aWord.Length() )
        {
        // Copy the pwd as raw data
        aConverted.Copy( ( TUint8* ) ( &aWord[ 0 ] ), aWord.Size() );
        }
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionEventHandler::UnlockMMC
//
//
// -----------------------------------------------------------------------------
//
TBool CAknMemorySelectionEventHandler::UnlockMMC( TMediaPassword& aPswd ) const
    {
    // This functions is not used, so why put it here?
    RFs& fs = iCoeEnv->FsSession();
    return fs.UnlockDrive( EDriveE, aPswd, ETrue ) == KErrNone;
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionEventHandler::TryToUnlockDriveL
//
//
// -----------------------------------------------------------------------------
//
TBool CAknMemorySelectionEventHandler::TryToUnlockDriveL(
    TDriveNumber aDrive )
    {
    iDriveMonitor->iDptr = CAknMemoryCardDialog::NewLC( iDriveMonitor );
    iDriveMonitor->iDptr->SetSelfPointer( &( iDriveMonitor->iDptr ) );
    iDriveMonitor->iDptr->UnlockCardLD( aDrive, ETrue );
    iDriveMonitor->Start();

    iDriveMonitor->iDptr = NULL;
    return (iDriveMonitor->iRet == KErrNone);
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionEventHandler::HandleEventL
//
//
// -----------------------------------------------------------------------------
//
MAknCommonDialogsEventObserver::TAction
    CAknMemorySelectionEventHandler::HandleEventL(
        TEvent aEvent,
        TInt& aFocusedItemIndex,
        TInt& /* aTopItemIndex */,
        CEikButtonGroupContainer* aContainer )
    {
    if ( aEvent == ECancelAllActions )
        {
        iCanceledAllActions = ETrue;
        
        if ( iDriveMonitor->iDptr )
            {
            delete iDriveMonitor->iDptr; // eventually stops the activeschedulerwait
            iDriveMonitor->iDptr = NULL;
            return MAknCommonDialogsEventObserver::ECanceled;
            }
        else
            {
            return MAknCommonDialogsEventObserver::EDidNothing;
            }
        }
    // Check status of the highlighted drive
    TBuf<KMaxPath> selectedPath;
    iModel->GetDrive( aFocusedItemIndex, selectedPath );
    TDriveNumber driveNumber(
        TDriveNumber( AknCFDUtility::DriveNumber( selectedPath ) ) );
    TCFDDriveStatus driveStatus =
        AknCFDUtility::DriveStatusL( driveNumber );

    // Return do nothing by default
    MAknCommonDialogsEventObserver::TAction
        action( MAknCommonDialogsEventObserver::EDidNothing );

    switch( aEvent )
        {
        case ESelectionKeyPress:
        case ELeftSoftkeyPress:
        case EEventClicked:
            {
            /*
            if( aFocusedItemIndex == CAknMemorySelectionDialog::EPhoneMemory )
                {
                // Phone memory can be always selected
                action = MAknCommonDialogsEventObserver::ETryingToExit;
                }
            else // Current item is memory card
            */
            if ( driveStatus == EDriveOK )
                {
                // Drive can be selected
                action = MAknCommonDialogsEventObserver::ETryingToExit;
                }
            else if( driveStatus == EDriveNotReady )
                {
                if ( aContainer )
                    {
    	            aContainer->MakeCommandVisible(
	                    aContainer->ButtonGroup()->CommandId( 0 ),
	                    EFalse );
	                aContainer->MakeCommandVisibleByPosition(
	                    CEikButtonGroupContainer::EMiddleSoftkeyPosition,
	                    EFalse );
                    }
                break;
                }
            else if( driveStatus == EDriveLocked )
                {
                // Memory card is locked because only MMC could be locked.
                if ( !iDriveMonitor->IsStarted() )
                    {
                    if( TryToUnlockDriveL( driveNumber ) )
                        {
                        action = MAknCommonDialogsEventObserver::ETryingToExit;
                        }
                    else if( iCanceledAllActions )
                        {
                        action = MAknCommonDialogsEventObserver::ECanceled;
                        }                    
                    }
                }
            break;
            }
        case ERightSoftkeyPress:
            {
            action = MAknCommonDialogsEventObserver::ETryingToExit;
            break;
            }
        case EFocusChange:
            {
            // Solve what left softkey should be
            TBool softkeyShouldBeVisible( ETrue );
            if( driveStatus == EDriveNotReady )
                {
                softkeyShouldBeVisible = EFalse;
                }
            aContainer->MakeCommandVisible(
                aContainer->ButtonGroup()->CommandId( 0 ),
                softkeyShouldBeVisible );
            aContainer->MakeCommandVisibleByPosition(
                CEikButtonGroupContainer::EMiddleSoftkeyPosition,
                softkeyShouldBeVisible );
            break;
            }
        default:
            {
            break;
            }
        }
    // If the item is about to be selected
    if( action == MAknCommonDialogsEventObserver::ETryingToExit &&
        aEvent != MAknCommonDialogsEventObserver::ERightSoftkeyPress )
        {
        if( iObserver ) // If the memory selection observer is set
            {           // ask it's permission to leave from memory selection
            if( !iObserver->OkToExitL(
                CAknMemorySelectionDialog::TMemory( aFocusedItemIndex ) ) )
                {
                action = MAknCommonDialogsEventObserver::EDidNothing;
                }
            }
        }
    return action;
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionEventHandler::StartNotifyDisk
//
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionEventHandler::StartNotifyDisk(
        MAknMemorySelectionDriveObserver* aObserver, TBool aHasRemoteDrive )
    {
    iDriveMonitor->StartMonitoring( aObserver );
    if ( aHasRemoteDrive )
        {
        iRemotePropertySubscriber->Subscribe( aObserver );
        }
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionEventHandler::StopNotifyDisk
//
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionEventHandler::StopNotifyDisk()
    {
    iDriveMonitor->Cancel();
    iRemotePropertySubscriber->Cancel();
    }
//End

