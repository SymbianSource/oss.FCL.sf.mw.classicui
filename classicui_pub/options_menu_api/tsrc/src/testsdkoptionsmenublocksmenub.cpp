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
* Description:  test options_menu_api
 *
*/

// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <e32const.h>
#include <fbs.h>
#include <akniconutils.h>
#include <gulicon.h>
#include <w32std.h>
#include <coecntrl.h>
#include <e32base.h>
#include <aiwserviceifbase.h>
#include <aiwserviceifmenu.h>
#include <aknenv.h>
#include <eikhkeyt.h>
#include <eikmobs.h>
#include <testsdkoptionsmenu.rsg>

#include "testsdkoptionsmenu.h"
#include "avkon.mbg"

// ============================ LOCAL FUNCTIONS ===============================

static void CreateBitmapsL(CFbsBitmap** aBitmap, CFbsBitmap** aMask)
    {
    *aBitmap = AknIconUtils::CreateIconL ( AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_graf_tab_21 );
    *aMask = AknIconUtils::CreateIconL ( AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_graf_tab_21_mask );
    }

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBCEikMenuBarTitleL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMBTCEikMenuBarTitleL( CStifItemParser& /*aItem*/ )
    {
    STIF_ASSERT_NOT_NULL( iEikMenuBarTitle );
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBTSetIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBTSetIconL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CGulIcon* gulIcon = CGulIcon::NewL( fbsBitmap, fbsMask );
    CleanupStack::PushL( gulIcon );
    iEikMenuBarTitle->SetIcon( gulIcon );
    CleanupStack::Pop( gulIcon );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBSetBitmapsOwnedExternallyL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMBTSetBitmapsOwnedExternallyL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    CGulIcon* gulIcon = CGulIcon::NewL( fbsBitmap, fbsMask );
    CleanupStack::PushL( gulIcon );
    iEikMenuBarTitle->SetIcon( gulIcon );	
    iEikMenuBarTitle->SetBitmapsOwnedExternally( ETrue );   
    STIF_ASSERT_NOT_NULL( gulIcon );
    CleanupStack::Pop( gulIcon );	
    CleanupStack::Pop( fbsMask );
    CleanupStack::Pop( fbsBitmap );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBDrawIconL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMBTDrawIconL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    iEikMenuBarTitle->SetIconBitmapL( fbsBitmap );
    iEikMenuBarTitle->SetIconMaskL( fbsMask );
    iEikMenuBarTitle->IconMask();
    iEikMenuBarTitle->IconBitmap();
    CWindowGc& gc = iContainer->SystemGc();
    TRect tmprect( 0, 0, 100, 100 );
    iContainer->ActivateGc();
    iEikMenuBarTitle->DrawIcon( gc, tmprect, 10 );
    iContainer->DeactivateGc();
    CleanupStack::Pop( fbsMask ); 
    CleanupStack::Pop( fbsBitmap ); 
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBCreateIconL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMBTCreateIconL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    iEikMenuBarTitle->CreateIconL( fbsBitmap, fbsMask );
    CleanupStack::Pop( fbsMask );
    CleanupStack::Pop( fbsBitmap );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBTSetIconBitmapL
// -----------------------------------------------------------------------------
//TestMBTSetIconBitmapL
TInt CTestSDKOptionsMenu::TestMBTSetIconBitmapL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    iEikMenuBarTitle->SetIconBitmapL( fbsBitmap );
    CleanupStack::Pop( fbsMask );
    CleanupStack::Pop( fbsBitmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBTSetIconMaskL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBTSetIconMaskL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    iEikMenuBarTitle->SetIconMaskL( fbsMask );
    CleanupStack::Pop( fbsMask );
    CleanupStack::Pop( fbsBitmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBTIconBitmapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBTIconBitmapL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    iEikMenuBarTitle->IconBitmap();
    CleanupStack::Pop( fbsMask );
    CleanupStack::Pop( fbsBitmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBTIconMaskL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBTIconMaskL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    iEikMenuBarTitle->IconMask();
    CleanupStack::Pop( fbsMask );
    CleanupStack::Pop( fbsBitmap );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBCEikMenuBarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBCEikMenuBarL( CStifItemParser& /*aItem*/ )
    {
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    TKeyEvent keyEvent;
    TPointerEvent pointerEvent;
    iEikMenuBar->OfferKeyEventL( keyEvent, EEventKey );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TPointerEvent pointerEvent;
    iEikMenuBar->HandlePointerEventL( pointerEvent );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBDraw
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBDraw( CStifItemParser& /*aItem*/ )
    {
    TRect rect( 1, 1, 5, 5 );
    iEikMenuBar->Draw( rect );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBCTitleArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBTACTitleArrayL( CStifItemParser& /*aItem*/ )
    {
    CEikMenuBar::CTitleArray* titleArray = new ( ELeave ) CEikMenuBar::CTitleArray();
    CleanupStack::PushL( titleArray );
    STIF_ASSERT_NOT_NULL( titleArray );
    CleanupStack::PopAndDestroy( titleArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBAddTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBTAAddTitleL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    CEikMenuBar::CTitleArray* titleArray = new ( ELeave ) CEikMenuBar::CTitleArray;
    CleanupStack::PushL( titleArray );
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    titleArray->AddTitleL( iEikMenuBarTitle );
    STIF_ASSERT_NOT_NULL( titleArray );
    CleanupStack::PopAndDestroy( titleArray );
    iEikMenuBarTitle = NULL;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBConstructL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    CleanupStack::PushL( fepMenuObserver );
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    CleanupStack::Pop();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikEnv = CEikonEnv::Static(); 
    TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader, R_MENUTESTMENU_MENUBAR_MAIN ); 
    iEikMenuBar->ConstructFromResourceL( resourceReader );
    CleanupStack::PopAndDestroy();
    fepMenuObserver = NULL;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBChangeMenuBarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBChangeMenuBarL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuBar->ChangeMenuBarL( 0, 1, ETrue );
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBSetHotKeyTableL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBSetHotKeyTableL( CStifItemParser& /*aItem*/ )
    {
    CEikHotKeyTable* hotKeyTable = new ( ELeave )CEikHotKeyTable();
    CleanupStack::PushL( hotKeyTable );
    iEikMenuBar->SetHotKeyTable( hotKeyTable );
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBSetMenuTitleResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBSetMenuTitleResourceIdL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuBar->SetMenuTitleResourceId( R_MENUTESTMENU_MENUBAR_MAIN );
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBSetContextMenuTitleResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBSetContextMenuTitleResourceIdL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->SetContextMenuTitleResourceId( R_MENUTESTMENU_MENUBAR_MAIN );
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBSetMenuTitleArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBSetMenuTitleArrayL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuBar->SetMenuTitleArray( iEikMenuBar->TitleArray() );
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBSetTitleArrayOwnedExternallyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBSetTitleArrayOwnedExternallyL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuBar->SetTitleArrayOwnedExternally( ETrue );
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBSetMenuCursorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBSetMenuCursorL( CStifItemParser& /*aItem*/ )
{
    CEikMenuBar::SCursor cursor;
    cursor.iMenuItemIndex = 1;
    cursor.iMenuPaneIndex = 1;
    iEikMenuBar->SetMenuCursor( cursor );
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBStopDisplayingMenuBarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBStopDisplayingMenuBarL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->StopDisplayingMenuBar();
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBTryDisplayMenuBarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBTryDisplayMenuBarL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->SetMenuTitleResourceId( R_MENUTESTMENU_MENUBAR_MAIN );
    iEikMenuBar->TryDisplayMenuBarL();
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBTryDisplayContextMenuBarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBTryDisplayContextMenuBarL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->TryDisplayContextMenuBarL();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBTryDisplayMenuBarWithoutFepMenusL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBTryDisplayMenuBarWithoutFepMenusL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->SetMenuTitleResourceId( R_MENUTESTMENU_MENUBAR_MAIN );
    iEikMenuBar->TryDisplayMenuBarWithoutFepMenusL();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBMoveHighlightToL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBMoveHighlightToL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->MoveHighlightToL( 1, 0 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBDrawItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBDrawItemL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuBar->DrawItem( 1 );
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBSelectedTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBSelectedTitleL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuBar->SelectedTitle();
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBSelectedItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBSelectedItemL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuBar->SelectedItem();
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBFindCommandIdInResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBFindCommandIdInResourceL( CStifItemParser& /*aItem*/ )
    {
    TInt paneindex;
    TInt itemindex;    
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->FindCommandIdInResourceL( 1, paneindex, itemindex );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBMenuPaneL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->SetEditMenuObserver( fepMenuObserver );
    iEikMenuBar->MenuPane();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBReduceRectL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    TRect rect( 1, 1, 5, 5 );
    iEikMenuBar->ReduceRect( rect );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBTitleArrayL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->SetMenuTitleArray( iEikMenuBar->TitleArray() );
    iEikMenuBar->TitleArray();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBSetEditMenuObserverL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->SetEditMenuObserver( fepMenuObserver );
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBRemoveEditMenuObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBRemoveEditMenuObserverL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->RemoveEditMenuObserver( fepMenuObserver );
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBRemoveEditMenuObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBIsDisplayedL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->IsDisplayed();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBSetMenuTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBSetMenuTypeL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->SetMenuType( CEikMenuBar::EMenuContext );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBSetMenuTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CArrayFix<TCoeColorUse>* indexArray = new ( ELeave )
                                               CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( indexArray );
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikMenuBar->GetColorUseListL( *indexArray ) ;
    CleanupStack::PopAndDestroy( indexArray );//������֤!!!
    return KErrNone;
    }
    
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMBHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL(fepMenuObserver, 0, 1);
    iEikMenuBar->HandleResourceChange( 1);
    STIF_ASSERT_NOT_NULL( iEikMenuBar );
    return KErrNone;
    }
    

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPTCEikMenuPaneTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPTCEikMenuPaneTitleL( CStifItemParser& /*aItem*/ )
    {
    STIF_ASSERT_NOT_NULL( iEikMenuPaneTitle );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPTConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPTConstructL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuPaneTitle->ConstructL();
    STIF_ASSERT_NOT_NULL( iEikMenuPaneTitle );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPTSetSelectedTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPTSetSelectedTitleL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuPaneTitle->ConstructL();
    iEikMenuPaneTitle->SetSelectedTitle( 1 );
    STIF_ASSERT_NOT_NULL( iEikMenuPaneTitle );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPTDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPTDrawL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuPaneTitle->ConstructL();
    TRect tmprect( 1, 1, 5, 5 );
    iEikMenuPaneTitle->Draw( tmprect );
    STIF_ASSERT_NOT_NULL( iEikMenuPaneTitle );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPTMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPTMarginsL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuPaneTitle->ConstructL();
    iEikMenuPaneTitle->Margins();
    STIF_ASSERT_NOT_NULL( iEikMenuPaneTitle );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPTCloseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPTCloseL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuPaneTitle->ConstructL();
    iEikMenuPaneTitle->Close();
    STIF_ASSERT_NOT_NULL( iEikMenuPaneTitle );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPTHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPTHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuPaneTitle->ConstructL();
    TPointerEvent pointerEvent;
    iEikMenuPaneTitle->HandlePointerEventL( pointerEvent );
    STIF_ASSERT_NOT_NULL( iEikMenuPaneTitle );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPTGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPTGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuPaneTitle->ConstructL();
    CArrayFix<TCoeColorUse>* indexArray = new ( ELeave ) 
                                        CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( indexArray );
    iEikMenuPaneTitle->GetColorUseListL( *indexArray ) ;
    STIF_ASSERT_NOT_NULL( iEikMenuPaneTitle );
    CleanupStack::PopAndDestroy( indexArray );//!!!
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPTHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPTHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuPaneTitle->ConstructL();
    iEikMenuPaneTitle->HandleResourceChange( 1 ) ;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMBItemSpecificCommandsEnabled
// -----------------------------------------------------------------------------
//
TInt 
CTestSDKOptionsMenu::TestMBItemSpecificCommandsEnabled(CStifItemParser& /*aItem*/)
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, R_MENUTESTMENU_MENUBAR_MAIN );   
    iEikMenuBar->ItemSpecificCommandsEnabled();
    return KErrNone;    
    }
//  [End of File]
