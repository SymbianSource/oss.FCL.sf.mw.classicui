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
* Description:  avkon_secondary_display_support_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknmediatorfacade.h>

#include "testdomasds.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMASDS::TestMFNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMASDS::TestMFNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomasds, "testdomasds" );
    _LIT( KTestMFNewL, "In TestMFNewL" );
    TestModuleIf().Printf( 0, Ktestdomasds, KTestMFNewL );
    // Print to log file
    iLog->Log( KTestMFNewL );
    CEikDialog *dialog = new ( ELeave ) CEikDialog();
    TInt err = KErrNone;
    CleanupStack::PushL( dialog );
    TRAP( err, iMediatorFacade = CAknMediatorFacade::NewL( dialog ) );
    CleanupStack::PopAndDestroy( dialog );
    
    return err;

    }
// -----------------------------------------------------------------------------
// CTestDOMASDS::TestMFIssueCommandL
// -----------------------------------------------------------------------------
//
TInt CTestDOMASDS::TestMFIssueCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomasds, "testdomasds" );
    _LIT( KTestMFIssueCommand, "In TestMFIssueCommand" );
    TestModuleIf().Printf( 0, Ktestdomasds, KTestMFIssueCommand );
    // Print to log file
    iLog->Log( KTestMFIssueCommand );
    CEikDialog *dialog = new ( ELeave ) CEikDialog();
    CleanupStack::PushL( dialog );
    iMediatorFacade = CAknMediatorFacade::NewL( dialog );
    TInt& cIndex = iMediatorFacade->DialogIndex();
    cIndex = 1;
    iMediatorFacade->IssueCommand();
    CleanupStack::PopAndDestroy( dialog );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMASDS::TestMFCancelCommandL
// -----------------------------------------------------------------------------
//
TInt CTestDOMASDS::TestMFCancelCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomasds, "testdomasds" );
    _LIT( KTestMFCancelCommand, "In TestMFCancelCommand" );
    TestModuleIf().Printf( 0, Ktestdomasds, KTestMFCancelCommand );
    // Print to log file
    iLog->Log( KTestMFCancelCommand );
    CEikDialog *dialog = new ( ELeave ) CEikDialog();
    CleanupStack::PushL( dialog );
    iMediatorFacade = CAknMediatorFacade::NewL( dialog );
    iMediatorFacade->CancelCommand();
    CleanupStack::PopAndDestroy( dialog );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMASDS::TestMFResetBufferL
// -----------------------------------------------------------------------------
//
TInt CTestDOMASDS::TestMFResetBufferL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomasds, "testdomasds" );
    _LIT( KTestMFResetBuffer, "In TestMFResetBuffer" );
    TestModuleIf().Printf( 0, Ktestdomasds, KTestMFResetBuffer );
    // Print to log file
    iLog->Log( KTestMFResetBuffer );
    CEikDialog *dialog = new ( ELeave ) CEikDialog();
    CleanupStack::PushL( dialog );
    iMediatorFacade = CAknMediatorFacade::NewL( dialog );
    iMediatorFacade->ResetBuffer();
    CleanupStack::PopAndDestroy( dialog );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMASDS::TestMFSetObserverL
// -----------------------------------------------------------------------------
//
TInt CTestDOMASDS::TestMFSetObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomasds, "testdomasds" );
    _LIT( KTestMFSetObserver, "In TestMFSetObserver" );
    TestModuleIf().Printf( 0, Ktestdomasds, KTestMFSetObserver );
    // Print to log file
    iLog->Log( KTestMFSetObserver );
    CEikDialog *dialog = new ( ELeave ) CEikDialog();
    CleanupStack::PushL( dialog );
    iMediatorFacade = CAknMediatorFacade::NewL( dialog );
    iMediatorFacade->SetObserver( NULL );
    CleanupStack::PopAndDestroy( dialog );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMASDS::TestMFPostUpdatedDataL
// -----------------------------------------------------------------------------
//
TInt CTestDOMASDS::TestMFPostUpdatedDataL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomasds, "testdomasds" );
    _LIT( KTestMFPostUpdatedDataL, "In TestMFPostUpdatedDataL" );
    TestModuleIf().Printf( 0, Ktestdomasds, KTestMFPostUpdatedDataL );
    // Print to log file
    iLog->Log( KTestMFPostUpdatedDataL );
    TInt err = KErrNone;
    CEikDialog *dialog = new ( ELeave ) CEikDialog();
    CleanupStack::PushL( dialog );
    iMediatorFacade = CAknMediatorFacade::NewL( dialog );
    TRAP( err, iMediatorFacade->PostUpdatedDataL() );
    CleanupStack::PopAndDestroy( dialog );
    return err;

    }
