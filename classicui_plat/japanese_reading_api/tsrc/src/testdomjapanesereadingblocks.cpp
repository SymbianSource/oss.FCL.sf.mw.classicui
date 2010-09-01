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
* Description:  test japanese_reading_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomjapanesereading.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomJapaneseReading::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomJapaneseReading::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestJRCreateL", CTestDomJapaneseReading::TestJRCreateL ),
        ENTRY( "TestJRReadingTextL", CTestDomJapaneseReading::TestJRReadingTextL ),
        ENTRY( "TestRCNewL", CTestDomJapaneseReading::TestRCNewL ),
        ENTRY( "TestRCNewCEikEdwinL", CTestDomJapaneseReading::TestRCNewCEikEdwinL ),
        ENTRY( "TestRCHandleCompletionOfTransactionL", CTestDomJapaneseReading::TestRCHandleCompletionOfTransactionL ),
        ENTRY( "TestRCSetMainEditorL", CTestDomJapaneseReading::TestRCSetMainEditorL ),
        ENTRY( "TestRCMainEditorL", CTestDomJapaneseReading::TestRCMainEditorL ),
        ENTRY( "TestRCSetReadingEditorL", CTestDomJapaneseReading::TestRCSetReadingEditorL ),
        ENTRY( "TestRCReadingEditorL", CTestDomJapaneseReading::TestRCReadingEditorL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }



//  [End of File]
