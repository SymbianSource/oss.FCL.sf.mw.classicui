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
// CTestPlatGane::TestCHgSingleTextListL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgSingleTextListL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgsingletextlistl, "In TestCHgSingleTextListL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgsingletextlistl);
    iLog->Log(Ktestchgsingletextlistl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgSingleTextList* list = CHgSingleTextList::NewL( rect, item);
    CleanupStack::PushL( list );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

