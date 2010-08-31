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
* Description:  Test AknGlobalNote.h
*
*/

/*
 * Include files
 */
	
#include <aknglobalnote.h>
#include <aknnotifystd.h>

#include "testsdknotifiers.hrh"
#include "activeexample.h"
#include "testsdknotifiers.h"

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteNewLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteNewLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewL();
    CleanupStack::PushL( note );
    STIF_ASSERT_NOT_NULL( note );
    CleanupStack::PopAndDestroy( note );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteNewLCL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewLC();
    STIF_ASSERT_NOT_NULL( note );
    CleanupStack::PopAndDestroy( note );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewL();
    CleanupStack::PushL( note );
    STIF_ASSERT_NOT_NULL( note );
    CleanupStack::PopAndDestroy( note );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteSetTextProcessingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteSetTextProcessingL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewL();
    CleanupStack::PushL( note );
    
    note->SetTextProcessing( ETrue );
    note->SetTextProcessing( EFalse );
    
    CleanupStack::PopAndDestroy( note );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteShowNoteLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteShowNoteLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewL();
    CleanupStack::PushL( note );
    
    TBuf<KBufSize> text( KTestString );
    note->ShowNoteL( EAknGlobalInformationNote, text );

    CleanupStack::PopAndDestroy( note );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteShowNoteLStatusL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteShowNoteLStatusL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> text( KTestString );
    CActiveExample* observer = CActiveExample::NewLC();
    observer->ShowNoteLL( EAknGlobalInformationNote, text );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteCancelNoteLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteCancelNoteLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewL();
    CleanupStack::PushL( note );
    note->CancelNoteL( KOne );
    CleanupStack::PopAndDestroy( note );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteSetPriorityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteSetPriorityL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewL();
    CleanupStack::PushL( note );
    note->SetPriority( KOne );
    CleanupStack::PopAndDestroy( note );
        
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteSetSoftkeysL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteSetSoftkeysL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewL();
    CleanupStack::PushL( note );
    note->SetSoftkeys( KOne );
    CleanupStack::PopAndDestroy( note );
        
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteSetGraphicL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteSetGraphicL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewL();
    CleanupStack::PushL( note );
    note->SetGraphic( KOne );
    CleanupStack::PopAndDestroy( note );
        
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteSetAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteSetAnimationL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewL();
    CleanupStack::PushL( note );
    note->SetAnimation( KOne );
    CleanupStack::PopAndDestroy( note );
        
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteSetToneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteSetToneL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewL();
    CleanupStack::PushL( note );
    note->SetTone( KOne );
    CleanupStack::PopAndDestroy( note );
        
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersNoteDoGlobaNoteBufferLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersNoteDoGlobaNoteBufferLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalNote* note = CAknGlobalNote::NewL();
    CleanupStack::PushL( note );

    TBuf<KBufSize> text( KTestString );
    CBufFlat* buffer = CBufFlat::NewL( KSize );
    CleanupStack::PushL( buffer );
    
    HBufC* buf1 = KTestString().AllocLC();
    HBufC* buf2 = KTestString().AllocLC();
    HBufC* buf3 = KTestString().AllocLC();
    
    buffer->InsertL( KZero, buf1, buf1->Length() );
    buffer->InsertL( KZero, buf2, buf2->Length() );
    buffer->InsertL( KZero, buf3, buf3->Length() );
    
    note->DoGlobaNoteBufferL( KShortIntOne, KShortIntOne, KOne, KShortIntOne, KShortIntOne,
        KOne, KShortIntOne, ETrue, ETrue, text, buffer );
    
    CleanupStack::PopAndDestroy( buf3 );
    CleanupStack::PopAndDestroy( buf2 );
    CleanupStack::PopAndDestroy( buf1 );
    CleanupStack::PopAndDestroy( buffer );
    CleanupStack::PopAndDestroy( note );
    return KErrNone;
    }


//End file
