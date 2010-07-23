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
* Description:  test eikscbut.h
*
*/


// [INCLUDE FILES]
#include <eikscbut.h>

#include "testsdkscroller.h"
#include "testsdkscrollercontrol.h"

// CONSTANTS
const TInt KPointX = 5;
const TInt KPointY = 5;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikScbDefConsWithPaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikScbDefConsWithPaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikScbDefConsWithPa, "in EikScbDefConsWithPa" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikScbDefConsWithPa );
    // Print to log file
    iLog->Log( KTestSDKEikScbDefConsWithPa );

    CEikScrollButton::TType type = CEikScrollButton::ENudgeLeft;
    CEikScrollButton* scButton = new ( ELeave ) CEikScrollButton( type );
    CleanupStack::PushL( scButton );
    STIF_ASSERT_NOT_NULL( scButton );
    
    CleanupStack::PopAndDestroy( scButton );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikScbTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikScbTypeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikScbType, "in EikScbType" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikScbType );
    // Print to log file
    iLog->Log( KTestSDKEikScbType );

    CEikScrollButton::TType type = CEikScrollButton::ENudgeUp;
    CEikScrollButton* scButton = new ( ELeave ) CEikScrollButton( type );
    CleanupStack::PushL( scButton );
    
    CEikScrollButton::TType sbType = scButton->Type();
    STIF_ASSERT_EQUALS( type, sbType );
    
    CleanupStack::PopAndDestroy( scButton );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikScbHanPoiEveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikScbHanPoiEveL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikScbHanPoiEveL, "in EikScbHanPoiEveL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikScbHanPoiEveL );
    // Print to log file
    iLog->Log( KTestSDKEikScbHanPoiEveL );

    CEikScrollButton::TType type = CEikScrollButton::ENudgeUp;
    CEikScrollButton* scButton = new ( ELeave ) CEikScrollButton( type );
    CleanupStack::PushL( scButton );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPointX, KPointY );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    scButton->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( scButton );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikAhSbNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikAhSbNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikAhSbNewL, "in EikAhSbNewL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikAhSbNewL );
    // Print to log file
    iLog->Log( KTestSDKEikAhSbNewL );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollButton::TType type = CEikScrollButton::ENudgeUp;

    CEikArrowHeadScrollButton* ahScBut = CEikArrowHeadScrollButton::NewL( control, type );
    CleanupStack::PushL( ahScBut );
    STIF_ASSERT_NULL( ahScBut );

    CleanupStack::PopAndDestroy( ahScBut );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

