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
* Description:  test aknindicator.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknindicator.h>

#include "testdomindicator.h"
#include "testdomindicatorcontainer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomIndicator::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomIndicator::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestSetIndicatorObserver",
                CTestDomIndicator::TestSetIndicatorObserverL ),
        ENTRY( "TestHandlePointerEventL",
                CTestDomIndicator::TestHandlePointerEventL ),
        ENTRY( "TestPositionChanged",
                CTestDomIndicator::TestPositionChangedL ),
        ENTRY( "TestGetBitmapIndexL", CTestDomIndicator::TestGetBitmapIndexL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDomIndicator::TestSetIndicatorObserverL
// -----------------------------------------------------------------------------
//
TInt CTestDomIndicator::TestSetIndicatorObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDomIndicator, "testdomindicator" );
    _LIT( KTestSetIndicatorObserver, "In SetIndicatorObserver" );
    TestModuleIf().Printf( 0, KTestDomIndicator, KTestSetIndicatorObserver );
    // Print to log file
    iLog->Log( KTestSetIndicatorObserver );

    CTestDomIndicatorContainer* indicatorPane = CTestDomIndicatorContainer::NewLC();
    CCoeControl* indicatorControl = indicatorPane->ComponentControl( 0 );
    CAknIndicator* aknIndicator = static_cast<CAknIndicator*>( indicatorControl );

    aknIndicator->SetIndicatorObserver( NULL );

    CleanupStack::PopAndDestroy( indicatorPane );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDomIndicator::TestHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestDomIndicator::TestHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDomIndicator, "testdomindicator" );
    _LIT( KTestHandlePointerEventL, "In HandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestDomIndicator, KTestHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestHandlePointerEventL );

    CTestDomIndicatorContainer* indicatorPane = CTestDomIndicatorContainer::NewLC();
    CCoeControl* indicatorControl = indicatorPane->ComponentControl( 0 );
    CAknIndicator* aknIndicator = static_cast<CAknIndicator*>( indicatorControl );

    TPointerEvent  pointerEvent ;
    pointerEvent.iType = TPointerEvent::EMove;
    aknIndicator->HandlePointerEventL( pointerEvent );

    CleanupStack::PopAndDestroy( indicatorPane );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDomIndicator::TestPositionChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDomIndicator::TestPositionChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDomIndicator, "testdomindicator" );
    _LIT( KTestPositionChanged, "In PositionChanged" );
    TestModuleIf().Printf( 0, KTestDomIndicator, KTestPositionChanged );
    // Print to log file
    iLog->Log( KTestPositionChanged );

    CTestDomIndicatorContainer* indicatorPane = CTestDomIndicatorContainer::NewLC();
    CCoeControl* indicatorControl = indicatorPane->ComponentControl( 0 );
    CAknIndicator* aknIndicator = static_cast<CAknIndicator*>( indicatorControl );

    aknIndicator->PositionChanged();

    CleanupStack::PopAndDestroy( indicatorPane );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDomIndicator::TestGetBitmapIndexL
// -----------------------------------------------------------------------------
//
TInt CTestDomIndicator::TestGetBitmapIndexL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDomIndicator, "testdomindicator" );
    _LIT( KTestGetBitmapIndexL, "In GetBitmapIndexL" );
    TestModuleIf().Printf( 0, KTestDomIndicator, KTestGetBitmapIndexL );
    // Print to log file
    iLog->Log( KTestGetBitmapIndexL );

    TInt bitmapIndex = 0;
    TInt maskIndex = 0 ;
    CAknIndicator::GetBitmapIndexL( 0, 0, bitmapIndex, maskIndex );

    return KErrNone;

    }


//  [End of File]
