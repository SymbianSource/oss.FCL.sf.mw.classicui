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
* Description:  test functions for testing aknnotifiercontroller.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknnotifiercontroller.h>

#include "testdomextnotifiers.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestANCtlHideAllNotifications
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestANCtlHideAllNotifications( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestANCtlHideAllNotifications, "TestANCtlHideAllNotifications" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestANCtlHideAllNotifications );
    // Print to log file
    iLog->Log( KTestANCtlHideAllNotifications );
    
    AknNotifierController::HideAllNotifications( EFalse );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestANCtlCancelAllNotifications
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestANCtlCancelAllNotifications( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestANCtlCancelAllNotifications, "TestANCtlCancelAllNotifications" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestANCtlCancelAllNotifications );
    // Print to log file
    iLog->Log( KTestANCtlCancelAllNotifications );
    
    AknNotifierController::CancelAllNotifications();
    
    return KErrNone;
    }


//  [End of File]
