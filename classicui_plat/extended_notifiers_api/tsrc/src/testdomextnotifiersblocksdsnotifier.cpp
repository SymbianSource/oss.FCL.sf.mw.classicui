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
* Description:  test functions for testing AknDynamicSoftNotifier.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akndynamicsoftnotifier.h>
#include <akndynamicsoftnotificationparams.h>
#include <aknsddata.h>

#include "testdomextnotifiers.h"


// CONSTANTS
const TInt KSoftNotificationPriority = 1001;
const TInt KDialogIndex = 0;

_LIT8( KAdditionalData, "TestAdditionalData" );


// FORWARD DECLARATION
// CTestDynamicSoftNoteObserver for testing CAknDynamicSoftNotifier
class CTestDynamicSoftNoteObserver: public CBase, public MAknDynamicSoftNoteObserver
    {
public:
    // Constructor
    CTestDynamicSoftNoteObserver(): CBase() {}
    
    // from MAknDynamicSoftNoteObserver
    void NotificationAccepted( TInt /*aNoteId*/ ) {}
    
    // from MAknDynamicSoftNoteObserver
    void NotificationCanceled( TInt /*aNoteId*/ ) {}
    };


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCADSNNewL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCADSNNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCADSNNewL, "TestCADSNNewL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCADSNNewL );
    // Print to log file
    iLog->Log( KTestCADSNNewL );
    
    CAknDynamicSoftNotifier* softNotifier = CAknDynamicSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    STIF_ASSERT_NOT_NULL( softNotifier );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCADSNNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCADSNNewLCL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCADSNNewLCL, "TestCADSNNewLCL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCADSNNewLCL );
    // Print to log file
    iLog->Log( KTestCADSNNewLCL );
    
    CAknDynamicSoftNotifier* softNotifier = CAknDynamicSoftNotifier::NewLC();
    
    STIF_ASSERT_NOT_NULL( softNotifier );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCADSNAddDynamicNotificationL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCADSNAddDynamicNotificationL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCADSNAddDynamicNotificationL, "TestCADSNAddDynamicNotificationL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCADSNAddDynamicNotificationL );
    // Print to log file
    iLog->Log( KTestCADSNAddDynamicNotificationL );
    
    TAknDynamicSoftNotificationParams softnparams( KSoftNotificationPriority );
    CAknDynamicSoftNotifier* softNotifier = CAknDynamicSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    softNotifier->AddDynamicNotificationL( softnparams );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCADSNSetDynamicNotificationCountL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCADSNSetDynamicNotificationCountL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCADSNSetDynamicNotificationCountL, "TestCADSNSetDynamicNotificationCountL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCADSNSetDynamicNotificationCountL );
    // Print to log file
    iLog->Log( KTestCADSNSetDynamicNotificationCountL );
    
    TAknDynamicSoftNotificationParams softnparams( KSoftNotificationPriority );
    CAknDynamicSoftNotifier* softNotifier = CAknDynamicSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    softNotifier->SetDynamicNotificationCountL( softnparams, KErrUnknown, 1 );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCADSNCancelDynamicNotificationL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCADSNCancelDynamicNotificationL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCADSNCancelDynamicNotificationL, "TestCADSNCancelDynamicNotificationL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCADSNCancelDynamicNotificationL );
    // Print to log file
    iLog->Log( KTestCADSNCancelDynamicNotificationL );
    
    CAknDynamicSoftNotifier* softNotifier = CAknDynamicSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    softNotifier->CancelDynamicNotificationL( KErrUnknown );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCADSNStartObservingL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCADSNStartObservingL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCADSNStartObservingL, "TestCADSNStartObservingL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCADSNStartObservingL );
    // Print to log file
    iLog->Log( KTestCADSNStartObservingL );
    
    CAknDynamicSoftNotifier* softNotifier = CAknDynamicSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    CTestDynamicSoftNoteObserver* noteobserver =
                new ( ELeave ) CTestDynamicSoftNoteObserver();
    CleanupStack::PushL( noteobserver );
    
    softNotifier->StartObservingL( KErrUnknown, noteobserver );
    
    CleanupStack::PopAndDestroy( noteobserver );
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCADSNStopObservingL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCADSNStopObservingL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCADSNStopObservingL, "TestCADSNStopObservingL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCADSNStopObservingL );
    // Print to log file
    iLog->Log( KTestCADSNStopObservingL );
    
    CAknDynamicSoftNotifier* softNotifier = CAknDynamicSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    softNotifier->StopObserving( KErrUnknown );
    
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCADSNSetSecondaryDisplayDataL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCADSNSetSecondaryDisplayDataL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCADSNSetSecondaryDisplayDataL, "TestCADSNSetSecondaryDisplayDataL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCADSNSetSecondaryDisplayDataL );
    // Print to log file
    iLog->Log( KTestCADSNSetSecondaryDisplayDataL );
    
    CAknDynamicSoftNotifier* softNotifier = CAknDynamicSoftNotifier::NewL();
    CleanupStack::PushL( softNotifier );
    
    CAknSDData* data = CAknSDData::NewL( TUid::Null(), KDialogIndex, KAdditionalData );
    CleanupStack::PushL( data );
    
    softNotifier->SetSecondaryDisplayData( data );
    
    CleanupStack::PopAndDestroy( data );
    CleanupStack::PopAndDestroy( softNotifier );
    
    return KErrNone;
    }


//  [End of File]
