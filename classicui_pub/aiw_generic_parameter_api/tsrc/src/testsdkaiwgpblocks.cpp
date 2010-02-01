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
* Description:    No test functions of TestSDKAiwgp implement
*
*/





// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkaiwgp.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKAiwgp::Delete() 
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestTAiwVariantL", CTestSDKAiwgp::TestTAiwVariantL ),
        ENTRY( "TestTAiwGP", CTestSDKAiwgp::TestTAiwGP ),
        ENTRY( "TestTAiwGPListNewFunctionsL", CTestSDKAiwgp::TestTAiwGPListNewFunctionsL ),
        ENTRY( "TestTAiwGPListCountL", CTestSDKAiwgp::TestTAiwGPListCountL ),
        ENTRY( "TestTAiwGPListSquareBracketL", CTestSDKAiwgp::TestTAiwGPListSquareBracketL ),
        ENTRY( "TestTAiwGPListAppendL", CTestSDKAiwgp::TestTAiwGPListAppendL ),
        ENTRY( "TestTAiwGPListResetL", CTestSDKAiwgp::TestTAiwGPListResetL ),
        ENTRY( "TestTAiwGPListFindL", CTestSDKAiwgp::TestTAiwGPListFindL ),
        ENTRY( "TestTAiwGPListSizeL", CTestSDKAiwgp::TestTAiwGPListSizeL ),
        ENTRY( "TestTAiwGPListRemoveL", CTestSDKAiwgp::TestTAiwGPListRemoveL ),
        ENTRY( "TestTAiwGPListInternalizeLAndExternalizeL", CTestSDKAiwgp::TestTAiwGPListInternalizeLAndExternalizeL ),
        ENTRY( "TestTAiwGPListPackForServerL", CTestSDKAiwgp::TestTAiwGPListPackForServerL ),
        ENTRY( "TestTAiwGPListUnpackFromClientL", CTestSDKAiwgp::TestTAiwGPListUnpackFromClientL ),
        

        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove
        
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//  [End of File] - Do not remove
