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
* Description:  test aknmemorycarddialog.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknmemorycarddialog.h>

#include "testdommemorycard.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMMemoryCard::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMMemoryCard::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestNewLC", CTestDOMMemoryCard::TestNewLCL ),
        ENTRY( "TestUnlockCardLD", CTestDOMMemoryCard::TestUnlockCardLDL ),
        ENTRY( "TestSetSelfPointer", CTestDOMMemoryCard::TestSetSelfPointerL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMMemoryCard::TestNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMMemoryCard::TestNewLCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMMemoryCard, "testdommemorycard" );
    _LIT( KTestNewLC, "In NewLC" );
    TestModuleIf().Printf( 0, KTestDOMMemoryCard, KTestNewLC );
    // Print to log file
    iLog->Log( KTestNewLC );

    CAknMemoryCardDialog* dlg = CAknMemoryCardDialog::NewLC();
    STIF_ASSERT_NOT_NULL( dlg );

    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMMemoryCard::TestUnlockCardLDL
// -----------------------------------------------------------------------------
//
TInt CTestDOMMemoryCard::TestUnlockCardLDL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTestDOMMemoryCard, "testdommemorycard" );
    _LIT( KTestUnlockCardLD, "In UnlockCardLD" );
    TestModuleIf().Printf( 0, KTestDOMMemoryCard, KTestUnlockCardLD );
    // Print to log file
    iLog->Log( KTestUnlockCardLD );

    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }

    CAknMemoryCardDialog* dlg = CAknMemoryCardDialog::NewLC();

    switch( num )
        {
        case 1:
            dlg->UnlockCardLD();
            break;

        case 2:
            {
            TDriveNumber drive = EDriveA;
            dlg->UnlockCardLD( drive );
            }
            break;

        default:
            CleanupStack::PopAndDestroy( dlg );
            return KErrNotSupported;
        }

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMMemoryCard::TestSetSelfPointerL
// -----------------------------------------------------------------------------
//
TInt CTestDOMMemoryCard::TestSetSelfPointerL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMMemoryCard, "testdommemorycard" );
    _LIT( KTestSetSelfPointer, "In SetSelfPointer" );
    TestModuleIf().Printf( 0, KTestDOMMemoryCard, KTestSetSelfPointer );
    // Print to log file
    iLog->Log( KTestSetSelfPointer );

    CAknMemoryCardDialog* dlg = CAknMemoryCardDialog::NewLC();

    dlg->SetSelfPointer( &dlg );

    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;

    }


//  [End of File]
