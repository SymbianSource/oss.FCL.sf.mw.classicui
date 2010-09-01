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
* Description:  test AknToolbarObserver.h
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akntoolbarobserver.h>

#include <testsdktoolbar.rsg>
#include "testsdktoolbar.h"
#include "testsdktoolbarcontrol.h"

// ======== MEMBER FUNCTIONS ========

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarObserverDynInitToolbarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarObserverDynInitToolbarL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarobserver" );
    _LIT( KTestToolbarExtSetShown, "DynInitToolbar" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarExtSetShown );
    // Print to log file
    iLog->Log( KTestToolbarExtSetShown );

    CTestToolbarControl* observer = CTestToolbarControl::NewL();
    CleanupStack::PushL( observer );
    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    observer->DoDynInitToolbarL( R_TOOLBAR, toolbar );

    CleanupStack::PopAndDestroy( toolbar );
    CleanupStack::PopAndDestroy( observer );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarObserverReservedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarObserverReservedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarobserver" );
    _LIT( KTestToolbarObserverReserved_1L, "Reserved_1" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarObserverReserved_1L );
    // Print to log file
    iLog->Log( KTestToolbarObserverReserved_1L );

    CTestToolbarControl* observer = CTestToolbarControl::NewL();
    CleanupStack::PushL( observer );

    TInt reserved = observer->DoMAknToolbarObserver_Reserved_1();
    STIF_ASSERT_EQUALS( 1, reserved );

    CleanupStack::PopAndDestroy( observer );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarObserverReservedTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarObserverReservedTwoL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarobserver" );
    _LIT( KTestToolbarObserverReserved_2L, "Reserved_2" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarObserverReserved_2L );
    // Print to log file
    iLog->Log( KTestToolbarObserverReserved_2L );

    CTestToolbarControl* observer = CTestToolbarControl::NewL();
    CleanupStack::PushL( observer );
    
    TInt reserved = observer->DoMAknToolbarObserver_Reserved_2();
    STIF_ASSERT_EQUALS( 1, reserved );

    CleanupStack::PopAndDestroy( observer );
    return KErrNone;

    }

