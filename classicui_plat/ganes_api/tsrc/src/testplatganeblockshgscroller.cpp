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
// CTestPlatGane::TestCHgScrollerInitScreenL1
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerInitScreenL1( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerinitscreenl1, "In TestCHgScrollerInitScreenL1");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerinitscreenl1);
    iLog->Log(Ktestchgscrollerinitscreenl1);

    // DSA not supported anymore.

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerInitScreenL2L
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerInitScreenL2L( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerinitscreenl2l, "In TestCHgScrollerInitScreenL2L");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerinitscreenl2l);
    iLog->Log(Ktestchgscrollerinitscreenl2l);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item, 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.InitScreenL( rect );
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerRefreshScreenL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerRefreshScreenL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerrefreshscreenl, "In TestCHgScrollerRefreshScreenL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerrefreshscreenl);
    iLog->Log(Ktestchgscrollerrefreshscreenl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.RefreshScreen( item );
    
    CleanupStack::PopAndDestroy( scroler );
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerFirstIndexOnScreenL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerFirstIndexOnScreenL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerfirstindexonscreenl, "In TestCHgScrollerFirstIndexOnScreenL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerfirstindexonscreenl);
    iLog->Log(Ktestchgscrollerfirstindexonscreenl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.FirstIndexOnScreen();
    
    CleanupStack::PopAndDestroy( scroler );
        
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerItemsOnScreenL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerItemsOnScreenL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrolleritemsonscreenl, "In TestCHgScrollerItemsOnScreenL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrolleritemsonscreenl);
    iLog->Log(Ktestchgscrolleritemsonscreenl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.ItemsOnScreen();
    
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerItemL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerItemL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrolleriteml, "In TestCHgScrollerItemL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrolleriteml);
    iLog->Log(Ktestchgscrolleriteml);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    
    CHgItem* newItem = CHgItem::NewL();
    CleanupStack::PushL( newItem );
    
    temp.AddItem( newItem );
    temp.ItemL( item );
    
    CleanupStack::Pop( newItem );
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerSetItemL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerSetItemL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollersetiteml, "In TestCHgScrollerSetItemL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollersetiteml);
    iLog->Log(Ktestchgscrollersetiteml);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    CHgItem* newItem = CHgItem::NewL();
  
    temp.SetItem( newItem, item );
    
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerAddItemL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerAddItemL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrolleradditeml, "In TestCHgScrollerAddItemL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrolleradditeml);
    iLog->Log(Ktestchgscrolleradditeml);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
  
    CHgItem* newItem = CHgItem::NewL();

    temp.AddItem( newItem );

    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerInsertItemL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerInsertItemL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerinsertiteml, "In TestCHgScrollerInsertItemL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerinsertiteml);
    iLog->Log(Ktestchgscrollerinsertiteml);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    CHgItem* newItem = CHgItem::NewL();

    temp.InsertItem( newItem, item );
 
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;
    
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerRemoveItemL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerRemoveItemL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerremoveiteml, "In TestCHgScrollerRemoveItemL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerremoveiteml);
    iLog->Log(Ktestchgscrollerremoveiteml);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    item = 0;

    CHgItem* newItem = CHgItem::NewL();

    temp.AddItem( newItem );
    temp.RemoveItem( item );
    
    CleanupStack::PopAndDestroy( scroler );
    

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerSelectedIndexL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerSelectedIndexL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerselectedindexl, "In TestCHgScrollerSelectedIndexL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerselectedindexl);
    iLog->Log(Ktestchgscrollerselectedindexl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();

    temp.SelectedIndex();
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerSetSelectedIndexL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerSetSelectedIndexL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollersetselectedindexl, "In TestCHgScrollerSetSelectedIndexL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollersetselectedindexl);
    iLog->Log(Ktestchgscrollersetselectedindexl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    item = 0;

    CHgItem* newItem = CHgItem::NewL();

    temp.AddItem( newItem );
    temp.SetSelectedIndex( item );
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerMarkL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerMarkL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollermarkl, "In TestCHgScrollerMarkL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollermarkl);
    iLog->Log(Ktestchgscrollermarkl);
    
    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    TInt itemmark = 0;
    temp.Mark( itemmark );
    
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerUnMarkL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerUnMarkL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerunmarkl, "In TestCHgScrollerUnMarkL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerunmarkl);
    iLog->Log(Ktestchgscrollerunmarkl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    TInt itemmark = 0;
    temp.Mark( itemmark );
    temp.UnMark( itemmark );
    
    CleanupStack::PopAndDestroy( scroler );
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerMarkAllL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerMarkAllL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollermarkalll, "In TestCHgScrollerMarkAllL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollermarkalll);
    iLog->Log(Ktestchgscrollermarkalll);
    
    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.MarkAll();
    
    CleanupStack::PopAndDestroy( scroler );
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerUnMarkAllL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerUnMarkAllL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerunmarkalll, "In TestCHgScrollerUnMarkAllL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerunmarkalll);
    iLog->Log(Ktestchgscrollerunmarkalll);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.MarkAll();
    temp.UnMarkAll();
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerGetMarkedItemsL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerGetMarkedItemsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollergetmarkeditemsl, "In TestCHgScrollerGetMarkedItemsL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollergetmarkeditemsl);
    iLog->Log(Ktestchgscrollergetmarkeditemsl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    RArray<TInt> indexes;
    CleanupClosePushL( indexes );
    temp.GetMarkedItemsL( indexes );
    indexes.Reset();
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerResetL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerResetL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerresetl, "In TestCHgScrollerResetL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerresetl);
    iLog->Log(Ktestchgscrollerresetl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();

    temp.Reset();
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerResizeL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerResizeL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerresizel, "In TestCHgScrollerResizeL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerresizel);
    iLog->Log(Ktestchgscrollerresizel);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    TInt tmp = 0;
    temp.ResizeL( tmp );
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerSetEmptyTextL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerSetEmptyTextL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollersetemptytextl, "In TestCHgScrollerSetEmptyTextL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollersetemptytextl);
    iLog->Log(Ktestchgscrollersetemptytextl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    
    TBufC<KStringSize> tmp( _L("Hi") );
    temp.SetEmptyTextL( tmp );
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerItemCountL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerItemCountL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrolleritemcountl, "In TestCHgScrollerItemCountL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrolleritemcountl);
    iLog->Log(Ktestchgscrolleritemcountl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.ItemCount();
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerSetScrollBarTypeL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerSetScrollBarTypeL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollersetscrollbartypel, "In TestCHgScrollerSetScrollBarTypeL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollersetscrollbartypel);
    iLog->Log(Ktestchgscrollersetscrollbartypel);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.SetScrollBarTypeL( CHgScroller::EHgScrollerScrollBar );
    
    CleanupStack::PopAndDestroy( scroler );
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerSetFlagsL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerSetFlagsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollersetflagsl, "In TestCHgScrollerSetFlagsL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollersetflagsl);
    iLog->Log(Ktestchgscrollersetflagsl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    TInt tmp = 0;
    temp.SetFlags( tmp );
    
    CleanupStack::PopAndDestroy( scroler );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerClearFlagsL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerClearFlagsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerclearflagsl, "In TestCHgScrollerClearFlagsL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerclearflagsl);
    iLog->Log(Ktestchgscrollerclearflagsl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    TInt tmp = 0;
    temp.ClearFlags( tmp );
    
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerFlagsL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerFlagsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerflagsl, "In TestCHgScrollerFlagsL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerflagsl);
    iLog->Log(Ktestchgscrollerflagsl);
    
    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.Flags();
   
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerHightlightItemL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerHightlightItemL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerhightlightiteml, "In TestCHgScrollerHightlightItemL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerhightlightiteml);
    iLog->Log(Ktestchgscrollerhightlightiteml);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.HightlightItem( _L("Test") );
    
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerSetDefaultIconL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerSetDefaultIconL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollersetdefaulticonl, "In TestCHgScrollerSetDefaultIconL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollersetdefaulticonl);
    iLog->Log(Ktestchgscrollersetdefaulticonl);

    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.SetDefaultIconL( NULL );
    
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerDisableScrollBufferL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerDisableScrollBufferL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerdisablescrollbufferl, "In TestCHgScrollerDisableScrollBufferL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerdisablescrollbufferl);
    iLog->Log(Ktestchgscrollerdisablescrollbufferl);
    
    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
    		                  CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    temp.DisableScrollBuffer();
    
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerEnableScrollBufferL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerEnableScrollBufferL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerdisablescrollbufferl, "In TestCHgScrollerDisableScrollBufferL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerdisablescrollbufferl);
    iLog->Log(Ktestchgscrollerdisablescrollbufferl);
    
    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
                              CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    TDummyObserver obs;
    temp.EnableScrollBufferL(obs, 80, 20);
        
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;    
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerSetSelectionObserver
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerSetSelectionObserver( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerdisablescrollbufferl, "In TestCHgScrollerDisableScrollBufferL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerdisablescrollbufferl);
    iLog->Log(Ktestchgscrollerdisablescrollbufferl);
    
    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
                              CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    TDummyObserver obs;
    temp.SetSelectionObserver(obs);
    
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;    
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgScrollerSetMarkingObserver
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgScrollerSetMarkingObserver( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatgane, "CTestPlatGane");
    _LIT(Ktestchgscrollerdisablescrollbufferl, "In TestCHgScrollerDisableScrollBufferL");
    TestModuleIf().Printf(0, Kctestplatgane, Ktestchgscrollerdisablescrollbufferl);
    iLog->Log(Ktestchgscrollerdisablescrollbufferl);
    
    TInt left = 0;
    TInt wrigth = KTest;
    TInt item = 0;
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) );
    
    CHgScrollerWithTitle* scroler = CHgScrollerWithTitle::NewL( rect, item , 
                              CHgScrollerWithTitle::EHgScrollerDoubleGraphicList );
    CleanupStack::PushL( scroler );

    CHgScroller& temp = scroler->Scroller();
    TDummyObserver obs;
    temp.SetMarkingObserver(obs);
    
    CleanupStack::PopAndDestroy( scroler );
    
    return KErrNone;    
    }


