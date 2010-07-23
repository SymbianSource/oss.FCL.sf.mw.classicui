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
* Description:  Test AknServerApp.h 
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknserverapp.h>
#include <avkon.hrh>
#include <aknenv.h>
#include <documenthandler.h>

#include "testsdkserverapplication.h"
#include "testsdkappservice.h"
#include "testsdkappservicebase.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestASBConnectChainedAppL", CTestSDKserverApplication::TestASBConnectChainedAppL ),
        ENTRY( "TestASBCloseL", CTestSDKserverApplication::TestASBCloseL ),
        ENTRY( "TestSAEOHandleServerAppExitL", CTestSDKserverApplication::TestSAEOHandleServerAppExitL ),
        ENTRY( "TestASBCAknAppServiceBaseL", CTestSDKserverApplication::TestASBCAknAppServiceBaseL ),
        ENTRY( "TestASBDeconstructorL", CTestSDKserverApplication::TestASBDeconstructorL ),
        ENTRY( "TestASBCreateL", CTestSDKserverApplication::TestASBCreateL ),
        ENTRY( "TestASBServiceL", CTestSDKserverApplication::TestASBServiceL ),
        ENTRY( "TestASBServiceErrorL", CTestSDKserverApplication::TestASBServiceErrorL ),
        ENTRY( "TestASDeconstructorL", CTestSDKserverApplication::TestASDeconstructorL ),
        ENTRY( "TestASConstructL", CTestSDKserverApplication::TestASConstructL ),
        ENTRY( "TestASCreateServiceL", CTestSDKserverApplication::TestASCreateServiceL ),
        ENTRY( "TestASHandleAllClientsClosedL", CTestSDKserverApplication::TestASHandleAllClientsClosedL ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestASBConnectChainedAppL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestASBConnectChainedAppL( CStifItemParser& /*aItem*/ )
    {
    RTestSDKAppService service;
    CleanupClosePushL( service );
    
    const TInt KTextUid = 0x2000F85A;
    TUid textUid( TUid::Uid( KTextUid ) );
    service.ConnectChainedAppL( textUid );
    service.Close();
    CleanupStack::PopAndDestroy( &service );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestASBCloseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestASBCloseL( CStifItemParser& aItem )
    {
    return TestASBConnectChainedAppL( aItem );
    }

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestSAEOHandleServerAppExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestSAEOHandleServerAppExitL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKAppServiceBase* observer = new (ELeave) CTestSDKAppServiceBase;
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    observer->HandleServerAppExit( EAknCmdExit );
    
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestASBCAknAppServiceBaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestASBCAknAppServiceBaseL( CStifItemParser& /*aItem*/ )
    {
    CAknAppServiceBase* service = new (ELeave) CAknAppServiceBase;
    CleanupStack::PushL( service );
    STIF_ASSERT_NOT_NULL( service );
    
    CleanupStack::PopAndDestroy( service );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestASBDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestASBDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknAppServiceBase* service = new (ELeave) CAknAppServiceBase;
    CleanupStack::PushL( service );
    STIF_ASSERT_NOT_NULL( service );
    
    CleanupStack::Pop( service );
    delete service;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestASBCreateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestASBCreateL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKAppServiceBase* service = new (ELeave) CTestSDKAppServiceBase;
    CleanupStack::PushL( service );
    STIF_ASSERT_NOT_NULL( service );
    
    service->CreateL();
    
    CleanupStack::PopAndDestroy( service );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestASBServiceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestASBServiceL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKAppServiceBase* service = new (ELeave) CTestSDKAppServiceBase;
    CleanupStack::PushL( service );
    STIF_ASSERT_NOT_NULL( service );
    
    RMessage2 message;
    
    service->ServiceL( message );
    
    CleanupStack::PopAndDestroy( service );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestASBServiceErrorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestASBServiceErrorL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKAppServiceBase* service = new (ELeave) CTestSDKAppServiceBase;
    CleanupStack::PushL( service );
    STIF_ASSERT_NOT_NULL( service );
    
    RMessage2 message;
    
    service->ServiceError( message, -1 );
    
    CleanupStack::PopAndDestroy( service );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestASDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestASDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknAppServer* server = new (ELeave) CAknAppServer;
    CleanupStack::PushL( server );
    STIF_ASSERT_NOT_NULL( server );
    
    CleanupStack::Pop( server );
    delete server;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestASConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestASConstructL( CStifItemParser& /*aItem*/ )
    {
    CAknAppServer* server = new (ELeave) CAknAppServer;
    CleanupStack::PushL( server );
    STIF_ASSERT_NOT_NULL( server );
    
    _LIT( KName, "server" );
    server->ConstructL( KName );
    
    CleanupStack::PopAndDestroy( server );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestASCreateServiceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestASCreateServiceL( CStifItemParser& /*aItem*/ )
    {
    CAknAppServer* server = new (ELeave) CAknAppServer;
    CleanupStack::PushL( server );
    STIF_ASSERT_NOT_NULL( server );
    
    _LIT( KName, "server" );
    server->ConstructL( KName );
    
    const TInt KAknLaunchAppServiceUid = 0x101F8827;
    TUid uid( TUid::Uid( KAknLaunchAppServiceUid ) );
    CAknAppServiceBase* service = static_cast< CAknAppServiceBase* >( server->CreateServiceL( uid ) );
    CleanupStack::PushL( service );
    STIF_ASSERT_NOT_NULL( service );
    
    CleanupStack::PopAndDestroy( service );
    CleanupStack::PopAndDestroy( server );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKserverApplication::TestASHandleAllClientsClosedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKserverApplication::TestASHandleAllClientsClosedL( CStifItemParser& /*aItem*/ )
    {
    CAknAppServer* server = new (ELeave) CAknAppServer;
    CleanupStack::PushL( server );
    STIF_ASSERT_NOT_NULL( server );
    
    _LIT( KName, "server" );
    server->ConstructL( KName );
    
    CTestSDKAppServiceBase* observer = new (ELeave) CTestSDKAppServiceBase;
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( CEikonEnv::Static()->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    documentHandler->SetExitObserver( observer );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    const TInt KLength = 50;
    TBuf8<KLength> context( KContext );
    
    RFs& fs = CEikonEnv::Static()->FsSession();
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType;
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    TInt flag = documentHandler->OpenFileL( file, dataType );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    server->HandleAllClientsClosed();
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( server );
    
    return KErrNone;
    
    }

//  [End of File]
