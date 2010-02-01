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
* Description:         test case for aknlistquery
*
*/









#include <w32std.h>
#include <eikenv.h>
#include <aknlistquerycontrol.h>
#include <barsread.h>
#include <aknutils.h>
#include <akniconutils.h>
#include <avkon.mbg>

#include "bctestlistquery.h"
#include "bctestquerycontainer.h"
#include "bctestquery.hrh"
#include <bctestquery.rsg>

_LIT( KListQueryTest1, "CBCTestListQueryDialog constructor" );
_LIT( KListQueryTest2, "CBCTestListQueryDialog::ExecuteLD" );
_LIT( KListQueryTest3, "CBCTestListQueryDialog constructor with index array" );
_LIT( KListQueryTest4, "CBCTestListQueryDialog::SetItemTextArray" );
_LIT( KListQueryTest5, "CBCTestListQueryDialog::SetOwnershipType" );
_LIT( KListQueryTest6, "CBCTestListQueryDialog::PreLayoutDynInitL" );
_LIT( KListQueryTest7, "CBCTestListQueryDialog::PostLayoutDynInitL" );
_LIT( KListQueryTest8, "CBCTestListQueryDialog::BorderStyle" );
_LIT( KListQueryTest9, "CBCTestListQueryDialog::SetTone" );
_LIT( KListQueryTest10, "CBCTestListQueryDialog::SetSizeAndPosition" );
_LIT( KListQueryTest11, "CBCTestListQueryDialog::OfferKeyEventL" );
_LIT( KListQueryTest12, "CBCTestListQueryDialog::HandleListBoxEventL" );
_LIT( KListQueryTest13, "CBCTestListQueryDialog::ListBox" );
_LIT( KListQueryTest14, "CBCTestListQueryDialog::SetIconArrayL" );
_LIT( KListQueryTest15, "CBCTestListQueryDialog::ListControl" );
_LIT( KListQueryTest16, "CAknListQueryControl::FocusChanged" );
_LIT( KListQueryTest17, "CAknListQueryControl::OfferKeyEventL" );
_LIT( KListQueryTest18, "CAknListQueryControl::HandlePointerEventL" );
_LIT( KListQueryTest19, "CBCTestListQueryDialog::MessageBox" );
_LIT( KListQueryTest20, "CBCTestListQueryDialog::QueryHeading" );
_LIT( KListQueryTest21, "CBCTestListQueryDialog::FindBox" );
_LIT( KListQueryTest22, "CBCTestListQueryDialog::ActivateL" );
_LIT( KListQueryTest23, "CBCTestListQueryDialog::HandlePointerEventL" );
_LIT( KListQueryTest24, "CBCTestListQueryDialog::OkToExitL" );
_LIT( KListQueryTest25, "CBCTestListQueryDialog::CloseState" );

_LIT( KMessageText, "Message Text" );
_LIT( KHeaderText, "Header Text" );
_LIT( KMsgQueryTest1, "CAknMessageQueryDialog::NewL" );
_LIT( KMsgQueryTest2, "CAknMessageQueryDialog::ExecuteLD" );
_LIT( KMsgQueryTest3, "CAknMessageQueryDialog constructor" );
_LIT( KMsgQueryTest4, "CAknMessageQueryDialog::SetSizeAndPosition" );
_LIT( KMsgQueryTest5, "CAknMessageQueryDialog::PreLayoutDynInitL" );
_LIT( KMsgQueryTest6, "CAknMessageQueryDialog::PostLayoutDynInitL" );
_LIT( KMsgQueryTest7, "CAknMessageQueryDialog::SetMessageTextL" );
_LIT( KMsgQueryTest8, "CAknMessageQueryDialog::SetHeaderTextL" );
_LIT( KMsgQueryTest9, "CAknMessageQueryDialog::SetLinkTextL" );
_LIT( KMsgQueryTest10, "CAknMessageQueryDialog::SetLink" );
_LIT( KMsgQueryTest11, "CAknMessageQueryDialog::OfferKeyEventL" );
_LIT( KMsgQueryTest12, "CAknMessageQueryDialog::HandlePointerEventL" );
_LIT( KMsgQueryTest13, "CAknMessageQueryDialog::ProcessCommandL" );
_LIT( KMsgQueryTest14, "CAknMessageQueryDialog::OkToExitL" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListQuery* CBCTestListQuery::NewL( CBCTestQueryContainer* aContainer,
    CEikonEnv* aEnv )
    {
    CBCTestListQuery* self = new( ELeave ) CBCTestListQuery(
        aContainer, aEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestListQuery::CBCTestListQuery(  CBCTestQueryContainer* aContainer,
    CEikonEnv* aEnv ): iContainer( aContainer ), iEnv( aEnv )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListQuery::~CBCTestListQuery()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListQuery::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestListQuery::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListQuery::BuildScriptL()
    {
    // outline1
    AddTestL( DELAY( 1 ), LeftCBA, KeyOK, TEND );
    AddTestL( KeyOK, REP( Down, 3), REP( Up, 2 ), LeftCBA, TEND );
    AddTestL( RightCBA, TEND );

    // outline2
    AddTestL( LeftCBA, KeyOK, TEND );
    AddTestL( Down, KeyOK, LeftCBA, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestListQuery::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListQuery::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline01 || aCmd > EBCTestCmdOutline02 )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestCmdOutline01:
            TestListQueryDialogL();
            break;
        case EBCTestCmdOutline02:
            TestMessageQueryDialogL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestListQuery::TestListQueryDialogL
// ---------------------------------------------------------------------------
//
void CBCTestListQuery::TestListQueryDialogL()
    {
    TInt index = 0;
    CBCTestListQueryDialog* dlg = new( ELeave ) CBCTestListQueryDialog(
        &index );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KListQueryTest1 );

    dlg->ExecuteLD( R_BCTESTQUERY_MULTI_SELECTION_QUERY );
    AssertTrueL( ETrue, KListQueryTest2 );
    CleanupStack::Pop( dlg );
    dlg = NULL;

    dlg = new( ELeave ) CBCTestListQueryDialog( &index );
    dlg->PrepareLC( R_BCTESTQUERY_EMPTY_QUERY );
    dlg->ActivateL();
    CleanupStack::Pop( dlg );

    TRect rect = iContainer->Rect();
    TSize size = rect.Size();

    CDesCArray* textArray = iEnv->ReadDesCArrayResourceL(
        R_BCTESTQUERY_MULTI_SELECTION_QUERY_LIST_ITEM );
    CleanupStack::PushL( textArray );

    CArrayFix<TInt>* indexArray = new( ELeave ) CArrayFixFlat<TInt>( 4 );
    CleanupStack::PushL( indexArray );
    indexArray->AppendL( 0 );
    indexArray->AppendL( 1 );

    dlg = new( ELeave ) CBCTestListQueryDialog( indexArray );
    dlg->PrepareLC( R_BCTESTQUERY_MULTI_SELECTION_QUERY );
    AssertTrueL( ETrue, KListQueryTest3 );

    dlg->SetItemTextArray( textArray );
    AssertTrueL( ETrue, KListQueryTest4 );

    dlg->SetOwnershipType( ELbmOwnsItemArray );
    AssertTrueL( ETrue, KListQueryTest5 );

    dlg->PreLayoutDynInitL();
    AssertTrueL( ETrue, KListQueryTest6 );

    dlg->PostLayoutDynInitL();
    AssertTrueL( ETrue, KListQueryTest7 );

    TInt style = dlg->BorderStyle();
    AssertTrueL( ETrue, KListQueryTest8 );

    dlg->SetTone( CAknQueryDialog::ENoTone );
    AssertTrueL( ETrue, KListQueryTest9 );

    dlg->SetSizeAndPosition( size );
    AssertTrueL( ETrue, KListQueryTest10 );

    TKeyEvent eventT = { 'T', 'T', 0, 0 };
    dlg->OfferKeyEventL( eventT, EEventKey );
    AssertTrueL( ETrue, KListQueryTest11 );

    dlg->HandleListBoxEventL(
        dlg->ListBox(),
        MEikListBoxObserver::EEventEnterKeyPressed );
    AssertTrueL( ETrue, KListQueryTest12 );
    AssertTrueL( ETrue, KListQueryTest13 );

    CArrayPtr<CGulIcon>* icons = new( ELeave ) CArrayPtrFlat<CGulIcon>(
            4 );
    CleanupStack::PushL( icons );
    GraphicIconL( icons );
    dlg->SetIconArrayL( icons );
    CleanupStack::Pop( icons );
    AssertTrueL( ETrue, KListQueryTest14 );

    CAknListQueryControl* listControl = dlg->ListControl();
    AssertTrueL( ETrue, KListQueryTest15 );

    listControl->FocusChanged( ENoDrawNow );
    AssertTrueL( ETrue, KListQueryTest16 );

    TKeyEvent eventEnter = { EKeyEnter, EKeyEnter, 0, 0 };
    listControl->OfferKeyEventL( eventEnter,  EEventKey );
    AssertTrueL( ETrue, KListQueryTest17 );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listControl->HandlePointerEventL( event );
    AssertTrueL( ETrue, KListQueryTest18 );

    CAknMessageQueryControl* message = dlg->MessageBox();
    AssertTrueL( ETrue, KListQueryTest19 );

    CAknPopupHeadingPane* pane = dlg->QueryHeading();
    AssertTrueL( ETrue, KListQueryTest20 );

    CAknSearchField* field = dlg->FindBox();
    AssertTrueL( ETrue, KListQueryTest21 );

    dlg->ActivateL();
    AssertTrueL( ETrue, KListQueryTest22 );

    event.iType = TPointerEvent::EButton2Up;
    dlg->HandlePointerEventL( event );
    AssertTrueL( ETrue, KListQueryTest23 );

    dlg->OkToExitL( EAknSoftkeyOk );
    AssertTrueL( ETrue, KListQueryTest24 );

    dlg->CloseState();
    AssertTrueL( ETrue, KListQueryTest25 );

    CleanupStack::Pop( dlg );
    CleanupStack::PopAndDestroy( indexArray );
    CleanupStack::Pop( textArray );

    TestListQuerySetSizeAndPositionL(
        R_BCTESTQUERY_SINGLEPOPUPMENU_QUERY );
    TestListQuerySetSizeAndPositionL(
        R_BCTESTQUERY_SINGLEGRAPHICHEADING_QUERY );
    TestListQuerySetSizeAndPositionL( R_BCTESTQUERY_MENUDOUBLE_QUERY );
    TestListQuerySetSizeAndPositionL(
        R_BCTESTQUERY_DOUBLELARGEGRAPHIC_QUERY );
    TestListQuerySetSizeAndPositionL(
        R_BCTESTQUERY_SINGLEHEADING_QUERY );
    TestListQuerySetSizeAndPositionL(
        R_BCTESTQUERY_DOUBLE2_QUERY );

    // NOTE: DO NOT USE this LIST (break ui-style, only for java)!!!
    //TestListQuerySetSizeAndPositionL(
    //    R_BCTESTQUERY_SINGLE2GRAPHIC_QUERY );
    }

// ---------------------------------------------------------------------------
// To improve branch coverage of SetSizeAndPosition
// ---------------------------------------------------------------------------
//
void CBCTestListQuery::TestListQuerySetSizeAndPositionL( TInt aResourceId )
    {
    TInt index = 0;
    CBCTestListQueryDialog* dlg = new( ELeave )
        CBCTestListQueryDialog( &index );
    dlg->PrepareLC( aResourceId );
    dlg->PreLayoutDynInitL();
    TSize size = iContainer->Rect().Size();
    dlg->SetSizeAndPosition( size );
    CleanupStack::PopAndDestroy( dlg );
    }

// ---------------------------------------------------------------------------
// Test CAknMessageQueryDialog
// ---------------------------------------------------------------------------
//
void CBCTestListQuery::TestMessageQueryDialogL()
    {
    TPtrC msg( KMessageText );
    CAknMessageQueryDialog* msgDlg = CAknMessageQueryDialog::NewL(
        msg, CAknQueryDialog::ENoTone );
    CleanupStack::PushL( msgDlg );
    AssertNotNullL( msgDlg, KMsgQueryTest1 );

    msgDlg->ExecuteLD( R_AVKON_MESSAGE_QUERY_DIALOG, KMessageText );
    AssertTrueL( ETrue, KMsgQueryTest2 );
    CleanupStack::Pop( msgDlg );

    CBCTestMessageQueryDialog* dlg = new( ELeave )
        CBCTestMessageQueryDialog( CAknQueryDialog::EConfirmationTone );
    dlg->PrepareLC( R_AVKON_MESSAGE_QUERY_DIALOG );
    AssertTrueL( ETrue, KMsgQueryTest3 );

    TSize size = iContainer->Rect().Size();
    dlg->SetSizeAndPosition( size );
    AssertTrueL( ETrue, KMsgQueryTest4 );

    dlg->PreLayoutDynInitL();
    AssertTrueL( ETrue, KMsgQueryTest5 );

    dlg->PostLayoutDynInitL();
    AssertTrueL( ETrue, KMsgQueryTest6 );

    dlg->SetMessageTextL( KMessageText );
    AssertTrueL( ETrue, KMsgQueryTest7 );

    dlg->SetHeaderTextL( KHeaderText );
    AssertTrueL( ETrue, KMsgQueryTest8 );

    dlg->SetLinkTextL( KMessageText );
    AssertTrueL( ETrue, KMsgQueryTest9 );

    TCallBack callBack;
    dlg->SetLink( callBack );
    AssertTrueL( ETrue, KMsgQueryTest10 );

    TKeyEvent eventT = { 'T', 'T', 0, 0 };
    dlg->OfferKeyEventL( eventT, EEventKey );
    AssertTrueL( ETrue, KMsgQueryTest11 );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Up;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    dlg->HandlePointerEventL( event );
    AssertTrueL( ETrue, KMsgQueryTest12 );

    dlg->ProcessCommandL( EAknSoftkeyView );
    AssertTrueL( ETrue, KMsgQueryTest13 );

    dlg->OkToExitL( EAknSoftkeyOk );
    AssertTrueL( ETrue, KMsgQueryTest14 );

    CleanupStack::PopAndDestroy( dlg );
    }

// ---------------------------------------------------------------------------
// Set graphic icon Array
// ---------------------------------------------------------------------------
//
void CBCTestListQuery::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        CreateIconAndAddToArrayL( aIcons, AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_indi_marked_add,
            EMbmAvkonQgn_indi_marked_add_mask );
        CreateIconAndAddToArrayL( aIcons, AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_prop_folder_medium,
            EMbmAvkonQgn_prop_folder_medium_mask );
        }
    }

// ----------------------------------------------------------------------------
// Creates the icon and adds it to the array if it was successful
// ----------------------------------------------------------------------------
//
void CBCTestListQuery::CreateIconAndAddToArrayL(
    CArrayPtr<CGulIcon>*& aIconsArray,
    const TDesC& aIconFile,
    TInt aBitmap, TInt aMask/* = -1*/)
    {
    CGulIcon* icon = CGulIcon::NewLC();
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    if (aMask >= 0)
        {
        AknIconUtils::CreateIconL( bitmap, mask, aIconFile, aBitmap, aMask);
        }
    else
        {
        bitmap = AknIconUtils::CreateIconL( aIconFile, aBitmap);
        }

    if (bitmap)
        {
        icon->SetBitmap(bitmap);
        if (mask)
            icon->SetMask(mask);
        aIconsArray->AppendL(icon);
        CleanupStack::Pop(icon);
        }
    else
        {
        CleanupStack::PopAndDestroy(icon);
        }
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestListQueryDialog::CBCTestListQueryDialog( TInt* aIndex )
    : CAknListQueryDialog( aIndex )
    {
    }

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestListQueryDialog::CBCTestListQueryDialog(
    CListBoxView::CSelectionIndexArray* aSelectionIndexArray  )
    : CAknListQueryDialog( aSelectionIndexArray )
    {
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestMessageQueryDialog::CBCTestMessageQueryDialog( const TTone aTone )
    : CAknMessageQueryDialog( aTone )
    {
    }
