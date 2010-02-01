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
* Description:  test functions for testing AknNotiferAppServerApplication.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknnotiferappserverapplication.h>

#include "testdomextnotifiers.h"


// CONSTANTS
const TInt KAppUiHandleErr = 0;
const TInt KOdinaryPosition = 1;
const TInt KErrorTxtLength = 64; 

_LIT( KAppUiHandleErrTxt, "AppUi HandleError" );

const TUid KUidTestApp = { 0x00000001 };


// FORWARD DECLARATION
class CTestNotifierAppServerApplication: public CAknNotifierAppServerApplication
    {
public:
    // Constructor
    CTestNotifierAppServerApplication() : CAknNotifierAppServerApplication() {}
    
    // from CAknNotifierAppServerApplication
    TUid AppDllUid() const { return KUidTestApp; }
    };

// CTestNotifierAppServerAppUi for testing CAknNotifierAppServerAppUi
class CTestNotifierAppServerAppUi: public CAknNotifierAppServerAppUi
    {
public:
    // Constructor
    CTestNotifierAppServerAppUi() : CAknNotifierAppServerAppUi() {}
    
    // Second phase constructor
    void ConstructL ()
        {
        CAknNotifierAppServerAppUi::ConstructL();
        }
    
    // from CAknNotifierAppServerAppUi
    void SetOrdinalPositionL( TInt aPosition )
        {
        CAknNotifierAppServerAppUi::SetOrdinalPositionL( aPosition );
        }
    };


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASACAknNotifierAppServerApplicationL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASACAknNotifierAppServerApplicationL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASACAknNotifierAppServerApplicationL, "TestCANASACAknNotifierAppServerApplicationL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASACAknNotifierAppServerApplicationL );
    // Print to log file
    iLog->Log( KTestCANASACAknNotifierAppServerApplicationL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    
    STIF_ASSERT_NOT_NULL( appsrvapp );
    
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASANewAppServerL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASANewAppServerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASANewAppServerL, "TestCANASANewAppServerL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASANewAppServerL );
    // Print to log file
    iLog->Log( KTestCANASANewAppServerL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CApaAppServer* appServer = NULL;
    appsrvapp->NewAppServerL( appServer );
    CleanupStack::PushL( appServer );
    
    STIF_ASSERT_NOT_NULL( appServer );
    
    CleanupStack::PopAndDestroy( appServer );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASACreateDocumentL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASACreateDocumentL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASACreateDocumentL, "TestCANASACreateDocumentL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASACreateDocumentL );
    // Print to log file
    iLog->Log( KTestCANASACreateDocumentL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CApaDocument* apadoc = appsrvapp->CreateDocumentL();
    CleanupStack::PushL( apadoc );
    
    STIF_ASSERT_NOT_NULL( apadoc );
    
    CleanupStack::PopAndDestroy( apadoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiCAknNotifierAppServerAppUiL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiCAknNotifierAppServerAppUiL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiCAknNotifierAppServerAppUiL, "TestCANASAUiCAknNotifierAppServerAppUiL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiCAknNotifierAppServerAppUiL );
    // Print to log file
    iLog->Log( KTestCANASAUiCAknNotifierAppServerAppUiL );
    
    CAknNotifierAppServerAppUi* appUi = new ( ELeave ) CAknNotifierAppServerAppUi();
    CleanupStack::PushL( appUi );
    
    STIF_ASSERT_NOT_NULL( appUi );
    
    appUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    CleanupStack::PopAndDestroy( appUi );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiConstructL, "TestCANASAUiConstructL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiConstructL );
    // Print to log file
    iLog->Log( KTestCANASAUiConstructL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CEikDocument* appsrvdoc = static_cast<CEikDocument*> ( appsrvapp->CreateDocumentL() );
    CleanupStack::PushL( appsrvdoc );
    CAknNotifierAppServerAppUi* appUi = new ( ELeave ) CAknNotifierAppServerAppUi();
    CleanupStack::PushL( appUi );
    
    appUi->SetDocument( appsrvdoc );
    
    appUi->ConstructL();
    
    
    CleanupStack::PopAndDestroy( appUi );
    CleanupStack::PopAndDestroy( appsrvdoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiHandleCommandL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiHandleCommandL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiHandleCommandL, "TestCANASAUiHandleCommandL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiHandleCommandL );
    // Print to log file
    iLog->Log( KTestCANASAUiHandleCommandL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CEikDocument* appsrvdoc = static_cast<CEikDocument*> ( appsrvapp->CreateDocumentL() );
    CleanupStack::PushL( appsrvdoc );
    CAknNotifierAppServerAppUi* appUi = new ( ELeave ) CAknNotifierAppServerAppUi();
    CleanupStack::PushL( appUi );
    appUi->SetDocument( appsrvdoc );
    appUi->ConstructL();
    
    appUi->HandleCommandL( EAknSoftkeyOk );
    
    CleanupStack::PopAndDestroy( appUi );
    CleanupStack::PopAndDestroy( appsrvdoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiHandleKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiHandleKeyEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiHandleKeyEventL, "TestCANASAUiHandleKeyEventL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiHandleKeyEventL );
    // Print to log file
    iLog->Log( KTestCANASAUiHandleKeyEventL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CEikDocument* appsrvdoc = static_cast<CEikDocument*> ( appsrvapp->CreateDocumentL() );
    CleanupStack::PushL( appsrvdoc );
    CAknNotifierAppServerAppUi* appUi = new ( ELeave ) CAknNotifierAppServerAppUi();
    CleanupStack::PushL( appUi );
    appUi->SetDocument( appsrvdoc );
    appUi->ConstructL();
    
    TKeyEvent keyEvent = { EKeyEnter, EStdKeyEnter, 0, 0 };
    appUi->HandleKeyEventL( keyEvent, EEventNull );
    
    CleanupStack::PopAndDestroy( appUi );
    CleanupStack::PopAndDestroy( appsrvdoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiSetFadedL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiSetFadedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiSetFadedL, "TestCANASAUiSetFadedL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiSetFadedL );
    // Print to log file
    iLog->Log( KTestCANASAUiSetFadedL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CEikDocument* appsrvdoc = static_cast<CEikDocument*> ( appsrvapp->CreateDocumentL() );
    CleanupStack::PushL( appsrvdoc );
    CAknNotifierAppServerAppUi* appUi = new ( ELeave ) CAknNotifierAppServerAppUi();
    CleanupStack::PushL( appUi );
    appUi->SetDocument( appsrvdoc );
    appUi->ConstructL();
    
    appUi->SetFadedL( ETrue );
    
    CleanupStack::PopAndDestroy( appUi );
    CleanupStack::PopAndDestroy( appsrvdoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiHandleErrorL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiHandleErrorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiHandleErrorL, "TestCANASAUiHandleErrorL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiHandleErrorL );
    // Print to log file
    iLog->Log( KTestCANASAUiHandleErrorL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CEikDocument* appsrvdoc = static_cast<CEikDocument*> ( appsrvapp->CreateDocumentL() );
    CleanupStack::PushL( appsrvdoc );
    CAknNotifierAppServerAppUi* appUi = new ( ELeave ) CAknNotifierAppServerAppUi();
    CleanupStack::PushL( appUi );
    appUi->SetDocument( appsrvdoc );
    appUi->ConstructL();
    
    SExtendedError exterr;
    TBuf<KErrorTxtLength> errtxt( KAppUiHandleErrTxt );
    appUi->HandleError( KAppUiHandleErr, exterr, errtxt, errtxt );
    
    CleanupStack::PopAndDestroy( appUi );
    CleanupStack::PopAndDestroy( appsrvdoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiHandleSystemEventL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiHandleSystemEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiHandleSystemEventL, "TestCANASAUiHandleSystemEventL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiHandleSystemEventL );
    // Print to log file
    iLog->Log( KTestCANASAUiHandleSystemEventL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CEikDocument* appsrvdoc = static_cast<CEikDocument*> ( appsrvapp->CreateDocumentL() );
    CleanupStack::PushL( appsrvdoc );
    CAknNotifierAppServerAppUi* appUi = new ( ELeave ) CAknNotifierAppServerAppUi();
    CleanupStack::PushL( appUi );
    appUi->SetDocument( appsrvdoc );
    appUi->ConstructL();
    
    TWsEvent wsEvent;
    appUi->HandleSystemEventL( wsEvent );
    
    CleanupStack::PopAndDestroy( appUi );
    CleanupStack::PopAndDestroy( appsrvdoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiSuppressAppSwitchingL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiSuppressAppSwitchingL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiSuppressAppSwitchingL, "TestCANASAUiSuppressAppSwitchingL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiSuppressAppSwitchingL );
    // Print to log file
    iLog->Log( KTestCANASAUiSuppressAppSwitchingL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CEikDocument* appsrvdoc = static_cast<CEikDocument*> ( appsrvapp->CreateDocumentL() );
    CleanupStack::PushL( appsrvdoc );
    CAknNotifierAppServerAppUi* appUi = new ( ELeave ) CAknNotifierAppServerAppUi();
    CleanupStack::PushL( appUi );
    appUi->SetDocument( appsrvdoc );
    appUi->ConstructL();
    
    appUi->SuppressAppSwitching( ETrue );
    
    CleanupStack::PopAndDestroy( appUi );
    CleanupStack::PopAndDestroy( appsrvdoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiSetManagerL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiSetManagerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiSetManagerL, "TestCANASAUiSetManagerL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiSetManagerL );
    // Print to log file
    iLog->Log( KTestCANASAUiSetManagerL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CEikDocument* appsrvdoc = static_cast<CEikDocument*> ( appsrvapp->CreateDocumentL() );
    CleanupStack::PushL( appsrvdoc );
    CAknNotifierAppServerAppUi* appUi = new ( ELeave ) CAknNotifierAppServerAppUi();
    CleanupStack::PushL( appUi );
    appUi->SetDocument( appsrvdoc );
    appUi->ConstructL();
    
    MEikSrvNotifierManager* manager = appUi->Manager();
    appUi->SetManager( manager );
    
    CleanupStack::PopAndDestroy( appUi );
    CleanupStack::PopAndDestroy( appsrvdoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiManagerL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiManagerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiManagerL, "TestCANASAUiManagerL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiManagerL );
    // Print to log file
    iLog->Log( KTestCANASAUiManagerL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CEikDocument* appsrvdoc = static_cast<CEikDocument*> ( appsrvapp->CreateDocumentL() );
    CleanupStack::PushL( appsrvdoc );
    CAknNotifierAppServerAppUi* appUi = new ( ELeave ) CAknNotifierAppServerAppUi();
    CleanupStack::PushL( appUi );
    appUi->SetDocument( appsrvdoc );
    appUi->ConstructL();
    
    appUi->Manager();
    
    CleanupStack::PopAndDestroy( appUi );
    CleanupStack::PopAndDestroy( appsrvdoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiEikSrvBlockedL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiEikSrvBlockedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiEikSrvBlockedL, "TestCANASAUiEikSrvBlockedL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiEikSrvBlockedL );
    // Print to log file
    iLog->Log( KTestCANASAUiEikSrvBlockedL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CEikDocument* appsrvdoc = static_cast<CEikDocument*> ( appsrvapp->CreateDocumentL() );
    CleanupStack::PushL( appsrvdoc );
    CAknNotifierAppServerAppUi* appUi = new ( ELeave ) CAknNotifierAppServerAppUi();
    CleanupStack::PushL( appUi );
    appUi->SetDocument( appsrvdoc );
    appUi->ConstructL();
    
    appUi->EikSrvBlocked();
    
    CleanupStack::PopAndDestroy( appUi );
    CleanupStack::PopAndDestroy( appsrvdoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANASAUiSetOrdinalPositionL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANASAUiSetOrdinalPositionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANASAUiSetOrdinalPositionL, "TestCANASAUiSetOrdinalPositionL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANASAUiSetOrdinalPositionL );
    // Print to log file
    iLog->Log( KTestCANASAUiSetOrdinalPositionL );
    
    CTestNotifierAppServerApplication* appsrvapp = new ( ELeave ) CTestNotifierAppServerApplication();
    CleanupStack::PushL( appsrvapp );
    CEikDocument* appsrvdoc = static_cast<CEikDocument*> ( appsrvapp->CreateDocumentL() );
    CleanupStack::PushL( appsrvdoc );
    CTestNotifierAppServerAppUi* testAppUi = new ( ELeave ) CTestNotifierAppServerAppUi();
    CleanupStack::PushL( testAppUi );
    testAppUi->SetDocument( appsrvdoc );
    testAppUi->ConstructL();
    
    testAppUi->SetOrdinalPositionL( KOdinaryPosition );
    
    CleanupStack::PopAndDestroy( testAppUi );
    CleanupStack::PopAndDestroy( appsrvdoc );
    CleanupStack::PopAndDestroy( appsrvapp );
    
    return KErrNone;
    }


//  [End of File]
