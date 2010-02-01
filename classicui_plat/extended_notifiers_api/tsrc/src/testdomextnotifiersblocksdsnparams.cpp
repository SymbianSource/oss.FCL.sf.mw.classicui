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
* Description:  test functions for testing AknDynamicSoftNotificationParams.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akndynamicsoftnotificationparams.h>

#include "testdomextnotifiers.h"


// CONSTANTS
const TInt KSoftNotificationPriority = 1001;

_LIT( KTestLeftSoftkeyTxt, "TestLeftSoftkey" );
_LIT( KTestSingularLabelTxt, "TestSingularLabelTxt" );
_LIT( KTestPluralLabelTxt, "TestPluralLabelTxt" );
_LIT8( KImageData, "TestImageDataTxt" );



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestTADSNPTAknDynamicSoftNotificationParamsL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestTADSNPTAknDynamicSoftNotificationParamsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestTADSNPTAknDynamicSoftNotificationParamsL, "TestTADSNPTAknDynamicSoftNotificationParamsL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestTADSNPTAknDynamicSoftNotificationParamsL );
    // Print to log file
    iLog->Log( KTestTADSNPTAknDynamicSoftNotificationParamsL );
    
    TAknDynamicSoftNotificationParams* softnparams =
                new ( ELeave ) TAknDynamicSoftNotificationParams( KSoftNotificationPriority );
    CleanupStack::PushL( softnparams );
    
    STIF_ASSERT_NOT_NULL( softnparams );
    
    CleanupStack::PopAndDestroy( softnparams );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestTADSNPSetViewActivationParams
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestTADSNPSetViewActivationParams( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestTADSNPSetViewActivationParams, "TestTADSNPSetViewActivationParams" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestTADSNPSetViewActivationParams );
    // Print to log file
    iLog->Log( KTestTADSNPSetViewActivationParams );
    
    TVwsViewId viewId;
    TAknDynamicSoftNotificationParams softnparams( KSoftNotificationPriority );
    softnparams.SetViewActivationParams( viewId );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestTADSNPSetSoftkeys
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestTADSNPSetSoftkeys( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestTADSNPSetSoftkeys, "TestTADSNPSetSoftkeys" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestTADSNPSetSoftkeys );
    // Print to log file
    iLog->Log( KTestTADSNPSetSoftkeys );
    
    TAknDynamicSoftNotificationParams softnparams( KSoftNotificationPriority );
    softnparams.SetSoftkeys( KTestLeftSoftkeyTxt, KTestLeftSoftkeyTxt );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestTADSNPSetNoteLabels
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestTADSNPSetNoteLabels( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestTADSNPSetNoteLabels, "TestTADSNPSetNoteLabels" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestTADSNPSetNoteLabels );
    // Print to log file
    iLog->Log( KTestTADSNPSetNoteLabels );
    
    TAknDynamicSoftNotificationParams softnparams( KSoftNotificationPriority );
    softnparams.SetNoteLabels( KTestSingularLabelTxt, KTestPluralLabelTxt );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestTADSNPSetGroupLabels
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestTADSNPSetGroupLabels( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestTADSNPSetGroupLabels, "TestTADSNPSetGroupLabels" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestTADSNPSetGroupLabels );
    // Print to log file
    iLog->Log( KTestTADSNPSetGroupLabels );
    
    TAknDynamicSoftNotificationParams softnparams( KSoftNotificationPriority );
    softnparams.SetGroupLabels( KTestSingularLabelTxt, KTestPluralLabelTxt );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestTADSNPSetImageData
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestTADSNPSetImageData( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestTADSNPSetImageData, "TestTADSNPSetImageData" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestTADSNPSetImageData );
    // Print to log file
    iLog->Log( KTestTADSNPSetImageData );
    
    TAknDynamicSoftNotificationParams softnparams( KSoftNotificationPriority );
    softnparams.SetImageData( KImageData );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestTADSNPEnableObserver
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestTADSNPEnableObserver( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestTADSNPEnableObserver, "TestTADSNPEnableObserver" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestTADSNPEnableObserver );
    // Print to log file
    iLog->Log( KTestTADSNPEnableObserver );
    
    TAknDynamicSoftNotificationParams softnparams( KSoftNotificationPriority );
    softnparams.EnableObserver();
    
    return KErrNone;
    }



//  [End of File]
