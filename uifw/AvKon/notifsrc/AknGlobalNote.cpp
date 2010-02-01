/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for the client used to show global notes.
*
*/


#include "AknGlobalNote.h"

#include <s32mem.h>
#include <AknNotifySignature.h>
#include <aknSDData.h>

#include <gfxtranseffect/gfxtranseffect.h>
#include <akntransitionutils.h>

const TInt KBufferGranularity    = 128;
const TInt KGlobalNoteTextLength = 256;

void CheckOpcodeForDisplayingGlobalNoteL( TInt aType )
    {
    if ( ( aType < EAknGlobalInformationNote ||
           aType > EAknGlobalTextNote ||
           aType == EAknCancelGlobalNote ) &&
         aType != EAknGlobalBatteryFullUnplugNote &&
         aType != EAknGlobalUnplugChargerNote )
        {
        User::Leave( KErrNotSupported );
        }
    }

EXPORT_C CAknGlobalNote* CAknGlobalNote::NewL()
    {
    CAknGlobalNote* self = NewLC();
    CleanupStack::Pop( self );
    return self;
    }

EXPORT_C CAknGlobalNote* CAknGlobalNote::NewLC()
    {
    CAknGlobalNote* self = new (ELeave) CAknGlobalNote;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

EXPORT_C CAknGlobalNote::~CAknGlobalNote()
    {
    delete iBuffer;
    delete iCancelBuffer;
    }

EXPORT_C void CAknGlobalNote::SetTextProcessing( TBool aEnabled )
    {
    iTextProcessing = aEnabled;
    }

EXPORT_C TInt CAknGlobalNote::ShowNoteL( TRequestStatus& aStatus, 
                                         TAknGlobalNoteType aType,
                                         const TDesC& aNoteText )
    {
    CheckOpcodeForDisplayingGlobalNoteL( aType );
    
    // We need to pre-allocate a note id for the global note first. It is fetched synchronously.
    TPckgBuf<TInt32> msg( KAKNNOTIFIERSIGNATURE_GETNOTEID );
    TPckgBuf<SAknGlobalNoteReturnParams> noteIdRetPckg;
    StartOrUpdateL( msg, noteIdRetPckg );

    // Then the global note is shown asynchronously with pre-allocated note id as a parameter. 
    PrepareBufferL( aType, aNoteText, noteIdRetPckg().iNoteId );
    StartOrUpdateAndGetResponseL( aStatus, iBufferPtr, iRetPckg );

    return noteIdRetPckg().iNoteId;
    }

EXPORT_C TInt CAknGlobalNote::ShowNoteL( TAknGlobalNoteType aType,
                                         const TDesC& aNoteText )
    {
    CheckOpcodeForDisplayingGlobalNoteL( aType );
    PrepareBufferL( aType, aNoteText );
    TPckgBuf<SAknGlobalNoteReturnParams> retPckg;
    StartOrUpdateL( iBufferPtr, retPckg );

    return retPckg().iNoteId;
    }

void CAknGlobalNote::PrepareBufferL( 
    TAknGlobalNoteType aType,
    const TDesC& aNoteText,
    TInt aPreallocatedGlobalNoteId)
    {
    CBufFlat* buffer = CBufFlat::NewL( KBufferGranularity );
    CleanupStack::PushL( buffer );
    
    TBool isAdapterEnabled( EFalse );

    if ( iPriority > 0xFFFF ) // It would overflow, we use this as an
                              // indication that global note has been
        {                     // activated from adapter.  
        isAdapterEnabled = ETrue;
        iPriority = 0;        // Restore default priority
        }

    DoGlobalNoteBufferL(
        aType,
        iPriority,
        iSoftkeys,
        iGraphic,
        iGraphicMask,
        iAnimation,
        iTone,
        isAdapterEnabled,
        iTextProcessing,
        aNoteText,
        buffer,
        aPreallocatedGlobalNoteId
        );
    
    if ( SecondaryDisplayData() )
        {
        RBufWriteStream bufStream;
        // To overwrite sd info previously set
        bufStream.Open( *buffer, buffer->Size() - 1 );

        CleanupClosePushL( bufStream );

        bufStream.WriteInt8L( ETrue );
        bufStream << *( SecondaryDisplayData() );        
        
        CleanupStack::PopAndDestroy( &bufStream );
        }
        
    if (aType == EAknCancelGlobalNote)
        {
        delete iCancelBuffer;
        iCancelBuffer = buffer;
        iCancelBufferPtr.Set( buffer->Ptr( 0 ) );
        }
    else
        {
        delete iBuffer;
        iBuffer = buffer;
        iBufferPtr.Set( buffer->Ptr( 0 ) );
        }        
        
    CleanupStack::Pop( buffer );
    }

EXPORT_C void CAknGlobalNote::CancelNoteL( TInt aNoteId )
    {
    TInt oldPriority = iPriority;
    iPriority        = aNoteId;
    
    PrepareBufferL( EAknCancelGlobalNote, KNullDesC );
    TPckgBuf<SAknGlobalNoteReturnParams> retPckg;
    StartOrUpdateL( iCancelBufferPtr, retPckg );
    iPriority = oldPriority;
    }

EXPORT_C void CAknGlobalNote::SetPriority( TInt aPriority )
    {
    iPriority = aPriority;
    }

EXPORT_C void CAknGlobalNote::SetSoftkeys( TInt aId )
    {
    iSoftkeys = aId;
    }

EXPORT_C void CAknGlobalNote::SetGraphic( TInt aId, TInt aMaskId )
    {
    iGraphic     = aId;
    iGraphicMask = aMaskId;
    }

EXPORT_C void CAknGlobalNote::SetAnimation( TInt aResourceId )
    {
    iAnimation = aResourceId;
    }

EXPORT_C void CAknGlobalNote::SetTone( TInt aTone )
    {
    iTone = aTone;
    }

CAknGlobalNote::CAknGlobalNote() : CAknNotifyBase( KAknGlobalNoteUid )
    {
    iGraphic        = -1;
    iGraphicMask    = -1;
    iTone           = -1;
    iTextProcessing = ETrue;
    }

void CAknGlobalNote::ConstructL()
    {
    CAknNotifyBase::ConstructL();
    }

EXPORT_C void CAknGlobalNote::CAknNotifyBase_Reserved()
    {
    }

EXPORT_C void CAknGlobalNote::DoGlobaNoteBufferL(
    TInt16 aType,
    TInt16 aPriority,
    TInt aSoftkeys,
    TInt16 aGraphic,
    TInt16 aGraphicMask,
    TInt aAnimation,
    TInt16 aTone,
    TBool aAdapterUsed,
    TBool aTextProcessingEnabled,
    const TDesC& aNoteText,
    CBufFlat* aBuffer )
    {
    DoGlobalNoteBufferL(
        aType,
        aPriority,
        aSoftkeys,
        aGraphic,
        aGraphicMask,
        aAnimation,
        aTone,
        aAdapterUsed,
        aTextProcessingEnabled,
        aNoteText,
        aBuffer,
        0);
    }
    
void CAknGlobalNote::DoGlobalNoteBufferL(
    TInt16 aType,
    TInt16 aPriority,
    TInt aSoftkeys,
    TInt16 aGraphic,
    TInt16 aGraphicMask,
    TInt aAnimation,
    TInt16 aTone,
    TBool aAdapterUsed,
    TBool aTextProcessingEnabled,
    const TDesC& aNoteText,
    CBufFlat* aBuffer,
    TInt32 aPreallocatedGlobalNoteId)
    {
    if ( aNoteText.Length() > KGlobalNoteTextLength )
        {
        User::Leave( KErrTooBig );
        }

    RBufWriteStream bufStream;
    bufStream.Open( *aBuffer );

    CleanupClosePushL( bufStream );

    bufStream.WriteInt32L( KAKNNOTIFIERSIGNATURE );

    bufStream.WriteInt16L( aType );
    bufStream << aNoteText;
    bufStream.WriteInt16L( aPriority );
    bufStream.WriteInt32L( aSoftkeys );
    bufStream.WriteInt16L( aGraphic );
    bufStream.WriteInt16L( aGraphicMask );
    bufStream.WriteInt32L( aAnimation );
    bufStream.WriteInt16L( aTone );
    bufStream.WriteInt8L( aAdapterUsed );
    bufStream.WriteInt8L( aTextProcessingEnabled );
    bufStream.WriteInt32L( aPreallocatedGlobalNoteId );
    bufStream.WriteInt8L( EFalse ); // suppress sd data by default

    CleanupStack::PopAndDestroy( &bufStream );
    }

// End of File
