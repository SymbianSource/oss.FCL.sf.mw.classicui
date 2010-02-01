/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Client API for Dynamic Avkon soft notifications.
*
*/

#include "AknDynamicSoftNotifier.h"
#include "AknDynamicSoftNoteObserver.h"
#include "AknDynamicSoftNoteObserver.h"
#include "AknDynamicNotifier.h"
#include "aknsoftnoteconsts.h"
#include <AknDynamicSoftNotificationParams.h>
#include <AknNotifySignature.h>
#include <aknSDData.h>
#include <AknNotifyStd.h>
#include <s32mem.h>

// CONSTANTS

/// IPC message buffer granularity
const TInt KAknBufferGranularity       = 1024;
/// Observer array granularity
const TInt KAknObserverListGranularity = 4;
/// Priority of cancel message. Value only needs to be in allowed range.
const TInt KAknPriorityOfCancelMessage = 1000;

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::NewL
//-----------------------------------------------------------------------------
//
EXPORT_C CAknDynamicSoftNotifier* CAknDynamicSoftNotifier::NewL()
    {
    CAknDynamicSoftNotifier* self = NewLC();
    CleanupStack::Pop( self );
    return self;
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::NewLC
//-----------------------------------------------------------------------------
//
EXPORT_C CAknDynamicSoftNotifier* CAknDynamicSoftNotifier::NewLC()
    {
    CAknDynamicSoftNotifier * self = new( ELeave ) CAknDynamicSoftNotifier;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::~CAknDynamicSoftNotifier
//-----------------------------------------------------------------------------
//
EXPORT_C CAknDynamicSoftNotifier::~CAknDynamicSoftNotifier()
    {
    iObservers.ResetAndDestroy();
    delete iNotifier;
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::ConstructL
//-----------------------------------------------------------------------------
//
void CAknDynamicSoftNotifier::ConstructL()
    {
    iNotifier = new(ELeave) CAknDynamicNotifier( KAknSoftNotificationUid );
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::CAknDynamicSoftNotifier
//-----------------------------------------------------------------------------
//
CAknDynamicSoftNotifier::CAknDynamicSoftNotifier() :
    iObservers( KAknObserverListGranularity )
    {
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::AddDynamicNotificationL
//-----------------------------------------------------------------------------
//
EXPORT_C TInt CAknDynamicSoftNotifier::AddDynamicNotificationL(
    TAknDynamicSoftNotificationParams& aParams,
    TInt aNoteId, // = KErrUnknown
    TInt aCount ) // = 1
    {
    return SendMessageL( aNoteId, aCount, EFalse, ETrue, aParams );
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::SetDynamicNotificationCountL
//-----------------------------------------------------------------------------
//
EXPORT_C TInt CAknDynamicSoftNotifier::SetDynamicNotificationCountL(
    TAknDynamicSoftNotificationParams& aParams,
    TInt aNoteId,
    TInt aCount )
    {
    return SendMessageL( aNoteId, aCount, EFalse, EFalse, aParams );
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::CancelDynamicSoftNotificationL
//-----------------------------------------------------------------------------
//
EXPORT_C void CAknDynamicSoftNotifier::CancelDynamicNotificationL(
    TInt aNoteId )
    {
    // parameters are unrelevant
    TAknDynamicSoftNotificationParams params( KAknPriorityOfCancelMessage );
    SendMessageL( aNoteId, 0, ETrue, EFalse, params );
    StopObserving( aNoteId );
    }
    
//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::StartObservingL
//-----------------------------------------------------------------------------
//    
EXPORT_C void CAknDynamicSoftNotifier::StartObservingL( TInt aNoteId, 
    MAknDynamicSoftNoteObserver* aObserver )
    {
    // Only one observer for a note id allowed.
    if( FindByNoteId( aNoteId ) != KErrNotFound )
        {
        User::Leave( KErrAlreadyExists );
        }
    
    CAknDynamicSoftNoteObserver* observer = 
        CAknDynamicSoftNoteObserver::NewLC( *this, aObserver, aNoteId );
        
    iObservers.AppendL( observer );
    CleanupStack::Pop( observer );
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::StopObserving
//-----------------------------------------------------------------------------
//
EXPORT_C void CAknDynamicSoftNotifier::StopObserving( TInt aNoteId )
    {
    TInt pos = FindByNoteId( aNoteId );
    if( pos != KErrNotFound )
        {
        delete iObservers[pos];
        iObservers.Remove(pos);
        }
    }
    
//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::DeleteObserver
//-----------------------------------------------------------------------------
//
void CAknDynamicSoftNotifier::DeleteObserver( 
    CAknDynamicSoftNoteObserver* aObserver )
    {
    TInt pos = iObservers.Find( aObserver );
    if( pos != KErrNotFound )
        {
        iObservers.Remove( pos );
        }
    delete aObserver;
    }    

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::SetSecondaryDisplayData
//-----------------------------------------------------------------------------
//
EXPORT_C void CAknDynamicSoftNotifier::SetSecondaryDisplayData( 
    CAknSDData* aData )
    {
    delete iSecondaryDisplayData;
    iSecondaryDisplayData = aData;
    }
   
//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::SecondaryDisplayData
//-----------------------------------------------------------------------------
//
CAknSDData* CAknDynamicSoftNotifier::SecondaryDisplayData()
    {
    return iSecondaryDisplayData;
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::SendMessageL
//-----------------------------------------------------------------------------
//
TInt CAknDynamicSoftNotifier::SendMessageL(
    TInt aNoteId,
    TInt aCount,
    TBool aCancel,
    TBool aAddCount,
    TAknDynamicSoftNotificationParams& aParams )
    {
    CBufFlat* buf = CBufFlat::NewL( KAknBufferGranularity );
    CleanupStack::PushL( buf );

    RBufWriteStream bufStream( *buf );
    bufStream.PushL();
    
    // Common data for dynamic notification
    bufStream.WriteInt32L( KAKNNOTIFIERSIGNATURE );
    bufStream.WriteUint8L( ECustomSoftNotification );
    bufStream.WriteInt16L( aCount );  // count
    bufStream.WriteUint8L( aCancel ? ETrue : EFalse ); // convert TBool to 0 or 1
    bufStream.WriteUint8L( aAddCount ? ETrue : EFalse ); // convert TBool to 0 or 1
    // text prompt (not used in this type of notification). 
    // It's put here to simplify changes in server side
    bufStream << KNullDesC();   
    bufStream.WriteInt32L( aNoteId ); // notification id
    
    // Type Specific data for this dynamic notification
    // Keep this synchronized with AknDynamicNotificationData
    //
    bufStream.WriteInt16L( KAknSoftNotificationDynamic ); // parameter type id
    bufStream.WriteInt32L( aNoteId ); // notification id
    bufStream << aParams;

    // Additional data
    //
    // Secondary display data not available
    bufStream.WriteInt8L( EFalse );
    
    bufStream.CommitL();
    CleanupStack::PopAndDestroy();  // bufStream

    TPckgBuf<TInt> response;
    User::LeaveIfError( iNotifier->StartOrUpdate( buf->Ptr( 0 ), response ) );
    
    CleanupStack::PopAndDestroy( buf );
    return response();
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNotifier::FindByNoteId
//-----------------------------------------------------------------------------
//
TInt CAknDynamicSoftNotifier::FindByNoteId( TInt aNoteId ) const
    {
    TInt result = KErrNotFound;
    
    const TInt count = iObservers.Count();
    for( TInt i = 0; i < count; i++ )
        {
        if( aNoteId == iObservers[i]->NoteId() )
            {
            result = i;
            break;
            }
        }
    
    return result;
    }

// End of File
