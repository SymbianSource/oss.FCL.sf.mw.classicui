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
* Description:  test functions for testing aknSoftNotificationParameters.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <vwsdefpartner.h>
#include <aknsoftnotificationparameters.h>

#include "testdomextnotifiers.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNPNewL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNPNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNPNewL, "TestCASNPNewL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNPNewL );
    // Print to log file
    iLog->Log( KTestCASNPNewL );
    
    CAknSoftNotificationParameters* softParam = CAknSoftNotificationParameters::NewL();
    CleanupStack::PushL( softParam );
    
    STIF_ASSERT_NOT_NULL( softParam );
    
    CleanupStack::PopAndDestroy( softParam );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNPNewWith5ParamL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNPNewWith5ParamL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNPNewWith5ParamL, "TestCASNPNewWith5ParamL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNPNewWith5ParamL );
    // Print to log file
    iLog->Log( KTestCASNPNewWith5ParamL );
    
    _LIT( KFilePath, "C:\\stiftest\\rest.txt" );
    
    CAknSoftNotificationParameters* softParam =
            CAknSoftNotificationParameters::NewL( KFilePath, 0, 0, 0, CAknNoteDialog::ENoTone );
    CleanupStack::PushL( softParam );
    
    STIF_ASSERT_NOT_NULL( softParam );
    
    CleanupStack::PopAndDestroy( softParam );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNPNewWith9ParamL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNPNewWith9ParamL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNPNewWith9ParamL, "TestCASNPNewWith9ParamL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNPNewWith9ParamL );
    // Print to log file
    iLog->Log( KTestCASNPNewWith9ParamL );
    
    _LIT( KFilePath, "C:\\stiftest\\rest.txt" );
    _LIT8( KMessage, "Message Descriptor" );
    
    CAknSoftNotificationParameters* softParam =
            CAknSoftNotificationParameters::NewL( KFilePath, 0, 0, 0,
                    CAknNoteDialog::ENoTone,
                    KNullViewId, KNullUid,
                    0, KMessage );
    CleanupStack::PushL( softParam );
    
    STIF_ASSERT_NOT_NULL( softParam );
    
    CleanupStack::PopAndDestroy( softParam );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNPSetGroupedTextsL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNPSetGroupedTextsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNPSetGroupedTextsL, "TestCASNPSetGroupedTextsL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNPSetGroupedTextsL );
    // Print to log file
    iLog->Log( KTestCASNPSetGroupedTextsL );
    
    CAknSoftNotificationParameters* softParam = CAknSoftNotificationParameters::NewL();
    CleanupStack::PushL( softParam );
    
    softParam->SetGroupedTexts( 0 );
    
    CleanupStack::PopAndDestroy( softParam );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNPSetPluralViewIdL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNPSetPluralViewIdL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNPSetPluralViewIdL, "TestCASNPSetPluralViewIdL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNPSetPluralViewIdL );
    // Print to log file
    iLog->Log( KTestCASNPSetPluralViewIdL );
    
    CAknSoftNotificationParameters* softParam = CAknSoftNotificationParameters::NewL();
    CleanupStack::PushL( softParam );
    
    softParam->SetPluralViewId( KNullViewId );
    
    CleanupStack::PopAndDestroy( softParam );
    
    return KErrNone;
    }


//  [End of File]
