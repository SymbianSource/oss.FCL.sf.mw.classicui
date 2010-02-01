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
* Description:  Test eikspace.h
 *
*/


#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eikspace.h>
#include <w32std.h>

#include "testsdkscreenclearer.h"

const TInt KWidth = 10;
const TInt KHeight = 10;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSpacerConstructor
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSpacerConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSpacerTestModule, "SpacerTestModule" );
    _LIT( KSpacerConstructor, "In SpacerConstructor" );
    TestModuleIf().Printf( 0, KSpacerTestModule, KSpacerConstructor );
    // Print to log file
    iLog->Log( KSpacerConstructor );
    
    //constructor
    iSpacer = new( ELeave ) CEikSpacer();
    STIF_ASSERT_NOT_NULL( iSpacer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSpacerSConstructor
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSpacerSConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSpacerTestModule, "SpacerTestModule" );
    _LIT( KSpacerSConstructor, "In SpacerConstructor#2" );
    TestModuleIf().Printf( 0, KSpacerTestModule, KSpacerSConstructor );
    // Print to log file
    iLog->Log( KSpacerSConstructor );
    
    TInt height(1);
    TInt width(1);
    TRgb iColor = TRgb( 0xffffff );
    //constructor
    iSpacer = new( ELeave ) CEikSpacer( height, width, iColor);
    STIF_ASSERT_NOT_NULL( iSpacer );
    
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSpacerDestructor
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSpacerDestructor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSpacerTestModule, "SpacerTestModule" );
    _LIT( KSpacerDestructor, "In SpacerDestructor" );
    TestModuleIf().Printf( 0, KSpacerTestModule, KSpacerDestructor );
    // Print to log file
    iLog->Log( KSpacerDestructor );
    
    //destructor
    delete iSpacer;
    iSpacer = NULL;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSpacerSetWidth
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSpacerSetWidth( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSpacerTestModule, "SpacerTestModule" );
    _LIT( KSpacerSetWidth, "In SpacerSetWidth" );
    TestModuleIf().Printf( 0, KSpacerTestModule, KSpacerSetWidth );
    // Print to log file
    iLog->Log( KSpacerSetWidth );
    
    iSpacer->SetWidth( KWidth );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSpacerSetHeight
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSpacerSetHeight( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSpacerTestModule, "SpacerTestModule" );
    _LIT( KSpacerSetHeight, "In SpacerSetHeight" );
    TestModuleIf().Printf( 0, KSpacerTestModule, KSpacerSetHeight );
    // Print to log file
    iLog->Log( KSpacerSetHeight );
    
    iSpacer->SetHeight( KHeight );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSpacerSetColor
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSpacerSetColor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSpacerTestModule, "SpacerTestModule" );
    _LIT( KSpacerSetColor, "In SpacerSetColor" );
    TestModuleIf().Printf( 0, KSpacerTestModule, KSpacerSetColor );
    // Print to log file
    iLog->Log( KSpacerSetColor );
    
    iSpacer->SetColor( KRgbBlack );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSpacerSetClear
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSpacerSetClear( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSpacerTestModule, "SpacerTestModule" );
    _LIT( KSpacerSetClear, "In SpacerSetClear" );
    TestModuleIf().Printf( 0, KSpacerTestModule, KSpacerSetClear );
    // Print to log file
    iLog->Log( KSpacerSetClear );

    iSpacer->SetClear( ETrue );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSpacerSetClear
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSpacerHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSpacerTestModule, "SpacerTestModule" );
    _LIT( KSpacerHandlePointerEventL, "In SpacerHandlePointerEventL" );
    TestModuleIf().Printf( 0, KSpacerTestModule, KSpacerHandlePointerEventL );
    // Print to log file
    iLog->Log( KSpacerHandlePointerEventL );
    
    //define TPointerEvent
    TInt err;
    TPointerEvent pointerEvent;
    TRAP( err, iSpacer->HandlePointerEventL( pointerEvent ) );
    return err;
    
    }
