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
* Description:  Test AknClearer.h & eikspace.h
*
*/



// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkscreenclearer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestsSDKScreenClearer::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        // AknClear.h
        ENTRY( "TestLSCNewL", CTestsSDKScreenClearer::TestLSCNewL ),
        ENTRY( "TestLSCNewLC", CTestsSDKScreenClearer::TestLSCNewLC ),
        ENTRY( "TestLSCNewLCSC", CTestsSDKScreenClearer::TestLSCSNewLC ),
        ENTRY( "TestSCBHandleStatusPaneSizeChangeL", CTestsSDKScreenClearer::TestSCBHandleStatusPaneSizeChangeL ),
        ENTRY( "TestSCBHandlePointerEventL", CTestsSDKScreenClearer::TestSCBHandlePointerEventL ),
        ENTRY( "TestSCBHandleResourceChangeL", CTestsSDKScreenClearer::TestSCBHandleResourceChangeL ),
        ENTRY( "TestSCBDeleteL", CTestsSDKScreenClearer::TestSCBDeleteL ),
        ENTRY( "TestSCBConstructL", CTestsSDKScreenClearer::TestSCBConstructL ),
        
        // eikspace.h
        ENTRY( "TestSpacerConstructor", CTestsSDKScreenClearer::TestSpacerConstructorL ),
        ENTRY( "TestSpacerSConstructor", CTestsSDKScreenClearer::TestSpacerSConstructorL ),
        ENTRY( "TestSpacerDestructor", CTestsSDKScreenClearer::TestSpacerDestructor ),
        ENTRY( "TestSpacerSetWidth", CTestsSDKScreenClearer::TestSpacerSetWidth ),
        ENTRY( "TestSpacerSetHeight", CTestsSDKScreenClearer::TestSpacerSetHeight ),
        ENTRY( "TestSpacerSetColor", CTestsSDKScreenClearer::TestSpacerSetColor ),
        ENTRY( "TestSpacerSetClear", CTestsSDKScreenClearer::TestSpacerSetClear ),
        ENTRY( "TestSpacerHandlePointerEventL", CTestsSDKScreenClearer::TestSpacerHandlePointerEventL ),
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//  [End of File] - Do not remove
