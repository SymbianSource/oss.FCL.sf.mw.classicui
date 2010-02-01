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
* Description:         test case for selection list dialog classes
*
*/









#include <w32std.h>
#include <eikenv.h>

#include "bctestlistselectioncase.h"
#include "bctestlistcontainer.h"
#include "bctestlist.hrh"
#include <bctestlist.rsg>
#include <bctestlist.mbg>

_LIT( KSelectNewL, "CAknSelectionListDialog::NewL" );
_LIT( KSelSetFind, "CAknMarkableListDialog::SetupFind" );
_LIT( KSelSetIconArray, "CAknSelectionListDialog::SetIconArrayL" );
_LIT( KSelHandleListEvent, "CAknSelectionListDialog::HandleListBoxEventL" );
_LIT( KSelSelListProcCmd, "CAknSelectionListDialog::SelectionListProcessCommandL" );
_LIT( KSelProcCmd, "CAknSelectionListDialog::ProcessCommandL" );
_LIT( KSelCustomCtrl, "CAknSelectionListDialog::CreateCustomControlL" );
_LIT( KSelDraw, "CAknSelectionListDialog::Draw" );

_LIT( KMarkedNewL, "CAknMarkableListDialog::NewL" );
_LIT( KSelHandlePointer, "CAknMarkableListDialog::HandlePointerEventL" );
_LIT( KSelPreLayout, "CAknMarkableListDialog::PreLayoutDynInitL" );
_LIT( KMarSelListProcCmd, "CAknMarkableListDialog::SelectionListProcessCommandL" );
_LIT( KMarPreProcCmd, "CAknMarkableListDialog::ProcessCommandL" );
_LIT( KSelDynMenPane, "CAknMarkableListDialog::DynInitMenuPaneL" );
_LIT( KMarHandleListEvent, "CAknMarkableListDialog::HandleListBoxEventL" );
_LIT( KMarOfferKey, "CAknMarkableListDialog::OfferKeyEventL" );
_LIT( KMarPostLayout, "CAknMarkableListDialog::PostLayoutDynInitL" );
_LIT( KMarOK, "CAknMarkableListDialog::OkToExitL" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListSelectionCase* CBCTestListSelectionCase::NewL( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    {
    CBCTestListSelectionCase* self = new( ELeave ) CBCTestListSelectionCase( 
        aContainer, aEikEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestListSelectionCase::CBCTestListSelectionCase( CBCTestListContainer* aContainer,
    CEikonEnv* aEikEnv )
    : CBCTestListBaseCase( aContainer, aEikEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListSelectionCase::~CBCTestListSelectionCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListSelectionCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListSelectionCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListSelectionCase::BuildScriptL()
    {    
    for ( TInt i=0; i <= EBCTestCmdOutline57 - EBCTestCmdOutline56; i++ )
        {
        AddTestL( LeftCBA, REP( Down, 9 ), KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }      
    }
    
// ---------------------------------------------------------------------------
// CBCTestListSelectionCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListSelectionCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline56 || aCmd > EBCTestCmdOutline57 )
        {
        return;
        }
    ReleaseCase();
    switch ( aCmd )  
        {
        case EBCTestCmdOutline56:
            TestMarkableListDialogL();       
            break;
        case EBCTestCmdOutline57:
            TestSelectionListDialogL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestListSelectionCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestListSelectionCase::ReleaseCase()
    {
    iContainer->ResetControl();    
    }

// ---------------------------------------------------------------------------
// Test CAknSelectionListDialog
// ---------------------------------------------------------------------------
//

void CBCTestListSelectionCase::TestSelectionListDialogL()
    {
    TInt value( -1 );    
    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );
    CDesCArray* textArray = NULL;   
    textArray = iEikEnv->ReadDesCArrayResourceL( R_BCTESTLIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );
    
    // test CAknSelectionListDialog::NewL
    CAknSelectionListDialog* selDlg = CAknSelectionListDialog::NewL(
        value, textArray, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( selDlg );    
    AssertNotNullL( selDlg, KSelectNewL );    
    CleanupStack::PopAndDestroy( selDlg );    
    
    // test API of CAknSelectionListDialog
    CBCSelectionListDialog* dlg = CBCSelectionListDialog::NewL( value, 
        textArray );    
    dlg->PrepareLC( R_BCTESTLIST_SINGLE_SELECTION_LIST_DIALOG );
    
    dlg->SetupFind( CAknSelectionListDialog::EFixedFind );    
    AssertTrueL( ETrue, KSelSetFind );
    
    CArrayPtr<CGulIcon>* icons = new( ELeave ) CArrayPtrFlat<CGulIcon>(
            KBCTestListGraphicGulIconIndex );
    CleanupStack::PushL( icons );    
    GraphicIconL( icons );
    dlg->SetIconArrayL( icons );
    CArrayPtr<CGulIcon>* getIcons = dlg->IconArray();    
    AssertTrueL( ( getIcons == icons ), KSelSetIconArray );
    CleanupStack::Pop( icons );
    
    dlg->SetSizeAndPosition( iContainer->Rect().Size() );
    
    dlg->HandleListBoxEventL( 
        dlg->ListBox(), 
        MEikListBoxObserver::EEventEnterKeyPressed );    
    AssertTrueL( ETrue, KSelHandleListEvent );
    
    dlg->SelectionListProcessCommandL( EAknMarkAll );    
    AssertTrueL( ETrue, KSelSelListProcCmd );
    
    dlg->ProcessCommandL( EAknUnmarkAll );    
    AssertTrueL( ETrue, KSelProcCmd );
    
    SEikControlInfo info = dlg->CreateCustomControlL( 
        EAknCtSingleNumberListBox );
    AssertTrueL( ETrue, KSelCustomCtrl );
    delete info.iControl;
    
    TRect rect = iContainer->Rect();
    dlg->Draw( rect );
    AssertTrueL( ETrue, KSelDraw );
    
    CleanupStack::PopAndDestroy(); // for PrepareLC 
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( markedItems );
    }

// ---------------------------------------------------------------------------
// Test CAknMarkableListDialog
// ---------------------------------------------------------------------------
//
void CBCTestListSelectionCase::TestMarkableListDialogL()
    {
    TInt value( -1 );    
    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );
    CDesCArray* textArray = NULL;
   
    textArray = iEikEnv->ReadDesCArrayResourceL( R_BCTESTLIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );
    
    // test CAknMarkableListDialog::NewL
    CAknMarkableListDialog* markedDlg = CAknMarkableListDialog::NewL( 
        value, markedItems, textArray, 
        R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( markedDlg );    
    AssertNotNullL( markedDlg, KMarkedNewL );
    CleanupStack::PopAndDestroy( markedDlg );    
    
    // test API of CAknMarkableListDialog
    CBCMarkableListDialog* dlg = CBCMarkableListDialog::NewL(
        value, markedItems, textArray ); 
    CleanupStack::PushL( dlg );   
    dlg->PrepareLC( R_BCTESTLIST_MARKABLE_DIALOG );
    
    dlg->PreLayoutDynInitL();    
    AssertTrueL( ETrue, KSelPreLayout );
    
    dlg->PostLayoutDynInitL();    
    AssertTrueL( ETrue, KMarPostLayout );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    dlg->HandlePointerEventL( event );    
    AssertTrueL( ETrue, KSelHandlePointer );
            
    dlg->SelectionListProcessCommandL( EAknMarkAll );    
    AssertTrueL( ETrue, KMarSelListProcCmd );
    
    dlg->ProcessCommandL( EAknUnmarkAll );    
    AssertTrueL( ETrue, KMarPreProcCmd );
    
    CEikMenuPane* menuPane = new( ELeave ) CEikMenuPane( dlg );
    CleanupStack::PushL( menuPane );    
    dlg->DynInitMenuPaneL( R_BCTESTLIST_COLUMN_MENU, menuPane );    
    AssertTrueL( ETrue, KSelDynMenPane );
    CleanupStack::PopAndDestroy( menuPane );
    
    dlg->HandleListBoxEventL( dlg->ListBox(), 
        MEikListBoxObserver::EEventItemClicked );    
    AssertTrueL( ETrue, KMarHandleListEvent );
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyLeftArrow;    
    dlg->OfferKeyEventL( keyEvent, EEventKey );
    keyEvent.iCode = 'M';
    dlg->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KMarOfferKey );
    
    dlg->OkToExitL( EAknSoftkeyOk );    
    AssertTrueL( ETrue, KMarOK );    
    
    CleanupStack::PopAndDestroy(); //prepareLC
    CleanupStack::Pop( dlg );
    CleanupStack::PopAndDestroy( textArray );    
    CleanupStack::PopAndDestroy( markedItems );
    }

// ---------------------------------------------------------------------------
// GraphicIconL
// ---------------------------------------------------------------------------
//
void CBCTestListSelectionCase::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        CreateIconAndAddToArrayL(
            aIcons, KBCTestListMifFileName,
            EMbmBctestlistQgn_indi_marked_add,
            EMbmBctestlistQgn_indi_marked_add_mask );
        CreateIconAndAddToArrayL(
            aIcons, KBCTestListMbmFileName,
            EMbmBctestlistGolgo2,
            EMbmBctestlistGolgo2_mask );            
        }
    }
 
// ======== MEMBER FUNCTIONS ========
// CBCMarkableListDialog

// ---------------------------------------------------------------------------
// Symbian 2nd constructor
// ---------------------------------------------------------------------------
//
CBCMarkableListDialog* CBCMarkableListDialog::NewL( TInt &aValue, 
    CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray )
    {
    CBCMarkableListDialog* self = new( ELeave ) CBCMarkableListDialog(
        aValue, aSelectedItems, aArray, 
        R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( self );
    self->ConstructL( R_AVKON_DIALOG_EMPTY_MENUBAR );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ constructor
// ---------------------------------------------------------------------------
//
CBCMarkableListDialog::CBCMarkableListDialog( 
    TInt &aValue, CArrayFix<TInt> *aSelectedItems, 
    MDesCArray *aArray, TInt aMenuBarResourceId, 
    TInt aOkMenuBarResourceId, MEikCommandObserver *aObserver ):
    CAknMarkableListDialog( aValue, aSelectedItems, aArray, aMenuBarResourceId,
        aOkMenuBarResourceId, aObserver )
    {    
    }
    
// ======== MEMBER FUNCTIONS ========
// CBCSelectionListDialog

// ---------------------------------------------------------------------------
// Symbian 2nd constructor
// ---------------------------------------------------------------------------
//
CBCSelectionListDialog* CBCSelectionListDialog::NewL( TInt &aValue, 
    MDesCArray *aArray )
    {
    CBCSelectionListDialog* self = new( ELeave ) CBCSelectionListDialog(
        aValue, aArray, NULL );
    CleanupStack::PushL( self );
    self->ConstructL( R_AVKON_DIALOG_EMPTY_MENUBAR );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ constructor
// ---------------------------------------------------------------------------
//
CBCSelectionListDialog::CBCSelectionListDialog( 
    TInt &aValue, MDesCArray *aArray,    
    MEikCommandObserver *aObserver ):
    CAknSelectionListDialog( aValue, aArray, aObserver )
    {    
    }
