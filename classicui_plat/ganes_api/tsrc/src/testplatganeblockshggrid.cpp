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
* Description:  ganes_api
*
*/

// [INCLUDE FILES]
#include "testplatgane.h"

// ============================ MEMBER FUNCTIONS =========================


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgGridNewL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgGridNewL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchggridnewl, "In TestCHgGridNewL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchggridnewl);
    iLog->Log(Ktestchggridnewl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    CHgGrid* temp = CHgGrid::NewL( rect, item);
    CleanupStack::PushL( temp );
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgGridPreferredImageSize
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgGridPreferredImageSize( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(KTestCHgGridPreferredImageSize, "In TestCHgGridPreferredImageSize");
    TestModuleIf().Printf(0, Kctestplatgane, KTestCHgGridPreferredImageSize);
    iLog->Log(KTestCHgGridPreferredImageSize);

    CHgGrid::PreferredImageSize();

    return KErrNone;
    }

TInt CTestPlatGane::TestCHgGridSetLandscapeScrollingSupport( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(KTestCHgGridSetLandscapeScrollingSupport, "In TestCHgGridSetLandscapeScrollingSupport");
    TestModuleIf().Printf(0, Kctestplatgane, KTestCHgGridSetLandscapeScrollingSupport);
    iLog->Log(KTestCHgGridSetLandscapeScrollingSupport);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    CHgGrid* temp = CHgGrid::NewL( rect, item);
    temp->SetLandscapeScrollingSupport(ETrue);
    CleanupStack::PushL( temp );
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }
