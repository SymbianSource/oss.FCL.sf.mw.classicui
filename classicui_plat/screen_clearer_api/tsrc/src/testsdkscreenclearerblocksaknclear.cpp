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
* Description:  Test AknClearer.h
*
*/

#include <coecntrl.h>
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknclearer.h>
#include <w32std.h>
#include <akndef.h>

#include "testsdkscreenclearer.h"
#include "testsdkscscreenclearerbase.h"
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestLSCNewL
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestLSCNewL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KLSCTestModule, "LSCTestModule" );
    _LIT( KLSCNewL, "In LSCNewL" );
    TestModuleIf().Printf( 0, KLSCTestModule, KLSCNewL );
    // Print to log file
    iLog->Log( KLSCNewL );
    
    CAknLocalScreenClearer* localSClearer = CAknLocalScreenClearer::NewL( ETrue );
    STIF_ASSERT_NOT_NULL( localSClearer );
    
    delete localSClearer;
    localSClearer = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestLSCNewLC
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestLSCNewLC( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KLSCTestModule, "LSCTestModule" );
    _LIT( KLSCNewLC, "In LSCNewLC" );
    TestModuleIf().Printf( 0, KLSCTestModule, KLSCNewLC );
    // Print to log file
    iLog->Log( KLSCNewLC );
    
    CAknLocalScreenClearer* localSClearer = CAknLocalScreenClearer::NewLC();
    CleanupStack::Pop();
    STIF_ASSERT_NOT_NULL( localSClearer );
    
    delete localSClearer;
    localSClearer = NULL;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestLSCNewLC(TBool aBlankAppStatusPane)
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestLSCSNewLC( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KLSCTestModule, "LSCTestModule" );
    _LIT( KLSCNewLC, "In LSCNewLC#2" );
    TestModuleIf().Printf( 0, KLSCTestModule, KLSCNewLC );
    // Print to log file
    iLog->Log( KLSCNewLC );
    
    CAknLocalScreenClearer* localSClearer = CAknLocalScreenClearer::NewLC( ETrue );
    CleanupStack::Pop();
    STIF_ASSERT_NOT_NULL( localSClearer );
    
    delete localSClearer;
    localSClearer = NULL;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSCBHandleStatusPaneSizeChangeL
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSCBHandleStatusPaneSizeChangeL(CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KSCBTestModule, "SCBTestModule" );
    _LIT( KSCBHandleStatusPaneSizeChangeL, "In SCBHandleStatusPaneSizeChangeL" );
    TestModuleIf().Printf( 0, KSCBTestModule, KSCBHandleStatusPaneSizeChangeL );
    // Print to log file
    iLog->Log( KSCBHandleStatusPaneSizeChangeL );
    
    //call method HandleStatusPaneSizeChangeL()
    CAknLocalScreenClearer* localSClearer = CAknLocalScreenClearer::NewL( ETrue );
    TInt err;
    TRAP( err, localSClearer->HandleStatusPaneSizeChangeL() );
    
    delete localSClearer;
    localSClearer =NULL;
    
    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSCBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSCBHandlePointerEventL(CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KSCBTestModule, "SCBTestModule" );
    _LIT( KSCBHandlePointerEventL, "In SCBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KSCBTestModule, KSCBHandlePointerEventL );
    // Print to log file
    iLog->Log( KSCBHandlePointerEventL );
    
    //call method HandlePointerEventL
    CAknLocalScreenClearer* localSClearer = CAknLocalScreenClearer::NewL( ETrue );
    TInt err;
    TPointerEvent pointerEvent( TPointerEvent::EButton1Up,
            EModifierAutorepeatable, TPoint( 20, 20 ), TPoint( 0, 0 ) );
    TRAP( err, localSClearer->HandlePointerEventL(pointerEvent) );
    
    delete localSClearer;
    localSClearer =NULL;
    
    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSCBHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSCBHandleResourceChangeL(CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KSCBTestModule, "SCBTestModule" );
    _LIT( KSCBHandlePointerEventL, "In SCBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KSCBTestModule, KSCBHandlePointerEventL );
    // Print to log file
    iLog->Log( KSCBHandlePointerEventL );
    
    //call method HandlePointerEventL
    CAknLocalScreenClearer* localSClearer = CAknLocalScreenClearer::NewL( ETrue );
    
    localSClearer->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    delete localSClearer;
    localSClearer =NULL;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSCBDeleteL
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSCBDeleteL(CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KSCBTestModule, "SCBTestModule" );
    _LIT( KSCBHandlePointerEventL, "In SCBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KSCBTestModule, KSCBHandlePointerEventL );
    // Print to log file
    iLog->Log( KSCBHandlePointerEventL );

    CTestSDKSCScreenClearerBase* localSClearer = new( ELeave ) CTestSDKSCScreenClearerBase();
    CleanupStack::PushL( localSClearer );
    STIF_ASSERT_NOT_NULL( localSClearer );
    CleanupStack::PopAndDestroy( localSClearer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenclearer::TestSCBConstructL
// -----------------------------------------------------------------------------
//
TInt CTestsSDKScreenClearer::TestSCBConstructL(CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KSCBTestModule, "SCBTestModule" );
    _LIT( KSCBHandlePointerEventL, "In SCBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KSCBTestModule, KSCBHandlePointerEventL );
    // Print to log file
    iLog->Log( KSCBHandlePointerEventL );

    CTestSDKSCScreenClearerBase* localSClearer = new( ELeave ) CTestSDKSCScreenClearerBase();
    CleanupStack::PushL( localSClearer );
    RWindowGroup& parent = CCoeEnv::Static()->RootWin();
    localSClearer->ConstructL( parent, 0 , EFalse );
    CleanupStack::PopAndDestroy( localSClearer );

    return KErrNone;
    }
