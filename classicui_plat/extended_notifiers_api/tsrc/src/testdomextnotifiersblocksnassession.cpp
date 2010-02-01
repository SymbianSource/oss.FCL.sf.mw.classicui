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
* Description:  test functions for testing AknNotifierAppServerSession.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknnotifierappserversession.h>
#include <aknnotifierappserver.h>
#include <aknnotifystd.h>

#include "testdomextnotifiers.h"

const TInt KGeneralBufferLength = 32;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANSASCAknNotifierServerAppServiceL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANSASCAknNotifierServerAppServiceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANSASCAknNotifierServerAppServiceL, "TestCANSASCAknNotifierServerAppServiceL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANSASCAknNotifierServerAppServiceL );
    // Print to log file
    iLog->Log( KTestCANSASCAknNotifierServerAppServiceL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    CAknNotifierServerAppService* appService = new ( ELeave ) CAknNotifierServerAppService( *appSrv );
    CleanupStack::PushL( appService );
    
    STIF_ASSERT_NOT_NULL( appService );
    
    CleanupStack::PopAndDestroy( appService );
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANSASServiceL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANSASServiceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANSASServiceL, "TestCANSASServiceL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANSASServiceL );
    // Print to log file
    iLog->Log( KTestCANSASServiceL );
    
    _LIT( KTextLine1, "RNotify(first line)" );
    _LIT( KTextLine2, "second line" );
    _LIT( KButton1, "Button1" );
    _LIT( KButton2, "Button2" );
    TInt response( -1 );
    
    TRequestStatus status;
    RNotifier notifier;
    User::LeaveIfError( notifier.Connect() );
    //This function can call ServiceL() function
    notifier.Notify( KTextLine1, KTextLine2, KButton1, KButton2, response,status );
    User::WaitForRequest( status );
    
    notifier.Close();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANSASAllowClientL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANSASAllowClientL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANSASAllowClientL, "TestCANSASAllowClientL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANSASAllowClientL );
    // Print to log file
    iLog->Log( KTestCANSASAllowClientL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    CAknNotifierServerAppService* appService = new ( ELeave ) CAknNotifierServerAppService( *appSrv );
    CleanupStack::PushL( appService );
    
    RMessage2 msg2;
    appService->AllowClientL( msg2 );
    
    CleanupStack::PopAndDestroy( appService );
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANSASHandleMessageL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANSASHandleMessageL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANSASHandleMessageL, "TestCANSASHandleMessageL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANSASHandleMessageL );
    // Print to log file
    iLog->Log( KTestCANSASHandleMessageL );
    
    TBuf8<KGeneralBufferLength> buffer;
    TBuf8<KGeneralBufferLength> responseBuffer;
    
    RNotifier notify;
    User::LeaveIfError( notify.Connect() );
    
    //Call StartL() function.
    notify.StartNotifier( KAknGlobalNoteUid,
        buffer, responseBuffer);
    
    notify.UpdateNotifier( KAknGlobalNoteUid,
        buffer, responseBuffer );
    
    notify.CancelNotifier( KAknGlobalNoteUid );
    notify.Close();
    
    return KErrNone;
    }


//  [End of File]
