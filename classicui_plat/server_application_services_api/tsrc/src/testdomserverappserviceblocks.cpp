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
* Description:  Methods implement
*
* 
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eikenv.h>

#include "testdomserverappservice.h"

// CONSTANTS
_LIT( KTempFileName, "c:\\testframework\\tctest.cfg" );
const TInt KBufSize = 64;
const TUid KFileManagerUid = { 0x101F84EB };
const TUid KNotepadUid = { 0x10005907 };
// FORWARD DECLARATIONS
// Observer for test, no used
class CTestServerAppExitObserver : public CBase, public MAknServerAppExitObserver
    {};

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomServerAppService::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomServerAppService::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestCAknLaunchAppServiceNewL", CTestDomServerAppService::TestCAknLaunchAppServiceNewL ),
        ENTRY( "TestCAknNullServiceNewL", CTestDomServerAppService::TestCAknNullServiceNewL ),
        ENTRY( "TestCAknOpenFileServiceNewL", CTestDomServerAppService::TestCAknOpenFileServiceNewL ),
        ENTRY( "TestCAknOpenFileServiceSecNewL", CTestDomServerAppService::TestCAknOpenFileServiceSecNewL ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDomServerAppService::TestCAknLaunchAppServiceNewL
// -----------------------------------------------------------------------------
//
TInt CTestDomServerAppService::TestCAknLaunchAppServiceNewL( CStifItemParser& /*aItem*/ )
    {
    TInt err = 0;
    CAknLaunchAppService* appserv = NULL;
    appserv = CAknLaunchAppService::NewL( KFileManagerUid, NULL, NULL );
    CleanupStack::PushL( appserv );
    CleanupStack::PopAndDestroy( appserv );
    if ( err != KErrNone )
        {
        err = KErrNone;
        }
    return err;

    }

// -----------------------------------------------------------------------------
// CTestDomServerAppService::TestCAknNullServiceNewL
// -----------------------------------------------------------------------------
//
TInt CTestDomServerAppService::TestCAknNullServiceNewL( CStifItemParser& /*aItem*/ )
    {
    CTestServerAppExitObserver* ob = new ( ELeave ) CTestServerAppExitObserver;
    CleanupStack::PushL( ob );
    TInt err = 0;
    CAknNullService* serv = NULL;
    serv = CAknNullService::NewL( KFileManagerUid, ob );
    CleanupStack::PushL( serv );
    CleanupStack::PopAndDestroy( 2 );
    
    if ( err != KErrNone )
        {
        err = KErrNone;
        }
    return err;

    }


// -----------------------------------------------------------------------------
// CTestDomServerAppService::TestCAknOpenFileServiceNewL
// -----------------------------------------------------------------------------
//
TInt CTestDomServerAppService::TestCAknOpenFileServiceNewL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTempFileName );
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    CAknOpenFileService* appserv = NULL;
    appserv = CAknOpenFileService::NewL( buf, NULL, list );
    CleanupStack::PushL( appserv );
    CleanupStack::PopAndDestroy( 2 );// list, appserv
    return KErrNone;
    }



// -----------------------------------------------------------------------------
// CTestDomServerAppService::TestCAknOpenFileServiceSecNewL
// -----------------------------------------------------------------------------
//
TInt CTestDomServerAppService::TestCAknOpenFileServiceSecNewL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTempFileName );
    RFile rfile;
    CleanupClosePushL( rfile );
    TInt err = rfile.Open( CEikonEnv::Static()->FsSession(), buf, EFileWrite );
    if ( err != KErrNone )
        {
        CleanupStack::PopAndDestroy( &rfile );
        return -1000;
        }
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    CAknOpenFileService* appserv = NULL;
    appserv = CAknOpenFileService::NewL( KNotepadUid, rfile, NULL, list );
    CleanupStack::PushL( appserv );
    CleanupStack::PopAndDestroy( 3 );// rfile, list, appserv
    return KErrNone;
    }


//  [End of File]
