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
* Description:    Test aiw_provider_utility_api
*
*/





// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aiwmenu.h>
#include <eikmobs.h>
#include <testdomaiwpro.rsg>
#include <aiwcommon.hrh>

#include "testdomaiwpro.h"

const TInt KBufLen = 10;

// -----------------------------------------------------------------------------
// simple test class
// -----------------------------------------------------------------------------
//
class CObserver : public CBase, public MEikMenuObserver
    {
    void ProcessCommandL( TInt /*aCommandId*/ )
        {
        }
    void SetEmphasis( CCoeControl* /*aMenuControl*/, TBool /*aEmphasis*/ )
        {
        }
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMAIWPro::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestDOMAIWPro::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestDOMAIWPro::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMAIWPro::RunMethodL( CStifItemParser& aItem )
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestAMConstructorL", CTestDOMAIWPro::TestAMConstructorL ),
        ENTRY( "TestAMAddMenuItemL", CTestDOMAIWPro::TestAMAddMenuItemL ),
        ENTRY( "TestAMAddMenuItemLTextL", CTestDOMAIWPro::TestAMAddMenuItemLTextL ),
        ENTRY( "TestAMAddMenuItemsL", CTestDOMAIWPro::TestAMAddMenuItemsL ),
        ENTRY( "TestAMAddMenuItemsLFileNameL", CTestDOMAIWPro::TestAMAddMenuItemsLFileNameL ),
        ENTRY( "TestAMMenuCmdIdL", CTestDOMAIWPro::TestAMMenuCmdIdL ),
        ENTRY( "TestAMDynCmdIdL", CTestDOMAIWPro::TestAMDynCmdIdL ),
        ENTRY( "TestAMServiceCmdIdL", CTestDOMAIWPro::TestAMServiceCmdIdL ),
        ENTRY( "TestAMAddTitleItemL", CTestDOMAIWPro::TestAMAddTitleItemL ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMAIWPro::TestAMConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAIWPro::TestAMConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestAMModule, "TestAMModule" );
    _LIT( KTestAMConstructor, "In TestAMConstructor" );
    TestModuleIf().Printf( 0, KTestAMModule, KTestAMConstructor );
    // Print to log file
    iLog->Log( KTestAMConstructor );

    CObserver* observer = new( ELeave ) CObserver;
    CleanupStack::PushL( observer );

    CEikMenuPane* eikMenuPane = new( ELeave ) CEikMenuPane( observer );
    CleanupStack::Pop( observer );
    CleanupStack::PushL( eikMenuPane );

    TInt baseCmdId = 0;
    CAiwMenuPane* aiwMenupane = new( ELeave ) CAiwMenuPane( *eikMenuPane, baseCmdId ); 
    CleanupStack::Pop( eikMenuPane );
    CleanupStack::PushL( aiwMenupane );

    STIF_ASSERT_NOT_NULL( aiwMenupane );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMAIWPro::TestAMAddMenuItemL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAIWPro::TestAMAddMenuItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestAMModule, "TestAMModule" );
    _LIT( KTestAMAddMenuItemL, "In TestAMAddMenuItemL" );
    TestModuleIf().Printf( 0, KTestAMModule, KTestAMAddMenuItemL );
    // Print to log file
    iLog->Log( KTestAMAddMenuItemL );

    CObserver* observer = new( ELeave ) CObserver;
    CleanupStack::PushL( observer );

    CEikMenuPane* eikMenuPane = new( ELeave ) CEikMenuPane( observer );
    CleanupStack::Pop( observer );
    CleanupStack::PushL( eikMenuPane );

    TInt baseCmdId = 0;
    CAiwMenuPane* aiwMenupane = new( ELeave ) CAiwMenuPane( *eikMenuPane, baseCmdId ); 
    CleanupStack::Pop( eikMenuPane );
    CleanupStack::PushL( aiwMenupane );
    
    TInt serviceCmd = 0;
    CEikMenuPaneItem::SData  menuItem ;
    TInt index = 0;
    aiwMenupane->AddMenuItemL( serviceCmd, menuItem, index );

    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMAIWPro::TestAMAddMenuItemLTextL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAIWPro::TestAMAddMenuItemLTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestAMModule, "TestAMModule" );
    _LIT( KTestAMAddMenuItemLTextL, "In TestAMAddMenuItemLTextL" );
    TestModuleIf().Printf( 0, KTestAMModule, KTestAMAddMenuItemLTextL );
    // Print to log file
    iLog->Log( KTestAMAddMenuItemLTextL );

    CObserver* observer = new( ELeave ) CObserver;
    CleanupStack::PushL( observer );

    CEikMenuPane* eikMenuPane = new( ELeave ) CEikMenuPane( observer );
    CleanupStack::Pop( observer );
    CleanupStack::PushL( eikMenuPane );

    TInt baseCmdId = 0;
    CAiwMenuPane* aiwMenupane = new( ELeave ) CAiwMenuPane( *eikMenuPane, baseCmdId ); 
    CleanupStack::Pop( eikMenuPane );
    CleanupStack::PushL( aiwMenupane );
    
    TInt serviceCmd = 0;
    CEikMenuPaneItem::SData  menuItem ;
    TInt index = 0;
    TBuf<KBufLen> extraText;
    aiwMenupane->AddMenuItemL( serviceCmd, menuItem, index, extraText );

    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMAIWPro::TestAMAddMenuItemsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAIWPro::TestAMAddMenuItemsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestAMModule, "TestAMModule" );
    _LIT( KTestAMAddMenuItemsL, "In TestAMAddMenuItemsL" );
    TestModuleIf().Printf( 0, KTestAMModule, KTestAMAddMenuItemsL );
    // Print to log file
    iLog->Log( KTestAMAddMenuItemsL );

    CObserver* observer = new( ELeave ) CObserver;
    CleanupStack::PushL( observer );

    CEikMenuPane* eikMenuPane = new( ELeave ) CEikMenuPane( observer );
    CleanupStack::Pop( observer );
    CleanupStack::PushL( eikMenuPane );

    TInt baseCmdId = 0;
    CAiwMenuPane* aiwMenupane = new( ELeave ) CAiwMenuPane( *eikMenuPane, baseCmdId ); 
    CleanupStack::Pop( eikMenuPane );
    CleanupStack::PushL( aiwMenupane );

    TResourceReader resReader;
    CCoeEnv::Static()->CreateResourceReaderLC( resReader, R_AIW_MENU );
    TInt serviceCmd = 0;
    TInt index = 0;
    aiwMenupane->AddMenuItemsL( resReader, serviceCmd, index );
    aiwMenupane->AddMenuItemsL( resReader, AIW_SUBMENU_TITLE, index );
    CleanupStack::PopAndDestroy( 2 ); // resReader, aiwMenupane

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMAIWPro::TestAMAddMenuItemsLFileNameL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAIWPro::TestAMAddMenuItemsLFileNameL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestAMModule, "TestAMModule" );
    _LIT( KTestAMAddMenuItemsLFileNameL, "In TestAMAddMenuItemsLFileNameL" );
    TestModuleIf().Printf( 0, KTestAMModule, KTestAMAddMenuItemsLFileNameL );
    // Print to log file
    iLog->Log( KTestAMAddMenuItemsLFileNameL );

    CObserver* observer = new( ELeave ) CObserver;
    CleanupStack::PushL( observer );

    CEikMenuPane* eikMenuPane = new( ELeave ) CEikMenuPane( observer );
    CleanupStack::Pop( observer );
    CleanupStack::PushL( eikMenuPane );

    TInt baseCmdId = 0;
    CAiwMenuPane* aiwMenupane = new( ELeave ) CAiwMenuPane( *eikMenuPane, baseCmdId ); 
    CleanupStack::Pop( eikMenuPane );
    CleanupStack::PushL( aiwMenupane );

    TFileName resourceFileName( KResourcePath );
    TInt serviceCmd = 0;
    TInt index = 0;
    aiwMenupane->AddMenuItemsL( resourceFileName, R_AIW_MENU, serviceCmd, index );
    CleanupStack::PopAndDestroy(); // resReader, aiwMenupane

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMAIWPro::TestAMMenuCmdIdL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAIWPro::TestAMMenuCmdIdL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestAMModule, "TestAMModule" );
    _LIT( KTestAMMenuCmdId, "In TestAMMenuCmdId" );
    TestModuleIf().Printf( 0, KTestAMModule, KTestAMMenuCmdId );
    // Print to log file
    iLog->Log( KTestAMMenuCmdId );

    CObserver* observer = new( ELeave ) CObserver;
    CleanupStack::PushL( observer );

    CEikMenuPane* eikMenuPane = new( ELeave ) CEikMenuPane( observer );
    CleanupStack::Pop( observer );
    CleanupStack::PushL( eikMenuPane );

    TInt baseCmdId = 0;
    CAiwMenuPane* aiwMenupane = new( ELeave ) CAiwMenuPane( *eikMenuPane, baseCmdId ); 
    CleanupStack::Pop( eikMenuPane );
    CleanupStack::PushL( aiwMenupane );

    TInt dynCmdId = 0;
    aiwMenupane->MenuCmdId( dynCmdId );
    CleanupStack::PopAndDestroy(); //aiwMenupane

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMAIWPro::TestAMDynCmdIdL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAIWPro::TestAMDynCmdIdL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestAMModule, "TestAMModule" );
    _LIT( KTestAMDynCmdId, "In TestAMDynCmdId" );
    TestModuleIf().Printf( 0, KTestAMModule, KTestAMDynCmdId );
    // Print to log file
    iLog->Log( KTestAMDynCmdId );

    CObserver* observer = new( ELeave ) CObserver;
    CleanupStack::PushL( observer );

    CEikMenuPane* eikMenuPane = new( ELeave ) CEikMenuPane( observer );
    CleanupStack::Pop( observer );
    CleanupStack::PushL( eikMenuPane );

    TInt baseCmdId = 0;
    CAiwMenuPane* aiwMenupane = new( ELeave ) CAiwMenuPane( *eikMenuPane, baseCmdId ); 
    CleanupStack::Pop( eikMenuPane );
    CleanupStack::PushL( aiwMenupane );

    TInt menuCmdId = 0;
    aiwMenupane->DynCmdId( menuCmdId );
    CleanupStack::PopAndDestroy(); //aiwMenupane

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMAIWPro::TestAMServiceCmdIdL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAIWPro::TestAMServiceCmdIdL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestAMModule, "TestAMModule" );
    _LIT( KTestAMServiceCmdId, "In TestAMServiceCmdId" );
    TestModuleIf().Printf( 0, KTestAMModule, KTestAMServiceCmdId );
    // Print to log file
    iLog->Log( KTestAMServiceCmdId );

    CObserver* observer = new( ELeave ) CObserver;
    CleanupStack::PushL( observer );

    CEikMenuPane* eikMenuPane = new( ELeave ) CEikMenuPane( observer );
    CleanupStack::Pop( observer );
    CleanupStack::PushL( eikMenuPane );

    TInt baseCmdId = 0;
    CAiwMenuPane* aiwMenupane = new( ELeave ) CAiwMenuPane( *eikMenuPane, baseCmdId ); 
    CleanupStack::Pop( eikMenuPane );
    CleanupStack::PushL( aiwMenupane );

    TInt dynCmdId = 0;
    aiwMenupane->ServiceCmdId( dynCmdId );
    CleanupStack::PopAndDestroy(); //aiwMenupane

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMAIWPro::TestAMAddTitleItemL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAIWPro::TestAMAddTitleItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestAMModule, "TestAMModule" );
    _LIT( KTestAMAddTitleItemL, "In TestAMAddTitleItemL" );
    TestModuleIf().Printf( 0, KTestAMModule, KTestAMAddTitleItemL );
    // Print to log file
    iLog->Log( KTestAMAddTitleItemL );

    CObserver* observer = new( ELeave ) CObserver;
    CleanupStack::PushL( observer );

    CEikMenuPane* eikMenuPane = new( ELeave ) CEikMenuPane( observer );
    CleanupStack::Pop( observer );
    CleanupStack::PushL( eikMenuPane );

    TInt baseCmdId = 0;
    CAiwMenuPane* aiwMenupane = new( ELeave ) CAiwMenuPane( *eikMenuPane, baseCmdId ); 
    CleanupStack::Pop( eikMenuPane );
    CleanupStack::PushL( aiwMenupane );

    _LIT( KTitle, "title" );
    TBuf<KBufLen> title( KTitle );
    TInt index = 0;
    aiwMenupane->AddTitleItemL( title, index );
    CleanupStack::PopAndDestroy(); //aiwMenupane

    return KErrNone;

    }

//  [End of File]
