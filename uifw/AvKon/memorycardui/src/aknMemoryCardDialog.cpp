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
* Description:  The dialog used to unlock memory card
*
*/



#include <stringresourcereader.h>
#include <AknGlobalNote.h>
#include <avkon.rsg>
#include <pathinfo.h>
#include <f32file.h>

#include "aknmemorycarddialog.h"

_LIT(KResFileName,         "z:\\resource\\avkon.rsc");

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// NotifierArray
// ---------------------------------------------------------------------------
//
EXPORT_C   CArrayPtr<MEikSrvNotifierBase2>* NotifierArray()
    {
    return 0;
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknMemoryCardDialog::NewLC
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemoryCardDialog* CAknMemoryCardDialog::NewLC(
    MAknMemoryCardDialogObserver* aObserver)
    {
    CAknMemoryCardDialog* self =
        new (ELeave) CAknMemoryCardDialog( aObserver );
    CleanupStack::PushL(self);

    // Locked (i.e. password protected) memory card support disabled / enabled.
    // Variation made with __MMC_LOCK feature flag.
    TInt lockedMMCsupported = EFalse;
#ifdef __MMC_LOCK
    lockedMMCsupported = ETrue;
#endif
    self->ConstructL( lockedMMCsupported );
    return self;
    }

// ---------------------------------------------------------------------------
// CAknMemoryCardDialog::UnlockCardLD
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemoryCardDialog::UnlockCardLD(TBool aStore)
    {
#ifdef _DEBUG
    RDebug::Print(_L("CAknMemoryCardDialog::UnlockCardLD"));
#endif

    CleanupStack::Pop(); //this
    iStore = aStore;

    TPath mmcRootPath = PathInfo::MemoryCardRootPath();
    TDriveUnit unit( mmcRootPath );
    TDriveNumber defaultMMCDrive = TDriveNumber( TInt( unit ) );
    StartL( defaultMMCDrive );
    }

// ---------------------------------------------------------------------------
// CAknMemoryCardDialog::SetSelfPointer
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemoryCardDialog::SetSelfPointer(
    CAknMemoryCardDialog** aSelf)
    {
    iSelf = aSelf;
    }


// ---------------------------------------------------------------------------
// C++ constructor
// ---------------------------------------------------------------------------
//
CAknMemoryCardDialog::CAknMemoryCardDialog(
    MAknMemoryCardDialogObserver* aObserver)
    : CActive(CActive::EPriorityLow),
      iObserver(aObserver)
    {
    CActiveScheduler::Add( this );
    }

// ---------------------------------------------------------------------------
// Symbian C++ constructor
// ---------------------------------------------------------------------------
//
void CAknMemoryCardDialog::ConstructL( TBool aUnlock )
    {
    iStubInUse = !aUnlock;
    }

// ---------------------------------------------------------------------------
// C++ destructor
// ---------------------------------------------------------------------------
//
CAknMemoryCardDialog::~CAknMemoryCardDialog()
    {
    iBoolDeletingAlready = ETrue;

    Cancel();

    if ( iSelf )
        {
        ( *iSelf ) = 0;
        }

    iAknCapServerClient.Close();
    if ( !iObserverNotified && iObserver )
        {
        iObserver->UnlockComplete( KErrCancel );
        }
    }

// ---------------------------------------------------------------------------
// From CActive
// ---------------------------------------------------------------------------
//
void CAknMemoryCardDialog::DoCancel()
    {
    iAknCapServerClient.CancelUnlockMedia();
    if ( !iBoolDeletingAlready )
        {
        delete this;
        }
    }

// ---------------------------------------------------------------------------
// From CActive
// ---------------------------------------------------------------------------
//
void CAknMemoryCardDialog::RunL()
    {
    NotifyObserverAndExit( iStatus.Int() );
    }

// ---------------------------------------------------------------------------
// CAknMemoryCardDialog::StartL
// ---------------------------------------------------------------------------
//
void CAknMemoryCardDialog::StartL( TDriveNumber& aDrive )
    {
    if ( IsActive() )
        return;

    if ( !iStubInUse )
        {
        iAknCapServerClient.UnlockMedia( aDrive, iStore, iStatus );
        SetActive();
        }
    else
        {
        CAknGlobalNote*note = CAknGlobalNote::NewLC();
        // load Note text
        TFileName resourceFile = KResFileName();
        CStringResourceReader* reader =
            CStringResourceReader::NewLC(resourceFile);
        HBufC* noteText =
            reader->ReadResourceString(R_AKN_LOCKED_MEMORY_CARD_NOT_SUPPORTED)
            .AllocLC();
            
        // ignore return value            
        note->ShowNoteL( EAknGlobalInformationNote, *noteText );
        
        CleanupStack::PopAndDestroy(3); // note, reader and text

        SetActive();
        TRequestStatus* ptr = &iStatus;
        User::RequestComplete( ptr, KErrCancel );
        }
    }

// ---------------------------------------------------------------------------
// CAknMemoryCardDialog::NotifyObserverAndExit
// ---------------------------------------------------------------------------
//
void CAknMemoryCardDialog::NotifyObserverAndExit( TInt aResult ) const
    {
    // ugly const cast..
    ((CAknMemoryCardDialog*)this)->iObserverNotified = ETrue; 
    
    if ( iObserver )
        {
#ifdef _DEBUG
        RDebug::Print(_L("CAknMemoryCardDialog::UnlockComplete: %D"), aResult);
#endif
        iObserver->UnlockComplete(aResult);
        }
        
    if ( !iBoolDeletingAlready )
        {
        delete this;
        }
    }

// ---------------------------------------------------------------------------
// CAknMemoryCardDialog::UnlockCardLD
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemoryCardDialog::UnlockCardLD(
    TDriveNumber& aDrive, TBool aStore)
    {
#ifdef _DEBUG
    RDebug::Print(_L("CAknMemoryCardDialog::UnlockCardLD"));
#endif

    CleanupStack::Pop(); //this
    iStore = aStore;

    StartL( aDrive );
    }
