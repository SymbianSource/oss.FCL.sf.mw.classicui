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
* Description:  test aknsyncdraw.h
*
*/


#include <aknsyncdraw.h>

#include "testdomstatuspane.h"
#include "testdomstatuspanecontrol.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSyncDefConL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSyncDefConL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSyncDefConL, "In SyncDefConL" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSyncDefConL );
    // Print to log file
    iLog->Log( KTestSyncDefConL );

    TAknSyncControlDrawer* controlDrawer = new ( ELeave ) TAknSyncControlDrawer;
    CleanupStack::PushL( controlDrawer );
    STIF_ASSERT_NOT_NULL( controlDrawer );

    CleanupStack::PopAndDestroy( controlDrawer );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSyncSetControlL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSyncSetControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSyncSetControl, "In SyncSetControl" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSyncSetControl );
    // Print to log file
    iLog->Log( KTestSyncSetControl );

    TAknSyncControlDrawer controlDrawer;
    CTestStatusPaneControl* control = CTestStatusPaneControl::NewL();
    CleanupStack::PushL( control );
    controlDrawer.SetControl( control );

    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSyncMasrPrepareForDrawL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSyncMasrPrepareForDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSyncMasrPrepareForDraw, "In SyncMasrPrepareForDraw" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSyncMasrPrepareForDraw );
    // Print to log file
    iLog->Log( KTestSyncMasrPrepareForDraw );

    TAknSyncControlDrawer controlDrawer;
    CTestStatusPaneControl* control = CTestStatusPaneControl::NewL();
    CleanupStack::PushL( control );
    controlDrawer.SetControl( control );

    controlDrawer.MasrPrepareForDraw();

    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSyncMasrDrawL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSyncMasrDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSyncMasrDraw, "In SyncMasrDraw" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSyncMasrDraw );
    // Print to log file
    iLog->Log( KTestSyncMasrDraw );

    TAknSyncControlDrawer controlDrawer;
    CTestStatusPaneControl* control = CTestStatusPaneControl::NewL();
    CleanupStack::PushL( control );
    controlDrawer.SetControl( control );

    controlDrawer.MasrDraw();

    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSyncMasrDeactivateGcL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSyncMasrDeactivateGcL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSyncMasrDeactivateGc, "In SyncMasrDeactivateGc" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSyncMasrDeactivateGc );
    // Print to log file
    iLog->Log( KTestSyncMasrDeactivateGc );

    TAknSyncControlDrawer controlDrawer;
    CTestStatusPaneControl* control = CTestStatusPaneControl::NewL();
    CleanupStack::PushL( control );
    controlDrawer.SetControl( control );
    controlDrawer.MasrActivateGc();

    controlDrawer.MasrDeactivateGc();

    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSyncMasrActivateGcL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSyncMasrActivateGcL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSyncMasrActivateGc, "In SyncMasrActivateGc" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSyncMasrActivateGc );
    // Print to log file
    iLog->Log( KTestSyncMasrActivateGc );

    TAknSyncControlDrawer controlDrawer;
    CTestStatusPaneControl* control = CTestStatusPaneControl::NewL();
    CleanupStack::PushL( control );
    controlDrawer.SetControl( control );

    controlDrawer.MasrActivateGc();

    controlDrawer.MasrDeactivateGc();
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSynchNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSynchNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSynchNewL, "In SynchNewL" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSynchNewL );
    // Print to log file
    iLog->Log( KTestSynchNewL );

    CAknDrawSynchronizer* drawSynch = CAknDrawSynchronizer::NewL();
    CleanupStack::PushL( drawSynch );
    STIF_ASSERT_NOT_NULL( drawSynch );

    CleanupStack::PopAndDestroy( drawSynch );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSynchAddL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSynchAddL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSynchAddL, "In SynchAddL" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSynchAddL );
    // Print to log file
    iLog->Log( KTestSynchAddL );

    CAknDrawSynchronizer* drawSynch = CAknDrawSynchronizer::NewL();
    CleanupStack::PushL( drawSynch );

    CTestStatusPaneControl* control = CTestStatusPaneControl::NewL();
    CleanupStack::PushL( control );
    TAknSyncControlDrawer controlDrawer;
    controlDrawer.SetControl( control );

    drawSynch->AddL( &controlDrawer );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( drawSynch );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSynchRemoveL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSynchRemoveL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSynchRemove, "In SynchRemove" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSynchRemove );
    // Print to log file
    iLog->Log( KTestSynchRemove );

    CAknDrawSynchronizer* drawSynch = CAknDrawSynchronizer::NewL();
    CleanupStack::PushL( drawSynch );

    CTestStatusPaneControl* control = CTestStatusPaneControl::NewL();
    CleanupStack::PushL( control );
    TAknSyncControlDrawer controlDrawer;
    controlDrawer.SetControl( control );
    drawSynch->AddL( &controlDrawer );

    drawSynch->Remove( &controlDrawer );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( drawSynch );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSynchSignalL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSynchSignalL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSynchSignal, "In SynchSignal" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSynchSignal );
    // Print to log file
    iLog->Log( KTestSynchSignal );

    CAknDrawSynchronizer* drawSynch = CAknDrawSynchronizer::NewL();
    CleanupStack::PushL( drawSynch );

    CTestStatusPaneControl* control = CTestStatusPaneControl::NewL();
    CleanupStack::PushL( control );
    TAknSyncControlDrawer controlDrawer;
    controlDrawer.SetControl( control );
    drawSynch->AddL( &controlDrawer );

    drawSynch->Signal( &controlDrawer );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( drawSynch );
    return KErrNone;

    }

