/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknclearer.h>
#include <eikspace.h>
#include <w32std.h>
#include <bctestscreenclearer.rsg>

#include "bctestscreenclearercase.h"
#include "bctestscreenclearercontainer.h"
#include "bctestscreenclearer.hrh"

const TInt KLength = 200;
const TInt KNum = 500;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestScreenClearerCase* CBCTestScreenClearerCase::NewL(
    CBCTestScreenClearerContainer* aContainer )
    {
    CBCTestScreenClearerCase* self = new( ELeave ) CBCTestScreenClearerCase(
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestScreenClearerCase::CBCTestScreenClearerCase(
    CBCTestScreenClearerContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestScreenClearerCase::~CBCTestScreenClearerCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestScreenClearerCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestScreenClearerCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestScreenClearerCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( LeftCBA, KeyOK, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestScreenClearerCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestScreenClearerCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdTestL || aCmd > EBCTestCmdTestL )
        {
        return;
        }
   
    switch ( aCmd )
        {
        case EBCTestCmdTestL:
            TestL();
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// test ScreenClearer API
// ----------------------------------------------------------------------------
//
void CBCTestScreenClearerCase::TestL()
    {
    TBool blankAppStatusPane = ETrue;
    TPointerEvent pointerEvent;

    CAknLocalScreenClearer* screenclearernew1 = 
        CAknLocalScreenClearer::NewLC();
    _LIT( KScreenClearerNew11, "~CAknScreenClearerBase() test" );
    AssertNotNullL( screenclearernew1, KScreenClearerNew11 );
    _LIT( KScreenClearerNew12, "NewLC test" );
    AssertNotNullL( screenclearernew1, KScreenClearerNew12 );
    _LIT( KScreenClearerNew13, "ConstructL( 3 ) test for screenclearer:" );
    AssertNotNullL( screenclearernew1, KScreenClearerNew13 );
    screenclearernew1->HandleStatusPaneSizeChangeL();
    _LIT( KScreenClearerNew14, "HandleStatusPaneSizeChangeL test" );
    AssertNotNullL( screenclearernew1, KScreenClearerNew14 );
    screenclearernew1->HandlePointerEventL( pointerEvent );
    _LIT( KScreenClearerNew15, "HandlePointerEventL test" );
    AssertNotNullL( screenclearernew1, KScreenClearerNew15 );
    CleanupStack::PopAndDestroy( screenclearernew1 );

    CAknLocalScreenClearer* screenclearernew2; 
    screenclearernew2 = CAknLocalScreenClearer::NewLC( blankAppStatusPane );
    _LIT( KScreenClearerNew21, "NewLC( TBool aBlankAppStatusPane) test" );
    AssertNotNullL( screenclearernew2, KScreenClearerNew21 );
    CleanupStack::PopAndDestroy( screenclearernew2 );

    CAknLocalScreenClearer* screenclearernew3; 
    screenclearernew3 = CAknLocalScreenClearer::NewL( blankAppStatusPane );
    CleanupStack::PushL( screenclearernew3 );
    _LIT( KScreenClearerNew22, "NewL( TBool aBlankAppStatusPane ) test" );
    AssertNotNullL( screenclearernew3, KScreenClearerNew22 );
    CleanupStack::PopAndDestroy( screenclearernew3 );

    CEikSpacer* eikspacer1 = new( ELeave ) CEikSpacer;
    CleanupStack::PushL( eikspacer1 );
    _LIT( KEikSpacer11, "CEikSpacer test for screenclearer:" );
    AssertNotNullL( eikspacer1, KEikSpacer11 );
    eikspacer1->SetWidth( KLength );
    _LIT( KEikSpacer12, "SetWidth( TInt aWidth ) test" );
    AssertNotNullL( eikspacer1, KEikSpacer12 );
    eikspacer1->SetHeight( KLength );
    _LIT( KEikSpacer13, "SetHeight( TInt aHeight ) test" );
    AssertNotNullL( eikspacer1, KEikSpacer13 );

    eikspacer1->SetColor( KRgbBlack );
    _LIT( KEikSpacer14, "SetColor( TRgb aColor ) test" );
    AssertNotNullL( eikspacer1, KEikSpacer14 );

    eikspacer1->SetClear( ETrue );
    _LIT( KEikSpacer15, "SetClear( TBool aClear ) test" );
    AssertNotNullL( eikspacer1, KEikSpacer15 );

    TPointerEvent pointerEvent2 = { TPointerEvent::EButton1Up,
         EModifierAutorepeatable, TPoint( 20, 20 ), TPoint( 0, 0 ) };
    eikspacer1->HandlePointerEventL( pointerEvent2 );
    _LIT( KHandlePointerEventL2, "HandlePointerEventL test" );
    AssertNotNullL( eikspacer1, KHandlePointerEventL2 );
    
    CleanupStack::PopAndDestroy( eikspacer1 );

    CEikSpacer* eikspacer2; 
    eikspacer2 = new( ELeave )CEikSpacer( KNum, KNum, KRgbBlack );
    CleanupStack::PushL( eikspacer2 );
    _LIT( KEikSpacer21, "CEikSpacer( 3 ) test" );
    AssertNotNullL( eikspacer2, KEikSpacer21 );
    _LIT( KEikSpacer22, "~CEikSpacer() test" );
    AssertNotNullL( eikspacer2, KEikSpacer22 );
    CleanupStack::PopAndDestroy( eikspacer2 );
    }
