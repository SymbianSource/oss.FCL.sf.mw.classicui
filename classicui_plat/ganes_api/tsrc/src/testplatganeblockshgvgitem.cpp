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
// CTestPlatGane::TestCHgItemNewL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgItemNewL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemnewl, "In TestCHgVgItemNewL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemnewl);
    iLog->Log(Ktestchgitemnewl);

    CHgVgItem* temp = CHgVgItem::NewL();
    CleanupStack::PushL( temp );
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemNewLCL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgItemNewLC( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemnewlcl, "In TestCHgVgItemNewLC");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemnewlcl);
    iLog->Log(Ktestchgitemnewlcl);

    CHgVgItem* temp = CHgVgItem::NewLC();
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemSetIconL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgItemSetIcon( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemseticonl, "In TestCHgVgItemSetIcon");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemseticonl);
    iLog->Log(Ktestchgitemseticonl);

    CHgVgItem* temp = CHgVgItem::NewL();
    CleanupStack::PushL( temp );
    temp->SetIcon( NULL );
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

