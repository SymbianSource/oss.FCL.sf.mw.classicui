/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/








#include <bctestmenu.rsg>
#include <w32std.h>
#include <coecntrl.h>
#include <eikmenub.h>
#include <barsread.h>
#include <eikmobs.h>
#include <aknenv.h>
#include <eikmenub.h>
#include <eikhkeyt.h>
#include <e32std.h>
#include <fbs.h>
#include <e32cmn.h>
#include <gdi.h>
#include <gulicon.h>
#include <coemain.h>
#include <akniconutils.h>
#include <eikbutb.h>

#include "bctestmenucase.h"
#include "bctestmenucontainer.h"
#include "bctestmenu.hrh"
#include "avkon.mbg"

// ========= LOCAL FUNCTIONS =======

static void CreateBitmapsL(CFbsBitmap** aBitmap, CFbsBitmap** aMask)
    {
    *aBitmap = AknIconUtils::CreateIconL( 
               AknIconUtils::AvkonIconFileName(), EMbmAvkonQgn_graf_tab_21 );
    *aMask = AknIconUtils::CreateIconL( 
                           AknIconUtils::AvkonIconFileName(), 
                           EMbmAvkonQgn_graf_tab_21_mask );
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMenuCase* CBCTestMenuCase::NewL( 
    CBCTestMenuContainer* aContainer )
    {
    CBCTestMenuCase* self = new( ELeave ) CBCTestMenuCase( 
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestMenuCase::CBCTestMenuCase( 
    CBCTestMenuContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMenuCase::~CBCTestMenuCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMenuCase::ConstructL()
    {    
    BuildScriptL();   
    iEikEnv = CEikonEnv::Static(); 
    }
    
// ---------------------------------------------------------------------------
// CBCTestMenuCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestMenuCase::BuildScriptL()
    { 
    // Add script as your need.  
    AddTestL( DELAY( 1 ),TEND );
    for( int i = 0; i <= 4; i++)
    {
    AddTestL( LeftCBA,TEND );
    AddTestL( REP( Down, i), KeyOK, TEND );
    }
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestMenuCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestMenuCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline6 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestEikMenuBarL();
            break;
        case EBCTestCmdOutline2:
            TestEikMenuBarTitleL();
            break;
        case EBCTestCmdOutline3:
            TestEikMenuPaneL();
            break;
        case EBCTestCmdOutline4:
            TestEikMenuPaneTitleL();
            break;
        case EBCTestCmdOutline5:
            TestEikMenuPaneItemL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestMenuCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestMenuCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control 
            // instead of this.
            iControl = new( ELeave ) CCoeControl();            
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControlL( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestMenuCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestMenuCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }


// ---------------------------------------------------------------------------
// Test Class CEikMenuBar
// ---------------------------------------------------------------------------
//     
void CBCTestMenuCase::TestEikMenuBarL()
    {
    iEikMenuBar = new ( ELeave )CEikMenuBar();
    _LIT( KCEikMenuBar, 
    "Class CEikMenuBar Function CEikMenuBar tested" );
    AssertTrueL( ETrue, KCEikMenuBar );
              
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    _LIT( KConstructL, 
    "Class CEikMenuBar Function ConstructL tested" );
    AssertTrueL( ETrue, KConstructL );
    
    TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader,
                               R_BCTESTMENU_MENUBAR_MAIN ); 
    iEikMenuBar->ConstructFromResourceL( resourceReader );
    _LIT( KConstructFromResourceL, 
    "Class CEikMenuBar Function ConstructFromResourceL tested" );
    AssertTrueL( ETrue, KConstructFromResourceL );
    
    CleanupStack::PopAndDestroy();//resourceReader
    
    iEikMenuBar->SetMenuTitleArray( iEikMenuBar->TitleArray() );
    _LIT( KSetMenuTitleArray, 
    "Class CEikMenuBar Function SetMenuTitleArray tested" );
    AssertTrueL( ETrue, KSetMenuTitleArray );
    
    iEikMenuBar->SetEditMenuObserver( fepMenuObserver );
    _LIT( KSetEditMenuObserver, 
    "Class CEikMenuBar Function SetEditMenuObserver tested" );
    AssertTrueL( ETrue, KSetEditMenuObserver );
    
    CEikHotKeyTable* hotKeyTable = new ( ELeave )CEikHotKeyTable();
    CleanupStack::PushL( hotKeyTable );
    iEikMenuBar->SetHotKeyTable( hotKeyTable );
    _LIT( KSetHotKeyTable, 
    "Class CEikMenuBar Function SetHotKeyTable tested" );
    AssertTrueL( ETrue, KSetHotKeyTable );
    CleanupStack::PopAndDestroy( hotKeyTable );
    
    CEikMenuBar::SCursor cursor;
    cursor.iMenuItemIndex = 1;
    cursor.iMenuPaneIndex = 1;
    iEikMenuBar->SetMenuCursor( cursor );
    _LIT( KSetMenuCursor, 
    "Class CEikMenuBar Function SetMenuCursor tested" );
    AssertTrueL( ETrue, KSetMenuCursor );
    
    iEikMenuBar->HandleResourceChange( 1 );
    _LIT( KHandleResourceChange, 
    "Class CEikMenuBar Function HandleResourceChange tested" );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    iEikMenuBar->SetMenuTitleResourceId( R_BCTESTMENU_MENUBAR_MAIN );
    _LIT( KSetMenuTitleResourceId, 
    "Class CEikMenuBar Function SetMenuTitleResourceId tested" );
    AssertTrueL( ETrue, KSetMenuTitleResourceId );
    
    iEikMenuBar->ChangeMenuBarL( 0, 1, ETrue );
    _LIT( KChangeMenuBarL, 
    "Class CEikMenuBar Function ChangeMenuBarL tested" );
    AssertTrueL( ETrue, KChangeMenuBarL );
    
    iEikMenuBar->SetTitleArrayOwnedExternally( ETrue );
    _LIT( KSetTitleArrayOwnedExternally, 
    "Class CEikMenuBar Function SetTitleArrayOwnedExternally tested" );
    AssertTrueL( ETrue, KSetTitleArrayOwnedExternally );
    
    iEikMenuBar->TitleArray();
    _LIT( KTitleArray, 
    "Class CEikMenuBar Function TitleArray tested" );
    AssertTrueL( ETrue, KTitleArray );
    
    iEikMenuBar->MenuPane();
    _LIT( KMenuPane, 
    "Class CEikMenuBar Function MenuPane tested" );
    AssertTrueL( ETrue, KMenuPane );
    
    iEikMenuBar->IsDisplayed();
    _LIT( KIsDisplayed, 
    "Class CEikMenuBar Function IsDisplayed tested" );
    AssertTrueL( ETrue, KIsDisplayed );
    
    iEikMenuBar->SelectedTitle();
    _LIT( KSelectedTitle, 
    "Class CEikMenuBar Function SelectedTitle tested" );
    AssertTrueL( ETrue, KSelectedTitle );
    
    iEikMenuBar->SelectedItem();
    _LIT( KSelectedItem, 
    "Class CEikMenuBar Function SelectedItem tested" );
    AssertTrueL( ETrue, KSelectedItem );
    
    iEikMenuBar->DrawItem( 1 );
    _LIT( KDrawItem, 
    "Class CEikMenuBar Function DrawItem tested" );
    AssertTrueL( ETrue, KDrawItem );
    
    iEikMenuBar->TryDisplayMenuBarWithoutFepMenusL();
    _LIT( KTryDisplayMenuBarWithoutFepMenusL, 
    "Class CEikMenuBar Function TryDisplayMenuBarWithoutFepMenusL tested" );
    AssertTrueL( ETrue, KTryDisplayMenuBarWithoutFepMenusL );
    
    iEikMenuBar->MoveHighlightToL( 1, 0 );
    _LIT( KMoveHighlightToL, 
    "Class CEikMenuBar Function MoveHighlightToL tested" );
    AssertTrueL( ETrue, KMoveHighlightToL );
    
    iEikMenuBar->StopDisplayingMenuBar();
    _LIT( KStopDisplayingMenuBar, 
    "Class CEikMenuBar Function StopDisplayingMenuBar tested" );
    AssertTrueL( ETrue, KStopDisplayingMenuBar );
    
    TInt paneindex;
    TInt itemindex;
    iEikMenuBar->FindCommandIdInResourceL( 1, paneindex, itemindex );
    _LIT( KFindCommandIdInResourceL, 
    "Class CEikMenuBar Function FindCommandIdInResourceL tested" );
    AssertTrueL( ETrue, KFindCommandIdInResourceL );
    
    TRect rect( 1, 1, 5, 5 );
    iEikMenuBar->ReduceRect( rect );
    _LIT( KReduceRect, 
    "Class CEikMenuBar Function ReduceRect tested" );
    AssertTrueL( ETrue, KReduceRect );
    
    iEikMenuBar->Draw( rect );
    _LIT( KDraw, 
    "Class CEikMenuBar Function Draw tested" );
    AssertTrueL( ETrue, KDraw );
    
    iEikMenuBar->RemoveEditMenuObserver( fepMenuObserver );
    _LIT( KRemoveEditMenuObserver, 
    "Class CEikMenuBar Function RemoveEditMenuObserver tested" );
    AssertTrueL( ETrue, KRemoveEditMenuObserver );
    
    CArrayFix<TCoeColorUse>* indexArray = new ( ELeave ) 
                                    CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( indexArray );
    iEikMenuBar->GetColorUseListL( *indexArray ) ;
    _LIT( KGetColorUseListL, 
    "Class CEikMenuBar Function GetColorUseListL tested" );
    AssertTrueL( ETrue, KGetColorUseListL );
    
    CleanupStack::PopAndDestroy( indexArray );
    
    TKeyEvent keyEvent;
    TPointerEvent pointerEvent;
    iEikMenuBar->OfferKeyEventL( keyEvent, EEventKey);
    _LIT( KOfferKeyEventL, 
    "Class CEikMenuBar Function OfferKeyEventL tested" );
    AssertTrueL( ETrue, KOfferKeyEventL );

    iEikMenuBar->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL, 
    "Class CEikMenuBar Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KHandlePointerEventL );
    
    delete iEikMenuBar;
    iEikMenuBar = NULL;
    }

// ---------------------------------------------------------------------------
// Test Class CEikMenuBarTitle
// ---------------------------------------------------------------------------
//     
void CBCTestMenuCase::TestEikMenuBarTitleL()
    {
    iEikMenuBarTitle = new ( ELeave )CEikMenuBarTitle();
    _LIT( KCEikMenuBarTitle, 
    "Class CEikMenuBarTitle Function CEikMenuBarTitle tested" );
    AssertTrueL( ETrue, KCEikMenuBarTitle );
    
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    iEikMenuBarTitle->CreateIconL( fbsBitmap, fbsMask );    //take the owner ship of args
    _LIT( KCreateIconL, 
    "Class CEikMenuBarTitle Function CreateIconL tested" );
    AssertTrueL( ETrue, KCreateIconL );
 
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    
    CGulIcon* gulIcon = CGulIcon::NewL( fbsBitmap, fbsMask );
    CleanupStack::PushL( gulIcon );
    iEikMenuBarTitle->SetIcon( gulIcon );
    _LIT( KSetIcon, 
    "Class CEikMenuBarTitle Function SetIcon tested" );
    AssertTrueL( ETrue, KSetIcon );
    
    iEikMenuBarTitle->SetBitmapsOwnedExternally( ETrue );
    _LIT( KSetBitmapsOwnedExternally, 
    "Class CEikMenuBarTitle Function SetBitmapsOwnedExternally tested" );
    AssertTrueL( ETrue, KSetBitmapsOwnedExternally );
    
    iEikMenuBarTitle->SetIconBitmapL( fbsBitmap );
    _LIT( KSetIconBitmapL, 
    "Class CEikMenuBarTitle Function SetIconBitmapL tested" );
    AssertTrueL( ETrue, KSetIconBitmapL );
    
    iEikMenuBarTitle->SetIconMaskL( fbsMask );
    _LIT( KSetIconMaskL, 
    "Class CEikMenuBarTitle Function SetIconMaskL tested" );
    AssertTrueL( ETrue, KSetIconMaskL );
    
    iEikMenuBarTitle->IconMask();
    _LIT( KIconMask, 
    "Class CEikMenuBarTitle Function IconMask tested" );
    AssertTrueL( ETrue, KIconMask );
    
    iEikMenuBarTitle->IconBitmap();
    _LIT( KIconBitmap, 
    "Class CEikMenuBarTitle Function IconBitmap tested" );
    AssertTrueL( ETrue, KIconBitmap );
    
        
    CWindowGc& gc = iContainer->SystemGc();
    TSize tmpsize( 10,10 );
    TRect tmprect( 0, 0, 10, 10 );
    iContainer->ActivateGc();
    iEikMenuBarTitle->DrawIcon( gc, tmprect, 10 );
    iContainer->DeactivateGc();
    _LIT( KDrawIcon, 
    "Class CEikMenuBarTitle Function DrawIcon tested" );
    AssertTrueL( ETrue, KDrawIcon );
    
    CleanupStack::Pop( gulIcon );
    CleanupStack::PopAndDestroy( fbsMask );
    CleanupStack::PopAndDestroy( fbsBitmap );
    
    delete iEikMenuBarTitle;
    iEikMenuBarTitle = NULL;
    }

void CBCTestMenuCase::CreateMenuPaneL()
    {
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuPane = new( ELeave )CEikMenuPane( fepMenuObserver );
    _LIT( KCEikMenuPane, 
        "Class CEikMenuPane Function CEikMenuPane tested" );
    AssertTrueL( ETrue, KCEikMenuPane );
    
    iEikMenuPane->ConstructL( iEikMenuPane, fepMenuObserver );
    _LIT( KConstructL, 
        "Class CEikMenuPane Function ConstructL tested" );
    AssertTrueL( ETrue, KConstructL );
    }

void CBCTestMenuCase::DestroyMenuPaneL()
    {
    iEikMenuPane->Reset();
    _LIT( KReset, "Class CEikMenuPane Function Reset tested" );
    AssertTrueL( ETrue, KReset );
    
    delete iEikMenuPane;
    iEikMenuPane=NULL;
    }

// ---------------------------------------------------------------------------
// Test Class CEikMenuPane
// ---------------------------------------------------------------------------
//        
void CBCTestMenuCase::TestEikMenuPaneL()
    {
    CEikMenuPaneItem::SData item;
    
    _LIT( Kformat,"New Item" );
    item.iCommandId = EProgCmdAutoTest;
    item.iFlags = 0;
    item.iCascadeId = 0;
    item.iText = Kformat;

    //[Section 1]
    //---------------------------------------------------------
    CreateMenuPaneL();

    iEikMenuPane->SetItemArrayOwnedExternally( EFalse );

    CEikMenuPane::CItemArray* itemArray = new ( ELeave )CEikMenuPane::CItemArray();
    CleanupStack::PushL( itemArray );
    
    // add stuffs.
    CEikMenuPaneItem* pItem = new (ELeave) CEikMenuPaneItem();
    pItem->iData = item;
    itemArray->AddItemL(pItem);
    CleanupStack::Pop();    //itemArray
    iEikMenuPane->SetItemArray( itemArray );   //transfer ownership of aItemArray
    _LIT( KSetItemArray, 
        "Class CEikMenuPane Function SetItemArray tested" );
    AssertTrueL( ETrue, KSetItemArray );

    DestroyMenuPaneL();

    //[Section 2]
    //-----------------------------------------------------
    CreateMenuPaneL();
    // 1st ver.
    iEikMenuPane->AddMenuItemL( item );
    _LIT( KAddMenuItemL, 
        "Class CEikMenuPane Function AddMenuItemL tested" );
    AssertTrueL( ETrue, KAddMenuItemL );

    // 2nd ver.
    _LIT( KItemText, "New Item 2" );
    item.iText = KItemText;
    iEikMenuPane->AddMenuItemL( item, EProgCmdAutoTest );
    AssertTrueL( ETrue, KAddMenuItemL );

    iEikMenuPane->InsertMenuItemL( item, 1 );
    _LIT( KInsertMenuItemL, 
    "Class CEikMenuPane Function InsertMenuItemL tested" );
    AssertTrueL( ETrue, KInsertMenuItemL );
    
    iEikMenuPane->SetArrowHeadScrollBar( ETrue );
    _LIT( KSetArrowHeadScrollBar, 
    "Class CEikMenuPane Function SetArrowHeadScrollBar tested" );
    AssertTrueL( ETrue, KSetArrowHeadScrollBar );
    
    iEikMenuPane->SetItemArrayOwnedExternally( ETrue );
    _LIT( KSetItemArrayOwnedExternally, 
        "Class CEikMenuPane Function SetItemArrayOwnedExternally tested" );
    AssertTrueL( ETrue, KSetItemArrayOwnedExternally );
    
    iEikMenuPane->SetItemButtonState( EProgCmdAutoTest, 1 );
    _LIT( KSetItemButtonState, 
    "Class CEikMenuPane Function SetItemButtonState tested" );
    AssertTrueL( ETrue, KSetItemButtonState );

    iEikMenuPane->SetItemDimmed( EProgCmdAutoTest, ETrue );
    _LIT( KSetItemDimmed, 
        "Class CEikMenuPane Function SetItemDimmed tested" );
    AssertTrueL( ETrue, KSetItemDimmed );
    
    iEikMenuPane->SetItemTextL( EProgCmdAutoTest, 10 );
    _LIT( KSetItemTextL, 
    "Class CEikMenuPane Function SetItemTextL tested" );
    AssertTrueL( ETrue, KSetItemTextL );
   
    iEikMenuPane->ItemDataByIndexL( 0 );
    _LIT( KItemDataByIndexL, 
    "Class CEikMenuPane Function ItemDataByIndexL tested" );
    AssertTrueL( ETrue, KItemDataByIndexL );
   
    _LIT( str, " ");
    TDesC16 tmp = str;
    iEikMenuPane->SetItemTextL( EProgCmdAutoTest, tmp );
    AssertTrueL( ETrue, KSetItemTextL );
    
    CEikButtonBase* eikButtonBase = new ( ELeave )CEikButtonBase();
    CleanupStack::PushL( eikButtonBase );
    iEikMenuPane->SetLaunchingButton( eikButtonBase );
    _LIT( KSetLaunchingButton, 
    "Class CEikMenuPane Function SetLaunchingButton tested" );
    AssertTrueL( ETrue, KSetLaunchingButton );
    
    iEikMenuPane->MoveHighlightTo( 0 );
    _LIT( KMoveHighlightTo, 
    "Class CEikMenuPane Function MoveHighlightTo tested" );
    AssertTrueL( ETrue, KMoveHighlightTo );
     
    iEikMenuPane->SetScrollBarOnLeft( ETrue );
    _LIT( KSetScrollBarOnLeft, 
    "Class CEikMenuPane Function SetScrollBarOnLeft tested" );
    AssertTrueL( ETrue, KSetScrollBarOnLeft );
    
    TInt tmpInt;
    iEikMenuPane->MenuItemExists( EProgCmdAutoTest, tmpInt );
    _LIT( KMenuItemExists, 
    "Class CEikMenuPane Function MenuItemExists tested" );
    AssertTrueL( ETrue, KMenuItemExists );
    
    CArrayFix<TCoeColorUse>* indexArray = new ( ELeave ) 
                                        CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( indexArray );
    iEikMenuPane->GetColorUseListL( *indexArray ) ;
    _LIT( KGetColorUseListL, 
    "Class CEikMenuPane Function GetColorUseListL tested" );
    AssertTrueL( ETrue, KGetColorUseListL );
    
    CleanupStack::PopAndDestroy( indexArray );
    
    iEikMenuPane->SetSelectedItem( 0 );
    _LIT( KSetSelectedItem, 
    "Class CEikMenuPane Function SetSelectedItem tested" );
    AssertTrueL( ETrue, KSetSelectedItem );
    
    iEikMenuPane->NavigateToNextItem();
    _LIT( KNavigateToNextItem, 
    "Class CEikMenuPane Function NavigateToNextItem tested" );
    AssertTrueL( ETrue, KNavigateToNextItem );
    
    iEikMenuPane->EnableMarqueeL( ETrue );
    _LIT( KEnableMarqueeL, 
    "Class CEikMenuPane Function EnableMarqueeL tested" );
    AssertTrueL( ETrue, KEnableMarqueeL );
    
    iEikMenuPane->InputCapabilities();
    _LIT( KInputCapabilities, 
    "Class CEikMenuPane Function InputCapabilities tested" );
    AssertTrueL( ETrue, KInputCapabilities );
    
    TPointerEvent pointerEvent;
    iEikMenuPane->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL, 
    "Class CEikMenuPane Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KHandlePointerEventL );
    
    iEikMenuPane->HandleResourceChange( 0 );
    _LIT( KHandleResourceChange, 
    "Class CEikMenuPane Function HandleResourceChange tested" );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    TFileName specialChars;
    iEikMenuPane->ConstructMenuSctRowL( specialChars );
    _LIT( KConstructMenuSctRowL, 
    "Class CEikMenuPane Function ConstructMenuSctRowL tested" );
    AssertTrueL( ETrue, KConstructMenuSctRowL );
    
    iEikMenuPane->DeleteBetweenMenuItems( 0, 1 );
    _LIT( KDeleteBetweenMenuItems, 
    "Class CEikMenuPane Function DeleteBetweenMenuItems tested" );
    AssertTrueL( ETrue, KDeleteBetweenMenuItems );
    
    DestroyMenuPaneL();
    CleanupStack::PopAndDestroy( eikButtonBase );    
    }

// ---------------------------------------------------------------------------
// Test Class CEikMenuPaneTitle
// ---------------------------------------------------------------------------
//     
void CBCTestMenuCase::TestEikMenuPaneTitleL()
    {    
    iEikMenuBar = new ( ELeave )CEikMenuBar();
                                                  
    MEikMenuObserver* fepMenuObserver = 
                      CAknEnv::Static()->FepMenuObserver();
    
    iEikMenuBar->ConstructL( fepMenuObserver, 0, 1 );
    TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader,
                               R_BCTESTMENU_MENUBAR_MAIN ); 
    iEikMenuBar->ConstructFromResourceL( resourceReader );
    CleanupStack::PopAndDestroy();//resourceReader
    
    iEikMenuPaneTitle = new ( ELeave )CEikMenuPaneTitle( iEikMenuBar );
    _LIT( KCEikMenuPaneTitle, 
    "Class CEikMenuPaneTitle Function CEikMenuPaneTitle tested" );
    AssertTrueL( ETrue, KCEikMenuPaneTitle );
    
    iEikMenuPaneTitle->ConstructL();
    _LIT( KConstructL, 
    "Class CEikMenuPaneTitle Function ConstructL tested" );
    AssertTrueL( ETrue, KConstructL );
    
    iEikMenuPaneTitle->SetSelectedTitle( 1 );
    _LIT( KSetSelectedTitle, 
    "Class CEikMenuPaneTitle Function SetSelectedTitle tested" );
    AssertTrueL( ETrue, KSetSelectedTitle );
    
    iEikMenuPaneTitle->Margins();
    _LIT( KMargins, 
    "Class CEikMenuPaneTitle Function Margins tested" );
    AssertTrueL( ETrue, KMargins );
    
    CArrayFix<TCoeColorUse>* indexArray = new ( ELeave ) 
                                       CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( indexArray );
    iEikMenuPaneTitle->GetColorUseListL( *indexArray );
    _LIT( KGetColorUseListL, 
    "Class CEikMenuPaneTitle Function GetColorUseListL tested" );
    AssertTrueL( ETrue, KGetColorUseListL );
    CleanupStack::PopAndDestroy( indexArray );
    
    TPointerEvent pointerEvent;
    iEikMenuPaneTitle->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL, 
    "Class CEikMenuPaneTitle Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KHandlePointerEventL );
    
    iEikMenuPaneTitle->HandleResourceChange( 0 );
    _LIT( KHandleResourceChange, 
    "Class CEikMenuPaneTitle Function HandleResourceChange tested" );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    TRect tmprect( 1, 1, 5, 5 );
    iEikMenuPaneTitle->Draw( tmprect );
    _LIT( KDraw, 
    "Class CEikMenuPaneTitle Function Draw tested" );
    AssertTrueL( ETrue, KDraw );
    
    iEikMenuPaneTitle->Close();
    _LIT( KClose, 
    "Class CEikMenuPaneTitle Function Close tested" );
    AssertTrueL( ETrue, KClose );
    
    delete iEikMenuBar;
    iEikMenuBar = NULL;
    delete iEikMenuPaneTitle;
    iEikMenuPaneTitle = NULL;
    }

// ---------------------------------------------------------------------------
// Test Class CEikMenuPaneItem
// ---------------------------------------------------------------------------
//     
void CBCTestMenuCase::TestEikMenuPaneItemL()
    { 
    iEikMenuPaneItem = new ( ELeave )CEikMenuPaneItem();
    _LIT( KCEikMenuPaneItem, 
    "Class CEikMenuPaneItem Function CEikMenuPaneItem tested" );
    AssertTrueL( ETrue, KCEikMenuPaneItem );
        
    CFbsBitmap *fbsBitmap( 0 ), *fbsMask( 0 );
    CreateBitmapsL( &fbsBitmap, &fbsMask );
 
    iEikMenuPaneItem->CreateIconL( fbsBitmap, fbsMask ); //take the ownership of bitmap and mask

    _LIT( KCreateIconL, 
    "Class CEikMenuPaneItem Function CreateIconL tested" );
    AssertTrueL( ETrue, KCreateIconL );
    
    CreateBitmapsL( &fbsBitmap, &fbsMask );
    CleanupStack::PushL( fbsBitmap );
    CleanupStack::PushL( fbsMask );
    
    CGulIcon* gulIcon = CGulIcon::NewL( fbsBitmap, fbsMask );
    CleanupStack::PushL( gulIcon );
    iEikMenuPaneItem->SetIcon( gulIcon );
    _LIT( KSetIcon, 
    "Class CEikMenuPaneItem Function SetIcon tested" );
    AssertTrueL( ETrue, KSetIcon );
    
    _LIT( str, " ");
    TDesC16 tmp = str;
    iEikMenuPaneItem->SetScaleableTextL( tmp );
    _LIT( KSetScaleableTextL, 
    "Class CEikMenuPaneItem Function SetScaleableTextL tested" );
    AssertTrueL( ETrue, KSetScaleableTextL );
    
    iEikMenuPaneItem->ScaleableText();
    _LIT( KScaleableTextL, 
    "Class CEikMenuPaneItem Function ScaleableText tested" );
    AssertTrueL( ETrue, KScaleableTextL );
   
    iEikMenuPaneItem->SetBitmapsOwnedExternally( ETrue );
    _LIT( KSetBitmapsOwnedExternally, 
    "Class CEikMenuPaneItem Function SetBitmapsOwnedExternally tested" );
    AssertTrueL( ETrue, KSetBitmapsOwnedExternally );
   
    iEikMenuPaneItem->SetIconBitmapL( fbsBitmap );
    _LIT( KSetIconBitmapL, 
    "Class CEikMenuPaneItem Function SetIconBitmapL tested" );
    AssertTrueL( ETrue, KSetIconBitmapL );
   
    iEikMenuPaneItem->SetIconMaskL( fbsMask );
    _LIT( KSetIconMaskL, 
    "Class CEikMenuPaneItem Function SetIconMaskL tested" );
    AssertTrueL( ETrue, KSetIconMaskL );
   
    iEikMenuPaneItem->IconMask();
    _LIT( KIconMask, 
    "Class CEikMenuPaneItem Function IconMask tested" );
    AssertTrueL( ETrue, KIconMask );
   
    iEikMenuPaneItem->IconBitmap();
    _LIT( KIconBitmap, 
    "Class CEikMenuPaneItem Function IconBitmap tested" );
    AssertTrueL( ETrue, KIconBitmap );

    //drawing
    CWindowGc& gc = iContainer->SystemGc();
    TSize tmpsize( 10, 10 );
    TRect tmprect( 0, 0, 100, 100 );
    iContainer->ActivateGc();
    iEikMenuPaneItem->DrawItemIcon( gc, tmprect, ETrue, 100 );
    iContainer->DeactivateGc();
    _LIT( KDrawItemIcon, 
    "Class CEikMenuPaneItem Function DrawItemIcon tested" );
    AssertTrueL( ETrue, KDrawItemIcon );
    
    CleanupStack::Pop( gulIcon );
    CleanupStack::PopAndDestroy( fbsMask );
    CleanupStack::PopAndDestroy( fbsBitmap );
    
    delete iEikMenuPaneItem;
    iEikMenuPaneItem = NULL;
    }

//end of file

