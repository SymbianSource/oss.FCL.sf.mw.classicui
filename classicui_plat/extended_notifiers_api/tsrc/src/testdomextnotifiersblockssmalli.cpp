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
* Description:  test functions for testing AknSmallIndicator.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknsmallindicator.h>
#include <aknindicator.h>

#include "testdomextnotifiers.h"


// CONSTANTS
const TUid KIndicatorUid = { 0x00000001 };


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASINewL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASINewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASINewL, "TestCASINewL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASINewL );
    // Print to log file
    iLog->Log( KTestCASINewL );
    
    CAknSmallIndicator* indicator = CAknSmallIndicator::NewL( KIndicatorUid );
    CleanupStack::PushL( indicator );
    
    STIF_ASSERT_NOT_NULL( indicator );
    
    CleanupStack::PopAndDestroy( indicator );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASINewLCL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASINewLCL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASINewLCL, "TestCASINewLCL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASINewLCL );
    // Print to log file
    iLog->Log( KTestCASINewLCL );
    
    CAknSmallIndicator* indicator = CAknSmallIndicator::NewLC( KIndicatorUid );
    
    STIF_ASSERT_NOT_NULL( indicator );
    
    CleanupStack::PopAndDestroy( indicator );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASISetIndicatorStateL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASISetIndicatorStateL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASISetIndicatorStateL, "TestCASISetIndicatorStateL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASISetIndicatorStateL );
    // Print to log file
    iLog->Log( KTestCASISetIndicatorStateL );
    
    CAknSmallIndicator* indicator = CAknSmallIndicator::NewL( KIndicatorUid );
    CleanupStack::PushL( indicator );
    
    indicator->SetIndicatorStateL( MAknIndicator::EIndicatorOff );
    
    CleanupStack::PopAndDestroy( indicator );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASIHandleIndicatorTapL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASIHandleIndicatorTapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASIHandleIndicatorTapL, "TestCASIHandleIndicatorTapL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASIHandleIndicatorTapL );
    // Print to log file
    iLog->Log( KTestCASIHandleIndicatorTapL );
    
    CAknSmallIndicator* indicator = CAknSmallIndicator::NewL( KIndicatorUid );
    CleanupStack::PushL( indicator );
    
    indicator->HandleIndicatorTapL();
    
    CleanupStack::PopAndDestroy( indicator );
    
    return KErrNone;
    }


//  [End of File]
