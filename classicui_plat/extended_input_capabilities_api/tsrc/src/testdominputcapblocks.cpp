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
* Description:  test aknextendedinputcapabilities.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknextendedinputcapabilities.h>

#include "testdominputcap.h"
#include "testdominputcapext.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMInputCap::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestProviderDefCon", CTestDOMInputCap::TestProviderDefConL ),
        ENTRY( "TestProviderSetCap", CTestDOMInputCap::TestProviderSetCapL ),
        ENTRY( "TestProviderInputCap", CTestDOMInputCap::TestProviderInputCapL ),
        ENTRY( "TestProviderSetMopParent",
                CTestDOMInputCap::TestProviderSetMopParentL ),

        ENTRY( "TestInputCapNewL", CTestDOMInputCap::TestInputCapNewL ),
        ENTRY( "TestInputCapNewLC", CTestDOMInputCap::TestInputCapNewLCL ),
        ENTRY( "TestInputCapSetCapabilities",
                CTestDOMInputCap::TestInputCapSetCapabilitiesL ),
        ENTRY( "TestInputCapCapabilities",
                CTestDOMInputCap::TestInputCapCapabilitiesL ),
        ENTRY( "TestInputCapSupportsCapabilities",
                CTestDOMInputCap::TestInputCapSupportsCapabilitiesL ),
        ENTRY( "TestInputCapSetMIDPConstraints",
                CTestDOMInputCap::TestInputCapSetMIDPConstraintsL ),
        ENTRY( "TestInputCapMIDPConstrainst",
                CTestDOMInputCap::TestInputCapMIDPConstrainstL ),
        ENTRY( "TestInputCapSetEditorType",
                CTestDOMInputCap::TestInputCapSetEditorTypeL ),
        ENTRY( "TestInputCapEditorType",
                CTestDOMInputCap::TestInputCapEditorTypeL ),
        ENTRY( "TestInputCapRegisterObserver",
                CTestDOMInputCap::TestInputCapRegisterObserverL ),
        ENTRY( "TestInputCapUnregisterObserver",
                CTestDOMInputCap::TestInputCapUnregisterObserverL ),
        ENTRY( "TestInputCapReportEventL",
                CTestDOMInputCap::TestInputCapReportEventL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestProviderDefConL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestProviderDefConL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestProviderDefCon, "In ProviderDefCon" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestProviderDefCon );
    // Print to log file
    iLog->Log( KTestProviderDefCon );

    CAknExtendedInputCapabilities::
    CAknExtendedInputCapabilitiesProvider* provider = 
            new ( ELeave ) CAknExtendedInputCapabilities::
            CAknExtendedInputCapabilitiesProvider;
    CleanupStack::PushL( provider );
    STIF_ASSERT_NOT_NULL( provider );

    CleanupStack::PopAndDestroy( provider );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestProviderSetCapL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestProviderSetCapL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestProviderSetCap, "In ProviderSetCap" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestProviderSetCap );
    // Print to log file
    iLog->Log( KTestProviderSetCap );

    CAknExtendedInputCapabilities::
    CAknExtendedInputCapabilitiesProvider* provider = 
            new ( ELeave ) CAknExtendedInputCapabilities::
            CAknExtendedInputCapabilitiesProvider;
    CleanupStack::PushL( provider );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewL();
    CleanupStack::PushL( inputCap );
    provider->SetExtendedInputCapabilities( inputCap );

    CleanupStack::PopAndDestroy( inputCap );
    CleanupStack::PopAndDestroy( provider );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestProviderInputCapL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestProviderInputCapL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestProviderInputCap, "In ProviderInputCap" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestProviderInputCap );
    // Print to log file
    iLog->Log( KTestProviderInputCap );

    CAknExtendedInputCapabilities::
    CAknExtendedInputCapabilitiesProvider* provider = 
            new ( ELeave ) CAknExtendedInputCapabilities::
            CAknExtendedInputCapabilitiesProvider;
    CleanupStack::PushL( provider );
    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewL();
    CleanupStack::PushL( inputCap );
    provider->SetExtendedInputCapabilities( inputCap );

    inputCap = provider->ExtendedInputCapabilities();
    STIF_ASSERT_NOT_NULL( inputCap );

    CleanupStack::PopAndDestroy( inputCap );
    CleanupStack::PopAndDestroy( provider );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestProviderSetMopParentL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestProviderSetMopParentL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestProviderSetMopParent, "In ProviderSetMopParent" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestProviderSetMopParent );
    // Print to log file
    iLog->Log( KTestProviderSetMopParent );

    CAknExtendedInputCapabilities::
    CAknExtendedInputCapabilitiesProvider* provider = 
            new ( ELeave ) CAknExtendedInputCapabilities::
            CAknExtendedInputCapabilitiesProvider;
    CleanupStack::PushL( provider );

    provider->SetMopParent( provider );

    CleanupStack::PopAndDestroy( provider );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapNewL, "In InputCapNewL" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapNewL );
    // Print to log file
    iLog->Log( KTestInputCapNewL );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewL();
    CleanupStack::PushL( inputCap );
    STIF_ASSERT_NOT_NULL( inputCap );

    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapNewLCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapNewLC, "In InputCapNewLC" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapNewLC );
    // Print to log file
    iLog->Log( KTestInputCapNewLC );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewLC();
    STIF_ASSERT_NOT_NULL( inputCap );

    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapSetCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapSetCapabilitiesL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapSetCapabilities, "In InputCapSetCapabilities" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapSetCapabilities );
    // Print to log file
    iLog->Log( KTestInputCapSetCapabilities );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewLC();

    inputCap->SetCapabilities( 0 );

    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapCapabilitiesL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapCapabilities, "In InputCapCapabilities" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapCapabilities );
    // Print to log file
    iLog->Log( KTestInputCapCapabilities );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewLC();

    TUint capabilities = inputCap->Capabilities();
    STIF_ASSERT_EQUALS( TUint( 0 ), capabilities );

    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapSupportsCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapSupportsCapabilitiesL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapSupportsCapabilities, "In InputCapSupportsCapabilities" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapSupportsCapabilities );
    // Print to log file
    iLog->Log( KTestInputCapSupportsCapabilities );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewLC();

    TBool supportsCap = inputCap->SupportsCapabilities( 0 );
    STIF_ASSERT_FALSE( supportsCap );

    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapSetMIDPConstraintsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapSetMIDPConstraintsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapSetMIDPConstraints, "In InputCapSetMIDPConstraints" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapSetMIDPConstraints );
    // Print to log file
    iLog->Log( KTestInputCapSetMIDPConstraints );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewLC();

    inputCap->SetMIDPConstraints( 0 );

    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapMIDPConstrainstL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapMIDPConstrainstL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapMIDPConstrainst, "In InputCapMIDPConstrainst" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapMIDPConstrainst );
    // Print to log file
    iLog->Log( KTestInputCapMIDPConstrainst );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewLC();

    TUint constrainst = inputCap->MIDPConstrainst();
    STIF_ASSERT_EQUALS( TUint( 0 ), constrainst );

    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapSetEditorTypeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapSetEditorTypeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapSetEditorType, "In InputCapSetEditorType" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapSetEditorType );
    // Print to log file
    iLog->Log( KTestInputCapSetEditorType );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewLC();

    inputCap->SetEditorType( 0 );

    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapEditorTypeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapEditorTypeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapEditorType, "In InputCapEditorType" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapEditorType );
    // Print to log file
    iLog->Log( KTestInputCapEditorType );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewLC();

    TInt type = inputCap->EditorType();
    STIF_ASSERT_EQUALS( 0, type );

    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapRegisterObserverL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapRegisterObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapRegisterObserver, "In InputCapRegisterObserver" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapRegisterObserver );
    // Print to log file
    iLog->Log( KTestInputCapRegisterObserver );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewLC();

    CAknExtInputCapObserver* observer = new ( ELeave ) CAknExtInputCapObserver;
    CleanupStack::PushL( observer );
    inputCap->RegisterObserver( observer );

    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapUnregisterObserverL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapUnregisterObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapUnregisterObserver, "In InputCapUnregisterObserver" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapUnregisterObserver );
    // Print to log file
    iLog->Log( KTestInputCapUnregisterObserver );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewLC();

    CAknExtInputCapObserver* observer = new ( ELeave ) CAknExtInputCapObserver;
    CleanupStack::PushL( observer );

    inputCap->UnregisterObserver( observer );

    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMInputCap::TestInputCapReportEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMInputCap::TestInputCapReportEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdominputcap, "testdominputcap" );
    _LIT( KTestInputCapReportEventL, "In InputCapReportEventL" );
    TestModuleIf().Printf( 0, Ktestdominputcap, KTestInputCapReportEventL );
    // Print to log file
    iLog->Log( KTestInputCapReportEventL );

    CAknExtendedInputCapabilities* inputCap = CAknExtendedInputCapabilities::NewLC();

    inputCap->ReportEventL( CAknExtendedInputCapabilities::
            MAknEventObserver::EActivatePenInputRequest, inputCap );

    CleanupStack::PopAndDestroy( inputCap );
    return KErrNone;

    }


//  [End of File]
