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
* Description:  Test PslnFWBaseContainer.h
 *
*/


// [INCLUDE FILES]
#include "testdompslnframework.h"
#include "testdompslnfwbc.h"
// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBCConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBCConstructL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBCConstructL, "In TestPlsnFWBCConstructL" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBCConstructL );
    // Print to log file
    iLog->Log( KTestPlsnFWBCConstructL );

    TRect rect( 0, 0, 0, 0 );
    iFWBContainer->ConstructL( rect );
    STIF_ASSERT_NOT_NULL( iFWBContainer );

    return KErrNone;
    }



// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBCBaseConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBCBaseConstructL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBCBaseConstructL, "In TestPlsnFWBCBaseConstructL" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBCBaseConstructL );
    // Print to log file
    iLog->Log( KTestPlsnFWBCBaseConstructL );

    TRect rect( 0, 0, 0, 0 );
    iFWBContainer->ConstructL( rect );
    STIF_ASSERT_NOT_NULL( iFWBContainer );

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBCCPslnFWBaseContainer
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBCCPslnFWBaseContainerL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBCCPslnFWBaseContainer, "In TestPlsnFWBCCPslnFWBaseContainer" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBCCPslnFWBaseContainer );
    // Print to log file
    iLog->Log( KTestPlsnFWBCCPslnFWBaseContainer );

    TRect rect( 0, 0, 0, 0 );
    iFWBContainer = new( ELeave ) CTestPslnFWBaseContainer;
    STIF_ASSERT_NOT_NULL( iFWBContainer );

    return KErrNone;

    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBCDelete
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBCDelete( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBCDelete, "In TestPlsnFWBCDelete" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBCDelete );
    // Print to log file
    iLog->Log( KTestPlsnFWBCDelete );

    delete iFWBContainer;
    iFWBContainer = NULL;
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBCSetMiddleSoftkeyObserver
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBCSetMiddleSoftkeyObserverL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBCSetMiddleSoftkeyObserver, "In TestPlsnFWBCSetMiddleSoftkeyObserver" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBCSetMiddleSoftkeyObserver );
    // Print to log file
    iLog->Log( KTestPlsnFWBCSetMiddleSoftkeyObserver );

    iFWBContainer->SetMiddleSoftkeyObserver( NULL );

    return KErrNone;
    }


