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
// CTestPlatGane::TestCHgSingleLargeListNewL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgSingleLargeListNewL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgsinglelargelistnewl, "In TestCHgSingleLargeListNewL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgsinglelargelistnewl);
    iLog->Log(Ktestchgsinglelargelistnewl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgSingleLargeList* list = CHgSingleLargeList::NewL( rect, item);
    CleanupStack::PushL( list );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgSingleLargeListPreferredImageSize
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgSingleLargeListPreferredImageSize( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(KTestCHgSingleLargeListPreferredImageSize, "In TestCHgSingleLargeListPreferredImageSize");
    TestModuleIf().Printf(0, Kctestplatgane, KTestCHgSingleLargeListPreferredImageSize);
    iLog->Log(KTestCHgSingleLargeListPreferredImageSize);

    CHgSingleLargeList::PreferredImageSize();

    return KErrNone;
    }

