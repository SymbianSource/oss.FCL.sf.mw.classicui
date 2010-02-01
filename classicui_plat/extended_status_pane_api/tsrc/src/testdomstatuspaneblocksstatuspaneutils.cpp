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
* Description:  test aknstatuspaneutils.h
*
*/



#include <aknstatuspaneutils.h>

#include "testdomstatuspane.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestUtilsStaconPaneActive
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestUtilsStaconPaneActive( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestUtilsStaconPaneActive, "In UtilsStaconPaneActive" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestUtilsStaconPaneActive );
    // Print to log file
    iLog->Log( KTestUtilsStaconPaneActive );

    TBool active = AknStatuspaneUtils::StaconPaneActive();
    STIF_ASSERT_FALSE( active );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestUtilsStaconSoftKeysLeft
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestUtilsStaconSoftKeysLeft( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestUtilsStaconSoftKeysLeft, "In UtilsStaconSoftKeysLeft" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestUtilsStaconSoftKeysLeft );
    // Print to log file
    iLog->Log( KTestUtilsStaconSoftKeysLeft );

    TBool staconSoftKeysLeft = AknStatuspaneUtils::StaconSoftKeysLeft();
    STIF_ASSERT_FALSE( staconSoftKeysLeft );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestUtilsStaconSoftKeysRight
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestUtilsStaconSoftKeysRight( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestUtilsStaconSoftKeysRight, "In UtilsStaconSoftKeysRight" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestUtilsStaconSoftKeysRight );
    // Print to log file
    iLog->Log( KTestUtilsStaconSoftKeysRight );

    AknStatuspaneUtils::StaconSoftKeysRight();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestUtilsIdleLayoutActive
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestUtilsIdleLayoutActive( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestUtilsIdleLayoutActive, "In UtilsIdleLayoutActive" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestUtilsIdleLayoutActive );
    // Print to log file
    iLog->Log( KTestUtilsIdleLayoutActive );

    TBool active = AknStatuspaneUtils::IdleLayoutActive();
    STIF_ASSERT_FALSE( active );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestUtilsFlatLayoutActive
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestUtilsFlatLayoutActive( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestUtilsFlatLayoutActive, "In UtilsFlatLayoutActive" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestUtilsFlatLayoutActive );
    // Print to log file
    iLog->Log( KTestUtilsFlatLayoutActive );

    TBool active = AknStatuspaneUtils::FlatLayoutActive();
    STIF_ASSERT_FALSE( active );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestUtilsUsualLayoutActive
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestUtilsUsualLayoutActive( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestUtilsUsualLayoutActive, "In UtilsUsualLayoutActive" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestUtilsUsualLayoutActive );
    // Print to log file
    iLog->Log( KTestUtilsUsualLayoutActive );

    TBool active = AknStatuspaneUtils::UsualLayoutActive();
    STIF_ASSERT_TRUE( active );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestUtilsSmallLayoutActive
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestUtilsSmallLayoutActive( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestUtilsSmallLayoutActive, "In UtilsSmallLayoutActive" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestUtilsSmallLayoutActive );
    // Print to log file
    iLog->Log( KTestUtilsSmallLayoutActive );

    TBool active = AknStatuspaneUtils::SmallLayoutActive();
    STIF_ASSERT_FALSE( active );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestUtilsTouchPaneCompatibleLayoutActive
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestUtilsTouchPaneCompatibleLayoutActive( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestUtilsTouchPaneCompatibleLayoutActive, "In UtilsTouchPaneCompatibleLayoutActive" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestUtilsTouchPaneCompatibleLayoutActive );
    // Print to log file
    iLog->Log( KTestUtilsTouchPaneCompatibleLayoutActive );

    TBool active = AknStatuspaneUtils::TouchPaneCompatibleLayoutActive();
    STIF_ASSERT_TRUE( active );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestUtilsExtendedStaconPaneActive
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestUtilsExtendedStaconPaneActive( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestUtilsExtendedStaconPaneActive, "In UtilsExtendedStaconPaneActive" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestUtilsExtendedStaconPaneActive );
    // Print to log file
    iLog->Log( KTestUtilsExtendedStaconPaneActive );

    TBool active = AknStatuspaneUtils::ExtendedStaconPaneActive();
    STIF_ASSERT_FALSE( active );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestUtilsExtendedFlatLayoutActive
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestUtilsExtendedFlatLayoutActive( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestUtilsExtendedFlatLayoutActive, "In UtilsExtendedFlatLayoutActive" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestUtilsExtendedFlatLayoutActive );
    // Print to log file
    iLog->Log( KTestUtilsExtendedFlatLayoutActive );

    TBool active = AknStatuspaneUtils::ExtendedFlatLayoutActive();
    STIF_ASSERT_FALSE( active );

    return KErrNone;

    }

