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
* Description:  Test AknTasHook.h
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testplattestability.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestPlatTestAbility::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestPlatTestAbility::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        // [test cases entries]
        //AknTasHook.h
        ENTRY( "TestCAknTasHookAddL", CTestPlatTestAbility::TestCAknTasHookAddL ), 
        ENTRY( "TestCAknTasHookRemoveL", CTestPlatTestAbility::TestCAknTasHookRemoveL ), 
        ENTRY( "TestCAknTasHookGetL", CTestPlatTestAbility::TestCAknTasHookGetL ), 
        ENTRY( "TestCAknTasHookGetAllL", CTestPlatTestAbility::TestCAknTasHookGetAllL ), 
        ENTRY( "TestCAknTasHookGetAknUiLCL", CTestPlatTestAbility::TestCAknTasHookGetAknUiLCL ), 

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

