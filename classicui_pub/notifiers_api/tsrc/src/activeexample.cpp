/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test notifiers_api
*
*/


/*
 *  [INCLUDE FILES]
 */
#include <aknglobalconfirmationquery.h>
#include <akngloballistquery.h>
#include <aknglobalmsgquery.h>
#include <aknglobalnote.h>
#include <aknglobalprogressdialog.h>
#include <avkon.mbg>
#include <akngloballistmsgquery.h>
#include <bamdesca.h>
#include <badesca.h>
#include <aknsddata.h>

#include "testsdknotifiers.hrh"
#include "activeexample.h"

// -----------------------------------------------------------------------------
// CActiveExample::ShowAndCancelConfirmationQueryLL
// -----------------------------------------------------------------------------
//
void CActiveExample::ShowAndCancelConfirmationQueryLL( const TDesC& aPrompt )
    {
    CActiveExample* self = new( ELeave ) CActiveExample();
    CleanupStack::PushL( self );
    self->ConstructL();
    self->ShowAndCancelConfirmationQueryL( aPrompt );
    CleanupStack::PopAndDestroy( self );
    }

// -----------------------------------------------------------------------------
// CActiveExample::ShowAndCancelConfirmationQueryL
// -----------------------------------------------------------------------------
//
void CActiveExample::ShowAndCancelConfirmationQueryL( const TDesC& aPrompt )
    {
    iConfirmationquery->ShowConfirmationQueryL( iStatus, aPrompt );
    iConfirmationquery->CancelConfirmationQuery();
    SetActive();
    CActiveScheduler::Start();
    
    }

// -----------------------------------------------------------------------------
// CActiveExample::ShowAndCancelListQueryLL
// -----------------------------------------------------------------------------
//
void CActiveExample::ShowAndCancelListQueryLL( const MDesCArray* aItems )
    {
    CActiveExample* self = new( ELeave ) CActiveExample();
    CleanupStack::PushL( self );
    self->ConstructL();
    self->ShowAndCancelListQueryL( aItems );
    CleanupStack::PopAndDestroy( self );
    }

// -----------------------------------------------------------------------------
// CActiveExample::ShowAndCancelListQueryL
// -----------------------------------------------------------------------------
//
void CActiveExample::ShowAndCancelListQueryL( const MDesCArray* aItems )
    {
    iListQuery->ShowListQueryL( aItems, iStatus, KOne );
    iListQuery->CancelListQuery();
    SetActive();
    CActiveScheduler::Start();
    }

// -----------------------------------------------------------------------------
// CActiveExample::ShowMsgQueryLL
// -----------------------------------------------------------------------------
//
void CActiveExample::ShowMsgQueryLL( const TDesC& aMsgText,
            TInt aSoftkeys,
            const TDesC& aHeaderText,
            const TDesC& aHeaderImageFile,
            TInt aImageId,
            TInt aImageMaskId )
    {
    CActiveExample* self = new(ELeave) CActiveExample();
    CleanupStack::PushL( self );
    self->ConstructL();
    self->ShowMsgQueryL( aMsgText, aSoftkeys, aHeaderText, aHeaderImageFile, 
        aImageId, aImageMaskId );
    CleanupStack::PopAndDestroy( self );
    }

// -----------------------------------------------------------------------------
// CActiveExample::ShowMsgQueryL
// -----------------------------------------------------------------------------
//
void CActiveExample::ShowMsgQueryL( const TDesC& aMsgText,
        TInt aSoftkeys,
        const TDesC& aHeaderText,
        const TDesC& aHeaderImageFile,
        TInt aImageId,
        TInt aImageMaskId )
    {
    iMsgQuery->ShowMsgQueryL( iStatus, aMsgText, aSoftkeys, aHeaderText, 
        aHeaderImageFile, aImageId, aImageMaskId );
    iMsgQuery->CancelMsgQuery();
    SetActive();
    CActiveScheduler::Start();
    }

// -----------------------------------------------------------------------------
// CActiveExample::ShowNoteLL
// -----------------------------------------------------------------------------
//
void CActiveExample::ShowNoteLL( TAknGlobalNoteType aType, const TDesC& aNoteText )
    {
    CActiveExample* self = new( ELeave ) CActiveExample();
    CleanupStack::PushL( self );
    self->ConstructL();
    self->ShowNoteL( aType, aNoteText );
    CleanupStack::PopAndDestroy( self );
    }

// -----------------------------------------------------------------------------
// CActiveExample::ShowNoteL
// -----------------------------------------------------------------------------
//
void CActiveExample::ShowNoteL( TAknGlobalNoteType aType, const TDesC& aNoteText )
    {
    iNote->ShowNoteL( iStatus, aType, aNoteText );
    SetActive();
    CActiveScheduler::Start();
    }

// -----------------------------------------------------------------------------
// CActiveExample::ShowAndCancelProgressDialogLL
// -----------------------------------------------------------------------------
//
void CActiveExample::ShowAndCancelProgressDialogLL( const TDesC& aPrompt )
    {
    CActiveExample* self = new(ELeave) CActiveExample();
    CleanupStack::PushL( self );
    self->ConstructL();
    self->ShwoAndCancelProgressDialogL( aPrompt );
    CleanupStack::PopAndDestroy( self );
    }

// -----------------------------------------------------------------------------
// CActiveExample::ShwoAndCancelProgressDialogL
// -----------------------------------------------------------------------------
//
void CActiveExample::ShwoAndCancelProgressDialogL( const TDesC& aPrompt )
    {
    iProgressDialog->ShowProgressDialogL( iStatus, aPrompt );
    iProgressDialog->CancelProgressDialog();
    SetActive();
    CActiveScheduler::Start();
    }

// -----------------------------------------------------------------------------
// CActiveExample::ShowTheListMsgQueryL
// -----------------------------------------------------------------------------
//
void CActiveExample::ShowTheListMsgQueryL()
    {
    
    _LIT( KHead, "Message" );
    _LIT( KText, "Item" ); 
    
    TBufC<20> tempString( KText );
    CDesCArrayFlat* arrayItem = new( ELeave ) CDesCArrayFlat( 20 );
    arrayItem->AppendL( tempString );
    iGlobalListMsgQuery->ShowListMsgQueryL( arrayItem, iStatus, KHead, KText );
    SetActive();
    
    CActiveScheduler::Start();
    
    }
    
// -----------------------------------------------------------------------------
// CActiveExample::DoCancel
// -----------------------------------------------------------------------------
//
void CActiveExample::DoCancel()
    {
    Cancel();
    }

// -----------------------------------------------------------------------------
// CActiveExample::RunL
// -----------------------------------------------------------------------------
//
void CActiveExample::RunL()
    {
    CActiveScheduler::Stop();
    }
 
// -----------------------------------------------------------------------------
// CActiveExample::CActiveExample
// -----------------------------------------------------------------------------
//
CActiveExample::CActiveExample() : CActive(CActive::EPriorityStandard)
    {
    CActiveScheduler::Add( this );
    }

// -----------------------------------------------------------------------------
// CActiveExample::ConstructL
// -----------------------------------------------------------------------------
//
void CActiveExample::ConstructL()
    {
    iConfirmationquery = CAknGlobalConfirmationQuery::NewL();
    iListQuery = CAknGlobalListQuery::NewL();
    iMsgQuery = CAknGlobalMsgQuery::NewL();
    iNote = CAknGlobalNote::NewL();
    iProgressDialog = CAknGlobalProgressDialog::NewL();
    iGlobalListMsgQuery = CAknGlobalListMsgQuery::NewL();
    
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) );
    
    TBuf<KBufSize> buf( KTestString );
    iProgressDialog->SetIconL( buf, file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    iProgressDialog->SetImageL( file, EMbmAvkonQgn_indi_mic, 
        EMbmAvkonQgn_indi_mic_mask );
    }

// -----------------------------------------------------------------------------
// CActiveExample::~CActiveExample
// -----------------------------------------------------------------------------
//
CActiveExample::~CActiveExample()
    {
    Cancel();
    delete iConfirmationquery;
    delete iListQuery;
    delete iMsgQuery;
    delete iNote;
    delete iProgressDialog;
    delete iGlobalListMsgQuery;
    }
  
// -----------------------------------------------------------------------------
// CActiveExample::NewL()
// -----------------------------------------------------------------------------
//
CActiveExample* CActiveExample::NewL()
{
    CActiveExample* self=CActiveExample::NewLC();
    CleanupStack::Pop( self ); // self;
    return self;
}

// -----------------------------------------------------------------------------
// CActiveExample::NewLC
// -----------------------------------------------------------------------------
//
CActiveExample* CActiveExample::NewLC()
{
    CActiveExample* self = new (ELeave)CActiveExample();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
}

//End file
