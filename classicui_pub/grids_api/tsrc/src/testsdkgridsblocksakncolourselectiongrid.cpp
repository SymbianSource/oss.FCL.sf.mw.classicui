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
* Description:  Test akncolourselectiongrid.h
*
*/


/*
 *  [INCLUDE FILES]
 */
#include <akncolourselectiongrid.h>
#include <eiklbo.h>
#include <coeaui.h>
#include <coecobs.h>

#include "testsdkgrids.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsCCSGNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsCCSGNewL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsCCSGNewL, "In TestGridsCCSGNewL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsCCSGNewL );
    iLog->Log( KTestGridsCCSGNewL );
    
    CArrayFixFlat<TRgb>* array = new( ELeave ) CArrayFixFlat<TRgb>(1);
    CleanupStack::PushL( array );
    TRgb rgb = ( KRgbRed, KRgbGreen, KRgbBlue );
    array->AppendL( rgb );
    TBool noneChosen = ETrue;
    iCCSGrid = CAknColourSelectionGrid::NewL( array, ETrue, noneChosen, rgb );

    STIF_ASSERT_NOT_NULL( iCCSGrid );

    CleanupStack::Pop( array );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsCCSGExecuteLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsCCSGExecuteLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsCCSGExecuteLD, "In TestGridsCCSGExecuteLD" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsCCSGExecuteLD );
    iLog->Log( KTestGridsCCSGExecuteLD );
    
    iCCSGrid->ExecuteLD();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsCCSGDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsCCSGDelete( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsCCSGDelete, "In TestGridsCCSGDelete" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsCCSGDelete );
    iLog->Log( KTestGridsCCSGDelete );

    delete iCCSGrid;
    iCCSGrid = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsCCSGHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsCCSGHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsCCSGHandleControlEventL, "In TestGridsCCSGHandleControlEventL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsCCSGHandleControlEventL );
    iLog->Log( KTestGridsCCSGHandleControlEventL );

    TPointerEvent event;
    iCCSGrid->HandlePointerEventL( event );
    return KErrNone;
    }


/*
 * End file
 */
