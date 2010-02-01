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
* Description:  test aknlistloadertfx.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknlistloadertfx.h>
#include <eiklbx.h>
#include <akndialog.h>
#include <eikmenup.h>
#include <aknsinglestyletreelist.h>

#include <eiktxlbx.h>

#include "testdomlisteffects.h"
#include "testdomlisteffectscontainer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMListEffects::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMListEffects::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestTfxApi", CTestDOMListEffects::TestTfxApiL ),
        ENTRY( "TestTfxApiInternal", CTestDOMListEffects::TestTfxApiInternalL ),
        ENTRY( "TestCreateTfxGc", CTestDOMListEffects::TestCreateTfxGcL ),
        ENTRY( "TestRemoveTfxGc", CTestDOMListEffects::TestRemoveTfxGcL ),
        ENTRY( "TestInvalidateAll", CTestDOMListEffects::TestInvalidateAll ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMListEffects::TestTfxApiL
// -----------------------------------------------------------------------------
//
TInt CTestDOMListEffects::TestTfxApiL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlisteffects, "testdomlisteffects" );
    _LIT( KTestTfxApi, "In TfxApi" );
    TestModuleIf().Printf( 0, Ktestdomlisteffects, KTestTfxApi );
    // Print to log file
    iLog->Log( KTestTfxApi );

    CTestDOMListsEffectsContainer* container = CTestDOMListsEffectsContainer::NewL();
    CleanupStack::PushL( container );
    container->DoActivateGc();
    CWindowGc& gc = container->SystemGc();

    MAknListBoxTfx* fxApi = CAknListLoader::TfxApi( &gc );
    STIF_ASSERT_NULL( fxApi );

    container->DoDeactivateGc();
    CleanupStack::PopAndDestroy( container );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMListEffects::TestTfxApiInternalL
// -----------------------------------------------------------------------------
//
TInt CTestDOMListEffects::TestTfxApiInternalL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlisteffects, "testdomlisteffects" );
    _LIT( KTestTfxApiInternal, "In TfxApiInternal" );
    TestModuleIf().Printf( 0, Ktestdomlisteffects, KTestTfxApiInternal );
    // Print to log file
    iLog->Log( KTestTfxApiInternal );

    CTestDOMListsEffectsContainer* container = CTestDOMListsEffectsContainer::NewL();
    CleanupStack::PushL( container );
    container->DoActivateGc();
    CWindowGc& gc = container->SystemGc();

    MAknListBoxTfxInternal* fxApiInternal = CAknListLoader::TfxApiInternal( &gc );
    STIF_ASSERT_NULL( fxApiInternal );

    container->DoDeactivateGc();
    CleanupStack::PopAndDestroy( container );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMListEffects::TestCreateTfxGcL
// -----------------------------------------------------------------------------
//
TInt CTestDOMListEffects::TestCreateTfxGcL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Ktestdomlisteffects, "testdomlisteffects" );
    _LIT( KTestCreateTfxGc, "In CreateTfxGc" );
    TestModuleIf().Printf( 0, Ktestdomlisteffects, KTestCreateTfxGc );
    // Print to log file
    iLog->Log( KTestCreateTfxGc );

    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }

    CWindowGc* gc = NULL;
    TInt topIndex = 0;
    TInt items= 1;

    CTestDOMListsEffectsContainer* container = 
            CTestDOMListsEffectsContainer::NewL();
    CleanupStack::PushL( container );
    CEikTextListBox* listbox = new ( ELeave ) CEikTextListBox();
    CleanupStack::PushL( listbox );
    listbox->ConstructL( container, CEikListBox::EPopout );

    CAknDialog* dlg = new ( ELeave ) CAknDialog();
    CleanupStack::PushL( dlg );
    CEikMenuPane* menupane = new ( ELeave ) CEikMenuPane(dlg);
    CleanupStack::PushL( menupane );

    switch ( num )
        {
        case 1:
            {
            gc = CAknListLoader::CreateTfxGc( *listbox );
            STIF_ASSERT_NOT_NULL( gc );
            break;
            }
        case 2:
            {
            gc = CAknListLoader::CreateTfxGc( *menupane, topIndex, items );
            break;
            }
        case 3:
            {
            CCoeControl* coe = dynamic_cast<CCoeControl* > (listbox);
            gc = CAknListLoader::CreateTfxGc( *coe );
            break;
            }
        default:
            {
            CleanupStack::PopAndDestroy( menupane );
            CleanupStack::PopAndDestroy( dlg );
            CleanupStack::PopAndDestroy( listbox );
            CleanupStack::PopAndDestroy( container );
            return KErrNotSupported;
            }
        }

    CleanupStack::PopAndDestroy( menupane );
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( listbox );
    CleanupStack::PopAndDestroy( container );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMListEffects::TestRemoveTfxGcL
// -----------------------------------------------------------------------------
//
TInt CTestDOMListEffects::TestRemoveTfxGcL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlisteffects, "testdomlisteffects" );
    _LIT( KTestRemoveTfxGc, "In RemoveTfxGc" );
    TestModuleIf().Printf( 0, Ktestdomlisteffects, KTestRemoveTfxGc );
    // Print to log file
    iLog->Log( KTestRemoveTfxGc );

    CTestDOMListsEffectsContainer* container = CTestDOMListsEffectsContainer::NewL();
    CleanupStack::PushL( container );
    container->DoActivateGc();
    CWindowGc& gc = container->SystemGc();

    CAknListLoader::RemoveTfxGc( &gc );

    container->DoDeactivateGc();
    CleanupStack::PopAndDestroy( container );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMListEffects::TestInvalidateAll
// -----------------------------------------------------------------------------
//
TInt CTestDOMListEffects::TestInvalidateAll( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlisteffects, "testdomlisteffects" );
    _LIT( KTestInvalidateAll, "In InvalidateAll" );
    TestModuleIf().Printf( 0, Ktestdomlisteffects, KTestInvalidateAll );
    // Print to log file
    iLog->Log( KTestInvalidateAll );

    CAknListLoader::InvalidateAll();

    return KErrNone;

    }


//  [End of File]
