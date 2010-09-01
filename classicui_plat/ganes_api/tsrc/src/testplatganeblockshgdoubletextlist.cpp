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
// CTestPlatGane::TestCHgDoubleTextListL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgDoubleTextListL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgdoubletextlistl, "In TestCHgDoubleTextListL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgdoubletextlistl);
    iLog->Log(Ktestchgdoubletextlistl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    CHgDoubleTextList* temp = CHgDoubleTextList::NewL( rect, item);
    CleanupStack::PushL( temp );
    CleanupStack::PopAndDestroy( temp );


    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgDoubleTextListPreferredImageSize
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgDoubleTextListPreferredImageSize( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(KTestCHgDoubleTextListPreferredImageSize, "In TestCHgDoubleTextListPreferredImageSize");
    TestModuleIf().Printf(0, Kctestplatgane, KTestCHgDoubleTextListPreferredImageSize);
    iLog->Log(KTestCHgDoubleTextListPreferredImageSize);

    CHgDoubleGraphicList::PreferredImageSize();

    return KErrNone;
    }

