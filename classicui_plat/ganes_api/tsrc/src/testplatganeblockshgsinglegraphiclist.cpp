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
// CTestPlatGane::TestCHgSingleGraphicListNewL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgSingleGraphicListNewL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgsinglegraphiclistnewl, "In TestCHgSingleGraphicListNewL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgsinglegraphiclistnewl);
    iLog->Log(Ktestchgsinglegraphiclistnewl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgSingleGraphicList* list = CHgSingleGraphicList::NewL( rect, item);
    CleanupStack::PushL( list );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgSingleGraphicListPreferredImageSize
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgSingleGraphicListPreferredImageSize( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(KTestCHgSingleGraphicListPreferredImageSize, "In TestCHgSingleGraphicListPreferredImageSize");
    TestModuleIf().Printf(0, Kctestplatgane, KTestCHgSingleGraphicListPreferredImageSize);
    iLog->Log(KTestCHgSingleGraphicListPreferredImageSize);

    CHgSingleGraphicList::PreferredImageSize();

    return KErrNone;
    }

