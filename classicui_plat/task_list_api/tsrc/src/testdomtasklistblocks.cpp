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
* Description:  task_list_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akntasklist.h>
#include <coemain.h>

#include "testdomtasklist.h"

// CONSTANTS


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMTaskList::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMTaskList::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestTLNewL", CTestDOMTaskList::TestTLNewL ),
        ENTRY( "TestTLNewLC", CTestDOMTaskList::TestTLNewLC ),
        ENTRY( "TestTLDestructor", CTestDOMTaskList::TestTLDestructor ),
        ENTRY( "TestTLUpdateListL", CTestDOMTaskList::TestTLUpdateListL ),
        ENTRY( "TestTLWgArray", CTestDOMTaskList::TestTLWgArray ),
        ENTRY( "TestTLFindRootApp", CTestDOMTaskList::TestTLFindRootApp ),
        ENTRY( "TestTLIsRootWindowGroup", CTestDOMTaskList::TestTLIsRootWindowGroup ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMTaskList::TestTLNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTaskList::TestTLNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomtasklist, "testdomtasklist" );
    _LIT( KTestTLNewL, "In TestTLNewL" );
    TestModuleIf().Printf( 0, Ktestdomtasklist, KTestTLNewL );
    // Print to log file
    iLog->Log( KTestTLNewL );
    TBool err = KErrNone;
    TRAP( err, iTaskList = CAknTaskList::NewL( CCoeEnv::Static()->WsSession() ) );
    STIF_ASSERT_NOT_NULL( iTaskList );
    return err;

    }
// -----------------------------------------------------------------------------
// CTestDOMTaskList::TestTLNewLC
// -----------------------------------------------------------------------------
//
TInt CTestDOMTaskList::TestTLNewLC( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomtasklist, "testdomtasklist" );
    _LIT( KTestTLNewLC, "In TestTLNewLC" );
    TestModuleIf().Printf( 0, Ktestdomtasklist, KTestTLNewLC );
    // Print to log file
    iLog->Log( KTestTLNewLC );

    CAknTaskList* taskList = CAknTaskList::NewLC( CCoeEnv::Static()->WsSession() );
    STIF_ASSERT_NOT_NULL( taskList );
    CleanupStack::PopAndDestroy( taskList );
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMTaskList::TestTLDestructor
// -----------------------------------------------------------------------------
//
TInt CTestDOMTaskList::TestTLDestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomtasklist, "testdomtasklist" );
    _LIT( KTestTLDestructor, "In TestTLDestructor" );
    TestModuleIf().Printf( 0, Ktestdomtasklist, KTestTLDestructor );
    // Print to log file
    iLog->Log( KTestTLDestructor );
    
    delete iTaskList;
    iTaskList = NULL;
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMTaskList::TestTLUpdateListL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTaskList::TestTLUpdateListL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomtasklist, "testdomtasklist" );
    _LIT( KTestTLUpdateListL, "In TestTLUpdateListL" );
    TestModuleIf().Printf( 0, Ktestdomtasklist, KTestTLUpdateListL );
    // Print to log file
    iLog->Log( KTestTLUpdateListL );
    TBool err = KErrNone;
    TRAP( err, iTaskList->UpdateListL() );

    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMTaskList::TestTLWgArray
// -----------------------------------------------------------------------------
//
TInt CTestDOMTaskList::TestTLWgArray( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomtasklist, "testdomtasklist" );
    _LIT( KTestTLWgArray, "In TestTLWgArray" );
    TestModuleIf().Printf( 0, Ktestdomtasklist, KTestTLWgArray );
    // Print to log file
    iLog->Log( KTestTLWgArray );
    iTaskList->WgArray();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMTaskList::TestTLFindRootApp
// -----------------------------------------------------------------------------
//
TInt CTestDOMTaskList::TestTLFindRootApp( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomtasklist, "testdomtasklist" );
    _LIT( KTestTLFindRootApp, "In TestTLFindRootApp" );
    TestModuleIf().Printf( 0, Ktestdomtasklist, KTestTLFindRootApp );
    // Print to log file
    iLog->Log( KTestTLFindRootApp );
    TTypeUid uid = 0x00000000;
    iTaskList->FindRootApp( uid );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMTaskList::TestTLIsRootWindowGroup
// -----------------------------------------------------------------------------
//
TInt CTestDOMTaskList::TestTLIsRootWindowGroup( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomtasklist, "testdomtasklist" );
    _LIT( KTestTLIsRootWindowGroup, "In TestTLIsRootWindowGroup" );
    TestModuleIf().Printf( 0, Ktestdomtasklist, KTestTLIsRootWindowGroup );
    // Print to log file
    iLog->Log( KTestTLIsRootWindowGroup );
    TInt wgId = 0;
    iTaskList->IsRootWindowGroup( wgId );
    return KErrNone;
    }
//  [End of File]
