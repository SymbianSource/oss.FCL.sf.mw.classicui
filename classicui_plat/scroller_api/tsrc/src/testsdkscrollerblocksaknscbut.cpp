/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test aknscbut.h
*
*/


// [INCLUDE FILES]
#include <aknscbut.h>

#include "testsdkscroller.h"
#include "testsdkscrollercontrol.h"

// CONSTANTS
const TInt KScrollSpan = 9;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKAknScbNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKAknScbNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKAknScbNewL, "in AknScButNewL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKAknScbNewL );
    // Print to log file
    iLog->Log( KTestSDKAknScbNewL );

    CAknScrollButton::TType type = CAknScrollButton::ENudgeLeft;
    CAknScrollButton* scButton = CAknScrollButton::NewL( type );
    CleanupStack::PushL( scButton );
    STIF_ASSERT_NOT_NULL( scButton );

    CleanupStack::PopAndDestroy( scButton );
     return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKAknScbNewLWithScBarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKAknScbNewLWithScBarL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKAknScbNewLWithScBarL, "in AknScButNewLWithScBarL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKAknScbNewLWithScBarL );
    // Print to log file
    iLog->Log( KTestSDKAknScbNewLWithScBarL );

    CAknScrollButton::TType type = CAknScrollButton::ENudgeLeft;
    CAknScrollButton::TTypeOfScrollBar scType = CAknScrollButton::ENormal;

    CAknScrollButton* scButton = CAknScrollButton::NewL( type, scType );
    CleanupStack::PushL( scButton );
    STIF_ASSERT_NOT_NULL( scButton );

    CleanupStack::PopAndDestroy( scButton );
     return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKAknScbTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKAknScbTypeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKAknScbType, "in AknScButType" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKAknScbType );
    // Print to log file
    iLog->Log( KTestSDKAknScbType );

    CAknScrollButton::TType type = CAknScrollButton::ENudgeLeft;
    CAknScrollButton* scButton = CAknScrollButton::NewL( type );
    CleanupStack::PushL( scButton );

    CAknScrollButton::TType scButType = scButton->Type();
    STIF_ASSERT_EQUALS( type, scButType );

    CleanupStack::PopAndDestroy( scButton );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKAknScbCreWinOnlyForArrsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKAknScbCreWinOnlyForArrsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKAknScbCreWinOnlyForArrsL, "in AknScButCreWinOnlyForArrsL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKAknScbCreWinOnlyForArrsL );
    // Print to log file
    iLog->Log( KTestSDKAknScbCreWinOnlyForArrsL );

    CAknScrollButton::TType type = CAknScrollButton::ENudgeLeft;
    CAknScrollButton* scButton = CAknScrollButton::NewL( type );
    CleanupStack::PushL( scButton );
    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );

    scButton->CreateWindowOnlyForArrowsL( control );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( scButton );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKAknScbIsNormalSbUsingButL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKAknScbIsNormalSbUsingButL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKAknScbIsNormalSbUsingBut, "in AknScButIsNormalSbUsingBut" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKAknScbIsNormalSbUsingBut );
    // Print to log file
    iLog->Log( KTestSDKAknScbIsNormalSbUsingBut );

    CAknScrollButton::TType type = CAknScrollButton::ENudgeLeft;
    CAknScrollButton* scButton = CAknScrollButton::NewL( type );
    CleanupStack::PushL( scButton );

    scButton->IsNormalScrollBarUsingButton();

    CleanupStack::PopAndDestroy( scButton );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKAknScbSetTypeOfSbUsingButL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKAknScbSetTypeOfSbUsingButL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKAknScbSetTypeOfSbUsingBut, "in AknScButSetTypeOfSbUsingBut" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKAknScbSetTypeOfSbUsingBut );
    // Print to log file
    iLog->Log( KTestSDKAknScbSetTypeOfSbUsingBut );

    CAknScrollButton::TType type = CAknScrollButton::ENudgeLeft;
    CAknScrollButton* scButton = CAknScrollButton::NewL( type );
    CleanupStack::PushL( scButton );

    CAknScrollButton::TTypeOfScrollBar scType = CAknScrollButton::ENormal;
    scButton->SetTypeOfScrollBarUsingButton( scType );

    CleanupStack::PopAndDestroy( scButton );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKAknScbSetPositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKAknScbSetPositionL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKAknScbSetPosition, "in AknScButSetPosition" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKAknScbSetPosition );
    // Print to log file
    iLog->Log( KTestSDKAknScbSetPosition );

    CAknScrollButton::TType type = CAknScrollButton::ENudgeLeft;
    CAknScrollButton* scButton = CAknScrollButton::NewL( type );
    CleanupStack::PushL( scButton );

    TInt focusPosition = 0;
    scButton->SetPosition( focusPosition, KScrollSpan );

    CleanupStack::PopAndDestroy( scButton );
    return KErrNone;

    }


//  [End of File]
