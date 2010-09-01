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
TInt CTestPlatGane::TestCHgItemNewL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemnewl, "In TestCHgItemNewL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemnewl);
    iLog->Log(Ktestchgitemnewl);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemNewLCL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemNewLCL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemnewlcl, "In TestCHgItemNewLCL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemnewlcl);
    iLog->Log(Ktestchgitemnewlcl);

    CHgItem* temp = CHgItem::NewLC();
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemIconL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemIconL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemiconl, "In TestCHgItemIconL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemiconl);
    iLog->Log(Ktestchgitemiconl);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    temp->Icon();
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemTitleL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemtitlel, "In TestCHgItemTitleL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemtitlel);
    iLog->Log(Ktestchgitemtitlel);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    temp->Title();
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemTextL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemTextL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemtextl, "In TestCHgItemTextL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemtextl);
    iLog->Log(Ktestchgitemtextl);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    temp->Text();
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemTimeL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemTimeL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemtimel, "In TestCHgItemTimeL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemtimel);
    iLog->Log(Ktestchgitemtimel);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    temp->Time();
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemSetIconL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemSetIconL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemseticonl, "In TestCHgItemSetIconL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemseticonl);
    iLog->Log(Ktestchgitemseticonl);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    temp->SetIcon( NULL );
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemSetTitleL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemSetTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemsettitlel, "In TestCHgItemSetTitleL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemsettitlel);
    iLog->Log(Ktestchgitemsettitlel);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    temp->SetTitleL( _L( "SetTile" ) );
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemSetTextL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemSetTextL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemsettextl, "In TestCHgItemSetTextL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemsettextl);
    iLog->Log(Ktestchgitemsettextl);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    temp->SetTextL( _L( "SetText" ) );
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemSetTimeL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemSetTimeL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemsettimel, "In TestCHgItemSetTimeL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemsettimel);
    iLog->Log(Ktestchgitemsettimel);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    TInt tp = 10;
    TTime time(tp);
    
    temp->SetTime( time );
    CleanupStack::PopAndDestroy( temp );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemFlagsL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemFlagsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemflagsl, "In TestCHgItemFlagsL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemflagsl);
    iLog->Log(Ktestchgitemflagsl);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    temp->Flags();
    CleanupStack::PopAndDestroy( temp );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemSetFlagsL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemSetFlagsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemsetflagsl, "In TestCHgItemSetFlagsL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemsetflagsl);
    iLog->Log(Ktestchgitemsetflagsl);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    TInt flag = 0;
    temp->SetFlags( flag );
    CleanupStack::PopAndDestroy( temp );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgItemClearFlagsL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgItemClearFlagsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgitemclearflagsl, "In TestCHgItemClearFlagsL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgitemclearflagsl);
    iLog->Log(Ktestchgitemclearflagsl);

    CHgItem* temp = CHgItem::NewL();
    CleanupStack::PushL( temp );
    TInt flag = 0 ;
    temp->ClearFlags( flag );
    CleanupStack::PopAndDestroy( temp );
    
    return KErrNone;
    }

