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
* Description:  test aknsgcc.h, aknstatuspaneutils.h and aknsyncdraw.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomstatuspane.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        // test functions of aknsgcc.h
        ENTRY( "TestSgccCreateL", CTestDOMStatusPane::TestSgccCreateL ),
        ENTRY( "TestSgccHandleChangeL",
                CTestDOMStatusPane::TestSgccHandleChangeL ),
        ENTRY( "TestSgccAknSrv", CTestDOMStatusPane::TestSgccAknSrvL ),
        ENTRY( "TestSgccSetStatusPaneRedrawCoordinator",
                CTestDOMStatusPane::TestSgccSetStatusPaneRedrawCoordinator ),
        ENTRY( "TestSgccBlockServerStatusPaneRedrawsL",
                CTestDOMStatusPane::TestSgccBlockServerStatusPaneRedrawsL ),
        ENTRY( "TestSgccRedrawServerStatusPane",
                CTestDOMStatusPane::TestSgccRedrawServerStatusPane ),
        ENTRY( "TestSgccDrawSynchronizer",
                CTestDOMStatusPane::TestSgccDrawSynchronizerL ),
        ENTRY( "TestSgccPrepareForAppExit",
                CTestDOMStatusPane::TestSgccPrepareForAppExit ),
        ENTRY( "TestSgccSetSystemFaded",
                CTestDOMStatusPane::TestSgccSetSystemFaded ),
        ENTRY( "TestSgccIsSystemFaded",
                CTestDOMStatusPane::TestSgccIsSystemFaded ),
        ENTRY( "TestSgccPixelsAndRotation",
                CTestDOMStatusPane::TestSgccPixelsAndRotation ),
        ENTRY( "TestSgccCalculatePixelsAndRotation",
                CTestDOMStatusPane::TestSgccCalculatePixelsAndRotation ),
        ENTRY( "TestSgccScreenMode", CTestDOMStatusPane::TestSgccScreenMode ),
        ENTRY( "TestSgccCalculateScreenMode",
                CTestDOMStatusPane::TestSgccCalculateScreenMode ),
        ENTRY( "TestSgccCalculateScreenModeWithInt",
                CTestDOMStatusPane::TestSgccCalculateScreenModeWithInt ),
        ENTRY( "TestSgccSetKeyBlockMode",
                CTestDOMStatusPane::TestSgccSetKeyBlockMode ),
        ENTRY( "TestSgccSetKeyboardRepeatRate",
                CTestDOMStatusPane::TestSgccSetKeyboardRepeatRate ),
        ENTRY( "TestSgccCurrentStatuspaneResource",
                CTestDOMStatusPane::TestSgccCurrentStatuspaneResource ),
        ENTRY( "TestSgccLayoutConfig", 
                CTestDOMStatusPane::TestSgccLayoutConfig ),
        ENTRY( "TestSgccLayoutConfigBuf",
                CTestDOMStatusPane::TestSgccLayoutConfigBuf ),
        ENTRY( "TestSgccMoveApp", CTestDOMStatusPane::TestSgccMoveApp ),
        ENTRY( "TestSgccSetImpl", CTestDOMStatusPane::TestSgccSetImplL ),

        // test functions of aknstatuspaneutils.h
        ENTRY( "TestUtilsStaconPaneActive",
                CTestDOMStatusPane::TestUtilsStaconPaneActive ),
        ENTRY( "TestUtilsStaconSoftKeysLeft",
                CTestDOMStatusPane::TestUtilsStaconSoftKeysLeft ),
        ENTRY( "TestUtilsStaconSoftKeysRight",
                CTestDOMStatusPane::TestUtilsStaconSoftKeysRight ),
        ENTRY( "TestUtilsIdleLayoutActive",
                CTestDOMStatusPane::TestUtilsIdleLayoutActive ),
        ENTRY( "TestUtilsFlatLayoutActive",
                CTestDOMStatusPane::TestUtilsFlatLayoutActive ),
        ENTRY( "TestUtilsUsualLayoutActive",
                CTestDOMStatusPane::TestUtilsUsualLayoutActive ),
        ENTRY( "TestUtilsSmallLayoutActive",
                CTestDOMStatusPane::TestUtilsSmallLayoutActive ),
        ENTRY( "TestUtilsTouchPaneCompatibleLayoutActive",
                CTestDOMStatusPane::TestUtilsTouchPaneCompatibleLayoutActive ),
        ENTRY( "TestUtilsExtendedStaconPaneActive",
                CTestDOMStatusPane::TestUtilsExtendedStaconPaneActive ),
        ENTRY( "TestUtilsExtendedFlatLayoutActive",
                CTestDOMStatusPane::TestUtilsExtendedFlatLayoutActive ),

        // test functions of aknstatuspaneutils.h
        ENTRY( "TestSyncDefConL", CTestDOMStatusPane::TestSyncDefConL ),
        ENTRY( "TestSyncSetControl", CTestDOMStatusPane::TestSyncSetControlL ),
        ENTRY( "TestSyncMasrPrepareForDraw",
                CTestDOMStatusPane::TestSyncMasrPrepareForDrawL ),
        ENTRY( "TestSyncMasrDraw", CTestDOMStatusPane::TestSyncMasrDrawL ),
        ENTRY( "TestSyncMasrDeactivateGc",
                CTestDOMStatusPane::TestSyncMasrDeactivateGcL ),
        ENTRY( "TestSyncMasrActivateGc",
                CTestDOMStatusPane::TestSyncMasrActivateGcL ),
        ENTRY( "TestSynchNewL", CTestDOMStatusPane::TestSynchNewL ),
        ENTRY( "TestSynchAddL", CTestDOMStatusPane::TestSynchAddL ),
        ENTRY( "TestSynchRemove", CTestDOMStatusPane::TestSynchRemoveL ),
        ENTRY( "TestSynchSignal", CTestDOMStatusPane::TestSynchSignalL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
