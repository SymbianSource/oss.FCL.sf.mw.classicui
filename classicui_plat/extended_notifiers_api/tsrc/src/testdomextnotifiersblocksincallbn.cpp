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
* Description:  test functions for testing AknIncallBubbleNotify.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknincallbubblenotify.h>

#include "testdomextnotifiers.h"


// CONSTANTS
const TInt KIncallBubbleFlags = 0;


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCAIBNewL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCAIBNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCAIBNewL, "TestCAIBNewL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCAIBNewL );
    // Print to log file
    iLog->Log( KTestCAIBNewL );
    
    CAknIncallBubble* bubble = CAknIncallBubble::NewL();
    CleanupStack::PushL( bubble );
    
    STIF_ASSERT_NOT_NULL( bubble );
    
    CleanupStack::PopAndDestroy( bubble );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCAIBNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCAIBNewLCL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCAIBNewLCL, "TestCAIBNewLCL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCAIBNewLCL );
    // Print to log file
    iLog->Log( KTestCAIBNewLCL );
    
    CAknIncallBubble* bubble = CAknIncallBubble::NewLC();
    
    STIF_ASSERT_NOT_NULL( bubble );
    
    CleanupStack::PopAndDestroy( bubble );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCAIBSetIncallBubbleFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCAIBSetIncallBubbleFlagsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCAIBSetIncallBubbleFlagsL, "TestCAIBSetIncallBubbleFlagsL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCAIBSetIncallBubbleFlagsL );
    // Print to log file
    iLog->Log( KTestCAIBSetIncallBubbleFlagsL );
    
    CAknIncallBubble* bubble = CAknIncallBubble::NewL();
    CleanupStack::PushL( bubble );
    
    bubble->SetIncallBubbleFlagsL( KIncallBubbleFlags );
    
    CleanupStack::PopAndDestroy( bubble );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCAIBSetIncallBubbleAllowedInIdleL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCAIBSetIncallBubbleAllowedInIdleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCAIBSetIncallBubbleAllowedInIdleL, "TestCAIBSetIncallBubbleAllowedInIdleL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCAIBSetIncallBubbleAllowedInIdleL );
    // Print to log file
    iLog->Log( KTestCAIBSetIncallBubbleAllowedInIdleL );
    
    CAknIncallBubble* bubble = CAknIncallBubble::NewL();
    CleanupStack::PushL( bubble );
    
    bubble->SetIncallBubbleAllowedInIdleL( ETrue );
    
    CleanupStack::PopAndDestroy( bubble );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCAIBSetIncallBubbleAllowedInUsualL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCAIBSetIncallBubbleAllowedInUsualL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCAIBSetIncallBubbleAllowedInUsualL, "TestCAIBSetIncallBubbleAllowedInUsualL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCAIBSetIncallBubbleAllowedInUsualL );
    // Print to log file
    iLog->Log( KTestCAIBSetIncallBubbleAllowedInUsualL );
    
    CAknIncallBubble* bubble = CAknIncallBubble::NewL();
    CleanupStack::PushL( bubble );
    
    bubble->SetIncallBubbleAllowedInUsualL( ETrue );
    
    CleanupStack::PopAndDestroy( bubble );
    
    return KErrNone;
    }


//  [End of File]
