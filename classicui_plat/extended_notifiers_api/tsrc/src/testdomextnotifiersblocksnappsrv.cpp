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
* Description:  test functions for testing AknNotifierAppServer.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknnotifierappserver.h>
#include <aknnotifierwrapperdefs.h>
#include <aknnotifystd.h>

#include "testdomextnotifiers.h"


// CONSTANTS
const TInt KGeneralBufferLength = 32;


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASCAknNotifierAppServerL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASCAknNotifierAppServerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASCAknNotifierAppServerL, "TestCANASCAknNotifierAppServerL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASCAknNotifierAppServerL );
    // Print to log file
    iLog->Log( KTestCANASCAknNotifierAppServerL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    
    STIF_ASSERT_NOT_NULL( appSrv );
    
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASStartNotifierL
// It should be noted:
// notify.StartNotifier() function can call the StartNotifierL() function
// which is tested by the TestCANASStartNotifierL() function.
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASStartNotifierL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASStartNotifierL, "TestCANASStartNotifierL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASStartNotifierL );
    // Print to log file
    iLog->Log( KTestCANASStartNotifierL );
    
    TBuf8<KGeneralBufferLength> buffer;
    TBuf8<KGeneralBufferLength> responseBuffer;
    
    RNotifier notify;
    User::LeaveIfError( notify.Connect() );
    
    //Call StartNotifierL() function.
    notify.StartNotifier( KAknGlobalNoteUid,
        buffer, responseBuffer);
    
    notify.CancelNotifier( KAknGlobalNoteUid );
    notify.Close();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASCancelNotifierL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASCancelNotifierL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASCancelNotifierL, "TestCANASCancelNotifierL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASCancelNotifierL );
    // Print to log file
    iLog->Log( KTestCANASCancelNotifierL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    
    appSrv->CancelNotifier( KAknNotifierServiceUid );
    
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASUpdateNotifierL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASUpdateNotifierL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASUpdateNotifierL, "TestCANASUpdateNotifierL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASUpdateNotifierL );
    // Print to log file
    iLog->Log( KTestCANASUpdateNotifierL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    
    TBuf8<KGeneralBufferLength> buffer;
    TInt err = KErrNone;
    TRAP( err, appSrv->UpdateNotifierL( KAknNotifierServiceUid, buffer, buffer ) );
    
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASStartNotifierAndGetResponseL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASStartNotifierAndGetResponseL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASStartNotifierAndGetResponseL, "TestCANASStartNotifierAndGetResponseL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASStartNotifierAndGetResponseL );
    // Print to log file
    iLog->Log( KTestCANASStartNotifierAndGetResponseL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    
    RMessagePtr2 msg;
    TBuf8<KGeneralBufferLength> buffer;
    TInt err = KErrNone;
    TRAP( err, appSrv->StartNotifierAndGetResponseL( KAknNotifierServiceUid, buffer, msg, 1 ) );
    
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAppendNotifierLibNameL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAppendNotifierLibNameL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAppendNotifierLibNameL, "TestCANASAppendNotifierLibNameL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAppendNotifierLibNameL );
    // Print to log file
    iLog->Log( KTestCANASAppendNotifierLibNameL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    
    _LIT( KTestLibName, "testlib" );
    appSrv->AppendNotifierLibNameL( KTestLibName );
    
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASLoadNotifiersL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASLoadNotifiersL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASLoadNotifiersL, "TestCANASLoadNotifiersL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASLoadNotifiersL );
    // Print to log file
    iLog->Log( KTestCANASLoadNotifiersL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    
    _LIT( KTestLibName, "testlib" );
    appSrv->AppendNotifierLibNameL( KTestLibName );
    TInt err = KErrNone;
    TRAP( err, appSrv->LoadNotifiersL() );
    
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASCreateServiceL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASCreateServiceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASCreateServiceL, "TestCANASCreateServiceL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASCreateServiceL );
    // Print to log file
    iLog->Log( KTestCANASCreateServiceL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    
    _LIT( KFixedServerName, "TestServer" );
    appSrv->ConstructL( KFixedServerName );
    TInt err = KErrNone;
    TRAP( err, appSrv->CreateServiceL( KAknNotifierServiceUid ) );
    
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASSetImplementationFinderL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASSetImplementationFinderL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASSetImplementationFinderL, "TestCANASSetImplementationFinderL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASSetImplementationFinderL );
    // Print to log file
    iLog->Log( KTestCANASSetImplementationFinderL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    
    MNotifLibraryOwningServer* finder = NULL;
    appSrv->SetImplementationFinderL( finder );
    
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASUnbalanceReferenceCountForNotifL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASUnbalanceReferenceCountForNotifL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASUnbalanceReferenceCountForNotifL, "TestCANASUnbalanceReferenceCountForNotifL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASUnbalanceReferenceCountForNotifL );
    // Print to log file
    iLog->Log( KTestCANASUnbalanceReferenceCountForNotifL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    
    appSrv->UnbalanceReferenceCountForNotif( KAknNotifierServiceUid, ETrue );
    
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASUpdateNotifierAndGetResponseL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASUpdateNotifierAndGetResponseL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASUpdateNotifierAndGetResponseL, "TestCANASUpdateNotifierAndGetResponseL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASUpdateNotifierAndGetResponseL );
    // Print to log file
    iLog->Log( KTestCANASUpdateNotifierAndGetResponseL );
    
    CAknNotifierAppServer* appSrv = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( appSrv );
    
    TBuf8<KGeneralBufferLength> buffer;
    RMessagePtr2 msg;
    TInt err = KErrNone;
    TRAP( err, appSrv->UpdateNotifierAndGetResponseL( KAknNotifierServiceUid, buffer, msg, 1 ) );
    
    CleanupStack::PopAndDestroy( appSrv );
    
    return KErrNone;
    }


//  [End of File]
