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
* Description:  test aknappgrid.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknappgrid.h>

#include "testdomgrids.h"
#include "testdomgridscontainer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestdomgrids::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctestdomgrids::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestGridsConstructL", Ctestdomgrids::TestGridsConstructL ),
        ENTRY( "TestGridsSizeChanged", Ctestdomgrids::TestGridsSizeChangedL ),
        ENTRY( "TestGridsMinimumSize", Ctestdomgrids::TestGridsMinimumSizeL ),
        ENTRY( "TestGridsSetShortcutEnabledL",
                Ctestdomgrids::TestGridsSetShortcutEnabledL ),
        ENTRY( "TestGridsDrawBackgroundAroundGrid",
                Ctestdomgrids::TestGridsDrawBackgroundAroundGridL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctestdomgrids::TestGridsConstructL
// -----------------------------------------------------------------------------
//
TInt Ctestdomgrids::TestGridsConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgrids, "testdomgrids" );
    _LIT( KConstructL, "In ConstructL" );
    TestModuleIf().Printf( 0, Ktestdomgrids, KConstructL );
    // Print to log file
    iLog->Log( KConstructL );

    CAknAppStyleGrid* grid = new ( ELeave ) CAknAppStyleGrid;
    CleanupStack::PushL( grid );
    CTestDOMGridsContainer* container = CTestDOMGridsContainer::NewL();
    CleanupStack::PushL( container );
    grid->ConstructL( container );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomgrids::TestGridsSizeChangedL
// -----------------------------------------------------------------------------
//
TInt Ctestdomgrids::TestGridsSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgrids, "testdomgrids" );
    _LIT( KSizeChanged, "In SizeChanged" );
    TestModuleIf().Printf( 0, Ktestdomgrids, KSizeChanged );
    // Print to log file
    iLog->Log( KSizeChanged );

    CAknAppStyleGrid* grid = new ( ELeave ) CAknAppStyleGrid;
    CleanupStack::PushL( grid );
    CTestDOMGridsContainer* container = CTestDOMGridsContainer::NewL();
    CleanupStack::PushL( container );
    grid->ConstructL( container );

    grid->SizeChanged();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomgrids::TestGridsMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt Ctestdomgrids::TestGridsMinimumSizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgrids, "testdomgrids" );
    _LIT( KMinimumSize, "In MinimumSize" );
    TestModuleIf().Printf( 0, Ktestdomgrids, KMinimumSize );
    // Print to log file
    iLog->Log( KMinimumSize );

    CAknAppStyleGrid* grid = new ( ELeave ) CAknAppStyleGrid;
    CleanupStack::PushL( grid );
    CTestDOMGridsContainer* container = CTestDOMGridsContainer::NewL();
    CleanupStack::PushL( container );
    grid->ConstructL( container );

    TSize size( grid->MinimumSize() );
    STIF_ASSERT_TRUE( ( size.iWidth >= 0 ) && ( size.iHeight >= 0 ) );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomgrids::TestGridsSetShortcutEnabledL
// -----------------------------------------------------------------------------
//
TInt Ctestdomgrids::TestGridsSetShortcutEnabledL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgrids, "testdomgrids" );
    _LIT( KSetShortcutEnabledL, "In SetShortcutEnabledL" );
    TestModuleIf().Printf( 0, Ktestdomgrids, KSetShortcutEnabledL );
    // Print to log file
    iLog->Log( KSetShortcutEnabledL );

    CAknAppStyleGrid* grid = new ( ELeave ) CAknAppStyleGrid;
    CleanupStack::PushL( grid );
    CTestDOMGridsContainer* container = CTestDOMGridsContainer::NewL();
    CleanupStack::PushL( container );
    grid->ConstructL( container );

    grid->SetShortcutEnabledL( ETrue );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomgrids::TestGridsDrawBackgroundAroundGridL
// -----------------------------------------------------------------------------
//
TInt Ctestdomgrids::TestGridsDrawBackgroundAroundGridL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgrids, "testdomgrids" );
    _LIT( KDrawBackgroundAroundGrid, "In DrawBackgroundAroundGrid" );
    TestModuleIf().Printf( 0, Ktestdomgrids, KDrawBackgroundAroundGrid );
    // Print to log file
    iLog->Log( KDrawBackgroundAroundGrid );

    CAknAppStyleGrid* grid = new ( ELeave ) CAknAppStyleGrid;
    CleanupStack::PushL( grid );
    CTestDOMGridsContainer* container = CTestDOMGridsContainer::NewL();
    CleanupStack::PushL( container );
    grid->ConstructL( container );

    container->DoActivateGc();
    CWindowGc& gc = container->SystemGc();
    grid->DrawBackgroundAroundGrid( gc, TRect(), TRect() );

    container->DoDeactivateGc();
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;

    }


//  [End of File]
