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
* Description:  test aknjavalists.h, aknshortcuts.h and eikslbd.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomlists.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMLists::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        // test functions in aknjavalists.h
        ENTRY( "TestLargeListDefCon", CTestDOMLists::TestLargeListDefConL ),
        ENTRY( "TestLargeListSizeChanged",
                CTestDOMLists::TestLargeListSizeChangedL ),
        ENTRY( "TestLargeListMinimumSize",
                CTestDOMLists::TestLargeListMinimumSizeL ),
        ENTRY( "TestLargeListCreateItemDrawerL",
                CTestDOMLists::TestLargeListCreateItemDrawerL ),
        ENTRY( "TestListDefCon", CTestDOMLists::TestListDefConL ),
        ENTRY( "TestListSizeChanged", CTestDOMLists::TestListSizeChangedL ),
        ENTRY( "TestListMinimumSize", CTestDOMLists::TestListMinimumSizeL ),
        ENTRY( "TestListUseEmptyIconSpace",
                CTestDOMLists::TestListUseEmptyIconSpaceL ),
        ENTRY( "TestListCreateItemDrawerL",
                CTestDOMLists::TestListCreateItemDrawerL ),

        // test functions in aknshortcuts.h
        // methods of AknListBoxShortCutTemplate class
        ENTRY( "TestTempConstructL", CTestDOMLists::TestTempConstructL ),
        ENTRY( "TestTempConstructFromResourceL",
                CTestDOMLists::TestTempConstructFromResourceL ),
        ENTRY( "TestTempOfferKeyEventL", CTestDOMLists::TestTempOfferKeyEventL ),
        ENTRY( "TestTempShortcutValueForNextList",
                CTestDOMLists::TestTempShortcutValueForNextListL ),
        ENTRY( "TestTempSetShortcutValueFromPrevList",
                CTestDOMLists::TestTempSetShortcutValueFromPrevListL ),
        ENTRY( "TestTempSetShortcutEnabledL",
                CTestDOMLists::TestTempSetShortcutEnabledL ),

        // methods of AknListBoxShortCuts class
        ENTRY( "TestCutsDefCon", CTestDOMLists::TestCutsDefConL ),
        ENTRY( "TestCutsConstructL", CTestDOMLists::TestCutsConstructL ),
        ENTRY( "TestCutsOfferKeyEventL", CTestDOMLists::TestCutsOfferKeyEventL ),
        ENTRY( "TestCutsRecursionLock", CTestDOMLists::TestCutsRecursionLockL ),
        ENTRY( "TestCutsRecursionUnlock",
                CTestDOMLists::TestCutsRecursionUnlockL ),
        ENTRY( "TestCutsRunL", CTestDOMLists::TestCutsRunL ),
        ENTRY( "TestCutsChangeStateL", CTestDOMLists::TestCutsChangeStateL ),
        ENTRY( "TestCutsDoProcedureL", CTestDOMLists::TestCutsDoProcedureL ),
        ENTRY( "TestCutsStartTimerL", CTestDOMLists::TestCutsStartTimerL ),
        ENTRY( "TestCutsEndTimer", CTestDOMLists::TestCutsEndTimerL ),

        // methods of AknListBoxShortCutsImplementation class
        ENTRY( "TestImpleDefCon", CTestDOMLists::TestImpleDefConL ),
        ENTRY( "TestImpleConstructL", CTestDOMLists::TestImpleConstructL ),
        ENTRY( "TestImpleDoTest", CTestDOMLists::TestImpleDoTestL ),
        ENTRY( "TestImpleDoActionL", CTestDOMLists::TestImpleDoActionL ),
        ENTRY( "TestImpleOfferKeyEventL",
                CTestDOMLists::TestImpleOfferKeyEventL ),
        ENTRY( "TestImpleShortcutValueForNextList",
                CTestDOMLists::TestImpleShortcutValueForNextListL ),
        ENTRY( "TestImpleSetShortcutValueFromPrevList",
                CTestDOMLists::TestImpleSetShortcutValueFromPrevListL ),
        ENTRY( "TestImpleProcessCommandL",
                CTestDOMLists::TestImpleProcessCommandL ),

        // test functions in aknjavalists.h
        ENTRY( "TestSetDataNewL", CTestDOMLists::TestSetDataNewL ),
        ENTRY( "TestSetDataDraw", CTestDOMLists::TestSetDataDrawL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
