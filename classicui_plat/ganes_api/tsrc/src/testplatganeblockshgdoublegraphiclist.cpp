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

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgDoubleGraphicListL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgDoubleGraphicListL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgdoublegraphiclistl, "In TestCHgDoubleGraphicListL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgdoublegraphiclistl);
    iLog->Log(Ktestchgdoublegraphiclistl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    CHgDoubleGraphicList* temp = CHgDoubleGraphicList::NewL( rect, item);
    CleanupStack::PushL( temp );
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgDoubleGraphicListPreferredImageSize
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgDoubleGraphicListPreferredImageSize( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(KTestCHgDoubleGraphicListPreferredImageSize, "In TestCHgDoubleGraphicListPreferredImageSize");
    TestModuleIf().Printf(0, Kctestplatgane, KTestCHgDoubleGraphicListPreferredImageSize);
    iLog->Log(KTestCHgDoubleGraphicListPreferredImageSize);

    CHgDoubleGraphicList::PreferredImageSize();

    return KErrNone;
    }

