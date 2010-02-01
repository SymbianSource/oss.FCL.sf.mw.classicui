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
* Description:  test skinnable_clock_api
 *
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknskinnableclock.h>
#include <e32const.h>

#include "testdomskinnableclock.h"

//CONSTANTS
const TInt KWidth = 25;
const TInt KHeight = 25;


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomSkinnableClock::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomSkinnableClock::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestSCNewL", CTestDomSkinnableClock::TestSCNewL ),
        ENTRY( "TestSCUpdateDisplayL", CTestDomSkinnableClock::TestSCUpdateDisplayL ),
        ENTRY( "TestSCSetFormatL", CTestDomSkinnableClock::TestSCSetFormatL ),
        ENTRY( "TestSCPositionChangedL", CTestDomSkinnableClock::TestSCPositionChangedL ),
        ENTRY( "TestSCHandlePointerEventL", CTestDomSkinnableClock::TestSCHandlePointerEventL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


// -----------------------------------------------------------------------------
// CTestDomSkinnableClock::TestSCNewL
// -----------------------------------------------------------------------------
//

TInt CTestDomSkinnableClock::TestSCNewL( CStifItemParser& /*aItem*/ )
    {
    CAknSkinnableClock* clock = CAknSkinnableClock::NewL( iContainer, ETrue,ETrue );
    CleanupStack::PushL( clock );
    STIF_ASSERT_NOT_NULL( clock );
    CleanupStack::PopAndDestroy( clock );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSkinnableClock::TestSCUpdateDisplayL
// -----------------------------------------------------------------------------
//

TInt CTestDomSkinnableClock::TestSCUpdateDisplayL( CStifItemParser& /*aItem*/ )
    {
    CAknSkinnableClock* clock = CAknSkinnableClock::NewL( iContainer, ETrue,ETrue );
    CleanupStack::PushL( clock );
    clock->UpdateDisplay();
    STIF_ASSERT_NOT_NULL( clock );
    CleanupStack::PopAndDestroy( clock );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSkinnableClock::TestSCSetFormatL
// -----------------------------------------------------------------------------
//

TInt CTestDomSkinnableClock::TestSCSetFormatL( CStifItemParser& /*aItem*/ )
    {
    CAknSkinnableClock* clock = CAknSkinnableClock::NewL( iContainer, ETrue,ETrue );
    CleanupStack::PushL( clock );
    clock->SetFormatL( EClockDigital );
    STIF_ASSERT_NOT_NULL( clock );
    CleanupStack::PopAndDestroy( clock );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSkinnableClock::TestSCPositionChangedL
// -----------------------------------------------------------------------------
//

TInt CTestDomSkinnableClock::TestSCPositionChangedL( CStifItemParser& /*aItem*/ )
    {
    CAknSkinnableClock* clock = CAknSkinnableClock::NewL( iContainer, ETrue,ETrue );
    CleanupStack::PushL( clock );
    clock->PositionChanged();
    STIF_ASSERT_NOT_NULL( clock );
    CleanupStack::PopAndDestroy( clock );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSkinnableClock::TestSCHandlePointerEventL
// -----------------------------------------------------------------------------
//

TInt CTestDomSkinnableClock::TestSCHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknSkinnableClock* clock = CAknSkinnableClock::NewL( iContainer, ETrue,ETrue );
    CleanupStack::PushL( clock );
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KWidth, KHeight );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    clock->HandlePointerEventL( event );
    STIF_ASSERT_NOT_NULL( clock );
    CleanupStack::PopAndDestroy( clock );
    return KErrNone;
    }



//  [End of File]
