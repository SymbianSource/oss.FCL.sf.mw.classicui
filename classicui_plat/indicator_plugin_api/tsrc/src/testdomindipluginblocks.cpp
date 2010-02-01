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
* Description:  test aknindicatorplugin.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknindicatorplugin.h>
#include <aknindicatorpluginimpluids.hrh>

#include "testdomindiplugin.h"
#include "testdomindipluginext.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMIndiPlugin::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMIndiPlugin::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestNewL", CTestDOMIndiPlugin::TestNewL ),
        ENTRY( "TestTextL", CTestDOMIndiPlugin::TestTextL ),
        ENTRY( "TestIconL", CTestDOMIndiPlugin::TestIconL ),
        ENTRY( "TestUpdateL", CTestDOMIndiPlugin::TestUpdateL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMIndiPlugin::TestNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMIndiPlugin::TestNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMIndiPlugin, "testdomindiplugin" );
    _LIT( KTestNewL, "In NewL" );
    TestModuleIf().Printf( 0, KTestDOMIndiPlugin, KTestNewL );
    // Print to log file
    iLog->Log( KTestNewL );

    TUid pluginUid = TUid::Uid( KImplUIDMessagingIndicatorsPlugin );
    CAknIndicatorPlugin* plugin = CAknIndicatorPlugin::NewL( pluginUid );
    CleanupStack::PushL( plugin );
    
    CleanupStack::PopAndDestroy( plugin );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMIndiPlugin::TestTextL
// -----------------------------------------------------------------------------
//
TInt CTestDOMIndiPlugin::TestTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMIndiPlugin, "testdomindiplugin" );
    _LIT( KTestTextL, "In TextL" );
    TestModuleIf().Printf( 0, KTestDOMIndiPlugin, KTestTextL );
    // Print to log file
    iLog->Log( KTestTextL );

    CAknIndicatorPluginExt* pluginExt = new ( ELeave ) CAknIndicatorPluginExt;
    CleanupStack::PushL( pluginExt );

    TInt textType = 0;
    HBufC* text  = pluginExt->TextL( 0, textType );
    STIF_ASSERT_NULL( text );

    CleanupStack::PopAndDestroy( pluginExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMIndiPlugin::TestIconL
// -----------------------------------------------------------------------------
//
TInt CTestDOMIndiPlugin::TestIconL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMIndiPlugin, "testdomindiplugin" );
    _LIT( KTestIconL, "In IconL" );
    TestModuleIf().Printf( 0, KTestDOMIndiPlugin, KTestIconL );
    // Print to log file
    iLog->Log( KTestIconL );

    CAknIndicatorPluginExt* pluginExt = new ( ELeave ) CAknIndicatorPluginExt;
    CleanupStack::PushL( pluginExt );

    const CGulIcon* icon = pluginExt->IconL( 0 );
    STIF_ASSERT_NULL( icon );

    CleanupStack::PopAndDestroy( pluginExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMIndiPlugin::TestUpdateL
// -----------------------------------------------------------------------------
//
TInt CTestDOMIndiPlugin::TestUpdateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMIndiPlugin, "testdomindiplugin" );
    _LIT( KTestUpdateL, "In UpdateL" );
    TestModuleIf().Printf( 0, KTestDOMIndiPlugin, KTestUpdateL );
    // Print to log file
    iLog->Log( KTestUpdateL );

    CAknIndicatorPluginExt* pluginExt = new ( ELeave ) CAknIndicatorPluginExt;
    CleanupStack::PushL( pluginExt );

    pluginExt->UpdateL( 0 );

    CleanupStack::PopAndDestroy( pluginExt );
    return KErrNone;

    }


//  [End of File]
