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
* Description:  test genericparamconsumer.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <genericparamconsumer.h>
#include <coemain.h>
#include <eikenv.h>
#include <eikappui.h>
#include <aiwgenericparam.h>
#include <s32file.h>
#include <f32file.h>

#include "testdomgenparam.h"
#include "testdomgenparamext.h"


// CONSTANTS
const TUid KUidEmbedInputStream  = { 0x1000 };

_LIT( KFileName, "c:\\testsdkstroe.txt" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMGenParam::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMGenParam::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestDefConsL", CTestDOMGenParam::TestDefConsL ),
        ENTRY( "TestRestoreL", CTestDOMGenParam::TestRestoreL ),
        ENTRY( "TestGetInputParameters", CTestDOMGenParam::TestGetInputParametersL ),
        ENTRY( "TestSetOutputParamsL", CTestDOMGenParam::TestSetOutputParamsL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMGenParam::TestDefConsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGenParam::TestDefConsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMGenParam, "testdomgenparam" );
    _LIT( KTestDefConsL, "In DefConsL" );
    TestModuleIf().Printf( 0, KTestDOMGenParam, KTestDefConsL );
    // Print to log file
    iLog->Log( KTestDefConsL );

    CEikAppUi* appui = static_cast<CEikAppUi*>( CCoeEnv::Static()->AppUi() );
    CAiwGenericParamConsumerExt* consumer = new ( ELeave )
            CAiwGenericParamConsumerExt( *appui->Application() );
    CleanupStack::PushL( consumer );
    STIF_ASSERT_NOT_NULL( consumer );

    CleanupStack::Pop( consumer );
    delete consumer;
    consumer = NULL;

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMGenParam::TestRestoreL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGenParam::TestRestoreL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMGenParam, "testdomgenparam" );
    _LIT( KTestRestoreL, "In RestoreL" );
    TestModuleIf().Printf( 0, KTestDOMGenParam, KTestRestoreL );
    // Print to log file
    iLog->Log( KTestRestoreL );

    CEikAppUi* appui = static_cast<CEikAppUi*>( CCoeEnv::Static()->AppUi() );
    CAiwGenericParamConsumerExt* consumer = new ( ELeave )
            CAiwGenericParamConsumerExt( *appui->Application() );
    CleanupStack::PushL( consumer );

    RFs rfs;
    CleanupClosePushL( rfs );
    TInt err = rfs.Connect();
    if ( err != KErrNone )
        {
        return err;
        }

    CFileStore* store = consumer->CreateFileStoreLC( rfs, KFileName );

    RStoreWriteStream stream;
    TStreamId id = stream.CreateLC( *store );

    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    list->ExternalizeL( stream );

    CStreamDictionary* dict = CStreamDictionary::NewLC();
    dict->AssignL( KUidEmbedInputStream, id );

    consumer->StoreL( *store, *dict );

    consumer->RestoreL( *store, *dict );

    CleanupStack::PopAndDestroy( dict );
    CleanupStack::PopAndDestroy( list );
    CleanupStack::PopAndDestroy( &stream );
    CleanupStack::PopAndDestroy( store );
    CleanupStack::PopAndDestroy( &rfs );
    CleanupStack::PopAndDestroy( consumer );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMGenParam::TestGetInputParametersL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGenParam::TestGetInputParametersL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMGenParam, "testdomgenparam" );
    _LIT( KTestGetInputParameters, "In GetInputParameters" );
    TestModuleIf().Printf( 0, KTestDOMGenParam, KTestGetInputParameters );
    // Print to log file
    iLog->Log( KTestGetInputParameters );

    CEikAppUi* appui = static_cast<CEikAppUi*>( CCoeEnv::Static()->AppUi() );
    CAiwGenericParamConsumerExt* consumer = new ( ELeave )
            CAiwGenericParamConsumerExt( *appui->Application() );
    CleanupStack::PushL( consumer );

    RFs rfs;
    CleanupClosePushL( rfs );
    TInt err = rfs.Connect();
    if ( err != KErrNone )
        {
        return err;
        }

    CFileStore* store = consumer->CreateFileStoreLC( rfs, KFileName );

    RStoreWriteStream stream;
    TStreamId id = stream.CreateLC( *store );

    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    list->ExternalizeL( stream );

    CStreamDictionary* dict = CStreamDictionary::NewLC();
    dict->AssignL( KUidEmbedInputStream, id );

    consumer->StoreL( *store, *dict );
    consumer->RestoreL( *store, *dict );

    const CAiwGenericParamList* paramList = consumer->DoGetInputParameters();
    STIF_ASSERT_NOT_NULL( paramList );

    CleanupStack::PopAndDestroy( dict );
    CleanupStack::PopAndDestroy( list );
    CleanupStack::PopAndDestroy( &stream );
    CleanupStack::PopAndDestroy( store );
    CleanupStack::PopAndDestroy( &rfs );
    CleanupStack::PopAndDestroy( consumer );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMGenParam::TestSetOutputParamsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGenParam::TestSetOutputParamsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMGenParam, "testdomgenparam" );
    _LIT( KTestSetOutputParamsL, "In SetOutputParamsL" );
    TestModuleIf().Printf( 0, KTestDOMGenParam, KTestSetOutputParamsL );
    // Print to log file
    iLog->Log( KTestSetOutputParamsL );

    CEikAppUi* appui = static_cast<CEikAppUi*>( CCoeEnv::Static()->AppUi() );
    CAiwGenericParamConsumerExt* consumer = new ( ELeave )
            CAiwGenericParamConsumerExt( *appui->Application() );
    CleanupStack::PushL( consumer );

    RFs rfs;
    CleanupClosePushL( rfs );
    TInt err = rfs.Connect();
    if ( err != KErrNone )
        {
        return err;
        }

    CFileStore* store = consumer->CreateFileStoreLC( rfs, KFileName );

    RStoreWriteStream stream;
    TStreamId id = stream.CreateLC( *store );

    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    list->ExternalizeL( stream );

    CStreamDictionary* dict = CStreamDictionary::NewLC();
    dict->AssignL( KUidEmbedInputStream, id );

    consumer->StoreL( *store, *dict );
    consumer->RestoreL( *store, *dict );

    consumer->DoSetOutputParamsL( list );

    CleanupStack::PopAndDestroy( dict );
    CleanupStack::PopAndDestroy( list );
    CleanupStack::PopAndDestroy( &stream );
    CleanupStack::PopAndDestroy( store );
    CleanupStack::PopAndDestroy( &rfs );
    CleanupStack::PopAndDestroy( consumer );
    return KErrNone;

    }


//  [End of File]
