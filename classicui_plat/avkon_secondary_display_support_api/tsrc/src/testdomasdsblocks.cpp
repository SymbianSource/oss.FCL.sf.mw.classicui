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
* Description:  avkon_secondary_display_support_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomasds.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMASDS::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMASDS::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestMFNewL", CTestDOMASDS::TestMFNewL ),
        ENTRY( "TestMFIssueCommand", CTestDOMASDS::TestMFIssueCommandL ),
        ENTRY( "TestMFCancelCommand", CTestDOMASDS::TestMFCancelCommandL ),
        ENTRY( "TestMFResetBuffer", CTestDOMASDS::TestMFResetBufferL ),
        ENTRY( "TestMFSetObserver", CTestDOMASDS::TestMFSetObserverL ),
        ENTRY( "TestMFPostUpdatedDataL", CTestDOMASDS::TestMFPostUpdatedDataL ),
        ENTRY( "TestSDDExternalizeL", CTestDOMASDS::TestSDDExternalizeL ),
        ENTRY( "TestSDDInternalizeL", CTestDOMASDS::TestSDDInternalizeL ),
        ENTRY( "TestSDDInsertGlobalListQueryItemIdsL", CTestDOMASDS::TestSDDInsertGlobalListQueryItemIdsL ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }




//  [End of File]
