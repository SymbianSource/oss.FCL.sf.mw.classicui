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
* Description:  No test functions of CTestSDKBaseControls implement
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkbasecontrols.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKBaseControls::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestCAknControlContructorL", CTestSDKBaseControls::TestCAknControlContructorL ),
        ENTRY( "TestCAknControlDecontructorL", CTestSDKBaseControls::TestCAknControlDecontructorL ),
        ENTRY( "TestCEikAlignedControlContructorL", CTestSDKBaseControls::TestCEikAlignedControlContructorL ),
        ENTRY( "TestCEikAlignedControlDecontructorL", CTestSDKBaseControls::TestCEikAlignedControlDecontructorL ),
        ENTRY( "TestCEikAlignedControlSetAllMarginsToL", CTestSDKBaseControls::TestCEikAlignedControlSetAllMarginsToL ),
        ENTRY( "TestCEikAlignedControlSetAlignmentL", CTestSDKBaseControls::TestCEikAlignedControlSetAlignmentL ),
        ENTRY( "TestCEikAlignedControlHandlePointerEventL", CTestSDKBaseControls::TestCEikAlignedControlHandlePointerEventL ),
        ENTRY( "TestCEikAlignedControlWriteInternalStateL", CTestSDKBaseControls::TestCEikAlignedControlWriteInternalStateL ),
        ENTRY( "TestCEikBorderedControlContructorL", CTestSDKBaseControls::TestCEikBorderedControlContructorL ),
        ENTRY( "TestCEikBorderedControlHasBorderL", CTestSDKBaseControls::TestCEikBorderedControlHasBorderL ),
        ENTRY( "TestCEikBorderedControlSetAdjacentL", CTestSDKBaseControls::TestCEikBorderedControlSetAdjacentL ),
        ENTRY( "TestCEikBorderedControlGetColorUseListL", CTestSDKBaseControls::TestCEikBorderedControlGetColorUseListL ),
        ENTRY( "TestCEikBorderedControlHandleResourceChangeL", CTestSDKBaseControls::TestCEikBorderedControlHandleResourceChangeL ),
        ENTRY( "TestCEikBorderedControlHandlePointerEventL", CTestSDKBaseControls::TestCEikBorderedControlHandlePointerEventL ),
        ENTRY( "TestCEikBorderedControlSetBorderL", CTestSDKBaseControls::TestCEikBorderedControlSetBorderL ),
        ENTRY( "TestCEikBorderedControlBorderL", CTestSDKBaseControls::TestCEikBorderedControlBorderL ),
        ENTRY( "TestCEikBorderedControlDrawL", CTestSDKBaseControls::TestCEikBorderedControlDrawL ),
        ENTRY( "TestCEikBorderedControlWriteInternalStateL", CTestSDKBaseControls::TestCEikBorderedControlWriteInternalStateL ),
        
        // [test cases entries]
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }



//  [End of File]
