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
* Description:  test functions for testing AknSoftNotifier.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <vwsdefpartner.h>
#include <aknsoftnotifier.h>
#include <aknsoftnotificationparameters.h>

#include "testdomextnotifiers.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNNewL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNNewL, "TestCASNNewL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNNewL );
    // Print to log file
    iLog->Log( KTestCASNNewL );
    
    CAknSoftNotifier* softNotifier = CAknSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    STIF_ASSERT_NOT_NULL( softNotifier );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNNewLCL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNNewLCL, "TestCASNNewLCL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNNewLCL );
    // Print to log file
    iLog->Log( KTestCASNNewLCL );
    
    CAknSoftNotifier* softNotifier = CAknSoftNotifier::NewLC();
    
    STIF_ASSERT_NOT_NULL( softNotifier );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNAddNotificationL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNAddNotificationL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNAddNotificationL, "TestCASNAddNotificationL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNAddNotificationL );
    // Print to log file
    iLog->Log( KTestCASNAddNotificationL );
    
    CAknSoftNotifier* softNotifier = CAknSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    softNotifier->AddNotificationL( ENetworkInformationNotification );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNAddNotificationWithCountL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNAddNotificationWithCountL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNAddNotificationWithCountL, "TestCASNAddNotificationWithCountL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNAddNotificationWithCountL );
    // Print to log file
    iLog->Log( KTestCASNAddNotificationWithCountL );
    
    CAknSoftNotifier* softNotifier = CAknSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    softNotifier->AddNotificationL( ENetworkInformationNotification, 1 );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNSetNotificationCountL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNSetNotificationCountL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNSetNotificationCountL, "TestCASNSetNotificationCountL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNSetNotificationCountL );
    // Print to log file
    iLog->Log( KTestCASNSetNotificationCountL );
    
    CAknSoftNotifier* softNotifier = CAknSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    softNotifier->SetNotificationCountL( ENetworkInformationNotification, 1 );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNCancelSoftNotificationL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNCancelSoftNotificationL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNCancelSoftNotificationL, "TestCASNCancelSoftNotificationL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNCancelSoftNotificationL );
    // Print to log file
    iLog->Log( KTestCASNCancelSoftNotificationL );
    
    CAknSoftNotifier* softNotifier = CAknSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    softNotifier->SetNotificationCountL( ENetworkInformationNotification, 1 );
    softNotifier->CancelSoftNotificationL( ENetworkInformationNotification );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNAddCustomNotificationL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNAddCustomNotificationL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNAddCustomNotificationL, "TestCASNAddCustomNotificationL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNAddCustomNotificationL );
    // Print to log file
    iLog->Log( KTestCASNAddCustomNotificationL );
    
    CAknSoftNotifier* softNotifier = CAknSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    _LIT( KFilePath, "C:" );
    _LIT8( KMessage, "Message Descriptor" );
    
    CAknSoftNotificationParameters* softParam = 
            CAknSoftNotificationParameters::NewL( KFilePath, 0, 0, 0,
                    CAknNoteDialog::ENoTone,
                    KNullViewId, KNullUid,
                    0, KMessage );
    CleanupStack::PushL( softParam );
    
    softNotifier->AddCustomNotificationL( *softParam );
    
    CleanupStack::PopAndDestroy( softParam );
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNSetCustomNotificationCountL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNSetCustomNotificationCountL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNSetCustomNotificationCountL, "TestCASNSetCustomNotificationCountL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNSetCustomNotificationCountL );
    // Print to log file
    iLog->Log( KTestCASNSetCustomNotificationCountL );
    
    CAknSoftNotifier* softNotifier = CAknSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    _LIT( KFilePath, "C:" );
    _LIT8( KMessage, "Message Descriptor" );
    
    CAknSoftNotificationParameters* softParam = 
            CAknSoftNotificationParameters::NewL( KFilePath, 0, 0, 0,
                    CAknNoteDialog::ENoTone,
                    KNullViewId, KNullUid,
                    0, KMessage );
    CleanupStack::PushL( softParam );
    
    softNotifier->SetCustomNotificationCountL( *softParam, 1 );
    
    CleanupStack::PopAndDestroy( softParam );
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCASNCancelCustomSoftNotificationL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCASNCancelCustomSoftNotificationL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCASNCancelCustomSoftNotificationL, "TestCASNCancelCustomSoftNotificationL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCASNCancelCustomSoftNotificationL );
    // Print to log file
    iLog->Log( KTestCASNCancelCustomSoftNotificationL );
    
    CAknSoftNotifier* softNotifier = CAknSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    _LIT( KFilePath, "C:" );
    _LIT8( KMessage, "Message Descriptor" );
    
    CAknSoftNotificationParameters* softParam = 
            CAknSoftNotificationParameters::NewL( KFilePath, 0, 0, 0,
                    CAknNoteDialog::ENoTone,
                    KNullViewId, KNullUid,
                    0, KMessage );
    CleanupStack::PushL( softParam );
    
    softNotifier->SetCustomNotificationCountL( *softParam, 1 );
    softNotifier->CancelCustomSoftNotificationL( *softParam );
    
    CleanupStack::PopAndDestroy( softParam );
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }


//  [End of File]
