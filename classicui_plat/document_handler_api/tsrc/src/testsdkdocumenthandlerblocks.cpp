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
* Description:  test document_handler_api 
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eikproc.h>
#include <eikenv.h>
#include <f32file.h>
#include <apmstd.h>
#include <pathinfo.h>
#include <documenthandler.h>

#include "testsdkdocumenthandler.h"
#include "testsdkdocumenthandlerobserver.h"

const TInt KLength = 50;
_LIT( KNewFile, "\\data\\others\\testdocumenthandlercopy.txt" );
_LIT( KSaveFile, "\\data\\others\\save" );
_LIT8( KType, "text/vnd.test" );
_LIT( KUnnamedFile, "\\data\\others\\Unnamed" );

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKDocumentHandler::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestPLNewPL", CTestSDKDocumentHandler::TestDHNewPL ),
        ENTRY( "TestDHNewPLC", CTestSDKDocumentHandler::TestDHNewPLC ),
        ENTRY( "TestDHNewL", CTestSDKDocumentHandler::TestDHNewL ),
        ENTRY( "TestDHNewLC", CTestSDKDocumentHandler::TestDHNewLC ),
        ENTRY( "TestDHDeconstructorL", CTestSDKDocumentHandler::TestDHDeconstructorL ),
        ENTRY( "TestDHOpenTempFileL", CTestSDKDocumentHandler::TestDHOpenTempFileL ),
        ENTRY( "TestDHSaveTempFileL", CTestSDKDocumentHandler::TestDHSaveTempFileL ),
        ENTRY( "TestDHInParamListL", CTestSDKDocumentHandler::TestDHInParamListL ),
        ENTRY( "TestDHOutParamListL", CTestSDKDocumentHandler::TestDHOutParamListL ),
        ENTRY( "TestDHOpenFileRL", CTestSDKDocumentHandler::TestDHOpenFileRL ),
        ENTRY( "TestDHOpenFileEmbeddedGPL", CTestSDKDocumentHandler::TestDHOpenFileEmbeddedGPL ),
        ENTRY( "TestDHOpenFileEmbeddedRL", CTestSDKDocumentHandler::TestDHOpenFileEmbeddedRL ),
        ENTRY( "TestDHOpenFileL", CTestSDKDocumentHandler::TestDHOpenFileL ),
        ENTRY( "TestDHOpenFileEmbeddedL", CTestSDKDocumentHandler::TestDHOpenFileEmbeddedL ),
        ENTRY( "TestDHSaveL", CTestSDKDocumentHandler::TestDHSaveL ),
        ENTRY( "TestDHSaveNL", CTestSDKDocumentHandler::TestDHSaveNL ),
        ENTRY( "TestDHCopyL", CTestSDKDocumentHandler::TestDHCopyL ),
        ENTRY( "TestDHCopyRL", CTestSDKDocumentHandler::TestDHCopyRL ),
        ENTRY( "TestDHMoveL", CTestSDKDocumentHandler::TestDHMoveL ),
        ENTRY( "TestDHSilentMoveL", CTestSDKDocumentHandler::TestDHSilentMoveL ),
        ENTRY( "TestDHCanHandleL", CTestSDKDocumentHandler::TestDHCanHandleL ),
        ENTRY( "TestDHCanOpenL", CTestSDKDocumentHandler::TestDHCanOpenL ),
        ENTRY( "TestDHCanSaveL", CTestSDKDocumentHandler::TestDHCanSaveL ),
        ENTRY( "TestDHGetPathL", CTestSDKDocumentHandler::TestDHGetPathL ),
        ENTRY( "TestDHHandlerAppUidL", CTestSDKDocumentHandler::TestDHHandlerAppUidL ),
        ENTRY( "TestDHSetExitObserverL", CTestSDKDocumentHandler::TestDHSetExitObserverL ),
        ENTRY( "TestDHCheckFileNameExtensionL", CTestSDKDocumentHandler::TestDHCheckFileNameExtensionL ),
        ENTRY( "TestDHCanHandleProgressivelyL", CTestSDKDocumentHandler::TestDHCanHandleProgressivelyL ),
        ENTRY( "TestDHGetProgressiveDownloadAppUidsL", CTestSDKDocumentHandler::TestDHGetProgressiveDownloadAppUidsL ),


        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHNewPL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHNewPL( CStifItemParser& /*aItem*/ )
    {
    CEikProcess* process = iEikonEnvPointer->Process();
    CleanupStack::PushL( process );
    STIF_ASSERT_NOT_NULL( process );
    
    CDocumentHandler* documentHandler = CDocumentHandler::NewL( process );
    CleanupStack::PushL( documentHandler );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    CleanupStack::PopAndDestroy( documentHandler );
    CleanupStack::Pop( process );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHNewPLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHNewPLC( CStifItemParser& /*aItem*/ )
    {
    CEikProcess* process = iEikonEnvPointer->Process();
    CleanupStack::PushL( process );
    STIF_ASSERT_NOT_NULL( process );
    
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( process );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    CleanupStack::PopAndDestroy( documentHandler );
    CleanupStack::Pop( process );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHNewL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewL();
    CleanupStack::PushL( documentHandler );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHNewLC( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC();
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC();
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHOpenTempFileL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHOpenTempFileL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\opentemp.txt" );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    TInt error = KErrNone;
    
    TRAP( error, documentHandler->OpenTempFileL( KFile, file ) );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return error;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHSaveTempFileL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHSaveTempFileL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "savetemp.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType;
    
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    TInt error = KErrNone;
    
    TRAP( error, documentHandler->SaveTempFileL( context, dataType, KFile, file ) );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return error;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHInParamListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHInParamListL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewL( iEikonEnvPointer->Process() );
    CleanupStack::PushL( documentHandler );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    CAiwGenericParamList& paramlist = documentHandler->InParamListL();
    STIF_ASSERT_NOT_NULL( &paramlist );
    
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHOutParamListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHOutParamListL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewL( iEikonEnvPointer->Process() );
    CleanupStack::PushL( documentHandler );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    const CAiwGenericParamList* paramlist = documentHandler->OutParamList();
    STIF_ASSERT_NULL( paramlist );
    
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHOpenFileRL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHOpenFileRL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    
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
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHOpenFileEmbeddedGPL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHOpenFileEmbeddedGPL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType;
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    CAiwGenericParamList& paramlist = documentHandler->InParamListL();
    STIF_ASSERT_NOT_NULL( &paramlist );
    
    file.Write( context );
    TInt flag = documentHandler->OpenFileEmbeddedL( file, dataType, paramlist );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHOpenFileEmbeddedRL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHOpenFileEmbeddedRL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType;
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    TInt flag = documentHandler->OpenFileEmbeddedL( file, dataType );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHOpenFileL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHOpenFileL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType;
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    TInt flag = documentHandler->OpenFileL( KFile, dataType );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHOpenFileEmbeddedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHOpenFileEmbeddedL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType;
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    TInt flag = documentHandler->OpenFileEmbeddedL( KFile, dataType );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHSaveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHSaveL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    fs.Delete( KUnnamedFile );
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType( KType );
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    TInt flag = documentHandler->SaveL( context, dataType, 0 );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHSaveNL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHSaveNL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    fs.Delete( KSaveFile );
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType( KType );
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    
    _LIT( KName, "save" );
    TBuf<KLength> name( KName );
    
    TInt flag = documentHandler->SaveL( context, dataType, name, 0 );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHCopyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHCopyL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "C:\\system\\apps\\testdocumenthandler.txt" );
    _LIT( KNewPath, "testdocumenthandlercopy.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    fs.Delete( KNewFile );
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType( KType );
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    
    _LIT( KName, "save" );
    TBuf<KLength> name( KName );
    
    CleanupStack::PopAndDestroy( &file );
    
    TInt flag = documentHandler->CopyL( KFile, KNewPath, dataType, 0 );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHCopyRL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHCopyRL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "C:\\system\\apps\\testdocumenthandler.txt" );
    _LIT( KNewPath, "testdocumenthandlercopy.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    fs.Delete( KNewFile );
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType( KType );
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    
    _LIT( KName, "save" );
    TBuf<KLength> name( KName );
    
    TInt flag = documentHandler->CopyL( file, KNewPath, dataType, 0 );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHMoveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHMoveL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "C:\\system\\apps\\testdocumenthandler.txt" );
    _LIT( KNewPath, "testdocumenthandlercopy.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    fs.Delete( KNewFile );
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType( KType );
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    
    _LIT( KName, "save" );
    TBuf<KLength> name( KName );
    
    CleanupStack::PopAndDestroy( &file );
    
    TInt flag = documentHandler->MoveL( KFile, KNewPath, dataType, 0 );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHSilentMoveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHSilentMoveL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "C:\\system\\apps\\testdocumenthandler.txt" );
    _LIT( KNewPath, "testdocumenthandlercopy.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    fs.Delete( KNewFile );
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType( KType );
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    
    _LIT( KName, "save" );
    TBuf<KLength> name( KName );
    
    CleanupStack::PopAndDestroy( &file );
    
    TInt flag = documentHandler->SilentMoveL( KFile, KNewPath, PathInfo::PhoneMemoryRootPath(), dataType, 0 );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHCanHandleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHCanHandleL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType;
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    
    _LIT( KName, "save" );
    TBuf<KLength> name( KName );
    
    TInt flag = documentHandler->OpenFileL( KFile, dataType );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    TInt canhandle = documentHandler->CanHandleL( dataType );
    STIF_ASSERT_TRUE( canhandle );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHCanOpenL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHCanOpenL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType;
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    
    _LIT( KName, "save" );
    TBuf<KLength> name( KName );
    
    TInt flag = documentHandler->OpenFileL( KFile, dataType );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    TInt canopen = documentHandler->CanOpenL( dataType );
    STIF_ASSERT_TRUE( canopen );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHCanSaveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHCanSaveL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType;
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    
    _LIT( KName, "save" );
    TBuf<KLength> name( KName );
    
    TInt cansave = documentHandler->CanSaveL( dataType );
    STIF_ASSERT_TRUE( cansave );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHGetPathL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHGetPathL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    fs.Delete( KSaveFile );
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType( KType );
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    
    _LIT( KName, "save" );
    TBuf<KLength> name( KName );
    
    TInt flag = documentHandler->SaveL( context, dataType, name, 0 );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    const TInt KPathLength = 50;
    TBuf<KPathLength> path;
    TInt getpath = documentHandler->GetPath( path );
    STIF_ASSERT_TRUE( getpath == KErrNone );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHHandlerAppUidL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHHandlerAppUidL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    fs.Delete( KUnnamedFile );
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    TDataType dataType( KType );
    TInt flag = documentHandler->SaveL( context, dataType, 0 );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    TUid uid;
    documentHandler->HandlerAppUid( uid );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHSetExitObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHSetExitObserverL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDocumentHandlerObserver* observer = new (ELeave) CTestSDKDocumentHandlerObserver;
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    CDocumentHandler* documentHandler = CDocumentHandler::NewL( iEikonEnvPointer->Process() );
    CleanupStack::PushL( documentHandler );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    documentHandler->SetExitObserver( observer );
    
    CleanupStack::PopAndDestroy( documentHandler );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHCheckFileNameExtensionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHCheckFileNameExtensionL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    fs.Delete( KUnnamedFile );
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType( KType );
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    TInt flag = documentHandler->SaveL( context, dataType, 0 );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    TBuf<KLength> filename;
    documentHandler->CheckFileNameExtension( filename, dataType );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHCanHandleProgressivelyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHCanHandleProgressivelyL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    fs.Delete( KUnnamedFile );
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType( KType );
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    TInt flag = documentHandler->SaveL( context, dataType, 0 );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    TUid uid;
    documentHandler->CanHandleProgressivelyL( dataType, uid );
    
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDocumentHandler::TestDHGetProgressiveDownloadAppUidsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKDocumentHandler::TestDHGetProgressiveDownloadAppUidsL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* documentHandler = CDocumentHandler::NewLC( iEikonEnvPointer->Process() );
    STIF_ASSERT_NOT_NULL( documentHandler );
    
    _LIT( KFile, "\\system\\apps\\testdocumenthandler.txt" );
    _LIT8( KContext, "Content Text" );
    TBuf8<KLength> context( KContext );
    
    RFs& fs = iEikonEnvPointer->FsSession();
    fs.Delete( KUnnamedFile );
    
    RFile file;
    CleanupClosePushL( file );
    STIF_ASSERT_NOT_NULL( &file );
    
    TDataType dataType( KType );
    if( file.Open( fs, KFile, EFileWrite | EFileShareAny ) != KErrNone )
        {
        file.Create( fs, KFile, EFileWrite | EFileShareAny );
        }
    
    file.Write( context );
    TInt flag = documentHandler->SaveL( context, dataType, 0 );
    STIF_ASSERT_TRUE( flag == KErrNone );
    
    RArray<TInt32> uidList;
    CleanupClosePushL( uidList );
    STIF_ASSERT_NOT_NULL( &uidList );
    
    TUid uid;
    documentHandler->CanHandleProgressivelyL( dataType, uid );
    documentHandler->GetProgressiveDownloadAppUidsL( uidList );
    
    CleanupStack::PopAndDestroy( &uidList );
    CleanupStack::PopAndDestroy( &file );
    CleanupStack::PopAndDestroy( documentHandler );
    
    return KErrNone;
    
    }

//  [End of File]
