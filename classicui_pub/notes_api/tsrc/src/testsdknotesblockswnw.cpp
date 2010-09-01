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
* Description:  Test AknWaitNoteWrapper.h
*
*/


#include <aknwaitnotewrapper.h>
#include <barsread.h>
#include <coeaui.h>
#include <testsdknotes.rsg>

#include "testsdknotesbackgroundprocess.h"
#include "testsdknotes.h"

const TInt KLength = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWNWCAknWaitNoteWrapperL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWNWCAknWaitNoteWrapperL( CStifItemParser& /*aItem*/ )
    {
    CAknWaitNoteWrapper* noteWrapper = CAknWaitNoteWrapper::NewL();
    STIF_ASSERT_NOT_NULL( noteWrapper );
    
    delete noteWrapper;
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWNWDeconstructorL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWNWDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknWaitNoteWrapper* noteWrapper = CAknWaitNoteWrapper::NewL();
    STIF_ASSERT_NOT_NULL( noteWrapper );
    
    delete noteWrapper;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWNWExecuteL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWNWExecuteL( CStifItemParser& /*aItem*/ )
    {
    CAknWaitNoteWrapper* noteWrapper = CAknWaitNoteWrapper::NewL();
    STIF_ASSERT_NOT_NULL( noteWrapper );
    
    CTestSDKNotesBackGroundProcess* callback = new (ELeave) CTestSDKNotesBackGroundProcess;
    STIF_ASSERT_NOT_NULL( callback );
    CleanupStack::PushL( callback );
    
    noteWrapper->ExecuteL( R_TESTSDK_WAITNOTEWRAPPER, *callback );
    
    CleanupStack::PopAndDestroy( callback );
    delete noteWrapper;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWNWExecutePromptL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWNWExecutePromptL( CStifItemParser& /*aItem*/ )
    {
    CAknWaitNoteWrapper* noteWrapper = CAknWaitNoteWrapper::NewL();
    STIF_ASSERT_NOT_NULL( noteWrapper );
    
    CTestSDKNotesBackGroundProcess* callback = new (ELeave) CTestSDKNotesBackGroundProcess;
    STIF_ASSERT_NOT_NULL( callback );
    CleanupStack::PushL( callback );
    
    _LIT( KPrompt, "waitnote" );
    TBuf<KLength> prompt( KPrompt );
    noteWrapper->ExecuteL( R_TESTSDK_WAITNOTEWRAPPER, *callback, prompt );
    
    CleanupStack::PopAndDestroy( callback );
    delete noteWrapper;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWNWWaitDialogL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWNWWaitDialogL( CStifItemParser& /*aItem*/ )
    {
    CAknWaitNoteWrapper* noteWrapper = CAknWaitNoteWrapper::NewL();
    STIF_ASSERT_NOT_NULL( noteWrapper );
    
    CTestSDKNotesBackGroundProcess* callback = new (ELeave) CTestSDKNotesBackGroundProcess;
    STIF_ASSERT_NOT_NULL( callback );
    CleanupStack::PushL( callback );
    
    _LIT( KPrompt, "waitnote" );
    TBuf<KLength> prompt( KPrompt );
    noteWrapper->ExecuteL( R_TESTSDK_WAITNOTEWRAPPER, *callback, prompt );
    
    CAknWaitDialog* dialog = noteWrapper->WaitDialog();
        
    CleanupStack::PopAndDestroy( callback );
    delete noteWrapper;
    
    return KErrNone;
    
    }
