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
* Description:  test special_character_table_api
*
*/



// INCLUDE FILES
#include "testdomspecialchartab.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestCMDCAknCharMapDialogL", CTestDomSpecialCharTab::TestCMDCAknCharMapDialogL ),
        ENTRY( "TestCMDExecuteLDL", CTestDomSpecialCharTab::TestCMDExecuteLDL ),
        ENTRY( "TestCMDOfferKeyEventL", CTestDomSpecialCharTab::TestCMDOfferKeyEventL ),
        ENTRY( "TestCMDHandleResourceChangeL", CTestDomSpecialCharTab::TestCMDHandleResourceChangeL ),
        ENTRY( "TestCMDShowNoPictographsL", CTestDomSpecialCharTab::TestCMDShowNoPictographsL ),
        ENTRY( "TestCMDShowPictographsFirstL", CTestDomSpecialCharTab::TestCMDShowPictographsFirstL ),
        ENTRY( "TestCMDShowAnotherTableL", CTestDomSpecialCharTab::TestCMDShowAnotherTableL ),
        ENTRY( "TestCMDHandleControlEventL", CTestDomSpecialCharTab::TestCMDHandleControlEventL ),
        ENTRY( "TestCMDHandleDialogPageEventL", CTestDomSpecialCharTab::TestCMDHandleDialogPageEventL ),
        ENTRY( "TestCMDLockNumericKeysL", CTestDomSpecialCharTab::TestCMDLockNumericKeysL ),
        ENTRY( "TestCMDDisableRecentCharsRowL", CTestDomSpecialCharTab::TestCMDDisableRecentCharsRowL ),
        ENTRY( "TestCMCAknCharMapL", CTestDomSpecialCharTab::TestCMCAknCharMapL ),
        ENTRY( "TestCMSetBufferL", CTestDomSpecialCharTab::TestCMSetBufferL ),
        ENTRY( "TestCMMinimumSizeL", CTestDomSpecialCharTab::TestCMMinimumSizeL ),
        ENTRY( "TestCMOfferKeyEventL", CTestDomSpecialCharTab::TestCMOfferKeyEventL ),
        ENTRY( "TestCMInputCapabilitiesL", CTestDomSpecialCharTab::TestCMInputCapabilitiesL ),
        ENTRY( "TestCMActivateL", CTestDomSpecialCharTab::TestCMActivateL ),
        ENTRY( "TestCMDoSizeChangedL", CTestDomSpecialCharTab::TestCMDoSizeChangedL ),
        ENTRY( "TestCMDoHandleResourceChangeL", CTestDomSpecialCharTab::TestCMDoHandleResourceChangeL ),
        ENTRY( "TestCMDoCountComponentControlsL", CTestDomSpecialCharTab::TestCMDoCountComponentControlsL ),
        ENTRY( "TestCMDoComponentControlL", CTestDomSpecialCharTab::TestCMDoComponentControlL ),
        ENTRY( "TestCMHandlePointerEventL", CTestDomSpecialCharTab::TestCMHandlePointerEventL ),
        ENTRY( "TestCMSetObserverL", CTestDomSpecialCharTab::TestCMSetObserverL ),
        ENTRY( "TestCMConstructMenuSctRowL", CTestDomSpecialCharTab::TestCMConstructMenuSctRowL ),
        ENTRY( "TestCMSetMenuSctRectL", CTestDomSpecialCharTab::TestCMSetMenuSctRectL ),
        ENTRY( "TestCMConstructMenuSctRowIdL", CTestDomSpecialCharTab::TestCMConstructMenuSctRowIdL ),
        ENTRY( "TestCMHighlightSctRowL", CTestDomSpecialCharTab::TestCMHighlightSctRowL ),
        ENTRY( "TestCMDHandlePointerEventLL", CTestDomSpecialCharTab::TestCMDHandlePointerEventLL ),

        
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//  [End of File]


