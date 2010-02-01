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
// CTestPlatGane::TestCHgScrollerWithTitleNewL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerWithTitleNewL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerwithtitlenewl, "In TestCHgScrollerWithTitleNewL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerwithtitlenewl);
    iLog->Log(Ktestchgscrollerwithtitlenewl);
      
    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item, 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );
    
    CleanupStack::PopAndDestroy( scroler );
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerWithTitleInitScreenL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerWithTitleInitScreenL( CStifItemParser& /*aItem*/ )
    {
    
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerwithtitleinitscreenl, "In TestCHgScrollerWithTitleInitScreenL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerwithtitleinitscreenl);
    iLog->Log(Ktestchgscrollerwithtitleinitscreenl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item, 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );
    
    scroler->InitScreenL( rect );
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerWithTitleScrollerL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerWithTitleScrollerL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerwithtitlescrollerl, "In TestCHgScrollerWithTitleScrollerL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerwithtitlescrollerl);
    iLog->Log(Ktestchgscrollerwithtitlescrollerl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item, 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );
    
    scroler->Scroller();
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerWithTitleTitleItemL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerWithTitleTitleItemL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerwithtitletitleiteml, "In TestCHgScrollerWithTitleTitleItemL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerwithtitletitleiteml);
    iLog->Log(Ktestchgscrollerwithtitletitleiteml);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item, 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );
    
    scroler->TitleItem();
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerWithTitlePreferredImageSize
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerWithTitlePreferredImageSize( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(KTestCHgScrollerWithTitlePreferredImageSize, "In TestCHgScrollerWithTitlePreferredImageSize");
    TestModuleIf().Printf(0, Kctestplatgane, KTestCHgScrollerWithTitlePreferredImageSize);
    iLog->Log(KTestCHgScrollerWithTitlePreferredImageSize);
    
    CHgScrollerWithTitle::PreferredImageSize();

    return KErrNone;
    }

