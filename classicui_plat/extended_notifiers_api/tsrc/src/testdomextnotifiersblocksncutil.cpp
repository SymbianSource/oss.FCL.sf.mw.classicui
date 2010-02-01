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
* Description:  test functions for testing AknNotifierControllerUtilities.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknnotifiercontrollerutilities.h>

#include "testdomextnotifiers.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANCUDoAllowNotificationsL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANCUDoAllowNotificationsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANCUDoAllowNotificationsL, "TestCANCUDoAllowNotificationsL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANCUDoAllowNotificationsL );
    // Print to log file
    iLog->Log( KTestCANCUDoAllowNotificationsL );
    
    CAknNotifierControllerUtility* ctlUtil =
                new ( ELeave ) CAknNotifierControllerUtility( 0 );
    CleanupStack::PushL( ctlUtil );
    
    ctlUtil->DoAllowNotifications();
    
    CleanupStack::PopAndDestroy( ctlUtil );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANCUDoStopNotificationsL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANCUDoStopNotificationsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANCUDoStopNotificationsL, "TestCANCUDoStopNotificationsL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANCUDoStopNotificationsL );
    // Print to log file
    iLog->Log( KTestCANCUDoStopNotificationsL );
    
    CAknNotifierControllerUtility* ctlUtil =
                new ( ELeave ) CAknNotifierControllerUtility( 0 );
    CleanupStack::PushL( ctlUtil );
    
    ctlUtil->DoStopNotifications();
    
    CleanupStack::PopAndDestroy( ctlUtil );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANCUDoCancelAllNotificatonsL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANCUDoCancelAllNotificatonsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANCUDoCancelAllNotificatonsL, "TestCANCUDoCancelAllNotificatonsLL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANCUDoCancelAllNotificatonsL );
    // Print to log file
    iLog->Log( KTestCANCUDoCancelAllNotificatonsL );
    
    CAknNotifierControllerUtility* ctlUtil =
                new ( ELeave ) CAknNotifierControllerUtility( 0 );
    CleanupStack::PushL( ctlUtil );
    
    ctlUtil->DoCancelAllNotificatonsL();
    
    CleanupStack::PopAndDestroy( ctlUtil );
    
    return KErrNone;
    }


//  [End of File]
