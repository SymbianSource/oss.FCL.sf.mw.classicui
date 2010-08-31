/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  New memory selection setting item to support multiple drives.
*
*/


// INCLUDE FILES
#include <e32std.h>
#include "CAknCFDFileSystemEvent.h"
#include "MAknCFDFileSystemObserver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknCFDFileSystemEvent::CAknCFDFileSystemEvent
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknCFDFileSystemEvent::CAknCFDFileSystemEvent(
        RFs& aFs,
        MAknCFDFileSystemObserver& aObserver,
        TNotifyType aNotifyType ) :
    CActive( CActive::EPriorityLow ),
    iFs( aFs ),
    iObserver( aObserver),
    iNotifyType( aNotifyType )
    {
    }
        
// -----------------------------------------------------------------------------
// CAknCFDFileSystemEvent::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknCFDFileSystemEvent::ConstructL( const TDesC& aFullPath )
    {
    CActiveScheduler::Add( this );

    if ( aFullPath.Length() )
        {
        iFullPath = aFullPath.AllocL();
        }

    Setup();
    }
// -----------------------------------------------------------------------------
// CAknCFDFileSystemEvent::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknCFDFileSystemEvent* CAknCFDFileSystemEvent::NewL(
        RFs& aFs,
        MAknCFDFileSystemObserver& aObserver,
        TNotifyType aNotifyType,
        const TDesC& aFullPath )
    {
    CAknCFDFileSystemEvent* self =
        new( ELeave ) CAknCFDFileSystemEvent( 
            aFs,
            aObserver,
            aNotifyType );

    CleanupStack::PushL( self );
    self->ConstructL( aFullPath );
    CleanupStack::Pop( self );

    return self;
    }

// ------------------------------------------------------------------------------
// CAknCFDFileSystemEvent::~CAknCFDFileSystemEvent
//
// ------------------------------------------------------------------------------
CAknCFDFileSystemEvent::~CAknCFDFileSystemEvent()
    {
    Cancel();
    delete iFullPath;
    }

// -----------------------------------------------------------------------------
// CAknCFDFileSystemEvent::RunL
// From CActive. Called when asynchronous request is completed. 
// Notifies the observer
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknCFDFileSystemEvent::RunL()
    {
    TInt err( iStatus.Int() );

    // Mark as received if there is no error
    if ( err == KErrNone )
        {
        iIsReceived = ETrue;
        }

    // If not ENotifyDisk, do refresh when event is checked
    // using CheckFileSystemEvent
    if ( iNotifyType == ENotifyDisk )
        {
        iObserver.NotifyFileSystemChangedL();
        }
    }

// -----------------------------------------------------------------------------
// CAknCFDFileSystemEvent::RunError
// From CActive. Called when error occurred in asynchronous request
// Notifies the observer
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CAknCFDFileSystemEvent::RunError( TInt /*aError*/ )
    {
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CAknCFDFileSystemEvent::DoCancel
// From CActive. Called when asynchronous request is canceled
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknCFDFileSystemEvent::DoCancel()
    {
    iFs.NotifyChangeCancel( iStatus );
    }

// ------------------------------------------------------------------------------
// CAknCFDFileSystemEvent::Setup
//
// ------------------------------------------------------------------------------
//
void CAknCFDFileSystemEvent::Setup()
    {
    if( IsActive() )
        {
        return;
        }

    iIsReceived = EFalse;

    if( iFullPath )
        {
        iFs.NotifyChange( iNotifyType, iStatus, *iFullPath );
        }
    else
        {
        iFs.NotifyChange( iNotifyType, iStatus );
        }

    SetActive();
    }

// ------------------------------------------------------------------------------
// CAknCFDFileSystemEvent::CheckFileSystemEvent
//
// ------------------------------------------------------------------------------
//
void CAknCFDFileSystemEvent::CheckFileSystemEvent()
    {}

//  End of File
