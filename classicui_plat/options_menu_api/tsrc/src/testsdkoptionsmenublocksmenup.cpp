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
#include <coemain.h>
#include <eikbutb.h> 
#include <testsdkoptionsmenu.rsg>
#include <avkon.hrh>
#include <avkon.rsg>
#include <avkon.mbg>

#include "testsdkoptionsmenu.hrh"
#include "testsdkoptionsmenu.h"
#include "testsdkoptionsmenucontainer.h"
#include "testoptionsmenu.h"


// CONSTANTS
_LIT( KString, "test item");
_LIT( KTestitem,"New Item" );


class CEikMenuPaneExtension ;

// ============================ LOCAL FUNCTIONS ===============================

static void CreateBitmapsL( CFbsBitmap** aBitmap, CFbsBitmap** aMask )
    {
    *aBitmap = AknIconUtils::CreateIconL ( AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_graf_tab_21 );
    *aMask = AknIconUtils::CreateIconL ( AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_graf_tab_21_mask );
    }

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPICEikMenuPaneItemL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPICEikMenuPaneItemL( CStifItemParser& /*aItem*/ )
    {
    STIF_ASSERT_NOT_NULL( iEikMenuPaneItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPISetIconL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPISetIconL( CStifItemParser& /*aItem*/ )
    {

    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    CGulIcon* gulIcon = CGulIcon::NewL( fbsBitmap, fbsMask );
    CleanupStack::PushL( gulIcon );
    iEikMenuPaneItem->SetIcon( gulIcon );
    CleanupStack::Pop( 3 );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPIDrawItemIcon
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPIDrawItemIcon( CStifItemParser& /*aItem*/ )
    {
    CWindowGc& gc = iContainer->SystemGc();
    TSize tmpsize( 10, 10 );
    TRect tmprect( 0, 0, 100, 100 );
    iEikMenuPaneItem->DrawItemIcon( gc, tmprect, ETrue, 100 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPICreateIconL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPICreateIconL(CStifItemParser& /*aItem*/)
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    iEikMenuPaneItem->CreateIconL( fbsBitmap, fbsMask ); //take the ownership of bitmap and mask
    CleanupStack::Pop( fbsMask );
    CleanupStack::Pop( fbsBitmap );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPIIconBitmap
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPIIconBitmap( CStifItemParser& /*aItem*/ )
    {
    iEikMenuPaneItem->IconBitmap();   
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPIIconMask
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPIIconMask( CStifItemParser& /*aItem*/ )
    {
    iEikMenuPaneItem->IconMask();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPISetBitmapsOwnedExternallyL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPISetBitmapsOwnedExternallyL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    CGulIcon* gulIcon = CGulIcon::NewL( fbsBitmap, fbsMask );
    CleanupStack::PushL(gulIcon);
    iEikMenuPaneItem->SetIcon( gulIcon );   
    iEikMenuPaneItem->SetBitmapsOwnedExternally( ETrue );
    STIF_ASSERT_NOT_NULL( iEikMenuPaneItem );
    CleanupStack::Pop( 3 );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPISetIconBitmapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPISetIconBitmapL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::Pop( fbsBitmap );
    CleanupStack::PopAndDestroy( fbsMask );
    iEikMenuPaneItem->SetIconBitmapL( fbsBitmap ); 
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPISetIconMaskL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPISetIconMaskL( CStifItemParser& /*aItem*/ )
    {
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsMask );
    CleanupStack::PushL( fbsBitmap );
    iEikMenuPaneItem->SetIconMaskL( fbsMask ); 
    CleanupStack::Pop( fbsBitmap );
    CleanupStack::Pop( fbsMask );

    return KErrNone;
    }

//
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPIScaleableTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPIScaleableTextL( CStifItemParser& /*aItem*/ )
    {
    iEikMenuPaneItem->ScaleableText();
    STIF_ASSERT_NOT_NULL( iEikMenuPaneItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPISetScaleableTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPISetScaleableTextL( CStifItemParser& /*aItem*/ )
    {
    TDesC16 tmp = KString;
    iEikMenuPaneItem->SetScaleableTextL( tmp );
    STIF_ASSERT_NOT_NULL( iEikMenuPaneItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPIACItemArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPIACItemArrayL( CStifItemParser& /*aItem*/ )
    {
    CEikMenuPane::CItemArray* itemArray = new ( ELeave )CEikMenuPane::CItemArray();
    CleanupStack::PushL( itemArray );
    STIF_ASSERT_NOT_NULL( itemArray );
    CleanupStack::PopAndDestroy( itemArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPIAAddItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPIAAddItemL( CStifItemParser& /*aItem*/ )
    {
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    CEikMenuPane::CItemArray* itemArray = new ( ELeave )CEikMenuPane::CItemArray();
    CleanupStack::PushL( itemArray );
    iEikMenuPaneItem->iData = item;
    itemArray->AddItemL( iEikMenuPaneItem );
    CleanupStack::PopAndDestroy( itemArray );
    iEikMenuPaneItem = NULL;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPCEikMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPCEikMenuPaneL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }
    
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPConstructL( CStifItemParser& /*aItem*/)
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->ConstructL( menuPane, fepMenuObserver );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPResetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPResetL( CStifItemParser& /*aItem*/)
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->Reset();
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    TKeyEvent keyEvent;
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->ConstructL( menuPane, fepMenuObserver );
    menuPane->OfferKeyEventL( keyEvent, EEventKey );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TPointerEvent pointerEvent;
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->ConstructL( menuPane, fepMenuObserver );
    menuPane->HandlePointerEventL( pointerEvent );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CArrayFix<TCoeColorUse>* fixindexArray = new ( ELeave ) 
                                           CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( fixindexArray );
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new ( ELeave ) CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->ConstructL( menuPane, fepMenuObserver );
    menuPane->GetColorUseListL( *fixindexArray );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new ( ELeave ) CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->ConstructL( menuPane, fepMenuObserver );
    menuPane->HandleResourceChange( 0 );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->ConstructL( menuPane, fepMenuObserver );
    menuPane->InputCapabilities();
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPDrawL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CTestOptionsMenu* testoptionsmenu=new( ELeave )CTestOptionsMenu( fepMenuObserver );
    CleanupStack::PushL( testoptionsmenu );
    testoptionsmenu->ConstructL( testoptionsmenu,fepMenuObserver );
    testoptionsmenu->DoActivateGc();
    TRect tmprect( 1, 1, 5, 5 );
    testoptionsmenu->DoDraw( tmprect );
    testoptionsmenu->DoDeactivateGc();
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CTestOptionsMenu* testoptionsmenu=new( ELeave )CTestOptionsMenu( fepMenuObserver );
    CleanupStack::PushL( testoptionsmenu );
    testoptionsmenu->DoFocusChanged( ENoDrawNow );
    CleanupStack::PopAndDestroy( testoptionsmenu );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    iEikEnv = CEikonEnv::Static(); 
    TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader, R_MENUTESTMENU_CASE_MENU );
    CTestOptionsMenu* testoptionsmenu = new ( ELeave ) CTestOptionsMenu( fepMenuObserver );
    CleanupStack::PushL( testoptionsmenu );
    testoptionsmenu->DoConstructFromResourceL( resourceReader );
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPAddMenuItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPAddMenuItemL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPAddMenuItemIntL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPAddMenuItemIntL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new ( ELeave ) CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    CEikMenuPaneItem::SData item2;
    item.iCommandId = EProgCmdAutoTest2;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->InputCapabilities();
    menuPane->AddMenuItemL( item2 ,EProgCmdAutoTest );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPAddMenuItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPAddMenuItemsL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    CEikMenuPaneItem::SData item2;
    item2.iCommandId = EProgCmdAutoTest2;
    item2.iFlags = 0;
    item2.iCascadeId = 0;
    item2.iText = KTestitem;
    menuPane->AddMenuItemsL( R_MENUTESTMENU_MENU ,EProgCmdAutoTest,EFalse);
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPDeleteMenuItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPDeleteMenuItemL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->DeleteMenuItem( EProgCmdAutoTest );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPDeleteBetweenMenuItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPDeleteBetweenMenuItemsL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->AddMenuItemsL( R_MENUTESTMENU_MENU ,EProgCmdAutoTest,EFalse);
    menuPane->DeleteBetweenMenuItems( 0,1 );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPItemDataL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPItemDataL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->ItemData( EProgCmdAutoTest );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPItemAndPosL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPItemAndPosL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    TInt pos=1;
    menuPane->AddMenuItemL( item );
    menuPane->ItemData( EProgCmdAutoTest );
    menuPane->ItemAndPos( EProgCmdAutoTest ,pos );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }
 


// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPStartDisplayingMenuPaneL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPStartDisplayingMenuPaneL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikHotKeyTable* aHotKeyTable=new( ELeave )CEikHotKeyTable();
    CleanupStack::PushL( aHotKeyTable );
    TPoint pointerEvent;
    
    //menuPane->ConstructL( menuPane, fepMenuObserver );
    menuPane->ConstructL( NULL, fepMenuObserver );
    
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->StartDisplayingMenuPane( aHotKeyTable ,pointerEvent,iEikMenuPaneTitle,1 ,EPopupTargetTopLeft );
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPStartDisplayingMenuPaneL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPSetItemTextDesCL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    TDesC16 tmp = KString;
    menuPane->SetItemTextL( EProgCmdAutoTest, tmp );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPStartDisplayingMenuPaneL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPSetItemTextIntL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->SetItemTextL( EProgCmdAutoTest, 10 );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPSetItemDimmedL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPSetItemDimmedL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->SetItemDimmed( EProgCmdAutoTest, ETrue );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPSetItemButtonStateL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPSetItemButtonStateL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->ConstructL( menuPane, fepMenuObserver );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->SetItemButtonState( EProgCmdAutoTest, 1 );
    menuPane->SetItemDimmed( EProgCmdAutoTest, ETrue );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPSetSelectedItemL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPSetSelectedItemL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->SetSelectedItem( 0 );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPSelectedItemL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPSelectedItemL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->SelectedItem();
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPCloseCascadeMenuL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPCloseCascadeMenuL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->CloseCascadeMenu();
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPSetItemArrayL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPSetItemArrayL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    CEikMenuPane::CItemArray* itemArray = new ( ELeave )CEikMenuPane::CItemArray();
    CleanupStack::PushL( itemArray );
    CEikMenuPaneItem* pItem = new ( ELeave ) CEikMenuPaneItem();
    CleanupStack::PushL( pItem );
    pItem->iData = item;
    itemArray->AddItemL( pItem );
    menuPane->SetItemArray( itemArray );
    menuPane->SetItemArrayOwnedExternally( ETrue );
    CleanupStack::Pop( 2 );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPSetItemArrayOwnedExternallyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPSetItemArrayOwnedExternallyL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    CEikMenuPane::CItemArray* itemArray = new ( ELeave )CEikMenuPane::CItemArray();
    CleanupStack::PushL(itemArray);
    CEikMenuPaneItem* pItem = new ( ELeave ) CEikMenuPaneItem();
    CleanupStack::PushL( pItem );
    pItem->iData = item;
    itemArray->AddItemL( pItem );
    menuPane->SetItemArray( itemArray );
    menuPane->SetItemArrayOwnedExternally( ETrue );
    CleanupStack::Pop( 2 );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPSetLaunchingButtonL
// -----------------------------------------------------------------------------
//

TInt CTestSDKOptionsMenu::TestMPSetLaunchingButtonL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikButtonBase* eikButtonBase = new ( ELeave )CEikButtonBase();
    CleanupStack::PushL( eikButtonBase );
    menuPane->SetLaunchingButton( eikButtonBase );
    CleanupStack::Pop();
    CleanupStack::PopAndDestroy( menuPane );
    delete eikButtonBase;
    eikButtonBase = NULL;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPMoveHighlightToL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPMoveHighlightToL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->MoveHighlightTo( 0 );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPNumberOfItemsInPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPNumberOfItemsInPaneL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->NumberOfItemsInPane();
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPCloseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPCloseL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->Close();
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPOfferKeyEventBoolL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPOfferKeyEventBoolL( CStifItemParser& /*aItem*/ )
    {
    TKeyEvent keyEvent;
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->ConstructL( menuPane, fepMenuObserver );
    menuPane->OfferKeyEventL( keyEvent, EEventKey, ETrue );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPSetScrollBarOnLeftL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPSetScrollBarOnLeftL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->SetScrollBarOnLeft( ETrue );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::SetArrowHeadScrollBar
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPSetArrowHeadScrollBarL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->SetArrowHeadScrollBar( ETrue );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPNavigateToNextItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPNavigateToNextItemL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->NavigateToNextItem();
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPInsertMenuItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPInsertMenuItemL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->InsertMenuItemL( item,0 );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPMenuItemExistsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPMenuItemExistsL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    TInt tmpInt;
    menuPane->AddMenuItemL( item );
    menuPane->MenuItemExists( EProgCmdAutoTest, tmpInt );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPIsCascadeMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPIsCascadeMenuPaneL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->IsCascadeMenuPane();
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPCascadeMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPCascadeMenuPaneL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->CascadeMenuPane();
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPItemDataByIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPItemDataByIndexL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPaneItem* menupaneitem = new ( ELeave )CEikMenuPaneItem();
    CleanupStack::PushL( menupaneitem );
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    CEikMenuPane::CItemArray* itemArray = new ( ELeave )CEikMenuPane::CItemArray();
    CleanupStack::PushL( itemArray );
    iEikMenuPaneItem->iData = item;
    itemArray->AddItemL( iEikMenuPaneItem );
    menuPane->AddMenuItemL( item );
    menuPane->ItemData( EProgCmdAutoTest );
    menuPane->ItemDataByIndexL( 0 );
    CleanupStack::PopAndDestroy( 3 );
    iEikMenuPaneItem = NULL;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPEnableMarqueeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPEnableMarqueeL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->EnableMarqueeL( ETrue );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPConstructMenuSctRowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPConstructMenuSctRowL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    TFileName specialChars;
    menuPane->ConstructMenuSctRowL( specialChars );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy( menuPane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPMenuItemCommandIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPMenuItemCommandIdL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPaneItem* menupaneitem = new ( ELeave )CEikMenuPaneItem();
    CleanupStack::PushL( menupaneitem );
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    CEikMenuPane::CItemArray* itemArray = new ( ELeave )CEikMenuPane::CItemArray();
    CleanupStack::PushL( itemArray );
    iEikMenuPaneItem->iData = item;
    itemArray->AddItemL( iEikMenuPaneItem );
    menuPane->AddMenuItemL( item );
    menuPane->ItemData( EProgCmdAutoTest );
    menuPane->MenuItemCommandId( 0 );
    CleanupStack::PopAndDestroy( 3 );
    iEikMenuPaneItem = NULL;
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPConstructMenuSctRowIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPConstructMenuSctRowIdL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    TFileName specialChars;
    menuPane->ConstructL( menuPane, fepMenuObserver );
    menuPane->ConstructMenuSctRowL( specialChars );
    menuPane->ConstructMenuSctRowL( specialChars ,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPConstructMenuSctRowFromDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPConstructMenuSctRowFromDialogL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    TFileName specialChars;
    menuPane->ConstructMenuSctRowFromDialogL( specialChars ,R_AVKON_SPECIAL_CHARACTER_TABLE_DIALOG_CHINESE );
    menuPane->ConstructMenuSctRowFromDialogL( 0, specialChars ,R_AVKON_SPECIAL_CHARACTER_TABLE_DIALOG_CHINESE );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    CMenuObserver* observer = new( ELeave ) CMenuObserver;
    CleanupStack::PushL( observer );
    const TTypeUid KTestUid = 0x11111111;
    CTestOptionsMenuMop*testOptionsMenuMop=new( ELeave )CTestOptionsMenuMop ( observer );
    CleanupStack::PushL( testOptionsMenuMop );
    testOptionsMenuMop->DoMopSupplyObject( KTestUid );
    CleanupStack::PopAndDestroy( testOptionsMenuMop );
    CleanupStack::PopAndDestroy( observer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->ConstructL( menuPane, fepMenuObserver );
    menuPane->CountComponentControls();
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPComponentControlL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    menuPane->ConstructL( menuPane, fepMenuObserver );
    menuPane->ComponentControl( 0 );
    STIF_ASSERT_NOT_NULL( menuPane );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestMPSetItemSpecific
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::TestMPSetItemSpecific( CStifItemParser& /*aItem*/)
    {
    MEikMenuObserver* fepMenuObserver = CAknEnv::Static()->FepMenuObserver();
    CEikMenuPane *menuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    CleanupStack::PushL( menuPane );
    CEikMenuPaneItem::SData item;
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = KTestitem;
    menuPane->AddMenuItemL( item );
    menuPane->SetItemSpecific( EProgCmdAutoTest, EFalse );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

//End of file
