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
* Description:  test aknlongtapanimation.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknlongtapanimation.h>

#include "testdomlongtap.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMLongTap::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMLongTap::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestNewL", CTestDOMLongTap::TestNewL ),
        ENTRY( "TestNewLC", CTestDOMLongTap::TestNewLCL ),
        ENTRY( "TestShowAnimationL", CTestDOMLongTap::TestShowAnimationL ),
        ENTRY( "TestHideAnimation", CTestDOMLongTap::TestHideAnimationL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMLongTap::TestNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLongTap::TestNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMLongTap, "testdomlongtap" );
    _LIT( KTestNewL, "In NewL" );
    TestModuleIf().Printf( 0, KTestDOMLongTap, KTestNewL );
    // Print to log file
    iLog->Log( KTestNewL );

    CAknLongTapAnimation* animation = CAknLongTapAnimation::NewL();
    CleanupStack::PushL( animation );
    STIF_ASSERT_NOT_NULL( animation );

    CleanupStack::PopAndDestroy( animation );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLongTap::TestNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLongTap::TestNewLCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMLongTap, "testdomlongtap" );
    _LIT( KTestNewLC, "In NewLC" );
    TestModuleIf().Printf( 0, KTestDOMLongTap, KTestNewLC );
    // Print to log file
    iLog->Log( KTestNewLC );

    CAknLongTapAnimation* animation = CAknLongTapAnimation::NewLC();
    STIF_ASSERT_NOT_NULL( animation );

    CleanupStack::PopAndDestroy( animation );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLongTap::TestShowAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLongTap::TestShowAnimationL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMLongTap, "testdomlongtap" );
    _LIT( KTestShowAnimationL, "In ShowAnimationL" );
    TestModuleIf().Printf( 0, KTestDOMLongTap, KTestShowAnimationL );
    // Print to log file
    iLog->Log( KTestShowAnimationL );

    CAknLongTapAnimation* animation = CAknLongTapAnimation::NewLC();

    animation->ShowAnimationL( 0, 0 );

    CleanupStack::PopAndDestroy( animation );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLongTap::TestHideAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLongTap::TestHideAnimationL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMLongTap, "testdomlongtap" );
    _LIT( KTestHideAnimation, "In HideAnimation" );
    TestModuleIf().Printf( 0, KTestDOMLongTap, KTestHideAnimation );
    // Print to log file
    iLog->Log( KTestHideAnimation );

    CAknLongTapAnimation* animation = CAknLongTapAnimation::NewLC();

    animation->HideAnimation();

    CleanupStack::PopAndDestroy( animation );
    return KErrNone;

    }


//  [End of File]
