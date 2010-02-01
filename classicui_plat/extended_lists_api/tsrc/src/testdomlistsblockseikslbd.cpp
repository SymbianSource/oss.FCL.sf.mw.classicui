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
* Description:  test eikslbd.h
*
*/


#include <eikslbd.h>

#include "testdomlists.h"
#include "testdomlistscontainer.h"

//    CONSTANTS
const TInt KWidth = 25;
const TInt KHeight = 25;

_LIT( KText, "Text" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMLists::TestSetDataNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestSetDataNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestSetDataNewL, "In SetDataNewL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestSetDataNewL );
    // Print to log file
    iLog->Log( KTestSetDataNewL );

    CSettingsListBoxData* data = CSettingsListBoxData::NewL();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );

    CleanupStack::PopAndDestroy( data );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestSetDataDrawL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestSetDataDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestSetDataDraw, "In SetDataDraw" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestSetDataDraw );
    // Print to log file
    iLog->Log( KTestSetDataDraw );

    CSettingsListBoxData* data = CSettingsListBoxData::NewL();
    CleanupStack::PushL( data );

    TListItemProperties proper;
    CFormattedCellListBoxData::TColors gulcolor;
    TRect rect( 0, 0, KWidth, KHeight );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    container->DoActivateGc();
    CWindowGc& gc = container->SystemGc();

    data->Draw( proper, gc, &KText, rect, ETrue, gulcolor );

    container->DoDeactivateGc();
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( data );
    return KErrNone;

    }


